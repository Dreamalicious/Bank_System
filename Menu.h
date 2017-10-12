#ifndef MENU_H
#define MENU_H

#include "Transaction.h"
#include "Account.h"
#include "IOFile.h"
#include "Money.h"
#include <string>
#include <stdlib.h>

using namespace std;

class Menu{

      private:
              char choice; //User first choice

      public:

        void menu1(); 
	
        bool checkPositions(IOFile & );
	
	bool createAccount();

	bool login();

	void menu2(Account &, Money &, Transaction &);

        bool searchPass(IOFile &, string);

	void initializeCustomer(IOFile &, Account &, Money &, Transaction &);

	void printInfo(Account &, Money &);

	void changePass(Account &);

	void transferDest(IOFile &, Account & , Money & , Transaction &, long);

	long getAccountNumber(IOFile &);

	bool finalTransfer( Account &, Money &, Transaction &);

	bool deposit(Money &, Transaction &);

	bool withdraw(Money &, Transaction &);

	long transfer(Account &, Money &, Transaction &, long );

	void setTransferTrans(IOFile &, Transaction &);

	void printTransaction(Transaction  &);

	void chooseWhatPrint( long , long , long , char  );

	bool backUp(Account &, Money &, Transaction &);

        bool checkIT( string *, string );

        void alreadyExist( IOFile &,  string * );


};

#endif
