#include "dixon.hpp"

dixon::dixon(NTL::ZZ N):
    N(N){}

void dixon::create_factor_base(){
    auto tmp = NTL::log(NTL::log(NTL::conv<NTL::RR>(N)))*NTL::log(N);
    auto Ln = NTL::exp(NTL::sqrt(tmp));
    auto M = NTL::sqrt(Ln);
    NTL::PrimeSeq P;// less than 2^30;
    long p = P.next();
    while (p <= M) {
       prime_numbers.push_back(NTL::ZZ(p));
       p = P.next();
    }
    for(auto &i:prime_numbers){
        std::cout<<i<<' ';
    }
    std::cout<<std::endl;
}
std::pair<NTL::ZZ,NTL::ZZ> dixon::generate_numbers(){
    std::pair<NTL::ZZ,NTL::ZZ> numbers;
    NTL::RR b;
    while((b = NTL::random_RR())==0){continue;}
    numbers.first = NTL::conv<NTL::ZZ>(b *((NTL::conv<NTL::RR>(N) - NTL::sqr(NTL::conv<NTL::RR>(N))) + NTL::sqr(NTL::conv<NTL::RR>(N))));
    numbers.second = NTL::PowerMod(numbers.first, 2, N);
    std::cout<<N<<'\n'<<numbers.first<<'\n'<<numbers.second<<'\n';
    return numbers;
}
bool dixon::Check_on_Smooth(std::pair<NTL::ZZ, NTL::ZZ> pair){// b and a
    NTL::ZZ tmp(pair.second);
    std::vector<u_int32_t> pow;
    uint32_t counter;
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
        return 1;
    }
    else
        return 0;
}


