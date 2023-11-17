#include "Pars.h"
#include "Mathh.h"
#include <iostream>
int ctoi(char* a) {
	int b = 0;
	for (int i = 0; isdigit(a[i]); i++) {
		b = (b * 10) + (static_cast<int>(a[i]) - 48);
	}
	return b;
}
double ctod(char* a) {
	double d = 0;
	bool point = 0;
	int after_p = 1;
	for (int i = 0; isdigit(a[i]) || a[i] == '.' || a[i] == ','; i++) {
		if (a[i] == ',' || a[i] == '.') {
			point = 1;
			continue;
		}
		if (!point) {
			d = (d * 10) + (static_cast<double>(a[i]) - 48);
		}
		else if (point) {
			d = d + static_cast<double>((static_cast<double>(a[i]) - 48) / pow(10, after_p));
			after_p++;
		}
	}
	return d;
}
double pars(char* a, double first, bool switc) {
	int j = 0, num_of_b_o = 0, num_of_b_c = 0;
	double second = 0, third = 0;
	bool i_d = 0;
	bool find = 0;
	char sym_f = 0, sym_s = 0, sym_t = 0, sym_fo = 0;
	if (switc) {
		if (first != 0) {
			find = 1;
		}
	}
	for (int i = 0; a[i];) {
		if (!find) {
			if (a[i] == '(') {
				sym_f = '(';
				i++;
			} 
			if (sym_f != '(') {
				if (isdigit(a[i])) {
					for (; isdigit(a[i + j]) || a[i + j] == ',' || a[i + j] == '.'; j++) {
						if (a[i + j] == ',' || a[i + j] == '.') {
							i_d = 1;
						}
					}
					if (i_d) {
						first = ctod(a + i);
					}
					else {
						first = ctoi(a + i);
					}
					i += j;
					j = 0;
					i_d = 0;
				}
			}
			else if (sym_f == '(') {
				num_of_b_o = 1;
				first = brackets(a + i, first);
				for (; a[i + j] && num_of_b_o != num_of_b_c; j++) {
					if (a[i + j] == '(') {
						num_of_b_o++;
					}
					else if (a[i + j] == ')') {
						num_of_b_c++;
					}
				} // len of brackets
				i += j;
				j = 0;
				num_of_b_o = 0;
				num_of_b_c = 0;
			}
			find = 1;
			sym_f = 0;
		}
		if (find) {
			if (a[i] == ' ' || a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '(' || a[i] == ')') {
				sym_search(i, j, a, sym_f, sym_s);
				i += j;
				j = 0;
			} //first and mb second sym find
			for (; a[i + j] && (isdigit(a[i + j]) || a[i + j] == ',' || a[i + j] == '.'); j++) {
				if (a[i + j] == ',' || a[i + j] == '.') {
					i_d = 1;
				}
			} //len of second num
			if (!i_d) {
				second = ctoi(a + i);
			} //if second is int
			else if (i_d) {
				second = ctod(a + i);
			} //if second is double
			i_d = 0;
			i += j;
			j = 0;
			if (sym_s == '(') {
				num_of_b_o = 1;
				second = brackets(a + i, second);
				for (; a[i + j] && num_of_b_o != num_of_b_c; j++) {
					if (a[i + j] == '(') {
						num_of_b_o++;
					}
					else if (a[i + j] == ')') {
						num_of_b_c++;
					}
				} // len of brackets
				i += j;
				j = 0;
				num_of_b_o = 0;
				num_of_b_c = 0;
				if (sym_f == '+' || sym_f == '-') {
					sym_search(i,j,a,sym_t,sym_fo);
					if (sym_t == '*' || sym_t == '/') {
						i += j;
						j = 0;
						if (sym_fo != '(') {
							for (; isdigit(a[i + j]) || a[i + j] == ',' || a[i + j] == '.'; j++) {
								if (a[i + j] == ',' || a[i + j] == '.') {
									i_d = 1;
								}
							} //len of third
							if (!i_d) {
								third = ctoi(a + i);
							} //if third is int
							else if (i_d) {
								third = ctod(a + i);
							} //if third is double
							i_d = 0;
							i += j;
							j = 0;
						} //if four sym isnt (
						else if (sym_fo == '(') {
							num_of_b_o = 1;
							third = brackets(a + i, second);
							for (; a[i + j] && num_of_b_o != num_of_b_c; j++) {
								if (a[i + j] == '(') {
									num_of_b_o++;
								} //if inside brackets we have other brackets
								else if (a[i + j] == ')') {
									num_of_b_c++;
								} //if we get one closed bracket
							} //bracket len
							i += j;
							j = 0;
							num_of_b_o = 0;
							num_of_b_c = 0;
						} //if four sym is (
						if (sym_t == '*') {
							second = multi(second, third);
						} //if third sym is *
						else if (sym_t == '/') {
							second = divided(second, third);
						} //if third sym is /
					} // if first sym  is + or -, second sym is (, and third sym is * or /
					j = 0;
				} // if first sym is + or - and second is (
			} //if second sym is (
			else if (!sym_s && (sym_f == '+' || sym_f == '-')) {
				sym_search(i, j, a, sym_s, sym_t);
				if (sym_s == '*' || sym_s == '/') {
					for (; a[i] && (sym_s == '*' || sym_s == '/');) {
						i += j;
						j = 0;
						for (; a[i + j] && (isdigit(a[i + j]) || a[i + j] == ',' || a[i + j] == '.'); j++) {
							if (a[i + j] == ',' || a[i + j] == '.') {
								i_d = 1;
							}
						}
						if (!i_d) {
							third = ctoi(a + i);
						}
						else if (i_d) {
							third = ctod(a + i);
						}
						i_d = 0;
						i += j;
						j = 0;
						if (sym_t != '(') {
							sym_search(i, j, a, sym_t, sym_fo);
							i += j;
							j = 0;
						}
						else if (sym_t == '(') {
							num_of_b_o = 1;
							third = brackets(a + i, third);
							for (; a[i + j] && num_of_b_o != num_of_b_c; j++) {
								if (a[i + j] == '(') {
									num_of_b_o++;
								}
								else if (a[i + j] == ')') {
									num_of_b_c++;
								}
							}
							i += j;
							j = 0;
							num_of_b_o = 0;
							num_of_b_c = 0;
						}
						j = 0;
						if (sym_s == '*') {
							second = multi(second, third);
						}
						else if (sym_s == '/') {
							second = divided(second, third);
						}
						sym_s = sym_t;
						sym_t = sym_fo;
						sym_fo = 0;
						third = 0;
					}
					j = 0;
				} // if first sym is + or - and second sym is * or /
				j = 0;
			} // if second sym isnt (
			if (sym_f == '+') {
				first = add(first, second);
			}
			else if (sym_f == '-') {
				first = minu(first, second);
			}
			else if (sym_f == '*') {
				first = multi(first, second);
			}
			else if (sym_f == '/') {
				first = divided(first, second);
			}
			sym_f = 0;
			sym_s = 0;
			sym_t = 0;
			sym_fo = 0;
			second = 0;
			third = 0;
			if (switc && a[i] == ')') {
				return first;
			}
		}
		else { continue; }
	}
	return first;
}
double brackets(char* a, double num_f = 0) {
	double res = pars(a, num_f, static_cast<bool>(1));
	return res;
}
int error(char* a) {
	for (int i = 0; a[i]; i++) {
		if (a[i] != ' ' && !isdigit(a[i]) && a[i] != '+' && a[i] != '-' && a[i] != '*' && a[i] != '/' && a[i] != ',' && a[i] != '.' && a[i] != '(' && a[i] != ')') {
			return 1;
		}
	}
	return 0;
}

void sym_search(int &i, int &j, char*a,char &sym_f,char &sym_s) {
	for (; a[i + j] && (a[i + j] == ' ' || a[i + j] == '+' || a[i + j] == '-' || a[i + j] == '*' || a[i + j] == '/' || a[i + j] == '('); j++) {
		if (a[i + j] == '+' || a[i + j] == '-' || a[i + j] == '*' || a[i + j] == '/' || a[i + j] == '(') {
			if (!sym_f) {
				sym_f = a[i + j];
			}
			if (sym_f && a[i + j] == '(' && sym_f!='(') {
				sym_s = a[i + j];
				j++;
				break;
			}
		}
	}
}