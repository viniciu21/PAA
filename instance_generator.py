import random

OUTPUT_FILE = "instance.txt"

print("This is script generates instances to 1D BP.")
print("What is the maximum height of a rectangle? ")
max_height = float(input())

print("How many rectangles to be randomized? ")
qnt_rects = int(input())

f = open(OUTPUT_FILE, "w")
f.write("%d\n" % qnt_rects)

for i in range(0, qnt_rects):
    f.write("%f\n" % random.uniform(0, max_height))

print("It was generated in file %s" % OUTPUT_FILE)