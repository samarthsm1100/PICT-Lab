#include <iostream>
using namespace std;

// Iterative Fibonacci function
int fibonacciIterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, fib = 1;
    for (int i = 2; i <= n; i++) {
        fib = a + b;
        a = b;
        b = fib;
    }
    return fib;
}

// Recursive Fibonacci function
int fibonacciRecursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n;
    cout << "Enter the number: ";
    cin >> n;

    // Calling both functions
    cout << "Fibonacci (Iterative) of " << n << " is: " << fibonacciIterative(n) << endl;
    cout << "Fibonacci (Recursive) of " << n << " is: " << fibonacciRecursive(n) << endl;

    return 0;
}
