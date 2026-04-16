import numpy as np
import random

dist_matrix = np.array([
    [0,  10, 15, 20, 25, 30, 35, 40], # A
    [12, 0,  35, 15, 20, 25, 30, 45], # B
    [25, 30, 0,  10, 40, 20, 15, 35], # C
    [18, 25, 12, 0,  15, 30, 20, 10], # D
    [22, 18, 28, 20, 0,  15, 25, 30], # E
    [35, 22, 18, 28, 12, 0,  40, 20], # F
    [30, 35, 22, 18, 28, 32, 0,  15], # G
    [40, 28, 35, 22, 18, 25, 12, 0 ]  # H
])

cities = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
n_cities = 8

def calculate_cost(path):
    cost = 0
    for i in range(len(path) - 1):
        cost += dist_matrix[path[i]][path[i+1]]
    cost += dist_matrix[path[-1]][path[0]]
    return cost

def crossover_1point(parent1, parent2):
    point = random.randint(1, n_cities - 2)
    child = parent1[:point]
    for city in parent2:
        if city not in child:
            child.append(city)
    return child

def crossover_2point(parent1, parent2):
    point1, point2 = sorted(random.sample(range(1, n_cities), 2))
    child = [-1] * n_cities
    child[point1:point2] = parent1[point1:point2]
    
    p2_idx = 0
    for i in range(n_cities):
        if child[i] == -1:
            while parent2[p2_idx] in child:
                p2_idx += 1
            child[i] = parent2[p2_idx]
    return child

def mutate(path, rate=0.1):
    if random.random() < rate:
        i, j = random.sample(range(n_cities), 2)
        path[i], path[j] = path[j], path[i]
    return path

def run_ga(crossover_type, pop_size=50, max_gen=100):
    population = [list(np.random.permutation(n_cities)) for _ in range(pop_size)]
    best_cost = float('inf')
    best_path = None
    
    for gen in range(max_gen):
        scored = [(calculate_cost(p), p) for p in population]
        scored.sort(key=lambda x: x[0])
        
        if scored[0][0] < best_cost:
            best_cost = scored[0][0]
            best_path = scored[0][1]
            
        survivors = [p for cost, p in scored[:pop_size//2]]
        next_gen = survivors.copy()
        
        while len(next_gen) < pop_size:
            p1, p2 = random.sample(survivors, 2)
            child = crossover_1point(p1, p2) if crossover_type == 1 else crossover_2point(p1, p2)
            next_gen.append(mutate(child))
            
        population = next_gen
        
    return best_path, best_cost

if __name__ == "__main__":
    
    print("\n" + "="*60)
    print(" GENETIC ALGORITHM ANALYSIS (TSP) ")
    print("="*60)
    
    for cx_type, name in [(1, "1-Point Crossover"), (2, "2-Point Crossover")]:
        success_count = 0
        best_overall_cost = float('inf')
        best_overall_path = None
        
        for _ in range(20):
            path, cost = run_ga(cx_type)
            if cost == 121:
                success_count += 1
            if cost < best_overall_cost:
                best_overall_cost = cost
                best_overall_path = path

        path_names = [cities[i] for i in best_overall_path]
        route = ' -> '.join(path_names) + f' -> {path_names[0]}'
        
        print(f"\n {name}")
        print("-" * 60)
        print(f" Best Cost Reached : {best_overall_cost}")
        print(f" Best Route Found  : {route}")
        print(f" Convergence Rate  : Found optimum {success_count} out of 20 runs.")

    # print("\n" + "="*60)
    # print(" COMPARATIVE ANALYSIS:")
    # print(" -> YES, the number of crossover points impacts convergence.")
    # print(" -> 1-Point Crossover is more disruptive to sub-routes, lowering")
    # print("    overall reliability.")
    # print(" -> 2-Point Crossover preserves chunks of 'good' routes better,")
    # print("    resulting in a noticeably higher convergence rate.")
    # print("="*60 + "\n")
