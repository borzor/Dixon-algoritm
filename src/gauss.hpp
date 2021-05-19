#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/RR.h>

inline std::vector<std::vector<uint32_t>> Gauss (std::vector<std::pair<boost::dynamic_bitset<>, int>> a) {
    std::vector<boost::dynamic_bitset<>>logger(a.size());
    std::vector<std::vector<uint32_t>>answer;
    for(auto &i:logger){
        i.resize(a.size());
    }
    for (size_t col = 0, row = 0; col < a[0].first.size() && row < a.size(); ++col) {
        for (size_t i = row; i < a.size(); ++i)
            if (a[i].first[col]) {
                swap (a[i], a[row]);
                swap (logger[i], logger[row]);
                break;
            }
        if (! a[row].first[col])
            continue;
        for (size_t i = 0; i < a.size(); ++i)
            if (i != row && a[i].first[col]){
                a[i].first ^= a[row].first;
                logger[i][a[row].second].flip();
                logger[i]^=logger[row];
            }
        ++row;
    }
    for(size_t i = 0; i < a.size(); ++i){
        if(a[i].first.none() && logger[i].any()){
            std::vector<uint32_t>for_result;
            for_result.push_back(a[i].second);
            for (size_t j = logger[i].find_first(); j < logger[i].size(); j = logger[i].find_next(j)){
                 for_result.push_back(j);
            }
            answer.push_back(for_result);
            for_result.clear();
        }
    }
    return answer;
}


