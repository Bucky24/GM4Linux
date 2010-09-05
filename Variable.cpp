#include "Variable.h"

Variable::Variable() {
	sdata = "";
	idata = 0;
	/* default to int */
	type = 1;
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

Variable Variable::operator+(const Variable &var2) {
	Variable ret = *(new Variable());
	if (type == var2.type) {
		ret.type = type;
	}
	ret.idata = idata+var2.idata;
	ret.sdata = sdata+var2.sdata;
	return ret;
}

Variable Variable::operator+(const int data) {
	Variable ret = *(new Variable());
	if (type == 1) {
		ret.type = 1;
		ret.idata = idata+data;
	}
	return ret;
}

Variable Variable::operator+(const string data) {
	Variable ret = *(new Variable());
	if (type == 2) {
		ret.type = 2;
		ret.sdata = sdata+data;
	}
	return ret;
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
	} else {
		output << "(UNDEF)";
	}
	return output;
}

bool operator==(const Variable &var1, string data) {
	if (var1.type == 2) {
		if (var1.sdata == data) {
			return true;
		}
	}
	return false;
}

bool operator==(const Variable &var1, int data) {
	if (var1.type == 1) {
		if (var1.idata == data) {
			return true;
		}
	}
	return false;
}

bool operator==(const Variable &var1, const Variable &var2) {
	if (var1.type == 1 && var2.type == 1) {
		if (var1.idata == var2.idata) {
			return true;
		}
	} else if (var1.type == 2 && var2.type == 2) {
		if (var1.sdata == var2.sdata) {
			return true;
		}
	}
	return false;
}

bool operator!=(const Variable &var1, string data) {
	return !(var1 == data);
}

bool operator!=(const Variable &var1, int data) {
	return !(var1 == data);
}

bool operator!=(const Variable &var1, const Variable &var2) {
	return !(var1 == var2);
}
