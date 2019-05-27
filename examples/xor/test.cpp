#include <iostream>
#include <tuple>
using namespace std;

template <typename... types>
void print(types... Params){
  long        Size   = sizeof...(Params);
  long        Param1 = get<0>(tie(Params...));
  const char* Param2 = get<1>(tie(Params...));
  
  cout <<Size <<endl;
  cout <<Param1 <<" " <<Param2 <<endl;
}

int main(){
  print(123, "foobar");
}

//eof