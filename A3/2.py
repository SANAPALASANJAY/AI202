class Environment:
    def __init__(self):
        self.state = {
            'track_sensor': False,
            'obstacle_sensor': False,
            'emergency_lever': "Neutral"
        }
    
    def percept(self):
        return (
            self.state['track_sensor'],
            self.state['obstacle_sensor'],
            self.state['emergency_lever']
        )

    def transition(self, next_state):
        self.state['track_sensor'] = next_state[0]
        self.state['obstacle_sensor'] = next_state[1]
        self.state['emergency_lever'] = next_state[2]

    def show(self, action):
        train = "PRESENT" if self.state['track_sensor'] else "  "
        obstacle = "PRESENT" if self.state['obstacle_sensor'] else "  "
        gate = "DOWN [#######]" if action['Gate'] == "Lower" else "UP   [       ]"
        
        if action['Signal'] == "Red":
            signal = "[RED]  " 
        elif action['Signal'] == "Green":
            signal = "  [GRN]"
        else:
            signal = "  [OFF]"

        print(f"| Train: {train:<7} | Obstacle: {obstacle:<7} | Signal: {signal} | Gate: {gate} |")


def reflex_agent(percept):
    train, obstacle, emergency = percept

    if emergency == "Active":
        return {"Signal": "Red", "Gate": "Lower", "Reason": "MANUAL EMERGENCY"}

    if obstacle:
        return {"Signal": "Red", "Gate": "Raise", "Reason": "OBSTACLE DETECTED"}

    if train:
        return {"Signal": "Green", "Gate": "Lower", "Reason": "TRAIN PASSING"}

    return {"Signal": "Red", "Gate": "Raise", "Reason": "IDLE / SAFE"}


def simulate():
    test_cases = [
        (False, False, "Neutral"),
        (True,  False, "Neutral"),
        (True,  True,  "Neutral"),
        (False, True,  "Neutral"),
        (False, False, "Active"),
        (True,  False, "Active"),
        (False, False, "Neutral"),
    ]

    env = Environment()

    print(f"{'TIME':<5} | {'PERCEPT (T,O,E)':<20} | {'ACTION':<45} | VISUAL")
    print("-" * 130)

    for i, case in enumerate(test_cases):
        env.transition(case)
        percept = env.percept()
        action = reflex_agent(percept)

        per = f"({int(percept[0])}, {int(percept[1])}, {percept[2][0]})"
        act = f"Sig:{action['Signal']} | Gate:{action['Gate']} | {action['Reason']}"

        print(f"{i+1:<5} | {per:<20} | {act:<45} ", end="")
        env.show(action)

    print("-" * 130)

simulate()
