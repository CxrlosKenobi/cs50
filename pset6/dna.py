import csv
import sys

def getMaxNumOfTimesSubString(s, sub):
	# Calculate tha maximum number of times
	# a substring is repeated
	# O(len(s)) time complexity O(len(s)): space complexity
	# s:   [ATATATTATAT]
	# ans: [30201002010] # Starting at that index how many times does the substring repeat in s
	# sub: AT
	ans = [0] * len(s)
	for i in range(len(s) - len(sub), -1, -1):
		if s[i: i + len(sub)] == sub:
			if i + len(sub) > len(s) - 1:
				ans[i] = 1
			else:
				ans[i] = 1 + ans[i + len(sub)]
	return max(ans)

def print_match(reader, actual):
	for line in reader:
		person = line[0]
		values = [int(val) for val in line[1:]]
		if values == actual:
			print(person)
			return
	print("No match")

def main():
	if len(sys.argv) != 3:
		print("Usage: python dna.py location/file.csv location/file.txt")
		sys.exit(1)

	csvP = sys.argv[1]
	with open(csvP) as csvF:
		reader = csv.reader(csvF)
		# for row in reader:
		# 	print(row)
		all_sequences = next(reader)[1:]

		dnaP = sys.argv[2]
		with open(dnaP) as dnaF:
			s = dnaF.read()
			actual = [getMaxNumOfTimesSubString(s, seq) for seq in all_sequences]

		print_match(reader, actual)

if __name__ == '__main__':
	main()
