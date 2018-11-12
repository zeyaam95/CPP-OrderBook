#include "Order.h"

Order::Order() {

}

Order::~Order() {

}

Order::Order(TYPE& type, ACTION& action, double& price, long int& shares, long int& accountid) {
	this->orderType = type;
	this->orderAction = action;
	this->orderPrice = price;
	this->numOfShares = shares;
	this->accountID = accountid;
}

istream& operator>>(istream& is , Order& ord) {
	double price;
	long int validation, id;
	
	is >> validation;
	if (validation != 0 || validation != 1) {
		throw "INVALID TYPE ERROR: Order Type can only be a 0 (Market) or a 1 (Limited).\n";
	}
	TYPE type = static_cast<TYPE>(validation);
	ord.setOrderType(type);

	is >> validation;
	if (validation != -1 || validation != 1) {
		throw "INVALID ACTION ERROR: Order Action can only be a -1 (Sell) or a 1 (Buy).\n";
	}
	ACTION act = static_cast<ACTION>(validation);
	ord.setOrderAction(act);

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
	ord.orderPrice = ord.orderPrice - fmod(ord.orderPrice, 0.01);

	return is;
}

ostream& operator<<(ostream& os, Order& ord) {
	os 	<< ord.getOrderType() 	<< " "
		<< ord.getActionType() 	<< " "
		<< ord.getOrderPrice()	<< " "
		<< ord.getNumOfShares() << " "
		<< ord.getAccountID() 	<< endl;
	return os;
}