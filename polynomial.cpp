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
}