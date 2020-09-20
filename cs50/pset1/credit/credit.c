#include <stdio.h>
#include <cs50.h>

// tests credit card numbers for validity and origin
int main(void)
{
    // variables to track validity
    string code;
    bool valid;

    // retrieve number to test from user
    long number = get_long("Number: ");

    // prepare digit variables
    int digit_ct = 1;
    long digits[20];
    digits[0] = number;

    long result = number / 10;

    // break down the number
    while (result > 0)
    {
        digits[digit_ct] = result;
        result /= 10;
        digit_ct++;
    }

    // get array of single digits
    for (int i = 0; i < digit_ct - 1; i++)
    {
        digits[i] = digits[i] % (digits[i + 1] * 10);
    }

    // initial testing logic
    if (digit_ct == 13 || digit_ct == 15 || digit_ct == 16)
    {
        if (digits[digit_ct - 1] == 4)
        {
            code = "VISA";
            valid = true;
        }
        else if (digits[digit_ct - 1] == 3)
        {
            if (digits[digit_ct - 2] == 4 || digits[digit_ct - 2] == 7)
            {
                code = "AMEX";
                valid = true;
            }
            else
            {
                code = "INVALID";
                valid = false;
            }
        }
        else if (digits[digit_ct - 1] == 5)
        {
            if (digits[digit_ct - 2] == 1 || digits[digit_ct - 2] == 2 ||
                digits[digit_ct - 2] == 3 || digits[digit_ct - 2] == 4 ||
                digits[digit_ct - 2] == 5)
            {
                code = "MASTERCARD";
                valid = true;
            }
            else
            {
                code = "INVALID";
                valid = false;
            }
        }
        else
        {
            code = "INVALID";
            valid = false;
        }
    }
    else
    {
        code = "INVALID";
        valid = false;
    }

    // test using Luhn's algorithm
    if (valid)
    {
        int prod_sum = 0;
        int sing_sum = 0;

        // sum all digits
        for (int i = 0; i < digit_ct; i++)
        {
            if (i % 2 == 0)
            {
                sing_sum += digits[i];
            }
            else if (2 * digits[i] < 10)
            {
                prod_sum += 2 * digits[i];
            }
            else
            {
                prod_sum++;
                prod_sum += (2 * digits[i]) % 10;
            }
        }

        // test for good check digit
        if ((prod_sum + sing_sum) % 10 != 0)
        {
            code = "INVALID";
        }
    }

    // give output of validity and type
    printf("%s\n", code);
}