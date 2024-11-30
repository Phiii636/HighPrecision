#include "test.h"

//operator>
bool test_operator_dayu(ll x, ll y)
{
	if ((x > y) == (High(x) > High(y)))
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout<< " 期望值 = "<< (x > y) << " 返回值 = " << (High(x) > High(y)) << endl;
		return false;
	}
}

bool testall_operator_dayu()
{
	test_operator_dayu(100, 20);
	test_operator_dayu(20, 20);
	test_operator_dayu(20, 100);
	test_operator_dayu(100, 0);
	test_operator_dayu(0, 100);
	test_operator_dayu(-100, 0);
	test_operator_dayu(0, -100);
	test_operator_dayu(0, 0);
	test_operator_dayu(-100, -20);
	test_operator_dayu(-20, -100);
	test_operator_dayu(-20, -20);
	test_operator_dayu(20, -20);
	test_operator_dayu(-20, 20);
	test_operator_dayu(-100, 20);
	test_operator_dayu(-20, 100);
	test_operator_dayu(100, -20);
	test_operator_dayu(20, -100);

	return true;
}

//operator+
bool test_operator_sub(ll x, ll y)
{
	if (High(x + y) == (High(x) + High(y)))
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout << " 期望值 = " << High(x + y) << " 返回值 = " << (High(x) + High(y)) << endl;
		return false;
	}
}

bool testall_operator_sub()
{

	test_operator_sub(20, 10);
	test_operator_sub(10, 20);
	test_operator_sub(0, 0);
	test_operator_sub(20, 20);
	test_operator_sub(-20, -20);
	test_operator_sub(20, -20);
	test_operator_sub(-20, 20);
	test_operator_sub(20, -10);
	test_operator_sub(-10, 20);
	test_operator_sub(-20, 10);
	test_operator_sub(10, -20);
	test_operator_sub(20, 0);
	test_operator_sub(0, 20);
	test_operator_sub(-20, 0);
	test_operator_sub(0, -20);

	

	return false;
}

//operator%
bool test_operator_mod(ll x, ll y)
{
	if (High(x % y) == (High(x) % High(y)))
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout << " 期望值 = " << High(x % y) << " 返回值 = " << (High(x) % High(y)) << endl;
		return false;
	}
}

bool testall_operator_mod()
{
	test_operator_mod(100, 10);
	test_operator_mod(0, 100);
	test_operator_mod(101, 10);
	test_operator_mod(5, 2);

	test_operator_mod(1000001, 1000);

	return true;
}

bool test_operator_add(ll x, ll y)
{
	return false;
}


