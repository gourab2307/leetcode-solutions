class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int count = 0;
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    long long total = grid[i][j];
                    grid[i][j] = 0;  // mark visited
                    vector<pair<int, int>> stack;
                    stack.push_back({i, j});

                    while (!stack.empty()) {
                        auto [x, y] = stack.back();
                        stack.pop_back();
                        for (auto& d : dirs) {
                            int nx = x + d[0], ny = y + d[1];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > 0) {
                                total += grid[nx][ny];
                                grid[nx][ny] = 0;
                                stack.push_back({nx, ny});
                            }
                        }
                    }

                    if (total % k == 0) count++;
                }
            }
        }
        return count;
        
    }
};