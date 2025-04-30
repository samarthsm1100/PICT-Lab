import random

n = 10000     # number of vertices
m = 50000     # number of edges
source = 0    # starting vertex

edges = set()

# Add a connected spanning tree first
for i in range(1, n):
    u = i
    v = random.randint(0, i - 1)
    edges.add((min(u, v), max(u, v)))

# Add remaining random edges
while len(edges) < m:
    u = random.randint(0, n - 1)
    v = random.randint(0, n - 1)
    if u != v:
        edges.add((min(u, v), max(u, v)))

# Save to file
with open("input.txt", "w") as f:
    f.write(f"{n}\n")
    f.write(f"{m}\n")
    for u, v in edges:
        f.write(f"{u} {v}\n")
    f.write(f"{source}\n")
