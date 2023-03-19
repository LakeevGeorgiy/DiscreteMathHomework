#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ifstream in("input.txt");
	ll n = 44, m = 43;
  // graph
	vector <vector<ll>> g(n, vector <ll>(n, INT_MAX));
	map<string, int> mp;
	vector <string> name(n);
	ll pok = 0;
	for (int i = 0; i < m; i++) {
		string from, to;
		ll w;
		in >> from >> to >> w;
    // read the country and match number to the country
		if (mp.find(from) == mp.end()) {
			mp.emplace(from, pok++);
			name[pok - 1] = from;
		}
		if (mp.find(to) == mp.end()) {
			mp.emplace(to, pok++);
			name[pok - 1] = to;
		}

    // adjacency table
		ll u = mp[from], v = mp[to];
		g[u][v] = w;
		g[v][u] = w;
	}
  
  // Floyd-Warshal
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}
  // maximal distance for every vertex
	vector <ll> dist(n);
	for (int i = 0; i < n; i++) {
		ll max = 0;
		for (int j = 0; j < n; j++) {
			max = ::max(max, g[i][j]);
		}
		dist[i] = max;
	}
  // value of centroid
	ll ans = *min_element(dist.begin(), dist.end());
	for (int i = 0; i < n; i++) {
		if (dist[i] == ans) {
			cout << name[i] << "\n";
		}
	}
	return 0;
}
