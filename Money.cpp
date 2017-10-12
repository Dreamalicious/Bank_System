#include "Money.h"

using namespace std;

//gets an amount of cash and subtracts it from current amount of cash
void Money::withdrawCash(long x)
{
       cash -= x;
}

//gets an amount of cash and add it to current amount of cash
void Money::depositCash(long x)
{
     cash += x;
}

// gets and returns current amount of cash
long Money::getCash()
{
     return cash;
}

// gets and amount of cash and places it in current amount of cash
void Money::setCash(long x)
{
     cash = x;
}

// checks if given amount of cash is a negative number. If a positive
// amount of cash returns true, if negative returns false
bool Money::checkIfNegative( long a )
{
     if(a < 0)
     {
             cout << "Wrong amount of cash" << endl;
             return false;
     }
     return true;
}

// checks if client is able to make that withdraw(or transfer) and is
// not trying to overdraw. If trying to overdraw returns false else true
bool Money::checkOverdraw( long a )
{
     if( cash < a )
     {
             cout << "You reached cash limit" << endl;
             return false;
     }
     return true;
}

