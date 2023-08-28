#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

namespace minnow
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		// 构造函数
		//string()
		//	:_str(new char[1]{'\0'})
		//	,_size(0)
		//	,_capacity(0)
		//{
		//	//_str = new char[1] {'\0'};
		//}
		// 带参的构造函数
		//string(const char* str)
		//	:_size(strlen(str))
		//	,_capacity(_size)
		//{
		//	_str = new char[_capacity + 1];
		//	strcpy(_str, str);
		//}

		// 合并为全缺省的构造函数(C语言中空串默认带个'\0')
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			// 开空间时多一开一个，用来存放'\0'
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		// 拷贝构造（深拷贝）
		/*string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			_str = new char[s._capacity + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}*/
		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			// 调用构造函数
			string tmp(s._str);
			swap(tmp);
		}
		// 返回长度
		size_t size() const
		{
			return _size;
		}
		// 返回容量
		size_t capacity() const
		{
			return _capacity;
		}

		const char* c_str() const
		{
			return _str;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);

			return _str[pos];
		}

		const char& operator[](size_t pos) const
		{
			assert(pos < _size);

			return _str[pos];
		}

		// 迭代器
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}

		// 提前开空间/扩容
		void reserve(size_t n = 0)
		{
			// 给的n比容量大，则进行扩容
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				// 将原数据拷贝到新空间中
				strcpy(tmp, _str);
				// 释放原空间
				delete[] _str;
				_str = tmp;

				_capacity = n;
			}
		}
		void resize(size_t n, char c = '\0')
		{
			if (n <= _size)
			{
				_str[n] = '\0';
			}
			else
			{
				// reserve会帮助检查空间是否充足
				reserve(n);
				while (_size < n)
				{
					_str[_size++] = c;
				}
				_str[_size] = '\0';
			}
		}

		// 尾插
		void push_back(char c)
		{
			// 检测容量
			if (_size == _capacity)
			{
				// 错误写法，改变了capacity的值，导致reserve不会进入循环，
				// 也就不会新开辟空间（我是个蠢蛋）
				/*_capacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(_capacity);*/
				// 扩容二倍
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size++] = c;
			// 放入'\0'
			_str[_size] = '\0';
		}

		void append(const char* str)
		{
			// 计算追加字符串的长度
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcat(_str, str);
			_size += len;
		}

		// 在pos位置插入一个字符
		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			// 判断是否需要扩容
			if (_size == _capacity)
			{
				// 扩容二倍
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			// 放入元素
			_str[pos] = ch;
			++_size;
		}
		// 在pos位置插入一个字符串
		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			// 判断是否需要扩容
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size + len;
			while (end > pos)
			{
				_str[end] = _str[end - len];
				--end;
			}
			// 放入字符串
			strncpy(_str + pos, str, len);
			_size += len;
		}

		// 从pos位置开始删除len个字符
		void erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			size_t end = pos + len;
			size_t begin = pos;
			// 如果删除的字符长度超过最后一个字符
			if (end > _size)
			{
				end = _size;
				len = end - pos;
			}
			while (end <= _size)
			{
				_str[begin] = _str[end];
				++end;
				++begin;
			}
			_size -= len;
		}
		/*void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);

			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t begin = pos + len;
				while (begin <= _size)
				{
					_str[begin - len] = _str[begin];
					++begin;
				}
				_size -= len;
			}
		}*/
		// 查找pos位置某个字符，默认从零位置开始找
		size_t find(char c, size_t pos = 0) const
		{
			assert(pos < _size);
			for (; pos < _size; ++pos)
			{
				if (_str[pos] == c)
				{
					return pos;
				}
			}
			// 没有找到
			return npos;
		}
		// 查找从pos位置开始匹配字符串的位置
		size_t find(const char* str, size_t pos = 0) const
		{
			assert(pos < _size);
			
			char* ret = strstr(_str + pos, str);
			if (ret)
			{
				return ret - _str;
			}
			else
			{
				return npos;
			}
		}
		// 从pos位置开始取出npos个子串
		string substr(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			
			string s;
			size_t end = pos + len;
			// 修正len
			if (end >= _size || len == npos)
			{
				end = _size;
				len = end - pos;
			}
			reserve(len);
			for (size_t i = pos; i < end; ++i)
			{
				s += _str[i];
			}
			return s;
		}

		// 判空
		bool empty()const
		{
			if (_str[0] == '\0')
				return true;
			return false;
		}
		// 清空
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		// 传统写法
		//string& operator=(const string& s)
		//{
		//	// 排除自己给自己赋值的情况
		//	if (*this != s)
		//	{
		//		char* tmp = new char[s._capacity + 1];
		//		strcpy(tmp, s._str);
		//		delete[] _str;
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}
		
		void swap(string& str)
		{
			std::swap(_str, str._str);
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}
		// 现代写法(初代)
		//string& operator=(string& s)
		//{
		//	if (this != &s)
		//	{
		//		// 调用拷贝构造
		//		string tmp = s;
		//		swap(tmp);
		//	}
		//	return *this;
		//}
		
		// 现代写法(惊奇~)
		string& operator=(string tmp)
		{
			swap(tmp);

			return *this;
		}
		string& operator+=(string& s)
		{
			append(s._str);
			return *this;
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		// 判空

		bool operator>(const string& s)
		{
			return strcmp(_str, s._str);
		}

		bool operator==(const string& s)
		{
			int ret = strcmp(_str, s._str);
			if (ret == 0)
				return true;
			return false;
		}

		bool operator!=(const string& s)
		{
			return !(*this == s);
		}

		bool operator<=(const string& s)
		{
			return !(*this > s);
		}

		bool operator>=(const string& s)
		{
			return *this > s || *this == s;
		}

		bool operator<(const string& s)
		{
			return !(*this >= s);
		}

		// 析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	public:
		const static size_t npos;
	};
	const size_t string::npos = -1;

	// 输出流函数重载
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	// 输入流函数重载
	/*istream& operator>>(istream& in, string& s)
	{
		s.clear();

		char ch;
		ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}

		return in;
	}*/
	istream& operator>>(istream& in, string& s)
	{
		s.clear();

		char c;
		c = in.get();
		char buff[129] = { 0 };
		size_t i = 0;
		
		while (c != ' ' && c != '\n')
		{
			if (i == 129)
			{
				buff[128] = '\0';
				s += buff;
				i = 0;
			}
			buff[i++] = c;
			c = in.get();
		}
		buff[i] = '\0';
		s += buff;

		return in;
	}

	// 测试
	void test_string1()
	{
		string s1("hello world");
		string::iterator itb = s1.begin();
		while (itb != s1.end())
		{
			cout << *itb << " ";
			++itb;
		}
		cout << endl;

		for (int i = 0; i < s1.size(); ++i)
		{
			cout << s1[i] << " ";
		}
		cout << endl;
		for (auto ch : s1)
		{
			cout << ch << " ";
		}
		cout << endl;
	}

	void test_string2()
	{
		string s1("hello world");
		string s2;
		s1.push_back('x');
		s1.push_back('x');
		s1.push_back('x');
		cout << s1.c_str() << endl;
		s2.push_back('x');
		s2.push_back('x');
		s2.push_back('x');
		cout << s2.c_str() << endl;

		string s3("I");
		s3.append(" Love You!");
		cout << s3.c_str() << endl;

		string s4("xxx");
		s4 += "666";
		cout << s4.c_str() << endl;
	}

	void test_string3()
	{
		string s3("I");
		s3.append(" Love You!");
		cout << s3.c_str() << endl;

		string s4("xxx");
		s4 += "666";
		cout << s4.c_str() << endl;
		s4 += '0';
		cout << s4.c_str() << endl;

		cout << (s3 > s4) << endl;
		cout << (s3 == s4) << endl;
		cout << (s3 >= s4) << endl;
		cout << (s3 <= s4) << endl;
		cout << (s3 < s4) << endl;
	}

	void test_string4()
	{
		string s1("helloworld");
		string s2(s1);
		cout << s1.empty() << endl;
		cout << s2.empty() << endl;
		
		s1.insert(5, 'x');
		s1.resize(5);
		cout << s1.c_str() << endl;
		s2.resize(20, '+');
		cout << s2.c_str() << endl;
	}

	void test_string5()
	{
		string s1("hello world");
		string s2(s1);

		s1.erase(5, 3);
		cout << s1.c_str() << endl;
		s1.erase(5, 1);
		cout << s1.c_str() << endl;
		cout << s1.find('o') << endl;
		cout << s1.find("ld", 1) << endl;
	}

	void test_string6()
	{
		string s1("hello world");
		string s2(s1);
		string s3;

		cout << s1 << endl;

		cout << s2 << endl;

		s3 = s2;

		cout << s3 << endl;
	}

	void test_string7()
	{
		string s1("hello world");
		string s2(s1);
		string s3;

		cout << s2 << endl;

		cin >> s3;
		cout << s3 << endl;
		cout << s3.size() << endl;
		cout << s3.capacity() << endl;
	}
}