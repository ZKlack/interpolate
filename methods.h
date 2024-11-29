#pragma once
#include"polynomial.h"

namespace ZK::methods {
	namespace interpolation {
		polynomial newtons_forward(const std::vector<std::pair<real, real> >&);
		polynomial newtons_backward(const std::vector<std::pair<real, real> >&);
		polynomial newtons_general_devided(const std::vector<std::pair<real, real> >&);
	}
}