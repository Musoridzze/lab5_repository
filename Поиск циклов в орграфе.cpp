#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> path;
vector<vector<int>> cycles;
void dfs(int u, int startNode) {
 visited[u] = true;
 path.push_back(u);
 for (int v : adj[u]) {
 if (v == startNode && path.size() > 2) { // Цикл найден
 cycles.push_back(path);
 }
 else if (!visited[v]) {
 dfs(v, startNode);

 }
 }
 visited[u] = false;
 path.pop_back();
}
int main() {
 int n;
 cout << "Amount of peaks: ";
 cin >> n;
 adj.resize(n);
 visited.resize(n, false);
 cout << "Generate path from peaks to other peaks randomly or manually? \n1 -
random; 0 - manual:\n";
 int chce;
 cin >> chce;
 if (chce == 1) {
 for (int i = 0; i < n; ++i) {
 int u;
 cout << "\n" << i << " -> ";
 int cntr = 0;
 while (true) {
 int vcand = ((rand() % (n + 1)) - 1);
 int v;
 if ((vcand == i) && (i != n)) {
 v = vcand + 1;
 }

 else if ((vcand == i) && (i == n)) {
 v = vcand - 1;
 }
 else {
 v = vcand;
 }
 cntr++;
 if (cntr == 4) v = -1;
 if (v == -1) break;
 adj[i].push_back(v);
 cout << v << " ";
 }
 }
 }
 else if (chce == 0) {
 cout << "Path from peak to other peaks (-1 for end input):" << endl;
 for (int i = 0; i < n; ++i) {
 int u;
 cout << i << " -> ";
 while (true) {
 int v;
 cin >> v;
 if (v == -1) break;
 adj[i].push_back(v);
 }
 }
 }
 for (int i = 0; i < n; ++i) {
 dfs(i, i);
 }

 // Удаляем дубликаты циклов (циклы, которые отличаются только порядком
обхода)
 sort(cycles.begin(), cycles.end());
 cycles.erase(unique(cycles.begin(), cycles.end()), cycles.end());
 cout << "\nFound cycles:" << endl;
 if (cycles.empty()) {
 cout << "No cycles found." << endl;
 }
 else {
 for (const auto& cycle : cycles) {
 for (int i = 0; i < cycle.size(); ++i) {
 cout << cycle[i] << (i == cycle.size() - 1 ? "" : " -> ");
 }
 cout << " -> " << cycle[0];
 cout << endl;
 }
 }
 return 0;
}