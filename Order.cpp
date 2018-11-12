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
	int cast;
	is >> cast;

	if (cast != 0 || cast != 1) {
		throw "INVALID TYPE ERROR: Order Type can only be a 0 (Market) or a 1 (Limited).\n";
	}
	ord.orderType = static_cast<TYPE>(cast);

	is >> cast;

	if (cast != -1 || cast != 1) {
		throw "INVALID ACTION ERROR: Order Action can only be a -1 (Sell) or a 1 (Buy).\n";
	}
	ord.orderAction = static_cast<ACTION>(cast);

	is >> ord.orderPrice >> ord.numOfShares >> ord.numOfShares;
	ord.orderPrice = ord.orderPrice - fmod(ord.orderPrice, 0.01);

	return is;
}