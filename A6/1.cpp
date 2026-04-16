#include <bits/stdc++.h>
using namespace std;
unordered_map<string, int> cton = {
    {"Chicago", 0},
    {"Indianapolis", 1},
    {"Columbus", 2},
    {"Cleveland", 3},
    {"Detroit", 4},
    {"Buffalo", 5},
    {"Pittsburgh", 6},
    {"Syracuse", 7},
    {"Baltimore", 8},
    {"Philadelphia", 9},
    {"New York", 10},
    {"Providence", 11},
    {"Boston", 12},
    {"Portland", 13}
};

vector<string> ntoc = {
    "Chicago","Indianapolis","Columbus","Cleveland","Detroit",
    "Buffalo","Pittsburgh","Syracuse","Baltimore","Philadelphia",
    "New York","Providence","Boston","Portland"
};

void make_graph(vector<vector<pair<int, int>>>& g) {
    auto addEdge = [&](size_t u, size_t v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };

    addEdge(0, 4, 283);   // Chicago - Detroit
    addEdge(0, 3, 345);   // Chicago - Cleveland
    addEdge(0, 1, 182);   // Chicago - Indianapolis

    addEdge(1, 2, 176);   // Indianapolis - Columbus

    addEdge(2, 3, 144);   // Columbus - Cleveland
    addEdge(2, 6, 185);   // Columbus - Pittsburgh

    addEdge(3, 4, 169);   // Cleveland - Detroit
    addEdge(3, 5, 189);   // Cleveland - Buffalo
    addEdge(3, 6, 134);   // Cleveland - Pittsburgh

    addEdge(4, 5, 256);   // Detroit - Buffalo

    addEdge(5, 6, 215);   // Buffalo - Pittsburgh
    addEdge(5, 7, 150);   // Buffalo - Syracuse

    addEdge(6, 8, 247);   // Pittsburgh - Baltimore
    addEdge(6, 9, 305);   // Pittsburgh - Philadelphia

    addEdge(7,10, 254);   // Syracuse - New York
    addEdge(7,12, 312);   // Syracuse - Boston
    addEdge(7, 9, 253);   // Syracuse - Philadelphia

    addEdge(8, 9, 101);   // Baltimore - Philadelphia

    addEdge(9,10, 97);    // Philadelphia - New York

    addEdge(10,11,181);   // New York - Providence
    addEdge(10,12,215);   // New York - Boston

    addEdge(11,12,50);    // Providence - Boston

    addEdge(12,13,107);   // Boston - Portland
}

int h(string city) {
    if (city == "Boston") {
        return 0;
    } else if (city == "Providence") {
        return 50;
    } else if (city == "Portland") {
        return 107;
    } else if (city == "New York") {
        return 215;
    } else if (city == "Philadelphia") {
        return 270;
    }  else if (city == "Baltimore") {
        return 360;
    }  else if (city == "Syracuse") {
        return 260;
    }  else if (city == "Buffalo") {
        return 400;
    }  else if (city == "Pittsburgh") {
        return 470;
    }  else if (city == "Cleveland") {
        return 550;
    }  else if (city == "Columbus") {
        return 640;
    }  else if (city == "Detroit") {
        return 610;
    }  else if (city == "Indianapolis") {
        return 780;
    }  else if (city == "Chicago") {
        return 860;
    }
    return INT_MAX;
}

template <typename T>
class Pq {
private:
    vector<T> heap;

    void heapify_up(int idx) {
        if (idx == 0) return;
        int parent = (idx - 1) / 2;

        if (heap[parent] > heap[idx]) {
            swap(heap[parent], heap[idx]);
            heapify_up(parent);
        }
    }

    void heapify_down(int idx) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            heapify_down(smallest);
        }
    }

public:
    void push(T s) {
        heap.push_back(s);
        heapify_up(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapify_down(0);
        }
    }

    T top() {
        return heap[0];
    }

    bool empty() {
        return heap.empty();
    }
};

struct node{
    int city;
    int h;
    vector<int> path;
};

void gbfs(vector<vector<pair<int, int>>>& graph) {
    int s = cton["Chicago"], d = cton["Boston"];
    Pq<pair<int, pair<int, vector<int>>>> pq;
    int states = 0;
    vector<int> visited(14, 0);
    pq.push({h(ntoc[s]), {s, {}}});

    while (!pq.empty()) {
        auto f = pq.top();
        pq.pop();

        int u = f.second.first;

        if (visited[u]) continue;
        visited[u] = 1;
        states++;
        vector<int> new_path = f.second.second;
        new_path.push_back(u);

        if (u == d) {
            cout << "Greedy Best First Search:\n";
            int n = new_path.size();
            int totalCost = 0;

            for (int i = 0; i < n - 1; i++) {
                for (auto edge : graph[new_path[i]]) {
                    if (edge.first == new_path[i + 1]) {
                        totalCost += edge.second;
                        break;
                    }
                }
            }
            for (int i = 0; i < n - 1; i++) {
                cout << ntoc[new_path[i]] << " -> ";
            }
            cout << ntoc[new_path[n - 1]] << "\n";
            cout << "Path Cost: " << totalCost << "\n";
            cout << "Number of states: " << states << "\n";
            return;
        }

        for (auto n : graph[u]) {
            int v = n.first;

            if (!visited[v]) {
                pq.push({h(ntoc[v]), {v, new_path}});
            }
        }
    }
    cout << "No path found\n";
}

void astar(vector<vector<pair<int, int>>>& graph){
    int s = cton["Chicago"];
    int d = cton["Boston"];

    Pq<pair<int, pair<int, pair<int, vector<int>>>>> pq;

    vector<int> visited(14, 0);
    int states = 0;

    pq.push({h(ntoc[s]), {s, {0, {}}}});

    while (!pq.empty()) {
        auto f = pq.top();
        pq.pop();

        int u = f.second.first;
        int g_cost = f.second.second.first;

        if (visited[u]) continue;

        visited[u] = 1;
        states++;

        vector<int> path = f.second.second.second;
        path.push_back(u);

        if (u == d) {
            cout << "A* Search:" << "\n";
            int n = path.size();
            for (int i = 0; i < n - 1; i++) {
                cout << ntoc[path[i]] << " -> ";
            }
            cout << ntoc[path[n - 1]] << "\n";
            cout << "Total Cost: " << g_cost << "\n";
            cout << "States Visited: " << states << "\n";

            return;
        }

        for (auto edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!visited[v]) {
                int new_g = g_cost + w;
                int new_f = new_g + h(ntoc[v]);

                pq.push({new_f, {v, {new_g, path}}});
            }
        }
    }

    cout << "No path found\n";
} 

int main() {
    int count = 0;
    vector<vector<pair<int,int>>> graph(14);
    vector<int> visited(14, 0);
    make_graph(graph);

    gbfs(graph);
    astar(graph);
    return 0;
}
