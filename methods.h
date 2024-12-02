#pragma once
#include"polynomial.h"
#include <map>

namespace ZK {
	namespace methods {
		namespace interpolation {
			extern const std::map<std::string, polynomial(*)(const std::vector<std::pair<real, real> >&)> methods;

			polynomial newtons_forward(const std::vector<std::pair<real, real> >&);
			polynomial newtons_backward(const std::vector<std::pair<real, real> >&);
			polynomial newtons_general_devided(const std::vector<std::pair<real, real> >&);
			polynomial lagranges(const std::vector<std::pair<real, real> >&);
		}
	}
}