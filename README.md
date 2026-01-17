
````md
# 📘 Compiler Design & C Programming Problems

Welcome to the **Compiler Design & Data Structures** repository 👋  
This repository contains **clear and exam-oriented C implementations** of frequently asked **algorithmic and data-structure problems**.

It is ideal for:
- 📚 University exams
- 🧠 Concept revision
- 💻 Coding interview practice
- 🧪 Competitive programming foundations

---

## 📌 Contents

This repository includes:

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

**Check whether any two elements sum to a given target.**

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

## 🌲 Maximum Level Sum of a Binary Tree

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

## 🌳 Maximum Product of Splitted Binary Tree

```c
#define MOD 1000000007

long long totalSum = 0, maxProduct = 0;

long long getTotalSum(struct TreeNode* root) {
    if (!root) return 0;
    return root->val + getTotalSum(root->left) + getTotalSum(root->right);
}

long long dfs(struct TreeNode* root) {
    if (!root) return 0;

    long long sum = root->val + dfs(root->left) + dfs(root->right);
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

**Time:** `O(n × m)`
**Space:** `O(n × m)`

```c
#define NEG_INF -1000000000

int max(int a, int b) { return a > b ? a : b; }
int max3(int a, int b, int c) { return max(a, max(b, c)); }

int maxDotProduct(int* nums1, int n, int* nums2, int m) {
    int dp[n + 1][m + 1];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = NEG_INF;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int prod = nums1[i - 1] * nums2[j - 1];
            int take = prod + (dp[i - 1][j - 1] > 0 ? dp[i - 1][j - 1] : 0);
            dp[i][j] = max3(take, dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}
```

---

## 🟩 Maximal Rectangle in a Binary Matrix

**Time:** `O(rows × cols)`
**Space:** `O(cols)`

```c
#include <stdlib.h>

int largestRectangleArea(int* heights, int n) {
    int* stack = malloc(sizeof(int) * (n + 1));
    int top = -1, maxArea = 0;

    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        while (top >= 0 && h < heights[stack[top]]) {
            int height = heights[stack[top--]];
            int width = top < 0 ? i : i - stack[top] - 1;
            maxArea = maxArea > height * width ? maxArea : height * width;
        }
        stack[++top] = i;
    }
    free(stack);
    return maxArea;
}
```

---

## ⏱ Minimum Time to Visit All Points

**Key Formula:**

```
time += max(|x₂ − x₁|, |y₂ − y₁|)
```

```c
#include <stdlib.h>

int minTimeToVisitAllPoints(int** points, int n) {
    int time = 0;

    for (int i = 1; i < n; i++) {
        int dx = abs(points[i][0] - points[i - 1][0]);
        int dy = abs(points[i][1] - points[i - 1][1]);
        time += dx > dy ? dx : dy;
    }
    return time;
}
```

---

## 🟦 Maximum Square Hole in a Grid

```c
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maxGap(int* bars, int size) {
    qsort(bars, size, sizeof(int), cmp);
    int longest = 1, cur = 1;

    for (int i = 1; i < size; i++) {
        if (bars[i] == bars[i - 1] + 1) cur++;
        else { longest = longest > cur ? longest : cur; cur = 1; }
    }
    longest = longest > cur ? longest : cur;
    return longest + 1;
}

int maxSquareHole(int* hBars, int hSize, int* vBars, int vSize) {
    int side = maxGap(hBars, hSize) < maxGap(vBars, vSize)
               ? maxGap(hBars, hSize)
               : maxGap(vBars, vSize);
    return side * side;
}
```
# 🟦 Maximum Square Area by Removing Fences (C Implementation)

## 📌 Problem Statement

You are given a rectangular field of size **(m − 1) × (n − 1)** with horizontal and vertical fences.

- Horizontal fences are placed at positions given in `hFences`
- Vertical fences are placed at positions given in `vFences`
- The outer boundary fences **cannot be removed**

You may remove some internal fences to form a **square field**.

### 🎯 Objective
Return the **maximum possible area of a square** that can be formed, or `-1` if it is impossible.

> Since the answer may be large, return it modulo **10⁹ + 7**

---

## 🧠 Approach

1. Add **boundary fences** at positions:
   - Horizontal → `1` and `m`
   - Vertical → `1` and `n`

2. Sort all fence positions.

3. Compute **all possible distances (gaps)** between pairs of:
   - Horizontal fences
   - Vertical fences

4. A square is possible if the **same distance exists in both directions**.

5. Choose the **maximum common distance**, square it, and return modulo `10⁹ + 7`.

---

## ✅ C Implementation

```c
#include <stdlib.h>

