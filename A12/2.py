from collections import deque

# Each cell has a domain (set of values)
dom = [set() for _ in range(81)]

# Get row and column
def row(i):
    return i // 9

def col(i):
    return i % 9

# Constraint: values must be different
def ok(a, b):
    return a != b

# Get neighbors of a cell
def get_neighbors(idx):
    nbrs = []
    r, c = row(idx), col(idx)

    # Row and Column
    for i in range(9):
        if i != c:
            nbrs.append(r * 9 + i)
        if i != r:
            nbrs.append(i * 9 + c)

    # 3x3 box
    sr = (r // 3) * 3
    sc = (c // 3) * 3

    for i in range(sr, sr + 3):
        for j in range(sc, sc + 3):
            id = i * 9 + j
            if id != idx:
                nbrs.append(id)

    return nbrs

# Revise function
def revise(xi, xj):
    global removed_count
    changed = False
    to_remove = []

    for x in dom[xi]:
        possible = False

        for y in dom[xj]:
            if ok(x, y):
                possible = True
                break

        if not possible:
            to_remove.append(x)

    for v in to_remove:
        dom[xi].remove(v)
        removed_count += 1
        changed = True

    return changed

# AC-3 Algorithm
def ac3():
    q = deque()

    # Generate all arcs
    for i in range(81):
        for j in get_neighbors(i):
            q.append((i, j))

    while q:
        xi, xj = q.popleft()

        if revise(xi, xj):
            if len(dom[xi]) == 0:
                return False

            for xk in get_neighbors(xi):
                if xk != xj:
                    q.append((xk, xi))

    return True


# ---------------- MAIN ----------------

grid = [
    [0, 0, 0, 0, 0, 6, 0, 0, 0],
    [0, 5, 9, 0, 0, 0, 0, 0, 8],
    [2, 0, 0, 0, 0, 8, 0, 0, 0],
    [0, 4, 5, 0, 0, 0, 0, 0, 0],
    [0, 0, 3, 0, 0, 0, 0, 0, 0],
    [0, 0, 6, 0, 0, 3, 0, 5, 0],
    [0, 0, 0, 0, 0, 7, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 5, 0, 0, 0, 2]
]

# Initialize domains
for i in range(81):
    r, c = i // 9, i % 9

    if grid[r][c] == 0:
        dom[i] = set(range(1, 10))
    else:
        dom[i] = {grid[r][c]}

removed_count = 0

result = ac3()

print("Values removed:", removed_count)

print("\nDomain size grid:")

all_one = True

row = 1
for i in range(81):
    size = len(dom[i])
    print(size, end=" ")
    
    if size != 1:
        all_one = False
        
    if (i + 1) % 3 == 0:
        print("|", end="")
    if (i + 1) % 9 == 0:
        print()
        if row % 3 == 0:
            print("- - - - - - - - - - - ")
        row += 1

print()

if not result:
    print("Some domain became empty -> UNSOLVABLE")
elif all_one:
    print("Solved completely by AC-3")
else:
    print("Partially reduced, needs backtracking")
