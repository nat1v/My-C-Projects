#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Global variables to store polynomial information
int degree;
double *coefficients;
int *signs; // Array to store signs: 1 for positive, -1 for negative

// Function to evaluate the polynomial for a given x
double function(double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += signs[i] * coefficients[i] * pow(x, i);
    }
    return result;
}

// Function to display the polynomial equation
/*
void displayEquation() {
    printf("f(x) = ");
    int first_term = 1;
    
    for (int i = degree; i >= 0; i--) {
        if (coefficients[i] == 0) continue;
        
        if (signs[i] > 0 && !first_term) {
            printf("+ ");
        } else if (signs[i] < 0) {
            printf("- ");
        }
        
        if (i == 0) {
            printf("%.2f ", coefficients[i]);
        } else if (i == 1) {
            if (coefficients[i] == 1) {
                printf("x ");
            } else {
                printf("%.2fx ", coefficients[i]);
            }
        } else {
            if (coefficients[i] == 1) {
                printf("x^%d ", i);
            } else {
                printf("%.2fx^%d ", coefficients[i], i);
            }
        }
        
        first_term = 0;
    }
    printf("= 0\n");
}
*/
int main() {
    double a, b, m, h;
    double epsilon;
    int max_iterations, n = 1;
    char sign_choice;
    
    // Get polynomial degree
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &degree);
    
    // Allocate memory for coefficients and signs
    coefficients = (double*)malloc((degree + 1) * sizeof(double));
    signs = (int*)malloc((degree + 1) * sizeof(int));
    
    if (coefficients == NULL || signs == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Get coefficients and signs
    printf("Enter the coefficients and signs from highest to lowest degree:\n");
    for (int i = degree; i >= 0; i--) {
        if (i == degree) {
            printf("Coefficient of x^%d: ", i);
            scanf("%lf", &coefficients[i]);
            
            // For highest degree term, ask for sign only if it's not the only term
            if (degree > 0) {
                printf("Sign for next term (+ or -): ");
                scanf(" %c", &sign_choice);
                signs[i] = 1; // Highest degree term is always positive in this display
            } else {
                signs[i] = 1;
            }
        } else {
            // The sign for this term was selected in the previous iteration
            signs[i] = (sign_choice == '+') ? 1 : -1;
            
            printf("Coefficient of x^%d: ", i);
            scanf("%lf", &coefficients[i]);
            
            // Get sign for next term if not the last term
            if (i > 0) {
                printf("Sign for next term (+ or -): ");
                scanf(" %c", &sign_choice);
            }
        }
    }
    
    // Display the equation
  //  displayEquation();
    
    // Get interval endpoints
    printf("Enter the interval [a, b]:\n");
    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    
    // Calculate and display function values
    double fa = function(a);
    double fb = function(b);
    printf("f(%.4f) = %.4f, f(%.4f) = %.4f\n", a, fa, b, fb);
    
    // Check if f(a) * f(b) < 0
    if (fa * fb >= 0) {
        printf("Error: f(a) * f(b) must be < 0\n");
        printf("This means the function must have different signs at points a and b.\n");
        printf("Try different interval values.\n");
        free(coefficients);
        free(signs);
        return 1;
    }
    
    // Get desired accuracy
    printf("Enter the desired accuracy (epsilon): ");
    scanf("%lf", &epsilon);
    
    // Get maximum iterations
    printf("Enter maximum number of iterations: ");
    scanf("%d", &max_iterations);
    
    printf("\nBisection Method Results\n");
    printf("-------------------------------\n");
    printf("n\ta\t\tb\t\tm\t\tf(m)\n");
    printf("-------------------------------\n");
    
    // Bisection method
    do {
        // Calculate midpoint
        m = (a + b) / 2;
        
        // Calculate half interval
        h = fabs(b - a) / 2;
        
        // Calculate function value at midpoint
        double fm = function(m);
        
        // Print current iteration values
        printf("%d\t%.6f\t%.6f\t%.6f\t%.6f\n", n, a, b, m, fm);
        
        // Check if we found exact root
        if (fabs(fm) < epsilon) {
            break;
        }
        
        // Update interval based on where sign change occurs
        if (function(a) * fm < 0) {
            b = m;
        } else {
            a = m;
        }
        
        n++;
    } while (h > epsilon && n <= max_iterations);
    
    printf("-------------------------------\n");
    if (n <= max_iterations) {
        printf("Root found: %.10f\n", m);
        printf("Function value at root: %.10e\n", function(m));
        printf("Number of iterations: %d\n", n);
    } else {
        printf("Maximum iterations reached. Best approximation: %.10f\n", m);
        printf("Function value at approximation: %.10e\n", function(m));
    }
    
    // Free allocated memory
    free(coefficients);
    free(signs);
    
    return 0;
}
