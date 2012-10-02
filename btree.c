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

struct nodePosition {
    int key;
    struct node* box;
};

// Globals
int treeOrder;

// Menu functions
void showMenu();
void doInsert();
void doSearch();
void doInOrder();

// Tree Operations
struct node* newNode(int value,struct node *parent);
struct node* insertN(int value,struct node *root,struct node *parent);
struct nodePosition* searchNValue(int value,struct node *root);

// Printing
void inOrder(struct node *root);
void leftRightPrint(struct node *root);

// Utils
int findMax(struct node *root);
int findMin(struct node *root);

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
   printf("     |_____|           |_| |_| |___|___| \n\n");
   printf("     A Project in Data Structures by Raven G. Duran BSIT - 2R1\n");
   
   printf("\n\n");
   printf("(1) Insert a Node\n");
   printf("(2) Search a Node\n");
   printf("(3) Print In Order\n");
   printf("(4) Exit\n");
    
  switch(getch()){
     case '1' : doInsert();   break;
     case '2' : doSearch();   break;
     case '3' : doInOrder();   break;
     default  : exit(0);
  }                            
}

void doInsert(){
     int value;
     
     system("cls"); 
     printf("--- Insertion ---\n");
     printf("Value: ");
      scanf("%d",&value);
     
     
     if (tRoot == NULL) tRoot = insertN(value,tRoot,NULL);
     else insertN(value,tRoot,NULL);
     
     printf("\n\n\nPress any key to continue...\n");
     getch();
     showMenu();
}

void doSearch(){
     int toFind;
     
     system("cls"); 
     printf("--- Search ---\n");
     printf("To Find: ");
     scanf("%d",&toFind);
     
     if (searchNValue(toFind,tRoot) == NULL) printf("Not found!\n");
     else printf("found!\n");
     
     printf("\n\n\nPress any key to continue...\n");
     getch();
     showMenu();
}

void doInOrder(){
     int i;
     
     system("cls"); 
     printf("--- Printing ---\n");
     
     if (tRoot != NULL) inOrder(tRoot);
     else printf("\nThe tree is empty!\n");
     
     printf("--- Left to Right Order ---\n");
     if (tRoot != NULL) leftRightPrint(tRoot);
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
       for (i = 1; i <= treeOrder + 2; i++) {
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
                   if (root->keys[i+1] != NULL && root->keys[i+1]->keyCount < treeOrder + 1 && root->value[i+1] > value) {
                      PUT_RIGHT:
                       root->keys[i+1] = insertN(value,root->keys[i+1],root);
                       break;
                   } else i++;
                   
                   continue;
                } else { // This is if the value to be inserted is lesser which means, we can put it now
                   if (root->keys[i] != NULL && root->keys[i]->keyCount < treeOrder + 1) {
                      PUT_LEFT:
                       root->keys[i] = insertN(value,root->keys[i],root);
                       break;
                   } else {
                     for (j = treeOrder - 2; j >= i; j--) {
                         root->value[j+1] = root->value[j]; // move everything to the right
                         root->keys[j+2] = root->keys[j+1];
                     } 
                     
                     root->value[i] = value;
                     root->keyCount++;
                     
                     printf("Keys: %d\n",root->keyCount);
                     break;
                   }
                   
                }
             } else { // else if the box is null or the last box. Insert directly
               if (root->keys[i] != NULL && root->keys[i]->keyCount < treeOrder + 1) {
                  printf("Succes!\n");
                  goto PUT_LEFT;
               }
               
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
             struct node *leftHalf = NULL;
             struct node *rightHalf = NULL;
             
             for (i = 0; i <= left; i++){ // Move all left half data to new LeftHalf Box
                 leftHalf = insertN(root->value[i],leftHalf,NULL); // Set the parent to NULL temporarily
                 leftHalf->keys[i] = root->keys[i];
             } leftHalf->keys[left+1] = root->keys[left+1];
             
             int j = 0;
             for (i = right; i < treeOrder; i++, j++){ // Move all right half data to new LeftHalf Box
                 rightHalf = insertN(root->value[i],rightHalf,NULL);
                 rightHalf->keys[j] = root->keys[i];
             } rightHalf->keys[j] = root->keys[treeOrder];
            
             
             int pIsNull = parent == NULL ? 1 : 0;
             struct node *tempRoot = root;
             struct node *pParent = pIsNull ? NULL : parent->parent;
             
             parent = insertN(root->value[mid],parent,pParent); 
              
             if (pIsNull){ // Special case if splitted is the tRoot (The very Root)
               leftHalf->parent = parent;
               rightHalf->parent = parent;
               parent->keys[0] = leftHalf;
               parent->keys[1] = rightHalf;
               
               tRoot = parent;
               //free(tempRoot); // Delete old root node box
               
               printf("\n\n");
               inOrder(parent);
               printf("\n\n");
               
               return parent;
               
               
             } else {
               // put left and right half properly
                 int max = findMax(leftHalf); // Max of left half
                 struct nodePosition *position = searchNValue(max,tRoot);
                 
                 if (position != NULL){
                    printf("\nLeft half Max %d is Found at key: %d\n",max,position->key);
                 }
                
                 if (position != NULL){
                    // Find the parent of the current left and right box
                    int max = findMax(leftHalf);
                    for (i = 0; i < position->box->parent->keyCount; i++){
                       if (position->box->parent->keys[i] == position->box){
                          printf("\nLeft half is: %d\n",leftHalf->value[0]);
                          printf("Right half is: %d\n",rightHalf->value[0]);
                          
                          position->box->parent->keys[i]   = leftHalf;
                          position->box->parent->keys[i+1] = rightHalf;
                          
                          printf("Inserting Left half with Max of %d at key %d\n",max,i);
                          printf("Inserting Right half with Max of %d at key %d\n",rightHalf->value[0],i+1);
                          
                          printf("Parent is %d\n",position->box->parent->value[i]);
                    
                          leftHalf->parent = position->box->parent;
                          rightHalf->parent = position->box->parent;
                         
                          if ( position->box->parent->value[i] > tempRoot->value[mid] ) return rightHalf;
                          else return leftHalf;
                          
                          break;
                       }
                    }
                    
                 }
               
               return leftHalf;
             }
             
          }
       }
       
       return root;
}

