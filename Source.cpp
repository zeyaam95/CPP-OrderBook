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
	friend ostream& operator<<(ostream&, Transaction&);
};

ostream& operator<<(ostream& os, Transaction& tr) {
	os << tr.BuyerID << " "
		<< tr.SellerID << " "
		<< tr.Shares << " "
		<< tr.Price << " "
		<< tr.TimeStamp << endl;
	return os;
}

vector<Transaction> TRANSACTIONS;

void printTransaction(vector<Transaction> Tr) {
	for (int i = 0; i < Tr.size(); i++) {
		std::cout << Tr[i] << endl;
	}
}


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
inline void executeTransaction(Queue<OrderTypeA> anOrder, OrderTypeB incomingOrder) {
	if (anOrder.length() == 0) return;
	if (anOrder[0].getNumOfShares() > incomingOrder.getNumOfShares()) {
		TRANSACTIONS.push_back(Transaction( incomingOrder.getAccountID(), anOrder[0].getAccountID(), anOrder[0].getOrderPrice(), incomingOrder.getNumOfShares(), time(NULL)));
		long shareDiff = anOrder[0].getNumOfShares() - incomingOrder.getNumOfShares();
		anOrder[0].setNumOfShares(shareDiff);
	}
	/*
	else {
		while (incomingOrder.getNumOfShares() > 0) {
			executeTransaction(anOrder, incomingOrder);
			long shareDiff = incomingOrder.getNumOfShares() - anOrder[0].getNumOfShares();
			incomingOrder.setNumOfShares(shareDiff);
		}
	}
	*/
}


