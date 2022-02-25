#include "Vector2.h"

int main(){
	Vector2 a;
	Vector2 b;

	double c;
	std::cin >> a;
	std::cin >> b;

	c = a.angle(b);

	std::cout << c << "\n";

	system("pause");
}