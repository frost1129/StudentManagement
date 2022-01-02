#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cmath>
using namespace std;
/*
												-------------Boi vi la code chung nen ai code gi, viet code phai de lai info cho cac thanh vien trong team thac mac--------
												-------------Sua code cua thanh vien trong nhom nho de lai info va ngay cap nhat, vd: ' Update: Nguyen 30/12/2021 '-------
																							---Thank, cung chung tay nhau qua mon!!!---
																													Nguyen.
*/
struct HocVien
{
	int id{};
	string firstName;
	string lastName;
	int birthDay[3]{};// nn/tt/nnnn
	string idClass{};
	double point{};

	HocVien* link{};
};
struct Class
{
	string id;
	string name;
	string timeTable[3][7];
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
		p->birthDay[i] = NULL;
	p->point = NULL;
	p->idClass = "";
	p->link = NULL;
	return p;
}
void addFirstHV(HocVien*& First, HocVien*& add)
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
}
void addLastHV(HocVien*& First, HocVien* add)
{
	
	if (First == NULL)
		First = add;
	else
	{
		HocVien* p = First;
		while (p->link != NULL)
		{
			p = p->link;
		}
		p->link = add;
	}
}
void tranferHV(HocVien*& a, HocVien*& b) //- Gan cac nut HV b cho HV a
{
	a->id = b->id;
	a->firstName = b->firstName;
	a->lastName = b->lastName;
	a->idClass = b->idClass;
	a->point = b->point;
	for (int i = 0; i < 3; i++)
		a->birthDay[i] = b->birthDay[i];
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

//-------code cua Nguyen----------//
void addFirstClass(Class*& First, Class*& add)
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
}
void addLastClass(Class*& First, Class* add)
{
	Class* p = First;
	if (p == NULL)
		First = add;
	else
	{
		while (p->link != NULL)
		{
			p = p->link;
		}
		p->link = add;
	}
}
void tranferClass(Class*& a, Class*& b) //- Gan class b cho class a
{
	a->id = b->id;
	a->name = b->name;
	a->fee = b->fee;
	a->SLHV = b->SLHV;
	a->first = b->first;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 7; j++)
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
void inputClassFromFile(Class*& First, int &SL)
{
	SL = 0;
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
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 3; j++)
					getline(readFile, p->timeTable[j][i], '#');
			readFile.ignore(1);
			addFirstClass(First, p);
			SL++;
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
			readFile >> p->birthDay[0];
			readFile.ignore(1);
			readFile >> p->birthDay[1];
			readFile.ignore(1);
			readFile >> p->birthDay[2];
			readFile.ignore(1);
			readFile >> p->point;
			readFile.ignore(1);
			p->point = (round(p->point * 100))/100;
			addFirstHV(DShv, p);
			SL++;
			Class* t;
			t = firstclass;
			while (t!=NULL)
			{
				if (t->id == p->idClass)
				{
					HocVien* v = createHV();
					tranferHV(v, p);
					addFirstHV(t->first, v);
					t->SLHV++;
					break;
				}
				t = t->link;
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
		cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
		p = p->link;
	}
}

