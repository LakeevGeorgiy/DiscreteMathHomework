#include <iostream>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

typedef long long ll;

/*
Тесты

AUAU
AUUA
UAGCGUGAUCA
AUCGUAAUCGCG
CGUAAUUACGGCAUUAGCAU

*/

ll cnt = 0;
ll n = 0;
map<ll, ll> true_index;

bool check(vector<ll>& permutation) {
	for (int index_i = 0; index_i < n / 2; index_i++) {
		ll i = true_index[index_i];
		ll j = permutation[index_i];

		assert(i != j); // вершина не должна быть связана сама с собой
		if (i > j)
			swap(i, j);

		// для проверки каждой пары ребер по одному разу начинаем от index_i + 1
		for (int index_a = index_i + 1; index_a < n / 2; index_a++) {

			ll a = true_index[index_a];
			ll b = permutation[index_a];
			
			assert(a != b); // вершина не должна быть связана сама с собой
			if (a > b)
				swap(a, b);

			if ((i < a && a < j && j < b) || (a < i && i < b && b < j)) // условие пересечения ребер в matching-е
				return false;
		}
	}
	return true;
}

void rec(ll i, vector<vector<ll>>&g, vector<ll>& permutation, vector<bool>& used) {

	// если мы составили matching для одной доли графа,
	// то для второй доли нет смысла делать обход, так как 
	// граф двудольный, следовательно ребра mathing-а первой доли -
	// это matching и второй доли тоже

	if (i == n / 2) {
		if (check(permutation))
			cnt++;
		return;
	}

	// Создааю перестановку, основанную на списке смежности
	// т.е сопоставляю каждой вершине из первой доли, вершину из второй доли
	// тогда такая пара задает ребро

	// permutation[u] = v показывает ребро из true_index[u] в v.
	// где true_index[i] - это номер вершины в графе, а i это номер вершины в первой доли.
	// т.е счетчки i-ый пробегается по всем элеменатам первой доли, v - настоящий номер вершины в графе
	// u - вершниа смежная с v

	for (int j = 0; j < g[true_index[i]].size(); j++) {
		ll v = true_index[i];
		ll u = g[v][j];
		if (used[u])
			continue;
		permutation[i] = u;
		used[v] = true;
		used[u] = true;
		rec(i + 1, g, permutation, used);
		used[v] = false;
		used[u] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(false);  
	cin.tie(0);
	cout.tie(0);
	string graph = "CGUAAUUACGGCAUUAGCAU";
	n = graph.size();
	vector <vector<ll>> g(n + 1);
	ll pok = 0;
	for (int i = 0; i < n; i++) {
		char v = graph[i];
		// рассматриваю граф, как двудольный
		// Перебираю ребра, выходящие из первой доли
		if (graph[i] == 'A' || graph[i] == 'C') {
			true_index.emplace(pok++, i);
		}
		for (int j = 0; j < n; j++) {
			char u = graph[j];
			if (((v == 'A' && u == 'U') || (v == 'U' && u == 'A') || (v == 'C' && u == 'G') || (v == 'G' && u == 'C')) && abs(i - j) % 2 == 1) {
				g[i].push_back(j);
			}
		}
	}
	vector<ll> permutation(n / 2, -1);
	vector<bool> used(n, false);
	rec(0, g, permutation, used);
	cout << cnt << "\n";
	return 0;
}
