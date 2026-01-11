# compiler-Design
<br>
##welcome 
<h1>c program sum of odd and even numbers </h1>

---

## 🧩 C Program Implementation

```c
#include <stdbool.h>
#include <stdio.h>

bool twoSum(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target)
                return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {0, -1, 2, -3, 1};
    int target = -2;
    int n = sizeof(arr) / sizeof(arr[0]);

    if (twoSum(arr, n, target))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}

<br>

#Two sum problem 
## C program Implemetation 

```  
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


<br>
#palindrome Number
``c-program 
<p>#include <stdbool.h>

bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }

    int original = x;
    int reverse = 0;

    while (x > 0) {
        int digit = x % 10;
        reverse = reverse * 10 + digit;
        x = x / 10;
    }

    return original == reverse;
}
</p>
#include <stdlib.h>
#include <limits.h>

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxLevelSum(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode* queue[10001]; // max nodes constraint
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    int level = 1;
    int maxSum = INT_MIN;
    int answerLevel = 1;
    
    while (front < rear) {
        int size = rear - front;
        int levelSum = 0;
        
        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue[front++];
            levelSum += node->val;
            
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
        
        if (levelSum > maxSum) {
            maxSum = levelSum;
            answerLevel = level;
        }
        
        level++;
    }
    
    return answerLevel;
}
<h1>
 Maximum Product of Splitted Binary Tree
</h1>
<p>
 #include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

long long totalSum = 0;
long long maxProduct = 0;

/* First DFS: calculate total sum */
long long getTotalSum(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    return root->val 
         + getTotalSum(root->left) 
         + getTotalSum(root->right);
}

/* Second DFS: calculate subtree sums and max product */
long long dfs(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    long long leftSum = dfs(root->left);
    long long rightSum = dfs(root->right);

    long long subTreeSum = root->val + leftSum + rightSum;

    long long product = subTreeSum * (totalSum - subTreeSum);
    if (product > maxProduct)
        maxProduct = product;

    return subTreeSum;
}

int maxProductSplit(struct TreeNode* root) {
    totalSum = getTotalSum(root);
    dfs(root);
    return (int)(maxProduct % MOD);
}

</p>
#include <stdio.h>
#include <stdlib.h>

#define NEG_INF -1000000000

int max(int a, int b) {
    return (a > b) ? a : b;
}

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int maxDotProduct(int* nums1, int n, int* nums2, int m) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((m + 1) * sizeof(int));
        for (int j = 0; j <= m; j++) {
            dp[i][j] = NEG_INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int take = nums1[i - 1] * nums2[j - 1];
            if (dp[i - 1][j - 1] > 0)
                take += dp[i - 1][j - 1];

            dp[i][j] = max3(
                take,
                dp[i - 1][j],
                dp[i][j - 1]
            );
        }
    }

    int result = dp[n][m];

    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);

    return result;
}

/* Example usage */
int main() {
    int nums1[] = {2, 1, -2, 5};
    int nums2[] = {3, 0, -6};

    int n = sizeof(nums1) / sizeof(nums1[0]);
    int m = sizeof(nums2) / sizeof(nums2[0]);

    printf("Maximum Dot Product = %d\n", maxDotProduct(nums1, n, nums2, m));
    return 0;
}
<h1>Smallest Subtree with All the Deepest Nodes</h1>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct Result {
    int depth;
    struct TreeNode* node;
};

struct Result dfs(struct TreeNode* root) {
    if (root == NULL) {
        struct Result r = {0, NULL};
        return r;
    }

    struct Result left = dfs(root->left);
    struct Result right = dfs(root->right);

    if (left.depth > right.depth) {
        struct Result r = {left.depth + 1, left.node};
        return r;
    }
    if (right.depth > left.depth) {
        struct Result r = {right.depth + 1, right.node};
        return r;
    }

    struct Result r = {left.depth + 1, root};
    return r;
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    return dfs(root).node;
} 
#Below is a **ready-to-use `README.md` file content** for your **C implementation of Maximal Rectangle**.
You can **copy-paste this directly into `README.md`** in your GitHub repo.

---

# 🟩 Maximal Rectangle in a Binary Matrix (C)

This project implements an efficient solution to find the **largest rectangle containing only `1`s** in a binary matrix using **C language**.

The solution is based on:

* Converting each row into a **histogram**
* Applying the **Largest Rectangle in Histogram** algorithm using a **stack**

---

## 📌 Problem Statement

Given a `rows x cols` binary matrix filled with `'0'` and `'1'`, find the largest rectangle containing only `'1'`s and return its area.

---

## 🧠 Approach

1. Iterate through each row of the matrix
2. Maintain a `heights[]` array that represents histogram heights
3. For each row:

   * If the cell is `'1'`, increment height
   * If the cell is `'0'`, reset height to `0`
4. Compute the **largest rectangle area in histogram** using a stack
5. Track and return the maximum area

---

## ⏱️ Complexity Analysis

* **Time Complexity:** `O(rows × cols)`
* **Space Complexity:** `O(cols)`

---

## ✅ C Implementation

```c
#include <stdio.h>
#include <stdlib.h>

int largestRectangleArea(int* heights, int size) {
    int* stack = (int*)malloc(sizeof(int) * (size + 1));
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= size; i++) {
        int currHeight = (i == size) ? 0 : heights[i];

        while (top != -1 && currHeight < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int w = (top == -1) ? i : i - stack[top] - 1;
            int area = h * w;
            if (area > maxArea)
                maxArea = area;
        }
        stack[++top] = i;
    }

    free(stack);
    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0) return 0;

    int cols = matrixColSize[0];
    int* heights = (int*)calloc(cols, sizeof(int));
    int maxArea = 0;

    for (int i = 0; i < matrixSize; i++) {

        // Build histogram
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }

        // Find largest rectangle in histogram
        int area = largestRectangleArea(heights, cols);
        if (area > maxArea)
            maxArea = area;
    }

    free(heights);
    return maxArea;
}
```

---

## 🧪 Example

**Input**

```
[
 ["1","0","1","0","0"],
 ["1","0","1","1","1"],
 ["1","1","1","1","1"],
 ["1","0","0","1","0"]
]
```

**Output**

```
6
```

---

## 🚀 Key Features

✔ Efficient stack-based solution
✔ Works for large matrices (up to 200×200)
✔ LeetCode accepted approach
✔ Clean and modular C code

---

## 📄 License

This project is open-source and free to use for learning and academic purposes.

---



