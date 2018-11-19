#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

class Order
{
protected:
	int orderType;
	int orderAction;
	double orderPrice;
	long int numOfShares, accountID;
	time_t timeStamp = time(NULL);
public:
	// Constructors
	Order();
	Order(int&, int&, double&, long&, long&);
	~Order();
	// Setters
	void setOrderType(int& type) {this->orderType = type;}
	void setOrderAction(int& action) {this->orderAction = action;}
	void setOrderPrice(double& price) {this->orderPrice = price;}
	void setNumOfShares(long int& shares) {this->numOfShares = shares;}
	void setAccountID(long int& id) {this->accountID = id;}
	// Getters
	int getOrderType() {return this->orderType;}
	int getActionType() {return this->orderAction;}
	double getOrderPrice() {return this->orderPrice;}
	long getNumOfShares() {return this->numOfShares;}
	long getAccountID() {return this->accountID;}
	time_t getTimeStamp() {return this->timeStamp;}
	// Overloaded Operators
	void operator=(Order&);
	friend istream& operator>>(istream&, Order&);
	friend ostream& operator<<(ostream&, Order&);
};
//! Implement all the following functions in the Order.cpp file Justin.
/* 
* The Ask Order should be prioritized by the lowest asking price, meaning that if 
* some seller is asking for the lowest price then that seller should have the highest
* priority as a low buying price is appealing to a buyer.
* The opposite is true for Bid Order, which prioritizes by the highest bidding price
* since a high selling price is more appealing to a seller.
* By matching Bids and Asks we complete an order.
*/
class Ask : public Order {
public:
	Ask(int type, int action , double price, long shares, long accountid)
		: Order(type, action, price, shares, accountid) {
		this->timeStamp = time(NULL);
	}

	bool operator<=(Ask& r) {
		return this->getOrderPrice() <= r.getOrderPrice();
	}
	bool operator>=(Ask& r) {
		return this->getOrderPrice() >= r.getOrderPrice();
	}
	bool operator==(Ask&) {

	}
	bool operator!=(Ask&) {

	}
};

class Bid : public Order {
public:
	Bid(int type, int action , double price, long shares, long accountid)
	 : Order(type, action , price, shares, accountid) {
		this->timeStamp = time(NULL);
	}
	
	bool operator<=(Bid& r) {
		return this->getOrderPrice() <= r.getOrderPrice();
	}
	bool operator>=(Bid& r) {
		return this->getOrderPrice() >= r.getOrderPrice();
	}
	bool operator==(Bid&) {

	}
	bool operator!=(Bid&) {

	}
};
