#include <stdio.h>

// Menu functions
void showMenu();
void doInsert();
void doDelete();
void doSearch();
void doInOrder();


int main(){
    showMenu();
    
    getch();
    return 0;
}

void showMenu(){
   system("cls"); 
   printf("      _____           _____              \n");
   printf("     | __  |   ___   |_   _|___ ___ ___  \n");
   printf("     | __ -|  |___|    | | |  _| -_| -_| \n");
   printf("     |_____|           |_| |_| |___|___| \n");
   
   printf("\n\n");
   printf("(1) Insert a Node\n");
   printf("(2) Delete a Node\n");
   printf("(3) Search a Node\n");
   printf("(4) Print In Order\n");
   printf("(5) Exit\n");
    
  switch(getch()){
     case '1' : doInsert();   break;
     case '2' : doDelete();   break;
     case '3' : doSearch();   break;
     case '4' : doInOrder();   break;
     default  : exit(0);
  }                            
}

void doInsert(){
     system("cls"); 
     printf("--- Insertion ---\n");
     
     getch();
     showMenu();
}

void doDelete(){
     system("cls"); 
     printf("--- Deletion ---\n");
     
     getch();
     showMenu();
}

void doSearch(){
     system("cls"); 
     printf("--- Search ---\n");
     
     getch();
     showMenu();
}

void doInOrder(){
     system("cls"); 
     printf("--- Printing ---\n");
     
     getch();
     showMenu();
}
