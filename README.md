````md
# 📘 Compiler Design & C Programming Problems

Welcome to the **Compiler Design & Data Structures** repository 👋  
This repository contains **clean, exam-oriented C implementations** of frequently asked **algorithmic and data-structure problems**, written with clarity and correctness in mind.

---

## 🎯 Ideal For

- 📚 University & semester exams  
- 🧠 Concept revision  
- 💻 Coding interview preparation  
- 🧪 Competitive programming foundations  

---

## 📌 Contents

- Fundamental C Programs  
- Array & Math Problems  
- Greedy Algorithms  
- Bit Manipulation  
- Stack-based Algorithms  
- Binary Tree Problems  
- Geometry & Simulation Problems  

---

## 🧮 Sum of Odd and Even Numbers (C)

### 📌 Description
Reads `n` integers and calculates the sum of even and odd numbers separately.

```c
#include <stdio.h>

int main() {
    int n, num, evenSum = 0, oddSum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        if (num % 2 == 0)
            evenSum += num;
        else
            oddSum += num;
    }

    printf("Sum of Even Numbers = %d\n", evenSum);
    printf("Sum of Odd Numbers = %d\n", oddSum);

    return 0;
}
````

---

## 🔢 Two Sum Problem (C)

### 📌 Description

Checks whether any two elements in the array sum to a given target.

```c
#include <stdbool.h>
#include <stdio.h>

bool twoSum(int arr[], int n, int target) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] + arr[j] == target)
                return true;
    return false;
}

int main() {
    int arr[] = {0, -1, 2, -3, 1};
    int target = -2;
    int n = sizeof(arr) / sizeof(arr[0]);

    printf(twoSum(arr, n, target) ? "true\n" : "false\n");
    return 0;
}
```

---

## 🔁 Palindrome Number (C)

### 📌 Description

Determines whether a given integer is a palindrome.

```c
#include <stdbool.h>

bool isPalindrome(int x) {
    if (x < 0) return false;

    int original = x, reverse = 0;
    while (x > 0) {
        reverse = reverse * 10 + (x % 10);
        x /= 10;
    }
    return original == reverse;
}
```

---

## 🌲 Maximum Level Sum of a Binary Tree (C)

### 📌 Description

Finds the level of a binary tree with the maximum sum of node values.

```c
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxLevelSum(struct TreeNode* root) {
    struct TreeNode* queue[10001];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1, bestLevel = 1, maxSum = INT_MIN;

    while (front < rear) {
        int size = rear - front;
        int sum = 0;

        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue[front++];
            sum += node->val;
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }

        if (sum > maxSum) {
            maxSum = sum;
            bestLevel = level;
        }
        level++;
    }
    return bestLevel;
}
```

---

## 🔢 Minimum Bitwise Array (C)

### 📌 Problem Statement

For each `nums[i]`, find the **minimum** `ans[i]` such that:

```
ans[i] | (ans[i] + 1) == nums[i]
```

Return `-1` if no solution exists.

---

### 🧠 Key Observations

* `x | (x + 1)` is always **odd**
* Even numbers → **impossible**
* Count trailing `1`s (`k`)
* Minimum valid value:

```
ans[i] = nums[i] - 2^(k - 1)
```

---

### ✅ C Implementation

```c
#include <stdlib.h>

int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        if ((num & 1) == 0) {
            ans[i] = -1;
            continue;
        }

        int k = 0;
        while ((num >> k) & 1) k++;

        ans[i] = num - (1 << (k - 1));
    }

    return ans;
}
```

---

## 🔗 Minimize Maximum Pair Sum (C)

### 📌 Problem Statement

Pair array elements such that the **maximum pair sum is minimized**.

---

### 🧠 Approach (Greedy)

1. Sort the array
2. Pair smallest with largest
3. Track the maximum pair sum

---

### ✅ C Implementation

```c
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minPairSum(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);

    int left = 0, right = numsSize - 1;
    int maxPairSum = 0;

    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum > maxPairSum)
            maxPairSum = sum;
        left++;
        right--;
    }

    return maxPairSum;
}
```

---

## ⏱ Complexity Summary

| Problem Type     | Time       | Space |
| ---------------- | ---------- | ----- |
| Sorting Based    | O(n log n) | O(1)  |
| Bit Manipulation | O(n)       | O(1)  |
| Tree Traversal   | O(n)       | O(n)  |

---
# 📌 Minimum Difference Between k Scores (C Implementation)

You are given an integer array `nums` where each element represents a student's score,  
and an integer `k` representing the number of students to pick.

Your task is to select **any `k` students** such that the **difference between the highest
and lowest scores** among them is **minimum**.

---

## 🧠 Approach

1. **Sort the array**
2. Use a **sliding window of size `k`**
3. For each window, calculate:  
   `difference = nums[i + k - 1] - nums[i]`
4. Return the **minimum difference**

---

## ⏱ Time & Space Complexity

- **Time Complexity:** `O(n log n)`
- **Space Complexity:** `O(1)`

---

## 💻 C Code Implementation

```c
#include <stdlib.h>

