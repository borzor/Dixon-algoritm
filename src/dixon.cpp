#include "dixon.hpp"
#include "slaves.hpp"
#include <cmath>

dixon::dixon(NTL::ZZ N, short threads):
    N(N), number_of_threads(threads){}

std::vector<NTL::ZZ> dixon::create_factor_base(NTL::ZZ &N){
    std::vector<NTL::ZZ>prime_numbers;
    auto tmp = NTL::log(NTL::log(NTL::conv<NTL::RR>(N)))*NTL::log(N);
    auto Ln = NTL::exp(NTL::sqrt(tmp));
    auto M = NTL::sqrt(Ln);
    NTL::PrimeSeq P;// less than 2^30;
    long p = P.next();
    while (p <= M) {
       prime_numbers.push_back(NTL::ZZ(p));
       p = P.next();
    }
    return prime_numbers;
}

std::pair<NTL::ZZ, NTL::ZZ> dixon::do_factorise(){
    std::vector<std::vector<uint32_t>>result;
    std::vector<std::pair<boost::dynamic_bitset<>,int>> a;
    NTL::ZZ x(1);NTL::ZZ y(1);
    std::vector<std::vector<uint32_t>>vec;
    std::vector<std::pair<NTL::ZZ,NTL::ZZ>>pairs;
    std::vector<NTL::ZZ>prime_numbers(create_factor_base(N));

    while(1){
        a.clear();result.clear();
        uint32_t counter = 0;
        uint32_t size = prime_numbers.size() + 1;
        auto start = std::chrono::steady_clock::now();
        make_numbers(std::ref(prime_numbers), N, std::ref(vec), std::ref(pairs), size, number_of_threads);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "elapsed time on generating numbers: " << elapsed_seconds.count() << "s\n";
        for(auto &i:vec){
            boost::dynamic_bitset<>db;
            for(auto &j:i){
                db.push_back(j%2);
            }
            a.push_back(std::make_pair(db, counter++));
            db.reset();
        }
        auto start_gauss = std::chrono::steady_clock::now();
        result = Gauss(a);
        auto end_gauss = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_gauss = end_gauss-start_gauss;
        std::cout << "elapsed time on gauss: " << elapsed_seconds_gauss.count() << "s\n";
        std::vector<uint32_t>vec_for_y(vec[0].size(),0);
        if(result.empty()){
            pairs.clear();vec.clear();a.clear();
            continue;
        }
        else{
            for(auto &i:result){
                for(auto &j:i){
                    NTL::MulMod(x,x,pairs[j].first,N);
                    for(uint32_t k = 0; k < vec[j].size(); ++k){
                        vec_for_y[k]+=vec[j][k];
                    }
                }
                for(uint32_t k = 0; k < vec_for_y.size(); ++k){
                    vec_for_y[k]/=2;
                    NTL::MulMod(y, y, NTL::PowerMod(prime_numbers[k],vec_for_y[k], N),N);
                }
                if(((x - y) % N != 0) && ((x + y) % N != 0)){
                    return get_result(x,y);
                }
                else{
                    std::fill(vec_for_y.begin(),vec_for_y.end(),0);y=1;x=1;
            }
            }
        }
    }
}

std::pair<NTL::ZZ,NTL::ZZ> dixon::get_result(NTL::ZZ &x, NTL::ZZ &y){
    NTL::ZZ q;
    NTL::ZZ GCD_p = NTL::GCD(x+y, N); NTL::ZZ GCD_m = NTL::GCD(x-y, N);
    NTL::divide(q, GCD_p*GCD_m, N);
    return (NTL::divide(GCD_p, q) ? std::make_pair(GCD_p/q, GCD_m) : std::make_pair (GCD_p, GCD_m));
}

