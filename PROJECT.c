#include <stdio.h>
#include <string.h>

// ---------- Step 1: Fractional Knapsack (profit/price ratio) ----------
void fractionalKnapsack(double profit[], double price[], int n) {
    printf("\n--- Step 1: Fractional Knapsack (Profit to Price Ratio) ---\n");
    printf("Stock\tPrice\tProfit\tProfit/Price Ratio\n");
    for (int i = 0; i < n; i++) {
        double ratio = profit[i] / price[i];
        printf("%c\t%.2f\t%.2f\t%.2f\n", 'A' + i, price[i], profit[i], ratio);
    }
}

// ---------- Step 2: Divide and Conquer (average growth calculation) ----------
double findAvg(double arr[], int low, int high) {
    if (low == high)
        return arr[low];
    int mid = (low + high) / 2;
    double left = findAvg(arr, low, mid);
    double right = findAvg(arr, mid + 1, high);
    return (left + right) / 2.0; // combine step
}

// ---------- Step 3: Backtracking (best combination under risk and budget) ----------
double maxProfit = 0;
int bestSet[10];
int n;

void backtrack(double price[], double profit[], double growth[], double risk[],
               int selected[], int idx, double currProfit, double currCost, double currRisk,
               double budget, double maxRisk) {

    if (currCost > budget || currRisk > maxRisk)
        return;

    // update best combination
    if (currProfit > maxProfit) {
        maxProfit = currProfit;
        for (int i = 0; i < n; i++)
            bestSet[i] = selected[i];
    }

    // explore further choices
    for (int i = idx; i < n; i++) {
        selected[i] = 1;
        double effectiveProfit = profit[i] * growth[i]; // includes growth factor
        backtrack(price, profit, growth, risk, selected, i + 1,
                  currProfit + effectiveProfit, currCost + price[i], currRisk + risk[i],
                  budget, maxRisk);
        selected[i] = 0;
    }
}

// ---------- MAIN ----------
int main() {
    n = 4;
    double price[] = {100, 200, 150, 80};
    double profit[] = {40, 100, 60, 30};
    double risk[] = {0.3, 0.5, 0.4, 0.2};
    double budget = 300, maxRisk = 0.8;

    // Step 1: Fractional Knapsack
    fractionalKnapsack(profit, price, n);

    // Step 2: Divide and Conquer - Historical growth data
    printf("\n--- Step 2: Divide and Conquer (Average Growth Calculation) ---\n");
    double stockA[] = {5, 7, 6, 8};
    double stockB[] = {8, 9, 10, 11};
    double stockC[] = {4, 5, 5, 6};
    double stockD[] = {6, 7, 7, 8};
    double growth[] = {
        findAvg(stockA, 0, 3),
        findAvg(stockB, 0, 3),
        findAvg(stockC, 0, 3),
        findAvg(stockD, 0, 3)
    };

    // print avg growths in descending order
    char names[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (growth[i] < growth[j]) {
                double temp = growth[i]; growth[i] = growth[j]; growth[j] = temp;
                char t = names[i]; names[i] = names[j]; names[j] = t;
            }
        }
    }

    printf("Stock\tAvg Growth\n");
    for (int i = 0; i < n; i++)
        printf("%c\t%.2f\n", names[i], growth[i]);

    // Step 3: Backtracking - choose best combination
    printf("\n--- Step 3: Backtracking (Best Combination under Risk & Budget) ---\n");
    double g[] = {7, 9.5, 5, 7.5}; // using unsorted growth values
    int selected[10] = {0};
    backtrack(price, profit, g, risk, selected, 0, 0, 0, 0, budget, maxRisk);

    printf("\nBest combination of stocks:\n");
    double totalCost = 0, totalRisk = 0;
    for (int i = 0; i < n; i++) {
        if (bestSet[i]) {
            printf("Stock %c included\n", 'A' + i);
            totalCost += price[i];
            totalRisk += risk[i];
        }
    }

    printf("Total Growth-Weighted Profit: %.2f\n", maxProfit);
    printf("Total Cost: %.2f, Total Risk: %.2f\n", totalCost, totalRisk);
    return 0;
}