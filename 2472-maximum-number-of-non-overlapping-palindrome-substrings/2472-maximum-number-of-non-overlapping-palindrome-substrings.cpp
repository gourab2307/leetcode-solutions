class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<int> dp(n + 1, 0);

        for (int i = 0; i < n; i++) {
            dp[i + 1] = max(dp[i + 1], dp[i]);

            // Odd length palindromes
            for (int l = i, r = i; l >= 0 && r < n && s[l] == s[r]; l--, r++) {
                if (r - l + 1 >= k) {
                    dp[r + 1] = max(dp[r + 1], dp[l] + 1);
                    break;
                }
            }

            // Even length palindromes
            for (int l = i, r = i + 1; l >= 0 && r < n && s[l] == s[r]; l--, r++) {
                if (r - l + 1 >= k) {
                    dp[r + 1] = max(dp[r + 1], dp[l] + 1);
                    break;
                }
            }
        }

        return dp[n];
    }
};