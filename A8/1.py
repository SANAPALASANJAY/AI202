import numpy as np

dist_matrix = np.array([
   # 0.   1.  2. 3.  4.  5.  6.  7.  
    [0,  10, 15, 20, 25, 30, 35, 40], # City 0
    [12, 0,  35, 15, 20, 25, 30, 45], # City 1
    [25, 30, 0,  10, 40, 20, 15, 35], # City 2
    [18, 25, 12, 0,  15, 30, 20, 10], # City 3
    [22, 18, 28, 20, 0,  15, 25, 30], # City 4
    [35, 22, 18, 28, 12, 0,  40, 20], # City 5
    [30, 35, 22, 18, 28, 32, 0,  15], # City 6
    [40, 28, 35, 22, 18, 25, 12, 0 ]  # City 7
])

cities = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
n_cities = 8

def calculate_cost(path):
    cost = 0
    for i in range(len(path) - 1):
        cost += dist_matrix[path[i]][path[i+1]]
    cost += dist_matrix[path[-1]][path[0]]
    return cost

def get_neighbors(path):
    neighbors = []
    for i in range(n_cities):
        for j in range(i + 1, n_cities):
            neighbor = path.copy()
            neighbor[i], neighbor[j] = neighbor[j], neighbor[i]
            neighbors.append(neighbor)
    return neighbors

def local_beam_search(k, max_iter=100):
    # np.random.seed(43)
    population = [list(np.random.permutation(n_cities)) for _ in range(k)]
    best_cost = float('inf')
    best_path = None
    
    for _ in range(max_iter):
        all_neighbors = []
        for path in population:
            all_neighbors.extend(get_neighbors(path))
            
        scored_neighbors = [(calculate_cost(p), p) for p in all_neighbors]
        scored_neighbors.sort(key=lambda x: x[0])
        
        population = [p for cost, p in scored_neighbors[:k]]
        
        if scored_neighbors[0][0] < best_cost:
            best_cost = scored_neighbors[0][0]
            best_path = scored_neighbors[0][1]
            
    return best_path, best_cost

if __name__ == "__main__":
    print("\n" + "="*60)
    print(" LOCAL BEAM SEARCH ANALYSIS (TSP) ")
    print("="*60)
    
    for k in [3, 5, 10]:
        path, cost = local_beam_search(k)
        path_names = [cities[i] for i in path]
        route = ' -> '.join(path_names) + f' -> {path_names[0]}'
        
        print(f"\n Beam Width: k = {k}")
        print("-" * 60)
        print(f" Best Cost Found : {cost}")
        print(f" Optimal Route   : {route}")
        
    # print("\n" + "="*60)
    # print(" COMPARATIVE ANALYSIS:")
    # print(" -> YES, convergence depen ds heavily on k.")
    # print(" -> Low k (k=3): High risk of getting trapped in a local minimum.")
    # print(" -> High k (k>=5): More exploration, higher chance of finding the")
    # print("    global optimum (cost: 121).")
    # print("="*60 + "\n")
