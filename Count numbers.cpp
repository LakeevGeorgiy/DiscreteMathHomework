#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef long double ld;

ll n, k, v1, v2, v3, v5;

ll P(ll l);
ll K(ll l);
ll M(ll l);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;

	v1 = floor(static_cast<ld>(n) / 3);
	v2 = floor(static_cast<ld>(n + 2) / 3);
	v3 = floor(static_cast<ld>(n + 1) / 3);

	v5 = floor(static_cast<ld>(n) / 5);

	cout << P(k) + v5 * (pow(n, k - 1) - K(k - 1));

	return 0;
}

unordered_map<ll, ll> p;
unordered_map<ll, ll> k_;
unordered_map<ll, ll> m;

ll P(ll l) {
	if (p.find(l) != p.end())
		return p[l];
	if (l == 1)
		return v1;
	return p[l] = P(l - 1) * v1 + K(l - 1) * v3 + M(l - 1) * v2;
}

ll K(ll l) {
	if (k_.find(l) != k_.end())
		return k_[l];
	if (l == 1)
		return floor(static_cast<ld>(n + 2) / 3);
	return k_[l] = P(l - 1) * v3 + K(l - 1) * v1 + M(l - 1) * v3;
}

ll M(ll l) {
	if (m.find(l) != m.end())
		return m[l];
	if (l == 1)
		return floor(static_cast<ld>(n + 1) / 3);
	return m[l] = P(l - 1) * v3 + K(l - 1) * v2 + M(l - 1) * v1;
}
