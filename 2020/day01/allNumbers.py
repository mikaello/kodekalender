numbers_text = open("numbers.txt", "r").read().strip()
numbers_list = list(map(int, numbers_text.split(",")))
numbers_list_sorted = sorted(numbers_list)

for x in range(1, len(numbers_list_sorted)):
    if numbers_list_sorted[x-1] != x:
        print(f"{x} is missing!")
        exit(0)
