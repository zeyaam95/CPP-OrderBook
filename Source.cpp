/*
Author: Zeyaam Shahid
*/
#include "Order.h"
#include "Queue.h"
#include <vector>

using namespace std;

//Transaction struct for easier processing
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
		<< tr.Price << " "
		<< tr.Shares << " "
		<< tr.TimeStamp << endl;
	return os;
}

//Declaring a global Transaction vector
vector<Transaction> TRANSACTIONS;

//Function Prototypes
void executeTransactions(Queue<Ask>&, Queue<Bid>&);
void printTransaction(Transaction &, string, double);
void saveAskBook(Queue<Ask> &);
void saveBidBook(Queue<Bid> &);
void timeDelay(double);

int main() {
	Queue<Bid> Bids;
	Queue<Ask> Asks;
	executeTransactions(Asks, Bids);
	double delay = 0.5, lastPrice = 114.65;
	string stockTicker = "XYZ", fileName;
	saveAskBook(Asks);
	saveBidBook(Bids);
	system("pause");
	return 0;
}

void printTransaction(Transaction &Tr, string ticker, double lPrice) {
	std::cout << fixed << setprecision(2) << noshowpos
		<< ticker << " " << Tr.Price << setprecision(2)
		<< showpos << " " << (Tr.Price - lPrice) <<
		setprecision(2) << " (" << (1 - (Tr.Price / lPrice)) * 100 << "%)" << endl;
}

void saveAskBook(Queue<Ask> &AskBook) {
	if (AskBook.length() > 0) {
		ofstream ask;
		ask.open("askbook.dat");
		for (int i = 0; i < AskBook.length(); i++) {
			ask << AskBook[i] << endl;
		}
		ask.close();
	}
}

void saveBidBook(Queue<Bid> &BidBook) {
	if (BidBook.length() > 0) {
		ofstream bid;
		bid.open("bidbook.dat");
		for (int i = 0; i < BidBook.length(); i++) {
			bid << BidBook[i] << endl;
		}
		bid.close();
	}
}

void timeDelay(double t) {
	time_t initial, final;
	time_t ltime;
	initial = time(&ltime);
	final = initial + t;
	while (time(&ltime) < final)
	{
	}
	return;
}

