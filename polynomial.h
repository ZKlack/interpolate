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
		void trim();
	public:
		polynomial();
		polynomial(const real);
		polynomial(const std::vector<real>&);
		polynomial(const std::initializer_list<real>&);
		polynomial(const polynomial&);

		real operator()(const real) const;
		polynomial operator()(const polynomial&) const;

		polynomial operator+(const polynomial&) const;
		polynomial operator-(const polynomial&) const;
		polynomial operator*(const polynomial&) const;
		polynomial& operator+=(const polynomial&);
		polynomial& operator-=(const polynomial&);
		polynomial& operator*=(const polynomial&);

		polynomial operator+(const real) const;
		polynomial operator-(const real) const;
		polynomial operator*(const real) const;
		polynomial operator/(const real) const;
		polynomial& operator+=(const real);
		polynomial& operator-=(const real);
		polynomial& operator*=(const real);
		polynomial& operator/=(const real);

		bool operator==(const polynomial&) const;
		bool operator!=(const polynomial&) const;

		real& operator[](const num);
		const real& operator[](const num) const;
		num size() const;

		operator std::string() const;
		friend std::ostream& operator<<(std::ostream&, const polynomial&);
	};
}