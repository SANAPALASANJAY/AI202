#include <bits/stdc++.h>
using namespace std;

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
    set<vector<vector<char>>> visited;

    dfs_iterative(board, final, 1, 1);
    return 0;
}
