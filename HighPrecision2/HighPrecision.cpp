#include "HighPrecision.h"

namespace my
{
	High::High(const string& _s)
	{
		if (StrIsStandard(_s))
		{
			s = _s;
			posneg = _s == "" ? ZERO : POSITIVE;
		}
		else
		{
			cout << "输入格式错误！字符串没有标准化" << endl;
			s = "";
			posneg = ZERO;
		}
	}

	High::High(const string& _s, POSNEG _posneg)
	{
		if (StrIsStandard(_s))
		{
			s = _s;
			posneg = _posneg;
		}
		else
		{
			cout << "输入格式错误！字符串没有标准化" << endl;
			s = "";
			posneg = ZERO;
		}
	}

	High::High(ll num)
	{
		s = to_string(abs(num));

		if (num > 0)
			posneg = POSITIVE;
		else if (num == 0)
			posneg = ZERO;
		else
			posneg = NEGATIVE;
	}

	//格式化输出
	ostream& operator<<(ostream& os, const High& x)
	{
		if (x.posneg == ZERO)
		{
			os << "0";
			return os;
		}

		if (x.posneg == NEGATIVE)
			os << "-";
		os << x.s;

		return os;
	}

	//正负情况
	POSNEG High::getPosneg() const
	{
		return posneg;
	}

	//长度
	ull High::length() const
	{
		return s.length();
	}

	//等于0
	bool High::is0() const
	{
		return s == "";
	}

	//相反符号
	POSNEG High::opposite(POSNEG _posneg)
	{
		if (_posneg == ZERO)
			return ZERO;
		
		return _posneg == POSITIVE ? NEGATIVE : POSITIVE;
	}

	//绝对值
	High High::abs(const High& x)
	{
		High y(x);
		if (y.posneg == NEGATIVE)
			y.posneg = POSITIVE;
		return y;
	}

	ll High::abs(ll x)
	{
		return x * (x < 0 ? -1 : 1);
	}

	//最大值
	High High::maxH(const High& x, const High& y)
	{
		return x >= y ? x : y;
	}

	//最小值
	High High::minH(const High& x, const High& y)
	{
		return x <= y ? x : y;
	}

	//两者同号
	bool High::isSamePosneg(const High& x, const High& y)
	{
		return (x.posneg == POSITIVE && y.posneg == POSITIVE) ||
			(x.posneg == NEGATIVE && y.posneg == NEGATIVE) ||
			(x.posneg == ZERO && y.posneg == ZERO);
	}

	//交换
	void High::swap(High& x, High& y)
	{
		High buf(x);
		x = y;
		y = buf;
	}

	//全正加法
	High High::addPos(const High& x, const High& y)
	{
		//复制字符串
		string s1 = x.s;
		string s2 = y.s;

		//结果长度
		ull len = 1 + max(x.s.length(), y.s.length());

		//补齐0
		s1.insert(0, len - s1.length(), '0');
		s2.insert(0, len - s2.length(), '0');

		//每一位相加
		vector<digit> digs(len, 0);
		for (ull i = 0; i < len; ++i)
			digs[i] = ToNum(s1[i]) + ToNum(s2[i]);

		//进位
		for(ll i = len - 1; i >= 0; --i)
			if (digs[i] >= 10)
			{
				++digs[i - 1];
				digs[i] -= 10;
			}

		//还原为字符串
		string s_out = ToStr(digs);

		DeleteHeadZero(s_out);

		return High(s_out, s_out == "0" ? ZERO : POSITIVE);
	}

	//全正减法
	High High::subPos(const High& x, const High& y)
	{
		//s1 > s2
		string s1 = maxH(x, y).s;
		string s2 = minH(x, y).s;

		ull len = s1.length();
		s2.insert(0, len - s2.length(), '0');

		vector<digit> digs1(len, 0);
		vector<digit> digs2(len, 0);
		vector<digit> digs_out(len, 0);

		for (ull i = 0; i < len; ++i)
		{
			digs1[i] = ToNum(s1[i]);
			digs2[i] = ToNum(s2[i]);
		}

		for (ll i = len - 1; i >= 0; --i)
		{
			if (digs1[i] < digs2[i])
			{
				--digs1[i - 1];
				digs1[i] += 10;
			}
			digs_out[i] = digs1[i] - digs2[i];
		}

		string s_out = ToStr(digs_out);

		DeleteHeadZero(s_out);

		return High(s_out, s_out == "0" ? ZERO : POSITIVE);
	}

	//赋值
	void High::operator=(const High& x)
	{
		s = x.s;
		posneg = x.posneg;
	}

	void High::operator=(ll num)
	{
		*this = High(num);
	}

	//加法
	High High::operator+(const High& x) const
	{
		//有一个是0
		if (posneg == ZERO || x.posneg == ZERO)
			return *this == 0 ? x : *this;

		if(isSamePosneg(*this,x))//同号
		{
			if (posneg == POSITIVE)//同为正
				return addPos(*this, x);
			else//同为负
			{
				High out(addPos(*this, x));
				out.posneg = NEGATIVE;
				return out;
			}
		}
		else//一正一负
		{
			High hmax(abs(*this));
			High hmin(abs(x));
			POSNEG firstPosneg = posneg;

			if (hmin == hmax)
				return High(0);

			if (hmax < hmin)
			{
				swap(hmax, hmin);
				firstPosneg = x.posneg;
			}

			High out(subPos(hmax, hmin));
			if (firstPosneg == NEGATIVE)
				out.posneg = NEGATIVE;
			return out;
		}

	}

	//减法
	High High::operator-(const High& x) const
	{
		High x_minus(x);
		x_minus.posneg = opposite(x_minus.posneg);

		return *this + x_minus;
	}

