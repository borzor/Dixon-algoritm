#include "dixon.hpp"
#include <boost/dynamic_bitset.hpp>
#include <bitset>
int main()
{
    NTL::ZZ a(89755);
    dixon dixon(a);
    std::pair<NTL::ZZ,NTL::ZZ> result(dixon.do_factorise());
    std::cout<<a<<" можно получить умножив "<<result.first<<" на " <<result.second<<'\n';
    return 0;
}
