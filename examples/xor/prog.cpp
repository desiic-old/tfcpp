/*!
\file
\brief Test XOR using TFCpp library
*/

//core headers
#include <iostream>
#include <vector>

//custom headers (generic)
#include <types.hpp>

//custom headers (ML)
#include <tfcpp/t.hpp>           //functions
#include <tfcpp/model.hpp>       //ML model class
#include <tfcpp/miscs/utils.hpp> //utility class

//use core namespaces
using namespace std;

//use custom namespaces
using namespace tfcpp;

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
  print(Text=string("Learn XOR using TFCpp lib")); 

  //init
  init_ml();

  //build dnn model
  type<long>         Num_Inputs;
  type<vector<long>> Hidden_Units;
  type<long>         Num_Classes;

  vector<long> Hidden_Units_Values = {4}; //1 layer of 4 neurons

  model* Model = build_dnn_classifier(
    Num_Inputs   = 2,
    Hidden_Units = Hidden_Units_Values,
    Num_Classes  = 2
  );

  delete Model;
}

//eof