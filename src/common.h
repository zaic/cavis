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

/*
 *	Convert functions
 */
#include <string>
#include <sstream>

template<typename T>
std::string toStdString(const T& val)
{
	std::ostringstream ss;
	ss << val;
	return ss.str();
}

template<typename T>
T fromStdString(const std::string& s)
{
	std::istringstream ss(s);
	T val;
	ss >> val;
	return val;
}

/*
 *	Stupid functions
 */

template<typename T>
inline T divup(const T& a, const T& b)
{
    return (a + b - 1) / b;
}

#include <QPushButton>
#include <QSize>
QPushButton* createButtonFromIcon(const char* icon_path, int icon_size, int button_size = -1);
