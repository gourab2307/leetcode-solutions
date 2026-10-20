class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> target(nums);
        sort(target.begin(), target.end());

        int total = 0;
        for (int k = 1; k <= n; k++) {
            if (n % k) continue;
            bool ok = true;
            for (int s = 0; s < n && ok; s += k) {
                int descents = 0;
                for (int j = 0; j < k; j++) {
                    if (nums[s + j] > nums[s + (j + 1) % k]) descents++;
                }
                if (descents > 1) { ok = false; break; }

                vector<int> block(nums.begin() + s, nums.begin() + s + k);
                sort(block.begin(), block.end());
                if (!equal(block.begin(), block.end(), target.begin() + s)) ok = false;
            }
            if (ok) total += k;
        }
        return total;
    }
};