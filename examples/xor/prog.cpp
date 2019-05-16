/*!
\file
\brief Test XOR using TFCpp library,
       NamedType: 
       https://www.fluentcpp.com/2018/12/14/named-arguments-cpp
       https://github.com/joboccara/NamedType
*/

//c++ standard
#include <iostream>

//custom libs
#include <namedtype/named_type.hpp>

#include <tfcpp/t.hpp>
#include <tfcpp/model.hpp>
#include <tfcpp/miscs/utils.hpp>

//namespaces
using namespace std;
using namespace fluent;
using namespace tfcpp;

using text = NamedType<string,struct text_tag>;
static const text::argument Text;

/*void print(text const& Text){
  cout <<Text <<endl;
}*/

using FirstName = NamedType<std::string, struct FirstNameTag>;
using LastName = NamedType<std::string, struct LastNameTag>;

static const FirstName::argument firstName;
static const LastName::argument lastName;

void displayName(FirstName const& theFirstName, LastName const& theLastName){
  cout <<theFirstName.get() <<endl;
}


//PROGRAMME ENTRY POINT=========================================================
/*!
\brief Main function
*/
int main(int Argc,char* Args[]){
displayName(firstName = "John", lastName = "Doe");
  //print(Text = "Test named type!");
}

//eof