//-------------------------------------------------//Sap xep HV//----------------------------------//
//-sap xep- heapsort//
HocVien* getAddressHV(HocVien* first, int i) //- xuat dia chi tai vi tri i
{
	HocVien* p;
	p = first;
	for (int j = 0; j < i; j++)
		p = p->link;
	return p;
}
void shift(HocVien*& first, int i, int n)
{
	int j = 2 * i + 1;
	if (j >= n)
		return;
	if (j + 1 < n)
	{
		HocVien* a = getAddressHV(first, j);
		HocVien* b = getAddressHV(first, j + 1);
		if (a->point > b->point)
			j++;
	}
	HocVien* c = getAddressHV(first, i);
	HocVien* d = getAddressHV(first, j);
	if (c->point > d->point)
	{
		swapHV(c, d);
		shift(first, j, n);
	}
	else
		return;
}
void HeapSortHV(HocVien*& first, int SLHV)
{
	int i = SLHV / 2 - 1;
	while (i >= 0)
	{
		shift(first, i, SLHV);
		i--;
	}
	int n = SLHV - 1;
	while (n > 0)
	{
		HocVien* a = getAddressHV(first, n);
		swapHV(first, a);
		n--;
		if (n > 0)
		{
			i = (n + 1) / 2 - 1;
			shift(first, 0, n + 1);
		}
	}
}
//-sap xep merge sort-//
HocVien* mergePointHV(HocVien* a, HocVien* b)
{
	HocVien* first;
	initHV(first);
	HocVien* p = a;
	HocVien* q = b;
	while (p != NULL && q != NULL)
	{
		if (p->point > q->point)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			p = p->link;
			addLastHV(first, t);
		}
		else
		{
			HocVien* t = createHV();
			tranferHV(t, q);
			q = q->link;
			addLastHV(first, t);
		}
	}
	while (p!=NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, p);
		addLastHV(first, e);
		p = p->link;
	}
	while (q != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, q);
		addLastHV(first, e);
		q = q->link;
	}
	return first;
}
HocVien* mergeSortPointHV(HocVien* first, int SL)
{
	if (SL == 1)
		return first;
	HocVien* p = first;
	int mid = SL / 2;
	HocVien* first_1;
	initHV(first_1);
	HocVien* first_2;
	initHV(first_2);
	for (int i = 1; i <= mid; i++)
	{
		HocVien* t = createHV();
		tranferHV(t, p);
		addLastHV(first_1, t);
		p = p->link;
	}
	while (p != NULL)
	{
		HocVien* e = createHV();
		tranferHV(e, p);
		addLastHV(first_2, e);
		p = p->link;
	}
	first_1 = mergeSortPointHV(first_1, mid);
	first_2 = mergeSortPointHV(first_2, SL - mid);
	return mergePointHV(first_1, first_2);
}
//- sap xep counting sort-//
HocVien* countingSortHV(HocVien* first)
{
	HocVien* p = first;
	HocVien** a = new HocVien*[1001];
	for (int i = 0; i <= 1000; i++)
	{
		initHV(a[i]);
	}
	while (p != NULL)
	{
		int x = int(round(p->point * 100));
		HocVien* t = createHV();
		tranferHV(t, p);
		addLastHV(a[x], t); 
		p = p->link;
	}
	HocVien* KQ;
	initHV(KQ);
	for (int i = 1000; i >= 0; i--)
	{
		if (a[i] != NULL)
			addLastHV(KQ, a[i]);
	}
	delete[]a;
	return KQ;
}

//-------------------------------------------------//Sap xep class//----------------------------------//
//- sap xep lop thu tu tang dan heapSort-//
Class* getAddressClass(Class* first, int i) //- xuat dia chi tai vi tri i
{
	Class* p;
	p = first;
	for (int j = 0; j < i; j++)
		p = p->link;
	return p;
}
void shiftIdClass(Class*& first, int i, int n)
{
	int j = 2 * i + 1;
	if (j >= n)
		return;
	if (j + 1 < n)
	{
		Class* a = getAddressClass(first, j);
		Class* b = getAddressClass(first, j + 1);
		if (a->id<b->id)
			j++;
	}
	Class* c = getAddressClass(first, i);
	Class* d = getAddressClass(first, j);
	if (c->id < d->id)
	{
		swapClass(c, d);
		shiftIdClass(first, j, n);
	}
	else
		return;
}
void HeapSortIdClass(Class*& first, int SL)
{
	int i = SL / 2 - 1;
	while (i >= 0)
	{
		shiftIdClass(first, i, SL);
		i--;
	}
	int n = SL - 1;
	while (n > 0)
	{
		Class* a = getAddressClass(first, n);
		swapClass(first, a);
		n--;
		if (n > 0)
		{
			i = (n + 1) / 2 - 1;
			shiftIdClass(first, 0, n + 1);
		}
	}
}
//- sap xep lop thu tu tang dan mergeSort-//
Class* mergeIdClass(Class* a, Class* b)
{
	Class* first;
	initClass(first);
	Class* p = a;
	Class* q = b;
	while (p != NULL && q != NULL)
	{
		if (p->id < q->id)
		{
			Class* t = createClass();
			tranferClass(t, p);
			p = p->link;
			addLastClass(first, t);
		}
		else
		{
			Class* t = createClass();
			tranferClass(t, q);
			q = q->link;
			addLastClass(first, t);
		}
	}
	while (p != NULL)
	{
		Class* e = createClass();
		tranferClass(e, p);
		addLastClass(first, e);
		p = p->link;
	}
	while (q != NULL)
	{
		Class* e = createClass();
		tranferClass(e, q);
		addLastClass(first, e);
		q = q->link;
	}
	return first;
}
Class* mergeSortIdClass(Class* first, int SL)
{
	if (SL == 1)
		return first;
	Class* p = first;
	int mid = SL / 2;
	Class* first_1;
	initClass(first_1);
	Class* first_2;
	initClass(first_2);
	for (int i = 1; i <= mid; i++)
	{
		Class* t = createClass();
		tranferClass(t, p);
		addLastClass(first_1, t);
		p = p->link;
	}
	while (p != NULL)
	{
		Class* e = createClass();
		tranferClass(e, p);
		addLastClass(first_2, e);
		p = p->link;
	}
	first_1 = mergeSortIdClass(first_1, mid);
	first_2 = mergeSortIdClass(first_2, SL - mid);
	return mergeIdClass(first_1, first_2);
}
//- sap xep lop thu tu tang dan countingSort-//
int maxlengthStr(Class* first)
{
	Class* p = first;
	int Max = (p->id).length();
	while (p != NULL)
	{
		int x = (p->id).length();
		if (Max < x)
			Max = x;
		p = p->link;
	}
	return Max;
}
int anhXaClass(string a, int Maxlength)
{
	char* e = (char *)a.c_str();
	int i = 0, KQ = 0;
	while (e[i] != '\0')
	{
		KQ += int(e[i])*pow(10,Maxlength-1-i);
		i++;
	}
	return KQ;
}
int anhXaMaxClass(Class* first)
{
	Class* p = first;
	int Maxlength = maxlengthStr(first);
	int Max = anhXaClass(p->id, Maxlength);
	while (p != NULL)
	{
		if (Max < anhXaClass(p->id, Maxlength))
			Max = anhXaClass(p->id, Maxlength);
		p = p->link;
	}
	return Max;
}
Class* CountingSortIdClass(Class* first)
{
	int MaxLengthStr = maxlengthStr(first);
	int MaxAnhXa = anhXaMaxClass(first);
	Class** c = new Class * [MaxAnhXa + 1];
	for (int i = 0; i <= MaxAnhXa; i++)
		initClass(c[i]);
	Class* p = first;
	while (p!=NULL)
	{
		int x = anhXaClass(p->id,MaxLengthStr);
		Class* t = createClass();
		tranferClass(t, p);
		addLastClass(c[x], t);
		p = p->link;
	}
	Class* KQ;
	initClass(KQ);
	for (int i = 0; i <=MaxAnhXa; i++)
	{
		if (c[i] != NULL)
			addLastClass(KQ, c[i]);
	}
	delete[]c;
	return KQ;
}


