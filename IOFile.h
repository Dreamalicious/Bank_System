#ifndef IOFILE_H
#define IOFILE_H

#include <fstream>
#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include "Transaction.h"
#include "Account.h"
#include "Money.h"
using namespace std;

class IOFile {
      
      private:
              long cursorPos;					// position of cursor in file
              fstream file;					// instance of fstream
              
              
      public:
             IOFile(long x);					// constructor, opens connection with file
             ~IOFile();						// destructor, closes connection with file
             
             void autoMoveCursor();                               // moves cursor to find the right password

             void setAccountPass(string);                         // sets password in file bank.txt
             void setAccountName(string);                         // sets name in file bank.txt
             void setAccountSurname(string);                      // sets surname in file bank.txt
             void setAccountNumber(long);                         // sets account number in file bank.txt
             void setMoney(long);

             string getAccountPass();				  // get account password from bank.txt
             string getAccountName();				  // get account name from bank.txt
             string getAccountSurname();			  // get account surname from bank.txt
             long getAccountNumber();				  // get account number from bank.txt
             long getMoney();					  // get amount of cash available in this account from bank.txt

             bool searchAccountNum(long);			  // search for an account number in bank.txt

             int getNext();					  // get number of oldest transaction in the list of 5 in bank.txt
             void setNext( int );				  // set number of oldest transaction in the list of 5 in bank.txt

             char getType(int );				  // gets type of transaction from file. If it transfer, deposit 
								  //or withdraw
             void setType(char , int);				// writes the type of transaction to file. If it transfer, deposit or
								// withdraw 'i' is the position in the transactions that the type is
								// going to be written. One of the five positions.


             void setAmount(long , int);			// writes, the amount of cash used in transaction, to file. If it
								// transfer, deposit or withdraw 'i' is the position in the transactions
								// that the amount of cash is going to be written to. One of the five
								// positions.

             long getAmount(int);				// gets, amount of cash used in transaction, from file.
								// 'i' is the position in the transactions that the 
								// amount of cash is going to be read from. One of the five positions.

             void initialAmount(string, int);			// writes a specific string to the given position in file

             void setSource(long, int);				// writes source account number used in transfer, to file. 
								// 'i' is the position in the transactions that the account 
								// number is going to be written to. One of the five positions.
             
	     long getSource(int);				// reads source account number used in transfer, from file. 
								// 'i' is the position in the transactions that the account 
								// number is going to be read from. One of the five positions.

             void setDestination(long, int);			// writes destination account number used in transfer, to file. 
								// 'i' is the position in the transactions that the account 
								// number is going to be written to. One of the five positions.

             long getDestination(int);				// reads destination account number used in transfer, from file. 
								// 'i' is the position in the transactions that the account 
								// number is going to be read from. One of the five positions.

	     bool getFreePosition();


             friend class Menu;
             friend class Account;
             friend class Transaction;
             friend class Money;
};

#endif              
