/*!
\file
\brief DNN model class source file
*/

//core headers
#include <vector>

//custom headers
#include <tfcpp/model.hpp>

//use namespaces (core)
using namespace std;

//namespaces
namespace tfcpp {

  /*!
  \brief Constructor
  */
  model::model(long Num_Inputs,vector<long> Hidden_Units,long Num_Classes){
    this->Num_Inputs   = Num_Inputs;
    this->Hidden_Units = Hidden_Units;
    this->Num_Classes  = Num_Classes;
  }

  /*!
  \brief Model destructor
  */
  model::~model(){
    //
  }

//namespaces
}

//eof