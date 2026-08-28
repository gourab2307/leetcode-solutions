class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        int odd = 0;
        string mid = "";

        vector<int> half(26);
        for (int i = 0; i < 26; i++) {
            if (cnt[i] & 1) {
                odd++;
                mid.push_back('a' + i);
            }
            half[i] = cnt[i] / 2;
        }

        if (odd > 1) return "";

        int m = s.size() / 2;
        string prefix;

        auto feasible = [&]() -> bool {
            string left = prefix;

            vector<int> rem = half;

            for (int c = 25; c >= 0; c--) {
                left.append(rem[c], char('a' + c));
            }

            string pal = left + mid;
            for (int i = (int)left.size() - 1; i >= 0; i--) {
                pal.push_back(left[i]);
            }

            return pal > target;
        };

        for (int pos = 0; pos < m; pos++) {
            bool found = false;

            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                prefix.push_back('a' + c);

                if (feasible()) {
                    found = true;
                    break;
                }

                prefix.pop_back();
                half[c]++;
            }

            if (!found) return "";
        }

        string ans = prefix + mid;
        for (int i = (int)prefix.size() - 1; i >= 0; i--) {
            ans.push_back(prefix[i]);
        }

        return ans > target ? ans : "";
    }      
};