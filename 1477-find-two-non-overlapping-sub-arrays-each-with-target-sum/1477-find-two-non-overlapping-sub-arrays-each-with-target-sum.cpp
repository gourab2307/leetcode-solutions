class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        vector<int> best(n, INT_MAX);

        unordered_map<long long, int> mp;
        mp[0] = -1;

        long long prefix = 0;
        int minLen = INT_MAX;
        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {
            prefix += arr[i];

            if (mp.count(prefix - target)) {
                int start = mp[prefix - target] + 1;
                int len = i - start + 1;

                if (start > 0 && best[start - 1] != INT_MAX) {
                    ans = min(ans, len + best[start - 1]);
                }

                minLen = min(minLen, len);
            }

            best[i] = minLen;
            mp[prefix] = i;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};