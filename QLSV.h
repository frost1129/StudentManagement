#include<iostream>
#include<string>
using namespace std;
struct HocVien
{
	int id;
	string firstName;
	string lastName;
	int birdDay[3]; // nn/tt/nnnn
	int idClass;
	double point;
	HocVien* link;
};
struct Class
{
	int id;
	string name;
	string timeTable[16][7];
	int fee;
	HocVien* first;
	Class* link;
};