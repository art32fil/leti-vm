#pragma once
#include "Random_vector.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

class Limit_def {
	std::vector<std::ofstream> outfile_array;
	int amount_vars;
public:
	Limit_def(std::string folder = "./", int amount_vars = 1) : amount_vars(amount_vars) {
		outfile_array.reserve(amount_vars);
		for (int i = 0; i < amount_vars; i++) {
			std::cout << folder+std::string("/variant")+std::to_string(i+1)+".txt" << std::endl;
			outfile_array.push_back(std::ofstream(folder+"//variant"+std::to_string(i+1)+".txt"));
		}
	}
	~Limit_def() {
		for (auto& elem : outfile_array) {
			elem.close();
		}
	}

	void generate_ultra_easy_variant(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "По определению предела докажите что<br>";
		std::vector<Random_vector::INT> num = Random_vector(1,-5,5).get_data();
		std::vector<Random_vector::INT> den = Random_vector(2,-5,5).get_data();
		Random_vector::INT a = num[0];
		Random_vector::INT b = den[0];
		Random_vector::INT c = den[1];
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}\\\\frac{";
		print_polinom(out, num);
		out << "}{";
		print_polinom(out, den);
		out <<"} = 0$<br><br>";
		out <<"В качестве ответа укажите номер элемента последовательности (нумерация начинается с 1), начиная с которого все элементы последовательности лежат в эпислон окресности предела при $\\\\varepsilon=0.03$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		double eps = 0.03;
		out << "Max(-("<<c<<")/("<<b<<"), Max(-("<<c<<")/("<<b<<")+("<<a<<")/("<<b<<")/("<<eps<<"), -("<<c<<")/("<<b<<")-("<<a<<")/("<<b<<")/("<<eps<<")))+0.51";
		//int answer = Max(-c/b, Max(-c/b+a/b/eps, -c/b-a/b/eps)+0.51
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"2\",\"integer_only\":true}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}
	void generate_easy_variant(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "По определению предела докажите что<br>";
		auto set = not_collinear_set(2,2,-5,5);
		int a = set[0][0];
		int b = set[0][1];
		int c = set[1][0];
		int d = set[1][1];
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}\\\\frac{";
		print_polinom(out, set[0]);
		out << "}{";
		print_polinom(out, set[1]);
		out <<"} = \\\\frac{" << int(a) << "}{" << int(c) << "}$<br><br>";
		out <<"В качестве ответа укажите номер элемента последовательности (нумерация начинается с 1), начиная с которого все элементы последовательности лежат в эпислон окресности предела при $\\\\varepsilon=0.03$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		double eps = 0.03;
		out << "Max(-("<<d<<")/("<<c<<"), " <<
		       "Max(-("<<d<<")/("<<c<<")-("<<b<<")/("<<c<<")/("<<eps<<")+("<<a<<")*("<<d<<")/("<<c<<")/("<<c<<")/("<<eps<<"),"
		           "-("<<d<<")/("<<c<<")+("<<b<<")/("<<c<<")/("<<eps<<")-("<<a<<")*("<<d<<")/("<<c<<")/("<<c<<")/("<<eps<<")))+0.51";
		//int answer = Max(-d/c, Max(-d/c-b/c/eps-a*d/c/c/eps, -d/c+b/c/eps+a*d/c/c/eps))+0.51
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"2\",\"integer_only\":true}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}

	void generate_easy_root_variant(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "По определению предела докажите что<br>";
		std::vector<std::vector<Random_vector::INT>> set;
		Random_vector::INT a,b,c,d;
		do {
			set  = not_collinear_set(2,2,-5,5);
			a = set[0][0];
			b = set[0][1];
			c = set[1][0];
			d = set[1][1];
		} while (a < 0 || c < 0);
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}\\\\sqrt{\\\\frac{";
		print_polinom(out, set[0]);
		out << "}{";
		print_polinom(out, set[1]);
		out <<"}} = \\\\sqrt{\\\\frac{" << int(a) << "}{" << int(c) << "}}$<br><br>";
		out <<"В качестве ответа укажите номер элемента последовательности (нумерация начинается с 1), начиная с которого все элементы последовательности лежат в эпислон окресности предела при $\\\\varepsilon=0.03$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		double eps = 0.03;
		out << "Max(-("<<d<<")/("<<c<<"), Max(-(("<<b<<")-(sqrt(("<<a<<")/("<<c<<"))-("<<eps<<"))**2*("<<d<<"))/(("<<a<<")-(sqrt(("<<a<<"))-("<<eps<<")*sqrt(("<<c<<")))**2)," <<
		                                     "-((sqrt(("<<a<<")/("<<c<<"))+("<<eps<<"))**2*("<<d<<")-("<<b<<"))/((sqrt(("<<a<<"))+("<<eps<<")*sqrt(("<<c<<")))**2-("<<a<<"))))+0.51";
		//int answer = Max(-d/c, Max(-(b-(sqrt(a/c)-eps)**2*d)/(a-(sqrt(a)-eps*sqrt(c))**2),
		//                           -((sqrt(a/c)+eps)**2*d-b)/((sqrt(a)+eps*sqrt(c))**2-c)))+0.51
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"2\",\"integer_only\":true}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}

	void generate_easy_seq_variant(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "По определению предела докажите что<br>";
		Random_vector::INT a;
		do {
			a = Random_vector(1,-5,5).get_data()[0];
		} while(a == 1 || a == -1);
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}\\\\left(\\\\frac{1}{"<<a<<"}+\\\\frac{1}{"<<a*a<<"}+\\\\frac{1}{"<<a*a*a<<"}+...+\\\\frac{1}{"<<a<<"^n}\\\\right)" <<
		       "=\\\\frac{1}{"<< a-1 <<"}$<br><br>";
		out <<"В качестве ответа укажите номер элемента последовательности (нумерация начинается с 1), начиная с которого все элементы последовательности лежат в эпислон окресности предела при $\\\\varepsilon=0.03$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		double eps = 0.03;
		out << "-log(("<<eps<<")*(Abs("<<a<<")-1),Abs("<<a<<"))";
		//int answer = -log(eps*(|a|-1),|a|)+1,
		//                           -((sqrt(a/c)+eps)**2*d-b)/((sqrt(a)+eps*sqrt(c))**2-c)))+0.51
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"2\",\"integer_only\":true}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}

	void generate_calc_factorial(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "Вычислите предел:<br>";
		std::vector<Random_vector::INT> num = Random_vector(1,1,5).get_data();
		std::vector<Random_vector::INT> den = Random_vector(2,-5,5).get_data();
		Random_vector::INT a = num[0];
		Random_vector::INT b = den[0];
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}\\\\frac{("<<a<<"n+1)!-("<<a<<"n-1)!}{("<<a<<"n)!(";
		print_polinom(out, den);
		out << ")}$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		out << "("<<a<<")/("<<b<<")";
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.0001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}

	void generate_calc_root(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "Вычислите предел:<br>";
		auto set = not_collinear_set(2,2,-5,5);
		Random_vector::INT a = set[0][0];
		Random_vector::INT c = std::abs(set[1][0]);
		Random_vector::INT d = set[1][1];
		Random_vector::INT e = Random_vector(1,-5,5)[0];
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}(";
		print_polinom(out,set[0]);
		out << ")(\\\\sqrt{";
		print_polinom(out,{c*c,d*d,e});
		out << "}-(";
		print_polinom(out, {c,0});
		out << "+\\\\frac{"<<d*d<<"}{2\\\\cdot("<<c<<")}))$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		out << "("<<a<<")*(("<<e<<")-("<<d<<")**4/(4*("<<c<<")**2))/(2*("<<c<<"))";
		//answer = a*(e-d**4/(4*c**2))/(2*c)
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.0001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}
	void generate_calc_root_hard(std::ostream& out) {
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "Вычислите предел:<br>";
		Random_vector::INT a = Random_vector(1,1,5)[0];
		Random_vector::INT b = Random_vector(1,1,5)[0];
		Random_vector::INT c;
		do {
			c = Random_vector(1,-5,5)[0];
		} while (Random_vector::is_equal(c,0));
		Random_vector::INT d;
		do {
			d = Random_vector(1,-5,5)[0];
		} while (Random_vector::is_equal(d,0));
		Random_vector::INT e,f;
		do {
			e = Random_vector(1,-5,5)[0];
			f = Random_vector(1,-5,5)[0];
		} while (Random_vector::is_equal(e,f));
		out << "$\\\\lim_{n\\\\rightarrow\\\\infty}(\\\\sqrt{";
		print_great_monom(out,a,6*b);
		print_low_monom(out,c,0);
		out << "}-\\\\sqrt{";
		print_great_monom(out,a,6*b);
		print_low_monom(out,-c,0);
		out << "})((";
		print_polinom(out, {d,e});
		out << ")^{" << 3*b+1 << "}-(";
		print_polinom(out, {d,f});
		out << ")^{" << 3*b+1 << "})$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		out << "("<<c<<")*(3*("<<b<<")+1)*(("<<e<<")-("<<f<<"))*("<<d<<")**(3*("<<b<<"))/sqrt(("<<a<<"))";
		//answer = c*(3*b+1)*(e-f)*d**(3*b)/sqrt(a)
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.0001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
	}

	void generate(int complexity) {
		for (int i = 0; i < amount_vars; i++) {
			switch (complexity) {
			case 0:
				generate_ultra_easy_variant(outfile_array[i]);
				break;
			case 1:
				generate_easy_variant(outfile_array[i]);
				break;
			case 2:
				generate_easy_root_variant(outfile_array[i]);
				break;
			case 3:
				generate_easy_seq_variant(outfile_array[i]);
				break;
			case 4:
				generate_calc_factorial(outfile_array[i]);
				break;
			case 5:
				generate_calc_root(outfile_array[i]);
				break;
			case 6:
				generate_calc_root_hard(outfile_array[i]);
				break;
			default:
				break;
			}
		}
	}
};
