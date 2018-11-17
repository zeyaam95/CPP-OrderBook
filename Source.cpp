#include "Order.h"
#include "Queue.h"
#include <vector>

using namespace std;

struct Transaction {
	long BuyerID, SellerID, Shares;
	double Price;
	time_t TimeStamp;
	Transaction(long buyer, long seller, double price, long share, time_t time) 
		: BuyerID(buyer), SellerID(seller), Price(price), Shares(share), TimeStamp(time) {}
};

vector<Transaction> TRANSACTIONS;


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

template <typename OrderTypeA, typename OrderTypeB>
void executeTransaction(Queue<OrderTypeA> anOrder, OrderTypeB incomingOrder) {
	if (anOrder.length() == 0) return;
	if (anOrder[0].getNumOfShares() > incomingOrder.getNumOfShares()) {
		TRANSACTIONS.push_back(Transaction( incomingOrder.getAccountID(), 
											anOrder[0].getAccountID(), 
											anOrder[0].getOrderPrice(), 
											incomingOrder.getNumOfShares(), 
											time(NULL)));
		long shareDiff = anOrder[0].getNumOfShares() - incomingOrder.getNumOfShares();
		anOrder[0].setNumOfShares(shareDiff);
	}

	else if (anOrder[0].getNumOfShares() == incomingOrder.getNumOfShares()) {
		TRANSACTIONS.push_back(Transaction( incomingOrder.getAccountID(), 
											anOrder[0].getAccountID(), 
											anOrder[0].getOrderPrice(), 
											incomingOrder.getNumOfShares(), 
											time(NULL)));
		anOrder.deQueue();
	}

	else {
		while (incomingOrder.getNumOfShares() > 0) {
			executeTransaction(anOrder, incomingOrder);
			long shareDiff = incomingOrder.getNumOfShares() - anOrder[0].getNumOfShares() ;
			incomingOrder.setNumOfShares(shareDiff);
		}
	}
}


int main() {
	Queue<Bid> Bids;
	Queue<Ask> Asks;
	fstream ordersFile;
	ordersFile.open("shortorder.dat", ios::in);
	Order *inputOrder = new Order;
	while (!ordersFile.eof()) {

		ordersFile >> *inputOrder;
		if(inputOrder->getActionType() == 1) {
			cout << "(inputOrder->getOrderPrice() == 0) " << (inputOrder->getOrderPrice() == 0) << endl;
			if (inputOrder->getOrderPrice() == 0) {
				cout << "ASK: "<< Asks[0] <<" " << "BID: "<<*inputOrder<< endl;
				executeTransaction(Asks, *inputOrder);
				/**
				if (Asks[0].getNumOfShares() > inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					long shareDiff = Asks[0].getNumOfShares() - inputOrder->getNumOfShares();
					Asks[0].setNumOfShares(shareDiff);
				}
				else if (Asks[0].getNumOfShares() == inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					Asks.deQueue();
				}
				else {
					 
				}*/
			}
			else {
				Bid *newBid = new Bid(inputOrder->getOrderType(),
					inputOrder->getActionType(),
					inputOrder->getOrderPrice(),
					inputOrder->getNumOfShares(),
					inputOrder->getAccountID());
				//cout << *newBid;
				Bids.enQueue(newBid);
			}
		}
		else {
			cout << "(inputOrder->getOrderPrice() == 0) " <<(inputOrder->getOrderPrice() == 0) << endl;
			if (inputOrder->getOrderPrice() == 0) {
				cout << "BID: " << Bids[0] << endl;
			}
			else {
				Ask *newAsk = new Ask(inputOrder->getOrderType(),
					inputOrder->getActionType(),
					inputOrder->getOrderPrice(),
					inputOrder->getNumOfShares(),
					inputOrder->getAccountID());
				//cout << *newAsk;
				Asks.enQueue(newAsk);
			}
		}
		inputOrder = new Order;
		//timeDelay(1);
	}
	cout << "WOWOWOWOWO"<<endl;
	//cout << Bids;
	ordersFile.close();
	return 0;
}