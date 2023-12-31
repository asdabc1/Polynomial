#include "polynomial.h"

int factorial(const int a) {
	int result = 1;
	for (int i = 1; i <= a; i++)
		result = result * i;
	return a != 0 ? result : 1;
}

Polynomial::Polynomial(const int deg, const double coeffic[]) {
	locked = false;
	degree = deg;
	coefficients = new double[degree + 1];

	for (int i = 0; i <= degree; i++)
		coefficients[i] = coeffic[i];
}

Polynomial::Polynomial(const int deg, const std::vector<double>& coeffic) {
	locked = false;
	degree = deg;
	coefficients = new double[degree + 1];

	if (coeffic.size() > degree)
		for (int i = 0; i <= degree; i++)
			coefficients[i] = coeffic[i];
	else {
		int i = 0;
		for (double x : coeffic) {
			coefficients[i] = x;
			i++;
		}
		for (i; i <= degree; i++)
			coefficients[i] = 0;
	}
}

Polynomial::Polynomial(const std::vector<double>& coeffic) {
	locked = false;
	degree = coeffic.size() - 1;
	coefficients = new double[degree + 1];

	int i = 0;
	for (double x : coeffic) {
		coefficients[i] = coeffic[i];
		++i;
	}
}

Polynomial::Polynomial(const std::initializer_list<double> li) {
	locked = false;
	degree = li.size() - 1;
	coefficients = new double[degree + 1];

	int i = 0;
	for (double x : li) {
		coefficients[i] = x;
		++i;
	}
}

Polynomial::Polynomial(const int deg, const bool manual_input) {
	locked = false;
	degree = deg;
	coefficients = new double[degree + 1];

	if (manual_input) {
		std::cout << "Podaj czynnik a[0]: ";
		std::cin >> coefficients[0];
		for (int i = 1; i <= degree; i++) {
			std::cout << "\nPodaj czynnik a[" << i << "]: ";
			std::cin >> coefficients[i];
		}
	}
}

Polynomial::Polynomial(const Polynomial& p) {
	locked = p.locked;
	limits[0] = p.limits[0];
	limits[1] = p.limits[1];
	degree = p.degree;
	delete[] coefficients;
	coefficients = new double[degree + 1];

	for (int i = 0; i <= degree; i++)
		coefficients[i] = p.coefficients[i];
}

Polynomial::Polynomial(Polynomial&& p) {
	locked = p.locked;
	limits[0] = p.limits[0];
	limits[1] = p.limits[1];
	degree = p.degree;
	coefficients = p.coefficients;
	p.coefficients = nullptr;
	p.degree = -1;
	p.locked = true;
	p.limits[0] = 0;
	p.limits[1] = 0;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
	locked = p.locked;
	limits[0] = p.limits[0];
	limits[1] = p.limits[1];
	degree = p.degree;
	delete[] coefficients;
	coefficients = new double[degree + 1];

	for (int i = 0; i <= degree; i++)
		coefficients[i] = p.coefficients[i];

	return *this;
}

Polynomial& Polynomial::operator=(Polynomial&& p) {
	locked = p.locked;
	limits[0] = p.limits[0];
	limits[1] = p.limits[1];
	degree = p.degree;
	coefficients = p.coefficients;
	p.coefficients = nullptr;
	p.degree = -1;
	p.locked = true;
	p.limits[0] = 0;
	p.limits[1] = 0;

	return *this;
}

double Polynomial::value(const double x) const {
	if (locked && (x > limits[1] || x < limits[0])) {
		std::cout << "ten wielomian nie pozwala na obliczenie wartosci poza zakresem!";
		return NULL;
	}

	double result = coefficients[0];

	for (int i = 1; i <= degree; i++)
		result = result * x + coefficients[i];

	return result;
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
	Polynomial result(this->degree + p.degree);

	for (int i = 0; i <= this->degree + p.degree; i++)
		result.coefficients[i] = 0;

	for (int i = 0; i <= this->degree; i++) {
		for (int j = 0; j <= p.degree; j++)
			result.coefficients[i + j] += this->coefficients[i] * p.coefficients[j];
	}
	return result;
}

Polynomial Polynomial::operator/(const double a) const {
	Polynomial result(*this);
	result.locked = false;

	for (int i = 0; i <= degree; i++)
		coefficients[i] /= a;

	return result;
}

