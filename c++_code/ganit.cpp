// basic_operations.cpp
#include "ganit.hpp"
#include <vector>
#include <stdexcept>

namespace ganit {

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int vec_add(const std::vector<int>& vec) {
    int sum = 0;
    for (int num : vec) {
        sum += num;
    }
    return sum;
}

double vec_add(const std::vector<double>& vec) {
    double sum = 0;
    for (double num : vec) {
        sum += num;
    }
    return sum;
}

int sub(int a, int b) {
    return a - b;
}

double sub(double a, double b) {
    return a - b;
}

int vec_sub(const std::vector<int>& vec) {
    int diff = 0;
    for (int num : vec) {
        diff -= num;
    }
    return diff;
}

double vec_sub(const std::vector<double>& vec) {
    double diff = 0;
    for (double num : vec) {
        diff -= num;
    }
    return diff;
}

int cross(int a, int b) {
    return a * b;
}

double cross(double a, double b) {
    return a * b;
}

int vec_cross(const std::vector<int>& vec) {
    int dot = 1; // Initialize to 1 for multiplication
    for (int num : vec) {
        dot *= num;
    }
    return dot;
}

double vec_cross(const std::vector<double>& vec) {
    double dot = 1; // Initialize to 1 for multiplication
    for (double num : vec) {
        dot *= num;
    }
    return dot;
}

int div(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

double div(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

int modulus(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Modulus by zero");
    }
    return a % b;
}

double modulus(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Modulus by zero");
    }
    double quotient = a / b;
    return a - static_cast<int>(quotient) * b;
}

double fabs(double x) {
    return (x < 0) ? -x : x;
}

// log and power

double exp(double x) {
    const int MAX_ITER = 10;
    double term = 1;
    double sum = 1;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= x / i;
        sum += term;
    }
    return sum;
}

double log(double x) {
    if (x <= 0) {
        // Handle error: log of non-positive number is undefined
        return -1; // Return a sentinel value indicating error
    }
    const int MAX_ITER = 50;
    double sum = 0;
    double term = (x - 1) / x;
    for (int i = 1; i < MAX_ITER; ++i) {
        sum += term / i;
        term *= (x - 1) / x;
    }
    return sum;
}

double log10(double x) {
    return log(x) / log(10);
}

double logx(double base, double value) {
    return log(value) / log(base);
}

double pow(double base, double exponent) {
    double result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

double root2(double x) {
    if (x < 0) {
        // Handle error: square root of negative number is undefined
        return -1; // Return a sentinel value indicating error
    }
    const double EPSILON = 1e-15;
    double guess = x / 2;
    while (fabs(guess * guess - x) > EPSILON) {
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

double root3(double x) {
    double guess = 1.0;
    const double EPSILON = 1e-15;
    while (fabs(guess * guess * guess - x) > EPSILON) {
        guess = (2 * guess + x / (guess * guess)) / 3;
    }
    return guess;
}

double rootx(double value, int root) {
    if (value < 0 && root % 2 == 0) {
        // Handle error: even root of negative number is undefined
        return -1; // Return a sentinel value indicating error
    }
    if (value == 0) {
        return 0; // Return 0 for the 0th root
    }
    double guess = value / root;
    const double EPSILON = 1e-15;
    while (fabs(pow(guess, root) - value) > EPSILON) {
        guess = ((root - 1) * guess + value / pow(guess, root - 1)) / root;
    }
    return guess;
}

// trignometry 

double sin(double x) {
    const int MAX_ITER = 5;
    double term = x;
    double sum = x;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= -x * x / (2 * i * (2 * i + 1));
        sum += term;
    }
    return sum;
}

double cos(double x) {
    const int MAX_ITER = 5;
    double term = 1;
    double sum = 1;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= -x * x / (2 * i * (2 * i - 1));
        sum += term;
    }
    return sum;
}

double tan(double x) {
    return sin(x) / cos(x);
}

double asin(double x) {
    const int MAX_ITER = 5;
    double term = x;
    double sum = x;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= (x * x * (2 * i - 1) * (2 * i - 1)) / (2 * i * (2 * i + 1));
        sum += term / (2 * i + 1);
    }
    return sum;
}

double acos(double x) {
    return PI / 2 - asin(x);
}

double atan(double x) {
    const int MAX_ITER = 5;
    double term = x;
    double sum = x;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= -x * x;
        sum += term / (2 * i + 1);
    }
    return sum;
}

double sinh(double x) {
    const int MAX_ITER = 5;
    double term = x;
    double sum = x;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= x * x / (2 * i * (2 * i + 1));
        sum += term;
    }
    return sum;
}

double cosh(double x) {
    const int MAX_ITER = 5;
    double term = 1;
    double sum = 1;
    for (int i = 1; i < MAX_ITER; ++i) {
        term *= x * x / (2 * i * (2 * i - 1));
        sum += term;
    }
    return sum;
}

double tanh(double x) {
    return sinh(x) / cosh(x);
}

double asinh(double x) {
    return log(x + root2(x * x + 1));
}

double acosh(double x) {
    return log(x + root2(x * x - 1));
}

double atanh(double x) {
    return 0.5 * log((1 + x) / (1 - x));
}

//angles and radian

double to_degrees(double radians) {
    return radians * (180.0 / PI);
}

double to_radians(double degrees) {
    return degrees * (PI / 180.0);
}

} // namespace ganit
