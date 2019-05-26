#include <iostream>
using namespace std;

//headers
template <typename T>
class c {
  public:
    static void print(T value);
};

template <typename T>
void print(T value);

//definitions
template <typename T>
void c<T>::print(T value){
  cout <<value <<endl;
}

template <typename T>
void print(T value){
  cout <<value <<endl;
}

//entry point
int main(){
  c<const char*>::print("foo");
  print<const char*>("bar");
}

//eof