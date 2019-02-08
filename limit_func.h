#pragma once
#include "Random_vector.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <cstring>

class Limit_func {
	std::vector<std::vector<std::ofstream>> outfile_array;
	int amount_vars;
	const int amount_tasks = 7;
public:
	Limit_func(std::string folder = "./", int amount_vars = 1) : amount_vars(amount_vars) {
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

	~Limit_func() {
		for (auto& var : outfile_array) {
			for (auto& file : var) {
				file.close();
			}
		}
	}

	std::string generate_task_0() {
		std::string out = "";
		out += "{\"block\":{\"name\":\"math\",\"text\":\"";
		out += "По определению предела докажите что<br>";
		Random_vector::INT a = Random_vector(1,20,70).get_data()[0];
		std::vector<Random_vector::INT> v = Random_vector(2,-5,5).get_data();
		Random_vector::INT b = v[0], c = v[1];
		out += "$\\\\lim_{x\\\\rightarrow\\\\frac{"+std::to_string(2*a)+"\\\\pi}{3}}("+print_great_koef(b)+"\\\\cos x "+ print_low_monom(c,0)+") =";
		if ((2*a)%3 == 0)
			out += std::to_string(b+c);
		else
			out += std::to_string(c-double(b)/2.0);
		out += "$<br><br>";
		double eps = 0.0003;
		out += "В качестве ответа укажите значение $\\\\delta$, такое что $\\\\delta$-окрестность полностью переходит в $\\\\varepsilon$-окрестность под действием функции, находящейся под пределом, при $\\\\varepsilon="+std::to_string(eps)+"$<br><br>";
		out += "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out += "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		if ((2*a)%3 == 0) {
			//answer = arccos(-eps/|b|+1)
			out += "acos(-"+std::to_string(eps)+"/Abs("+std::to_string(b)+")+1)";
		}
		else if ((2*a)%3 == 1) {
			//answer = Min(|arccos(eps/|b|-1/2)-2*pi/3|, |arccos(-eps/|b|-1/2)-2*pi/3|)
			out += "Min(Abs(acos("+std::to_string(eps)+"/Abs("+std::to_string(b)+")-1/2)-2*pi/3.0), Abs(acos(-"+std::to_string(eps)+"/Abs("+std::to_string(b)+")-1/2)-2*pi/3.0))";
		}
		else if ((2*a)%3 == 2) {
			//answer = Min(|-arccos(-eps/|b|-1/2)+2*pi/3|, |-arccos(eps/|b|-1/2)+2*pi/3|)
			out += "Min(Abs(-acos(-"+std::to_string(eps)+"/Abs("+std::to_string(b)+")-1/2)+2*pi/3.0), Abs(-acos("+std::to_string(eps)+"/Abs("+std::to_string(b)+")-1/2)+2*pi/3.0))";
		}

		/*out += "Min(Min(Abs( acos(-("+std::to_string(eps)+")+cos(2*("+std::to_string(a)+")*pi/3.0))+2*pi*"+std::to_string(round(a/3))+"-2*("+std::to_string(a)+")*pi/3.0),";
		out +=         "Abs(-acos(-("+std::to_string(eps)+")+cos(2*("+std::to_string(a)+")*pi/3.0))+2*pi*"+std::to_string(round(a/3))+"-2*("+std::to_string(a)+")*pi/3.0)),";
		out +=     "Min(Abs( acos( ("+std::to_string(eps)+")+cos(2*("+std::to_string(a)+")*pi/3.0))+2*pi*"+std::to_string(round(a/3))+"-2*("+std::to_string(a)+")*pi/3.0),";
		out +=         "Abs(-acos( ("+std::to_string(eps)+")+cos(2*("+std::to_string(a)+")*pi/3.0))+2*pi*"+std::to_string(round(a/3))+"-2*("+std::to_string(a)+")*pi/3.0)))";
*/
		out += "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.00000001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
		return out;
	}

	std::string generate_task_1() {
		std::string out = "";
		out += "{\"block\":{\"name\":\"math\",\"text\":\"";
		out += "По определению предела докажите что<br>";
		Random_vector::INT a = Random_vector(1,-10,10).get_data()[0];
		Random_vector::INT b = 0, c = 0;
		std::vector<Random_vector::INT> v = Random_vector(2,-5,5).get_data();
		b = v[0]; c = v[1];
		double eps = 0.0003;
		out += "$\\\\lim_{x\\\\rightarrow"+std::to_string(a)+"}\\\\sqrt{("+print_polinom({b,c})+")^2+1} = ";
		out += "\\\\sqrt{(("+std::to_string(a)+")\\\\cdot("+std::to_string(b)+")"+print_low_monom(c,0)+")^2+1}$<br><br>";
		out += "В качестве ответа укажите значение $\\\\delta$, такое что $\\\\delta$-окрестность полностью переходит в $\\\\varepsilon$-окрестность под действием функции, находящейся под пределом, при $\\\\varepsilon="+std::to_string(eps)+"$<br><br>";
		out += "Справка по способу ввода математических функций: <a rel=\\\"nofollow\\\" href=\\\"http://docs.sympy.org/latest/modules/functions/index.html#contents\\\">http://docs.sympy.org/latest/modules/functions/index.html#contents</a><br>\",";
		out += "\"video\":null,\"animation\":null,\"options\":{},\"subtitle_files\":[],\"source\":{\"answer\":\"";
		if (a*b+c > 0) {
			out += "Min(Abs((sqrt((-("+std::to_string(eps)+")+sqrt((("+std::to_string(a)+")*("+std::to_string(b)+".0)+("+std::to_string(c)+"))**2+1))**2-1)-("+std::to_string(c)+"))/("+std::to_string(b)+".0)-("+std::to_string(a)+")), "+
			           "Abs((sqrt(( ("+std::to_string(eps)+")+sqrt((("+std::to_string(a)+")*("+std::to_string(b)+".0)+("+std::to_string(c)+"))**2+1))**2-1)-("+std::to_string(c)+"))/("+std::to_string(b)+".0)-("+std::to_string(a)+")))";
			/* answer = min(|(sqrt((-eps+sqrt((a*b+c)**2+1))**2-1)-c)/b-a|,
			                |(sqrt(( eps+sqrt((a*b+c)**2+1))**2-1)-c)/b-a|)
			      / |  ____________________________        |  |  ___________________________        | \
			      | | /        _____________               |  | /       _____________               | |
			   min| |V(-eps + V(a*b+c)^2 + 1)^2 - 1 - c    |, |V(eps + V(a*b+c)^2 + 1)^2 - 1 - c    | |
			      | |---------------------------------- - a|  |--------------------------------- - a| |
			      \ |                 b                    |  |                b                    | /*/
		}
		else {
			out += "Min(Abs((-sqrt((-("+std::to_string(eps)+")+sqrt((("+std::to_string(a)+")*("+std::to_string(b)+".0)+("+std::to_string(c)+"))**2+1))**2-1)-("+std::to_string(c)+"))/("+std::to_string(b)+".0)-("+std::to_string(a)+")), "+
			           "Abs((-sqrt(( ("+std::to_string(eps)+")+sqrt((("+std::to_string(a)+")*("+std::to_string(b)+".0)+("+std::to_string(c)+"))**2+1))**2-1)-("+std::to_string(c)+"))/("+std::to_string(b)+".0)-("+std::to_string(a)+")))";
			/* answer = min(abs((-sqrt((-eps+sqrt((a*b+c)**2+1))**2-1)-c)/b),
			                abs((-sqrt(( eps+sqrt((a*b+c)**2+1))**2-1)-c)/b))
			      / |   ____________________________        |  |   ___________________________        | \
			      | |  /        _____________               |  |  /       _____________               | |
			   min| |-V(-eps + V(a*b+c)^2 + 1)^2 - 1 - c    |, |-V(eps + V(a*b+c)^2 + 1)^2 - 1 - c    | |
			      | |----------------------------------- - a|  |---------------------------------- - a| |
			      \ |                  b                    |  |                 b                    | /*/
		}
		out += "\",\"numerical_test\":{\"z_re_min\":\"2\",\"z_re_max\":\"3\",\"z_im_min\":\"-1\",\"z_im_max\":\"1\",\"max_error\":\"0.00000001\",\"integer_only\":false}},\"subtitles\":{},\"tests_archive\":null,\"feedback_correct\":\"\",\"feedback_wrong\":\"\"},\"id\":\"339348\",\"time\":\"2018-09-19T05:37:08.945Z\"}";
		return out;
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
		std::uniform_int_distribution<int> ui(1,5);
		// x, sin(x), tg(x), arcsin(x), arctg(x), 2-2cos(x)
		std::stringstream deg_func("");
		if (deg != 1)
			deg_func << "^{"<< deg <<"}";
		switch(ui(mt)) {
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

	int NOD(int vl, int v2)	{
		while (v2) {
			int temp=v2;
			v2=vl%v2;
			vl=temp;
		}
		return vl;
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

	std::string generate_task_2() {
		return generate_task_1st_limit(2,1,5);
	}

	std::string generate_task_3() {
		return generate_task_1st_limit(3,2,10);
	}

	std::string generate_task_4() {
		return generate_task_1st_limit(4,3,15);
	}

	std::string generate_task_5() {
		return generate_task_1st_limit(4,4,15);
	}

	std::string generate_task_6() {
		return generate_task_1st_limit(5,3,20);
	}

	void generate() {
		for (int i = 0; i < amount_vars; i++) {
			outfile_array[i][0] << generate_task_0().c_str();
			outfile_array[i][1] << generate_task_1().c_str();
			outfile_array[i][2] << generate_task_2().c_str();
			outfile_array[i][3] << generate_task_3().c_str();
			outfile_array[i][4] << generate_task_4().c_str();
			outfile_array[i][5] << generate_task_5().c_str();
			outfile_array[i][6] << generate_task_6().c_str();

		}
		std::cout << "finish!" << std::endl;
	}
};