//-----Code cua Dat -------//  update: Nguyen da sua ngay 2/1/2022
//xuat hoc vien theo tung lop                               --------- dang cho sua 
void outputHocVienOfClass(Class* first)
{
	Class* p = first;
	while (p != NULL)
	{
		cout << "Ma lop: " << p->id << "\t" << "Ten Lop: " << p->name << "\t" << "So luong hoc vien: " << p->SLHV << endl;
		outputListHV(p->first);
		p = p->link;
		cout << endl;
	}
}
//-Xuat hoc vien cao diem nhat-//
double MaxPoint(HocVien* first)
{
	HocVien* p = first;
	double max = p->point;
	while (p != NULL)
	{
		if (max < p->point)
		{
			max = p->point;
		}
		p = p->link;
	}
	return max;
}
void outputHocVienMax(HocVien* first)
{
	HocVien* KQ;
	initHV(KQ);
	HocVien* p = first;
	double maxPoint = MaxPoint(first);
	while (p != NULL)
	{
		if (p->point == maxPoint)
		{
			HocVien* t = createHV();
			tranferHV(t, p);
			addFirstHV(KQ,t);
		}
		p = p->link;
	}
	outputListHV(KQ);
}
//-Xuat hoc vien hoc o lop hoc phi cao nhat-//
int MaxFee(Class* first)
{
	Class* p = first;
	double max = p->fee;
	while (p != NULL)
	{
		if (max < p->fee)
		{
			max = p->fee;
		}
		p = p->link;
	}
	return max;
}
void ouputMaxFeeHocVien(Class* firstClass)
{
	int maxFeeClass = MaxFee(firstClass);
	Class* p = firstClass;
	while (p != NULL)
	{
		if (p->fee == maxFeeClass)
		{
			cout << setw(35) << "Ten lop: " << p->name << "|| Hoc phi:" << p->fee << endl << endl;
			outputListHV(p->first);
		}
		p = p->link;
	}
}


