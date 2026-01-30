````md
# 📘 Compiler Design & C Programming Problems

Welcome to the **Compiler Design & C Programming Problems** repository 👋  
This repository contains **clean, exam-oriented, and interview-friendly C implementations** of frequently asked **algorithmic and data-structure problems**, written with clarity, correctness, and simplicity in mind.

---

## 🎯 Ideal For

- 📚 University & semester examinations  
- 🧠 Concept revision for Compiler Design & Data Structures  
- 💻 Coding interview preparation (C language focus)  
- 🧪 Competitive programming foundations  

---

## 📌 Topics Covered

- Fundamental C Programs  
- Array & Math Problems  
- Greedy Algorithms  
- Bit Manipulation  
- Stack-based Algorithms  
- Binary Trees & BFS  
- Graph Algorithms (Dijkstra, Floyd–Warshall)  
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
````

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

Finds the level with the **maximum sum** of node values using **Breadth-First Search (BFS)**.

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

Return `-1` if no valid value exists.

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

```c
#include <limits.h>

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

Each edge is transformed as:

* Normal direction → cost `w`
* Reversed direction → cost `2w`

Then **Dijkstra’s Algorithm** is applied.

### ⏱ Complexity

* Time: `O((V + E) log V)`
* Space: `O(V + E)`

---

## 🔤 Minimum Cost to Convert String (C)

### 💡 Approach

* Treat characters `a–z` as graph nodes
* Use **Floyd–Warshall Algorithm** for all-pairs shortest paths

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

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            dist[i][j] = (i == j) ? 0 : INF;

    for (int i = 0; i < costSize; i++) {
        int u = original[i] - 'a';
        int v = changed[i] - 'a';
        if (cost[i] < dist[u][v])
            dist[u][v] = cost[i];
    }

    for (int k = 0; k < 26; k++)
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    long long totalCost = 0;
    for (int i = 0; source[i]; i++) {
        int s = source[i] - 'a';
        int t = target[i] - 'a';
        if (dist[s][t] == INF) return -1;
        totalCost += dist[s][t];
    }

    return totalCost;
}
```

# 🧩 LeetCode 2977 – Minimum Cost to Convert String II (C Solution)

This repository contains a **correct and fully accepted C implementation** for  
**LeetCode 2977: Minimum Cost to Convert String II**.

The solution correctly handles:
- ✅ **Multi-step transformations on the same substring**
- ✅ **Disjoint or identical substring operations**
- ✅ **All edge cases and hidden test cases**

---

## 🔍 Problem Summary

You are given:
- Two strings `source` and `target` of equal length
- Transformation rules: `original[i] → changed[i]` with cost `cost[i]`

You can:
- Apply transformations on **disjoint substrings**, or
- Apply **multiple transformations on the same substring**

Your goal is to compute the **minimum total cost** to convert `source` into `target`.

---

## 🧠 Key Idea

The solution uses **three main steps**:

1. **Graph Construction**
   - Treat each substring transformation as a directed edge
2. **Floyd–Warshall Algorithm**
   - Precompute the minimum cost to convert any substring → another substring
   - Allows chaining transformations (e.g., `c → e → b`)
3. **Dynamic Programming**
   - `dp[i]` = minimum cost to convert `source[0..i-1]` → `target[0..i-1]`

---

## ✅ Complete C Implementation

```c
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXM 210
#define MAXN 1005
#define INF  ((long long)1e18)

long long minimumCost(
    char* source,
    char* target,
    char** original,
    int originalSize,
    char** changed,
    int changedSize,
    int* cost,
    int costSize
) {
    int n = strlen(source);

    // Store all unique strings
    char* all[MAXM];
    int cnt = 0;

    int getId(char* s) {
        for (int i = 0; i < cnt; i++)
            if (strcmp(all[i], s) == 0)
                return i;
        all[cnt] = s;
        return cnt++;
    }

    for (int i = 0; i < costSize; i++) {
        getId(original[i]);
        getId(changed[i]);
    }

    // Floyd–Warshall initialization
    static long long dist[MAXM][MAXM];
    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < cnt; j++)
            dist[i][j] = (i == j ? 0 : INF);

    for (int i = 0; i < costSize; i++) {
        int u = getId(original[i]);
        int v = getId(changed[i]);
        if (cost[i] < dist[u][v])
            dist[u][v] = cost[i];
    }

    // Floyd–Warshall
    for (int k = 0; k < cnt; k++)
        for (int i = 0; i < cnt; i++)
            for (int j = 0; j < cnt; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // DP
    static long long dp[MAXN];
    for (int i = 0; i <= n; i++)
        dp[i] = INF;
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] == INF) continue;

        // No operation if characters match
        if (source[i] == target[i])
            if (dp[i] < dp[i + 1])
                dp[i + 1] = dp[i];

        // Try all substrings
        for (int len = 1; i + len <= n; len++) {
            char ssub[MAXN], tsub[MAXN];
            strncpy(ssub, source + i, len);
            strncpy(tsub, target + i, len);
            ssub[len] = tsub[len] = '\0';

            int u = -1, v = -1;
            for (int k = 0; k < cnt; k++) {
                if (strcmp(all[k], ssub) == 0) u = k;
                if (strcmp(all[k], tsub) == 0) v = k;
            }

            if (u != -1 && v != -1 && dist[u][v] < INF) {
                long long newCost = dp[i] + dist[u][v];
                if (newCost < dp[i + len])
                    dp[i + len] = newCost;
            }
        }
    }

    return dp[n] == INF ? -1 : dp[n];
}

---

## ⏱️ Complexity Summary

| Category | Time       | Space    |
| -------- | ---------- | -------- |
| Sorting  | O(n log n) | O(1)     |
| Arrays   | O(n)       | O(1)     |
| Trees    | O(n)       | O(n)     |
| Graphs   | O(E log V) | O(V + E) |
| Bit Ops  | O(n)       | O(1)     |

---

## 📄 License

This repository is **open-source** and intended for **learning and academic practice**.

⭐ If you find this useful, consider starring the repository.
Happy Coding 🚀

```

---
```
