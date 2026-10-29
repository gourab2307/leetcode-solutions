class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n);
        vector<vector<int>> up(n, vector<int>(20, 0));
        vector<int> mask(n);
        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = ++timer;
            up[u][0] = p;
            for (int j = 1; j < 20; j++)
                up[u][j] = up[up[u][j - 1]][j - 1];

            mask[u] = 1 << (s[u] - 'a');

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }

            tout[u] = timer;
        };

        dfs(0, 0);

        auto isAncestor = [&](int u, int v) {
            return tin[u] <= tin[v] && tout[v] <= tout[u];
        };

        auto lca = [&](int u, int v) {
            if (isAncestor(u, v)) return u;
            if (isAncestor(v, u)) return v;

            for (int j = 19; j >= 0; j--) {
                if (!isAncestor(up[u][j], v))
                    u = up[u][j];
            }
            return up[u][0];
        };

        vector<int> bit(n + 2, 0);

        auto add = [&](int idx, int val) {
            for (; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto query = [&](int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        for (int u = 0; u < n; u++) {
            add(tin[u], mask[u]);
            add(tout[u] + 1, mask[u]);
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                int newMask = 1 << (c - 'a');
                int delta = mask[u] ^ newMask;

                add(tin[u], delta);
                add(tout[u] + 1, delta);

                mask[u] = newMask;
                s[u] = c;
            } else {
                int u, v;
                ss >> u >> v;

                int w = lca(u, v);

                int pathMask =
                    query(tin[u]) ^ query(tin[v]) ^ mask[w];

                if (__builtin_popcount((unsigned)pathMask) <= 1)
                    ans.push_back(true);
                else
                    ans.push_back(false);
            }
        }

        return ans;
    }
};