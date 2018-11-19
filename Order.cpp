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

/*
	if (type != 0 || type != 1) {
		throw "INVALID TYPE ERROR: Order Type can only be a 0 (Market) or a 1 (Limited).\n";
	}
	ord.orderType = type;
	
	if (action != -1 || action != 1) {
		throw "INVALID ACTION ERROR: Order Action can only be a -1 (Sell) or a 1 (Buy).\n";
	}
	ord.setOrderAction(action);

	is >> price;
	if (price < 0) {
		throw "INVALID PRICE ERROR: Order Price cannot be negative.";
	}
	ord.setOrderPrice(price);
	
	is >> validation;
	if (validation <= 0 ) {
		throw "INVALID NUMBER OF SHARES: Number of Shares must be greater than 0.";
	}
	ord.setNumOfShares(validation);

	is >> id;
	if (id < 100000000 || id > 999999999) {
		throw "INVALID ACCOUNT ID: Account ID must be a 9 digit number.";
	}
	ord.setAccountID(id);

	is >> ord.orderPrice >> ord.numOfShares >> ord.accountID;
	*/