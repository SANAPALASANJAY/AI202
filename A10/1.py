from pypdf import PdfReader
import numpy as np

reader = PdfReader('cities.pdf')
text = reader.pages[0].extract_text() + "\n" + reader.pages[1].extract_text()

coord = []
temp = text.split("\n")

for t in temp:
    co = list(map(float, t.split(" ")))
    coord.append(co)
    
cities = np.array(coord)

def cost_function(cities, airports):
    cost = 0
    for city in cities:
        dist = [np.sum((city - airport)**2) for airport in airports]
        cost += min(dist)
    
    return cost

def gradient_descent(cities, alpha, epochs=100):
    print("-----------------GRADIENT DESCENT METHOD----------------")
    cost = float('inf')
    # np.random.seed(43)
    airports = np.random.rand(3, 2) * 6
    
    for epoch in range(epochs):
        grads = np.zeros((3, 2))
        
        for city in cities:
            dist = np.sum((airports - city)**2, axis=1)
            
            closest = np.argmin(dist)
            
            grad = 2 * (airports[closest] - city)
            grads[closest] += grad
        
        airports = airports - (alpha * grads)
        temp = cost_function(cities, airports)
        cost = min(cost, temp)
        print(f"Cost at Epoch{epoch+1}: {temp:.2f}\nAirports: \n{airports}\n")
    
    print("\nFinal Optimized Airport Coordinates:\n", airports, f"Cost: {cost}")

def newton_raphson(cities, epochs=10):
    print("------------------NEWTON RAPHSON METHOD-----------------")
    np.random.seed(43)
    airports = np.random.rand(3, 2) * 6
    
    for epoch in range(epochs):
        grads = np.zeros((3, 2))
        hessians = np.zeros((3, 2))
        
        for city in cities:
            dist = np.sum((airports - city)**2, axis=1)
            closest = np.argmin(dist)
            
            grad = 2 * (airports[closest] - city)
            grads[closest] += grad
            
            hessian = 2 
            hessians[closest] += hessian
            
        for i in range(3):
            if hessians[i, 0] > 0:
                step = grads[i] / hessians[i]
                airports[i] = airports[i] - step
                
        cost = cost_function(cities, airports)
        print(f"Cost at Epoch {epoch+1}: {cost:.2f}")
        print(f"Airports:\n{airports}\n")
        
    print("\nFinal Optimized Airport Coordinates (Newton-Raphson):\n", airports)
    print(f"Final Cost: {cost:.2f}")

newton_raphson(cities, 1)
gradient_descent(cities, 0.01, 100)
