#include <iostream>
#include <vector>

const int MOD = 1000000007;

int countGoodBinaryTrees(int n) {
    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] = (dp[i] + dp[j] * dp[i - 1 - j]) % MOD;
        }
    }

    return dp[n];
}

int main() {
    int n;
    std::cin >> n;
    std::cout << countGoodBinaryTrees(n) << std::endl;
    return 0;
}
