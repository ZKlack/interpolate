#pragma once
#include<vector>
#include<string>
namespace ZK {
	using real = long double;
	using num = long long;

	class polynomial
	{
	private:
		std::vector<real> _terms;
	public:
		polynomial();
		polynomial(const std::vector<real>&);
		polynomial(const std::initializer_list<real>&);
		polynomial(const polynomial&);

		real operator()(const real&) const;
		polynomial operator()(const polynomial&) const;

		polynomial operator+(const polynomial&) const;
		polynomial operator-(const polynomial&) const;
		polynomial operator*(const polynomial&) const;
		polynomial operator+=(const polynomial&);
		polynomial operator-=(const polynomial&);
		polynomial operator*=(const polynomial&);

		real operator+(real) const;
		real operator-(real) const;
		real operator*(real) const;
		real operator/(real) const;
		real operator+=(real);
		real operator-=(real);
		real operator*=(real);
		real operator/=(real);

		bool operator==(const polynomial&) const;
		bool operator!=(const polynomial&) const;

		real& operator[](num);
		const real& operator[](num) const;
		num size() const;

		explicit operator std::string() const;
		friend std::ostream& operator<<(std::ostream&, const polynomial&);
	};
}