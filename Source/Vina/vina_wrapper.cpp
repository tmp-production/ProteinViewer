#include "Public/vina.h"
#include "Private/vina.h"

Vina::Vina(const std::string &sf_name, int cpu, int seed, int verbosity, bool no_refine, std::function<void(double)>* progress_callback) {
    vina_impl = new IMPL::Vina(sf_name, cpu, seed, verbosity, no_refine, progress_callback);
}

Vina::~Vina() {
    delete ((IMPL::Vina *) vina_impl);
}

void Vina::cite() {
    auto vina = (IMPL::Vina *) vina_impl;
    vina->cite();
}

int Vina::seed() {
    auto vina = (IMPL::Vina *) vina_impl;
    return vina->seed();
};

// TODO: Implement remaining methods from "Public/vina.h"