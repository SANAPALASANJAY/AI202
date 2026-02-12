#include <bits/stdc++.h>
using namespace std;

int max_depth = 28; # For depth limit search
int dfs_depth, bfs_depth;
int dfs_states, bfs_states;

struct State {
    vector<vector<char>> board;
    int x, y, depth;
};

template <typename T>
class Stack {
    private:
        vector<T> elements;
    public:
        void push(const T& value) {
            elements.push_back(value);
        }
        
        void pop() {
            if (isEmpty()) {
                throw runtime_error("Stack is empty");
            }
            elements.pop_back();
        }

        T& top() {
            if (isEmpty()) {
                throw runtime_error("Stack is empty");
            }
            return elements.back();
        }

        bool isEmpty() const {
            return elements.empty();
        }

        size_t size() const {
            return elements.size();
        }
};

template <typename T>
class Queue {
    private:
        struct Node {
            T data;
            Node* next;
            Node(T val) : data(val), next(nullptr) {}
        };

        Node* frontNode;
        Node* rearNode;
    public:
        Queue() : frontNode(nullptr), rearNode(nullptr) {}

        ~ Queue() {
            while(!isEmpty()) {
                pop();
            }
        }

        void push(T val) {
            Node* newNode = new Node(val);
            if (isEmpty()) {
                frontNode = rearNode = newNode;
            } else {
                rearNode->next = newNode;
                rearNode = newNode;
            }
        }

        void pop() {
            if (isEmpty()) {
                return;
            }
            Node* temp = frontNode;
            frontNode = frontNode->next;
            if (frontNode == nullptr) {
                rearNode = nullptr;
            }
            delete temp;
        }

        T front() const {
            if (isEmpty()) {
                throw runtime_error("Queue is empty");
            }
            return frontNode->data;
        }

        bool isEmpty() const {
            return frontNode == nullptr;
        }
};

bool dfs_iterative(vector<vector<char>> start, vector<vector<char>> final, int sx, int sy) {
    Stack<State> st;
    set<vector<vector<char>>> visited;

    st.push({start, sx, sy, 0});
    int count = 0;

    while (!st.isEmpty()) {
        State cur = st.top();
        st.pop();

        if (visited.count(cur.board)) continue;
        visited.insert(cur.board);
        count++;

        if (cur.board == final) {
            dfs_depth = cur.depth;
            dfs_states = count;
            cout << "No. of States Before Reaching Final State (DFS): "
                 << count << " at depth: " << cur.depth << "\n";
            return true;
        }

        int x = cur.x, y = cur.y;
        // Push 0 Up Right Left Down
        if (x > 0) { 
            auto nxt = cur.board;
            swap(nxt[x][y], nxt[x-1][y]);
            st.push({nxt, x-1, y, cur.depth + 1});
        }
        if (y < 2) {
            auto nxt = cur.board;
            swap(nxt[x][y], nxt[x][y+1]);
            st.push({nxt, x, y+1, cur.depth + 1});
        }
        if (y > 0) {
            auto nxt = cur.board;
            swap(nxt[x][y], nxt[x][y-1]);
            st.push({nxt, x, y-1, cur.depth + 1});
        }
        if (x < 2) {
            auto nxt = cur.board;
            swap(nxt[x][y], nxt[x+1][y]);
            st.push({nxt, x+1, y, cur.depth + 1});
        }
    }

    cout << "No solution found\n";
    return false;
}

