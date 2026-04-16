def get_actions(state):
    return ['Left', 'Right', 'Suck']

def is_goal(state):
    _, dirt_A, dirt_B = state
    return not dirt_A and not dirt_B

def results(state, action):
    loc, dirt_A, dirt_B = state
    outcomes = set()

    if action == 'Left':
        outcomes.add(('A', dirt_A, dirt_B))
    elif action == 'Right':
        outcomes.add(('B', dirt_A, dirt_B))
    elif action == 'Suck':
        if loc == 'A':
            if dirt_A:
                outcomes.add(('A', False, dirt_B))
                outcomes.add(('A', False, False))
            else:
                outcomes.add(('A', False, dirt_B))
                outcomes.add(('A', True, dirt_B))
        elif loc == 'B':
            if dirt_B:
                outcomes.add(('B', dirt_A, False))
                outcomes.add(('B', False, False))
            else:
                outcomes.add(('B', dirt_A, False))
                outcomes.add(('B', dirt_A, True))
                
    return list(outcomes)

def and_or_graph_search(initial_state):
    return or_search(initial_state, [])

def or_search(state, path):
    if is_goal(state):
        return []
    

    if state in path:
        return 'failure'
    
    for action in get_actions(state):
        possible_outcomes = results(state, action)
        
    
        plan = and_search(possible_outcomes, path + [state])
        
    
        if plan != 'failure':
            return {'action': action, 'contingencies': plan}
            
    return 'failure'

def and_search(states, path):
    contingency_plan = {}
    
    for state in states:
        plan = or_search(state, path)
        
        if plan == 'failure':
            return 'failure'
            
        contingency_plan[str(state)] = plan 
        
    return contingency_plan

if __name__ == "__main__":
    initial_state = ('A', True, True)
    print(f"Initial State: {initial_state}\n")
    
    solution = and_or_graph_search(initial_state)
    
    import json
    print("Conditional Plan Found:")
    print(json.dumps(solution, indent=4))
