#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector <vector <ll>> g(n);
	for (int i = 0; i < n; i++) {
		ll from, to;
		cin >> from >> to;
		g[from].push_back(to);
		g[to].push_back(from);
	}
	ll min_degree = LLONG_MAX, max_degree = LLONG_MIN;
	for (int i = 0; i < n; i++) {
		min_degree = min(min_degree, (ll)g[i].size());
		max_degree = max(max_degree, (ll)g[i].size());
	}
	cout << min_degree << " " << max_degree << "\n";
	return 0;
}
