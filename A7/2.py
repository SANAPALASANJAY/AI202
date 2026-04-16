import math
import random
from g1 import EightQueens, steepest_ascent_hill_climbing 

def first_choice_hill_climbing(board):
    current_state = board.state
    current_h = board.calculate_heuristic(current_state)
    steps = 0
    max_attempts = 100
    
    while True:
        attempts = 0
        improved = False
        while attempts < max_attempts:
            # Randomly pick a neighbor
            col = random.randint(0, 7)
            row = random.randint(0, 7)
            if current_state[col] != row:
                neighbor = list(current_state)
                neighbor[col] = row
                neighbor_h = board.calculate_heuristic(neighbor)
                
                # First one that is better is chosen immediately
                if neighbor_h < current_h:
                    current_state = neighbor
                    current_h = neighbor_h
                    steps += 1
                    improved = True
                    break
            attempts += 1
            
        if not improved:
            status = "T" if current_h == 0 else "F"
            return current_h, steps, status

def random_restart_hill_climbing():
    total_steps = 0
    restarts = 0
    while True:
        board = EightQueens()
        final_h, steps, status, final_state = steepest_ascent_hill_climbing(board)
        total_steps += steps
        
        if status == "T":
            return final_h, total_steps, restarts, final_state
        restarts += 1

def simulated_annealing(board):
    current_state = board.state
    current_h = board.calculate_heuristic(current_state)
    steps = 0
    
    # Temperature schedule (exponential decay)
    T0 = 100.0
    alpha = 0.90
    
    T = T0
    while T > 0.0001:
        if current_h == 0:
            return current_h, steps, "T"
            
        # Pick a random neighbor
        col = random.randint(0, 7)
        row = random.randint(0, 7)
        neighbor = list(current_state)
        neighbor[col] = row
        neighbor_h = board.calculate_heuristic(neighbor)
        
        # Delta E = (Current Attacks) - (Neighbor Attacks)
        # Positive means improvement (fewer attacks)
        delta_e = current_h - neighbor_h 
        
        if delta_e > 0:
            current_state = neighbor
            current_h = neighbor_h
        else:
            # Accept bad move with probability e^(delta_E / T)
            probability = math.exp(delta_e / T)
            if random.random() < probability:
                current_state = neighbor
                current_h = neighbor_h
                
        T *= alpha
        steps += 1
        
    status = "T" if current_h == 0 else "F" # FIXED: "T" and "F"
    return current_h, steps, status

# --- Q2 Experiment & Comparison ---
print("\n--- Comparison ---")

# 1. First Choice (FIXED: Check for "T")
fc_success = sum(1 for _ in range(50) if first_choice_hill_climbing(EightQueens())[2] == "T")
print(f"First-Choice Success Rate: {fc_success}/50")

# 2. Simulated Annealing (FIXED: Check for "T")
sa_success = sum(1 for _ in range(50) if simulated_annealing(EightQueens())[2] == "T")
print(f"Simulated Annealing Success Rate: {sa_success}/50")

# 3. Random Restart
print("\nRandom Restart")
final_h, total_steps, restarts, winning_board = random_restart_hill_climbing()
print(f"Total steps taken across all restarts: {total_steps}")
print(f"Number of board resets required: {restarts}")
print("Winning Board Configuration:")
EightQueens().print_board(winning_board)
