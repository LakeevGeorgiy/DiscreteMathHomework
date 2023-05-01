#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n = 5;
	// пример массива с людьми разной высоты
	vector<ll> heights{ 1, 2, 3, 4, 5 };
	ll ans = 0;
	do {
		// проверка: удовлетворяет ли условию
		bool ok = true;
		for (int i = 1; i < n - 1; i++) {
			// 3 подряд идущих по возрастанию
			if (heights[i - 1] < heights[i] && heights[i] < heights[i + 1]) {
				ok = false;
				break;
			}
			// 3 подряд идущих по убыванию
			if (heights[i - 1] > heights[i] && heights[i] > heights[i + 1]) {
				ok = false;
				break;
			}
		}
		// если все условию выполняются, то ответ увеличивается
		if (ok) ++ans;
		// перебор всех перестановок
	} while (next_permutation(heights.begin(), heights.end()));
	cout << ans << "\n";
	return 0;
}
