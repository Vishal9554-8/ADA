#include <stdio.h>
#include <stdlib.h>

// Structure to store activities
struct Activity {
    int start, finish;
};

// Compare function for sorting by finish time
int compare(const void *a, const void *b) {
    struct Activity *x = (struct Activity *)a;
    struct Activity *y = (struct Activity *)b;
    return x->finish - y->finish;
}

// Function to select maximum number of activities
void activitySelection(struct Activity act[], int n) {
    // Sort by finish time
    qsort(act, n, sizeof(struct Activity), compare);

    printf("\nSelected activities are (start, finish):\n");

    // Select the first activity
    int i = 0;
    printf("(%d, %d)", act[i].start, act[i].finish);

    // Consider the rest
    for (int j = 1; j < n; j++) {
        if (act[j].start >= act[i].finish) {
            printf(", (%d, %d)", act[j].start, act[j].finish);
            i = j;
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    struct Activity act[n];

    printf("Enter start and finish times of each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d: ", i + 1);
        scanf("%d %d", &act[i].start, &act[i].finish);
    }

    activitySelection(act, n);

    return 0;
}
