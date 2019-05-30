/*!
\file
\brief Generic model class file
*/

//include guard
#ifndef TFCPP_MODEL_HPP
#define TFCPP_MODEL_HPP

//core headers
#include <initializer_list>
#include <vector>
#include <utility>

//lib headers
#include <tensorflow/cc/ops/standard_ops.h>         //operations
#include <tensorflow/cc/framework/gradients.h>      //optimisers
#include <tensorflow/core/framework/tensor.h>       //data
#include <tensorflow/core/framework/tensor_shape.h> //data
#include <tensorflow/cc/client/client_session.h>    //run

//use namespaces (core)
using namespace std;

//use namespaces (libs)
using namespace tensorflow;
using namespace tensorflow::ops;

//shortcuts
using     ilong   = initializer_list<long>;
using     iilong  = initializer_list<initializer_list<long>>; 
using     batch   = pair<vector<vector<long>>,vector<vector<long>>>; //pair of input batch & expected batch
using     applygd = ApplyGradientDescent;
namespace tf      = tensorflow;

//namespaces
namespace tfcpp {

  //external
  extern Scope R;

  /*!
  \brief Generic model class
  */
  class dnn_classifier {

    //properties
    public:
      long         Num_Inputs;
      vector<long> Hidden_Units;
      long         Num_Classes;

      //tensorflow 1.7-->1.13 has Placeholder hidden from official doc,
      //but not deprecated in future, seen in 2.0 array_ops.
      //another way: use Tensor instead.
      //the first value in shape is batch size (?)
      //Tensor Inp      = Tensor(DT_FLOAT, TensorShape({1,...}));
      //Tensor Expected = Tensor(DT_FLOAT, TensorShape({1,...}));
      Placeholder      Inp      = Placeholder(R, DT_FLOAT); //avoid conflict with tf::Input
      Placeholder      Expected = Placeholder(R, DT_FLOAT); //probs, not labels

      vector<Variable> Weights;    //hidden layers
      vector<Variable> Biases;     //hidden layers
      vector<Relu>     Hiddens;    //outputs of hidden layers

      Variable*        Out_Weight; //output layer weight
      Variable*        Out_Bias;   //output layer bias
      Identity*        Out;        //output layer's output (shape: [Num_Classes])

      Softmax*         Probs;      //probabilities (shape: [Num_Classes])
      Sum*             Loss;       //loss, scalar
      vector<applygd>  Optims;     //optimisation operations

      //training data
      vector<vector<long>> All_Inps;
      vector<vector<long>> All_Expecteds; //probs, not labels

      //batch data for training, eval
      Tensor Inps;
      Tensor Expecteds; //probs, not labels

    //constructors & destructor
    public:
      dnn_classifier(long Num_Inputs,ilong Hidden_Units,long Num_Classes);
      ~dnn_classifier();

    //methods
    public:
      void init_weights_and_biases(); //all layers
      void create_hidden_layers();    //hidden layer functions
      void create_output_layer();     //output layer function
      void complete_model();          //add probabilities, loss, and gradients

      //training, eval, and predict
      void          set_training_data(vector<vector<long>> Inputs,vector<long> Labels);
      batch         get_rand_batch(long Size);
      void          set_batch(batch Batch);
      void          train();
      float         get_current_loss();
      vector<float> infer(vector<long> Sample); //probability vector
  };

//namespaces
}

//include guard
#endif 

//eof