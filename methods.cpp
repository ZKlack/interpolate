#pragma once
#include"polynomial.h"
#include<vector>
#include<stdexcept>

namespace ZK::methods {
	namespace interpolation {
		//example signature
		//polynomial method_name(const std::vector<std::pair<real, real> >& points)


		polynomial newtons_forward(const std::vector<std::pair<real, real> >& points) {
			if (points.size() == 0)
				return 0;
			if (points.size() == 1)
				return points[0].second;
			num sample = points.size();
			real h = points[1].first - points[0].first;
			for(num i=2;i<sample;++i)
				if(points[i].first-points[i-1].first!=sample)
					throw std::invalid_argument("unequal intervals.");

			std::vector<std::vector<real> > table(sample, std::vector<real>(sample, 0));
			for (num j = 0; j < sample; ++j)
				table[0][j] = points[j].second;
			for (num i = 1; i < sample; ++i)
				for (num j = 0; j < sample - i; ++j)
					table[i][j] = table[i - 1][j + 1] - table[i - 1][j];

			polynomial u = { -points[0].first,1 };
			u /= h;
			polynomial result = 0;
			for (num n = 0; n < sample; ++n)
			{
				polynomial term = table[n][0];
				for (num i = 0; i < n; ++i)
					term *= (u - i) / n - i;
				result += term;
			}
			return result;
		}
	}
}