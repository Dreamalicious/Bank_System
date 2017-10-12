#include "Transaction.h"

using namespace std;

// constructor
Transaction::Transaction()
{
     next = 1;						// set pointer to oldest transaction to 1st transaction

     for(int i=0; i<5; i++)				
     {
      	source[i] = 0;					// initialize all source account numbers
      	destination[i] = 0;				// initialize all destination account numbers
      	amount[i] =0;					// initialize all amount of cash used in transactions
     }

     for(int j=0; j<5; j++)
	type[j] = '_';					// initialize all types of transactions
}


// deposites the given amount of cash to users account, gets the amount of money and position of oldest transaction
void Transaction::deposit(long a)
{
     int j = 0;

     j = getNext();					// gets pointer to oldest transaction

     type[j-1] = 'D';					// write the type of transaction (deposit)
     amount[j-1] = a;					// write the amount of cash used in deposit

     setNext(j); 					// set pointer to next oldest transaction
}


// informs bank.dat about a withdraw user did
void Transaction::withdraw(long a)
{
     int j = 0;

     j = getNext();					// gets pointer to oldest transaction

     type[j-1] = 'W';					// write the type of transaction (withdraw)
     amount[j-1] = a;					// write the amount of cash used in withdraw

     setNext(j); 					// set pointer to next oldest transaction
}

// transfers a given amount of cash from source account number to destination. Informs the 
// file about that transfer.
void Transaction::transfer( long a, long src, long dest)
{
     int j = 0;
     j = getNext();					// gets pointer to oldest transaction

     type[j-1] = 'T';					// write the type of transaction(transfer)
     amount[j-1] = a;					// write the amount of cash used in transfer
     source[j-1] = src;					// write the source account number
     destination[j-1] = dest;				// write the destination account number

     setNext(j);					// set pointer to next oldest transaction
}

// gets a number and sets pointer to oldest transaction
void Transaction::setCurrentNext(int n)
{
	next = n;					
}

// set pointer to next oldest transaction
void Transaction::setNext(int n)
{
      if( n==5 )					// if next is 5 then set it to 1
          n=1;
      else
          n++;						// else increment next
      next = n;						// save next
}

// gets pointer to oldest transaction
int  Transaction::getNext()
{
     return next;
}

// gets source account number used in a transaction
long Transaction::getSource(int i)
{
     return source[i-1];
}

// gets destination account number used in a transaction
long Transaction::getDestination(int i)
{
     return destination[i-1];
}

// gets type of transaction(deposit, withdraw, transfer)
char Transaction::getType(int i)
{
     return type[i-1];
}

// gets the current amount of cash
long Transaction::getAmount(int i)
{
     return amount[i-1];
}

// get type of transaction and write it to instance
void Transaction::setType( char c , int i)
{ 
     type[i-1] = c;
}

// get source account number used in transfer and write it to instance
void Transaction::setSource( long sc , int i )
{
     source[i-1] = sc;
}

// get destination account number used in transfer and write it to instance
void Transaction::setDestination( long d , int i )
{
     destination[i-1] = d;
}

// gets amount of cash used in current transaction
void Transaction::setAmount( long a , int i )
{
     amount[i-1] = a;
}

