#include "Thread.hpp"

void DoSomeStuff(int kawai)
{
	int i = 0;
	while (i++ < 10000) {
		std::cout << kawai;
	}
}

int main() {
	Thread<int> yooo(&DoSomeStuff, 2);
	Thread<int> yo(&DoSomeStuff, 3);
	Thread<int> yoy(&DoSomeStuff, 1);
	Thread<int> yoyo(&DoSomeStuff, 4);
	Thread<int> yoyoy(&DoSomeStuff, 5);
	Thread<int> yooy(&DoSomeStuff, 6);

	yooo.join();
	yo.join();
	yoy.join();
	yoyo.join();
	yoyoy.join();
	yooy.join();
	std::cout << std::endl;
}
