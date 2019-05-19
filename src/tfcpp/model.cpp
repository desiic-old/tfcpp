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

    //create weights & biases
    for (long I=0; I<Hidden_Units.size(); I++){      
      long Num_Units = Hidden_Units[I];        

      if (I==0) //first hidden layer, connects to input
        this->Weights.push_back(Variable(R, {Num_Inputs,Num_Units}, DT_FLOAT));
      else {
        long Prev_Num_Units = Hidden_Units[I-1];
        this->Weights.push_back(Variable(R, {Prev_Num_Units,Num_Units}, DT_FLOAT));
      }

      this->Biases.push_back(Variable(R, {Num_Units}, DT_FLOAT));
    }//hidden units loop
  }//constructor

  /*!
  \brief Model destructor
  */
  model::~model(){
    //
  }

//namespaces
}

//eof