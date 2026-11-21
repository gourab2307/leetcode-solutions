class Solution {
public:
vector<vector<int>> adj;
    vector<int> newParent;

    void dfs1(int u, string &s, vector<int> &last) {

        int c = s[u] - 'a';
        int prev = last[c];
        if (prev != -1) {
            newParent[u] = prev;
        }
        last[c] = u;
        for (int v : adj[u]) {
            dfs1(v, s, last);
        }
        last[c] = prev;
    }

    int dfs2(int u, vector<vector<int>> &tree,
             vector<int> &ans) {

        int sz = 1;

        for (int v : tree[u]) {
            sz += dfs2(v, tree, ans);
        }

        ans[u] = sz;

        return sz;
    }
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        adj.resize(n);
        newParent = parent;
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }
        vector<int> last(26, -1);

        dfs1(0, s, last);

        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }
        vector<int> ans(n, 0);

        dfs2(0, tree, ans);

        return ans;
    }
};