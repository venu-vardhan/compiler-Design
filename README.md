
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
This error is **100% a syntax / structure issue**, not your algorithm 👍
You’re very close.

---

## ❌ What This Error REALLY Means

```
error: invalid storage class for function ‘__LC_get_cpu_time’
```

👉 `__LC_get_cpu_time()` is **LeetCode’s internal function**.
👉 This error happens **ONLY when your code accidentally breaks the file structure**.

### 🚨 Root Cause

You are missing a **closing brace `}`** somewhere **before** your `separateSquares()` function ends.

Because of that:

* LeetCode’s internal function appears **inside your function**
* C does NOT allow function definitions inside other functions
* Compiler throws this error

---

## ✅ How to Fix It (IMPORTANT)

### ✔️ Step 1: Make sure every `{` has a matching `}`

Especially:

* `areaBelow(...)`
* `separateSquares(...)`
* No extra braces removed or added

---

## ✅ FULLY FIXED & SAFE CODE (COPY EXACTLY)

👉 **Replace your entire submission with this** ⬇️
(Do NOT add anything before or after)

```c
#include <float.h>

double areaBelow(double h, int** squares, int n) {
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        double y = squares[i][1];
        double l = squares[i][2];
        double top = y + l;

        if (h <= y) {
            continue;
        } else if (h >= top) {
            area += l * l;
        } else {
            area += l * (h - y);
        }
    }
    return area;
}

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double totalArea = 0.0;
    double low = DBL_MAX, high = 0.0;

    for (int i = 0; i < squaresSize; i++) {
        double y = squares[i][1];
        double l = squares[i][2];

        totalArea += l * l;
        if (y < low) low = y;
        if (y + l > high) high = y + l;
    }

    double target = totalArea / 2.0;

    for (int i = 0; i < 80; i++) {
        double mid = (low + high) / 2.0;
        double below = areaBelow(mid, squares, squaresSize);

        if (below < target) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return low;
}
```

-

---

````md
# Equal Area Horizontal Line – C Implementation

## 📘 Problem Description

You are given a 2D integer array `squares`, where each  
`squares[i] = [xi, yi, li]` represents a **square** with:

- Bottom-left corner at `(xi, yi)`
- Side length `li`
- Sides parallel to the x-axis

### 🎯 Objective

Find the **minimum y-coordinate** of a horizontal line such that:

- Area of the **union of squares above the line**
- Equals the **area of the union of squares below the line**

> ⚠️ Overlapping areas must be counted **only once**.

The answer is accepted if it is within `1e-5` of the correct value.

---

## 🧠 Approach Summary

1. **Union Area Calculation**
   - Use **Sweep Line Algorithm**
   - Merge overlapping x-intervals
2. **Binary Search on y**
   - Area below y is monotonic
   - Search for y where area below = total / 2
3. **Precision**
   - Binary search with 60 iterations (~1e-6 accuracy)

---

## ⏱️ Time Complexity

- Union Area: `O(n log n)`
- Binary Search: `~60` iterations  
- **Total:** `O(n log n × log precision)`

---

## 💻 C Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITER 60

typedef struct {
    double y;
    int type;          // +1 = add interval, -1 = remove interval
    double x1, x2;
} Event;

/* Sort events by y */
int cmpEvent(const void *a, const void *b) {
    double d = ((Event *)a)->y - ((Event *)b)->y;
    return (d > 0) - (d < 0);
}

/* Sort doubles */
int cmpDouble(const void *a, const void *b) {
    double d = (*(double *)a) - (*(double *)b);
    return (d > 0) - (d < 0);
}

/* Compute union length of x-intervals */
double unionX(double *x, int *cnt, int n) {
    double length = 0, prev = 0;
    int cover = 0;

    for (int i = 0; i < n; i++) {
        if (cover > 0) {
            length += x[i] - prev;
        }
        cover += cnt[i];
        prev = x[i];
    }
    return length;
}

