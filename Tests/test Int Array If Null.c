#include <stdio.h>

int main(){
    int a[10];
    a[0] = (int)NULL;
    ((void*)a[0] == NULL) ? printf("NULL!\n") : printf("Not NULL!\n");
    
    printf("%d\n",&a[0]);
    
    getch();
    return 0;
}
