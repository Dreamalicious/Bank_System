#include "Menu.h"

using namespace std;

//searches for password in bank.dat. If found returns true else false.
bool Menu::searchPass(IOFile &io, string pass)
{
     for(int i=0; i<10; i++)
     { 
             if(io.getAccountPass() == pass)					// gets passwords from bank.dat and checks if it's the same with the one we gave
                   return true;

             io.autoMoveCursor();						// else goes to next password
     }
     return false;
}

//gets information about user who logged in and places it in memory
void Menu::initializeCustomer(IOFile &io, Account &acc, Money &mon, Transaction &tr )
{
     char c;
     int counter;
     long tempL;
     string tempS;
     
     tempL = io.getAccountNumber();						// gets account number from bank.dat
     acc.setAccountNumber(tempL);						// writes it to memory
     
     tempS = io.getAccountSurname();						// gets surname of client from bank.dat
     acc.setAccountSurname(tempS);						// writes it to memory
     
     tempS = io.getAccountName();						// gets name of client from bank.dat
     acc.setAccountName(tempS);							// writes it to memory
     
     tempL = io.getMoney();							// gets amount of money client has from bank.dat
     mon.setCash(tempL);							// writes it to memory
     
     counter = io.getNext();							// gets pointer to oldest transaction from bank.dat
     tr.setCurrentNext(counter);						// writes it to memory

     for( int i = 1; i <= 5; i++)						// gets 5 newest transactions from file
     {
	c = io.getType(i);							// gets type of transaction from file

        if(c!='_')
        {
	          tr.setType(c , i);						// write the type of transaction to memory

	          if( c == 'T')							// if it is a transfer
	          {
		    tempL = io.getSource(i);					// get source account number from file
		    tr.setSource(tempL , i);					// write it to memory
		    tempL = io.getDestination(i);				// get destination account number from file
		    tr.setDestination(tempL , i);				// write it to memory
	          }

	tempL = io.getAmount(i);						// get amount of cash used in that transaction from file
	tr.setAmount(tempL , i);						// write it to memory
       }


     } 

}


// function that writes the transfer to file. It is used to update destination account's transactions 
void Menu::setTransferTrans(IOFile &i, Transaction &t)
{
     int in;
     char c;
     long temp;

     
     in = t.getNext();								// get pointer to oldest transaction 	
     in--;									
     
     c = t.getType(in);								// gets type of transaction from memory
     temp = t.getAmount(in);							// get amount of cash that was used in current transaction from memory

     i.setType(c , in);								// writes type of transaction to file
     i.setAmount(temp , in);							// writes amount of cash used in current transaction to file

     temp = t.getSource(in);							// gets source account number from memory
     i.setSource(temp , in);							// writes source account number to file

     temp = t.getDestination(in);						// gets destination account number from memory
     i.setDestination(temp , in);						// writes destination account number to file

     i.setNext(in+1);								// sets pointer to oldest transaction and writes it to file
}


//print information about a customer, Name, Surname and amount of cash 
void Menu::printInfo(Account &acc, Money &mon)
{
     string name, surname;
     long cash;

     name = acc.getAccountName();						// gets client's name from memory
     surname = acc.getAccountSurname();						// gets client's surname from memory
     cash = mon.getCash();							// gets client's balance from memory

     cout << "Name: " << name << endl
          << "Surname: " << surname << endl
          << "Balance: " << cash << endl;
}

// gets an instance of class Account, gets from user the new password 
// he wants to set and in the end calls the "set" function from class
// Account and changes the password.
void Menu::changePass(Account &acc)
{
     string pass;
     cout << "Insert new password: ";
     cin >> pass;

     acc.setAccountPass(pass);
}

// gets an instance of class Money and an instance of class Transaction.
// gets from user the amount of cash he wants to deposit. Checks if user 
// inserted a non negative amount. Writes information about transaction
// at the transaction-instance and at the money instance. Returns true if 
// success or false if user inserts an negative amount of cash.
bool Menu::deposit(Money &mon, Transaction &tr)
{
     long temp = 0;

     cout << "Insert amount of cash you want to deposit: "; // gets amount of cash from user to deposit
     cin >> temp;

     if( !mon.checkIfNegative(temp) )                      // checks if user deposites a negative amount of cash
                 return false;

     tr.deposit(temp);                                    // writes information about transaction in memory

     mon.depositCash(temp);                                // illustrates cash deposit in memory

     return true;
}


