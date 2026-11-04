class Solution {
public:
multiset<long long> low, high;
    long long sumLow = 0, sumHigh = 0;

    void balance() {
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            long long v = *it;

            low.erase(it);
            sumLow -= v;

            high.insert(v);
            sumHigh += v;
        }

        while (low.size() < high.size()) {
            auto it = high.begin();
            long long v = *it;

            high.erase(it);
            sumHigh -= v;

            low.insert(v);
            sumLow += v;
        }
    }

    void add(long long v) {
        if (low.empty() || v <= *low.rbegin()) {
            low.insert(v);
            sumLow += v;
        } else {
            high.insert(v);
            sumHigh += v;
        }

        balance();
    }

    void remove(long long v) {
        auto it = low.find(v);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= v;
        } else {
            it = high.find(v);
            high.erase(it);
            sumHigh -= v;
        }

        balance();
    }

    long long getCost() {
        long long median = *low.rbegin();

        return median * low.size() - sumLow
             + sumHigh - median * high.size();
    }
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        int m = n - x + 1;

        vector<long long> cost(m);
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }
        // Step 2: DP
const long long INF = 1e18;

vector<vector<long long>> dp(
    m + 1, vector<long long>(k + 1, INF)
);

for (int i = 0; i <= m; i++) {
    dp[i][0] = 0;
}

for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= k; j++) {

        // Skip current window
        dp[i][j] = dp[i - 1][j];

        // Take current window
        if (i >= 1) {
            long long prev = (i >= x) ? dp[i - x][j - 1] : 
                                         (j == 1 ? 0 : INF);

            if (prev != INF) {
                dp[i][j] = min(dp[i][j],
                               prev + cost[i - 1]);
            }
        }
    }
}

return dp[m][k];
    }
};