#include <stdio.h>
#define MAX 100

// B-Tree Node Structure
struct node {
    int value[MAX];
    struct node *keys[MAX+1];
    struct node *parent;
    int keyCount;
} *tRoot = NULL;

// Menu functions
void showMenu();
void doInsert();
void doDelete();
void doSearch();
void doInOrder();

// Tree Operations
struct node* newNode(int value,struct node *parent);
struct node* insertN(int value,struct node *root,struct node *parent);


int main(){
    showMenu();
    
    getch();
    return 0;
}

// Menus
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
     int value;
     
     system("cls"); 
     printf("--- Insertion ---\n");
     printf("Value: ");
     scanf("%d",&value);
     
     tRoot = insertN(value,tRoot,tRoot);
     
     printf("Press any key to continue...\n");
     getch();
     showMenu();
}

void doDelete(){
     system("cls"); 
     printf("--- Deletion ---\n");
     
     printf("Press any key to continue...\n");
     getch();
     showMenu();
}

void doSearch(){
     system("cls"); 
     printf("--- Search ---\n");
     
     printf("Press any key to continue...\n");
     getch();
     showMenu();
}

void doInOrder(){
     system("cls"); 
     printf("--- Printing ---\n");
     printf("%d\n",tRoot->value[0]);
     
     printf("Press any key to continue...\n");
     getch();
     showMenu();
}

// Operations
struct node* newNode(int value,struct node *parent){
       struct node *root = (struct node*)malloc(sizeof(struct node));
       root->value[0] = value;
       root->keyCount = 2;
       root->parent = parent;
       
       return root;
}

struct node* insertN(int value,struct node *root,struct node *parent){
       if (root == NULL){
          return newNode(value,parent);
       }
}

