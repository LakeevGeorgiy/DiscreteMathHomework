#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
typedef long long ll;

void PrufferCodeStep(priority_queue<string, vector<string>, greater<string>>& q, vector <vector<ll>>& g, map<string, int>&mp, vector <ll>& pruffer, vector<string>& name) {
	// extract min leaf (lexicographically by name)
  ll v = mp[q.top()];
	q.pop();
	ll u = g[v].front();
  // find vertex, which is connected with leaf
	pruffer.push_back(u);
	for (int i = 0; i < g[u].size(); i++) {
    // remove edge between leaf and her neighbour
		if (g[u][i] == v)
			g[u].erase(g[u].begin() + i);
	}
  // if vertex u became leaf, then push to queue
	if (g[u].size() == 1)
		q.push(name[u]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ifstream in("input.txt");
	ll n = 44, m = 43;
	vector <vector<ll>> g(n);
	map<string, int> mp;
	vector <string> name(n);
	ll pok = 0;
	for (int i = 0; i < m; i++) {
		string from, to;
		ll w;
		in >> from >> to >> w;

		if (mp.find(from) == mp.end()) {
			mp.emplace(from, pok++);
			name[pok - 1] = from;
		}
		if (mp.find(to) == mp.end()) {
			mp.emplace(to, pok++);
			name[pok - 1] = to;
		}

		ll u = mp[from], v = mp[to];
		g[u].push_back(v);
		g[v].push_back(u);
	}

  // priority queue for min
	priority_queue<string, vector<string>, std::greater<string>> q;
	for (int i = 0; i < n; i++)
		if (g[i].size() == 1)
			q.push(name[i]);
  // build pruffer's code
	vector <ll>pruffer;
	for (int i = 0; i < n - 2; i++) {
		PrufferCodeStep(q, g, mp, pruffer, name);
	}
  // print contries 
	for (int i = 0; i < pruffer.size(); i++) {
		cout << name[pruffer[i]] << " ";
	}
	return 0;
}
