/*!
\file
\brief TFCpp global functions
*/

//include guard
#ifndef TFCPP_T_HPP
#define TFCPP_T_HPP

//core headers
#include <vector>

//lib headers
#include <tensorflow/cc/ops/standard_ops.h>         //operations
#include <tensorflow/cc/framework/gradients.h>      //optimisers
#include <tensorflow/core/framework/tensor.h>       //data
#include <tensorflow/core/framework/tensor_shape.h> //data
#include <tensorflow/cc/client/client_session.h>    //run

//custom headers (generic)
#include <types.hpp>

//custom headers (ML)
#include <tfcpp/model.hpp>

//use core namespaces
using namespace std;

//use lib namespaces
using namespace tensorflow;
using namespace tensorflow::ops;

//namespaces
namespace tfcpp {

  //namespace static vars
  extern Scope R;

  /*!
  \brief Initialise machine learning
  */
  void init_ml();

  /*!
  \brief Build a DNN model
  */
  model* build_dnn_classifier(long Num_Inputs,vector<long> Hidden_Units,long Num_Classes);

//namespaces
}

//include guard
#endif

//eof