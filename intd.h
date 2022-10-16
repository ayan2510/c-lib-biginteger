/*Library "intd" -> Integer of arbitray length
intd is a nonnegative integer of arbitrary length (not more than 1000 decimal digits).
The integer is stored as a null terminated string of ASCII characters.
String of decimal digits ('0' to '9') are stored in big endian style.

DO NOT modify this header file.
The implementation file has the definition of the functions decalred here.
You can write some of your own helper functions, keep them "static". */

// Returns the sum of two nums.
// DONE
char *intdAdd(const char *num1, const char *num2);

// Returns the comparison value of two nums.
// Returns 0 when both are equal.
// Returns +1 when num1 is greater, and -1 when num2 is greater.
// DONE
int intdCompare(const char *num1, const char *num2);

// Returns the difference (obviously nonnegative) of two nums.
// DONE
char *intdDiff(const char *num1, const char *num2);

// Returns the product of two nums.
// DONE
char *intdMultiply(const char *num1, const char *num2);

// Returns num1 mod num2
// The mod value should be in the range [0, num2 - 1].
// num2 > 1
// A O(log num1) time taking algorithm.
// DONE
char *intdMod(const char *num1, const char *num2);

// Returns num1 ^ num2.
// Let 0 ^ n = 0, where n is an intad.
// A O(log n) intad multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit.
// DONE
char *intdPow(const char *num, unsigned int n);

// Returns nth fibonacci number.
// DONE
char *intdFibonacci(unsigned int n);

// Returns the factorial of n.
// DONE
char *intdFactorial(unsigned int n);

// Returns the offset of the largest num in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
// DONE
int intdMax(char **arr, int n);

// Returns the offset of the smallest num in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
// DONE
int intdMin(char **arr, int n);

// Returns the offset of the first occurrence of the key num in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
// DONE
int intdSearch(char **arr, int n, const char *key);

// Returns the offset of the first occurrence of the key num in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation is a O(log n) algorithm.
// DONE
int intdBinsearch(char **arr, int n, const char *key);

// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
// DONE
void intdSort(char **arr, int n);

// intd

// created by AYANAVA DAS
