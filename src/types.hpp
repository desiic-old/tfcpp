/*!
\file
\brief All type definitions
*/

//include guard
#ifndef TYPES_HPP
#define TYPES_HPP

//primitives
/*
//Systems:                             16bit  32bit  64bit
typedef unsigned char      byte_;    //1byte  1byte  1byte
typedef unsigned short     word;     //2bytes 2bytes 2bytes
typedef unsigned int       dword;    //2bytes 4bytes 4bytes
typedef unsigned long      qword;    //--     4bytes 8bytes
typedef unsigned long long oword;    //--     --     8bytes

typedef char               char_;    //the same like unsigned above.
typedef short              short_;   //the same.
typedef int                int_;     //the same.
typedef long               long_;    //the same.
typedef long long          llong;    //the same.

typedef float              float_;   //4bytes 4bytes 4bytes
typedef double             double_;  //--     8bytes 8bytes
typedef long double        ldouble;  //--     --     8bytes
*/

//typedef makes different types, 
//use #define for type compatibility,
//byte is already in std::byte (c++17) but it's not number,
//use another word 'bite' for byte instead.
//long double: https://stackoverflow.com/a/15176438/5581893
//Systems:                            16bit  32bit  64bit
#define byte_    unsigned char      //1byte  1byte  1byte
#define word     unsigned short     //2bytes 2bytes 2bytes
#define dword    unsigned int       //2bytes 4bytes 4bytes
#define qword    unsigned long      //--     4bytes 8bytes
#define oword    unsigned long long //--     --     8bytes

#define char_    char               //the same like unsigned above.
#define short_   short              //the same.
#define int_     int                //the same.
#define long_    long               //the same.
#define llong    long long          //the same.

#define float_   float              //4bytes 4bytes 4bytes
#define double_  double             //--     8bytes 8bytes
#define ldouble  long double        //--     --     8bytes

/*!
\brief Template for named parameters to functions/methods
*/
template <typename Type>
class type {
  public:
    Type operator=(Type Param){
      return Param;
    };
};

//include guard
#endif

//eof