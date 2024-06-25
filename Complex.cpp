#include "Complex.hpp"
#include <stdexcept>  // For std::runtime_error

Complex::Complex(double real, double imag) : re(real), im(imag) {}

// Getter and setter methods
double Complex::getReal() const {
    return re;
}

void Complex::setReal(double real) {
    re = real;
}

double Complex::getImag() const {
    return im;
}

void Complex::setImag(double imag) {
    im = imag;
}




// Implementations of member functions

Complex Complex::operator+(const Complex& other) const {
    return Complex(re + other.re, im + other.im);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re - other.re, im - other.im);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(re * other.re - im * other.im, re * other.im + im * other.re);
}

Complex Complex::operator/(const Complex& other) const {
    double denom = std::pow(other.re, 2) + std::pow(other.im, 2);
    if (denom == 0) {
        throw std::runtime_error("Division by zero for complex numbers");
    }
    return Complex((re * other.re + im * other.im) / denom, (im * other.re - re * other.im) / denom);
}

bool Complex::operator==(const Complex& other) const {
    return norm() == other.norm();
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

bool Complex::operator<(const Complex& other) const {
    return norm() < other.norm();
}

bool Complex::operator>(const Complex& other) const {
    return norm() > other.norm();
}

bool Complex::operator<=(const Complex& other) const {
    return norm() <= other.norm();
}

bool Complex::operator>=(const Complex& other) const {
    return norm() >= other.norm();
}

std::string Complex::to_string() const {
    std::stringstream ss;
    ss << re << (im >= 0 ? "+" : "") << im << "i";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.to_string();
    return os;
}

// Implementation of norm helper function
double Complex::norm() const {
    return std::sqrt(std::pow(re, 2) + std::pow(im, 2));
}
