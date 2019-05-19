/*!
\file
\brief Test XOR using TFCpp library
*/

//core headers
#include <iostream>

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
}

//eof