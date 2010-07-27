#ifndef filesH
#define filesH
#include <map>
#include <string>
using namespace std;
extern map<string,string *> files;
extern string main_cpp;
extern string common_h;
extern string Engine_cpp;
extern string Objects_h;
extern string Room_cpp;
extern string Image_h;
extern string Makefile;
extern string ObjectType_h;
extern string Rooms_h;
extern string Engine_h;
extern string Image_cpp;
extern string Object_cpp;
extern string Object_h;
extern string ObjectType_cpp;
extern string Room_h;
extern string common_cpp;
void initFiles();
#endif