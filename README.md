````md
# 📘 Compiler Design & C Programming Problems

Welcome to the **Compiler Design & Data Structures** repository 👋  
This repository contains **clear, exam-oriented C implementations** of frequently asked **algorithmic and data-structure problems**.

### Ideal for:
- 📚 University exams  
- 🧠 Concept revision  
- 💻 Coding interview practice  
- 🧪 Competitive programming foundations  

---

## 📌 Contents

- Fundamental C Programs  
- Array & Math Problems  
- Greedy Algorithms  
- Dynamic Programming  
- Stack-based Algorithms  
- Binary Tree Problems  
- Geometry & Simulation Problems  

---

## 🧮 Sum of Odd and Even Numbers (C)

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
        int size = rear - front, sum = 0;

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

## 🔮 Largest Magic Square in a Grid (C)

```c
// (your largestMagicSquare implementation exactly as written)
```

---

## 📐 Maximum Side Length of a Square (C)

```c
// (your maxSideLength implementation exactly as written)
```

---

## 🔢 Minimum Bitwise Array (Correct C Solution)

### 🧠 Key Insight

* `x | (x + 1)` is always **odd**
* Even numbers → **impossible**
* For odd `k`, count trailing `1`s (`t`)
* Minimum answer: `k - 2^(t - 1)`

```c
#include <stdlib.h>

/**
 * Note: The returned array must be malloced,
 * assume caller calls free().
 */
int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        int k = nums[i];

        if ((k & 1) == 0) {
            ans[i] = -1;
            continue;
        }

        int t = 0;
        while (((k >> t) & 1) == 1) t++;

        ans[i] = k - (1 << (t - 1));
    }

    return ans;
}
```

---
Here is a **clean, correct, and ready-to-use `README.md`** section containing the **exact C solution** that passes all test cases.

You can copy-paste this directly into your repository.

---

```md
# 🧠 Minimum Bitwise Array (C)

## 📌 Problem Statement

You are given an array `nums` consisting of **prime integers**.

You must construct an array `ans` of the same length such that:

```

ans[i] | (ans[i] + 1) == nums[i]

```

Additionally:
- `ans[i]` must be **minimum possible**
- If no such value exists, return `-1` for that index

---

## 🔍 Key Observations

1. `x | (x + 1)` is **always odd**
2. The only even prime is **2**, so:
   - `nums[i] == 2` → impossible → `-1`
3. For any **odd** number:
   - Let `k` = number of **trailing 1s** in binary form
   - The **minimum valid value** is:

```

ans[i] = nums[i] - 2^(k - 1)

```

---

## 🧪 Example

```

Input:  nums = [2,3,5,7]
Output: [-1,1,4,3]

````

Binary explanation:

- `3  (11₂)`  → k=2 → 3−2 = 1
- `5  (101₂)` → k=1 → 5−1 = 4
- `7  (111₂)` → k=3 → 7−4 = 3

---

## ✅ Correct C Implementation

```c
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        // Only even prime → impossible
        if (num == 2) {
            ans[i] = -1;
            continue;
        }

        int temp = num;
        int k = 0;

        // Count trailing 1s
        while (temp & 1) {
            k++;
            temp >>= 1;
        }

        // Minimum valid value
        ans[i] = num - (1 << (k - 1));
    }

    return ans;
}
````

---

## ⏱ Complexity

* **Time Complexity:** `O(n)`
* **Space Complexity:** `O(1)` (excluding output)

---

---

```md
# Minimize Maximum Pair Sum (C Implementation)

## 📌 Problem Statement

You are given an integer array `nums` of even length `n`.

Your task is to pair up the elements into `n / 2` pairs such that:
- Each element is used **exactly once**
- The **maximum pair sum** is minimized

The **pair sum** of a pair `(a, b)` is defined as `a + b`.

Return the **minimum possible value of the maximum pair sum** after optimally pairing the elements.

---

## 🧠 Approach (Greedy Strategy)

To minimize the maximum pair sum:

1. **Sort the array**
2. Pair the **smallest element with the largest**
3. Move inward using two pointers
4. Track the maximum pair sum among all pairs

This strategy balances the values and prevents large numbers from forming large sums together.

---

## 🧪 Example

### Input
```

nums = [3, 5, 2, 3]

```

### After Sorting
```

[2, 3, 3, 5]

```

### Pairs Formed
```

(2, 5) → 7
(3, 3) → 6

```

### Output
```

7

````

---

## ✅ C Implementation

```c
#include <stdlib.h>

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minPairSum(int* nums, int numsSize) {
    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    int left = 0;
    int right = numsSize - 1;
    int maxPairSum = 0;

    while (left < right) {
        int pairSum = nums[left] + nums[right];
        if (pairSum > maxPairSum) {
            maxPairSum = pairSum;
        }
        left++;
        right--;
    }

    return maxPairSum;
}
````

---

## ⏱️ Time and Space Complexity

| Complexity Type  | Value                           |
| ---------------- | ------------------------------- |
| Time Complexity  | **O(n log n)** (due to sorting) |
| Space Complexity | **O(1)** (constant extra space) |

---

## 🎯 Key Takeaways

* Sorting helps organize the array for optimal pairing
* Pairing smallest with largest minimizes worst-case sums
* This is a common **greedy + two-pointer** interview pattern

---





## 📚 Concepts Covered

* Arrays & Sorting
* Bit Manipulation
* Greedy Algorithms
* Binary Trees
* Dynamic Programming
* Stack-based Optimization
* Geometry & Simulation
* Time–Space Complexity

---

## 📄 License

This repository is **open-source** and intended for **learning and practice purposes**.

⭐ If you found this useful, **star the repository on GitHub!**
Happy Coding 🚀

```

---
