#include <ctime>
#include "Order.h"
#include "Queue.h"

using namespace std;


void timeDelay(double t)
{
	time_t initial, final;
	time_t ltime;
	initial = time(&ltime);
	final = initial + static_cast<time_t>(t);
	while (time(&ltime) < final)
	{
	}
	return;
}

int main() {
	Queue<Bid> Bids;
	Queue<Ask> Asks;

	return 0;
}