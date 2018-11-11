#include <iostream>
#include <ctime>

using namespace std;


void timeDelay(double t)
{
	time_t initial, final;
	time_t ltime;
	initial = time(&ltime);
	final = initial + t;
	while (time(&ltime) < final)
	{
	}
	return;
}

int main() {
	return 0;
}