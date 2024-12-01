#include "test.h"

#ifdef DEBUG

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

//operator-
bool test_operator_sub(ll x, ll y)
{
	if (High(x - y) == (High(x) - High(y)))
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout << " 期望值 = " << High(x - y) << " 返回值 = " << (High(x) - High(y)) << endl;
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
	test_operator_sub(100000, 20);
	test_operator_sub(100000, -20);


	

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

//operator+
bool test_operator_add(ll x, ll y)
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

bool testall_operator_add()
{
	test_operator_add(20, 10);
	test_operator_add(10, 20);
	test_operator_add(0, 0);
	test_operator_add(20, 20);
	test_operator_add(-20, -20);
	test_operator_add(20, -20);
	test_operator_add(-20, 20);
	test_operator_add(20, -10);
	test_operator_add(-10, 20);
	test_operator_add(-20, 10);
	test_operator_add(10, -20);
	test_operator_add(20, 0);
	test_operator_add(0, 20);
	test_operator_add(-20, 0);
	test_operator_add(0, -20);
	test_operator_add(100000, 20);
	test_operator_add(100000, -20);

	return false;
}

//addPos
bool test_addPos(ull x, ull y)
{
	High ret(High::addPos(x, y));
	High exp(x + y);

	if (ret == exp)
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout << " 期望值 = " << exp << " 返回值 = " << ret << endl;
		return false;
	}
}

bool testall_addPos()
{
	test_addPos(0, 0);
	test_addPos(20, 0);
	test_addPos(0, 20);
	test_addPos(20, 20);
	test_addPos(100, 20);
	test_addPos(20, 100);
	test_addPos(10000000, 20);
	test_addPos(7527537, 752661);

	return false;
}

//DeleteHeadZero
bool test_DeleteHeadZero(string s, string exp)
{
	string org(s);
	High::DeleteHeadZero(s);
	if (s == exp)
		return true;
	else
	{
		cout << "s = " << org << endl;
		cout << " 期望值 = " << exp << " 返回值 = " << s << endl;
		return false;
	}
}

bool testall_DeleteHeadZero()
{
	test_DeleteHeadZero("00123", "123");
	test_DeleteHeadZero("123", "123");
	test_DeleteHeadZero("0123", "123");
	test_DeleteHeadZero("0000", "0");
	test_DeleteHeadZero("0", "0");
	test_DeleteHeadZero("011001", "11001");

	return false;
}

bool test_subPos(ll x, ll y)
{
	High ret(High::subPos(x, y));
	High exp(x - y);

	if (ret == exp)
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout << " 期望值 = " << exp << " 返回值 = " << ret << endl;
		return false;
	}
}

bool testall_subPos()
{
	test_subPos(20, 0);
	test_subPos(0, 0);
	test_subPos(100, 100);
	test_subPos(100, 20);
	test_subPos(100000000, 20);
	test_subPos(200000000, 20);

	return false;
}

//operator/
bool test_operator_div(ll x, ll y)
{
	if (High(x / y) == (High(x) / High(y)))
		return true;
	else
	{
		cout << "x = " << x << " y = " << y;
		cout << " 期望值 = " << High(x / y) << " 返回值 = " << (High(x) / High(y)) << endl;
		return false;
	}
}

bool testall_operator_chu()
{
	test_operator_div(100, 20);
	test_operator_div(0, 20);
	test_operator_div(100, 19);
	test_operator_div(20, 19);
	test_operator_div(20, 20);

	//auto start = chrono::high_resolution_clock::now();
	test_operator_div(10000000, 10);
	//auto end = chrono::high_resolution_clock::now();
	//chrono::duration<double, milli> elapsed = end - start;
	//cout << "Elapsed time: " << elapsed.count() << " ms" << endl;
	
	test_operator_div(-100, 20);
	test_operator_div(100, -20);
	test_operator_div(-100, -20);
	test_operator_div(753745278, 75786);
	test_operator_div(4563, 50000);

	return false;
}

#endif // DEBUG

