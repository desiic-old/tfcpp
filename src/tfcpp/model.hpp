/*!
\file
\brief Generic model class file
*/

//include guard
#ifndef TFCPP_MODEL_HPP
#define TFCPP_MODEL_HPP

//core headers
#include <vector>
#include <initializer_list>

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
using     ilong = initializer_list<long>;
namespace tf    = tensorflow;

//namespaces
namespace tfcpp {

  //external
  extern Scope R;

  /*!
  \brief Generic model class
  */
  class model {

    //properties
    public:
      long         Num_Inputs;
      vector<long> Hidden_Units;
      long         Num_Classes;

      //tensorflow 1.7-->1.13 has Placeholder hidden from official doc,
      //but not deprecated in future, seen in 2.0 array_ops.
      //another way: use Tensor instead.
      //the first value in shape is batch size (?)
      //Tensor Input    = Tensor(DT_FLOAT, TensorShape({1,...}));
      //Tensor Expected = Tensor(DT_FLOAT, TensorShape({1,...}));
      Placeholder      Input    = Placeholder(R, DT_FLOAT);
      Placeholder      Expected = Placeholder(R, DT_FLOAT);
      vector<Variable> Weights;
      vector<Variable> Biases;

    //constructors & methods
    public:
      model(long Num_Inputs,ilong Hidden_Units,long Num_Classes);
      ~model();
  };

//namespaces
}

//include guard
#endif 

//eof