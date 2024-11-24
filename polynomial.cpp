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
}