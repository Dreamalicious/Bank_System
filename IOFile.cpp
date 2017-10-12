#include "IOFile.h"


using namespace std;

IOFile::IOFile(long x)
{
      file.open("bank.txt");

      cursorPos = (long)x;

      file.seekp(cursorPos, ios::beg);
}

IOFile::~IOFile()
{
      file.close();
      cursorPos = 0;
}

// moves cursors position 6 lines down, to find the right password
void IOFile::autoMoveCursor()
{
     cursorPos += 6*60;					// 60 characters is one line. 6 lines are used for 1 account
}							// It moves file cursor to next account


// set account password to bank.dat
void IOFile::setAccountPass(string password)
{	
     file.seekp(cursorPos, ios::beg);			// sets file cursor to certain position 
	
     file << password;					// writes the password to bank.dat
}

// set account number to bank.dat
void IOFile::setAccountNumber(long accountNumber)
{
     file.seekp(cursorPos + 6,ios::beg);		// sets file cursor to certain position 
    
     file << accountNumber;				// writes account number to bank.dat
}

// set account Surname to bank.dat
void IOFile::setAccountSurname(string surname)
{
     file.seekp(cursorPos + 14, ios::beg);		// sets file cursor to certain position
     
     file << surname;					// writes surname of client to bank.dat
}

// set account Name to bank.dat
void IOFile::setAccountName(string name)
{
     file.seekp(cursorPos + 30, ios::beg);		// sets file cursor to certain position
     
     file << name;					// writes name of client to bank.dat
}

// set account amount of cash to bank.dat     
void IOFile::setMoney( long cash )
{
     initialAmount("________________", 0);		// initializes space in bank.dat

     file.seekp(cursorPos + 43, ios::beg);		// moves file cursor to certain position
     
     file << cash;					// writes amount of cash to bank.dat
}

// get account password from bank.dat
string IOFile::getAccountPass()
{
     short pos = 0;
     string temp;
     
     temp.empty();					// emptying temporary variable

     file.seekg(cursorPos, ios::beg);			// moves file cursor to certain position
     file >> temp;					// gets from file data

     temp.resize(5);					// resizes data so that we have only valid data

     pos = temp.find_first_of('_');			// checks the size of the password

     if(pos > 0)					// if it's smaller than 5 we resize it again so that 
            temp.resize(pos);				// there are no "_" in temp
     
     return temp;					// returns the password
}  


// get a free position in file
bool IOFile::getFreePosition()
{
	char temp;

	file.seekg(cursorPos, ios::beg);		// moves file cursor to certain position
	file >> temp;					// gets from file data

	if(temp == '_')					// if "_"(means that position is empty) 
		return true;				// returns true

	return false;
}
	
// get account number from bank.dat
long IOFile::getAccountNumber()
{
     long temp = 0;
     file.seekg(cursorPos + 6,ios::beg);		// moves file cursor to certain position
     
     file >> temp;					// gets account number from file

     return temp;					// and returns it
}

// get surname from bank.dat
string IOFile::getAccountSurname()
{
       short pos = 0;
       string temp;
       
       file.seekg(cursorPos + 14,ios::beg);		// moves file cursor to certain position
       
       temp.empty();					// emptying temporary variable
     
       file >> temp;					// gets data from file
     
       temp.resize(15);					// resizes it to hold only "surname" space
       pos = temp.find('_');				// if it's smaller than 15 we resize it again so that  

       if(pos > 0)					// there are no "_" in temp. Now we have only valid
            temp.resize(pos);				// data, the surname of client
     
       return temp;					// returns the surname of the client
}

//get name  from bank.dat
string IOFile::getAccountName()
{
       short pos = 0;
       string temp;
       
       file.seekp(cursorPos + 30,ios::beg);		// moves file cursor to certain position
       
       temp.empty();					// emptying temporary variable
     
       file >> temp;					// gets data from file
       
       temp.resize(12);					// resizes it to hold only "name" space
       pos = temp.find('_');				// if it's smaller than 15 we resize it again so that  	

       if(pos > 0)					// there are no "_" in temp. Now we have only valid
            temp.resize(pos);				// data, the name of client
     
       return temp;					// returns the name of the client
}

//get amount of cash from bank.dat
long IOFile::getMoney()
{
     long temp = 0;
     file.seekg(cursorPos + 43,ios::beg);		// moves file cursor to certain position

     file >> temp;					// gets data from file(amount of money client has)
     return temp;					// returns the amount of cash client has
}