struct nodePosition* searchNValue(int value,struct node *root){
       int i;
       struct nodePosition *nodeF = NULL;
       if (root == NULL) return NULL;
       else {
          for (i = 0; i < root->keyCount; i++){   // -1 since left and right key of every data box    
            if (root->value[i] == value) {
               nodeF = (struct nodePosition*)malloc(sizeof(struct nodePosition));
               nodeF->box = root;
               nodeF->key = i;
               return nodeF;
            }
            else if (nodeF != NULL) return nodeF;
            else nodeF =  searchNValue(value,root->keys[i]);
          }  
          return nodeF;
       }
}

// Printing
void inOrder(struct node *root){
     int i;
     if (root == NULL) return;
     else {
          //root = root->keys[1]->keys[2];
          for (i = 0; i < root->keyCount + 2; i++){   // -1 since left and right key of every data box    
            inOrder(root->keys[i]);
            if (i < root->keyCount - 1) printf("~%d~\n",root->value[i]);
          }
     }
}

void leftRightPrint(struct node *root){
     int i;
     if (root == NULL) return;
     else {
          for (i = 0; i < root->keyCount - 1; i++){   // -1 since left and right key of every data box    
             printf("%d ",root->value[i]);
          }
          printf("   ");
          if (root->parent == NULL) printf("\n");
          else {
               for (i = 0; i < root->parent->keyCount + 2; i++){ // Check if had a right sibling, if none then proceed to next level
                   if (root->parent->keys[i] == root){
                      if (root->parent->keys[i+1] == NULL) printf("\n");
                      break;
                   }
               }
          }
          
          for (i = 0; i < root->keyCount; i++){
            leftRightPrint(root->keys[i]);
          }
     }
}

int findMax(struct node *root){
    int i, max = root->value[0];
    for (i = 0; i < root->keyCount; i++){
        if (root->value[i] > max) max = root->value[i];
    }
    
    return max;
}

int findMin(struct node *root){
    int i, min = root->value[0];
    for (i = 0; i < root->keyCount; i++){
        if (root->value[i] < min) min = root->value[i];
    }
    
    return min;
}
