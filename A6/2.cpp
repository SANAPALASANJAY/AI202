#include <bits/stdc++.h>
using namespace std;

#define N 5
typedef pair<int,int> pii;

int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};

int h(pii a, pii b){
    return abs(a.first-b.first)+abs(a.second-b.second);
}

bool valid(int x,int y, vector<vector<int>>& m){
    return x>=0 && x<N && y>=0 && y<N && m[x][y]!=1;
}

struct Node{
    int f;  
    pii point;  
    Node(int cost,pii p){
        f = cost;
        point = p;
    }
};

class priorityqueue{
    vector<Node> data;
    int frontIndex;
public:
    priorityqueue(){
        frontIndex = 0;
    }
    void push(Node x){
        data.push_back(x);
        int i = data.size()-1;
        while(i > frontIndex && data[i].f < data[i-1].f){
            swap(data[i], data[i-1]);
            i--;
        }
    }
    void pop(){
        frontIndex++;
    }
    Node top(){
        return data[frontIndex];
    }
    bool empty(){
        return frontIndex >= data.size();
    }
};

int step = 0;
vector<vector<string>> display(N, vector<string>(N, "   "));

void make_display(vector<vector<int>>& maze, vector<pii>& goals) {
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(maze[i][j] == 1) display[i][j] = " # ";
        }
    }

    display[0][0] = 'S';

    for(auto g : goals){
        display[g.first][g.second] = 'G';
    }
}



vector<pii> astar(vector<vector<int>>& m, pii s, pii g){
    priorityqueue pq;
    vector<vector<pii>> parent(N,vector<pii>(N,{-1,-1}));
    vector<vector<int>> cost(N,vector<int>(N,INT_MAX));

    pq.push(Node(h(s,g), s));
    cost[s.first][s.second] = 0;
    vector<pii> path;

    while(!pq.empty()){
        Node current = pq.top();
        pq.pop();

        pii cur = current.point;
        path.push_back(cur);
        display[cur.first][cur.second] = to_string(step++);
        int r = 3 - display[cur.first][cur.second].size();
        for (int y = 0; y < r; y++) {
            display[cur.first][cur.second] += " ";
        }

        if(cur == g) {
            step--;
            break;
        }
        for(int i=0;i<4;i++){
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if(valid(nx,ny,m)){
                int newCost = cost[cur.first][cur.second] + 1;
                if(newCost < cost[nx][ny]){
                    cost[nx][ny] = newCost;
                    int f = newCost + h({nx,ny},g);
                    pq.push(Node(f, {nx,ny}));
                    parent[nx][ny] = cur;
                }
            }
        }
    }
    // vector<pii> path;
    // if(cost[g.first][g.second] == INT_MAX) return path;
    // pii at = g;
    // while(at != s){
    //     path.push_back(at);
    //     at = parent[at.first][at.second];
    // }
    // path.push_back(s);
    // reverse(path.begin(),path.end());
    return path;
}
int main(){

    vector<vector<int>> maze={
        {2,0,0,0,1},
        {0,1,0,0,3},
        {0,3,0,1,1},
        {0,1,0,0,1},
        {3,0,0,0,3}
    };

    pii start;
    vector<pii> goals;
    goals = {
        {2, 1},
        {4, 0},
        {4, 4},
        {1, 4}
    };
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(maze[i][j] == 2) start = {i,j};
            // if(maze[i][j] == 3) goals.push_back({i,j});
        }
    }

    make_display(maze, goals);

    vector<pii> visited;
    int n = goals.size();

    for(int i = 0; i < 4; i++){
        int heu = INT_MAX;
        pii g;
        for (auto k: goals) {
            if (h(start, k) < heu) {
                heu = h(start, k);
                g = k;
            }
        }
        auto it = std::find(goals.begin(), goals.end(), g);
        goals.erase(it);

        vector<pii> path = astar(maze,start,g);
        for(auto p:path){
            visited.push_back(p);
        }
        start = g;
        cout << "\nFound goal at: {" << start.first << "," << start.second << "}\n\n";
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout << display[i][j] << " ";
            }
            cout << endl;
        }
    }




    // for(auto p : visited){
    //     display[p.first][p.second] = '*';
    // }

    cout << "\nFinal Maze Visualization:\n\n";
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << display[i][j] << " ";
        }
        cout << endl;
    }
}
