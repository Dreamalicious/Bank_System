#include <iostream>
#include <fstream>
#include "Account.h"

 using namespace std;

// gets an account number writes it to a certain instance
void Account::setAccountNumber (long x) 
{

	accountNumber = x;

} 

// gets a surname and writes it to a certain instance
void Account::setAccountSurname (string s) 
{

	surname = s;

} 

// gets a first name and writes it to a certain instance
void Account::setAccountName (string s) 
{
  
	name = s;

} 

// gets password and writes it to a certain instance
void Account::setAccountPass (string s)
{
	password = s;
}

// gets from a certain instance the account number and returns it
long Account::getAccountNumber () 
{

	return accountNumber;

}


// gets from a certain instance the Surname and returns it
string Account::getAccountSurname () 
{

	return surname;

}


//gets from a certain instance the first name and returns it
string Account::getAccountName () 
{

	return name;

}


// get from a certain instance the password and returns it
string Account::getAccountPass()
{

	return password;

}