// gets an instance of class Money and an instance of class Transaction.
// gets from user the amount of cash he wants to withdraw. Checks if user 
// inserted a non negative amount. Checks if user is trying to overdraw money.
// Writes information about transaction at the transaction-instance and at 
// the money instance. Returns true if success or false if user inserts 
// an negative amount of cash or tries overdrawing.
bool Menu::withdraw(Money &mon, Transaction &tr)
{
     long temp = 0;

     cout << "Insert amount of cash you want to withdraw: "; // gets amount of cash from user to withdraw
     cin >> temp;

     if( !mon.checkIfNegative(temp) )                        // checks if user withdraws a negative amount of cash
                 return false;
     if( !mon.checkOverdraw(temp))                           // checks if user is going to overdraw money
                 return false;

     tr.withdraw(temp);                                     // writes information about transaction in memory

     mon.withdrawCash(temp);                                 // illustrates cash withdraw in memory

     return true;
}

// gets an instance of class IOFile. That class opens bank.dat and allows
// reading and writing to and from file. After it gets the account number
// that user wants to transfer money to. Searches in file if this account
// exists. It returns the account number if it found it, or -1 if didn't.
long Menu::getAccountNumber(IOFile &dest)
{
     long accNumberDest =0;

     cout << "Insert destination Account: ";                 // gets amount of cash from user to transfer to
     cin >> accNumberDest;

     if( !dest.searchAccountNum( (long)accNumberDest) )      // searches for given account number. If found stores
     {                                                       // file position in dest
         cout << "\nAccount not Found\n";
         return -1;
     }
     return accNumberDest;
}

// gets instances of classes Account, Money, Transaction and the account
// number for the destination account. Inside it gets from user the amount
// of cash he wants to transfer.In the end it illustrates the transfer in 
// the memory.Return the amount of cash transfered 
long Menu::transfer(Account &acc, Money &mon, Transaction &tr, long accNumberDest)
{
     long temp;
     long accNumSource;

     cout << "\nInsert amount of cash: ";                     // gets amount of cash from user to be transfered
     cin >> temp;

     if( !mon.checkIfNegative(temp) )                        // checks if user withdraws a negative amount of cash
                 return -1;
     if( !mon.checkOverdraw(temp))                           // checks if user is going to overdraw money
                 return -1;

     accNumSource = acc.getAccountNumber();		     // get account number of source account
     tr.transfer(temp, accNumSource, accNumberDest);         // writes information about transaction in memory

     mon.withdrawCash(temp);                                 // illustrates cash withdraw in memory (source)

     return temp;
}

// gets instances of classes IOFile,  Account, Money, Transaction and the 
// amount of cash that is going to be transfered to the destination account.
// It writes to file the information about current transaction.
void Menu::transferDest(IOFile &dest, Account &acc, Money &mn, Transaction &dest_tr, long cash)
{
     int i=0;
     long accNumberDest, accNumSource;

     accNumSource = acc.getAccountNumber();		      // get account number of source account

     i = dest.getNext();                                      // get position of oldest DESTINATION transaction in bank.dat
     dest_tr.setCurrentNext(i);				      // get oldest transaction number and set it to memory

     accNumberDest = dest.getAccountNumber();
     dest_tr.transfer(cash, accNumSource, accNumberDest);      // writes information about transaction in memory

     dest_tr.setType('T', i);

     mn.depositCash(cash);                                    // illustrates cash deposit in memory (destination)
     cash = mn.getCash();                                     // get total amount of cash from memory
     dest.setMoney(cash);                                     // write total amount of cash to bank.dat

     setTransferTrans(dest, dest_tr);                         // writes information about transaction to bank.dat
}


// Illustrates the transfer of an amount of cash from one account 
// number to another. Creates 3 instances of IOFile, Account, Money
// and Transaction for the destination account. Gets 3 instances for 
// source account.Returns true if success or false if error.
bool Menu::finalTransfer(Account &acc, Money &mon, Transaction &tr )
{
	long caSH, temp;

	IOFile dest(120);
	Transaction dest_tr;
	Money mn;

	temp = getAccountNumber(dest);				// gets destination  account number from user

        if(temp<0)						// checks if not negative
        {
		cout << "Wrong account number\n";
         	sleep(2);
         	return false;
        }

        caSH = transfer(acc, mon, tr, temp);			// illustrates transfer for source account in memory

	if(caSH < 0)						
	{
		cout << "Couldn't transfer cash\n";
		dest.~IOFile();
		return false;
	}

        mn.cash = dest.getMoney();				// gets amount of cash from memory from destination's account instance
	transferDest(dest,acc,mn,dest_tr,caSH);			// illustrates transfer for destination account 

	dest.~IOFile();						// closes connection with file
	return true;
}