void executeTransactions(Queue<Ask> &Asks, Queue<Bid> &Bids) {
	fstream ordersFile;
	ofstream trans;
	long shareDiff;
	double delay = 0.5, lastPrice = 114.65;
	string stockTicker = "XYZ", fileName;
	cout << "Enter the simulation delay in fraction of a second (e.g. 0.1) = ";
	cin >> delay;
	cout << "Enter the ticker of the stock: ";
	cin >> stockTicker;
	cout << "Enter the closing price from yesterday: ";
	cin >> lastPrice;
	cout << "Enter the order data file name: ";
	cin >> fileName;
	ordersFile.open(fileName, ios::in);
	trans.open("trans.dat");
	Order *inputOrder = new Order;
	while (!ordersFile.eof()) {
		// Get an order from the file
		ordersFile >> *inputOrder;
		//Check if the order is a Bid
		if (inputOrder->getActionType() == 1) {
			//If the order is a marker order and the ask book is empty then ignore the order.
			if (inputOrder->getOrderType() == 0 && Asks.length() == 0) {
				trans << "Market Inbalance - Bid order ID: " << inputOrder->getAccountID() << " Volume : " << inputOrder->getNumOfShares() << " - unmatched" << endl;
			}
			//If the ask book is not empty and the order is a market bid or a relevant bid then proceed.
			else if (Asks.length() != 0 && (inputOrder->getOrderPrice() == 0 || Asks[0] <= *inputOrder)) {
				//Check if the Bid has a lower number of shares than the best Ask and create a transaction
				if (Asks[0].getNumOfShares() > inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					shareDiff = Asks[0].getNumOfShares() - inputOrder->getNumOfShares();
					Asks[0].setNumOfShares(shareDiff);
					trans << TRANSACTIONS.back();
					printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
				}
				//Check if the Bid matches the best Ask and create a transaction
				else if (Asks[0].getNumOfShares() == inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					if (Asks.length() > 0)
					Asks.deQueue();
					trans << TRANSACTIONS.back();
					printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
				}
				else {
					//If the Bid has a greater number of shares than the Ask and the ask book is not empty then proceed
					while (inputOrder->getNumOfShares() > 0 && Asks.length() > 0) {
						//If the Bid is not matching with the Ask and the Bid is not a market bid then create a new Bid.
						if (Asks[0] > *inputOrder && inputOrder->getOrderPrice() != 0) {
							Bid *newBid = new Bid(inputOrder->getOrderType(),
								inputOrder->getActionType(),
								inputOrder->getOrderPrice(),
								inputOrder->getNumOfShares(),
								inputOrder->getAccountID());
							Bids.enQueueBid(newBid);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
						}
						//If the Ask has a greater number of shares than the Bid, create a new transaction and adjust the shares
						else if (Asks[0].getNumOfShares() > inputOrder->getNumOfShares()) {
							TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
							shareDiff = Asks[0].getNumOfShares() - inputOrder->getNumOfShares();
							Asks[0].setNumOfShares(shareDiff);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
							trans << TRANSACTIONS.back();
							printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
						}
						//If the Ask has less shares than or equal the incoming Bid then create a transaction and adjust the shares.
						else if (Asks[0].getNumOfShares() <= inputOrder->getNumOfShares()) {
							TRANSACTIONS.push_back(Transaction(inputOrder->getAccountID(), Asks[0].getAccountID(), Asks[0].getOrderPrice(), Asks[0].getNumOfShares(), time(NULL)));
							shareDiff = inputOrder->getNumOfShares() - Asks[0].getNumOfShares();
							inputOrder->setNumOfShares(shareDiff);
							Asks.deQueue();
							trans << TRANSACTIONS.back();
							printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
						}
					}
					//If the ask book runs out then discard the market Bid and log the unexecuted order if the shares left are not 0
					if (inputOrder->getNumOfShares() != 0) {
						trans << "Market Inbalance - Bid order ID: " << inputOrder->getAccountID() << " Volume : " << inputOrder->getNumOfShares() << " - unmatched" << endl;
					}
				}
			}
			else {
				//If the Bid is not compatible and limited then create a new Bid in the bid book
				Bid *newBid = new Bid(inputOrder->getOrderType(),
					inputOrder->getActionType(),
					inputOrder->getOrderPrice(),
					inputOrder->getNumOfShares(),
					inputOrder->getAccountID());
				Bids.enQueueBid(newBid);
			}
		}
		else {
			//If the order is a marker order and the bid book is empty then ignore the order.
			if (inputOrder->getOrderType() == 0 && Bids.length() == 0) {
				trans << "Market Inbalance - Ask order ID: " << inputOrder->getAccountID() << " Volume : " << inputOrder->getNumOfShares() << " - unmatched" << endl;
			}
			//If the bid book is not empty and the order is a market ask or a relevant ask then proceed.
			else if (Bids.length() != 0 && (inputOrder->getOrderPrice() == 0 || Bids[0] >= *inputOrder)) {
				//Check if the Ask has a lower number of shares than the best Bid and create a transaction
				if (Bids[0].getNumOfShares() > inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					shareDiff = Bids[0].getNumOfShares() - inputOrder->getNumOfShares();
					Bids[0].setNumOfShares(shareDiff);
					trans << TRANSACTIONS.back();
					printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
				}
				//Check if the Ask matches the best Bid and create a transaction
				else if (Bids[0].getNumOfShares() == inputOrder->getNumOfShares()) {
					TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
					Bids.deQueue();
					if (Bids.length() > 0)
					trans << TRANSACTIONS.back();
					printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
				}
				else {
					//If the Ask has a greater number of shares than the Bid and the bid book is not empty then proceed
					while (inputOrder->getNumOfShares() > 0 && Bids.length() > 0) {
						//If the Ask is not matching with the Bid and the Ask is not a market ask then create a new Ask.
						if (Bids[0] < *inputOrder && inputOrder->getOrderPrice() != 0) {
							Ask *newAsk = new Ask(inputOrder->getOrderType(),
								inputOrder->getActionType(),
								inputOrder->getOrderPrice(),
								inputOrder->getNumOfShares(),
								inputOrder->getAccountID());
							Asks.enQueueAsk(newAsk);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
						}
						else if (Bids[0].getNumOfShares() > inputOrder->getNumOfShares()) {
							//If the Bid has a greater number of shares than the Ask, create a new transaction and adjust the shares
							TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), inputOrder->getNumOfShares(), time(NULL)));
							shareDiff = Bids[0].getNumOfShares() - inputOrder->getNumOfShares();
							Bids[0].setNumOfShares(shareDiff);
							shareDiff = 0;
							inputOrder->setNumOfShares(shareDiff);
							trans << TRANSACTIONS.back();
							printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
						}
						else if (Bids[0].getNumOfShares() <= inputOrder->getNumOfShares()) {
							//If the Bid has less shares than or equal the incoming Ask then create a transaction and adjust the shares
							TRANSACTIONS.push_back(Transaction(Bids[0].getAccountID(), inputOrder->getAccountID(), Bids[0].getOrderPrice(), Bids[0].getNumOfShares(), time(NULL)));
							shareDiff = inputOrder->getNumOfShares() - Bids[0].getNumOfShares();
							inputOrder->setNumOfShares(shareDiff);
							Bids.deQueue();
							trans << TRANSACTIONS.back();
							printTransaction(TRANSACTIONS.back(), stockTicker, lastPrice);
						}
						
					}
					if (inputOrder->getNumOfShares() != 0) {
						//If the bid book runs out then discard the market Ask and log the unexecuted order if the shares left are not 0
						trans << "Market Inbalance - Ask order ID: " << inputOrder->getAccountID() << " Volume : " << inputOrder->getNumOfShares() << " - unmatched" << endl;
					}
				}
				

			}
			else {
				//If the Ask is not compatible and limited then create a new Ask in the ask book
				Ask *newAsk = new Ask(inputOrder->getOrderType(),
					inputOrder->getActionType(),
					inputOrder->getOrderPrice(),
					inputOrder->getNumOfShares(),
					inputOrder->getAccountID());
				Asks.enQueueAsk(newAsk);
			}
		}
		timeDelay(delay);
	}
	trans.close();
	ordersFile.close();
	std::cout << endl;
}