
````md
# 📘 Compiler Design – C Programming Problems

Welcome to the **Compiler Design & Data Structures** repository 👋  
This repository contains **C language implementations** of commonly asked algorithmic and data-structure problems, written clearly for **learning, practice, and exams**.

---

## 👋 Welcome

This project includes:
- Fundamental C programs
- Popular algorithm problems
- Binary Tree problems
- Dynamic Programming solutions
- Stack-based problems

---

## 🧮 Sum of Odd and Even Numbers (C Program)

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

### 🔹 Problem Statement

Check whether any two numbers in the array add up to a given target.

### 🔹 C Implementation

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

## 🌲 Maximum Level Sum of a Binary Tree

```c
#include <stdlib.h>
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxLevelSum(struct TreeNode* root) {
    if (!root) return 0;

    struct TreeNode* queue[10001];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1, maxSum = INT_MIN, answerLevel = 1;

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
            answerLevel = level;
        }
        level++;
    }

    return answerLevel;
}
```

---

## 🌳 Maximum Product of Splitted Binary Tree

```c
#include <stdlib.h>

#define MOD 1000000007

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

long long totalSum = 0, maxProduct = 0;

long long getTotalSum(struct TreeNode* root) {
    if (!root) return 0;
    return root->val + getTotalSum(root->left) + getTotalSum(root->right);
}

long long dfs(struct TreeNode* root) {
    if (!root) return 0;

    long long left = dfs(root->left);
    long long right = dfs(root->right);
    long long sum = root->val + left + right;

    long long product = sum * (totalSum - sum);
    if (product > maxProduct) maxProduct = product;

    return sum;
}

int maxProductSplit(struct TreeNode* root) {
    totalSum = getTotalSum(root);
    dfs(root);
    return maxProduct % MOD;
}
```

---

## 📊 Maximum Dot Product of Two Subsequences

```c
#include <stdio.h>
#include <stdlib.h>

#define NEG_INF -1000000000

int max(int a, int b) { return a > b ? a : b; }
int max3(int a, int b, int c) { return max(a, max(b, c)); }

int maxDotProduct(int* nums1, int n, int* nums2, int m) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));

    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((m + 1) * sizeof(int));
        for (int j = 0; j <= m; j++)
            dp[i][j] = NEG_INF;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int take = nums1[i-1] * nums2[j-1];
            if (dp[i-1][j-1] > 0) take += dp[i-1][j-1];

            dp[i][j] = max3(take, dp[i-1][j], dp[i][j-1]);
        }
    }

    int result = dp[n][m];

    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);

    return result;
}
```

---

## 🌿 Smallest Subtree with All Deepest Nodes

```c
struct Result {
    int depth;
    struct TreeNode* node;
};

struct Result dfs(struct TreeNode* root) {
    if (!root) return (struct Result){0, NULL};

    struct Result l = dfs(root->left);
    struct Result r = dfs(root->right);

    if (l.depth > r.depth) return (struct Result){l.depth + 1, l.node};
    if (r.depth > l.depth) return (struct Result){r.depth + 1, r.node};

    return (struct Result){l.depth + 1, root};
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    return dfs(root).node;
}
```

---

## 🟩 Maximal Rectangle in a Binary Matrix (C)

### ⏱ Complexity

* **Time:** `O(rows × cols)`
* **Space:** `O(cols)`

```c
#include <stdio.h>
#include <stdlib.h>

int largestRectangleArea(int* heights, int size) {
    int* stack = (int*)malloc(sizeof(int) * (size + 1));
    int top = -1, maxArea = 0;

    for (int i = 0; i <= size; i++) {
        int curr = (i == size) ? 0 : heights[i];

        while (top != -1 && curr < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int w = (top == -1) ? i : i - stack[top] - 1;
            if (h * w > maxArea) maxArea = h * w;
        }
        stack[++top] = i;
    }

    free(stack);
    return maxArea;
}
```

---

```md
# Minimum Time Visiting All Points (C)

## 📌 Problem Statement

On a 2D plane, there are `n` points with integer coordinates:

```

points[i] = [xi, yi]

```

You must visit **all points in the given order**.

### ⏱ Movement Rules
In **1 second**, you can:
- Move **1 unit vertically**
- Move **1 unit horizontally**
- Move **diagonally** (1 unit vertically + 1 unit horizontally)

You may pass through other points, but only visiting in order counts.

---

## 🧠 Key Observation

To move from point `(x1, y1)` to `(x2, y2)`:

- Horizontal distance = `|x2 - x1|`
- Vertical distance = `|y2 - y1|`

Using diagonal moves efficiently:

```

Minimum Time = max(|x2 - x1|, |y2 - y1|)

````

Diagonal moves reduce both distances in one second.

---

## 🧩 Algorithm

1. Initialize `time = 0`
2. Loop through consecutive points
3. For each pair:
   - Compute `dx = abs(x2 - x1)`
   - Compute `dy = abs(y2 - y1)`
   - Add `max(dx, dy)` to `time`
4. Return `time`

---

## ✅ C Implementation

```c
#include <stdlib.h>

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize) {
    int time = 0;

    for (int i = 1; i < pointsSize; i++) {
        int x1 = points[i - 1][0];
        int y1 = points[i - 1][1];
        int x2 = points[i][0];
        int y2 = points[i][1];

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        time += (dx > dy) ? dx : dy;
    }

    return time;
}
````

---

## 🧪 Example

### Input

```
points = [[1,1],[3,4],[-1,0]]
```

### Output

```
7
```

### Explanation

* Time from `[1,1] → [3,4]` = 3 seconds
* Time from `[3,4] → [-1,0]` = 4 seconds
* Total = **7 seconds**

---

## ⏱ Time & Space Complexity

| Complexity | Value |
| ---------- | ----- |
| Time       | O(n)  |
| Space      | O(1)  |

---

## 🏷 Tags

* Greedy
* Geometry
* Array
* Simulation

---


---


```



## 📄 License

This repository is **open-source** and intended for:

* Learning

---

### ⭐ If you like this repository, don’t forget to **star it on GitHub!**
