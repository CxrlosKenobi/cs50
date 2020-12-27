from cs50 import get_int

while True:
	# Takin user input
	usin = get_int("Height: ")
	if usin >= 1 and usin <= 8:
		break

# Output the mario pyramid on Pythonic mode
for i in range(usin):
	print(" " * (usin-i-1), end="")
	print("#" * (i + 1), end="")
	print("  ", end="")
	print("#" * (i + 1))
