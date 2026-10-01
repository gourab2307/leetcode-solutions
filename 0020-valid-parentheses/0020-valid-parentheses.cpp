class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char c : s) {

            // Opening brackets
            if (c == '(') {
                st.push(')');
            }
            else if (c == '{') {
                st.push('}');
            }
            else if (c == '[') {
                st.push(']');
            }

            // Closing bracket
            else {
                if (st.empty() || st.top() != c) {
                    return false;
                }

                st.pop();
            }
        }

        return st.empty();
    }
};