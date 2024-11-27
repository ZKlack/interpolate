#pragma once
#include"polynomial.h"
#include<map>
namespace ZK {
	class interpolation
	{
	private:
		polynomial(*_interpolator)(const std::vector<std::pair<real, real> >&);
		std::map<real,real> _points;
		polynomial _func;
		void recompute();
	public:
		interpolation(polynomial(*)(const std::vector<std::pair<real, real> >&));
		interpolation(polynomial(*)(const std::vector<std::pair<real, real> >&), const std::map<real, real>&);
		interpolation(const interpolation&);

		real operator()(const real) const;
		polynomial operator()(const polynomial&) const;

		real get(const real) const;
		real set(const real, const real);
		real set(const std::pair<real, real>&);
		void set(const std::map<real, real>&);
		bool remove(const real);
		void clear();

		std::vector<std::pair<real, real> > points() const;
		num sample_size() const;
		num degree() const;
	};
}