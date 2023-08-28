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
		// ���캯��
		//string()
		//	:_str(new char[1]{'\0'})
		//	,_size(0)
		//	,_capacity(0)
		//{
		//	//_str = new char[1] {'\0'};
		//}
		// ���εĹ��캯��
		//string(const char* str)
		//	:_size(strlen(str))
		//	,_capacity(_size)
		//{
		//	_str = new char[_capacity + 1];
		//	strcpy(_str, str);
		//}

		// �ϲ�Ϊȫȱʡ�Ĺ��캯��(C�����пմ�Ĭ�ϴ���'\0')
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			// ���ռ�ʱ��һ��һ�����������'\0'
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		// �������죨�����
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
			// ���ù��캯��
			string tmp(s._str);
			swap(tmp);
		}
		// ���س���
		size_t size() const
		{
			return _size;
		}
		// ��������
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

		// ������
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

		// ��ǰ���ռ�/����
		void reserve(size_t n = 0)
		{
			// ����n�����������������
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				// ��ԭ���ݿ������¿ռ���
				strcpy(tmp, _str);
				// �ͷ�ԭ�ռ�
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
				// reserve��������ռ��Ƿ����
				reserve(n);
				while (_size < n)
				{
					_str[_size++] = c;
				}
				_str[_size] = '\0';
			}
		}

		// β��
		void push_back(char c)
		{
			// �������
			if (_size == _capacity)
			{
				// ����д�����ı���capacity��ֵ������reserve�������ѭ����
				// Ҳ�Ͳ����¿��ٿռ䣨���Ǹ�������
				/*_capacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(_capacity);*/
				// ���ݶ���
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size++] = c;
			// ����'\0'
			_str[_size] = '\0';
		}

		void append(const char* str)
		{
			// ����׷���ַ����ĳ���
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcat(_str, str);
			_size += len;
		}

		// ��posλ�ò���һ���ַ�
		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			// �ж��Ƿ���Ҫ����
			if (_size == _capacity)
			{
				// ���ݶ���
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			// ����Ԫ��
			_str[pos] = ch;
			++_size;
		}
		// ��posλ�ò���һ���ַ���
		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			// �ж��Ƿ���Ҫ����
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
			// �����ַ���
			strncpy(_str + pos, str, len);
			_size += len;
		}

		// ��posλ�ÿ�ʼɾ��len���ַ�
		void erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			size_t end = pos + len;
			size_t begin = pos;
			// ���ɾ�����ַ����ȳ������һ���ַ�
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
		// ����posλ��ĳ���ַ���Ĭ�ϴ���λ�ÿ�ʼ��
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
			// û���ҵ�
			return npos;
		}
		// ���Ҵ�posλ�ÿ�ʼƥ���ַ�����λ��
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
		// ��posλ�ÿ�ʼȡ��npos���Ӵ�
		string substr(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			
			string s;
			size_t end = pos + len;
			// ����len
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

		// �п�
		bool empty()const
		{
			if (_str[0] == '\0')
				return true;
			return false;
		}
		// ���
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		// ��ͳд��
		//string& operator=(const string& s)
		//{
		//	// �ų��Լ����Լ���ֵ�����
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
		// �ִ�д��(����)
		//string& operator=(string& s)
		//{
		//	if (this != &s)
		//	{
		//		// ���ÿ�������
		//		string tmp = s;
		//		swap(tmp);
		//	}
		//	return *this;
		//}
		
		// �ִ�д��(����~)
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
		// �п�

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

		// ��������
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

	// �������������
	ostream& operator<<(ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}
		return out;
	}

	// ��������������
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

	// ����
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