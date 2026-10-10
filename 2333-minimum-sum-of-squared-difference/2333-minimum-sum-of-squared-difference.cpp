class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();
        vector<int> freq(100001, 0);
        int mx = 0;

        for (int i = 0; i < n; i++) {
            int d = abs(nums1[i] - nums2[i]);
            freq[d]++;
            mx = max(mx, d);
        }

        long long total = 0;
        for (int d = 1; d <= mx; d++) {
            total += 1LL * d * freq[d];
        }

        if (k >= total) return 0;

        for (int d = mx; d > 0 && k > 0; d--) {
            if (freq[d] == 0) continue;

            long long count = min(k, (long long)freq[d]);
            freq[d] -= count;
            freq[d - 1] += count;
            k -= count;
        }

        long long ans = 0;
        for (int d = 1; d <= mx; d++) {
            ans += 1LL * d * d * freq[d];
        }

        return ans;
    }
};