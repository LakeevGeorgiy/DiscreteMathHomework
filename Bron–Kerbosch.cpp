#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;

typedef long long ll;

int count_bits(ll value) {
	int cnt = 0;
	for (int i = 0; i < 64; i++) {
		if (value & (1 << (i)))
			cnt++;
	}
	return cnt;
}

// R	all vertices from maximal clique
// P	firtstly, all vertices that we have in graph
// X	vertices which we don't need to use
// G	graph
// callback is the reference for function, that used to change the ans (size of the maximal clique)


// we use mask of sets to represent our sets as long long, where every bits show vertex in graph

void rec(ll R, ll P, ll X, const vector<ll>& G, const function<void(ll)>& callback) {
	if (P == 0 && X == 0) {
		// updating ans
		callback(R);
		return;
	}
	int u = 0; 
	while (!((P | X) & (1LL << u))) 
		++u;
	for (int v = 0; v < G.size(); ++v) {
		if ((P & ~G[u]) & (1LL << v)) {
			// добавляем вершину в клику, пересекаем текущее множество и множество вершин связанных с v
			// пересекаем множество уже проверенных вершин с множеством вершин связанных с v
			rec(R | (1LL << v), P & G[v], X & G[v], G, callback);
			// удаляем вершину из множество clique
			P &= ~(1LL << v);
			// добавляем вершину в проверенные
			X |= (1LL << v);
		}
	}
}

void enumerate_maximal_cliques(const vector<ll>& G, const function<void(ll)>& callback) {
	rec(0, (1LL << G.size()) - 1, 0, G, callback);
}

int max_clique(const vector<ll>& G) {
	int ans = 0;
	enumerate_maximal_cliques(G, [&ans](ll R) { ans = max(ans, count_bits(R)); });
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int Q, V;
	map<string, int> name2id;
	cin >> Q >> V;
	vector <ll> G(V);
	for (int i = 0; i < Q; ++i) {
		ll seen = 0;
		while (i < Q) {
			int op;
			cin >> op;
			if (op == 1) break;
			string s; 
			cin >> s;
			// считываем название вершины и присваивам ей номер
			if (!name2id.count(s)) {
				int newId = name2id.size();
				name2id[s] = newId;
			}
			// записываем вершину в смежную с вершниой 
			seen |= (1LL << name2id[s]);
			++i;
		}
		// создаем граф
		for (int k = 0; k < V; ++k)
			if (seen & (1LL << k))
				G[k] |= seen;
	}

	// G^-1
	// инвертируем последний бит
	for (int i = 0; i < V; ++i)
		G[i] = ~G[i] & ((1LL << V) - 1);

	// max_independent_set(G) = max_clique(G^1)
	cout << max_clique(G);
	return 0;
}
