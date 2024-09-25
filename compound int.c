#include <stdio.h>
#include <math.h>

// Function to calculate savings with compound interest
double calculate_savings(double weekly_deposit, double annual_interest_rate, int total_weeks) {
    double balance = 0.0;
    // Convert annual interest rate to weekly rate
    double weekly_interest_rate = pow(1 + annual_interest_rate, 1.0/52) - 1;

    // Loop through each week
    for (int week = 1; week <= total_weeks; week++) {
        // Add the weekly deposit
        balance += weekly_deposit;
        
        // Calculate interest for this week
        double interest = balance * weekly_interest_rate;
        
        // Add interest to the balance
        balance += interest;
        
        // Print the results for this week
        printf("Week %d: Balance = $%.2f, Interest earned this week = $%.2f\n", 
               week, balance, interest);
    }

    // Return the final balance
    return balance;
}

int main() {
    // Set the parameters
    double weekly_deposit = 1000.0;  // Amount deposited each week
    double annual_interest_rate = 0.25;  // Annual interest rate (25%)
    int total_weeks = 52;  // Total number of weeks in a year

    // Call the function to calculate savings
    double final_balance = calculate_savings(weekly_deposit, annual_interest_rate, total_weeks);
    
    // Print the final result
    printf("\nFinal balance after %d weeks (1 year): $%.2f\n", total_weeks, final_balance);

    // Calculate and print total interest earned
    double total_deposited = weekly_deposit * total_weeks;
    double total_interest = final_balance - total_deposited;
    printf("Total amount deposited: $%.2f\n", total_deposited);
    printf("Total interest earned: $%.2f\n", total_interest);

    return 0;
}