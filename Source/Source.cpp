#include <iostream>

using namespace std;

int test()
{
	int timeout;
	cout << "Hello Microsoft!" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << i << " squared = " << i*i << endl;
	}

	cin >> timeout;
	return 0;
}