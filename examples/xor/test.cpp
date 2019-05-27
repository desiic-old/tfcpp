#include <iostream>
using namespace std;

class c {
  public:
    long V;

  public:
    void operator()(long Sv); //set
    long operator()();        //get
};

void c::operator()(long Sv){
  this->V = Sv;
}

long c::operator()(){
  return this->V;
}

c Var;

c & get_var(){
  return Var;
}

int main(){
  get_var()(999);
  cout <<get_var()() <<endl;
}

//eof
