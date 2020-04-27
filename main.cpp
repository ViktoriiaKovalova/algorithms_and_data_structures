#include <bits/stdc++.h>
using namespace std;

struct Node {
    static const Node kDefaultNode;
    int64_t val;  // data
    void Merge(Node& lhs, Node& rhs) {
        val = lhs.val + rhs.val;   // function implementation
    }
};

const Node Node::kDefaultNode{0};  // default value

struct SegTree {
    int sz;
    vector<Node> tree;
    SegTree(vector<Node>& nodes) {
        sz = 1;
        while (sz < nodes.size())
            sz <<= 1;
        tree.resize(2 * sz, Node::kDefaultNode);
        copy(nodes.begin(), nodes.end(), tree.begin() + sz);
        for (int i = sz - 1; i > 0; --i)
            tree[i].Merge(tree[2 * i], tree[2 * i + 1]);
    }
    void Set(int ind, Node value) {
        ind += sz;
        tree[ind] = value;
        ind /= 2;
        while (ind) {
            tree[ind].Merge(tree[ind * 2], tree[ind * 2 + 1]);
            ind /= 2;
        }
    }
    Node GetValue(int l, int r) { // l and r included
        Node result = Node::kDefaultNode;
        l += sz;
        r += sz;
        while (l <= r) {
            if (l % 2 == 1) {
                result.Merge(result, tree[l]);
                ++l;
            }
            if (r % 2 == 0) {
                result.Merge(result, tree[r]);
                --r;
            }
            if (l > r)
                break;
            l >>= 1;
            r >>= 1;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >>n >> m;
    vector<Node> v(n);
    for (Node& x : v) {
        cin >> x.val;
    }
    SegTree stree(v);
    for (int i = 0; i < m; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int ind, val;
            cin >> ind >> val;
            stree.Set(ind, Node{val});
        } else {
            int l, r;
            cin >> l >> r;
            cout << stree.GetValue(l, --r).val << '\n';
        }
    }
    return 0;
}
