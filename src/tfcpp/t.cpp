/*!
\file
\brief TFCpp functions
*/

//core headers
#include <iostream>
#include <vector>

//lib headers
#include <tensorflow/cc/ops/standard_ops.h>         //operations
#include <tensorflow/cc/framework/gradients.h>      //optimisers
#include <tensorflow/core/framework/tensor.h>       //data
#include <tensorflow/core/framework/tensor_shape.h> //data
#include <tensorflow/cc/client/client_session.h>    //run

//custom headers (generic)
#include <tfcpp/t.hpp>

//custom headers (ML)
#include <tfcpp/model.hpp>

//use core namespaces
using namespace std;

//namespaces
namespace tfcpp {

  //namespace variables
  Scope R = Scope::NewRootScope();

  /*!
  \brief Init machine learning
  */
  void init_ml(){
    //
  }

  /*!
  \brief Build DNN classifier
  */
  model* build_dnn_classifier(long Num_Inputs,vector<long> Hidden_Units,long Num_Classes){
    return new model(Num_Inputs,Hidden_Units,Num_Classes);
  }

//namespaces
}

//eof