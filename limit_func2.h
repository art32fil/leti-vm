#pragma once
#include "Random_vector.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <cstring>

class Limit_func2 {
	std::vector<std::vector<std::ofstream>> outfile_array;
	int amount_vars;
	const int amount_tasks = 6;
public:
	Limit_func2(std::string folder = "./", int amount_vars = 1) : amount_vars(amount_vars) {
		std::system((std::string("rm -rf ")+folder).c_str());
		outfile_array.reserve(amount_vars);
		for (int i = 0; i < amount_vars; i++) {
			std::string folder_name = folder +
			                          std::string("/variant") +
			                          std::to_string(i+1);
			std::system((std::string("mkdir -p ")+folder_name).c_str());
			std::cout << folder+std::string("/variant")+std::to_string(i+1)+".txt" << std::endl;
			outfile_array.push_back(std::vector<std::ofstream>(amount_tasks));
			for (int j = 0; j < amount_tasks; j++) {
				outfile_array[i][j] = std::ofstream(folder_name+"/task"+std::to_string(j)+".txt");
			}
		}
	}

	~Limit_func2() {
		for (auto& var : outfile_array) {
			for (auto& file : var) {
				file.close();
			}
		}
	}

	std::string generate_easy_x(Random_vector::INT& k, int& deg) {
		std::stringstream s;
		do {
			k = Random_vector(1, -10, 10).get_data()[0];
		} while (k == 0);
		s << print_great_monom(k,1);
		return s.str();
	}

	std::string generate_hard_x(Random_vector::INT& k, int deg, int& type,
	                            std::string& koefs, const char* token_x,
	                            const char* token_k) {
		std::stringstream s;
		std::stringstream ss;
		do {
			k = Random_vector(1, -10, 10).get_data()[0];
		} while (k == 0);
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> ui(4,9);
		int choise = ui(mt);
		if (choise <= 5) {
			std::uniform_int_distribution<int> ui2(1,5);
			choise = ui2(mt);
		}
		std::stringstream deg_func("");
		if (deg != 1)
			deg_func << "^{"<< deg <<"}";
		switch(choise) {
		case 0:
			s << "--X--";
			type = 1;
			break;
		case 1:
			s << "\\\\sin" << deg_func.str() << "\\\\left(" << print_great_koef(k) << token_x  <<"\\\\right)";
			ss << "((" << k << "*" << token_k <<")^(" << deg << "))";
			type = 1;
			break;
		case 2:
			s << "\\\\tan" << deg_func.str() << "\\\\left(" << print_great_koef(k) << token_x << "\\\\right)";
			ss << "((" << k << "*" << token_k <<")^(" << deg << "))";
			type = 1;
			break;
		case 3:
			s << "\\\\arcsin" << deg_func.str() << "\\\\left(" << print_great_koef(k) << token_x << "\\\\right)";
			ss << "((" << k << "*" << token_k <<")^(" << deg << "))";
			type = 1;
			break;
		case 4:
			s << "\\\\arctan" << deg_func.str() << "\\\\left(" << print_great_koef(k) << token_x << "\\\\right)";
			ss << "((" << k << "*" << token_k <<")^(" << deg << "))";
			type = 1;
			break;
		case 5:
			s << "\\\\left(1-\\\\cos" << deg_func.str() << "\\\\left(" << print_great_koef(k) << token_x << "\\\\right)\\\\right)";
			ss << "((" << deg << "/2)*((" << k << "*" << token_k << ")^2))";
			type = 2;
			break;
		case 6:
			s << "\\\\log" << deg_func.str() << "\\\\left(1" << (k > 0? "+": "") << print_great_koef(k) << token_x << "\\\\right)";
			ss << "((" << k << "*(" << token_k <<"))^(" << deg << "))";
			type = 1;
			break;
		case 7:
			s << "\\\\left(e^{"  << print_great_koef(k) << token_x <<  "}-1" << "\\\\right)";
			ss << "("<< k << "*("  << token_k <<"))";
			type = 3;
			break;
		case 8: {
			Random_vector::INT a = get_rand(2,5);
			s << "\\\\left(" << a << "^{"  << print_great_koef(k) << token_x <<  "}-1" << "\\\\right)";
			ss << "("<< k << "*log(" << a <<")*("  << token_k <<"))";
			type = 3;
			break;
		}
		case 9: {
			Random_vector::INT a;
			do {
				a = get_rand(-5,5);
			} while (a == 0);
			Random_vector::INT b;
			do {
				b = get_rand(2,5);
			} while (b == a);
			s << "\\\\left(\\\\left(1" << (k > 0? "+": "") << print_great_koef(k) << token_x  << "\\\\right)" << print_deg(a,b)<< "-1\\\\right)";
			ss << "(" << k << "*(" << a << ")/" << b << "*(" << token_k <<"))";
			type = 3;
		}
		}

		koefs = ss.str();
		return s.str();
	}

