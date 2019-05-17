/*!
\file
\brief Test XOR using TFCpp library
*/

//c++ standard
#include <iostream>

//custom libs (generic)
#include <types.hpp>

//custom libs (ML)
#include <tfcpp/t.hpp>           //functions
#include <tfcpp/model.hpp>       //ML model class
#include <tfcpp/miscs/utils.hpp> //utility class

//namespaces
using namespace std;
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
}

//eof