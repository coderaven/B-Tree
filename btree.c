#include <stdio.h>
#include <math.h>
#define MAX 100

// B-Tree Node Structure
struct node {
    int value[MAX];
    struct node *keys[MAX+1];
    struct node *parent;
    int keyCount;
} *tRoot = NULL;

// Globals
int treeOrder;

// Menu functions
void showMenu();
void doInsert();
void doDelete();
void doSearch();
void doInOrder();

// Tree Operations
struct node* newNode(int value,struct node *parent);
struct node* insertN(int value,struct node *root,struct node *parent);

// Printing
void inOrder(struct node *root);
void levelOrder(struct node *root);

int main(){
    // Initialize
    printf("--- Initialization ---\n");
    printf("B-Tree Order: ");
    scanf("%d",&treeOrder);
    
    // Run menu
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
     
     tRoot = insertN(value,tRoot,NULL);
     
     printf("\n\n\nPress any key to continue...\n");
     getch();
     showMenu();
}

void doDelete(){
     system("cls"); 
     printf("--- Deletion ---\n");
     
     printf("\n\n\nPress any key to continue...\n");
     getch();
     showMenu();
}

void doSearch(){
     int toFind;
     
     system("cls"); 
     printf("--- Search ---\n");
     
     printf("\n\n\nPress any key to continue...\n");
     getch();
     showMenu();
}

void doInOrder(){
     int i;
     
     system("cls"); 
     printf("--- Printing ---\n");
     
     //for (i = 0; i < tRoot->keyCount - 1; i++) printf("%d ", tRoot->value[i]);
     if (tRoot != NULL) inOrder(tRoot);
     else printf("\nThe tree is empty!\n");
     
     printf("--- Level Order ---\n");
     if (tRoot != NULL) levelOrder(tRoot);
     else printf("\nThe tree is empty!\n");
     
     printf("\n\n\nPress any key to continue...\n");
     getch();
     showMenu();
}

// Operations
struct node* newNode(int value,struct node *parent){
       struct node *root = (struct node*)malloc(sizeof(struct node));
       root->value[0] = value;
       root->keyCount = 2;
       root->parent = parent;
       
       int i;
       for (i = 1; i < MAX; i++) {
           root->value[i] = (int)NULL; // Typcast and wrap NULL into an int for equality purposes
           root->keys[i] = NULL;
       }
       
       return root;
}

struct node* insertN(int value,struct node *root,struct node *parent){
       int i = 0, j;
       
       if (root == NULL){ // If the tree doesn't have a value yet
          return newNode(value,parent);
       } else { 
          while(1){ // Loop for inserting data in a node rect
             if ( (void*)root->value[i] != NULL ){ // If there is a value in the current box
                if (value == root->value[i]){ // If the value is already inserted
                   printf("Data Already inserted!\n");
                   break;
                } else if ( value > root->value[i] ){ // if value to be inserted is greater, then proceed to next box
                   //if (root->keys[i+1] != NULL) insertN(value,root->keys[i],root);
                   //else 
                   i++;
                   
                   continue;
                } else { // This is if the value to be inserted is lesser which means, we can put it now
                   //if (root->keys[i] != NULL) insertN(value,root->keys[i],root);
                   
                     for (j = treeOrder - 2; j >= i; j--) root->value[j+1] = root->value[j]; // move everything to the right
                     root->value[i] = value;
                     root->keyCount++;
                     
                     printf("Keys: %d\n",root->keyCount);
                     break;
                   
                }
             } else { // else if the box is null. Insert directly
               root->value[i] = value;
               root->keyCount++;
               
               printf("Keys: %d\n",root->keyCount);
               break;
             }   
             
             i++;       
          } 
          
          if (root->keyCount > treeOrder){ // Overflow
             int left = (treeOrder-1)/2 - 1;  // in Array position
             int right = (treeOrder-1)/2 + 1;
             int mid = (treeOrder-1)/2;
          
             printf("Overflow! Splitting and Promoting...\n");
             struct node *leftHalf = (struct node*)malloc(sizeof(struct node));
             struct node *rightHalf = (struct node*)malloc(sizeof(struct node));
             
             for (i = 0; i <= left; i++){ // Move all left half data to new LeftHalf Box
                 leftHalf = insertN(root->value[i],leftHalf,NULL); // Set the parent to NULL temporarily
             }
             
             for (i = right; i <= treeOrder; i++){ // Move all right half data to new LeftHalf Box
                 rightHalf = insertN(root->value[i],rightHalf,NULL); // pointer arithmethic
             }
             
             struct node *tempRoot = root;
             root = insertN(root->value[mid],parent,parent);
             
             if (parent == NULL){ // Special case if splitted is the tRoot (The very Root)
               leftHalf->parent = root;
               rightHalf->parent = root;
               root->keys[0] = leftHalf;
               root->keys[1] = rightHalf;
             }
             
             // To do : Non special case split and distribute... or if parent has a parent with values
             
             free(tempRoot); // Delete old root node box
          }
       }
       
       return root;
}

// Printing
void inOrder(struct node *root){
     int i;
     if (root == NULL) return;
     else {
          for (i = 0; i < root->keyCount; i++){   // -1 since left and right key of every data box    
            inOrder(root->keys[i]);
            if((void*)root->value[i] != NULL) printf("~%d~\n",root->value[i]);
          }
     }
}

void levelOrder(struct node *root){
     int i;
     if (root == NULL) return;
     else {
          for (i = 0; i < root->keyCount; i++){   // -1 since left and right key of every data box    
            if((void*)root->value[i] != NULL) printf("%d ",root->value[i]);
          }
          
          if (root->parent == NULL) printf("\n");
          else {
               for (i = 0; i < root->parent->keyCount; i++){ // Check if had a right sibling, if none then proceed to next level
                   if (root->parent->keys[i] == root){
                      if (root->parent->keys[i+1] == NULL) printf("\n");
                      break;
                   }
               }
          }
          
          for (i = 0; i < root->keyCount; i++){
            levelOrder(root->keys[i]);
          }
     }
}

