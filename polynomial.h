#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

int factorial(const int a);

class Polynomial {
private:
	double* coefficients;
	int degree;
	bool locked;
	double limits[2] = { 0,0 };
public:
	Polynomial() : degree(0) { coefficients = new double[1]; coefficients[0] = 0; locked = false; }
	Polynomial(const int deg, const double coeffic[]);
	Polynomial(const int deg, const std::vector<double>& coeffic);
	explicit Polynomial(const std::vector<double>& coeffic);
	Polynomial(const std::initializer_list<double> li);
	Polynomial(const int deg, const bool manual_input = false);

	Polynomial(const Polynomial& p);
	Polynomial(Polynomial&& p) noexcept;
	Polynomial& operator=(const Polynomial& p);
	Polynomial& operator=(Polynomial&& p) noexcept;
	~Polynomial() { delete[] coefficients; }

	Polynomial operator*(const Polynomial& p) const;
	Polynomial& operator*=(const Polynomial& p);
	Polynomial operator*(const double a) const;
	Polynomial& operator*=(const double a);
	Polynomial operator+(const Polynomial& p) const;
	Polynomial& operator+=(const Polynomial& p);
	Polynomial operator+(const double a) const;
	Polynomial& operator+=(const double a);
	Polynomial operator/(const double a) const;
	Polynomial& operator/=(const double a);
	Polynomial operator-(const Polynomial& p) const;
	Polynomial& operator-=(const Polynomial& p);
	Polynomial operator-(const double a) const;
	Polynomial& operator-=(const double a);

	friend Polynomial operator+(const double a, const Polynomial& p);
	friend Polynomial operator/(const double a, const Polynomial& p);
	friend Polynomial operator*(const double a, const Polynomial& p);
	friend Polynomial operator-(const double a, const Polynomial& p);

	double value(const double x) const;
	std::vector<double> derivatives(const double x) const;
	void show() const;
	void setLim(double a, double b);
	void unlock() { locked = false; }
};