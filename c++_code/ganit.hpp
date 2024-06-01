// ganit/basic_operations.hpp
#ifndef GANIT_HPP
#define GANIT_HPP

#include <vector>
#include <stdexcept>

namespace ganit {

int add(int a, int b);
double add(double a, double b);

int vec_add(const std::vector<int>& vec);
double vec_add(const std::vector<double>& vec);

int sub(int a, int b);
double sub(double a, double b);

int vec_sub(const std::vector<int>& vec);
double vec_sub(const std::vector<double>& vec);

int cross(int a, int b);
double cross(double a, double b);

int vec_cross(const std::vector<int>& vec);
double vec_cross(const std::vector<double>& vec);

int div(int a, int b);
double div(double a, double b);

int modulus(int a, int b);
double modulus(double a, double b);

double fabs(double a);
//constants
constexpr double PI = 3.141592653589793;
constexpr double E = 2.718281828459045;

//log and power

double exp(double x);
double log(double x);
double log10(double x);
double logx(double x, double y);
double pow(double x, double y);
double root2(double x);
double root3(double x);
double rootx(double x, int y);

//trignometry

double sin(double x);
double cos(double x);
double tan(double x);

double asin(double x);
double acos(double x);
double atan(double x);

double sinh(double x);
double cosh(double x);
double tanh(double x);

double asinh(double x);
double acosh(double x);
double atanh(double x);

//angles and radians

double to_degrees(double x);
double to_radians(double x);

} // namespace ganit

#endif // GANIT_BASIC_OPERATIONS_HPP
