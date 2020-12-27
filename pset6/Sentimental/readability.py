from cs50 import get_string

letters = 0
words = 1
sentences = 0

text = get_string("Text: ")

# Here we count the letters in the string
for i in range(len(text)):
	if (text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z'):
		letters += 1
	# Here we count the words in the string
	if text[i] == ' ':
		words += 1
	# Here we count the sentences in the string
	if text[i] == '.' or  text[i] == '!' or text[i] == '?':
		sentences += 1

# Finnally calculate the index
L = letters / words * 100
S = sentences / words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)


if index < 1:
	print("Before Grade 1")
elif index >= 16:
	print("Grade 16+")
else:
	print(f"Grade {index}")
