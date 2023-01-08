import csv
import sys


def main():

    # TODO: Check for command-line usage
    if not len(sys.argv) == 3:
        print("Incorrect usage")
        return
    elif not sys.argv[1][-4:] == ".csv":
        print("Incorrect file format")
    elif not sys.argv[2][-4:] == ".txt":
        print("Incorrect file format")
    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1]) as file:
        header_tmp = file.readline()
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            data.append(row)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file_dna:
        dna = file_dna.read()
    # TODO: Find longest match of each STR in DNA sequence
    header = []
    for i in range(len(header_tmp)):
        if header_tmp[i] == ',':
            tmp = i + 1
            count = 0
            tmp_str = ''
            while not header_tmp[tmp] == ',' and not header_tmp[tmp] == '\n':
                tmp_str = tmp_str + header_tmp[tmp]
                count = count + 1
                tmp = tmp + 1
            header.append(tmp_str)
    matches = []
    for pie in header:
        matches.append(longest_match(dna, pie))
    # TODO: Check database for matching profiles
    for i in range(len(data)):
        tmp_1 = 0
        for part in header:
            if data[i][part] == str(matches[tmp_1]):
                tmp_1 = tmp_1 + 1
            if len(header) == tmp_1:
                print(data[i]['name'])
                return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
