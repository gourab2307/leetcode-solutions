class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;
        vector<long long> arr(k, 0);

        // Count how many numbers contain each bit
        for (int bit = 0; bit < 32; bit++) {
            int cnt = 0;

            for (int num : nums) {
                if (num & (1LL << bit)) {
                    cnt++;
                }
            }

            // Distribute this bit among k numbers
            for (int i = 0; i < min(k, cnt); i++) {
                arr[i] |= (1LL << bit);
            }
        }

        long long ans = 0;

        for (long long x : arr) {
            ans = (ans + x * x % MOD) % MOD;
        }

        return ans;
    }
};