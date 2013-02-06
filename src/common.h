#pragma once



#ifdef _DEBUG

#include <iostream>
#define E(x) { std::cerr << #x << " = " << (x) << "   "; }
#define Eo(x) { std::cerr << #x << " = " << (x) << std::endl; }

#else

#define E(x)
#define Eo(x)

#endif /* _DEBUG */
#define EO(x) Eo(x)



#ifdef __unix

#include <unistd.h> // chdir

#else


#endif /* __unix */

typedef unsigned char uchar;
typedef unsigned int uint;
typedef float real;
