#include <NTL/ZZ.h>
#include <NTL/RR.h>
#include <vector>

class dixon
{
private:
    NTL::ZZ N;
    short number_of_threads;
public:
    dixon(NTL::ZZ N, short threads);
    std::vector<NTL::ZZ> create_factor_base(NTL::ZZ &N);
    std::pair<NTL::ZZ,NTL::ZZ> do_factorise();
    std::pair<NTL::ZZ,NTL::ZZ> get_result(NTL::ZZ &x, NTL::ZZ &y);
};


