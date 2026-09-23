class Solution {
public:
int K;

    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    vector<Node> seg;

    Node mergeNode(const Node &L, const Node &R) {
        Node res;

        res.prod = (L.prod * R.prod) % K;

        for (int i = 0; i < K; i++)
            res.cnt[i] += L.cnt[i];

        for (int r = 0; r < K; r++)
            res.cnt[(L.prod * r) % K] += R.cnt[r];

        return res;
    }

    void build(int idx, int l, int r, vector<int>& nums) {
        if (l == r) {
            seg[idx] = Node();
            int rem = nums[l] % K;
            seg[idx].prod = rem;
            seg[idx].cnt[rem] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        build(idx << 1, l, mid, nums);
        build(idx << 1 | 1, mid + 1, r, nums);

        seg[idx] = mergeNode(seg[idx << 1], seg[idx << 1 | 1]);
    }

    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            seg[idx] = Node();
            int rem = val % K;
            seg[idx].prod = rem;
            seg[idx].cnt[rem] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid)
            update(idx << 1, l, mid, pos, val);
        else
            update(idx << 1 | 1, mid + 1, r, pos, val);

        seg[idx] = mergeNode(seg[idx << 1], seg[idx << 1 | 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql == l && qr == r)
            return seg[idx];

        int mid = (l + r) >> 1;

        if (qr <= mid)
            return query(idx << 1, l, mid, ql, qr);

        if (ql > mid)
            return query(idx << 1 | 1, mid + 1, r, ql, qr);

        Node left = query(idx << 1, l, mid, ql, mid);
        Node right = query(idx << 1 | 1, mid + 1, r, mid + 1, qr);

        return mergeNode(left, right);
    }
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        K = k;
        int n = nums.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node cur = query(1, 0, n - 1, start, n - 1);

            ans.push_back(cur.cnt[x]);
        }

        return ans;
    }
};