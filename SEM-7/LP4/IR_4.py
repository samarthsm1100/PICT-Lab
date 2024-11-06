from collections import Counter
from multiprocessing import Pool

def mapper(chunk):
    counts = Counter(filter(str.isalpha, chunk.lower()))
    return counts

def reducer(counts_list):
    result = Counter()
    for counts in counts_list:
        result.update(counts)
    return result

if __name__ == "__main__": 
    data = "This is a sample dataset. Count the number of occurrences of each letter, case-insensitive."
    
    num_workers = 4
    chunk_size = len(data) // num_workers
    chunks = [data[i:i + chunk_size] for i in range(0, len(data), chunk_size)]
    
    with Pool(processes=num_workers) as pool:
        mapped_counts = pool.map(mapper, chunks)

    final_counts = reducer(mapped_counts)

    for letter, count in sorted(final_counts.items()):
        print(f"{letter}: {count}")
