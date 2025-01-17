#include "module_hamilt_lcao/hamilt_lcaodft/LCAO_domain.h"
#include "module_base/timer.h"
#include "module_hamilt_pw/hamilt_pwdft/global.h"
#include "module_hamilt_lcao/module_deepks/LCAO_deepks.h"

namespace LCAO_domain
{

void divide_HS_in_frag(const bool isGamma, Parallel_Orbitals& pv,const int& nks) {
    ModuleBase::TITLE("LCAO_Matrix", "divide_HS_in_frag");

    //(1), (2): set up matrix division have been moved into ESolver_KS_LCAO::init_basis_lcao
    // just pass `ParaV` as pointer is enough
#ifdef __DEEPKS
    // wenfei 2021-12-19
    // preparation for DeePKS

    if (GlobalV::deepks_out_labels || GlobalV::deepks_scf) {
        // allocate relevant data structures for calculating descriptors
        std::vector<int> na;
        na.resize(GlobalC::ucell.ntype);
        for (int it = 0; it < GlobalC::ucell.ntype; it++) {
            na[it] = GlobalC::ucell.atoms[it].na;
        }

        GlobalC::ld.init(GlobalC::ORB,
                         GlobalC::ucell.nat,
                         GlobalC::ucell.ntype,
                         pv,
                         na);

        if (GlobalV::deepks_scf) {
            if (isGamma) {
                GlobalC::ld.allocate_V_delta(GlobalC::ucell.nat);
            } else {
                GlobalC::ld.allocate_V_delta(GlobalC::ucell.nat, nks);
            }
        }
    }
#endif
    return;
}

}
