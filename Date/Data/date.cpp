#define _CRT_SECURE_NO_WARNINGS 1

#include"date.h"

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	
	// 检测日期是否合法
	if (month < 1 || month > 12 || (day > GetMonthDay(year, month)))
	{
		cout << "日期非法" << endl;
	}
}

Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

void Date::PrintDate()
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

int Date::GetMonthDay(int year, int month)
{
	int day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	// 闰年的2月为29天
	if ((2 == month) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}
	return day[month];
}
	
Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		*this -= (-day);
		return *this;
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;
		if (_month > 12)
		{
			_month = 1;
			++_year;
		}
	}
	return *this;
}

Date Date::operator+(int day)
{
	// +不改变本身的值
	Date tmp = *this;
	tmp += day;
	return tmp;
}

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		*this += (-day);
		return *this;
	}
	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month < 1)
		{
			_month = 12;
			--_year;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

Date& Date::operator++()
{
	// 先++后使用
	*this += 1;
	return *this;
}

Date Date::operator++(int)
{
	// 先使用后++
	Date tmp = *this;
	*this += 1;
	return tmp;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

Date& Date::operator=(const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

bool Date::operator>(const Date& d)
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year && _month > d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day > d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::operator<=(const Date& d)
{
	return !operator>(d);
}

bool Date::operator>=(const Date& d)
{
	return (*this > d) || (*this == d);
}

bool Date::operator<(const Date& d)
{
	/*if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year && _month < d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day < d._day)
	{
		return true;
	}
	else
	{
		return false;
	}*/

	return !(*this >= d);
}

bool Date::operator==(const Date& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::operator!=(const Date& d)
{
	return !operator==(d);
}

int Date::operator-(const Date& d)
{
	Date max = *this;
	Date min = d;
	int day = 0;
	int flag = 1;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	while (max != min)
	{
		++min;
		++day;
	}
	return day * flag;
}