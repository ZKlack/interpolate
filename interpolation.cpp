#include "interpolation.h"

namespace ZK {
	interpolation::interpolation(polynomial(*interpolator)(const std::vector<std::pair<real, real> >&))
		: _interpolator(interpolator)
		, _points()
		, _func(_interpolator({}))
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

	real interpolation::operator()(const real x) const {
		return _func(x);
	}
	polynomial interpolation::operator()(const polynomial& x) const {
		return _func(x);
	}

	std::optional<real> interpolation::get(const real x) const {
		auto point = _points.find(x);
		if (point == _points.end())
			return std::nullopt;
		return point->second;
	}

	real interpolation::set(const real x, const real y) {
		_points[x] = y;
		recompute();
		return _points[x];
	}
	real interpolation::set(const std::pair<real, real>& point) {
		_points[point.first] = point.second;
		recompute();
		return _points[point.first];
	}
	void interpolation::set(const std::map<real, real>& points) {
		for (auto point = points.begin(); point != points.end(); ++point)
			_points[point->first] = point->second;
		recompute();
	}
	bool interpolation::remove(const real x) {
		bool exists = _points.contains(x);
		_points.erase(x);
		recompute();
		return exists;
	}
	void interpolation::clear()
	{
		_points.clear();
		recompute();
	}
}