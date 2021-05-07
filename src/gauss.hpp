#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <iostream>

std::vector<std::vector<uint32_t>> Gauss (std::vector<std::pair<boost::dynamic_bitset<>,int>> a) {
    std::vector<std::pair<boost::dynamic_bitset<>,int>> copy = a;
    std::vector<std::vector<uint32_t>> result;
    std::vector<int> where (a[0].first.size(), -1);
    uint32_t counter = 0;
    for (int col=0, row=0; col<a[0].first.size() && row<a.size(); ++col) {
        for (int i=row; i<a.size(); ++i)
            if (a[i].first[col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row].first[col])
            continue;
        where[col] = row;

        for (int i=0; i<a.size(); ++i)
            if (i != row && a[i].first[col])
                a[i].first ^= a[row].first;
        ++row;
    }

    for(auto &i:a){
        if(i.first.any())
            ++counter;
    }
    boost::dynamic_bitset<>check_bitset(a[0].first.size());
    std::vector<uint32_t>for_result;
    for(uint32_t h = counter; h < a.size(); ++h){//h - zero bitsets
        if(copy[a[h].second].first.any()){
            for(uint32_t i = 1; i < (1 << counter); ++i){// i - bitset of indexs for xor
                boost::dynamic_bitset<>bits(counter, i);
                for(uint32_t j = 0; j < counter; ++j){
                    if(bits[j]){
                        check_bitset^=copy[a[j].second].first;//a[j].first;
                    }
                }
                if(check_bitset==copy[a[h].second].first){
                    for_result.push_back(copy[a[h].second].second);
                    for(uint j = 0; j < counter; ++j){
                        if(bits[j]){
                            for_result.push_back(a[j].second);
                        }
                    }
                    result.push_back(for_result);
                }
                check_bitset.reset();
                for_result.clear();
            }
        }
        else
            continue;
    }
    return result;
}