#define MOD 1000000007LL

// Comparator for sorting
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maximizeSquareArea(int m, int n,
                       int* hFences, int hFencesSize,
                       int* vFences, int vFencesSize) {

    // Include boundary fences
    int hSize = hFencesSize + 2;
    int vSize = vFencesSize + 2;

    int* h = (int*)malloc(hSize * sizeof(int));
    int* v = (int*)malloc(vSize * sizeof(int));

    h[0] = 1;
    h[1] = m;
    for (int i = 0; i < hFencesSize; i++)
        h[i + 2] = hFences[i];

    v[0] = 1;
    v[1] = n;
    for (int i = 0; i < vFencesSize; i++)
        v[i + 2] = vFences[i];

    // Sort fences
    qsort(h, hSize, sizeof(int), cmp);
    qsort(v, vSize, sizeof(int), cmp);

    // Store all horizontal gaps
    int maxHGaps = hSize * hSize;
    long long* hGaps = (long long*)malloc(maxHGaps * sizeof(long long));
    int hGapCount = 0;

    for (int i = 0; i < hSize; i++) {
        for (int j = i + 1; j < hSize; j++) {
            hGaps[hGapCount++] = (long long)(h[j] - h[i]);
        }
    }

    // Find maximum common square side
    long long maxSide = 0;
    for (int i = 0; i < vSize; i++) {
        for (int j = i + 1; j < vSize; j++) {
            long long vGap = (long long)(v[j] - v[i]);
            for (int k = 0; k < hGapCount; k++) {
                if (hGaps[k] == vGap && vGap > maxSide) {
                    maxSide = vGap;
                }
            }
        }
    }

    free(h);
    free(v);
    free(hGaps);

    if (maxSide == 0)
        return -1;

    return (int)((maxSide * maxSide) % MOD);
}

---
# 🟦 Maximum Square Area in Intersecting Rectangles (C)

This repository contains a **C implementation** to solve the problem of finding the **maximum area of a square** that can fit inside the **intersection of at least two rectangles** in a 2D plane.

All rectangles are **axis-aligned** (edges parallel to X and Y axes).

---

## 📘 Problem Statement

You are given:
- `bottomLeft[i] = [ai, bi]` → bottom-left corner of the *i-th* rectangle  
- `topRight[i] = [ci, di]` → top-right corner of the *i-th* rectangle  

Your task is to:
- Find the **largest square** that can fit completely inside the **intersection region of at least two rectangles**
- Return the **maximum square area**
- If **no rectangles intersect**, return `0`

---

## 🧠 Approach

1. Consider **every pair of rectangles**
2. Compute their **intersection rectangle**
3. If the intersection exists:
   - Width = `min(x2) - max(x1)`
   - Height = `min(y2) - max(y1)`
4. The **maximum square side** = `min(width, height)`
5. Square area = `side × side`
6. Keep track of the **maximum area found**

---

## ⏱️ Complexity Analysis

| Type | Complexity |
|-----|------------|
| Time | **O(n²)** |
| Space | **O(1)** |

> Efficient enough since `n ≤ 1000`

---

## ✅ C Implementation

```c
#include <stdio.h>

int maxSquareArea(int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize,
                  int** topRight, int topRightSize, int* topRightColSize) {

    int maxArea = 0;

    for (int i = 0; i < bottomLeftSize; i++) {
        for (int j = i + 1; j < bottomLeftSize; j++) {

            int xLeft   = bottomLeft[i][0] > bottomLeft[j][0] ? bottomLeft[i][0] : bottomLeft[j][0];
            int yBottom = bottomLeft[i][1] > bottomLeft[j][1] ? bottomLeft[i][1] : bottomLeft[j][1];
            int xRight  = topRight[i][0]  < topRight[j][0]  ? topRight[i][0]  : topRight[j][0];
            int yTop    = topRight[i][1]  < topRight[j][1]  ? topRight[i][1]  : topRight[j][1];

            int width  = xRight - xLeft;
            int height = yTop - yBottom;

            if (width > 0 && height > 0) {
                int side = width < height ? width : height;
                int area = side * side;

                if (area > maxArea)
                    maxArea = area;
            }
        }
    }

    return maxArea;
}


## 📚 Concepts Covered

* Arrays & Sorting
* Greedy Algorithms
* Binary Trees
* Dynamic Programming
* Stack-based Optimization
* Geometry & Simulation
* Time–Space Complexity Analysis

---

## 📄 License

This repository is **open-source** and intended for **learning and practice purposes**.

---

⭐ If you found this helpful, **star the repository on GitHub!**
Happy Coding 🚀

```
