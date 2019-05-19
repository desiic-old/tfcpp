/*!
\file
\brief Generic model class file
*/

//include guard
#ifndef TFCPP_MODEL_HPP
#define TFCPP_MODEL_HPP

//lib headers
#include <tensorflow/cc/ops/standard_ops.h>         //operations
#include <tensorflow/cc/framework/gradients.h>      //optimisers
#include <tensorflow/core/framework/tensor.h>       //data
#include <tensorflow/core/framework/tensor_shape.h> //data
#include <tensorflow/cc/client/client_session.h>    //run

//use namespaces (libs)
using namespace tensorflow;
using namespace tensorflow::ops;

//shortcuts
namespace tf = tensorflow;

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
      Placeholder Input    = Placeholder(R, DT_FLOAT);
      Placeholder Expected = Placeholder(R, DT_FLOAT);

    //constructors & methods
    public:
      model();
  };

//namespaces
}

//include guard
#endif 

//eof