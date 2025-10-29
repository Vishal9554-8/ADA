#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------- STRUCTURE FOR ITEMS ----------
struct Item {
    int value, weight;
    float ratio;
};

// ---------- FUNCTION FOR FRACTIONAL KNAPSACK (GREEDY) ----------
int compare(const void *a, const void *b) {
    struct Item *item1 = (struct Item *)a;
    struct Item *item2 = (struct Item *)b;
    if (item2->ratio > item1->ratio) return 1;
    else if (item2->ratio < item1->ratio) return -1;
    return 0;
}

float fractionalKnapsack(struct Item items[], int n, int W) {
    qsort(items, n, sizeof(struct Item), compare);

    float totalValue = 0.0;
    int curWeight = 0;

    for (int i = 0; i < n; i++) {
        if (curWeight + items[i].weight <= W) {
            curWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            int remain = W - curWeight;
            totalValue += items[i].value * ((float)remain / items[i].weight);
            break;
        }
    }
    return totalValue;
}

// ---------- FUNCTION FOR 0/1 KNAPSACK (DYNAMIC PROGRAMMING) ----------
int max(int a, int b) { return (a > b) ? a : b; }

int knapSack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    return K[n][W];
}

// ---------- MAIN FUNCTION ----------
int main() {
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int value[n], weight[n];
    struct Item items[n];

    printf("Enter the values and weights of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d value and weight: ", i + 1);
        scanf("%d %d", &value[i], &weight[i]);
        items[i].value = value[i];
        items[i].weight = weight[i];
        items[i].ratio = (float)value[i] / weight[i];
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    // ---------- FRACTIONAL KNAPSACK ----------
    clock_t start1 = clock();
    float maxValFractional = fractionalKnapsack(items, n, W);
    clock_t end1 = clock();

    double timeFractional = (double)(end1 - start1) / CLOCKS_PER_SEC;

    // ---------- 0/1 KNAPSACK ----------
    clock_t start2 = clock();
    int maxVal01 = knapSack(W, weight, value, n);
    clock_t end2 = clock();

    double timeDP = (double)(end2 - start2) / CLOCKS_PER_SEC;

    // ---------- RESULTS ----------
    printf("\n-----------------------------------------------\n");
    printf("Fractional Knapsack (Greedy): %.2f\n", maxValFractional);
    printf("Time Taken (Greedy): %lf seconds\n", timeFractional);
    printf("-----------------------------------------------\n");
    printf("0/1 Knapsack (Dynamic Programming): %d\n", maxVal01);
    printf("Time Taken (DP): %lf seconds\n", timeDP);
    printf("-----------------------------------------------\n");

    printf("\n(Use the recorded times to plot a graph comparing time complexities.)\n");
    printf("Greedy => O(n log n), DP => O(nW)\n");
    printf("Space: Greedy O(n), DP O(nW)\n");

    return 0;
}
