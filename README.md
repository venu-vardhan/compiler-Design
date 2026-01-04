# compiler-Design
<br>
welcome 
<h1>c program sum of odd and even numbers </h1>

#include <stdio.h>
 
void main()
{
    int i, num, odd_sum = 0, even_sum = 0;
 
    printf("Enter the value of num\n");
    scanf("%d", &num);
    for (i = 1; i <= num; i++)
    {
        if (i % 2 == 0)
            even_sum = even_sum + i;
        else
            odd_sum = odd_sum + i;
    }
    printf("Sum of all odd numbers  = %d\n", odd_sum);
    printf("Sum of all even numbers = %d\n", even_sum);
}
<h1>Two sum Problem </h1>
#include <stdbool.h>
#include <stdio.h>

bool twoSum(int arr[], int n, int target){

    for (int i = 0; i < n; i++){

        // For each element arr[i], check every
        // other element arr[j] that comes after it
        for (int j = i + 1; j < n; j++){

            // Check if the sum of the current pair
            // equals the target
            if (arr[i] + arr[j] == target)
                return true;
        }
    }
    
    // If no pair is found after checking
    // all possibilities
    return false;
}

int main(){

    int arr[] = {0, -1, 2, -3, 1};
    int target = -2;
    int n = sizeof(arr) / sizeof(arr[0]);

    // Call the twoSum function and print the result
    if (twoSum(arr, n, target))
        printf("true\n");
    else
        printf("false\n");
  
    return 0;
}
