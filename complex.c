/*
complex.c, ver. 2.1a                              // PROGRAM
last modified: 10 Feb 2014                        // PROGRAM
   Class definition of "Complex" for use          // PROGRAM
   in almost complex-valued operations,           // PROGRAM
   except for the three-term operation "()?:".    // PROGRAM
   24 Aug 2012: almost functions are made inline. // PROGRAM
*/

/*
  Complex  a(sr, si); define a complex number with a = (sr, si)
  Complex  a(sr);     define a complex number with a = (sr, 0.0)
  cmplx(sr,si);       return a complex number (sr, si)
  cmplx(sr);          return a complex number (sr, 0.0)
  ~a;                 return the complex conjugate of "a"
  re(a);              return the real part of "a"
  im(a);              return the imaginary part of "a"
  sqmag(a);           return the squared magnitude of "a"

  A complex-valued function should return its value by reference.
*/

#include <iostream>

#define COMPLEX
#define DEBUG_COMPLEX 0

class Complex {
public:
   friend Complex & operator+(Complex, Complex);
   friend Complex & operator+(double, Complex);
   friend Complex & operator+(Complex, double);
   friend Complex & operator-(Complex, Complex);
   friend Complex & operator-(double, Complex);
   friend Complex & operator-(Complex, double);
   friend Complex & operator*(Complex, Complex);
   friend Complex & operator*(double, Complex);
   friend Complex & operator*(Complex, double);
   friend Complex & operator/(Complex, Complex);
   friend Complex & operator/(double, Complex);
   friend Complex & operator/(Complex, double);
   friend Complex & cmplx(double, double);
   friend double re(Complex);
   friend double im(Complex);
   friend double sqmag(Complex);
   Complex & operator=(Complex);
   Complex & operator=(double);
   Complex & operator+=(Complex);
   Complex & operator+=(double);
   Complex & operator-=(Complex);
   Complex & operator-=(double);
   Complex & operator*=(Complex);
   Complex & operator*=(double);
   Complex & operator/=(Complex);
   Complex & operator/=(double);
   Complex & operator-();    // negation
   Complex & operator+();
   Complex & operator~();
   Complex(Complex &);       // copy constructor
   Complex(double, double);
   Complex();                // default: do nothing
   void print(std::ostream &);
private:
   double r;
   double i;
};

inline Complex & operator+(Complex source1, Complex source2) {
   static Complex temp;
   temp.r = source1.r+source2.r;
   temp.i = source1.i+source2.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator+(Complex, Complex)\n";
#endif
   return(temp);
}

Complex & operator+(double src1, Complex source2) {
   static Complex temp;
   temp.r = src1+source2.r;
   temp.i = source2.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator+(double, Complex)\n";
#endif
   return(temp);
}

Complex & operator+(Complex source1, double src2) {
   static Complex temp;
   temp.r = source1.r+src2;
   temp.i = source1.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator+(Complex, double)\n";
#endif
   return(temp);
}

inline Complex & operator-(Complex source1, Complex source2) {
   static Complex temp;
   temp.r = source1.r-source2.r;
   temp.i = source1.i-source2.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator-(Complex, Complex)\n";
#endif
   return(temp);
}

Complex & operator-(double src1, Complex source2) {
   static Complex temp;
   temp.r = src1-source2.r;
   temp.i = -source2.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator-(double, Complex)\n";
#endif
   return(temp);
}

Complex & operator-(Complex source1, double src2) {
   static Complex temp;
   temp.r = source1.r-src2;
   temp.i = source1.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator-(Complex, double)\n";
#endif
   return(temp);
}

inline Complex & operator*(Complex source1, Complex source2) {
   static Complex temp;
   temp.r = source1.r*source2.r-source1.i*source2.i;
   temp.i = source1.r*source2.i+source1.i*source2.r;
#if DEBUG_COMPLEX == 4
   std::cout << "operator*(Complex, Complex)\n";
#endif
   return(temp);
}

Complex & operator*(double src1, Complex source2) {
   static Complex temp;
   temp.r = src1*source2.r;
   temp.i = src1*source2.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator*(double, Complex)\n";
#endif
   return(temp);
}

Complex & operator*(Complex source1, double src2) {
   static Complex temp;
   temp.r = source1.r*src2;
   temp.i = source1.i*src2;
#if DEBUG_COMPLEX == 4
   std::cout << "operator*(Complex, double)\n";
#endif
   return(temp);
}

inline Complex & operator/(Complex source1, Complex source2) {
   static Complex temp;
   double vd, sr=source2.r, si=source2.i;
   vd = sr*sr+si*si;
   temp.r = (source1.r*sr+source1.i*si)/vd;
   temp.i = (-source1.r*si+source1.i*sr)/vd;
#if DEBUG_COMPLEX == 4
   std::cout << "operator/(Complex, Complex)\n";
#endif
   return(temp);
}

