from cs50 import get_float
from sys import exit

while True:
	change_o = get_float("Change owed: ")

	if change_o >= 0:
		break


coins = change_o * 100

round(coins, 1)

quarters = coins // 25
dimes = (coins % 25) // 10
nickels = ((coins % 25) % 10) // 5
pennies = ((coins % 25) % 10) % 5

total = quarters + dimes + nickels + pennies

print(int(total))
