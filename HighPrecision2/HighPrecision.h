#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned digit;

namespace my
{
	typedef enum
	{
		POSITIVE = 1,
		NEGATIVE = -1,
		ZERO = 0
	} POSNEG;

	class High
	{
	private:
		string s;
		POSNEG posneg;
	public:
		//构造函数
		High() :s(""), posneg(ZERO) {}
		High(const string& _s);
		High(const string& _s, POSNEG _posneg);
		High(ll num);
		High(const High& x) :s(x.s), posneg(x.posneg) {}

		friend ostream& operator<<(ostream& os, const High& x);

		POSNEG getPosneg() const;
		ull length() const;
		bool is0() const;

		static POSNEG opposite(POSNEG _posneg);
		static High abs(const High& x);
		static ll abs(ll x);
		static High maxH(const High& x, const High& y);
		static High minH(const High& x, const High& y);
		static bool isSamePosneg(const High& x, const High& y);
		static void swap(High& x, High& y);
	private:
		static High addPos(const High& x, const High& y);
		static High subPos(const High& x, const High& y);

	public:
		void operator=(const High& x);
		void operator=(ll num);

		High operator+(const High& x) const;
		High operator-(const High& x) const;
		High operator*(const High& x) const;
		//High operator/(const High& x) const;
		High operator%(const High& x) const;

		void operator+=(const High& x);
		void operator-=(const High& x);
		void operator*=(const High& x);
		//void operator/=(const High& x);
		//void operator%=(const High& x);

		High operator+(ll num) const;
		High operator-(ll num) const;
		High operator*(ll num) const;
		//High operator/(ll num) const;
		//High operator%(ll num) const;

		void operator+=(ll num);
		void operator-=(ll num);
		void operator*=(ll num);
		//void operator/=(ll num);
		//void operator%=(ll num);

		void operator++();
		void operator--();
		void operator++(int);
		void operator--(int);

		bool operator==(const High& x) const;
		bool operator!=(const High& x) const;
		bool operator>(const High& x) const;
		bool operator<(const High& x) const;
		bool operator>=(const High& x) const;
		bool operator<=(const High& x) const;

		bool operator==(ll num) const;
		bool operator!=(ll num) const;
		bool operator>(ll num) const;
		bool operator<(ll num) const;
		bool operator>=(ll num) const;
		bool operator<=(ll num) const;

		//中间层函数
	private:
		static bool StrIsStandard(const string& _s);
	public:
		//static char ToChar()
		static digit ToNum(char c);
		static char ToChar(digit d);
		static string ToStr(vector<digit> _digs);




	};

}
