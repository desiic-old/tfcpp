/*!
\file
\brief Test NamedType lib and template for named params,
       NamedType: 
       https://www.fluentcpp.com/2018/12/14/named-arguments-cpp
       https://github.com/joboccara/NamedType
*/

//c++ standard
#include <iostream>

//libs
#include <namedtype/named_type.hpp>

//custom libs (generic)
#include <types.hpp>

//custom libs (ML)
#include <tfcpp/t.hpp>           //functions
#include <tfcpp/model.hpp>       //ML model
#include <tfcpp/miscs/utils.hpp> //utilities

//namespaces
using namespace std;
using namespace fluent;
using namespace tfcpp;

//named types
using text = NamedType<string,struct text_tag>;
static const text::argument Text;

/*!
\brief Print a string (with NamedType lib)
*/
void print(text Text){
  cout <<Text.get() <<endl;
}

/*!
\brief Print a string (using template Type<>)
*/
void print(string Text){
  cout <<Text <<endl;
}

//PROGRAMME ENTRY POINT=========================================================
/*!
\brief Main function
*/
int main(int Argc,char* Args[]){
  //test NamedType lib
  print(Text="NamedType Lib, OK!");

  //test Type template
  type<string> Text;
  print(Text=string("Type Template, OK!")); 
}

//eof