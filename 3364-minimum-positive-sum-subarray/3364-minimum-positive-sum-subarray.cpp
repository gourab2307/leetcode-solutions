class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        multiset<long long> st;
        long long ans = LLONG_MAX;

        for (int j = l; j <= n; j++) {

            st.insert(prefix[j - l]);

            if (j - r - 1 >= 0) {
                st.erase(st.find(prefix[j - r - 1]));
            }

            auto it = st.lower_bound(prefix[j]);

            if (it != st.begin()) {
                --it;
                ans = min(ans, prefix[j] - *it);
            }
        }

        return ans == LLONG_MAX ? -1 : ans;
    }
};