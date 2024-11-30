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
			cout << "�����ʽ�����ַ���û�б�׼��" << endl;
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
			cout << "�����ʽ�����ַ���û�б�׼��" << endl;
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

	//��ʽ�����
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

	//�������
	POSNEG High::getPosneg() const
	{
		return posneg;
	}

	//����
	ull High::length() const
	{
		return s.length();
	}

	//����0
	bool High::is0() const
	{
		return s == "";
	}

	//�෴����
	POSNEG High::opposite(POSNEG _posneg)
	{
		if (_posneg == ZERO)
			return ZERO;
		
		return _posneg == POSITIVE ? NEGATIVE : POSITIVE;
	}

	//����ֵ
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

	//���ֵ
	High High::maxH(const High& x, const High& y)
	{
		return x >= y ? x : y;
	}

	//��Сֵ
	High High::minH(const High& x, const High& y)
	{
		return x <= y ? x : y;
	}

	//����ͬ��
	bool High::isSamePosneg(const High& x, const High& y)
	{
		return (x.posneg == POSITIVE && y.posneg == POSITIVE) ||
			(x.posneg == NEGATIVE && y.posneg == NEGATIVE) ||
			(x.posneg == ZERO && y.posneg == ZERO);
	}

	//����
	void High::swap(High& x, High& y)
	{
		High buf(x);
		x = y;
		y = buf;
	}

	//ȫ���ӷ�
	High High::addPos(const High& x, const High& y)
	{
		//�����ַ���
		string s1 = x.s;
		string s2 = y.s;

		//�������
		ull len = 1 + max(x.s.length(), y.s.length());

		//����0
		s1.insert(0, len - s1.length(), '0');
		s2.insert(0, len - s2.length(), '0');

		//ÿһλ���
		vector<digit> digs(len, 0);
		for (ull i = 0; i < len; ++i)
			digs[i] = ToNum(s1[i]) + ToNum(s2[i]);

		//��λ
		for(ll i = len - 1; i >= 0; --i)
			if (digs[i] >= 10)
			{
				++digs[i - 1];
				digs[i] -= 10;
			}

		//��ԭΪ�ַ���
		string s_out = ToStr(digs);

		DeleteHeadZero(s_out);

		return High(s_out, s_out == "0" ? ZERO : POSITIVE);
	}

	//ȫ������
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

	//��ֵ
	void High::operator=(const High& x)
	{
		s = x.s;
		posneg = x.posneg;
	}

	void High::operator=(ll num)
	{
		*this = High(num);
	}

	//�ӷ�
	High High::operator+(const High& x) const
	{
		//��һ����0
		if (posneg == ZERO || x.posneg == ZERO)
			return *this == 0 ? x : *this;

		if(isSamePosneg(*this,x))//ͬ��
		{
			if (posneg == POSITIVE)//ͬΪ��
				return addPos(*this, x);
			else//ͬΪ��
			{
				High out(addPos(*this, x));
				out.posneg = NEGATIVE;
				return out;
			}
		}
		else//һ��һ��
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

	//����
	High High::operator-(const High& x) const
	{
		High x_minus(x);
		x_minus.posneg = opposite(x_minus.posneg);

		return *this + x_minus;
	}

	//�˷�
	High High::operator*(const High& x) const
	{
		//��0
		if (posneg == ZERO || x.posneg == ZERO)
			return High("", ZERO);

		ull len = max(length(), x.length());
		ull len_out = 2 * len - 1;

		string s1 = s;
		string s2 = x.s;

		//����
		s1.insert(0, len - s1.length(), '0');
		s2.insert(0, len - s2.length(), '0');

		vector<digit> digs_out(len_out, 0);

		//����
		for (ull i = 0; i < len; ++i)
			for (ull j = 0; j < len; ++j)
				digs_out[i + j] += ToNum(s1[j]) * ToNum(s2[i]);

		//��λ
		for (ll i = len_out - 1; i >= 1; --i)
			if (digs_out[i] >= 10)
			{
				digs_out[i - 1] += digs_out[i] / 10;
				digs_out[i] %= 10;
			}

		//��һλ��λ
		if (digs_out[0] >= 10)
		{
			digs_out.insert(digs_out.begin(), 0);
			++len_out;
			digs_out[0] += digs_out[1] / 10;
			digs_out[1] %= 10;
		}

		string s_out = ToStr(digs_out);

		DeleteHeadZero(s_out);

		//ͬ��Ϊ�������Ϊ��
		POSNEG posneg_out{};
		if ((posneg == POSITIVE && x.posneg == POSITIVE) ||
			(posneg == NEGATIVE && x.posneg == NEGATIVE))
			posneg_out = POSITIVE;
		else
			posneg_out = NEGATIVE;

		return High(s_out, posneg_out);
	}

	//ģ
	High High::operator%(const High& x) const
	{
		if (!(*this >= 0 && x > 0))
		{
			cout << "����ģ�����������" << endl;
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

	//ǰ׺����
	void High::operator++()
	{
		*this += 1;
	}

	//ǰ׺�ݼ�
	void High::operator--()
	{
		*this -= 1;
	}

	//��׺����
	void High::operator++(int)
	{
		*this += 1;
	}

	//��׺�ݼ�
	void High::operator--(int)
	{
		*this -= 1;
	}

	//���
	bool High::operator==(const High& x) const
	{
		return s == x.s && posneg == x.posneg;
	}

	//������
	bool High::operator!=(const High& x) const
	{
		return !(*this == x);
	}

	//����
	bool High::operator>(const High& x) const
	{
		//���������ͬ
		if (!isSamePosneg(*this, x))
			if (posneg > x.posneg)
				return true;
			else
				return false;

		//��Ǳ���������ʱ���ȡ��
		bool sgn = !(posneg == POSITIVE);

		//���ȴ����ֵһ����
		if (length() > x.length())
			return true ^ sgn;
		if (length() < x.length())
			return false ^ sgn;

		//�������
		for (ull i = 0; i < length(); ++i)
			if (s[i] != x.s[i])
				return (s[i] > x.s[i]) ^ sgn;

		//�������
		return false;
	}

	//С��
	bool High::operator<(const High& x) const
	{
		if (*this == x)
			return false;
		else
			return !(*this > x);
	}

	//���ڵ���
	bool High::operator>=(const High& x) const
	{
		return *this > x || *this == x;
	}

	//С�ڵ���
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




	/*�м�㺯��*/
	//�ַ����Ǳ�׼����
	bool High::StrIsStandard(const string& _s)
	{
		for (char c : _s)
			if (!(c >= '0' && c <= '9'))
				return false;

		return true;
	}

	//ɾ����λ0
	void High::DeleteHeadZero(string& _s)
	{
		while (_s[0] == '0')
			_s.erase(0, 1);
		if (_s == "")
			_s += '0';
	}

	//�ַ�ת��Ϊ����
	digit High::ToNum(char c)
	{
		return c + 1 - '1';
	}

	//����ת�ַ�
	char High::ToChar(digit d)
	{
		if (d >= 10)
		{
			cout << "����ĳһλ��������10" << endl;
			return 0;
		}

		return d + '1' - 1;
	}

	//ת�ַ���
	string High::ToStr(vector<digit> _digs)
	{
		string out("");
		for (ull i = 0; i < _digs.size(); ++i)
			out += ToChar(_digs[i]);

		return out;
	}


	/*���Ժ���*/

	//��ȡs
	string High::getStr() const
	{
		return s;
	}

}