////----Code of Thuy -------// ps: dang check
//HocVien* inputFromKeyboard(HocVien* dsHV, Class* dsLop)
//{
//	HocVien* x = createHV();
//	cout << "Nhap ma so sinh vien: ";
//	cin >> x->id;
//	if (checkMaHV(dsHV, x->id) == true)
//	{
//		cout << "Ma so sinh vien bi trung. Vui long nhap lai\n";
//		cout << "Nhap ma so sinh vien: ";
//		cin >> x->id;
//	}
//	cin.ignore();
//	cout << "Nhap ho & ten dem: ";
//	getline(cin, x->firstName);
//	cout << "Nhap ten: ";
//	getline(cin, x->lastName);
//	cout << "Nhap ngay thang nam sinh (dd/mm/yyyy): ";
//	cin >> x->birthDay[0] >> x->birthDay[1] >> x->birthDay[2];
//	cin.ignore();
//	cout << "Nhap ma lop: ";
//	getline(cin, x->idClass);
//	if (checkMaLop(dsLop, x->idClass) == false)
//	{
//		cout << "Ma lop chua ton tai, vui long kiem tra lai\n";
//		cout << "Nhap ma lop: ";
//		getline(cin, x->idClass);
//	}
//	cout << "Nhap diem trung binh: ";
//	cin >> x->point;
//	return x;
//}
//bool checkMaLop(Class* first, string ma)
//{
//	if (first == NULL)
//	{
//
//		return false;
//	}
//
//	Class* p;
//	p = first;
//	while (p != NULL)
//	{
//		if (p->id == ma)
//		{
//			return true;
//		}
//		p = p->link;
//	}
//	return false;
//}
//string getmaFromName(Class* first, string name)
//{
//	if (first == NULL)
//	{
//
//		return "";
//	}
//
//	Class* p;
//	p = first;
//	while (p != NULL)
//	{
//		if (p->name == name)
//		{
//			return p->id;
//		}
//		p = p->link;
//	}
//	return "";
//}
//bool checkMaHV(HocVien* first, int ma)
//{
//	if (first == NULL)
//	{
//		return false;
//	}
//
//	HocVien* p;
//	p = first;
//	while (p != NULL)
//	{
//		if (p->id == ma)
//		{
//			return true;
//		}
//		p = p->link;
//	}
//	return false;
//}
//void outputListHV(HocVien* first) // 
//{
//	if (first == NULL)
//	{
//		cout << "Chua co danh sach!!!" << endl;
//		return;
//	}
//	int i = 1;
//	HocVien* p;
//	p = first;
//	cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
//	cout << "----------------------------------------------------------------------------------------------------------" << endl;
//	while (p != NULL)
//	{
//		cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
//		p = p->link;
//	}
//}
//// output theo ma lop
//void outputListHVTheoMaLop(HocVien* first, string malop)
//{
//	if (first == NULL)
//	{
//		cout << "Chua co danh sach!!!" << endl;
//		return;
//	}
//	int i = 1;
//	HocVien* p;
//	p = first;
//	cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
//	cout << "----------------------------------------------------------------------------------------------------------" << endl;
//	while (p != NULL)
//	{
//		if (p->idClass == malop)
//		{
//			cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
//
//		}
//		p = p->link;
//	}
//}
//// output theo ma hoc vien
//void outputListHVTheoMaHV(HocVien* first, int maHV)
//{
//	if (first == NULL)
//	{
//		cout << "Chua co danh sach!!!" << endl;
//		return;
//	}
//	int i = 1;
//	HocVien* p;
//	p = first;
//	while (p != NULL)
//	{
//		if (p->id == maHV)
//		{
//			cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
//			cout << "----------------------------------------------------------------------------------------------------------" << endl;
//			cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
//			return;
//		}
//		p = p->link;
//	}
//	cout << "Khong tim thay\n";
//}
//// output theo nam sinh
//void outputListHVTheoNamSinh(HocVien* first, int namsinh)
//{
//	if (first == NULL)
//	{
//		cout << "Chua co danh sach!!!" << endl;
//		return;
//	}
//	int i = 1;
//	HocVien* p;
//	p = first;
//
//	while (p != NULL)
//	{
//		if (p->birthDay[2] == namsinh)
//		{
//			//cout << p->birdDay[2] << " " << namsinh << endl;
//			//system("pause");
//			if (i == 1)
//			{
//				cout << setw(12) << "STT" << setw(20) << "MSSV" << setw(20) << "Ho & ten dem" << setw(10) << "Ten" << setw(20) << "Ngay Sinh" << setw(11) << "Ma Lop" << setw(10) << "Diem" << endl;
//				cout << "----------------------------------------------------------------------------------------------------------" << endl;
//
//			}
//			cout << setw(11) << i++ << "|" << setw(20) << p->id << setw(20) << p->firstName << setw(10) << p->lastName << setw(13) << p->birthDay[0] << "/" << setw(2) << p->birthDay[1] << "/" << setw(4) << p->birthDay[2] << setw(10) << p->idClass << setw(10) << p->point << endl;
//
//		}
//		p = p->link;
//	}
//	if (i == 1)
//		cout << "Khong tim thay\n";
//}


