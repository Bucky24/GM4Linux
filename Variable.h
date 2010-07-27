#ifndef VARIABLEH
#define VARIABLEH

#include <string>
#include <iostream>

using namespace std;

class Variable {
	friend ostream& operator<<(ostream &, const Variable &);
public:
	Variable();
	Variable &operator=(int);
	Variable &operator=(string);
	Variable &operator=(const Variable &);
	Variable &operator++();
	Variable &operator++(int);
	Variable operator+(const Variable &);
	Variable operator+(const int);
	Variable operator+(const string);
	friend bool operator<(const Variable &, int);
	friend bool operator<(const Variable &, const Variable &);
	operator float() {return (float)idata;}
	operator string() {return sdata;}
private:
	int type; // 1=int, 2=string
	string sdata;
	int idata;
};

#endif
