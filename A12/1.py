def revise(domains, xi, xj):
    """
    Checks if we need to remove any values from the domain of xi.
    Returns True if the domain of xi was modified, False otherwise.
    """
    revised = False
    
    for x in list(domains[xi]):
        if not any(x != y for y in domains[xj]):
            domains[xi].remove(x)
            revised = True
            print(f"  -> Removed '{x}' from domain of {xi} due to conflict with {xj}")
        else:
            print(f"Arc({xi},{xj}) checked, no change")
            
            
    return revised, domains

def ac3(domains, neighbors):
    """
    The main AC-3 algorithm.
    """
    queue = [(xi, xj) for xi in neighbors for xj in neighbors[xi]]
    
    iteration = 1
    while queue:
        (xi, xj) = queue.pop(0)
        
        val, domains = revise(domains, xi, xj)
        if val:
            if len(domains[xi]) == 0:
                print(f"Failure: Domain of {xi} became empty!")
                return False
            
            for xk in neighbors[xi]:
                if xk != xj:
                    queue.append((xk, xi))
        iteration += 1
        
    return True, domains

if __name__ == "__main__":
    domains = {
        'P1': ['R3'],
        'P2': ['R1', 'R2', 'R3'],
        'P3': ['R1', 'R2', 'R3'],
        'P4': ['R1', 'R2', 'R3'],
        'P5': ['R1', 'R2', 'R3'],
        'P6': ['R1', 'R2', 'R3']
    }

    neighbors = {
        'P1': ['P2', 'P3', 'P6'],
        'P2': ['P1', 'P3', 'P4'],
        'P3': ['P1', 'P2', 'P5'],
        'P4': ['P2', 'P6'],
        'P5': ['P3', 'P6'],
        'P6': ['P1', 'P4', 'P5']
    }

    for team, domain in domains.items():
        print(f"{team}: {domain}")
    print("\nStarting AC-3 Algorithm...")

    is_consistent, domains = ac3(domains, neighbors)

    print("\n--- Final Results ---")
    if is_consistent:
        print("AC-3 completed successfully. The problem is arc-consistent.")
        print("Reduced Domains:")
        for team, domain in domains.items():
            print(f"  {team}: {domain}")
    else:
        print("AC-3 detected a failure (no valid assignment possible).")
        
        
    # Example solution: P1 P2 P3 P4 P5 P6
    #                   3  2  1  1  3  2
