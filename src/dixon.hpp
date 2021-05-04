#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <vector>
class dixon
{
private:
    std::vector<NTL::ZZ>prime_numbers;
    NTL::ZZ N;
    std::vector<std::vector<uint32_t>>vec;
    std::vector<std::pair<NTL::ZZ,NTL::ZZ>>pairs;
public:
    dixon(NTL::ZZ N);
    void create_factor_base();
    std::pair<NTL::ZZ, NTL::ZZ> generate_numbers();
    bool Check_on_Smooth(std::pair<NTL::ZZ, NTL::ZZ> pair);
};


