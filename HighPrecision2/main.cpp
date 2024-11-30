#include "HighPrecision.h"
#include "test.h"

using namespace my;

int main()
{
	//testall_operator_mod();

	High x(100001);
	High y(100);

	//if ((x % y) == (100001 % 100))
	//	cout << "true" << endl;
	//else
	//	cout << "false" << endl;

	x -= y;
	cout << x << endl;

}