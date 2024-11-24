#include "polynomial.h"

namespace ZK {
	polynomial::polynomial()
		:_terms() { }
	polynomial::polynomial(const std::vector<real>& terms)
		:_terms(terms) { }
	polynomial::polynomial(const std::initializer_list<real>& terms)
		:_terms(terms) { }
	polynomial::polynomial(const polynomial& other)
		:_terms(other._terms) { }

	real polynomial::operator()(const real x) const {
		real result = 0;
		for (num i = 0; i < _terms.size(); ++i)
		{
			real term = 1;
			for (num j = 0; j < i; ++j)
				term *= x;
			term *= _terms[i];
			result += term;
		}
		return result;
	}
	polynomial polynomial::operator()(const polynomial& x) const {
		polynomial result;
		for (num i = 0; i < _terms.size(); ++i)
		{
			polynomial term = { 1 };
			for (num j = 0; j < i; ++j)
				term *= x;
			term *= _terms[i];
			result += term;
		}
		return result;
	}

	polynomial polynomial::operator+(const polynomial& other) const {
		polynomial result(*this);
		if (result.size() < other.size())
			result._terms.resize(other.size(), 0);
		for (num i = 0; i < other.size(); ++i)
			result[i] += other[i];
		return result;
	}
	polynomial polynomial::operator-(const polynomial& other) const {
		polynomial result(*this);
		if (result.size() < other.size())
			result._terms.resize(other.size(), 0);
		for (num i = 0; i < other.size(); ++i)
			result[i] -= other[i];
		return result;
	}
	polynomial polynomial::operator*(const polynomial& other) const {
		polynomial result;
		result._terms.resize(size() + other.size() - 1, 0);
		for (num i = 0; i < size(); ++i)
			for (num j = 0; j < other.size(); ++j)
				result[i + j] += _terms[i] * other[j];
		return result;
	}

	polynomial polynomial::operator+(const real x) const {
		polynomial result(*this);
		result[0] += x;
		return result;
	}
	polynomial polynomial::operator-(const real x) const {
		polynomial result(*this);
		result[0] -= x;
		return result;
	}
	polynomial polynomial::operator*(const real x) const {
		polynomial result(*this);
		for (num i = 0; i < size(); ++i)
			result[i] *= x;
		return result;
	}
	polynomial polynomial::operator/(const real x) const {
		polynomial result(*this);
		for (num i = 0; i < size(); ++i)
			result[i] /= x;
		return result;
	}
}