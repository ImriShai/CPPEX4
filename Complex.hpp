#include <cmath>
#include <sstream>
#include <iostream>
#include <ostream>

class Complex { 
    private:
    double re;  // Real part
    double im;  // Imaginary part

    // Helper function to calculate norm magnitude (declaration only)
    double norm() const;
public:
    Complex(double real = 0, double imag = 0);

    // Getter and setter methods (optional)
    double getReal() const;
    void setReal(double real);

    double getImag() const;
    void setImag(double imag);

    // Arithmetic operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Comparison operators based on norm magnitude
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator<=(const Complex& other) const;
    bool operator>=(const Complex& other) const;

    // String conversion for output
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);


};

