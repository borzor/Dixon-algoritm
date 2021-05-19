#include "gauss.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <bitset>
#include <benchmark/benchmark.h>

boost::dynamic_bitset<> random_bitset(size_t size, double p = 0.5) {
    boost::dynamic_bitset<> bits;
    std::random_device rd;
    std::mt19937 gen( rd());
    std::bernoulli_distribution d( p);
    for(size_t n = 0; n < size; ++n) {
        bits.push_back(d(gen));
    }
    return bits;
}

void gauss_test(benchmark::State& state){
    std::vector<std::pair<boost::dynamic_bitset<>, int>> vector;
    for(size_t i = 0; i < state.range(); ++i){
        vector.push_back(std::make_pair(random_bitset(state.range()), i));
    }
    for(auto i:state)
        Gauss(vector);



}