int main() {
	Queue<Bid> Bids;
	Queue<Ask> Asks;
	fstream ordersFile;
	long shareDiff;
	ordersFile.open("shortorder.dat", ios::in);
	Order *inputOrder = new Order;
	//Order temp;
	while (!ordersFile.eof()) {

		ordersFile >> *inputOrder;
		std::cout <<"NEW ORDER: " << *inputOrder << endl;
		std::cout <<"BIDS:\n "<< Bids <<"\nASKS: \n"<< Asks << endl;
		std::cout << "==========================\n\n";
		printTransaction(TRANSACTIONS);
		std::cout << "==========================\n\n";
		if(inputOrder->getActionType() == 1) {/*
			if (inputOrder->getOrderType() == 0 && Asks.length() == 0) {
				break;
			}
			else */if (Asks.length() > 0 && (inputOrder->getOrderPrice() == 0 || inputOrder->getOrderPrice() >= Asks[0].getOrderPrice())) {
				if (Asks[0].getNumOfShares() > inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					std::cout << "ASK: " << Asks[0] << " " << "BID: " << *inputOrder << endl;
					std::cout << "TRANSACTION: " << TRANSACTIONS.back();
					long shareDiff = Asks[0].getNumOfShares() - inputOrder->getNumOfShares();
					Asks[0].setNumOfShares(shareDiff);
					std::cout << "ASK: " << Asks[0] << endl;
				}
				else if (Asks[0].getNumOfShares() == inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					std::cout << "ASK: " << Asks[0] << " " << "BID: " << *inputOrder << endl;
					std::cout << "TRANSACTION: " << TRANSACTIONS.back();
					if (Asks.length() > 0) std::cout << Asks[0];
					Asks.deQueue();
				}
				else {
					while (inputOrder->getNumOfShares() > 0 && Asks.length() > 0) {
						std::cout << "\n<<<>>> WHILE LOOP IN BID LAND <<<>>>\n";
						if (inputOrder->getOrderPrice() < Asks[0].getOrderPrice() && inputOrder->getOrderPrice() !=0) {
							std::cout << "\nCREATING BID\n";
							Bid *newBid = new Bid(inputOrder->getOrderType(),
								inputOrder->getActionType(),
								inputOrder->getOrderPrice(),
								inputOrder->getNumOfShares(),
								inputOrder->getAccountID());
							//std::cout << *newBid;
							Bids.enQueueBid(newBid);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
						}
						else if (Asks[0].getNumOfShares() > inputOrder->getNumOfShares()) {
							TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
							std::cout << "TRANSACTION: " << TRANSACTIONS.back();
							std::cout << "ASK: " << Asks[0] << " " << "BID: " << *inputOrder << endl;
							shareDiff = Asks[0].getNumOfShares() - inputOrder->getNumOfShares();
							Asks[0].setNumOfShares(shareDiff);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
							std::cout << "ASK: " << Asks[0] << endl;
						}
						else if (Asks[0].getNumOfShares() <= inputOrder->getNumOfShares()) {
							TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), Asks[0].getNumOfShares(), time(NULL)));
							std::cout << "ASK: " << Asks[0] << " " << "BID: " << *inputOrder << endl;
							std::cout << "TRANSACTION: " << TRANSACTIONS.back() << endl;
							shareDiff = inputOrder->getNumOfShares() - Asks[0].getNumOfShares();
							inputOrder->setNumOfShares(shareDiff);
							std::cout << "BID: " << *inputOrder << endl;
							Asks.deQueue();
						}
					}
				}
			}
			else {
				std::cout << "CONDITION: " << (Asks.length() > 0 && (inputOrder->getOrderPrice() == 0 || inputOrder->getOrderPrice() >= Asks[0].getOrderPrice()))<<'\n';
				std::cout << "\nCREATING BID\n";
				Bid *newBid = new Bid(inputOrder->getOrderType(),
					inputOrder->getActionType(),
					inputOrder->getOrderPrice(),
					inputOrder->getNumOfShares(),
					inputOrder->getAccountID());
				std::cout << *newBid;
				Bids.enQueueBid(newBid);
				cout << Bids;
			}
		}
		else {
			if (inputOrder->getOrderType() == 0 && Bids.length() == 0) {
				cout << "Market Inbalance - Ask order ID: " << inputOrder->getAccountID()<<" Volume : "<<inputOrder->getNumOfShares() <<" - unmatched"<<endl;
			}
			else if (Bids.length() > 0 && (inputOrder->getOrderPrice() == 0 || inputOrder->getOrderPrice() <= Bids[0].getOrderPrice())) {
				if (Bids[0].getNumOfShares() > inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					std::cout << "BID: " << Bids[0] << " " << "ASK: " << *inputOrder << endl;
					std::cout << "TRANSACTION: " << TRANSACTIONS.back();
					long shareDiff = Bids[0].getNumOfShares() - inputOrder->getNumOfShares();
					Bids[0].setNumOfShares(shareDiff);
				}
				else if (Bids[0].getNumOfShares() == inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					std::cout << "BID: " << Bids[0] << " " << "ASK: " << *inputOrder << endl;
					std::cout << "TRANSACTION: " << TRANSACTIONS.back();
					Bids.deQueue();
					if (Bids.length() > 0) std::cout << Bids[0] << endl;
				}
				else {
					while (inputOrder->getNumOfShares() > 0 && Bids.length() > 0) {
						std::cout << "\n<<<>>> WHILE LOOP ASK LAND<<<>>>\n";
						//std::cout << "BID: " << Bids[0] << " " << "BID: " << *inputOrder << endl;
						if (inputOrder->getOrderPrice() > Bids[0].getOrderPrice()) {
							std::cout << "\nCREATING ASK\n";
							Ask *newAsk = new Ask(inputOrder->getOrderType(),
								inputOrder->getActionType(),
								inputOrder->getOrderPrice(),
								inputOrder->getNumOfShares(),
								inputOrder->getAccountID());
							//std::cout << *newAsk;
							Asks.enQueueAsk(newAsk);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
						}
						else if (Bids[0].getNumOfShares() > inputOrder->getNumOfShares()) {
							TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
							std::cout << "BID: " << Bids[0] << " " << "ASK: " << *inputOrder << endl;
							std::cout << "TRANSACTION: " << TRANSACTIONS.back();
							shareDiff = Bids[0].getNumOfShares() - inputOrder->getNumOfShares();
							Bids[0].setNumOfShares(shareDiff);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
							std::cout << "BID: " << Bids[0] << endl;
						}
						else if (Bids[0].getNumOfShares() <= inputOrder->getNumOfShares()) {
							TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), Bids[0].getNumOfShares(), time(NULL)));
							std::cout << "BID: " << Bids[0] << " " << "ASK: " << *inputOrder << endl;
							std::cout << "TRANSACTION: " << TRANSACTIONS.back() << endl;
							shareDiff = inputOrder->getNumOfShares() - Bids[0].getNumOfShares();
							inputOrder->setNumOfShares(shareDiff);
							std::cout << "ASK: " << *inputOrder << endl;
							Bids.deQueue();
						}
					}
				}
				

			}
			else {
				std::cout << "\nCREATING ASK\n";
				Ask *newAsk = new Ask(inputOrder->getOrderType(),
					inputOrder->getActionType(),
					inputOrder->getOrderPrice(),
					inputOrder->getNumOfShares(),
					inputOrder->getAccountID());
				//std::cout << *newAsk;
				Asks.enQueueAsk(newAsk);
			}
		}
		//inputOrder = new Order;
		//timeDelay(1);
	}
	std::cout << "asdasddwad" << endl;
	std::cout << Bids << Asks;
	printTransaction(TRANSACTIONS);
	ordersFile.close();
	return 0;
}