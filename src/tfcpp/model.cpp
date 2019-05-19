/*!
\file
\brief DNN model class source file
*/

//core headers
#include <vector>
#include <initializer_list>

//custom headers
#include <tfcpp/t.hpp>
#include <tfcpp/model.hpp>

//use namespaces (core)
using namespace std;

//shortcuts
using ilong = initializer_list<long>;

//namespaces
namespace tfcpp {

  /*!
  \brief Constructor
  */
  model::model(long Num_Inputs,ilong Hidden_Units,long Num_Classes){
    this->Num_Inputs   = Num_Inputs;
    this->Hidden_Units = Hidden_Units;
    this->Num_Classes  = Num_Classes;

    //create weights & biases
    for (long I=0; I<this->Hidden_Units.size(); I++){      
      long Num_Units = this->Hidden_Units[I];        

      if (I==0){ //first hidden layer, connects to input
        this->Weights.push_back(Variable(R, {Num_Inputs,Num_Units}, DT_FLOAT));
      }
      else {
        long Prev_Num_Units = this->Hidden_Units[I-1];
        this->Weights.push_back(Variable(R, {Prev_Num_Units,Num_Units}, DT_FLOAT));
      }

      this->Biases.push_back(Variable(R, {Num_Units}, DT_FLOAT));
    }//hidden units loop

    //init weights and biases
    for (long I=0; I<this->Hidden_Units.size(); I++){
      long    Num_Units = this->Hidden_Units[I];
      Assign* Weight_Init;
      Assign* Bias_Init;

      if (I==0){
        Weight_Init = new Assign(R, this->Weights[I], 
                          RandomNormal(R, {(int)Num_Inputs,(int)Num_Units}, DT_FLOAT));
        Bias_Init   = new Assign(R, this->Biases[I],  
                          RandomNormal(R,{(int)Num_Units}, DT_FLOAT)); 
      }
      else {
        long Prev_Num_Units = this->Hidden_Units[I-1];
        Weight_Init         = new Assign(R, this->Weights[I], 
                                  RandomNormal(R, {(int)Prev_Num_Units,(int)Num_Units}, DT_FLOAT));
        Bias_Init           = new Assign(R, this->Biases[I],  
                                  RandomNormal(R, {(int)Num_Units}, DT_FLOAT)); 
        
      }//if index

      TF_CHECK_OK(
        Sess.Run({*Weight_Init,*Bias_Init},nullptr)        
      );
      delete Weight_Init;
      delete Bias_Init;
    }//init loop
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