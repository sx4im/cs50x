
import csv
import sys


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0

        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


def main():
    # Check for correct command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    with open(sys.argv[1], "r") as database_file:
        reader = csv.DictReader(database_file)
        database = [row for row in reader]

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence_file:
        sequence = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for key in database[0].keys():
        if key == "name":
            continue
        str_counts[key] = longest_match(sequence, key)

    # Check database for matching profiles
    for row in database:
        match = True
        for key in row:
            if key == "name":
                continue
            if int(row[key]) != str_counts[key]:
                match = False
                break
        if match:
            print(row["name"])
            return

    print("No match")


if __name__ == "__main__":
    main()
