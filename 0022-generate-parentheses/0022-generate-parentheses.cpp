class Solution {
public:
void backtrack(int n, int open, int close,
                   string current, vector<string>& ans) {
        
        if (open == n && close == n) {
            ans.push_back(current);
            return;
        }

        if (open < n) {
            backtrack(n, open + 1, close,
                      current + '(', ans);
        }

        if (close < open) {
            backtrack(n, open, close + 1,
                      current + ')', ans);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        backtrack(n, 0, 0, "", ans);
        return ans;
    }
};