/*!
\file
\brief All type definitions
*/

//include guard
#ifndef TYPES_HPP
#define TYPES_HPP

//primitives,
//avoid 'int' as it has variable lengths
/*
typedef unsigned char      byte;
typedef unsigned short     word;
typedef unsigned long      dword;
typedef unsigned long long qword;

typedef char               char__;
typedef short              short__;
typedef long               long__;
typedef long long          llong;

typedef float              float__;
typedef double             double__;
typedef long double        ldouble;
*/

//typedef makes different types, 
//use #define for type compatibility,
//avoid using long double on x86-64 as PC can't process 128-bit values directly.
//byte is already in std::byte (c++17) but it's not number,
//use another word 'bite' for byte instead.
#define bite     unsigned char      //8 bits
#define word     unsigned short     //16 bits
#define dword    unsigned long      //32 bits
#define qword    unsigned long long //64 bits

#define char__   char               //8   bits
#define short__  short              //16  bits
#define long__   long               //32  bits
#define llong    long long          //64  bits

#define float__  float              //32  bits
#define double__ double             //64  bits
#define ldouble  long double        //128 bits

/*!
\brief Template for named parameters to functions/methods
*/
template <class Type>
class type {
  public:
    Type operator= (Type Param){
      return Param;
    }
};

//include guard
#endif

//eof