// depending on what type of transaction it prints appropriate information
void Menu::chooseWhatPrint( long sc, long d, long a, char c )
{
         char choice = c;

         switch(choice){
                        case 'D':
                                 cout<<"\nDeposit "<< a <<" Euros" << endl;	// prints amount of cash used in deposit
                                 break;
                        case 'W':
                                 cout<<"\nWithdraw "<< a <<" Euros" << endl;	// prints amount of cash used in withdraw
                                 break;
                        case 'T':
                                 cout<<"\nTransfer from "<< sc <<" to "<< d <<" "<< a <<" Euros" << endl;//prints account numbers 
                                 break;						// that are used in that transfer and the amount 
                        default:						// of cash.
                                break;
         };

}

// prints transaction information. Does a 5 loop that goes through the structure that holds transaction information
void Menu::printTransaction(Transaction &tr )
{
     int i;

     long source, destAccNumber, amount;
     char c;

     i = tr.getNext();								// get position of oldest transaction

     for(int j=0; j<5; j++)
     {
             tr.setNext(i);							// set pointer to oldest transaction
             c = tr.getType(j);						// get type of transaction , deposit, withdraw or transfer

             source = tr.getSource(j);						// get account number that money are transfered from
             destAccNumber = tr.getDestination(j);				// get account number that money are transfered to
             amount = tr.getAmount(j);						// get amount of cash that are used in transaction

             chooseWhatPrint( source, destAccNumber, amount,  c );		// print transactions
     }

}

// backup function. Gets a class Account, a class Money and a class Transaction. It creates an instance of
// of class IOFile that creates a connection with bank.dat. It writes password and current amount of cash
// to bank.dat. Also it writes the structure that holds the 5 latest transactions to bank.dat. Returns true
// if success or false if error.
bool Menu::backUp(Account &acc, Money &mon, Transaction &tr)
{
	IOFile io(120);							// create a connection with bank.dat
	int tempNext;
        long accountNum, tempL;
	char c;								// holds type of transaction(deposit, withdraw, transfer)
	string pass;							// holds password
        string initial("________________");
	
	accountNum = acc.getAccountNumber();				// gets account number from an instance of Account
	if(!io.searchAccountNum(accountNum))				// searches in bank.dat for current account number
	{
		cout <<"\n\n***********************\n"
		     << "   Error during backup\n"
		     <<"***********************\n\n";
		return false;
	}

	pass = acc.getAccountPass();					// gets password from instance and write it to buffer
	io.setAccountPass(pass);					// write buffer to right position in bank.dat
	
	tempL = mon.getCash();						// gets amount of cash from instance and write it to buffer
	io.setMoney(tempL);						// write buffer to right position in bank.dat

	for(int j = 1; j <= 5; j++)
	{
		c = tr.getType(j);					// get type of transaction(deposit, withdraw, transfer)

                if(c!='_')
                { 
		         io.setType(c , j);				// write type of transaction to bank.dat

		         if( c == 'T' )					// if transaction is a tranfer
		         {
			       tempL = tr.getSource(j);			// get source account number
			       io.setSource(tempL , j);			// write it to file
			       tempL = tr.getDestination(j);		// get destination account number
			       io.setDestination(tempL , j);		// write it to file
		         }

		  tempL = tr.getAmount(j);				// get amount of cash used in current transaction

                  io.initialAmount(initial, j);			        // initialise position in file, where amount of cash is to be placed
		  io.setAmount(tempL , j);				// write amount of cash to bank.dat

		 // tempNext = tr.getNext();				// get pointer to next oldest transaction
		 // io.setNext( tempNext );				// set next pointer to bank.dat
                }
	
	}

 tempNext = tr.getNext();                            // get pointer to next oldest transaction
 io.setNext( tempNext );                             // set next pointer to bank.dat


	io.~IOFile();							// close connection with file
	return true;							// return success
}


// function that creates the first menu
void Menu::menu1()
{
    int choice;

    while(1){

     system("clear");							// clear screen, for unix systems

     cout << "1.Insert Your Password\n"					// prints first menu
          << "2.Create new Account\n"
	  << "3.Terminate program\n"
	  << "\nEnter your choice: ";

     cin >> choice;							// get user's choice
     cout << endl;
     
     	switch(choice){

                    case 1:
                             if(!login())				// login in to an existing account
			     {
					cout <<"\n\n***********************\n"
					     << "   Error: logging in\n"
					     <<"***********************\n\n";
					sleep(3);	
			     }
				break;
                    case 2:

                             if(!createAccount())			// create a new account 
			     {
					cout <<"\n\n***********************\n"
					     << "   Error: no free space\n"
					     <<"***********************\n\n";
					sleep(3);
			     }
				break;
		    case 3: 
			      cout << "Terminating program...\n" << endl;	// exit program
				exit(0);
                    default:
                            continue;
        }
      }
}

