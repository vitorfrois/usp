def dec_to_bin(x):
    return (bin(x)[2:])

with open('urss.txt') as f:
    for line in f:
        print(dec_to_bin(line))
