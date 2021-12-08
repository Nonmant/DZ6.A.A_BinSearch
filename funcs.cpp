//https://contest.yandex.ru/contest/27844/problems/A/

#include "funcs.h"
#include <bits/stdc++.h>

//! @brief Index of last less. If everything is more return 0
size_t binSearchLowerBound(std::vector<int> & vector, int value){
    if(vector.empty())
        return 0;
    size_t left = 0,
        right = vector.size()-1;
    while (left<right){
        size_t cur = (left + right + 1)/2;
        if(vector[cur]<value){
            left = cur;
        } else {
            right = cur-1;
        }
    }
    return right;
}

void parseFile(std::istream & input, std::ostream & output){

    int n, k;
    input >> n >> k;
    std::vector<int> source(n), search(k);
    std::vector<bool> ans(k);
    std::copy_n(std::istream_iterator<int>(input), n, source.begin());
    std::copy_n(std::istream_iterator<int>(input), k, search.begin());

    std::sort(source.begin(), source.end());

    bool res;
    for(size_t i = 0; i < search.size(); ++i){
        auto index = binSearchLowerBound(source,search[i]) + 1;

        if(index == 1 && source[0] == search[i]){
            res = true;
        } else
        if(index == source.size())
            res = false;
        else {
            res = source[index] == search[i];
        }
        ans[i] = res;
    }

    for(auto ai : ans){
        output << (ai ? "YES\n" : "NO\n");
    }
}
