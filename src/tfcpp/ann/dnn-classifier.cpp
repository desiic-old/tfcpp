/*!
\file
\brief DNN model class source file
*/

//core headers
#include <initializer_list>
#include <vector>
#include <utility>

//custom headers
#include <tfcpp/t.hpp>
#include <tfcpp/ann/dnn-classifier.hpp>

//use namespaces (core)
using namespace std;

//shortcuts
using ilong   = initializer_list<long>;
using batch   = pair<vector<vector<long>>,vector<vector<long>>>; //pair of input batch & expected batch
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
        this->Out_Weight      = new Variable(R, {Last_Hidden_Size,Num_Classes}, DT_FLOAT);
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
    this->Out        = new Identity(R, Add(R, 
                         MatMul(R,this->Hiddens[Num_Hiddens-1],*this->Out_Weight), 
                         *this->Out_Bias
                       ));
  }

  /*!
  \brief Complete model with probabilities, loss, and gradients
  */
  void dnn_classifier::complete_model(){
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

  /*!
  \brief Set training data
  */
  void dnn_classifier::set_training_data(vector<vector<long>> Inputs,vector<long> Labels){
    
    //add input data
    for (vector<long> const& Inp: Inputs){
      vector<long> Values = Inp;
      this->All_Inps.push_back(Values);
    }

    //create expected probs from labels
    for (long Label: Labels){
      vector<long> Values;

      for (long I=0; I<this->Num_Classes; I++)
        if (I==Label) Values.push_back(1);
        else          Values.push_back(0);

      this->All_Expecteds.push_back(Values);
    }
  }//set training data

  /*!
  \brief Get random batch from set training data
  */
  batch dnn_classifier::get_rand_batch(long Size){

    //create index list to shuffle,
    //can't shuffle All_Inps or All_Expecteds alone as they have to match each other.
    vector<long> Indices;
    for (long I=0; I<this->All_Inps.size(); I++)
      Indices.push_back(I);

    //shuffle
    random_shuffle(Indices.begin(),Indices.end());

    //get first batch
    vector<vector<long>> Inps;
    vector<vector<long>> Expecteds;

    for (long I=0; I<Size; I++){
      long Index = Indices[I];
      vector<long> Inp      = this->All_Inps[Index];
      vector<long> Expected = this->All_Expecteds[Index];

      Inps.push_back(Inp);
      Expecteds.push_back(Expected);
    }

    //build pair
    batch Pair = {Inps,Expecteds};
    return Pair;
  }

  /*!
  \brief A batch for training
  */
  void dnn_classifier::set_batch(batch Batch){
    long Size = Batch.first.size(); //=second.size()

    //create data tensors and set data
    this->Inps      = Tensor(DT_FLOAT, TensorShape({(int)Size, (int)this->Num_Inputs}));
    this->Expecteds = Tensor(DT_FLOAT, TensorShape({(int)Size, (int)this->Num_Classes}));    

    //data for inputs (network feed)
    //flat<float>(): returns an instance of a class with set/get overloads of '()'
    long I=0;
    for (vector<long> const& Inp: Batch.first)
      for (long Value: Inp){
        this->Inps.flat<float>()(I) = Value;
        I++;
      }

    //data for expecteds (loss calculation)
    //flat<float>(): returns an instance of a class with set/get overloads of '()'
    I=0;
    for (vector<long> const& Expected: Batch.second)
      for (long Value: Expected){
        this->Expecteds.flat<float>()(I) = Value;
        I++;
      }
  }

  /*!
  \brief Train using set batch
  */
  void dnn_classifier::train() {

    /*
    //apply optimisation on layers
    vector<Operation> Ops;
    for (long I=0; I<this->Optims.size(); I++)
      Ops.push_back((Operation)this->Optims[I]);

    //output op
    Ops.push_back((Operation)this->Out);
    */

    //run
    TF_CHECK_OK(
      Sess.Run(
        {{this->Inp,this->Inps},{this->Expected,this->Expecteds}}, 
        {this->Optims[0],this->Optims[1],*this->Out}, 
        nullptr
      )
    );    
  }

  /*!
  \brief Get current loss
  */
  float dnn_classifier::get_current_loss(){
    vector<Tensor> Outputs;

    TF_CHECK_OK(
      Sess.Run(
        {{this->Inp,this->Inps},{this->Expected,this->Expecteds}}, 
        {*this->Loss}, 
        &Outputs
      )
    );

    //loss is scalar, only 1 value in outputs
    //scalar<float>(): returns an instance of a class with set/get overloads of '()'
    return Outputs[0].scalar<float>()();
  }

  /*!
  \brief Infer a single input
  */
  vector<float> dnn_classifier::infer(vector<long> Sample){
    vector<Tensor> Outputs;

    //convert to tensor
    Tensor Infer_Inp = Tensor(DT_FLOAT, TensorShape({1,(int)this->Num_Inputs}));

    for (long I=0; I<this->Num_Inputs; I++)
      Infer_Inp.flat<float>()(I) = Sample[I];

    //run
    TF_CHECK_OK(
      Sess.Run({{this->Inp,Infer_Inp}}, {*this->Probs}, &Outputs)
    );

    //extract output values
    //scalar<float>(): returns an instance of a class with set/get overloads of '()'
    vector<float> Probs;

    for (long I=0; I<this->Num_Classes; I++)
      Probs.push_back(Outputs[0].flat<float>()(I));

    return Probs;
  }

//namespaces
}

//eof