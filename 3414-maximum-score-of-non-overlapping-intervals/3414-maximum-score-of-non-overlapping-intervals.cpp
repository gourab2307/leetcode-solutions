class Solution {
public:
    struct Node {
        long long weight;
        vector<int> ids;
    };

    static bool lexSmaller(const vector<int>& a, const vector<int>& b) {
        return lexicographical_compare(a.begin(), a.end(),
                                       b.begin(), b.end());
    }

    static Node better(const Node& A, const Node& B) {
        if (A.weight != B.weight)
            return (A.weight > B.weight ? A : B);

        return lexSmaller(A.ids, B.ids) ? A : B;
    }
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<int,4>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {intervals[i][0], intervals[i][1],
                      intervals[i][2], i};
        }

        sort(arr.begin(), arr.end(),
             [](auto &a, auto &b) {
                 if (a[0] != b[0]) return a[0] < b[0];
                 return a[1] < b[1];
             });

        vector<int> starts(n);
        for (int i = 0; i < n; i++) starts[i] = arr[i][0];

        vector<int> nxt(n);
        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(
                starts.begin(), starts.end(), arr[i][1]
            ) - starts.begin();
        }

        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        for (int k = 0; k <= 4; k++) {
            dp[n][k] = {0, {}};
        }

        for (int i = n - 1; i >= 0; i--) {
            dp[i][0] = {0, {}};

            for (int k = 1; k <= 4; k++) {
                Node skip = dp[i + 1][k];

                Node take;
                take.weight = arr[i][2] + dp[nxt[i]][k - 1].weight;
                take.ids = dp[nxt[i]][k - 1].ids;
                take.ids.push_back(arr[i][3]);
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(take, skip);
            }
        }

        return dp[0][4].ids;
    }
};