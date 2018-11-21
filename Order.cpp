/*
Author: Zeyaam Shahid
*/
#include "Order.h"

Order::Order() {
	this->orderType = 0;
	this->orderAction = 0;
	this->orderPrice = 0;
	this->numOfShares = 0;
	this->accountID = 0;
	this->timeStamp = time(NULL);
}

Order::~Order() {

}

Order::Order(int& type, int& action, double& price, long& shares, long& accountid) {
	this->orderType = type;
	this->orderAction = action;
	this->orderPrice = price;
	this->numOfShares = shares;
	this->accountID = accountid;
}

void Order::operator=(Order& other) {
	this->orderType = other.getOrderType();
	this->orderAction = other.getActionType();
	this->orderPrice = other.getOrderPrice();
	this->numOfShares = other.getNumOfShares();
	this->accountID = other.getAccountID();
	this->timeStamp = other.getTimeStamp();
}


istream& operator>>(istream& is , Order& ord) {
	is >> ord.orderType >> ord.orderAction >> ord.orderPrice >> ord.numOfShares >> ord.accountID;
	ord.timeStamp = time(NULL);
	return is;
}

ostream& operator<<(ostream& os, Order& ord) {
	os 	<< ord.getOrderType() 	<< " "
		<< ord.getActionType() 	<< " "
		<< ord.getOrderPrice()	<< " "
		<< ord.getNumOfShares() << " "
		<< ord.getAccountID()   << " "
		<< ord.getTimeStamp()   << endl;
	return os;
}