// Comparator function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minimumDifference(int* nums, int numsSize, int k) {

    // If only one student is selected
    if (k == 1) {
        return 0;
    }

    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    int minDiff = 1000000000; // large initial value

    // Sliding window of size k
    for (int i = 0; i + k - 1 < numsSize; i++) {
        int diff = nums[i + k - 1] - nums[i];
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    return minDiff;
}
🧪 Example

Input

nums = [9,4,1,7], k = 2


Output

2

✅ Key Notes

Works for all valid constraints

Handles edge case when k = 1

Exam & interview friendly solution

# 🔍 Minimum Absolute Difference (C Implementation)

This repository contains an **efficient C solution** to the problem **“Minimum Absolute Difference”**, commonly asked in coding interviews and available on platforms like **LeetCode**.

---

## 📌 Problem Statement

Given an array of **distinct integers**, find **all pairs of elements** that have the **minimum absolute difference** among all possible pairs.

### Conditions:
- Each pair `[a, b]` must satisfy:
  - `a < b`
  - Both `a` and `b` belong to the array
  - `b - a` equals the minimum absolute difference
- Return the result in **ascending order**

---

## 🧠 Key Insight

After sorting the array:
- The **minimum absolute difference** will always occur between **adjacent elements**
- This reduces time complexity from `O(n²)` to `O(n log n)`

---

## ⚙️ Algorithm Steps

1. Sort the array using `qsort`
2. Find the minimum difference between adjacent elements
3. Count how many pairs match this minimum difference
4. Allocate memory for the result
5. Store all valid pairs

---

## 💻 C Implementation

```c
#include <stdlib.h>

// Comparator function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced.
 */
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    // Step 1: Sort the array
    qsort(arr, arrSize, sizeof(int), compare);

    // Step 2: Find minimum difference
    int minDiff = __INT_MAX__;
    for (int i = 1; i < arrSize; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    // Step 3: Count valid pairs
    int count = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] - arr[i - 1] == minDiff) {
            count++;
        }
    }

    // Step 4: Allocate memory
    *returnSize = count;
    int** result = (int**)malloc(count * sizeof(int*));
    *returnColumnSizes = (int*)malloc(count * sizeof(int));

    // Step 5: Store result pairs
    int index = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] - arr[i - 1] == minDiff) {
            result[index] = (int*)malloc(2 * sizeof(int));
            result[index][0] = arr[i - 1];
            result[index][1] = arr[i];
            (*returnColumnSizes)[index] = 2;
            index++;
        }
    }

    return result;
}
Example
Input
arr = [4, 2, 1, 3]

Output
[[1,2], [2,3], [3,4]]

⏱️ Complexity Analysis

Time Complexity: O(n log n)

Space Complexity: O(1) extra (excluding output)

✅ Notes

Fully compatible with LeetCode’s C function signature

Handles negative numbers correctly

Caller is responsible for freeing allocated memory

🚀 Author

Written in a clean, exam-oriented and interview-friendly style.

Happy coding! 🎯


---

If you want, I can:
- ✨ Enhance this README with **badges**
- 🖼️ Add **diagram placeholders**
- 📂 Align it with your **existing GitHub repo style**

Just tell me 😄


## 📚 Concepts Covered

* Arrays & Sorting
* Bit Manipulation
* Greedy Algorithms
* Binary Trees
* Queue-based BFS
* Time & Space Complexity

---

## 📄 License

This repository is **open-source** and intended purely for **learning and academic practice**.

⭐ If you find this useful, consider starring the repository.
Happy Coding 🚀

```

