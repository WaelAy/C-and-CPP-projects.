string longestCommonPrefix(vector<string>& strs) {
        int sizeOfArr = strs.size();
        int elementsize = strs[0].size();
        string answer = "";
        bool copy = 1;
        if (sizeOfArr == 0 || elementsize == 0)
            return "";
        if (sizeOfArr == 1)
            return strs[0];
        int letter = 0;
        for (letter;  letter<elementsize; letter++) {
            for (int i = 0; i < sizeOfArr-1; i++) {
                if (strs[i][letter] == strs[i + 1][letter]) {
                    continue;
                }
                else {
                    copy = 0;
                    break;
                }
            }
            if (copy == 1) {
                answer += strs[0][letter];
            }
            else
                break;
        }
        return answer;
    }
