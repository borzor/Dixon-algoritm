#include "dixon.hpp"
#include "gauss.hpp"
#include <cmath>

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
}

std::pair<NTL::ZZ,NTL::ZZ> dixon::generate_numbers(){
    std::pair<NTL::ZZ,NTL::ZZ> numbers;
    NTL::RR b;
    while((b = NTL::random_RR())==0){continue;}
    numbers.first = NTL::conv<NTL::ZZ>(b *((NTL::conv<NTL::RR>(N) - NTL::sqr(NTL::conv<NTL::RR>(N))) + NTL::sqr(NTL::conv<NTL::RR>(N))));
    numbers.second = NTL::PowerMod(numbers.first, 2, N);
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

void dixon::do_factorise(){
    std::vector<std::vector<uint32_t>>result;
    std::vector<std::pair<boost::dynamic_bitset<>,int>> a;

    create_factor_base();
    while(1){
        uint32_t counter = 0;
        uint32_t h = prime_numbers.size() + 1;
        while(h){
            std::pair<NTL::ZZ,NTL::ZZ> pair_ = generate_numbers();
            if(Check_on_Smooth(pair_))
                --h;
        }
        for(auto &i:vec){
            boost::dynamic_bitset<>db;
            for(auto &j:i){
                db.push_back(j%2);
            }
            a.push_back(std::make_pair(db, counter++));
            db.reset();
        }
        result = Gauss(a);
        if(result.empty()){
            pairs.clear();vec.clear();a.clear();
            continue;
        }
        else{
            for(auto &i:result){
                std::vector<uint32_t>vec_for_y(vec[0].size(),0);
                NTL::ZZ x(1);NTL::ZZ y(1);
                for(auto &j:i){
                    NTL::MulMod(x,x,pairs[j].first,N);
                    for(uint32_t k = 0; k < vec[j].size(); ++k){
                        vec_for_y[k]+=vec[j][k];
                        std::cout<<vec[j][k]<<' ';
                    }
                    std::cout<<'\n';
                }
                for(uint32_t k = 0; k < vec_for_y.size(); ++k){
                    vec_for_y[k]/=2;
                    NTL::MulMod(y, y, NTL::PowerMod(prime_numbers[k],vec_for_y[k], N),N);
                }
                std::cout<<x<<' '<<y<<'\n';
                if(((x - y) % N != 0) && ((x + y) % N != 0)){
                    std::cout<<NTL::GCD(x+y,N)<<' '<<NTL::GCD(x-y,N)<<'\n';
                    return;
                }
                else{
                    std::cout<<"no"<<'\n';
                    vec_for_y.clear();y=1;x=1;
                    continue;
            }
            }
        }


    }
}


