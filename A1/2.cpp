#include<bits/stdc++.h>
using namespace std;

void make_graph(unordered_map<string,vector<string>>& g) {
    g["Raj"]   = {"Sunil","Neha"};
    g["Akash"] = {"Sunil","Priya"};
    g["Sunil"] = {"Raj", "Maya","Sneha","Akash"};
    g["Sneha"] = {"Sunil", "Neha","Rahul"};
    g["Maya"]  = {"Sunil", "Rahul","Arjun1"};
    g["Priya"] = {"Raj","Neha", "Aarav","Akash"};
    g["Neha"]  = {"Raj", "Akash", "Aarav","Sneha"};
    g["Neha1"] = {"Priya","Neha","Rahul","Aarav"};
    g["Rahul"] = {"Neha","Neha1","Sneha","Pooja","Maya","Arjun"};
    g["Aarav"] = {"Neha","Neha1", "Arjun"};
    g["Arjun"] = {"Rahul", "Neha1","Aarav"};
    g["Arjun1"] = {"Maya","Pooja"};
    g["Pooja"] = {"Rahul","Arjun", "Arjun1"};
}

vector<string> bfs(unordered_map<string,vector<string>> &g, string src){
    size_t n = g.size();
    queue<string> q;
    unordered_map<string,bool> visited ;
    vector<string> res;
    visited[src] = true;
    q.push(src);
    q.push("");
    while(!q.empty()){
        string s = q.front();
        q.pop();
        if (s == "") {
            if (q.empty()) break;
            res.push_back("\n");
            q.push("");
            continue;
        }
        res.push_back(s);
        
        for(auto it : g[s]){
            if(!visited[it]){
                visited[it] = true;
                q.push(it);
            }
        }
    }
    return res;
}

void dfsrec(unordered_map<string,bool> &visited,string s,unordered_map<string,vector<string>> &g/*,vector<string> &ans*/, size_t c){
    visited[s] = true;
    size_t x = c * 5;
    string l(x, ' ');
    cout << l << "|____" << s <<"\n";
    // ans.push_back(s);
    for(auto it : g[s]){
        if(visited[it] == false) dfsrec(visited,it,g/*,ans*/, c + 1);
    }
}
vector<string> dfs(unordered_map<string,vector<string>> &net, string user, vector<string>& users){
    unordered_map<string,bool> visited;
    vector<string> ans;
    string s1 = user;
    int i = 0;
    do {
        if(visited[s1] == false){
            cout << "\n";
            dfsrec(visited,s1,net/*,ans*/,0);
        }
        s1 = users[(size_t)i];
        i++;
    } while (i < 13);
    return ans;
}

int main(){
    unordered_map<string,vector<string>> net;
    make_graph(net);

    vector<string> users = {"Raj", "Priya", "Aarav","Neha","Neha1","Sneha","Pooja","Maya","Arjun", "Arjun1", "Sunil", "Akash", "Rahul"};
    cout << "\nDFS:\n";
    for (auto user: users) {
        dfs(net, user, users);
        cout << "======================================================";
    }
    cout << "\n\n";

    for (auto user: users) {
        auto res = bfs(net, user);
        for(auto it : res) cout << it << " ";
        cout << "\n======================================================\n";
    }
}