/* Compute union area below Y */
double unionArea(int **squares, int n, double Y) {
    Event *events = malloc(sizeof(Event) * 2 * n);
    int m = 0;

    for (int i = 0; i < n; i++) {
        double x1 = squares[i][0];
        double x2 = squares[i][0] + squares[i][2];
        double y1 = squares[i][1];
        double y2 = fmin(squares[i][1] + squares[i][2], Y);

        if (y2 <= y1) continue;

        events[m++] = (Event){y1, +1, x1, x2};
        events[m++] = (Event){y2, -1, x1, x2};
    }

    qsort(events, m, sizeof(Event), cmpEvent);

    double *xs = malloc(sizeof(double) * 2 * m);
    int *cnt = malloc(sizeof(int) * 2 * m);
    int xsSize = 0;

    double area = 0;
    double prevY = events[0].y;

    for (int i = 0; i < m; ) {
        double curY = events[i].y;
        area += unionX(xs, cnt, xsSize) * (curY - prevY);

        while (i < m && events[i].y == curY) {
            xs[xsSize] = events[i].x1;
            cnt[xsSize++] = events[i].type;

            xs[xsSize] = events[i].x2;
            cnt[xsSize++] = -events[i].type;
            i++;
        }

        qsort(xs, xsSize, sizeof(double), cmpDouble);
        prevY = curY;
    }

    free(events);
    free(xs);
    free(cnt);

    return area;
}

/* Main API */
double separateSquares(int **squares, int squaresSize) {
    double low = 1e18, high = 0;

    for (int i = 0; i < squaresSize; i++) {
        low = fmin(low, squares[i][1]);
        high = fmax(high, squares[i][1] + squares[i][2]);
    }

    double totalArea = unionArea(squares, squaresSize, high);
    double half = totalArea / 2.0;

    for (int i = 0; i < ITER; i++) {
        double mid = (low + high) / 2;
        if (unionArea(squares, squaresSize, mid) < half)
            low = mid;
        else
            high = mid;
    }

    return low;
}
````

---

## 🧪 Example

### Input

```
[[0,0,2],[1,1,1]]
```

### Output

```
1.00000
```
🟦 Maximum Square Hole in a Grid (C Program)

This program calculates the maximum possible square hole area that can be formed in a grid after removing some horizontal and vertical bars.

📌 Problem Overview

You are given:

n horizontal bars and m vertical bars

Arrays hBars[] and vBars[] representing removed bars

The goal is to determine the largest square hole area that can be formed after removing consecutive bars.

🛠️ Approach

Sort the removed bars using qsort.

Find the longest consecutive sequence of removed bars.

The gap size = longest consecutive bars + 1.

The largest square side is the minimum of horizontal and vertical gaps.

Square area = side × side.

💻 C Program Implementation
#include <stdio.h>
#include <stdlib.h>

/* Comparator for qsort */
int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* Function to find the maximum gap after removing bars */
int maxGap(int *bars, int size) {
    qsort(bars, size, sizeof(int), cmp);

    int longest = 1;
    int current = 1;

    for (int i = 1; i < size; i++) {
        if (bars[i] == bars[i - 1] + 1) {
            current++;
        } else {
            if (current > longest)
                longest = current;
            current = 1;
        }
    }

    if (current > longest)
        longest = current;

    return longest + 1;   // gap size = bars + 1
}

/* Main logic */
int maxSquareHole(int n, int m, int *hBars, int hSize, int *vBars, int vSize) {
    int maxHGap = maxGap(hBars, hSize);
    int maxVGap = maxGap(vBars, vSize);

    int side = maxHGap < maxVGap ? maxHGap : maxVGap;
    return side * side;
}

/* Example usage */
int main() {
    int n = 2, m = 1;
    int hBars[] = {2, 3};
    int vBars[] = {2};

    int result = maxSquareHole(n, m, hBars, 2, vBars, 1);
    printf("Maximum square hole area = %d\n", result);

    return 0;
}

▶️ Sample Output
Maximum square hole area = 4

🧪 Example Explanation

Removed horizontal bars: {2, 3} → longest sequence = 2 → gap = 3

Removed vertical bars: {2} → longest sequence = 1 → gap = 2

Square side = min(3, 2) = 2

Area = 2 × 2 = 4

📚 Concepts Used

Arrays

Sorting using qsort

Pointer manipulation

Greedy logic

Time complexity: O(n log n)


---

---






## 📄 License

This repository is **open-source** and intended for:

* Learning

---

### ⭐ If you like this repository, don’t forget to **star it on GitHub!**
