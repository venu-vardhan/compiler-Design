# 📘 Compiler Design & C Programming Problems

Welcome to the **Compiler Design & C Programming Problems** repository 👋  
This repository contains **clean, exam-oriented, and interview-friendly C implementations** of frequently asked **algorithmic and data-structure problems**, written with clarity and correctness in mind.

---

## 🎯 Ideal For

- 📚 University & semester exams  
- 🧠 Concept revision  
- 💻 Coding interview preparation  
- 🧪 Competitive programming foundations  

---

## 📌 Topics Covered

- Fundamental C Programs  
- Array & Math Problems  
- Greedy Algorithms  
- Bit Manipulation  
- Stack-based Algorithms  
- Binary Trees & BFS  
- Graph Algorithms (Dijkstra)  
- Geometry & Simulation  

---

## 🧮 Sum of Odd and Even Numbers (C)

### 📌 Description
Reads `n` integers and calculates the sum of **even** and **odd** numbers separately.

```c
#include <stdio.h>

int main() {
    int n, num, evenSum = 0, oddSum = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        if (num % 2 == 0)
            evenSum += num;
        else
            oddSum += num;
    }

    printf("Even Sum = %d\n", evenSum);
    printf("Odd Sum = %d\n", oddSum);
    return 0;
}
```

---

## 🔢 Two Sum Problem (C)

### 📌 Description
Checks whether any two array elements sum to a given target.

```c
#include <stdbool.h>

bool twoSum(int arr[], int n, int target) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] + arr[j] == target)
                return true;
    return false;
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

    int original = x, rev = 0;
    while (x > 0) {
        rev = rev * 10 + (x % 10);
        x /= 10;
    }
    return original == rev;
}
```

---

## 🌲 Maximum Level Sum of a Binary Tree (C)

### 📌 Description
Finds the level with the **maximum sum** of node values using **BFS**.

```c
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxLevelSum(struct TreeNode* root) {
    struct TreeNode* q[10000];
    int front = 0, rear = 0;
    q[rear++] = root;

    int level = 1, bestLevel = 1, maxSum = INT_MIN;

    while (front < rear) {
        int size = rear - front, sum = 0;

        for (int i = 0; i < size; i++) {
            struct TreeNode* cur = q[front++];
            sum += cur->val;
            if (cur->left) q[rear++] = cur->left;
            if (cur->right) q[rear++] = cur->right;
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

### 📌 Problem
For each `nums[i]`, find the **minimum** `ans[i]` such that:

```
ans[i] | (ans[i] + 1) == nums[i]
```

Return `-1` if no solution exists.

### 🧠 Key Insight
- Result must be **odd**
- Count trailing `1`s
- Compute minimum valid value

```c
#include <stdlib.h>

