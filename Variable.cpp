#include "Variable.h"

Variable::Variable() {
	sdata = "";
	idata = 0;
	type = 0;
}

Variable &Variable::operator=(int data) {
	type = 1;
	idata = data;
	return *this;
}

Variable &Variable::operator=(string data) {
	type = 2;
	sdata = data;
	return *this;
}

Variable &Variable::operator=(const Variable &other) {
	type = other.type;
	idata = other.idata;
	sdata = other.sdata;
	return *this;
}

Variable &Variable::operator++() {
	if (type == 1) {
		idata ++;
	}
	return *this;
}

Variable &Variable::operator++(int unused) {
	if (type == 1) {
		idata ++;
	}
	return *this;
}

bool operator<(const Variable &var1, int data) {
	if (var1.type == 1) {
		if (var1.idata < data) {
			return true;
		}
	}
	return false;
}

bool operator<(const Variable &var1, const Variable &var2) {
	if (var1.type == 1 && var2.type == 1) {
		if (var1.idata < var2.idata) {
			return true;
		}
	}
	return false;
}

ostream& operator<<(ostream &output, const Variable &var) {
	if (var.type == 1) {
		output << var.idata;
	} else if (var.type == 2) {
		output << var.sdata;
	}
	return output;
}
