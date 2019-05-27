/*!
\file
\brief Test XOR using TFCpp library,
       Requires C++17
*/

//core headers
#include <iostream>
#include <vector>
#include <initializer_list>

//custom headers (generic)
#include <types.hpp>

//custom headers (ML)
#include <tfcpp/t.hpp>                  //functions
#include <tfcpp/ann/dnn-classifier.hpp> //ML model class
#include <tfcpp/miscs/utils.hpp>        //utility class

//use core namespaces
using namespace std;

//use custom namespaces
using namespace tfcpp;

//shortcuts
using ilong = initializer_list<long>;

/*!
\brief Print a string
*/
void print(string Text){
  cout <<Text <<endl;
}

//PROGRAMME ENTRY POINT=========================================================
/*!
\brief Main function
*/
int main(int Argc,char* Args[]){
  type<string> Text;
  print(Text=string("\nLearn XOR using TFCpp lib")); 

  //init
  init_ml();

  //build dnn model
  type<long>  Num_Inputs;
  type<ilong> Hidden_Units;
  type<long>  Num_Classes;

  //1 layer of 4 neurons, 2 classes make 2 output neurons
  //minimum hiddens: [4], change to [40] for better results.
  ilong Hidden_Units_Values = {40,20}; 

  dnn_classifier* Model = build_dnn_classifier(
    Num_Inputs   = 2,
    Hidden_Units = Hidden_Units_Values,
    Num_Classes  = 2 //2 identity output neurons, not counted in shape.
  );

  //set training data (xor)
  vector<vector<long>> Inps;
  vector<long>         Expecteds; //labels

  Inps.push_back(vector<long>({0,0}));
  Inps.push_back(vector<long>({0,1}));
  Inps.push_back(vector<long>({1,0}));
  Inps.push_back(vector<long>({1,1}));

  Expecteds = {0,1,1,0};
  Model->set_training_data(Inps,Expecteds);

  //train and eval
  cout <<"\nTraining..." <<endl;
  long Steps = 5000;      

  for (long I=0; I<Steps; I++){
    Model->set_batch(Model->get_rand_batch(4));    
    Model->train();

    //log after every 100 steps
    if ((I+1)%100 == 0) {
      float Loss = Model->get_current_loss();
      cout <<"Loss after\x20" <<I+1 <<"\x20steps:\x20" <<Loss <<endl;
    }//log
  }//steps

  //start inference
  cout <<"\nInferring the original training data..." <<endl;  

  for (long I=0; I<Inps.size(); I++){    
    vector<long>  Sample = Inps[I];
    vector<float> Probs  = Model->infer(Sample); //probabilities
    long          Class  = argmax<float>(Probs);

    /*
    Output probabilities:
            Class0 Class1
    0 ^ 0 = 1,     0
    0 ^ 1 = 0,     1
    1 ^ 0 = 0,     1
    1 ^ 1 = 1,     0
    */
    long X1 = Sample[0];
    long X2 = Sample[1];
    cout <<fixed <<X1 <<" ^ " <<X2 <<" = " <<Class <<" (" <<Probs[1] <<")" <<endl;
  }

  //free memory
  delete Model;
}

//eof