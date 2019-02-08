#pragma once
#include <vector>
#include <random>
#include <ostream>
#include <sstream>

class Random_vector {
public:
	using INT = int;
private:
	std::vector<INT> data;
	std::mt19937 mt;
	std::random_device rd;

public:
	static bool is_equal(INT a, INT b) {
		return a == b;
	}

	static bool is_equal(double a, double b) {
		return fabs(a-b) < 0.001;
	}

	Random_vector(size_t size, const INT& min = INT(0), const INT& max = INT(0)) {
		generate(size, min, max);
	}
	Random_vector(const Random_vector& rv) {
		data = rv.data;
		mt.seed(rd());
	}

	std::vector<INT>& generate(size_t size, const INT& min = INT(0),
	                                     const INT& max = INT(0)) {
		data = std::vector<INT>(size);
		if (size > 0) {
			mt.seed(rd());
			std::uniform_int_distribution<INT> rand(min, max);
			do {
				data[0] = rand(mt);
			} while (is_equal(data[0],INT(0)));
			for (size_t i = 1; i < data.size(); i++) {
				data[i] = rand(mt);
			}
		}
		return data;
	}

	INT& operator[] (size_t i) { return data[i]; }
	const INT& operator[] (size_t i) const { return data[i]; }
	std::vector<INT>& get_data() { return data; }
	const std::vector<INT>& get_data() const { return data; }
	const size_t size() const {
		return data.size();
	}

	friend std::ostream& operator << (std::ostream& ostr, const Random_vector& a) {
		for (const auto& elem : a.data) {
			ostr << elem << " ";
		}
		return ostr;
	}
};

bool are_collinear(const std::vector<Random_vector::INT>& a,
                   const std::vector<Random_vector::INT>& b) {
	if (a.size() != b.size())
		return false;
	double k = double(a[0])/double(b[0]);
	for (size_t i = 1; i < a.size(); i++) {
		if (!Random_vector::is_equal(k, double(a[i])/double(b[i])))
			return false;
	}
	return true;
}

std::vector<std::vector<Random_vector::INT>> not_collinear_set(size_t amount,
                                                               size_t size,
                                                               const Random_vector::INT& min = Random_vector::INT(-1),
                                                               const Random_vector::INT& max = Random_vector::INT(1)) {
	std::vector<std::vector<Random_vector::INT>> out;
	if (amount == 0)
		return out;
	if (amount > size)
		return out;
	Random_vector a{size, min, max};
	out.push_back(a.get_data());
	for (size_t i = 1; i < amount; i++) {
		Random_vector next{size, min, max};
		bool not_collinear = true;
		for (size_t j = 0; j < i; j++) {
			not_collinear &= !are_collinear(next.get_data(), out[j]);
		}
		if (not_collinear) {
			out.push_back(next.get_data());
		}
		else {
			i--;
		}
	}
	return out;
}

void print_x(std::ostream& ostr, size_t degree) {
	if (Random_vector::is_equal(degree, 0))
		return;
	if (Random_vector::is_equal(degree, 1)) {
		ostr << "n";
		return;
	}
	ostr << "n^{" << degree << "}";
	return;
}

void print_great_koef(std::ostream& ostr, Random_vector::INT k) {
	if (Random_vector::is_equal(k, 1))
		return;
	if (Random_vector::is_equal(k, -1)) {
		ostr << "-";
		return;
	}
	ostr << k;
	return;
}

void print_great_monom(std::ostream& ostr, Random_vector::INT k, size_t degree) {
	if (Random_vector::is_equal(k,1) && Random_vector::is_equal(degree,0)) {
		ostr << "1";
		return;
	}
	if (Random_vector::is_equal(k,-1) && Random_vector::is_equal(degree,0)) {
			ostr << "-1";
			return;
	}
	print_great_koef(ostr, k);
	print_x(ostr, degree);
	return;
}

void print_low_monom(std::ostream& ostr, Random_vector::INT k, size_t degree) {
	if (Random_vector::is_equal(k, 0))
		return;
	if (k > 0)
		ostr << "+";
	if (Random_vector::is_equal(k,1)) {
		if (Random_vector::is_equal(degree, 0))
			ostr << "1";
		else
			print_x(ostr, degree);
		return;
	}
	if (Random_vector::is_equal(k,-1)) {
		if (Random_vector::is_equal(degree, 0))
			ostr << "-1";
		else {
			ostr << "-";
			print_x(ostr, degree);
		}
		return;
	}
	ostr << k;
	print_x(ostr, degree);
	return;
}

void print_polinom(std::ostream& ostr, const std::vector<Random_vector::INT>& p) {
	int degree = p.size()-1;
	if (degree < 0)
		return;
	print_great_monom(ostr, p[0], degree);
	for (size_t i = 1; i < p.size(); i++)
		print_low_monom(ostr, p[i], degree-i);
	return;
}

std::string print_x(size_t degree) {
	std::stringstream ostr("");
	if (Random_vector::is_equal(degree, 0))
		return ostr.str().c_str();
	if (Random_vector::is_equal(degree, 1)) {
		ostr << "x";
		return ostr.str().c_str();
	}
	ostr << "x^{" << degree << "}";
	return ostr.str().c_str();
}

std::string print_great_koef(Random_vector::INT k) {
	std::stringstream ostr("");
	if (Random_vector::is_equal(k, 1))
		return ostr.str().c_str();
	if (Random_vector::is_equal(k, -1)) {
		ostr << "-";
		return ostr.str();
	}
	ostr << k;
	return ostr.str();
}

std::string print_great_monom(Random_vector::INT k, size_t degree) {
	std::stringstream ostr("");
	if (Random_vector::is_equal(k,1) && Random_vector::is_equal(degree,0)) {
		ostr << "1";
		return ostr.str();
	}
	if (Random_vector::is_equal(k,-1) && Random_vector::is_equal(degree,0)) {
			ostr << "-1";
			return ostr.str();
	}
	ostr << print_great_koef(k);
	ostr << print_x(degree);
	return ostr.str();
}

std::string print_low_monom(Random_vector::INT k, size_t degree) {
	std::stringstream ostr("");
	if (Random_vector::is_equal(k, 0))
		return ostr.str();
	if (k > 0)
		ostr << "+";
	if (Random_vector::is_equal(k,1)) {
		if (Random_vector::is_equal(degree, 0))
			ostr << "1";
		else
			ostr << print_x(degree);
		return ostr.str();
	}
	if (Random_vector::is_equal(k,-1)) {
		if (Random_vector::is_equal(degree, 0))
			ostr << "-1";
		else {
			ostr << "-" << print_x(degree);
		}
		return ostr.str();
	}
	ostr << k << print_x(degree);
	return ostr.str();
}

std::string print_polinom(const std::vector<Random_vector::INT>& p) {
	std::stringstream ostr("");
	int degree = p.size()-1;
	if (degree < 0)
		return ostr.str();
	ostr << print_great_monom(p[0], degree);
	for (size_t i = 1; i < p.size(); i++)
		ostr << print_low_monom(p[i], degree-i);
	return ostr.str();
}

template <typename T>
T NOD(T vl, T v2)	{
	while (v2) {
		T temp=v2;
		v2=vl%v2;
		vl=temp;
	}
	return vl;
}

template <typename T>
std::string print_deg(const T a, const T b) {
	std::stringstream s;
	int nod = NOD(a, b);
	if (b/nod == 1) {
		if (a/nod == 1)
			s << "";
		else
			s << "^{" << a/nod << "}";
	}
	else {
		s << "^{\\\\frac{" << a/nod << "}{"<< b/nod << "}}";
	}
	return s.str();
}
