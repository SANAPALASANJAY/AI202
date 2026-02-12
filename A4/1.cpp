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
    {"New_York", 10},
    {"Providence", 11},
    {"Boston", 12},
    {"Portland", 13}
};
vector<string> ntoc = {
    "Chicago","Indianapolis","Columbus","Cleveland","Detroit",
    "Buffalo","Pittsburgh","Syracuse","Baltimore","Philadelphia",
    "New_York","Providence","Boston","Portland"
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

void dfs(vector<vector<pair<int, int>>>& g, int i, int d,
         vector<pair<long long, vector<int>>>& ans,
         long long cost, vector<int>& visited, vector<int>& path, int& count) {

    if (count > 0) return;

    visited[i] = 1;
    path.push_back(i);

    if (i == d) {
        cout << "DFS Found Path : ";
        for (size_t j = 0; j < path.size(); ++j) {
            cout << ntoc[path[j]] << (j == path.size() - 1 ? "" : " -> ");
        }
        cout << " | Cost: " << cost << endl;
        count++;
        
        path.pop_back();
        visited[i] = 0;
        return; 
    } 
    
    for (auto &e : g[i]) {
        if (!visited[e.first]) {
            dfs(g, e.first, d, ans, cost + e.second, visited, path, count);
            if (count > 0) return; 
        }
    }

    path.pop_back();
    visited[i] = 0;
}

void bfs(vector<vector<pair<int, int>>>& g, int s, int d,
         vector<pair<long long, vector<int>>>& ans, int& count) {

    queue<pair<int, pair<long long, vector<int>>>> q;
    q.push({s, {0, {s}}});
    
    while (!q.empty()) {
        auto front = q.front(); q.pop();

        int u = front.first;
        long long cost = front.second.first;
        vector<int> curr_path = front.second.second;

        if (u == d) {
            cout << "BFS Found Path : ";
            for (size_t j = 0; j < curr_path.size(); ++j) {
                cout << ntoc[curr_path[j]] << (j == curr_path.size() - 1 ? "" : " -> ");
            }
            cout << " | Cost: " << cost << endl;
            count++;
            return;
        }

        for (auto& edge : g[u]) {
            int v = edge.first;
            int w = edge.second;
            if (find(curr_path.begin(), curr_path.end(), v) == curr_path.end()) {
                auto new_path = curr_path;
                new_path.push_back(v);
                q.push({v, {cost + w, new_path}});
            }
        }
    }
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

struct State {
    int u;
    long long edge_cost;
    vector<int> path;

    bool operator>(const State& other) const {
        return edge_cost > other.edge_cost;
    }
};


void greedy_search(vector<vector<pair<int, int>>>& g, int s, int d) {
    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push({s, 0, {s}});
    vector<bool> visited(g.size(), false);

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int u = current.u;
        vector<int> curr_path = current.path;

        if (u == d) {
            long long total_cost = 0;

            // calculate full path cost
            for (int i = 0; i < curr_path.size() - 1; ++i) {
                for (auto &e : g[curr_path[i]]) {
                    if (e.first == curr_path[i+1]) {
                        total_cost += e.second;
                        break;
                    }
                }
            }

            cout << "Greedy Path: ";
            for (size_t i = 0; i < curr_path.size(); ++i) {
                cout << ntoc[curr_path[i]]
                     << (i == curr_path.size() - 1 ? "" : " -> ");
            }
            cout << " | Total Cost: " << total_cost << endl;
            return;
        }

        if (visited[u]) continue;
        visited[u] = true;

        for (auto &edge : g[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!visited[v]) {
                vector<int> new_path = curr_path;
                new_path.push_back(v);

                // 🔥 ONLY push using immediate edge weight
                pq.push({v, w, new_path});
            }
        }
    }

    cout << "No path found." << endl;
}


int main() {
    vector<vector<pair<int,int>>> graph(14);
    vector<int> visited(14, 0);
    make_graph(graph);

    string start, end;
    cin >> start >> end;

    int s = cton[start];
    int d = cton[end];
    
    greedy_search(graph, s, d);

    vector<pair<long long, vector<int>>> ans;
    vector<int> path;
    int count = 0;

    dfs(graph, s, d, ans, 0, visited, path, count);
    count = 0;
    bfs(graph, s, d, ans, count);

    for (auto &res : ans) {
        for (int node : res.second) {
            cout << ntoc[node];
            if (node != res.second.back()) cout << " -> ";
        }
        cout << "  : " << res.first << "\n";
    }

    return 0;
}
