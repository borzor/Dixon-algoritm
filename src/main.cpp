#include "dixon.hpp"
#include "gauss_testing.hpp"


/*#define A "8042488335863228666059"

int main()
{
    NTL::ZZ a;
    NTL::conv(a, A);
    auto start = std::chrono::steady_clock::now();
    dixon dixon(a, 8);
    std::pair<NTL::ZZ,NTL::ZZ> result(dixon.do_factorise());
    auto end = std::chrono::steady_clock::now();
    std::cout<<a<<" можно получить умножив "<<result.first<<" на " <<result.second<<'\n';
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
*/
BENCHMARK(gauss_test)->RangeMultiplier(2)->Range(8, 8<<10);
BENCHMARK_MAIN();
