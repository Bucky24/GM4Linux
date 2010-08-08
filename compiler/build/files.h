#ifndef filesH
#define filesH
#include <map>
#include <string>
using namespace std;
extern map<string,string *> files;
extern string common_h;
extern string Variable_h;
extern string Font_h;
extern string Image_h;
extern string Font_cpp;
extern string Engine_cpp;
extern string common_cpp;
extern string Room_h;
extern string Makefile;
extern string Objects_h;
extern string Variable_cpp;
extern string Room_cpp;
extern string Object_h;
extern string ObjectType_cpp;
extern string Image_cpp;
extern string Rooms_h;
extern string main_cpp;
extern string Object_cpp;
extern string ObjectType_h;
extern string Engine_h;
void initFiles();
#endif
