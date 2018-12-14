//
// Created by nicholas on 4/12/18.
//

#include "main.h"
#include "qaoa.h"
#include <math.h>

int main(int argc, char *argv[]){

    run_spec_t run_spec;
    run_spec.correct = true;
    run_spec.report = false;
    run_spec.timing = true;
    run_spec.sampling = false;
    run_spec.num_samples = 0;
    run_spec.outfile = stdout;

    optimisation_spec_t opt_spec;
    opt_spec.ftol = 1e-8;
    opt_spec.xtol = 1e-8;
    opt_spec.nlopt_method = 28;
    opt_spec.max_evals = 200*1;

    machine_spec_t mach_spec;
    mach_spec.num_qubits = 4;
    mach_spec.P = 1;
    mach_spec.space_dimension = (MKL_INT)pow(2, mach_spec.num_qubits);

    cost_data_t cost_data;
    cost_data.cx_range = mach_spec.space_dimension;
    cost_data.x_range = mach_spec.space_dimension;

    qaoa(&mach_spec, &cost_data, &opt_spec, &run_spec);

    return 0;
}