bool dfs(vector<vector<char>>& curr, vector<vector<char>>& final, int x, int y, int depth, int& count, set<vector<vector<char>>>& visited) {
    count++;
    if (curr == final) {
        cout << "No.of States Before Reaching Final State (DFS): '" << count << "' at depth: " << depth << "\n";
        dfs_states = count;
        dfs_depth = depth;
        return true;
    }

    if (depth >= max_depth) return false;

    visited.insert(curr);

    // Moving zero Down (row + 1)
    if (x < 2) {
        swap(curr[x][y], curr[x + 1][y]);
        if (visited.find(curr) == visited.end()) {
            if (dfs(curr, final, x + 1, y, depth + 1, count, visited)) return true;
        }
        swap(curr[x][y], curr[x + 1][y]);
    }
    // Moving zero Up (row - 1)
    if (x > 0) {
        swap(curr[x][y], curr[x - 1][y]);
        if (visited.find(curr) == visited.end()) {
            if (dfs(curr, final, x - 1, y, depth + 1, count, visited)) return true;
        }
        swap(curr[x][y], curr[x - 1][y]);
    }

    // Moving zero Right (col + 1)
    if (y < 2) {
        swap(curr[x][y], curr[x][y + 1]);
        if (visited.find(curr) == visited.end()) {
            if (dfs(curr, final, x, y + 1, depth + 1, count, visited)) return true;
        }
        swap(curr[x][y], curr[x][y + 1]);
    }

    // Moving zero Left (col - 1)
    if (y > 0) {
        swap(curr[x][y], curr[x][y - 1]);
        if (visited.find(curr) == visited.end()) {
            if (dfs(curr, final, x, y - 1, depth + 1, count, visited)) return true;
        }
        swap(curr[x][y], curr[x][y - 1]);
    }

    visited.erase(curr);
    return false;
}

void bfs(vector<vector<char>>& board, vector<vector<char>>& final) {
    map<vector<vector<char>>, bool> visited;
    int count = 0;
    Queue<pair<vector<vector<char>>, pair<int, int>>> q;
    q.push({board, {1, 1}});
    visited[board] = true;
    int depth = 0;

    vector<vector<char>> Null = {
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    q.push({Null, {0, 0}});

    while (!q.isEmpty()) {
        auto curr = q.front().first;
        auto zero = q.front().second;
        q.pop();
        if (curr == Null) {
            if (!q.isEmpty()) {
                q.push({Null, {0, 0}});
                depth++;
                continue;
            } else {
                break;
            }
        }
        count++;

        if (curr == final) {
            break;
        }

        int x = zero.first, y = zero.second;

        
        // Moving zero down (Up)
        if (x < 2) {
            swap(curr[x][y], curr[x + 1][y]);
            if (!visited[curr]) {
                q.push({curr, {x + 1, y}});
                visited[curr] = true;
            }
            swap(curr[x][y], curr[x + 1][y]);
        }
        // Moving zero left (Right)
        if (y > 0) {
            swap(curr[x][y], curr[x][y - 1]);
            if (!visited[curr]) {
                q.push({curr, {x, y - 1}});
                visited[curr] = true;
            }
            swap(curr[x][y], curr[x][y - 1]);
        }
        // Moving zero right (left)
        if (y < 2) {
            swap(curr[x][y], curr[x][y + 1]);
            if (!visited[curr]) {
                q.push({curr, {x, y + 1}});
                visited[curr] = true;
            }
            swap(curr[x][y], curr[x][y + 1]);
        }
        // Moving zero up (Down)
        if (x > 0) {
            swap(curr[x][y], curr[x - 1][y]);
            if (!visited[curr]) {
                q.push({curr, {x - 1, y}});
                visited[curr] = true;
            }
            swap(curr[x][y], curr[x - 1][y]);
        }
    }

    bfs_depth = depth;
    bfs_states = count;
    cout << "\nNo.of States Visited Before Reaching Final State (BFS): '" << count << "' at depth: " << depth << "\n";

}

int main() {
    vector<vector<char>> board, final;
    board = {
        {'7', '2', '4'},
        {'5', '0', '6'},
        {'8', '3', '1'}
    };

    final = {
        {'0', '1', '2'},
        {'3', '4', '5'},
        {'6', '7', '8'}
    };
    
    int count = 0;
    bfs(board, final);

    // set<vector<vector<char>>> visited;
    // if (!dfs(board, final, 1, 1, 0, count, visited)) {
    //     cout << "\nSolution not found within depth limit." << endl;
    // }
    dfs_iterative(board, final, 1, 1);
    
    cout << "Comparing               BFS  \t DFS \n";
    cout << "In terms of States:   " << bfs_states << "\t" << dfs_states << "\n";
    cout << "In terms of  Depth:     " << bfs_depth << "\t  " << dfs_depth << "\n";
    return 0;
}
