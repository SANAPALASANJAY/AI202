import random

class EightQueens:
    def __init__(self, state=None):
        # State is a list of 8 integers representing the row of the queen in each column
        self.state = state if state else [random.randint(0, 7) for _ in range(8)]
    
    def calculate_heuristic(self, state):
        """Calculates the number of attacking pairs of queens."""
        attacks = 0
        n = len(state)
        for i in range(n):
            for j in range(i + 1, n):
                # Check for same row or same diagonal
                if state[i] == state[j] or abs(state[i] - state[j]) == abs(i - j):
                    attacks += 1
        return attacks

    def get_neighbors(self, current_state):
        """Generates all 56 successors for the GIVEN state."""
        neighbors = []
        for col in range(8):
            for row in range(8):
                if current_state[col] != row:
                    new_state = list(current_state)
                    new_state[col] = row
                    neighbors.append(new_state)
        return neighbors

    def print_board(self, state):
        """Visual terminal representation of the board."""
        for row in range(8):
            line = ""
            for col in range(8):
                if state[col] == row:
                    line += " ♕ "
                else:
                    line += " . "
            print(line)
        print("-" * 25)

def steepest_ascent_hill_climbing(board):
    current_state = board.state
    current_h = board.calculate_heuristic(current_state)
    steps = 0
    
    while True:
        neighbors = board.get_neighbors(current_state)
        best_neighbor = None
        best_h = current_h
        
        # Evaluate all neighbors to find the steepest ascent (lowest h)
        for neighbor in neighbors:
            h = board.calculate_heuristic(neighbor)
            if h < best_h:
                best_h = h
                best_neighbor = neighbor
                
        # If we can't improve, we hit a peak/minimum
        if best_neighbor is None:
            status = "T" if current_h == 0 else "F"
            return current_h, steps, status, current_state
            
        current_state = best_neighbor
        current_h = best_h
        steps += 1

print("--- Steepest-Ascent on 50 Random Boards ---")
successes = 0

boards = set()

for i in range(50):
    initial_board = EightQueens()
    init_h = initial_board.calculate_heuristic(initial_board.state)
    final_h, steps, status, final_state = steepest_ascent_hill_climbing(initial_board)
    
    if status == "T":
        successes += 1
        # initial_board.print_board(final_state)
    
    if status == "F":
        # print(f"\nBoard #{i+1} got stuck with h={final_h}. No single move can improve this state.")
        # initial_board.print_board(final_state)
        pass

print(f"\nSteepest-Ascent Success Rate: {successes}/50 ({round((successes/50)*100, 2)}%)")
