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
protected:
	TYPE orderType;
	ACTION orderAction;
	double orderPrice;
	long int numOfShares, accountID;
public:
	// Constructors
	Order();
	Order(TYPE&, ACTION&, double&, long int&, long int&);
	~Order();
	// Setters
	void setOrderType(TYPE& type) {this->orderType = type;}
	void setOrderAction(ACTION& action) {this->orderAction = action;}
	void setOrderPrice(double& price) {this->orderPrice = price;}
	void setNumOfShares(long int& shares) {this->numOfShares = shares;}
	void setAccountID(long int& id) {this->accountID = id;}
	// Getters
	TYPE getOrderType() const {return this->orderType;}
	ACTION getActionType() const {return this->orderAction;}
	double getOrderPrice() const {return this->orderPrice;}
	long int getNumOfShares() const {return this->numOfShares;}
	long int getAccountID() const {return this->accountID;}
	// Overloaded Operators
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
	Ask(TYPE& type, ACTION& action , double& price, long int& shares, long int& accountid)
	 : Order(type, action , price, shares, accountid) {}

	bool operator<=(const Order&) {

	}
	bool operator>=(const Order&) {

	}
	bool operator==(const Order&) {

	}
	bool operator!=(const Order&) {

	}
};

class Bid : public Order {
public:
	Bid(TYPE& type, ACTION& action , double& price, long int& shares, long int& accountid)
	 : Order(type, action , price, shares, accountid) {}
	
	bool operator<=(const Order&) {

	}
	bool operator>=(const Order&) {

	}
	bool operator==(const Order&) {

	}
	bool operator!=(const Order&) {

	}
};
