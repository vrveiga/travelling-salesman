#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> permutation;
vector<bool> chosen(20);

void search() {
    if (permutation.size() == n) {
        for (auto u : permutation) cout << u << " ";
        cout << endl;
    } else {
        for (int i = 0; i < n; i++) {
            if (chosen[i]) continue;
            chosen[i] = true;
            permutation.push_back(i);
            search();
            chosen[i] = false;
            permutation.pop_back();
        }
    }
}

int main() {
    cin >> n;
    search();
}