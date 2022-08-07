#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intd.h"

static char *removeLeadingZeroes(char *res)
{
	int nonz = 0, newlen = 0, i = 0;
	int n = strlen(res);

	for (nonz = 0; nonz < n; nonz++)
	{
		if (res[nonz] != 48)
			break;
	}
	// printf("NONZ == %d\n",nonz);

	if (nonz == 0)
		return res;

	newlen = n - nonz;
	for (i = 0; i < newlen; i++)
		res[i] = res[i + nonz];
	// res = (char*)realloc(res,sizeof(char)*(newlen+1)); //6474
	res[i] = '\0';

	if (res[0] == '\0')
	{
		free(res);
		res = (char *)calloc(2, sizeof(char));
		res[0] = 48;
		res[1] = '\0';
	}

	return res;
}

static void intdAdder(const char *num1, const char *num2, char *res)
{
	int l1 = strlen(num1) - 1;
	int l2 = strlen(num2) - 1;
	int sum = 0, carry = 0, k = l1 + 1;
	int adjust = 48, i;

	// all element of ans to 0
	for (i = 0; i < k + 1; i++)
		res[i] = '0';
	res[i] = '\0';

	while (l2 >= 0)
	{
		sum = num1[l1] + num2[l2] + carry - 2 * adjust;
		res[k] = sum % 10 + adjust;
		carry = sum / 10;
		l1--;
		l2--;
		k--;
	}

	while (l1 >= 0)
	{
		sum = num1[l1] + carry - adjust;
		res[k] = sum % 10 + adjust;
		carry = sum / 10;
		l1--;
		k--;
	}

	if (carry)
		res[k] = carry + adjust;
}

int intdCompare(const char *num1, const char *num2)
{
	int l1 = strlen(num1) - 1;
	int l2 = strlen(num2) - 1;

	int diff = 0, bigger = 0;
	int i = 0;
	if (l1 < l2)
		return -1;
	if (l1 == l2)
	{
		bigger = 0;
		do
		{
			diff = num1[i] - num2[i];
			if (diff > 0)
			{
				bigger = 1;
			}
			else if (diff < 0)
			{
				bigger = -1;
			}
			++i;
		} while (diff == 0 && i <= l1 && i <= l2);
		return bigger;
	}
	return 1;
}

char *intdAdd(const char *num1, const char *num2)
{
	int larger = intdCompare(num1, num2);
	char *sum;

	if (larger == -1)
	{
		sum = (char *)calloc(strlen(num2) + 2, sizeof(char));
		intdAdder(num2, num1, sum);
	}

	else
	{
		sum = (char *)calloc(strlen(num1) + 2, sizeof(char));
		intdAdder(num1, num2, sum);
	}

	return removeLeadingZeroes(sum);
}

static void intdDiffer(const char *num1, const char *num2, char *res)
{
	int l1 = strlen(num1) - 1;
	int l2 = strlen(num2) - 1;
	int top = 0, bottom = 0, k = l1, i;
	int borrow = 0;

	for (i = 0; i <= k; i++)
		res[i] = '0';
	res[i] = '\0';

	while (l2 >= 0)
	{
		top = num1[l1] - 48;
		bottom = num2[l2] - 48;

		if (borrow > 0)
		{
			if (borrow == 1)
				top -= 1;
			else
				top = 9 + num1[l1] - 48;

			borrow--;
		}

		if (top < bottom)
		{
			do
			{
				borrow++;
			} while (num1[l1 - borrow] == 48 && (l1 - borrow) > 0);

			top += 10;
		}

		res[k] = 48 + top - bottom;
		l1--;
		l2--;
		k--;
	}

	while (l1 >= 0)
	{
		if (borrow > 0)
		{
			res[k] = num1[l1] - 1;
			if (num1[l1] == 48)
				res[k] = 57;
			borrow--;
		}
		else
			res[k] = num1[l1];

		l1--;
		k--;
	}
}

char *intdDiff(const char *num1, const char *num2)
{
	int larger = intdCompare(num1, num2);
	char *diff;

	if (larger == -1)
	{
		diff = (char *)calloc(strlen(num2) + 2, sizeof(char));
		intdDiffer(num2, num1, diff);
	}
	else
	{
		diff = (char *)calloc(strlen(num1) + 2, sizeof(char));
		intdDiffer(num1, num2, diff);
	}

	return removeLeadingZeroes(diff);
}

static int isZero(const char *num)
{
	int l = strlen(num);
	int count = 0;

	for (int i = 0; i < l; i++)
	{
		if (num[i] == '0')
			count++;
	}

	return count == l;
}

