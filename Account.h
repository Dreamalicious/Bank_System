#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include "Transaction.h"
#include "IOFile.h"
#include "Money.h"

using namespace std;


class Account
{


private:
	string name;					// holds first name of client

	string surname;					// holds surname of client
  
	string password;				// holds password for current account
  
	long accountNumber;				// holds account number for current account




public:

	void setAccountNumber (long);			// gets an account number writes it to a certain instance

	void setAccountSurname (string);		// gets a surname and writes it to a certain instance

	void setAccountName (string);			// gets a first name and writes it to a certain instance

	void setAccountPass (string);			// gets password and writes it to a certain instance


	long getAccountNumber ();			// gets from a certain instance the account number and returns it
  
	string getAccountSurname ();			// gets from a certain instance the Surname and returns it
  
	string getAccountName ();			//gets from a certain instance the first name and returns it

	string getAccountPass ();			// get from a certain instance the password and returns it
  

	friend class Transaction;
  
	friend class Money;
  
	friend class Menu;


};



#endif
