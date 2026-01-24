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

