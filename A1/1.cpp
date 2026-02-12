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

void dfs(vector<vector<pair<int, int>>>& g, int i, int d,
         vector<pair<long long, vector<int>>>& ans,
         long long cost, vector<int>& visited, vector<int>& path, int& count) {

    visited[i] = 1;
    path.push_back(i);

    if (i == d) {
        ans.push_back({cost, path});
        count++;
    } else {
        for (auto &e : g[i]) {
            if (!visited[e.first]) {
                dfs(g, e.first, d, ans, cost + e.second, visited, path, count);
            }
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
            ans.push_back({cost, curr_path});
            count++;
            continue;
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

void bfs_exp_cost(vector<vector<pair<int, int>>>& g, int s, int d, int& cost) {
    queue<pair<pair<int, int>, vector<int>>> q;
    q.push({{s, 0}, {s}});

    while(!q.empty()) {
        auto front = q.front(); q.pop();
        int u = front.first.first;
        vector<int> curr = front.second;
        cost += front.first.second;
        if (u == d) {
            return;
        }

        for (auto& edge: g[u]) {
            int v = edge.first;
            int w = edge.second;

            if (find(curr.begin(), curr.end(), v) == curr.end()) {
                auto new_path = curr;
                new_path.push_back(v);
                q.push({{v, w}, new_path});
                
            }
        }
    }
}

int main() {
    int count = 0;
    vector<vector<pair<int,int>>> graph(14);
    vector<int> visited(14, 0);
    make_graph(graph);

    string start, end;
    cin >> start >> end;

    int s = cton[start];
    int d = cton[end];

    vector<pair<long long, vector<int>>> ans;
    vector<int> path;

    // dfs(graph, s, d, ans, 0, visited, path, count);
    bfs(graph, s, d, ans, count);
    // int cost = 0;
    // bfs_exp_cost(graph, s, d, cost);
    // cout << "BFS EXPLORATION COST: " << cost;

    // sort(ans.begin(), ans.end(),
    //      [](auto &a, auto &b) { return a.first < b.first; });

    for (auto &res : ans) {
        for (int node : res.second) {
            cout << ntoc[node];
            if (node != res.second.back()) cout << " -> ";
        }
        cout << "  : " << res.first << "\n";
    }

    cout << "Total paths: " << count;

    return 0;
}
