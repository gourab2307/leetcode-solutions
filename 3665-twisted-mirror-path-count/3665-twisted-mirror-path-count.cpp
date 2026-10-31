class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<long long>> dpR(m, vector<long long>(n, 0));
        vector<vector<long long>> dpD(m, vector<long long>(n, 0));

        long long ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                long long ways = dpR[i][j] + dpD[i][j];

                if (i == 0 && j == 0) {
                    ways = 1;
                }

                ways %= MOD;
                if (i == m - 1 && j == n - 1) {
                    return ways;
                }

                if (grid[i][j] == 1) {
                    if (dpR[i][j] && i + 1 < m) {
                        dpD[i + 1][j] =
                            (dpD[i + 1][j] + dpR[i][j]) % MOD;
                    }
                    if (dpD[i][j] && j + 1 < n) {
                        dpR[i][j + 1] =
                            (dpR[i][j + 1] + dpD[i][j]) % MOD;
                    }

                } else {
                    if (j + 1 < n) {
                        dpR[i][j + 1] =
                            (dpR[i][j + 1] + ways) % MOD;
                    }
                    if (i + 1 < m) {
                        dpD[i + 1][j] =
                            (dpD[i + 1][j] + ways) % MOD;
                    }
                }
            }
        }

        return 0;
    }
};