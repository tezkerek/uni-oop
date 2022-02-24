#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

class ComplexNumber {
  private:
    double re;
    double im;

  public:
    ComplexNumber(double real, double imaginary) : re(real), im(imaginary) {}
    ComplexNumber(const ComplexNumber &num) : re(num.re), im(num.im) {}

    double getReal() const { return re; }

    double getImaginary() const { return im; }

    void setReal(double real) { this->re = real; }

    void setImaginary(double imaginary) { this->im = imaginary; }

    double abs() const { return std::sqrt(re * re + im * im); }

    ComplexNumber conjugate() const { return ComplexNumber(re, -im); }

    std::string toString() const {
        std::stringstream ss;
        if (re != 0) {
            ss << re;
        }

        if (im > 0 && re != 0) {
            ss << "+i";
            if (im != 1) {
                ss << "*" << std::abs(im);
            }
        } else if (im < 0) {
            ss << "-i";
            if (im != -1) {
                ss << "*" << std::abs(im);
            }
        }

        return ss.str();
    }

    ComplexNumber operator+(ComplexNumber const &rhs) const {
        return ComplexNumber(re + rhs.re, im + rhs.im);
    }

    ComplexNumber operator*(ComplexNumber const &rhs) const {
        auto s1 = re * rhs.re;
        auto s2 = im * rhs.im;
        auto s3 = (re + im) * (rhs.re + rhs.im);

        return ComplexNumber(s1 - s2, s3 - s1 - s2);
    }

    ComplexNumber operator/(ComplexNumber const &rhs) const {
        auto numerator = *this * rhs.conjugate();
        auto denominator = rhs.getReal() * rhs.getReal() +
                           rhs.getImaginary() * rhs.getImaginary();

        return ComplexNumber(numerator.re / denominator,
                             numerator.im / denominator);
    }

    friend std::ostream &operator<<(std::ostream &out,
                                    ComplexNumber const &num) {
        out << num.toString();
        return out;
    }
};

int main() {
    ComplexNumber num1(-4, -1);
    ComplexNumber num2(num1);
    num2.setReal(0);
    num2.setImaginary(2);

    std::cout << num1 / num2 << '\n';
    std::cout << ComplexNumber(0, -1) << '\n';
}
