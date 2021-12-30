#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
struct HocVien
{
	int id{};
	string firstName;
	string lastName;
	int birdDay[3]{};// nn/tt/nnnn
	string idClass{};
	double point{};

	HocVien* link{};
};
struct Class
{
	string id{};
	string name;
	string timeTable[3][7]{};
	int fee{};
	int SLHV{};
	HocVien* first{};

	Class* link{};
};
//- Ham xu ly HocVien -//
void initHV(HocVien*& first)
{
	first = NULL;
}




HocVien* createHV()
{
	HocVien* p;
	p = new HocVien;
	p->id = NULL;
	p->firstName = "";
	p->lastName = "";
	for (int i = 0; i < 3; i++)
		p->birdDay[i] = NULL;
	p->point = NULL;
	p->idClass = "";
	p->link = NULL;
	return p;
}
HocVien* addFirstHV(HocVien*& First, HocVien*& add) // canoc
{
	if (First == NULL)
	{
		First = add;
	}
	else
	{
		add->link = First;
		First = add;
	}
	return First;
}
void tranferHV(HocVien*& a, HocVien*& b) //- Gan HV b cho HV a
{
	a->id = b->id;
	a->firstName = b->firstName;
	a->lastName = b->lastName;
	a->idClass = b->idClass;
	a->point = b->point;
	for (int i = 0; i < 3; i++)
		a->birdDay[i] = b->birdDay[i];
}
void swapHV(HocVien*& a, HocVien*& b) //- Hoan doi gia tri thanh phan hoc vien
{
	HocVien* c = createHV();
	tranferHV(c, a);
	tranferHV(a, b);
	tranferHV(b, c);
}
//- Ham xu ly Class -//
void initClass(Class*& first)
{
	first = NULL;
}
Class* createClass()
{
	Class* p;
	p = new Class;
	p->id = "";
	p->name = "";
	p->SLHV = 0;
	p->first = NULL;
	p->fee = NULL;
	p->link = NULL;
	return p;
}
Class* addFirstClass(Class*& First, Class*& add)
{
	if (First == NULL)
	{
		First = add;
	}
	else
	{
		add->link = First;
		First = add;
	}
	return First;
}
void tranferClass(Class*& a, Class*& b) //- Gan class b cho class a
{
	a->id = b->id;
	a->name = b->name;
	a->fee = b->fee;
	a->SLHV = b->SLHV;
	a->first = b->first;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 16; j++)
			a->timeTable[i][j] = b->timeTable[i][j];
}
void swapClass(Class*& a, Class*& b) //- Hoan doi cac gia tri thanh phan class
{
	Class* c = createClass();
	tranferClass(c, a);
	tranferClass(a, b);
	tranferClass(b, c);
}
//- doc file -//
void inputClassFromFile(Class*& First)
{
	ifstream readFile;
	readFile.open("lophoc.txt", ios::in);
	if (readFile.is_open())
	{
		while (readFile.eof() == false)
		{
			Class* p = createClass();

			getline(readFile, p->id, '#');
			getline(readFile, p->name, '#');
			readFile >> p->fee;
			readFile.ignore(1);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 7; j++)
					getline(readFile, p->timeTable[i][j], '#');
			readFile.ignore(1);
			addFirstClass(First, p);
		}
		cout << "Doc File thanh cong!!!" << endl;
	}
	else
		cout << "Khong mo duoc file lophoc.txt!!!" << endl;
	readFile.close();
}
void inputHVFromFile(HocVien*& DShv, int& SL, Class*& firstclass)
{
	ifstream readFile;
	readFile.open("hocvien.txt", ios::in);
	if (readFile.is_open())
	{
		while (readFile.eof() == false)
		{
			HocVien* p = createHV();
			getline(readFile, p->idClass, '#');
			readFile >> p->id;
			readFile.ignore(1);
			getline(readFile, p->firstName, '#');
			getline(readFile, p->lastName, '#');
			readFile >> p->birdDay[0];
			readFile.ignore(1);
			readFile >> p->birdDay[1];
			readFile.ignore(1);
			readFile >> p->birdDay[2];
			readFile.ignore(1);
			readFile >> p->point;
			readFile.ignore(1);
			addFirstHV(DShv, p);
			SL++;
			Class* t;
			t = firstclass;
			while (t->id != p->idClass)
			{
				t = t->link;
			}
			if (t != NULL)
			{
				addFirstHV(t->first, p);
				t->SLHV++;
			}
		}
		cout << "Doc File thanh cong!!!" << endl;
	}
	else
		cout << "Mo file khong thanh cong!!!" << endl;
	readFile.close();
}
//-in ra console-//
void outputListClass(Class* first)
{
	if (first == NULL)
	{
		cout << "Class chua co du lieu!" << endl;
		return;
	}
	int i = 1;
	Class* p;
	p = first;
	cout << setw(12) << "STT" << setw(10) << "Ma Lop" << setw(25) << "Ten Lop" << setw(35) << "So Luong Hoc Vien" << setw(20) << "Hoc Phi" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	while (p != NULL)
	{
		cout << setw(10) << i++ << "|" << setw(10) << p->id << setw(30) << p->name << setw(23) << p->SLHV << setw(28) << p->fee << endl;
		p = p->link;
	}
}
void outputListHV(HocVien* first)
{
	if (first == NULL)
	{
		cout << "Chua co danh sach!!!" << endl;
		return;
	}
	int i = 1;
	HocVien* p;
	p = first;
	cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	while (p != NULL)
	{
		cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birdDay[0] << "/" << setw(2) << p->birdDay[1] << "/" << setw(4) << p->birdDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
		p = p->link;
	}
}
//-sap xep- heapsort//
HocVien* getAddressHV(HocVien* first, int i) //- xuat dia chi tai vi tri i
{
	HocVien* p;
	p = first;
	for (int j = 0; j < i; j++)
		p = p->link;
	return p;
}
void shift(HocVien*& first, HocVien* a[], int point[])
{
}
void HeapSortHV(HocVien*& first, int SLHV)
{
	if (first == NULL)
		return;
	//- anh xa point vao danh sach dac-//
	int* point = new int[SLHV];
	HocVien* p;
	p = first;
	for (int i = 0; i < SLHV; i++)
	{
		point[i] = p->point;
		p = p->link;
	}
}

