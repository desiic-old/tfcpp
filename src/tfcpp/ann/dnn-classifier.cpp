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
using ilong = initializer_list<long>;

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
    delete this->Output_Weight;
    delete this->Output_Bias;
    delete this->Output;
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
        this->Output_Weight   = new Variable(R, {Last_Hidden_Size,Num_Classes}, DT_FLOAT);
      }
      else { //other hidden layers
        long Prev_Num_Units = this->Hidden_Units[I-1];
        this->Weights.push_back(Variable(R, {Prev_Num_Units,Num_Units}, DT_FLOAT));
      }

      if (I==Num_Hiddens)
        this->Output_Bias = new Variable(R, {Num_Classes}, DT_FLOAT);
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
        Weight_Init         = new Assign(R, *this->Output_Weight, 
                                  RandomNormal(R, {(int)Prev_Num_Units,(int)Num_Classes}, DT_FLOAT));
        Bias_Init           = new Assign(R, *this->Output_Bias,  
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
        Relu Layer = Relu(R, Add(R, MatMul(R,this->Input, this->Weights[I]), this->Biases[I]));
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
    this->Output     = new Identity(R, Add(R, 
                         MatMul(R,this->Hiddens[Num_Hiddens-1],*this->Output_Weight), 
                         *this->Output_Bias
                       ));
  }

  /*!
  \brief Finalise with probabilities and loss
  */
  void dnn_classifier::finalise(){
    this->Probs = new Softmax(R, *this->Output);
    this->Loss  = new Sum(R, Square(R, Sub(R, this->Expected, *this->Probs)), {0,1});

    //create optimiser
    //TODO
  }

//namespaces
}

//eof