static void intdMul(const char *num1, const char *num2, char *res)
{
	int l1 = strlen(num1);
	int l2 = strlen(num2);
	int sum = 0, carry = 0;
	int l3 = l1 + l2;
	int ptr1 = 1, ptr2;

	for (int i = 0; i < l3; i++)
		res[i] = '0';

	for (int i = l2 - 1; i >= 0; i--)
	{
		sum = 0;
		carry = 0;
		ptr2 = l3 - ptr1;
		for (int j = l1 - 1; j >= 0; j--)
		{
			sum = (num1[j] - 48) * (num2[i] - 48) + (res[ptr2] - 48) + carry;
			res[ptr2] = 48 + sum % 10;
			carry = sum / 10;
			ptr2--;
		}
		if (carry)
			res[ptr2] += carry;

		ptr1++;
	}
}

char *intdMultiply(const char *num1, const char *num2)
{
	if (!isZero(num1) && !isZero(num2))
	{
		int larger = intdCompare(num1, num2);
		char *res = (char *)calloc(strlen(num1) + strlen(num2) + 1, sizeof(char));

		if (larger)
			intdMul(num2, num1, res);
		else
			intdMul(num1, num2, res);

		return removeLeadingZeroes(res);
	}

	char *res = (char *)malloc(2 * sizeof(char));
	strcpy(res, "0");
	return res;
}

char *intdMod(const char *num1, const char *num2)
{
	int comp = intdCompare(num1, num2);
	int l1 = strlen(num1);
	int l2 = strlen(num2);
	int i;

	if (isZero(num1) || comp == 0)
	{
		char *res = (char *)calloc(2, sizeof(char));
		strcpy(res, "0");
		return res;
	}
	if (comp == -1)
	{
		char *res = (char *)calloc(l1 + 1, sizeof(char));
		strcpy(res, num1);
		return res;
	}
	int diff = l1 - l2;
	if (num1[0] <= num2[0])
		diff--;

	if (diff == 0)
	{
		char *temp = intdDiff(num1, num2);
		char *t2 = temp;
		char *res = intdMod(temp, num2);
		free(t2);
		return res;
	}
	char *ni1 = (char *)malloc(sizeof(char) * (l1 + 1));
	strcpy(ni1, num1);
	char *ni2 = (char *)malloc(sizeof(char) * (l2 + diff + 2));
	for (i = 0; i < l2; i++)
		ni2[i] = num2[i];
	for (i = 0; i < diff; i++)
		ni2[l2 + i] = 48;
	ni2[l2 + i] = '\0';

	while (intdCompare(ni1, ni2) > 0)
	{
		char *temp = intdDiff(ni1, ni2);
		char *t2 = ni1;
		ni1 = temp;
		free(t2);
	}
	free(ni2);

	if (intdCompare(ni1, num2) <= 0)
		return ni1;

	char *temp = ni1;
	char *res = intdMod(ni1, num2);
	free(temp);
	return res;
}

char *intdPow(const char *num1, unsigned int n)
{
	if (isZero(num1))
	{
		char *res = (char *)malloc(sizeof(char) * 2);
		strcpy(res, "0");
		return res;
	}
	char *res = (char *)malloc(sizeof(char) * 2);
	strcpy(res, "1");
	char *x = (char *)malloc(sizeof(char) * (strlen(num1) + 1));
	strcpy(x, num1);
	char *temp;
	while (n > 0)
	{
		if (n & 1)
		{
			temp = intdMultiply(res, x);
			free(res);
			res = temp;
		}
		n = n >> 1;
		temp = intdMultiply(x, x);
		free(x);
		x = temp;
	}
	free(x);
	return res;
}

char *intdGCD(const char *num1, const char *num2)
{
	if (strcmp(num1, "0") == 0 && strcmp(num2, "0") == 0)
	{
		char *res = (char *)calloc(2, sizeof(char));
		res[0] = '0';
		res[1] = '\0';
		return res;
	}

	if (strcmp(num1, "0") == 0)
	{
		char *res = (char *)calloc(strlen(num2) + 1, sizeof(char));
		int i = 0;
		for (i = 0; i < strlen(num2); i++)
			res[i] = num2[i];
		res[i] = '\0';
		return res;
	}
	if (strcmp(num2, "0") == 0)
	{
		char *res = (char *)calloc(strlen(num1) + 1, sizeof(char));
		int i = 0;
		for (i = 0; i < strlen(num1); i++)
			res[i] = num1[i];
		res[i] = '\0';
		return res;
	}
	char *temp = intdMod(num1, num2);
	char *res = intdGCD(num2, temp);
	free(temp);
	return res;
}