int* minBitwiseArray(int* nums, int n, int* returnSize) {
    int* ans = malloc(sizeof(int) * n);
    *returnSize = n;

    for (int i = 0; i < n; i++) {
        if ((nums[i] & 1) == 0) {
            ans[i] = -1;
            continue;
        }
        int k = 0;
        while ((nums[i] >> k) & 1) k++;
        ans[i] = nums[i] - (1 << (k - 1));
    }
    return ans;
}
```

---

## 🔗 Minimize Maximum Pair Sum (Greedy)

```c
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int minPairSum(int* nums, int n) {
    qsort(nums, n, sizeof(int), cmp);
    int l = 0, r = n - 1, ans = 0;

    while (l < r) {
        int sum = nums[l++] + nums[r--];
        if (sum > ans) ans = sum;
    }
    return ans;
}
```

---

## 📌 Minimum Difference Between k Scores

### 🧠 Approach
- Sort array
- Sliding window of size `k`
- Track minimum difference

```c
int minimumDifference(int* nums, int n, int k) {
    if (k == 1) return 0;
    qsort(nums, n, sizeof(int), cmp);

    int ans = 1e9;
    for (int i = 0; i + k - 1 < n; i++)
        if (nums[i + k - 1] - nums[i] < ans)
            ans = nums[i + k - 1] - nums[i];
    return ans;
}
```

---

## 🔍 Minimum Absolute Difference

### 🧠 Insight
Minimum difference occurs between **adjacent elements after sorting**.

```c
int** minimumAbsDifference(int* arr, int n, int* returnSize, int** col) {
    qsort(arr, n, sizeof(int), cmp);

    int minDiff = INT_MAX, count = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] - arr[i - 1] < minDiff)
            minDiff = arr[i] - arr[i - 1];

    for (int i = 1; i < n; i++)
        if (arr[i] - arr[i - 1] == minDiff)
            count++;

    *returnSize = count;
    *col = malloc(sizeof(int) * count);

    int** res = malloc(sizeof(int*) * count);
    int idx = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] - arr[i - 1] == minDiff) {
            res[idx] = malloc(2 * sizeof(int));
            res[idx][0] = arr[i - 1];
            res[idx][1] = arr[i];
            (*col)[idx++] = 2;
        }
    }
    return res;
}
```

---

## 🔀 Minimum Cost Path with One-Time Edge Reversal

### 🧠 Idea
Transform each edge:
- normal → `u → v (w)`
- reversed → `v → u (2w)`

Then apply **Dijkstra’s algorithm**.

### ⏱ Complexity
- Time: `O((n + m) log n)`
- Space: `O(n + m)`

✔ Efficient  
✔ Exam-friendly  
✔ Interview-safe  

---

## ⏱️ Complexity Summary

| Category | Time | Space |
|--------|------|-------|
| Sorting | O(n log n) | O(1) |
| Trees | O(n) | O(n) |
| Graphs | O(E log V) | O(V + E) |
| Bit Ops | O(n) | O(1) |

---

# 🔤 Minimum Cost to Convert String (C Implementation)

This repository contains a **clear and optimized C solution** for the problem  
**“Minimum Cost to Convert String”**, a graph-based string transformation problem frequently asked in **coding interviews and university exams**.

---

## 📌 Problem Summary

You are given:

- Two strings `source` and `target` of equal length
- Character conversion rules:
  - `original[i] → changed[i]` with cost `cost[i]`
- You can apply **any number of conversions**, including chaining multiple conversions

### 🎯 Goal  
Convert `source` into `target` with the **minimum total cost**, or return `-1` if it is impossible.

---

## 💡 Core Idea

- Each lowercase character (`a` to `z`) is treated as a **node**
- Each conversion rule acts as a **directed weighted edge**
- We compute the **minimum cost between all character pairs**

✔️ This is efficiently solved using the **Floyd–Warshall Algorithm** since there are only **26 characters**.

---

## 🧠 Algorithm Used

### Floyd–Warshall (All-Pairs Shortest Path)

1. Create a `26 × 26` distance matrix  
2. Initialize:
   - `dist[i][i] = 0`
   - Others = ∞  
3. Fill direct conversion costs  
4. Run Floyd–Warshall to allow chained conversions  
5. For each index `i`:
   - Add cost of converting `source[i] → target[i]`
   - If unreachable → return `-1`

---

## ⏱️ Complexity Analysis

| Metric | Value |
|------|------|
| Time | **O(26³ + n)** |
| Space | **O(26²)** |
| Efficient for | `n ≤ 10⁵` |

---

## ✅ C Implementation

```c
#include <limits.h>

#define INF 1000000000000000LL

long long minimumCost(
    char* source,
    char* target,
    char* original, int originalSize,
    char* changed,  int changedSize,
    int* cost,      int costSize
) {
    long long dist[26][26];

    // Initialize distance matrix
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Store minimum direct conversion costs
    for (int i = 0; i < costSize; i++) {
        int u = original[i] - 'a';
        int v = changed[i] - 'a';
        if (cost[i] < dist[u][v]) {
            dist[u][v] = cost[i];
        }
    }

    // Floyd–Warshall algorithm
    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Calculate total conversion cost
    long long totalCost = 0;
    for (int i = 0; source[i] != '\0'; i++) {
        int s = source[i] - 'a';
        int t = target[i] - 'a';

        if (dist[s][t] == INF) {
            return -1;
        }
        totalCost += dist[s][t];
    }

    return totalCost;
}

## 📄 License
This repository is **open-source** and intended for **learning & academic practice**.

⭐ If you find this helpful, consider starring the repository.  
Happy coding 🚀
