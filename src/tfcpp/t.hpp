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

  /*!
  \brief Demangle typeid name,
         Example: demangle_type(typeid(Some_Var).name())
         https://stackoverflow.com/a/34916852/5581893
  */
  string demangle_type(const char* Type_Id_Name);

  /*!
  \brief Initialise machine learning
  */
  void init_ml();

  /*!
  \brief Build a DNN model
  */
  dnn_classifier* build_dnn_classifier(long Num_Inputs,ilong Hidden_Units,long Num_Classes);

//namespaces
}

//include guard
#endif

//eof