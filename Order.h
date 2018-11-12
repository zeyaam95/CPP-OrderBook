#pragma once
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

enum TYPE {
	MarketOrder = 0,
	LimitOrder = 1
};
enum ACTION {
	Buy = 1,
	Sell = -1
};

class Order
{
private:
	TYPE orderType;
	ACTION orderAction;
	double orderPrice;
	long int numOfShares, accountID;
public:
	bool orderMatch(Order&);
	Order();
	Order(TYPE&, ACTION&, double&, long int&, long int&);
	~Order();
	friend istream& operator>>(istream&, Order&);
	friend ostream& operator<<(ostream&, Order&);
	
};


