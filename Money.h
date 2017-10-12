#ifndef MONEY_H
#define MONEY_H

#include "Transaction.h"
#include "Account.h"
#include "IOFile.h"


using namespace std;

class Money {

      private:
              long cash;				// holds current amount of cash

      public:
             void withdrawCash(long);			//gets an amount of cash and subtracts it from current amount of cash
             void depositCash(long);			//gets an amount of cash and add it to current amount of cash

             long getCash();				// gets and returns current amount of cash
             void setCash(long);			// gets and amount of cash and places it in current amount of cash

             bool checkIfNegative(long);		// checks if given amount of cash is a negative number. If a positive
							// amount of cash returns true, if negative returns false
             bool checkOverdraw(long);			// checks if client is able to make that withdraw(or transfer) and is
							// not trying to overdraw. If trying to overdraw returns false else true


             friend class Account;
             friend class Transaction;
             friend class Menu;

};

#endif
