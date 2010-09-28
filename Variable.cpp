#include "Variable.h"
#include "Engine.h"

Variable::Variable() {
	sdata = "";
	idata = 0;
	/* default to int */
	type = 1;
	isArray = false;
}

Variable::Variable(int d) {
	sdata = "";
	idata = d;
	type = 1;
	isArray = false;
}

Variable::Variable(string d) {
	sdata = d;
	idata = 0;
	type = 2;
	isArray = false;
}

Variable &Variable::operator=(int data) {
	type = 1;
	idata = data;
	isArray = false;
	return *this;
}

Variable &Variable::operator=(string data) {
	type = 2;
	sdata = data;
	isArray = false;
	return *this;
}

Variable &Variable::operator=(const Variable &other) {
	type = other.type;
	idata = other.idata;
	sdata = other.sdata;
	isArray = other.isArray;
	return *this;
}

Variable &Variable::operator=(const Variable *other) {
	type = other->type;
	idata = other->idata;
	sdata = other->sdata;
	isArray = other->isArray;
	return *this;
}

Variable &Variable::operator++() {
	if (type == 1) {
		idata ++;
	}
	isArray = false;
	return *this;
}

Variable &Variable::operator++(int unused) {
	if (type == 1) {
		idata ++;
	}
	isArray = false;
	return *this;
}

Variable Variable::operator+(const Variable &var2) {
	Variable ret = *(new Variable());
	if (type == var2.type) {
		ret.type = type;
	}
	ret.idata = idata+var2.idata;
	ret.sdata = sdata+var2.sdata;
	ret.isArray = false;
	return ret;
}

Variable Variable::operator+(const int data) {
	Variable ret = *(new Variable());
	if (type == 1) {
		ret.type = 1;
		ret.idata = idata+data;
	}
	ret.isArray = false;
	return ret;
}

Variable Variable::operator+(const string data) {
	Variable ret = *(new Variable());
	if (type == 2) {
		ret.type = 2;
		ret.sdata = sdata+data;
	}
	ret.isArray = false;
	return ret;
}

Variable Variable::operator/(const Variable &data) {
	Variable ret = *(new Variable());
	if (type == 1 and data.type == 1) {
		ret.type = 1;
		ret.idata = idata/data.idata;
	}
	ret.isArray = false;
	return ret;
}

Variable Variable::operator/(const int data) {
	Variable ret = *(new Variable());
	if (type == 1) {
		ret.type = 1;
		ret.idata = idata/data;
	}
	ret.isArray = false;
	return ret;
}

void Variable::operator+=(const Variable &var2) {
	if (type == var2.type) {
		if (type == 1) {
			idata = idata+var2.idata;
		} else if (type == 2) {
			sdata = sdata+var2.sdata;
		}
	}
	isArray = false;
}

void Variable::operator+=(const int data) {
	if (type == 1) {
		idata = idata+data;
	}
	isArray = false;
}

void Variable::operator+=(const string data) {
	if (type == 2) {
		sdata = sdata+data;
	}
	isArray = false;
}

/*void operator/=(const Variable &data) {
	if (type == 1 && data.type == 1) {
		idata /= data.idata;
	}
	isArray = false;
}

void operator/=(const int data) {
	if (type == 1) {
		idata /= data;
	}
	isArray = false;
}*/

Variable &Variable::operator[](int index) {
	if (type == 1) {
		map<int, Variable *> *vec;
		if ((unsigned int)idata < Engine::vecList->size() && idata >= 0 && isArray) {
			vec = Engine::vecList->at(idata);
		} else {
			vec = new map<int, Variable *>();
			Engine::vecList->push_back(vec);
			idata = Engine::vecList->size()-1;
			isArray = true;
			cout << "new vector " << idata << endl;
		}
		if (vec->find(index) != vec->end()) {
			return *(vec->find(index)->second);
		} else {
			Variable *var = new Variable(0);
			vec->insert(vec->begin(),pair<int,Variable*>(index,var));
			return *(var);
		}
	}
	return *(new Variable(-4));
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

/*bool operator>=(const Variable &var1, int data) {
	if (var1.type == 1) {
		if (var1.idata >= data) {
			return true;
		}
	}
	return false;
}

bool operator>=(const Variable &var1, const Variable &var2) {
	if (var1.type == 1 && var2.type == 1) {
		if (var1.idata >= var2.idata) {
			return true;
		}
	}
	return false;
}

bool operator<=(const Variable &var1, int data) {
	if (var1.type == 1) {
		if (var1.idata <= data) {
			return true;
		}
	}
	return false;
}

bool operator<=(const Variable &var1, const Variable &var2) {
	if (var1.type == 1 && var2.type == 1) {
		if (var1.idata <= var2.idata) {
			return true;
		}
	}
	return false;
}*/

ostream& operator<<(ostream &output, const Variable &var) {
	if (var.isArray) {
		output << "Array=>";
	}
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

string Variable::getS() {
	if (type == 2) {
		return sdata;
	} else {
		return "";
	}
}

int Variable::getI() {
	if (type == 1) {
		return idata;
	} else {
		return 0;
	}
}