Polynomial& Polynomial::operator*=(const Polynomial& p) {
	*this = *this * p;
	return *this;
}

Polynomial& Polynomial::operator/=(const double a) {
	*this = *this / a;
	return *this;
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
	if (this->degree > p.degree) {
		Polynomial result(*this);
		for (int i = 0; i <= p.degree; i++)
			result.coefficients[i] -= p.coefficients[i];
		return result;
	}
	else {
		Polynomial result(p);
		for (int i = 0; i <= result.degree; i++)
			result.coefficients[i] *= -1;
		return(result + *this);
	}
}

Polynomial& Polynomial::operator-=(const Polynomial& p) {
	*this = *this - p;

	return *this;
}

Polynomial Polynomial::operator-(const double a) const {
	Polynomial result(*this);

	result.coefficients[result.degree] -= a;

	return result;
}

Polynomial& Polynomial::operator-=(const double a) {
	coefficients[degree] -= a;

	return *this;
}

Polynomial Polynomial::operator*(const double a) const {
	Polynomial result(*this);

	for (int i = 0; i <= result.degree; i++)
		result.coefficients[i] *= a;

	return result;
}

Polynomial& Polynomial::operator*=(const double a) {
	for (int i = 0; i < -this->degree; i++)
		this->coefficients[i] *= a;

	return *this;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
	Polynomial result;

	if (this->degree > p.degree) {
		result = *this;

		for (int i = 0; i <= p.degree; i++)
			result.coefficients[result.degree - i] += p.coefficients[p.degree - i];
	}
	else if (this->degree < p.degree) {
		result = p;

		for (int i = 0; i <= this->degree; i++)
			result.coefficients[result.degree - i] += this->coefficients[this->degree - i];
	}
	else {
		result = p;

		for (int i = 0; i <= p.degree; i++)
			result.coefficients[i] += this->coefficients[i];
	}
	return result;
}

Polynomial Polynomial::operator+(const double a) const {
	Polynomial result(*this);

	result.coefficients[degree] += a;

	return result;
}

Polynomial& Polynomial::operator+=(const double a) {
	*this = *this + a;
	return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& p) {
	*this = *this + p;
	return *this;
}

std::vector<double> Polynomial::derivatives(const double x) const {
	if (locked)
		return std::vector<double>();

	std::vector<double> result;
	std::vector<double> temp(degree + 1);

	for (int i = 0; i <= degree + 1; i++) {
		temp[i] = coefficients[i];
	}

	for (int i = degree; i > 0; i--) {
		for (int j = 1; j <= i; j++) {
			temp[j] = temp[j] + temp[j - 1] * x;
			if (j == i)
				result.insert(result.begin(), temp[j]);
		}
	}
	result.insert(result.begin(), temp[0]);
	int te = 0;
	for (auto i = result.rbegin(); i != result.rend(); i++) {
		*i *= factorial(te);
		te++;
	}
	result.erase(result.end() - 1);
	std::reverse(result.begin(), result.end() - 1);
	return result;
}

void Polynomial::show() const{
	for (int i = 0; i <= degree; i++) {
		std::cout << coefficients[i] << "\t";
	}
	std::cout << std::endl;
}

void Polynomial::setLim(double a, double b) {
	locked = true;

	if (a > b) {
		limits[0] = b;
		limits[1] = a;
	}
	else {
		limits[0] = a;
		limits[1] = b;
	}
}

Polynomial operator+(const double a, const Polynomial& p) {
	Polynomial result(p);

	result.coefficients[result.degree] += a;
	return result;
}

Polynomial operator/(const double a, const Polynomial& p) {
	Polynomial result(p);

	for (int i = 0; i <= result.degree; i++)
		result.coefficients[i] /= a;
	
	return result;
}

Polynomial operator*(const double a, const Polynomial& p) {
	Polynomial result(p);

	for (int i = 0; i <= result.degree; i++)
		result.coefficients[i] *= a;

	return result;
}

Polynomial operator-(const double a, const Polynomial& p) {
	Polynomial result(p);

	for (int i = 0; i <= result.degree; i++)
		result.coefficients[i] *= -1;
	
	return (a + result);
}