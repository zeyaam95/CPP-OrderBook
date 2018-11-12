#include <ctime>
#include "Order.h"
#include "Queue.h"

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
	Queue<Order> Bids;
	Queue<Order> Asks;

	return 0;
}