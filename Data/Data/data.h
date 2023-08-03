#pragma once

#include<iostream>

using namespace std;

class Date
{
public:
	// 全缺省构造函数
	Date(int year = 1900, int month = 1, int day = 1);
	// 拷贝构造函数
	// d2(d1)
	Date(const Date& d);
	// 打印
	void PrintDate();
	// 获取某年某月的天数
	int GetMonthDay(int year, int month);
	// 日期+=天数
	Date& operator+=(int day);
	// 日期+天数
	Date operator+(int day);
	// 日期-=天数
	Date& operator-=(int day);
	// 日期-天数
	Date operator-(int day);
	// 前置++
	Date& operator++();
	// 后置++
	Date operator++(int);
	// 前置--
	Date& operator--();
	// 后置--
	Date operator--(int);
	// 赋值运算符重载
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);
	// 运算符重载>
	bool operator>(const Date& d);
	// 运算符重载<=
	bool operator<=(const Date& d);
	// 运算符重载>=
	bool operator>=(const Date& d);
	// 运算符重载<
	bool operator<(const Date& d);
	// 运算符重载==
	bool operator==(const Date& d);
	// 运算符重载!=
	bool operator!=(const Date& d);
	// 运算符重载日期-日期
	int operator-(const Date& d);
	// 析构函数(日期类不用写)
	// ~Date();

private:
	int _year;
	int _month;
	int _day;
};

