#include <bits/stdc++.h>
using namespace std;

signed main(){
    int n;
    cin >> n;
    int i = 2;
    int k = sqrt(n);
    while (n != 1 && i <= k){
        while(n % i == 0){
            n /= i;
            cout << i << "\n";
        }
    }
}
