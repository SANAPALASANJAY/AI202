from copy import deepcopy

class Environment:
    def __init__(self):
        self.st = ['B', 'B', 'B', 'G', 'G', 'G']
        self.boat = {
            "side": "st",
            "state": []
        }
        self.dest = []

    def is_goal(self):
        return bool(len(self.st) == 0)

    def is_valid(self):
        st_g = self.st.count('G')
        st_b = self.st.count('B')
        dest_g = self.dest.count('G')
        dest_b = self.dest.count('B')

        return bool(bool(st_g == 0 or st_g >= st_b) and bool(dest_g == 0 or dest_g >= dest_b))
    
    def state(self):
        return (self.st.count('G'), self.st.count('B'), self.boat['side'])
    
    def move(self, g, b):
        new_env = deepcopy(self)

        if self.boat["side"] == "st":
            for i in range(g):
                new_env.st.remove('G')
                new_env.dest.append('G')
            for i in range(b):
                new_env.st.remove('B')
                new_env.dest.append('B')
            new_env.boat['side'] = "dest"
        else:
            for i in range(g):
                new_env.dest.remove('G')
                new_env.st.append('G')
            for i in range(b):
                new_env.dest.remove('B')
                new_env.st.append('B')
            new_env.boat['side'] = "st"

        return new_env
            
    def show(self):
        print('='*11)
        for i in self.st:
            print(i, end=" ")
        print("")
        print("-"*11)

        if self.boat['side'] == "st":
            print("🛶")
        else:
            print("")
        print("")
        print("")
        if self.boat['side'] == "dest":
            print("🛶")
        else:
            print("")
        
        print("-"*11)
        for i in self.dest:
            print(i, end=" ")
        print("")
        print('='*11)


moves = [('G'), ('B'), ('G', 'B'), ('G', 'G'), ('B', 'B')]

def depth_limited_search(env, limit, explored, path, count):
    count[0] += 1
    if env.is_goal():
        return path
    
    if limit == 0:
        return None
    
    explored.add(env.state())

    for move in moves:
        g = move.count('G')
        b = move.count('B')
        side = env.boat['side']

        if side == "st":
            if g > env.st.count('G') or b > env.st.count('B'):
                continue
        else:
            if g > env.dest.count('G') or b > env.dest.count('B'):
                continue

        new_env = env.move(g, b)
        if new_env.is_valid() and new_env.state() not in explored:
            path.append(move)
            res = depth_limited_search(new_env, limit-1, explored, path, count)
            if res:
                return res
            path.pop()
    
    return None

count = [0]
env = Environment()
exp = set()
solution_dls = depth_limited_search(env, 3, exp, [], count)

print("DLS Solution:", solution_dls)
print("DLS Explored States:", count[0])
print("DLS Explored Unique States:", len(exp))
if (solution_dls):
    env.show()
    for mov in solution_dls:
        g = mov.count('G')
        b = mov.count('B')
        print("")
        env = env.move(g, b)
        print(f"Moving: {mov}")
        env.show()

def iterative_deepening(env, count):
    depth = 0
    explored_num = 0

    while True:
        explored = set()
        res = depth_limited_search(env, depth, explored, [], count)

        explored_num += len(explored)

        if res:
            return res, explored_num, depth
        
        depth += 1


count = [0]
env = Environment()
solution_ids, total_explored, depth = iterative_deepening(env, count)

print("IDS Depth:", depth)
print("IDS Explored States:", count[0])
print("IDS Unique Explored States:", total_explored)
print("IDS Solution:", solution_ids)

env = Environment()
if (solution_ids):
    env.show()
    for mov in solution_ids:
        g = mov.count('G')
        b = mov.count('B')
        print("")
        env = env.move(g, b)
        print(f"Moving: {mov}")
        env.show()
