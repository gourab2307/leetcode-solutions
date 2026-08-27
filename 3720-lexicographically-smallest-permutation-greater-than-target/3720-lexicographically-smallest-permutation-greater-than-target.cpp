class Solution {
public:
    bool canBeGreater(vector<int> cnt, const string& target, int pos) {
        int n = target.size();

        for (int i = pos; i < n; i++) {
            int t = target[i] - 'a';

            int mx = -1;
            for (int c = 25; c >= 0; c--) {
                if (cnt[c]) {
                    mx = c;
                    break;
                }
            }

            if (mx > t) return true;
            if (mx < t) return false;

            cnt[mx]--;
        }

        return false; 
    }
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char ch : s) cnt[ch - 'a']++;

        string ans;

        for (int i = 0; i < n; i++) {
            int need = target[i] - 'a';

            if (cnt[need] > 0) {
                cnt[need]--;

                if (canBeGreater(cnt, target, i + 1)) {
                    ans.push_back(target[i]);
                    continue;
                }

                cnt[need]++; 
            }

            bool found = false;

            for (int c = need + 1; c < 26; c++) {
                if (cnt[c] == 0) continue;

                ans.push_back(char('a' + c));
                cnt[c]--;

                for (int d = 0; d < 26; d++) {
                    ans.append(cnt[d], char('a' + d));
                }

                return ans;
            }

            return "";
        }

        return "";
    }
};