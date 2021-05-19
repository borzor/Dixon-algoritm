#include "gauss.hpp"
#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <vector>
#include <thread>
#include <ranges>
#include <mutex>

std::mutex mtx;

std::pair<NTL::ZZ,NTL::ZZ> generate_numbers(NTL::ZZ N){
    std::pair<NTL::ZZ,NTL::ZZ> numbers;
    NTL::RR b;
    while((b = NTL::random_RR())==0){continue;}
    numbers.first = NTL::conv<NTL::ZZ>(b *((NTL::conv<NTL::RR>(N) - NTL::sqr(NTL::conv<NTL::RR>(N))) + NTL::sqr(NTL::conv<NTL::RR>(N))));
    numbers.second = NTL::PowerMod(numbers.first, 2, N);
    return numbers;
}

void generate_smooth_numbers(std::vector<NTL::ZZ> &prime_numbers, NTL::ZZ N, std::vector<std::vector<uint32_t>> &vec, std::vector<std::pair<NTL::ZZ, NTL::ZZ>> &pairs, uint32_t &size){// b and a
    std::pair<NTL::ZZ, NTL::ZZ> pair;
    NTL::ZZ tmp;
    std::vector<u_int32_t> pow;
    uint32_t counter;
    while(size){
        pair = generate_numbers(N);
        tmp = pair.second;
        counter = 0; pow.clear();
        for(uint32_t i = 0; i < prime_numbers.size(); i++){
            counter = 0;
            while(NTL::divide(tmp, tmp, prime_numbers[i])){
                counter++;
            }
            pow.push_back(counter);
        }
        if(tmp==1){
            vec.push_back(pow);
            pairs.push_back(pair);
            mtx.lock();
            --size;
            mtx.unlock();
        }
        else
            continue;
}
}

void make_numbers(std::vector<NTL::ZZ> prime_numbers, NTL::ZZ N, std::vector<std::vector<uint32_t> > &vec, std::vector<std::pair<NTL::ZZ, NTL::ZZ> > &pairs, uint32_t size, short number_of_threads){
    std::vector<std::thread*> slave_pool;
    std::vector<std::vector<std::vector<uint32_t>>>vec_for_threads(number_of_threads);
    std::vector<std::vector<std::pair<NTL::ZZ,NTL::ZZ>>>pairs_for_threads(number_of_threads);
    for(auto i = 0 ;i < number_of_threads; ++i){
        slave_pool.push_back(new std::thread(generate_smooth_numbers, std::ref(prime_numbers), N, std::ref(vec_for_threads[i]), std::ref(pairs_for_threads[i]), std::ref(size)));
    }
    for(auto &thread:slave_pool){
        thread->join();
    }
    for(int i = 0; i < number_of_threads; ++i){
        vec.insert(vec.end(), vec_for_threads[i].begin(), vec_for_threads[i].end());
        pairs.insert(pairs.end(), pairs_for_threads[i].begin(), pairs_for_threads[i].end());
    }
}


