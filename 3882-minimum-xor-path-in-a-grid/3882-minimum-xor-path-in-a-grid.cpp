class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        int mx = 0;
        for (auto& row : grid)
            for (int v : row) mx = max(mx, v);
        int M = 1;
        while (M <= mx) M <<= 1;

        vector<vector<char>> dp(n, vector<char>(M, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vector<char> cur(M, 0);
                if (i == 0 && j == 0) {
                    cur[grid[0][0]] = 1;
                } else {
                    int g = grid[i][j];
                    for (int x = 0; x < M; x++) {
                        bool ok = false;
                        if (i > 0 && dp[j][x]) ok = true;      
                        if (j > 0 && dp[j - 1][x]) ok = true;  
                        if (ok) cur[x ^ g] = 1;
                    }
                }
                dp[j] = move(cur);
            }
        }

        for (int x = 0; x < M; x++)
            if (dp[n - 1][x]) return x;
        return -1;
    }
};