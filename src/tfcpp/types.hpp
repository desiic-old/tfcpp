/*!
\file
\brief All type definitions
*/

//include guard
#ifndef TFCPP_TYPES_HPP
#define TFCPP_TYPES_HPP

//primitives,
//avoid 'int' as it has variable lengths
typedef unsigned char      byte;
typedef unsigned short     word;
typedef unsigned long      dword;
typedef unsigned long long qword;

typedef signed   char      char__;
typedef signed   short     short__;
typedef signed   long      long__;
typedef signed   long long llong;

typedef float              float__;
typedef double             double__;
typedef long double        ldouble;

//for named types
template <class T>
class Type {
  public:
    T operator= (T Param){
      return Param;
    }
};

//include guard
#endif

//eof