	//乘法
	High High::operator*(const High& x) const
	{
		//有0
		if (posneg == ZERO || x.posneg == ZERO)
			return High("", ZERO);

		ull len = max(length(), x.length());
		ull len_out = 2 * len - 1;

		string s1 = s;
		string s2 = x.s;

		//对齐
		s1.insert(0, len - s1.length(), '0');
		s2.insert(0, len - s2.length(), '0');

		vector<digit> digs_out(len_out, 0);

		//计算
		for (ull i = 0; i < len; ++i)
			for (ull j = 0; j < len; ++j)
				digs_out[i + j] += ToNum(s1[j]) * ToNum(s2[i]);

		//进位
		for (ll i = len_out - 1; i >= 1; --i)
			if (digs_out[i] >= 10)
			{
				digs_out[i - 1] += digs_out[i] / 10;
				digs_out[i] %= 10;
			}

		//第一位进位
		if (digs_out[0] >= 10)
		{
			digs_out.insert(digs_out.begin(), 0);
			++len_out;
			digs_out[0] += digs_out[1] / 10;
			digs_out[1] %= 10;
		}

		string s_out = ToStr(digs_out);

		DeleteHeadZero(s_out);

		//同号为正，异号为负
		POSNEG posneg_out{};
		if ((posneg == POSITIVE && x.posneg == POSITIVE) ||
			(posneg == NEGATIVE && x.posneg == NEGATIVE))
			posneg_out = POSITIVE;
		else
			posneg_out = NEGATIVE;

		return High(s_out, posneg_out);
	}

	//模
	High High::operator%(const High& x) const
	{
		if (!(*this >= 0 && x > 0))
		{
			cout << "错误！模运算输入错误" << endl;
			return High(0);
		}

		High y(*this);

		///


		while (y > 0)
		{
			y -= x;

			//for (ull i = 1; i <= 20; ++i)
			//	cout << y << endl;
		
		}

		return y + (y == 0 ? 0 : x);
	}

	void High::operator+=(const High& x)
	{
		*this = *this + x;
	}

	void High::operator-=(const High& x)
	{
		*this = *this - x;
	}

	void High::operator*=(const High& x)
	{
		*this = *this * x;
	}

	High High::operator+(ll num) const
	{
		return *this + High(num);
	}

	High High::operator-(ll num) const
	{
		High x(num);
		return *this - High(num);
	}

	High High::operator*(ll num) const
	{
		return *this * High(num);
	}

	void High::operator+=(ll num)
	{
		*this += High(num);
	}

	void High::operator-=(ll num)
	{
		*this -= High(num);
	}

	void High::operator*=(ll num)
	{
		*this *= High(num);
	}

	//前缀递增
	void High::operator++()
	{
		*this += 1;
	}

	//前缀递减
	void High::operator--()
	{
		*this -= 1;
	}

	//后缀递增
	void High::operator++(int)
	{
		*this += 1;
	}

	//后缀递减
	void High::operator--(int)
	{
		*this -= 1;
	}

	//相等
	bool High::operator==(const High& x) const
	{
		return s == x.s && posneg == x.posneg;
	}

	//不等于
	bool High::operator!=(const High& x) const
	{
		return !(*this == x);
	}

	//大于
	bool High::operator>(const High& x) const
	{
		//符号情况不同
		if (!isSamePosneg(*this, x))
			if (posneg > x.posneg)
				return true;
			else
				return false;

		//标记变量，负数时结果取反
		bool sgn = !(posneg == POSITIVE);

		//长度大绝对值一定大
		if (length() > x.length())
			return true ^ sgn;
		if (length() < x.length())
			return false ^ sgn;

		//长度相等
		for (ull i = 0; i < length(); ++i)
			if (s[i] != x.s[i])
				return (s[i] > x.s[i]) ^ sgn;

		//两者相等
		return false;
	}

	//小于
	bool High::operator<(const High& x) const
	{
		if (*this == x)
			return false;
		else
			return !(*this > x);
	}

	//大于等于
	bool High::operator>=(const High& x) const
	{
		return *this > x || *this == x;
	}

	//小于等于
	bool High::operator<=(const High& x) const
	{
		return *this < x || *this == x;
	}

	bool High::operator==(ll num) const
	{
		return *this == High(num);
	}

	bool High::operator!=(ll num) const
	{
		return *this != High(num);
	}

	bool High::operator>(ll num) const
	{
		return *this > High(num);
	}

	bool High::operator<(ll num) const
	{
		return *this < High(num);
	}

	bool High::operator>=(ll num) const
	{
		return *this >= High(num);
	}

	bool High::operator<=(ll num) const
	{
		return *this <= High(num);
	}




	/*中间层函数*/
	//字符串是标准化的
	bool High::StrIsStandard(const string& _s)
	{
		for (char c : _s)
			if (!(c >= '0' && c <= '9'))
				return false;

		return true;
	}

	//删除首位0
	void High::DeleteHeadZero(string& _s)
	{
		while (_s[0] == '0')
			_s.erase(0, 1);
		if (_s == "")
			_s += '0';
	}

	//字符转换为数字
	digit High::ToNum(char c)
	{
		return c + 1 - '1';
	}

	//数字转字符
	char High::ToChar(digit d)
	{
		if (d >= 10)
		{
			cout << "错误！某一位数大于了10" << endl;
			return 0;
		}

		return d + '1' - 1;
	}

	//转字符串
	string High::ToStr(vector<digit> _digs)
	{
		string out("");
		for (ull i = 0; i < _digs.size(); ++i)
			out += ToChar(_digs[i]);

		return out;
	}


	/*测试函数*/

	//获取s
	string High::getStr() const
	{
		return s;
	}

}