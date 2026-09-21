class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int x : nums) {
            int cur = x % k;

            vector<long long> ndp(k, 0);

            // Start a new subarray
            ndp[cur]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r] == 0) continue;

                int nr = (1LL * r * cur) % k;
                ndp[nr] += dp[r];
            }

            // Add all subarrays ending here
            for (int r = 0; r < k; r++) {
                ans[r] += ndp[r];
            }

            dp = move(ndp);
        }

        return ans;
    }
};