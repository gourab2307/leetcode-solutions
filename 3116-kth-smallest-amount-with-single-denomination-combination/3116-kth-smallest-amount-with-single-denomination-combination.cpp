class Solution {
public:
    long long countNumbers(long long x, vector<int>& coins) {
        int n = coins.size();
        long long cnt = 0;

        for (int mask = 1; mask < (1 << n); mask++) {
            long long l = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    long long g = gcd(l, (long long)coins[i]);

                    if (l > x / (coins[i] / g)) {
                        valid = false;
                        break;
                    }

                    l = l / g * coins[i];
                }
            }

            if (!valid) continue;

            if (bits & 1)
                cnt += x / l;
            else
                cnt -= x / l;
        }

        return cnt;
    }
    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1, high = 1e18;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countNumbers(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};