// gets the first free line in bank.dat
// returns true if a free line found
bool Menu::checkPositions(IOFile &io)
{
     for(int i=0; i<10; i++)
     { 
             if(io.getFreePosition())						// checks if line is free
                   return true;

             io.autoMoveCursor();						// moves file cursor to next position
     }
     return false;
}


// creates a new account in file. Return true if success or false if error.
bool Menu::createAccount()
{
     long num;
     string pass;

     IOFile io (120);								// creates a connection with file

     if(!checkPositions(io))							// if there is any free space in file
           return false;

     cout << "Creating a new account" << endl
          << "Insert a  password: ";

     cin >> pass;								// gets the password for the account

     io.setAccountPass(pass);							// writes it to file

     cout << "\n\nInsert an account number: ";
     cin >> num;								// gets the account number 
     io.setAccountNumber(num);							// writes it to file

     cout << "\n\nInsert surname: ";
     cin >> pass;								// gets the client's surname
     io.setAccountSurname(pass);						// writes it to file

     cout << "\n\nInsert name: ";
     cin >> pass;								// gets the client's name
     io.setAccountName(pass);							// writes it to file

     cout << "\n\nInsert starting balance: ";
     cin >> num;								// get the starting balance
     io.setMoney(num);								// writes it to file

     io.setNext(1);								// initializes pointer to oldest transaction

     io.~IOFile();								// closes connection with file
	cout <<   "\n\n***********************\n"
		<< "    Account created!!\n"
		<<"***********************\n\n";
	sleep(3);
	return true;
}


// creates second menu
void Menu::menu2( Account &acc, Money &mon, Transaction &tr)
{
     int choice;

     while(1) {
	system("clear");

     	cout<<"1.Deposit"<< endl
        	<<"2.Withdraw"<< endl
         	<<"3.Print Info"<< endl 
       		<<"4.Change My Password"<< endl
         	<<"5.Transfer"<< endl
         	<<"6.Print Transaction"<< endl
         	<<"7.Exit"<< endl;

	cout << "\nEnter your choice: ";
     	cin >> choice;

	switch(choice){

                    case 1:
                             if(!deposit(mon, tr))					
                                    cout <<   "\n\n***********************\n"
					<< "    Error depositing..\n"
					<<"***********************\n\n";

			     cout<<"\n\nPlease wait...\n";
			     sleep(3);

                             break;
                    case 2:
                             if(!withdraw(mon, tr))
				cout <<   "\n\n***********************\n"
					<< "    Error withdrawing\n"
					<<"***********************\n\n";

                             cout<<"\n\nPlease wait...\n";
			     sleep(3);
                     
                             break;
                    case 3:
                             printInfo(acc, mon);
                             sleep(2);
                             break;
                    case 4:
                             changePass(acc);

			     cout<<"\nYour password changed successfully.\n";
                             sleep(2);
                             break;
                    case 5:
			     if( !finalTransfer( acc,mon,tr ) )
			     {
                        	cout<<"\nTry again...\n";
				break;
                             }

                             cout<<"\nTransfer completed successfully.\n";
                             sleep(2);

                             break;
                    case 6:
                             printTransaction(tr);
                             sleep(2);
                             break;
                    case 7:
                             cout << "\nHave a nice day:D\n\n" << endl;

                                sleep(1);
				backUp(acc, mon, tr);
				menu1();	
                             break;
                    default:
                            cout<<"\nTry again\a\n";
                            sleep(1);
                            break;
        }

      }
}


// creates a connection with the file. Gets a password from user. User has 2 opportunities to
// login successfully. If he logins successfully 3 instances are created and initialized. In 
// the end second menu is called
bool Menu::login()
{
     string pass;

     IOFile io(120);

     for(int i=0; i<2; i++){						// gives 2 opportunities to user to login 

                cout << "Insert Password: ";
                cin >> pass;						// gets password from user

                if( ! searchPass(io, pass) )
		{
			cout << "\nWrong Password\n";
                  	if(i == 2)
                  	{
                        	 return false;
                  	}

                }
                else {
                        Account acc;
                        Money mon;
                        Transaction tr; 

                        initializeCustomer(io ,acc, mon, tr);		// gets data for specific user from file and places them in memory
			io.~IOFile();					// closes connection with file
                        menu2( acc, mon, tr);				// calls second menu
                }
      }

      return true;
}

