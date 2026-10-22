class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        bool asc = true, desc = true;
        for (int i = 0; i < n; i++) {
            int nx = nums[(i + 1) % n];
            if (nx != (nums[i] + 1) % n) asc = false;
            if (nx != (nums[i] - 1 + n) % n) desc = false;
        }
        int ans = INT_MAX;
        if (asc) {
            int r = nums[0];
            if (r == 0) ans = 0;
            else ans = min(n - r, r + 2);
        }
        if (desc) {
            int rp = (nums[0] + 1) % n;
            if (rp == 0) ans = min(ans, 1);
            else ans = min(ans, 1 + min(rp, n - rp));
        }
        return ans == INT_MAX ? -1 : ans;
    }
};