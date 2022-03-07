#include "nuclidelibrary.h"

namespace model {

NuclideLibrary::NuclideLibrary()
{
}

nuclides_t NuclideLibrary::nuclides([[maybe_unused]]const probas_t &probas)
{
    nuclides_t result{
        {
            "Eu-152",
            {
                {121.782, 28.667800},
                {244.698, 7.606620},
                {344.279, 26.558000},
                {411.116, 2.237250},
                {443.965, 3.157560},
                {778.904, 12.960300},
                {867.373, 4.258420},
                {964.079, 14.649400},
                {1085.870, 10.237900},
                {1089.740, 1.729720},
                {1212.950, 1.426270},
                {1408.010, 21.069200},
            }
        }
    };

    return result;
}

}
