#pragma once

#include<iostream>

using namespace std;

class Date
{
public:
	// ȫȱʡ���캯��
	Date(int year = 1900, int month = 1, int day = 1);
	// �������캯��
	// d2(d1)
	Date(const Date& d);
	// ��ӡ
	void PrintDate();
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month);
	// ����+=����
	Date& operator+=(int day);
	// ����+����
	Date operator+(int day);
	// ����-=����
	Date& operator-=(int day);
	// ����-����
	Date operator-(int day);
	// ǰ��++
	Date& operator++();
	// ����++
	Date operator++(int);
	// ǰ��--
	Date& operator--();
	// ����--
	Date operator--(int);
	// ��ֵ���������
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);
	// ���������>
	bool operator>(const Date& d);
	// ���������<=
	bool operator<=(const Date& d);
	// ���������>=
	bool operator>=(const Date& d);
	// ���������<
	bool operator<(const Date& d);
	// ���������==
	bool operator==(const Date& d);
	// ���������!=
	bool operator!=(const Date& d);
	// �������������-����
	int operator-(const Date& d);
	// ��������(�����಻��д)
	// ~Date();

private:
	int _year;
	int _month;
	int _day;
};

