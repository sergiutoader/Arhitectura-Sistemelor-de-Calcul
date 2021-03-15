from random import choice, seed
from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import as_completed

def find_seq(data):
    index = data[0]
    sample = data[1]
    seq = data[2]

    if not sample.find(seq) == -1:
        return "DNA sequence found in sample " + str(index)

    return ""

def main():
    samples = []
    for i in range(100):
        seed(i)
        samples.append("".join([choice("ACGT") for i in range(10000)]))

    seq = "CACCGGG"
    data = [(index, samples[index], seq) for index in range(100)]

    with ThreadPoolExecutor(max_workers = 30) as executor:
        results = executor.map(find_seq, data)


    for result in results:
        if not result == "":
            print(result)

if __name__ == "__main__":
    main()