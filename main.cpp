#include <iostream>
#include <fstream>
#include "Menu.h"
#include <string>
using namespace std;

void FileBuilder();


int main(){

   fstream file;
   file.open("bank.txt" );
   
   if( !file.is_open() )
   { 
        FileBuilder();
   }

   system("clear");
   cout<<"\n\nLOADING...\n";
   sleep(2);
    
   cout<<"\nWelcome"<<endl;
   sleep(1);
   
   file.close();
    
    Menu men;
    men.menu1();

return 0;   
}

void FileBuilder() {
     
     fstream file; 
     int i, j;
     bool b = true;
     
     file.open("bank.txt", ios::out);
     
    file<<"CODE |ACCOUNT|   SURNAME     |   NAME     |  CAPITAL       \n";//string of 60 characters
    
    for(j=1; j<=61; j++) {
                               
    	for(i=1; i<60; i++) {
             
             if( (i==6) || (i==14) || (i==30) || (i==43) ) {
                               file<<"|";
                               b=false;
             }
             
             if(b) { 
                   file<<"_";
             }      
    	b=true;
    	}
    file<<"\n";
    }

file.close();
}
