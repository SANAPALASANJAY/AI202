from m1 import *

p = Symbol('P')
q = Symbol('Q')
r = Symbol('R')
l = Symbol('L')
m = Symbol('M')
a = Symbol('A')
b = Symbol('B')
c = Symbol('C')
d = Symbol('D')
e = Symbol('E')
f = Symbol('F')
s = Symbol('S')

KB1 = [
    Implication(p, q),
    Implication(And(l, m), p),
    Implication(And(a, b), l),
    a,
    b,
    m
]

KB2 = [
    Implication(a, b),
    Implication(b, c),
    Implication(c, d),
    a,
    e,
    Implication(And(d, e), f)
]

KB3 = [
    Implication(p, q),
    Implication(r, q),
    Implication(a, p),
    Implication(b, r),
    a,
    b
]

KB4 = [
    Implication(a, b),
    Implication(And(b, c), d),
    Implication(e, c),
    a,
    e
]

KB5 = [
    frozenset({p, q}),
    frozenset({Not(p), r}),
    frozenset({Not(q), s}),
    frozenset({Not(r), s})
]
query5 = [frozenset({Not(s)})]

KB6 = [
    frozenset({Not(p), q}),
    frozenset({Not(q), r}),
    frozenset({Not(s), Not(r)}),
    frozenset({p})
]
query6 = [frozenset({Not(s)})]

def forward_chaining(KB, query):
    print("PREMISES: ")
    q = []
    temp = {}
    inferred = set()
    for premise in KB:
        print(premise.formula())
        if isinstance(premise, Symbol):
            q.append(premise)
            inferred.add(premise.name)
        if isinstance(premise, Implication):
            temp[premise] = premise.antecedent.symbols()
            
    while q:
        i = q.pop(0)
        print("\nChecking with:", i)
        if i == query:
            return True
        for key, value in temp.items():
            print("before: ", value)
            if set(i.symbols()).issubset(value):
                temp[key].difference_update(i.symbols())
                if len(temp[key]) == 0:
                    if key.consequent not in q:
                        q.append(key.consequent)
            print("after: ", value)
                    
    return False

def backward_chaining(KB, query):
    inferred = set()
    visiting = set()
    
    for p in KB:
        if isinstance(p, Symbol):
            inferred.add(p.name)
            
    q = list(query.symbols())
    
    def rec(KB, target_name):
        if target_name in inferred:
            return True
            
        if target_name in visiting:
            return False
            
        visiting.add(target_name)
        
        for premise in KB:
            if isinstance(premise, Implication) and premise.consequent.name == target_name:
                
                all_premises_proven = True
                for ant_name in premise.antecedent.symbols():
                    if not rec(KB, ant_name):
                        all_premises_proven = False
                        break
                
                if all_premises_proven:
                    inferred.add(target_name)
                    return True
                    
        visiting.remove(target_name)
        return False
    
    for i in q:
        if not rec(KB, i):
            return False
            
    return True
            
                
def pl_resolve(ci, cj):
    resolvents = []
    
    for li in ci:
        for lj in cj:
            
            if (isinstance(li, Not) and li.operand == lj) or \
               (isinstance(lj, Not) and lj.operand == li):
                
                resolvent = set(ci).union(set(cj))
                
                resolvent.remove(li)
                resolvent.remove(lj)
                
                resolvents.append(frozenset(resolvent))
                
    return resolvents


def resolution(KB_clauses, query_clauses):
    clauses = set(KB_clauses).union(set(query_clauses))
    
    new_clauses = set()
    
    while True:
        clauses_list = list(clauses)
        n = len(clauses_list)
        
        for i in range(n):
            for j in range(i + 1, n):
                ci = clauses_list[i]
                cj = clauses_list[j]
                
                resolvents = pl_resolve(ci, cj)
                
                for resolvent in resolvents:
                    if len(resolvent) == 0:
                        return True
                    
                    new_clauses.add(resolvent)
        
        if new_clauses.issubset(clauses):
            return False
            
        clauses.update(new_clauses)
    
    
    
print("-------FORWARD CHAINING--------")
print(forward_chaining(KB1, q))
print("---------------")
print(forward_chaining(KB2, f))
print("-------BACKWARD CHAINING--------")
print(backward_chaining(KB3, q))
print("---------------")
print(backward_chaining(KB4, d))
print("-------RESOLUTION CHAINING--------")
print(resolution(KB5, query5))
print("---------------")
print(resolution(KB6, query6))
