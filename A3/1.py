import random

class Environment:
    def __init__(self):
        self.house = ['A', 'B', 'C']
        self.agent = random.choice(self.house)
        self.state = {
            'A': random.choice(["Clean", "Dirty"]),
            'B': random.choice(["Clean", "Dirty"]),
            'C': random.choice(["Clean", "Dirty"]),
        }
        self.cost = 0
    
    def percept(self):
        return (self.agent, self.state.copy())
    
    def transition(self, action, open=True):
        if action == "Suck":
            if self.state[self.agent] == "Dirty":
                self.state[self.agent] = "Clean"
                self.cost += 2
        elif action == "Left":
            pos = self.house.index(self.agent)
            if pos > 0:
                self.agent = self.house[pos - 1]
                self.cost += 1
        elif action == "Right":
            pos = self.house.index(self.agent)
            if pos < 2:
                self.agent = self.house[pos + 1]
                self.cost += 1
        elif action == "Stay":
            pass

        # for room in self.house:
        #     if self.state[room] == "Dirty":
        #         self.cost -= 2

        if open:
            if self.state['A'] == "Clean":
                self.state['A'] = random.choice(["Clean", "Dirty"])
            if self.state['B'] == "Clean":
                self.state['B'] = random.choice(["Clean", "Dirty"])
            if self.state['C'] == "Clean":
                self.state['C'] = random.choice(["Clean", "Dirty"])

    def show(self):
        for room in self.house:
            if self.agent == room:
                print(" 🤖 ", end = "")
            else:
                print(f" {room} ", end = "")
        print("\n")

    def isClean(self):
        return all(self.state[room] == "Clean" for room in self.house)

RULES = {
    "A":{"B": "Right", "C": "Right"},
    "B": {"A": "Left", "C": "Right"},
    "C": {"A": "Left", "B": "Left"},
}

def agent(percept):
    location, state = percept
    env = ["A", "B", "C"]
    if state[location] == "Dirty":
        return "Suck"
    else:
        env.remove(location)
        if (state[env[0]] == "Dirty" and state[env[1]] == "Dirty"):
            return RULES[location][random.choice(env)]
        elif state[env[0]] == "Dirty":
            return RULES[location][env[0]]
        elif state[env[1]] == "Dirty":
            return RULES[location][env[1]]
        else:
            return "Stay"
        
def simulate(time = 7):
    env = Environment()

    print("Initial State: ", end = "")
    env.show()

    for i in range(time):
        percept = env.percept()
        action = agent(percept)
        env.transition(action)

        print(f"Time    : {i+1}")
        print("Percept  :", percept[1])
        print("Action   :", action)
        print("Location :", env.agent)
        print("Current State: ", end = "")
        env.show()
        print("Score    :", env.cost)
        print("-"*43)
    
    while env.isClean() == False:
        percept = env.percept()
        action = agent(percept)
        env.transition(action, False)

        print(f"Time:   : {time}")
        print("Percept  :", percept[1])
        print("Action   :", action)
        print("Location :", env.agent)
        print("Current State: ", end = "")
        env.show()
        print("Scores    :", env.cost)
        print("-"*43)
        time += 1

    print("FINAL STATE: ", end="")
    env.show()

    
simulate(3)
