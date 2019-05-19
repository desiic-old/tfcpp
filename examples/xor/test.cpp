#include <iostream>
#include <vector>

using namespace std;

class c{
  public:
    c(initializer_list<long> a);
};

c::c(initializer_list<long> a){
  vector<long> v = a;
  cout <<typeid(v).name() <<endl;
  cout <<v.size() <<endl;
}

int main(){
  c foobar2 = c({1,2,3});
}

//