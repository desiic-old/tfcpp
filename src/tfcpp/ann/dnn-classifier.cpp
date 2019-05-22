/*!
\file
\brief DNN model class source file
*/

//core headers
#include <vector>
#include <initializer_list>

//custom headers
#include <tfcpp/t.hpp>
#include <tfcpp/ann/dnn-classifier.hpp>

//use namespaces (core)
using namespace std;

//shortcuts
using ilong   = initializer_list<long>;
using applygd = ApplyGradientDescent;

//namespaces
namespace tfcpp {

  /*!
  \brief Constructor
  */
  dnn_classifier::dnn_classifier(long Num_Inputs,ilong Hidden_Units,long Num_Classes){
    this->Num_Inputs   = Num_Inputs;
    this->Hidden_Units = Hidden_Units;
    this->Num_Classes  = Num_Classes;
  }

  /*!
  \brief Model destructor
  */
  dnn_classifier::~dnn_classifier(){
    delete this->Out_Weight;
    delete this->Out_Bias;
    delete this->Out;
    delete this->Probs;
    delete this->Loss;
  }

  /*!
  \brief Init the model
  */
  void dnn_classifier::init_weights_and_biases(){

    //create weights & biases (including output layer)
    long Num_Hiddens = this->Hidden_Units.size();

    for (long I=0; I<=Num_Hiddens; I++){      
      long Num_Units = this->Hidden_Units[I];        

      if (I==0){ //first hidden layer, connects to input
        this->Weights.push_back(Variable(R, {Num_Inputs,Num_Units}, DT_FLOAT));
      }
      else
      if (I==Num_Hiddens){ //output layer
        long Last_Hidden_Size = this->Hidden_Units[Num_Hiddens-1];
        this->Out_Weight   = new Variable(R, {Last_Hidden_Size,Num_Classes}, DT_FLOAT);
      }
      else { //other hidden layers
        long Prev_Num_Units = this->Hidden_Units[I-1];
        this->Weights.push_back(Variable(R, {Prev_Num_Units,Num_Units}, DT_FLOAT));
      }

      if (I==Num_Hiddens)
        this->Out_Bias = new Variable(R, {Num_Classes}, DT_FLOAT);
      else
        this->Biases.push_back(Variable(R, {Num_Units}, DT_FLOAT));
    }//hidden units loop

    //init weights and biases
    for (long I=0; I<=Num_Hiddens; I++){
      long    Num_Units = this->Hidden_Units[I];
      Assign* Weight_Init;
      Assign* Bias_Init;

      if (I==0){ //first hidden layer
        Weight_Init = new Assign(R, this->Weights[I], 
                          RandomNormal(R, {(int)Num_Inputs,(int)Num_Units}, DT_FLOAT));
        Bias_Init   = new Assign(R, this->Biases[I],  
                          RandomNormal(R,{(int)Num_Units}, DT_FLOAT)); 
      }
      else
      if (I==Num_Hiddens){ //output layer
        long Prev_Num_Units = this->Hidden_Units[Num_Hiddens-1];
        Weight_Init         = new Assign(R, *this->Out_Weight, 
                                  RandomNormal(R, {(int)Prev_Num_Units,(int)Num_Classes}, DT_FLOAT));
        Bias_Init           = new Assign(R, *this->Out_Bias,  
                                  RandomNormal(R, {(int)Num_Classes}, DT_FLOAT)); 
      }  
      else { //other hidden layer
        long Prev_Num_Units = this->Hidden_Units[I-1];
        Weight_Init         = new Assign(R, this->Weights[I], 
                                  RandomNormal(R, {(int)Prev_Num_Units,(int)Num_Units}, DT_FLOAT));
        Bias_Init           = new Assign(R, this->Biases[I],  
                                  RandomNormal(R, {(int)Num_Units}, DT_FLOAT));         
      }//if index

      TF_CHECK_OK(
        Sess.Run({*Weight_Init,*Bias_Init},nullptr)        
      );
      delete Weight_Init;
      delete Bias_Init;
    }//init loop
  }//init Ws & Bs  

  /*!
  \brief Create hidden layers
  */
  void dnn_classifier::create_hidden_layers(){
    long Num_Hiddens = this->Hidden_Units.size();

    for (long I=0; I<Num_Hiddens; I++){
      long Num_Units = this->Hidden_Units[I];

      if (I==0){
        Relu Layer = Relu(R, Add(R, MatMul(R,this->Inp, this->Weights[I]), this->Biases[I]));
        this->Hiddens.push_back(Layer);
      }
      else{
        Relu Layer = Relu(R, Add(R, MatMul(R,this->Weights[I-1], this->Weights[I]), this->Biases[I]));
        this->Hiddens.push_back(Layer);
      }
    }//hidden layer loop
  }

  /*!
  \brief Create output
  */
  void dnn_classifier::create_output_layer(){
    long Num_Hiddens = this->Hidden_Units.size();
    this->Out       = new Identity(R, Add(R, 
                         MatMul(R,this->Hiddens[Num_Hiddens-1],*this->Out_Weight), 
                         *this->Out_Bias
                       ));
  }

  /*!
  \brief Finalise with probabilities, loss, and gradients
  */
  void dnn_classifier::finalise(){
    this->Probs = new Softmax(R, *this->Out);
    this->Loss  = new Sum(R, Square(R, Sub(R, this->Expected, *this->Probs)), {0,1});

    //create optimiser
    vector<Output> Grad_Outputs;
    vector<Output> Loss; 
    vector<Output> Vars;

    Loss.push_back(*this->Loss);
    long Num_Hiddens = this->Hidden_Units.size();

    for (long I=0; I<Num_Hiddens; I++)
      Vars.push_back(this->Weights[I]);
    for (long I=0; I<Num_Hiddens; I++)
      Vars.push_back(this->Biases[I]);

    TF_CHECK_OK(
      AddSymbolicGradients(R, Loss, Vars, &Grad_Outputs)
    );

    for (long I=0; I<Num_Hiddens; I++){
      applygd Optim = ApplyGradientDescent(R, this->Weights[I], Cast(R,0.01,DT_FLOAT), {Grad_Outputs[I]});
      this->Optims.push_back(Optim);
    }

    for (long I=0; I<Num_Hiddens; I++){
      applygd Optim = ApplyGradientDescent(R, this->Biases[I], Cast(R,0.01,DT_FLOAT), {Grad_Outputs[Num_Hiddens+I]});
      this->Optims.push_back(Optim);
    } 
  }

//namespaces
}

//eof