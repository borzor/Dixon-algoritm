#include "dixon.hpp"
#include <boost/dynamic_bitset.hpp>
#include <bitset>
int main()
{
    NTL::ZZ a(89755);
    dixon dixon(a);
    dixon.do_factorise();
    return 0;
}
