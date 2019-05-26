/*!
\file
\brief TFCpp global functions
*/

//include guard
#ifndef TFCPP_T_HPP
#define TFCPP_T_HPP

//core headers
#include <vector>
#include <string>
#include <initializer_list>

//lib headers (generic)
#include <boost/core/demangle.hpp>

//lib headers (ML)
#include <tensorflow/cc/ops/standard_ops.h>         //operations
#include <tensorflow/cc/framework/gradients.h>      //optimisers
#include <tensorflow/core/framework/tensor.h>       //data
#include <tensorflow/core/framework/tensor_shape.h> //data
#include <tensorflow/cc/client/client_session.h>    //run

//custom headers (generic)
#include <types.hpp>

//custom headers (ML)
#include <tfcpp/ann/dnn-classifier.hpp>

//use core namespaces
using namespace std;

//use lib namespaces
using namespace tensorflow;
using namespace tensorflow::ops;

//shortcuts
using     ilong = initializer_list<long>;
namespace tf    = tensorflow;

//namespaces
namespace tfcpp {

  //namespace static vars
  extern Scope         R;
  extern ClientSession Sess;

  //exit with zero status
  void exit();

  //demangle typeid name
  string demangle_type(const char* Type_Id_Name);

  //get index of max value
  template <typename Type>
  long argmax(vector<Type> List);

  //initialise machine learning
  void init_ml();

  //build a DNN model
  dnn_classifier* build_dnn_classifier(long Num_Inputs,ilong Hidden_Units,long Num_Classes);

//namespaces
}

//include guard
#endif

//eof