//searches for account number in bank.dat. If found returns true else false.
bool IOFile::searchAccountNum(long pass)
{
     for(int i=0; i<10; i++)
     {
             if(getAccountNumber() == pass)		// checks if the password given is the same with the password in the account
                   return true;	
	     else
	           autoMoveCursor();			// moves to next account
     }
     return false;					// if no match returns false
}

// get pointer "next" to oldest transaction from file
int IOFile::getNext()
{
    int next = 0; 
    long cursor = cursorPos + 60 + 6;			// gets a copy of file-cursor
    
    file.seekg(cursor, ios::beg);			// moves file cursor to certain position
    
    file >> next;					// gets position of oldest transaction from file
    
    return next;					// and returns it
}

// writes pointer "next" to oldest transaction to file
void IOFile::setNext( int n )
{
     long cursor = cursorPos + 60 + 6;			// gets a copy of file-cursor
     
     file.seekp(cursor, ios::beg);			// moves file cursor to certain position

     file << n;						// writes pointer "next" to file
}

// gets type of transaction from file. If it transfer, deposit or withdraw
char IOFile::getType(int i)
{
    char c;
    long cursor = cursorPos + i*60;			// gets a copy of file-cursor
    
    file.seekg(cursor, ios::beg);			// moves file cursor to certain position
    
    file >> c;						// gets the letter D,W or T depending on what transaction it is
    
    return c;						// and returns it
}     

// writes the type of transaction to file. If it transfer, deposit or withdraw
// 'i' is the position in the transactions that the type is going to be written.
// One of the five positions.
void IOFile::setType( char c , int i)
{
     long cursor = cursorPos + i*60;			// gets a copy of file-cursor
     
     file.seekp(cursor, ios::beg);			// moves file cursor to certain position
     
     file << (char)c;					// writes the letter D,W or T depending on what transaction it is to file
}

// writes, the amount of cash used in transaction, to file. If it transfer, deposit or withdraw
// 'i' is the position in the transactions that the amount of cash is going to be written to.
// One of the five positions.
void IOFile::setAmount( long a , int i )
{
     long cursor = cursorPos + i*60 + 43;		// gets a copy of file-cursor
     
     file.seekp(cursor, ios::beg);			// moves file cursor to certain position
     
     file << a;						// writes the amount of cash used in the transaction to file
}

// gets, amount of cash used in transaction, from file.
// 'i' is the position in the transactions that the amount of cash is going to be read from.
// One of the five positions.
long IOFile::getAmount(int i)
{
    long a;
    long cursor = cursorPos + i*60 + 43;		// gets a copy of file-cursor
    
    file.seekg(cursor, ios::beg);			// moves file cursor to certain position
    
    file >> a;						// reads the amount of cash used in the transaction from file
    
    return a;
}


// writes source account number used in transfer, to file. 
// 'i' is the position in the transactions that the account number is going to be written to.
// One of the five positions.
void IOFile::setSource( long sc , int i)
{
     long cursor = cursorPos + i*60 + 14;		// gets a copy of file-cursor
     
     file.seekp(cursor, ios::beg);			// moves file cursor to certain position
     
     file << sc;					// writes the account number used in the transfer to file
}     

// reads source account number used in transfer, from file. 
// 'i' is the position in the transactions that the account number is going to be read from.
// One of the five positions.
long IOFile::getSource(int i)
{
    long sc;
    long cursor = cursorPos + i*60 + 14;		// gets a copy of file-cursor
    
    file.seekg(cursor, ios::beg);			// moves file cursor to certain position
    
    file >> sc;						// reads the account number used in the transfer from file
    
    return sc;						// and returns the account number
}


// writes destination account number used in transfer, to file. 
// 'i' is the position in the transactions that the account number is going to be written to.
// One of the five positions.
void IOFile::setDestination( long d , int i)
{
     long cursor = cursorPos + i*60 + 30;		// gets a copy of file-cursor
     
     file.seekp(cursor, ios::beg);			// moves file cursor to certain position
     
     file << d;						// writes the account number used in the transfer to file
}

// reads destination account number used in transfer, from file. 
// 'i' is the position in the transactions that the account number is going to be read from.
// One of the five positions.
long IOFile::getDestination(int i)
{
    long d;
    long cursor = cursorPos + i*60 + 30;		// gets a copy of file-cursor
    
    file.seekg(cursor, ios::beg);			// moves file cursor to certain position
    
    file >> d;						// reads the account number used in the transfer from file
    
    return d;						// and returns the account number
}

// writes a specific string to the given position in file
void IOFile::initialAmount( string str, int i )
{

    long cursor = cursorPos + i*60 + 43;		// gets a copy of file-cursor

    file.seekp( cursor, ios::beg );			// moves file cursor to certain position

    file << str;					// and writes given string to given line

}


