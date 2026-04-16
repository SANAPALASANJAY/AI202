import itertools
from m1 import *

def print_truth_table(proposition):
    symbols = sorted(list(proposition.symbols()))
    formula_str = proposition.formula()
    
    widths = [max(len(sym), 1) for sym in symbols]
    formula_width = max(len(formula_str), 1)
    
    header_parts = [sym.ljust(w) for sym, w in zip(symbols, widths)]
    header_parts.append(formula_str.ljust(formula_width))
    header = " | ".join(header_parts)
    
    print("-" * len(header))
    print(header)
    print("-" * len(header))
    
    combinations = itertools.product([False, True], repeat=len(symbols))
    
    for combo in combinations:
        model = dict(zip(symbols, combo))
        result = proposition.evaluate(model)
        
        row_parts = [("T" if model[sym] else "F").ljust(w) for sym, w in zip(symbols, widths)]
        row_parts.append(("T" if result else "F").ljust(formula_width))
        print(" | ".join(row_parts))
        
    print("-" * len(header) + "\n")


if __name__ == "__main__":
    P = Symbol('P')
    Q = Symbol('Q')
    R = Symbol('R')

    # 1. ~P -> Q
    prop1 = Implication(Not(P), Q)

    # 2. ~P ∧ ~Q
    prop2 = And(Not(P), Not(Q))

    # 3. ~P ∨ ~Q
    prop3 = Or(Not(P), Not(Q))

    # 4. ~P -> ~Q
    prop4 = Implication(Not(P), Not(Q))

    # 5. ~P <-> ~Q
    prop5 = Biconditional(Not(P), Not(Q))

    # 6. (P ∨ Q) ∧ (~P -> Q)
    prop6 = And(Or(P, Q), Implication(Not(P), Q))

    # 7. ((P ∨ Q) -> ~R)
    prop7 = Implication(Or(P, Q), Not(R))

    # 8. (((P ∨ Q) -> ~R) <-> ((~P ∧ ~Q) -> ~R))
    prop8 = Biconditional(
        Implication(Or(P, Q), Not(R)), 
        Implication(And(Not(P), Not(Q)), Not(R))
    )

    # 9. (((P -> Q) ∧ (Q -> R)) -> (Q -> R))
    prop9 = Implication(
        And(Implication(P, Q), Implication(Q, R)), 
        Implication(Q, R)
    )

    # 10. (((P -> (Q ∨ R)) -> (~P ∧ ~Q ∧ ~R)))
    prop10 = Implication(
        Implication(P, Or(Q, R)), 
        And(Not(P), Not(Q), Not(R))
    )

    propositions = [
        (1, prop1), (2, prop2), (3, prop3), (4, prop4), (5, prop5),
        (6, prop6), (7, prop7), (8, prop8), (9, prop9), (10, prop10)
    ]

    # Print all the truth tables
    for num, prop in propositions:
        print(f"Proposition {num}:")
        print_truth_table(prop)
