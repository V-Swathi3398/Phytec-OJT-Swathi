#include <stdio.h>
int main()

void ascending() {
    int arr[10], i, temp, j;
    
    printf("Enter 10 numbers: ");
    for(i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    } 
    
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10 - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    printf("Sorted array in ascending order: ");
    for(i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    } 
}

