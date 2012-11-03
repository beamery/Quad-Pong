#include <iostream>
#include <SFML/System.hpp>

using namespace std;

int main()
{
	sf::Clock clock;
	while (clock.GetElapsedTime() < 500.0f)
	{
		cout << clock.GetElapsedTime() << endl;
		sf::Sleep(0.5f);
	}
	return 0;
}
