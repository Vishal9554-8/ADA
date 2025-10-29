#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;time.h&gt;
// Function to perform linear search
void linear_search(int arr[], int size, int target) {
int found = 0;
for (int i = 0; i &lt; size; i++) {
if (arr[i] == target) {
found = 1;
printf(&quot;The element %d is found at index %d\n&quot;, target, i);
break;
}
}
if (!found) {
printf(&quot;The element %d is not found.\n&quot;, target);
}
}
// Function to generate an array with random values
void generate_random_array(int arr[], int size) {
for (int i = 0; i &lt; size; i++) {
arr[i] = rand() % 100000; // Random number between 0 and 99999
}
}
int main() {
int n;

printf(&quot;Enter the size of the array: &quot;);
if (scanf(&quot;%d&quot;, &amp;n) != 1 || n &lt;= 0) {
printf(&quot;Invalid array size.\n&quot;);
return 1;
}
int *arr = (int *)malloc(n * sizeof(int));
if (arr == NULL) {
printf(&quot;Memory allocation failed.\n&quot;);
return 1;
}
srand(time(NULL)); // Seed random number generator
generate_random_array(arr, n);
int key;
printf(&quot;Enter the key to search (0 to 99999): &quot;);
if (scanf(&quot;%d&quot;, &amp;key) != 1 || key &lt; 0 || key &gt;= 100000) {
printf(&quot;Invalid key.\n&quot;);
free(arr);
return 1;
}
int repetitions = 1000;
clock_t start = clock();
for (int i = 0; i &lt; repetitions; i++) {
linear_search(arr, n, key);
}
clock_t end = clock();
double average_time = ((double)(end - start)) / CLOCKS_PER_SEC / repetitions;
printf(&quot;\nAverage time taken per linear search: %f seconds\n&quot;, average_time);
free(arr);
return 0;
}