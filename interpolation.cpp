#include "interpolation.h"

namespace ZK {
	interpolation::interpolation(polynomial(*interpolator)(const std::vector<std::pair<real, real> >&))
		: _interpolator(interpolator)
		, _points()
		, _func(_interpolator({})
	{ }
	interpolation::interpolation(polynomial(*interpolator)(const std::vector<std::pair<real, real> >&), const std::map<real, real>& points)
		: _interpolator(interpolator)
		, _points(points)
		, _func(_interpolator(rewrap(_points)))
	{ }
	interpolation::interpolation(const interpolation& other)
		: _interpolator(other._interpolator)
		, _points(other._points)
		, _func(other._func)
	{ }
}