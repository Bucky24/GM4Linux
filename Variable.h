#ifndef VARIABLEH
#define VARIABLEH

#include <string>
#include <iostream>

using namespace std;

class Engine;

class Variable {
	friend ostream& operator<<(ostream &, const Variable &);
public:
	Variable();
	Variable(int);
	Variable(string);
	Variable &operator=(int);
	Variable &operator=(string);
	Variable &operator=(const Variable &);
	Variable &operator=(const Variable *);

	Variable &operator++();
	Variable &operator++(int);
	Variable &operator--();
	Variable &operator--(int);

	Variable operator+(const Variable &);
	Variable operator+(const int);
	Variable operator+(const string);

	Variable operator/(const Variable &);
	Variable operator/(const int);

	Variable &operator+=(const Variable &);
	Variable &operator+=(const int);
	Variable &operator+=(const string);

	//void operator/=(const Variable &);
	//void operator/=(const int);

	Variable &operator[](int);

	friend bool operator<(const Variable &, int);
	friend bool operator<(const Variable &, const Variable &);

	//friend bool operator>=(const Variable &, int);
	//friend bool operator>=(const Variable &, const Variable &);

	//friend bool operator<=(const Variable &, int);
	//friend bool operator<=(const Variable &, const Variable &);

	operator float() {return (float)idata;}
	operator string() {return sdata;}
	//operator int() {return idata;}

	friend bool operator==(const Variable &, string);
	friend bool operator==(const Variable &, int);
	friend bool operator==(const Variable &, const Variable &);

	friend bool operator!=(const Variable &, string);
	friend bool operator!=(const Variable &, int);
	friend bool operator!=(const Variable &, const Variable &);

	string getS();
	int getI();
	int getType() {return type;}
private:
	int type; // 1=int, 2=string
	string sdata;
	int idata;
	bool isArray;
};

#endif
