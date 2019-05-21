/*!
\file
\brief TFCpp functions
*/

//core headers
#include <iostream>
#include <vector>
#include <initializer_list>

//lib headers
#include <tensorflow/cc/ops/standard_ops.h>         //operations
#include <tensorflow/cc/framework/gradients.h>      //optimisers
#include <tensorflow/core/framework/tensor.h>       //data
#include <tensorflow/core/framework/tensor_shape.h> //data
#include <tensorflow/cc/client/client_session.h>    //run

//custom headers (generic)
#include <tfcpp/t.hpp>

//custom headers (ML)
#include <tfcpp/ann/dnn-classifier.hpp>

//use core namespaces
using namespace std;

//shortcuts
using ilong = initializer_list<long>;

//namespaces
namespace tfcpp {

  //namespace variables
  Scope         R    = Scope::NewRootScope();
  ClientSession Sess = ClientSession(R); 

  /*!
  \brief Demangle typeid name,
         Example: demangle_type(typeid(Some_Var).name())
  */
  string demangle_type(const char* Type_Id_Name){
    return boost::core::demangle(Type_Id_Name);
  }

  /*!
  \brief Init machine learning
  */
  void init_ml(){
    cout <<"Root scope:\x20" <<demangle_type(typeid(R).name()) <<endl;
  }

  /*!
  \brief Build DNN classifier
  */
  dnn_classifier* build_dnn_classifier(long Num_Inputs,ilong Hidden_Units,long Num_Classes){
    dnn_classifier* Model = new dnn_classifier(Num_Inputs,Hidden_Units,Num_Classes);
    Model->init_weights_and_biases();
    Model->create_hidden_layers();
    Model->create_output_layer();
    Model->finalise();
    return Model;
  }

//namespaces
}

//eof