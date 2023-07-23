#define _CRT_SECURE_NO_WARNINGS 1

#include"data.h"

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
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
	if (2 == month && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}
	return day[month];
}
	
Date& Date::operator+=(int day)
{
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
	_day -= day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day += GetMonthDay(_year, _month);
		--_month;
		if (_month < 1)
		{
			_month = 12;
			--_year;
		}
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
	_year = d._year;
	_month = d._month;
	_day = d._day;
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

bool Date::operator<(const Date& d)
{
	if (_year < d._year)
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
	}
}

bool Date::operator>=(const Date& d)
{
	return !operator<(d);
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

int main()
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