#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

struct ListOfEdges {
	ll weight = 0;
	ll from;
	ll to;
};

bool operator<(ListOfEdges& lhs, ListOfEdges& rhs) {
	return lhs.weight < rhs.weight;
}

void mst(ll n, ll m) {

	vector <ListOfEdges> a(m);
	vector <ll> id(n + 1);

	for (int i = 0; i <= n; i++) id[i] = i;

	for (int i = 0; i < m; i++){
		cin >> a[i].from >> a[i].to >> a[i].weight;
	}
	sort(a.begin(), a.end());
	ll sum = 0;
	vector <pair<ll, ll>> ans;
	ll pok = 0;
	for (int i = 0; i < m; i++) {
		ll to = a[i].to;
		ll from = a[i].from;
		if (id[to] != id[from]) {
			sum += a[i].weight;
			ans.push_back({ a[i].from, a[i].to });
			ll old = id[to];
			for (int j = 1; j <= n; j++) {
				if (id[j] == old)
					id[j] = id[from];
			}
		}
	}
	for (auto& now : ans) {
		cout << now.first << " " << now.second << "\n";
	}
	cout << sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll n, m;
	cin >> n >> m;
	return mst(n, m), 0;
}
