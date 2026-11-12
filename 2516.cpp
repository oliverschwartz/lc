class Solution {
public:
    using cnt_t = struct { int a; int b; int c; };

    int takeCharacters(string s, int k) {
        if (k == 0)
        {
            return 0;
        }

        cnt_t cnts {}; 
        for (char ch : s)
        {
            switch (ch)
            {
                case 'a': ++cnts.a; break;
                case 'b': ++cnts.b; break;
                case 'c': ++cnts.c; break;
            }
        }

        if (cnts.a < k || cnts.b < k || cnts.c < k)
        {
            return -1;
        }

        cnt_t wndw {};
        int left = 0; 
        int w_len = 0;
        int max_len = INT_MIN; 

        while (true)
        {
            bool a_sat = (cnts.a - wndw.a) >= k;
            bool b_sat = (cnts.b - wndw.b) >= k;
            bool c_sat = (cnts.c - wndw.c) >= k;
            if (a_sat && b_sat && c_sat)
            {
                max_len = std::max(w_len, max_len);

                if (left + w_len == s.size())
                {
                    break;
                }
                ++w_len;

                wndw.a += (s[left+w_len-1] == 'a');
                wndw.b += (s[left+w_len-1] == 'b');
                wndw.c += (s[left+w_len-1] == 'c');
            }
            else
            {
                if (w_len > 0)
                {
                    wndw.a -= (s[left] == 'a');
                    wndw.b -= (s[left] == 'b');
                    wndw.c -= (s[left] == 'c');
                    --w_len;
                }
                ++left; 
            }
        }

        return s.size() - max_len;
    }
};
