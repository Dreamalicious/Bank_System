#ifndef TRANSACTION_H
#define TRANSACTION_H


#include "Account.h"
#include "IOFile.h"
#include "Money.h"

class Transaction   {
      
      
      private:
              int next;				// variable that points to oldest transaction of 5
              long source[5];			// if transfer source account number
              long destination[5];		// if transfer destination account number
              char type[5];            		// type of Transaction(deposit, withdraw, transfer)
              long amount[5];			// amount of cash used in transaction
      
      public:
             
             Transaction();
             
             void deposit(long);		// deposites the given amount of cash to users account, gets the 
						// amount of money and position of oldest transaction

             void withdraw(long);		// withdraws given amount of cash from users account
             void transfer( long, long , long );// transfers a given amount of cash from source account number 
						// to destination. Informs the file about that transfer.

	     void setCurrentNext(int);		// gets a number and sets pointer to oldest transaction
             void setNext(int);			// set pointer to next oldest transaction
             int getNext();			// gets pointer to oldest transaction

             long getSource(int);		// gets source account number used in a transaction
             long getDestination(int);		// gets destination account number used in a transaction
             char getType(int);			// gets type of transaction(deposit, withdraw, transfer)
             long getAmount(int);		// gets the current amount of cash

             void setType(char , int);		// get type of transaction and write it to instance
             void setSource(long , int);	// get source account number used in transfer and write it to instance
             void setDestination(long , int);	// get destination account number used in transfer and write it to instance
             void setAmount(long , int);	// gets amount of cash used in current transaction

             friend class Account;
             friend class Money;
             friend class Menu;
};

#endif