Complex & operator/(double src1, Complex source2) {
   static Complex temp;
   double vd, sr=source2.r, si=source2.i;
   vd = sr*sr+si*si;
   temp.r = src1*sr/vd;
   temp.i = -src1*si/vd;
#if DEBUG_COMPLEX == 4
   std::cout << "operator/(double, Complex)\n";
#endif
   return(temp);
}

Complex & operator/(Complex source1, double src2) {
   static Complex temp;
   temp.r = source1.r/src2;
   temp.i = source1.i/src2;
#if DEBUG_COMPLEX == 4
   std::cout << "operator/(Complex, double)\n";
#endif
   return(temp);
}

inline Complex & cmplx(double src1, double src2=0.0) {
   static Complex temp;
   temp.r = src1;
   temp.i = src2;
#if DEBUG_COMPLEX == 4
   std::cout << "cmplx(double,double)\n";
#endif
   return(temp);
}

double re(Complex source){
#if DEBUG_COMPLEX == 4
   std::cout << "re(Complex)\n";
#endif
   return(source.r);
}

double im(Complex source) {
#if DEBUG_COMPLEX == 4
   std::cout << "im(Complex)\n";
#endif
   return(source.i);
}

double sqmag(Complex source) {
#if DEBUG_COMPLEX == 4
   std::cout << "sqmag(Complex)\n";
#endif
   return (source.r*source.r+source.i*source.i);
}

inline Complex & Complex::operator=(Complex source) {
   this->r = source.r;
   this->i = source.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator=(Complex)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator=(double src) {
   this->r = src;
   this->i = 0.0;
#if DEBUG_COMPLEX == 4
   std::cout << "operator=(double)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator+=(Complex source) {
   this->r += source.r;
   this->i += source.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator+=(Complex)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator+=(double src) {
   this->r += src;
#if DEBUG_COMPLEX == 4
   std::cout << "operator+=(double)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator-=(Complex source) {
   this->r -= source.r;
   this->i -= source.i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator-=(Complex)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator-=(double src) {
   this->r -= src;
#if DEBUG_COMPLEX == 4
   std::cout << "operator-=(double)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator*=(Complex source) {
   double rl, im;
   rl = this->r*source.r-this->i*source.i;
   im = this->r*source.i+this->i*source.r;
   this->r = rl;
   this->i = im;
#if DEBUG_COMPLEX == 4
   std::cout << "operator*=(Complex)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator*=(double src) {
   this->r *= src;
   this->i *= src;
#if DEBUG_COMPLEX == 4
   std::cout << "operator*=(double)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator/=(Complex source) {
   double rl, im, vd, sr=source.r, si=source.i;
   vd = sr*sr+si*si;
   rl = this->r*sr+this->i*si;
   im = -this->r*si+this->i*sr;
   this->r = rl/vd;
   this->i = im/vd;
#if DEBUG_COMPLEX == 4
   std::cout << "operator/=(Complex)\n";
#endif
   return (*this);
}

inline Complex & Complex::operator/=(double src) {
   this->r /= src;
   this->i /= src;
#if DEBUG_COMPLEX == 4
   std::cout << "operator/=(double)\n";
#endif
   return (*this);
}

void Complex::print(std::ostream &os) {
  os << "(" << this->r << ", " << this->i << ")";
}

std::ostream &operator<<(std::ostream &os, Complex &r) {
   r.print(os);
   return (os);
}

inline Complex & Complex::operator+() {
   static Complex temp;
   temp.r = this->r;
   temp.i = this->i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator+()\n";
#endif
   return (temp);
}

inline Complex & Complex::operator-() {
   static Complex temp;
   temp.r = -this->r;
   temp.i = -this->i;
#if DEBUG_COMPLEX == 4
   std::cout << "operator-()\n";
#endif
   return (temp);
}

inline Complex & Complex::operator~() {
   static Complex temp;
   temp.r = this->r;
   temp.i = -(this->i);
#if DEBUG_COMPLEX == 4
   std::cout << "~()\n";
#endif
   return(temp);
}

inline Complex::Complex(Complex &source) {
   r = source.r;
   i = source.i;
#if DEBUG_COMPLEX == 4
   std::cout << "Complex(Complex &)\n";
#endif
}

Complex::Complex(double src1, double src2=0.0) {
   r = src1;
   i = src2;
#if DEBUG_COMPLEX == 4
   std::cout << "Complex(double, double)\n";
#endif
}

Complex::Complex() {
#if DEBUG_COMPLEX == 4
   std::cout << "Complex()\n";
#endif
}
