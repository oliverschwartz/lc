class Solution {
public:
    /*
Consider this algorithm: 
- while there exist both a's and b's in the string, there must exist 
either "ab" or "ba" somewhere in the string (where the two chars meet). 
- Remove this string. 
- Repeat until only a's or b's are left.

This will remove the same number of a's and b's, and whatever is leftover
is just the more frequent character. Hence, just count the a's and b's. 
    */

    int minLengthAfterRemovals(string s) {
        int as = std::accumulate(s.begin(), s.end(), 0, [](int acc, char ch){
            return acc + static_cast<int>(ch == 'a');
        });
        int bs = s.size() - as; 
        return std::abs(as - bs);
    }
};
