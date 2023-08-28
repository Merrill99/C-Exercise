#define _CRT_SECURE_NO_WARNINGS 1

#include"date.h"

void DateTest1()
{
	Date d1(2023, 7, 23);
	d1.PrintDate();
	d1 += 50;
	d1.PrintDate();
	Date d2(2022, 7, 23);
	Date d3 = d2++;
	d3.PrintDate();
	d2.PrintDate();
	Date d4 = d1;
	d4.PrintDate();
	cout << (d1 > d2) << endl;
	cout << (d1 < d2) << endl;
	cout << (d1 >= d1) << endl;
	cout << (d1 <= d1) << endl;
}

void DateTest2()
{
	Date d1(2023, 7, 28);
	d1.PrintDate();
	d1 -= -2000;
	d1.PrintDate();
	Date d2(2023, 7, 28);
	d2 += -2000;
	d2.PrintDate();
	cout << (d2 - d1) << endl;
}

int main()
{
	//DateTest1();
	DateTest2();
	return 0;
}