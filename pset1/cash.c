#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main()
{
    int coins;

    do
    {
        float change_o = get_float("Change owed: ");
        coins = round(change_o * 100);
    }
    while (coins <= 0);

    int quarters = coins / 25;
    int dimes = (coins % 25) / 10;
    int nickels = ((coins % 25) % 10) / 5;
    int pennies = ((coins % 25) % 10) % 5;

    printf("%d\n", quarters + dimes + nickels + pennies);
}
