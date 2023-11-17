#pragma once
int ctoi(char* a);
double ctod(char* a);
double pars(char* a, double first = 0, bool switc = 0);
double brackets(char* a, double num_f);
int error(char* a);
void sym_search(int &i, int &j, char* a, char &sym_f, char &sym_s);