char *intdFibonacci(unsigned int n)
{
	unsigned int i;
	char *res1 = (char *)malloc(2 * sizeof(char));
	strcpy(res1, "0");
	if (n == 0)
		return res1;
	char *res2 = (char *)malloc(2 * sizeof(char));

	strcpy(res2, "1");
	char *temp = NULL;
	for (i = 2; i <= n; i++)
	{
		temp = intdAdd(res1, res2);
		free(res1);
		res1 = res2;
		res2 = temp;
	}

	free(res1);
	return res2;
}

char *intdFactorial(unsigned int n)
{
	char *res = (char *)calloc(2, sizeof(char));
	strcpy(res, "1");
	if (n == 0 || n == 1)
		return res;

	char *num = (char *)calloc(2, sizeof(char));
	char *copy = NULL;
	strcpy(num, "1");
	unsigned int i = 2;
	while (i <= n)
	{
		copy = intdAdd(num, "1");
		free(num);
		num = copy;
		copy = intdMultiply(num, res);
		free(res);
		res = copy;
		i++;
	}

	free(num);
	return removeLeadingZeroes(res);
}

char *intdBincoeff(unsigned int n, unsigned int k)
{
	unsigned int i = 0;
	unsigned int j = 0;

	if (k > (n - k))
		k = n - k;
	char **dp = (char **)malloc(sizeof(char *) * (k + 1));
	dp[0] = (char *)malloc(2 * sizeof(char));

	strcpy(dp[0], "1");

	for (i = 1; i <= k; i++)
	{
		dp[i] = (char *)malloc(2 * sizeof(char));
		strcpy(dp[i], "0");
	}

	char *temp;
	for (i = 1; i <= n; i++)
	{
		for (j = (i > k) ? k : i; j > 0; j--)
		{
			temp = intdAdd(dp[j], dp[j - 1]);
			free(dp[j]);
			dp[j] = temp;
		}
	}
	char *res = (char *)malloc(sizeof(char) * (strlen(dp[k]) + 1));
	strcpy(res, dp[k]);
	for (i = 0; i <= k; i++)
		free(dp[i]);

	free(dp);
	return res;
}

int intdMax(char **arr, int n)
{
	int max = 0, i;

	for (i = 1; i < n; i++)
	{
		if (intdCompare(arr[max], arr[i]) < 0)
			max = i;
	}

	return max;
}

int intdMin(char **arr, int n)
{
	int min = 0, i;

	for (i = 1; i < n; i++)
	{
		if (intdCompare(arr[min], arr[i]) > 0)
			min = i;
	}

	return min;
}

int intdSearch(char **arr, int n, const char *key)
{
	int index = -1, i;

	for (i = 0; i < n; i++)
	{
		if (intdCompare(arr[i], key) == 0)
		{
			index = i;
			break;
		}
	}

	return index;
}

int intdBinsearch(char **arr, int n, const char *key)
{
	int low = 0, high = n - 1;
	int mid = -1, comp = 0;

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		comp = intdCompare(arr[mid], key);

		if (comp == 0)
			return mid;

		if (comp == 1)
			high = mid - 1;

		else
			low = mid + 1;
	}

	return -1;
}

static void merge(char **arr, int low, int mid, int high)
{
	int i, j, k;
	int n1 = mid - low + 1;
	int n2 = high - mid;
	char **left = (char **)malloc(sizeof(char *) * n1);
	char **right = (char **)malloc(sizeof(char *) * n2);
	for (i = 0; i < n1; i++)
	{
		left[i] = (char *)malloc(sizeof(char) * (strlen(arr[low + i]) + 1));
		strcpy(left[i], arr[low + i]);
	}
	for (j = 0; j < n2; j++)
	{
		right[j] = (char *)malloc(sizeof(char) * (strlen(arr[mid + 1 + j]) + 1));
		strcpy(right[j], arr[mid + 1 + j]);
	}
	i = 0;
	j = 0;
	k = low;
	while (i < n1 && j < n2)
	{
		if (intal_compare(left[i], right[j]) <= 0)
		{
			strcpy(arr[k], left[i]);
			i++;
		}
		else
		{
			strcpy(arr[k], right[j]);
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		strcpy(arr[k], left[i]);
		i++;
		k++;
	}
	while (j < n2)
	{
		strcpy(arr[k], right[j]);
		j++;
		k++;
	}
	for (i = 0; i < n1; i++)
		free(left[i]);
	free(left);

	for (i = 0; i < n2; i++)
		free(right[i]);
	free(right);
}

void intdSort(char **arr, int n)
{
	int curr_size, left_start;

	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			int mid = ((left_start + curr_size - 1) > n - 1) ? (n - 1) : (left_start + curr_size - 1);
			int right_end = ((left_start + 2 * curr_size - 1) > n - 1) ? (n - 1) : (left_start + 2 * curr_size - 1);
			merge(arr, left_start, mid, right_end);
		}
	}
}
