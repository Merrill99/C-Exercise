#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace minnow
{
	template<typename T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		// 构造函数
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{}

		// 容量
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		//返回数据长度
		size_t size() const
		{
			return _finish - _start;
		}

		// 迭代器
		iterator begin()
		{
			return _start;
		}

		const_iterator begin() const
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator end() const
		{
			return _finish;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				// 记录原始数据长度
				size_t sz = size();
				T* tmp = new T[n];
				// 当_start不为空时，拷贝数据到新空间
				if (_start)
				{
					// 存在深拷贝中的浅拷贝问题
					//memcpy(tmp, _start, sizeof(T) * size());
					for (int i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];
					}
					// 释放旧空间
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				while (n != size())
				{
					pop_back();
				}
			}
			else
			{
				// reserve可以检测n是否大于当前vector的容量
				reserve(n);

				// 插入数据
				while (size() < n)
				{
					push_back(val);
				}
			}
		}

		void push_back(const T& val)
		{
			// 检查容量是否已满
			//if (size() == capacity())
			/*if (_finish == _end_of_storage)
			{
				size_t cp = capacity() == 0 ? 4 : capacity() * 2;
				reserve(cp);
			}
			*_finish = val;
			++_finish;*/

			insert(end(), val);
		}

		void pop_back()
		{
			assert(_start != _finish);
			--_finish;
		}

		// 在pos位置之前插入一个元素
		void insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			
			if (_finish == _end_of_storage)
			{
				// 记录pos的相对位置
				size_t sz = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				//更新pos
				pos = _start + sz;
			}
			
			iterator last = _finish;
			while (last > pos)
			{
				*(last) = *(last - 1);
				--last;
			}
			//_start[pos - _start] = val;
			*pos = val;
			++_finish;
		}

		// 删除pos位置前的元素
		T earse(iterator pos)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			// 记录pos下一个位置的元素
			T tmp = *(pos + 1);
			iterator last = pos + 1;

			while (last < _finish)
			{
				*(last - 1) = *(last);
				++last;
			}
			--_finish;

			return tmp;
		}

		bool empty() const
		{
			return _start == _finish;
		}

		T& operator[](size_t n)
		{
			return *(_start + n);
		}
		const T& operator[](size_t n) const
		{
			return *(_start + n);
		}

		// 析构函数
		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};

	void vector_test1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		//v.push_back(4);
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}

	void vector_test2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
		cout << endl;
		v.insert(v.begin() + 2, 30);
		v.insert(v.begin(), 10);
		v.insert(v.end() - 1, 40);
		for (auto vec : v)
		{
			cout << vec << " ";
		}
		cout << endl;
	}

	void vector_test3()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
	
		for (auto vec : v)
		{
			cout << vec << " ";
		}
		cout << endl;
		v.pop_back();
		v.pop_back();
		v.pop_back();
		v.pop_back();
		for (auto vec : v)
		{
			cout << vec << " ";
		}
		cout << endl;
	}

	void vector_test4()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		v.resize(10, 10);
		for (auto vec : v)
		{
			cout << vec << " ";
		}
		cout << endl;

		v.earse(v.begin() + 2);

		for (auto vec : v)
		{
			cout << vec << " ";
		}
		cout << endl;
	}
}
