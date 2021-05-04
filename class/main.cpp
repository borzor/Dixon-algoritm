#include "dixon.hpp"


int main()
{
    NTL::ZZ a(89755);
    NTL::ZZ two(2);
    std::pair<NTL::ZZ,NTL::ZZ> numbers(430, 5390);
    dixon dixon(a);
    dixon.create_factor_base();
    //dixon.generate_numbers();
    dixon.Check_on_Smooth(numbers);
    return 0;
}