	void update_token(std::string& input, std::string& koefs, int deg, int& type, const char* token_x, const char* token_k) {
		auto pos = input.find(token_x);
		Random_vector::INT k;
		std::string koef_current;
		input.replace(pos, strlen(token_x), generate_hard_x(k,deg,type,koef_current,token_x,token_k));
		pos = koefs.find(token_k);
		koefs.replace(pos, strlen(token_k), koef_current);
		return;
	}
	std::string& generate_1st_limit_queue(int* deg, const int n, int total_deg, std::string& input, std::string& koef) {
		int sum_deg = 1;
		for (int i = 0; i < n; i++) {
			int type;
			update_token(input, koef, deg[i],type,"--X--","--K--");
			if (type == 2) {
				sum_deg*=2;
			}
			else if (type == 3) {
				sum_deg *= 1;
			}
			else {
				sum_deg *= deg[i];
			}
		}
		std::stringstream s;
		int nod = NOD(total_deg, sum_deg);
		if (sum_deg/nod == 1) {
			if (total_deg/nod == 1)
				s << "x";
			else
				s << "x^{" << total_deg/nod << "}";
		}
		else {
			s << "x^{\\\\frac{" << total_deg/nod << "}{"<< sum_deg/nod << "}}";
		}
		input.replace(input.find("--X--"), 5, s.str().c_str());
		koef.replace(koef.find("--K--"), 5, "1");
		return input;
	}

	int get_rand(int a, int b) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> ui(a,b);
		return ui(mt);
	}

	int* get_random_seq(int n, int sum) {
		int* out = new int[n+1];
		out[0] = 1;
		do {
			int cur_sum = 0;
			for (int i = 1; i < n; i++) {
				out[i] = get_rand(1,2*sum/double(n));
				cur_sum += out[i];
			}
			out[n] = sum - cur_sum;
		} while (out[n] <= 0);
		return out+1;
	}



	std::string generate_task_1st_limit(int amount_func_num, int amount_func_den, int total_deg) {
		std::stringstream out;
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "Вычислите предел <br>";
		int* ar_num = get_random_seq(amount_func_num,total_deg);
		int* ar_den = get_random_seq(amount_func_den,total_deg);
		std::string num_input = "--X--";
		std::string num_koef = "--K--";
		std::string den_input = "--X--";
		std::string den_koef = "--K--";

		out << "$\\\\lim_{x\\\\rightarrow 0}\\\\frac{" << generate_1st_limit_queue(ar_num, amount_func_num, total_deg, num_input, num_koef)
		    << "}{"+ generate_1st_limit_queue(ar_den, amount_func_den, total_deg, den_input, den_koef)+"}$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		out << "(" << num_koef << ")/(" << den_koef << ")";
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.00000001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
		return out.str();
	}

	std::string generate_task_2nd_limit(int amount_func_num, int amount_func_den, int total_deg) {
		std::stringstream out;
		out << "{\"block\":{\"name\":\"math\",\"text\":\"";
		out << "Вычислите предел <br>";
		int* ar_num = get_random_seq(amount_func_num,total_deg);
		int* ar_den = get_random_seq(amount_func_den,total_deg);
		std::string num_input = "--X--";
		std::string num_koef = "--K--";
		std::string den_input = "--X--";
		std::string den_koef = "--K--";

		out << "$\\\\lim_{x\\\\rightarrow 0}\\\\left(1+" << generate_1st_limit_queue(ar_num, amount_func_num, total_deg, num_input, num_koef)
		    << "\\\\right)^\\\\frac{1}{"+ generate_1st_limit_queue(ar_den, amount_func_den, total_deg, den_input, den_koef)+"}$<br><br>";
		out << "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out << "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		out << "exp((" << num_koef << ")/(" << den_koef << "))";
		out << "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.00000001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
		return out.str();
	}

	std::string generate_task_0() {
		return generate_task_2nd_limit(2,1,6);
	}

	std::string generate_task_1() {
		return generate_task_2nd_limit(3,2,12);
	}

	std::string generate_task_2() {
		return generate_task_1st_limit(2,1,6);
	}

	std::string generate_task_3() {
		return generate_task_1st_limit(3,2,12);
	}

	std::string generate_task_4() {
		return generate_task_1st_limit(4,3,24);
	}

	std::string generate_task_5() {
		return generate_task_2nd_limit(4,4,24);
	}

	void generate() {
		for (int i = 0; i < amount_vars; i++) {
			outfile_array[i][0] << generate_task_0().c_str();
			outfile_array[i][1] << generate_task_1().c_str();
			outfile_array[i][2] << generate_task_2().c_str();
			outfile_array[i][3] << generate_task_3().c_str();
			outfile_array[i][4] << generate_task_4().c_str();
			outfile_array[i][5] << generate_task_5().c_str();

		}
		std::cout << "finish!" << std::endl;
	}
};
