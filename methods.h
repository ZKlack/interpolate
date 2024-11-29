#pragma once
#include"polynomial.h"

namespace ZK::methods {
	namespace interpolation {
		polynomial newtons_forward(const std::vector<std::pair<real, real> >&);
	}
}