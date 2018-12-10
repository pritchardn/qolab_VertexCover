//
// Created by nicholas on 28/06/18.
//
#include "uc.h"

//TODO: Use machine_spec structs
void generate_uc(qaoa_data_t *meta_data, int (*Cx)(int, int, qaoa_data_t *)) {
    int current, i, num_qubits;
    num_qubits = meta_data->machine_spec->num_qubits;
    MKL_INT space_dimension = (MKL_INT) pow(2, num_qubits);
    double c_sum = 0.0, classic_prob;
    classic_prob = (double) 1.0 / factorial(meta_data->cost_data->x_range);
    meta_data->qaoa_statistics->max_value = INT_MIN;
    meta_data->qaoa_statistics->max_index = 0;
    for (i = 0; i < space_dimension; ++i) {
        current = Cx(i, num_qubits, meta_data);
        if (current > meta_data->qaoa_statistics->max_value) {
            meta_data->qaoa_statistics->max_value = current;
            meta_data->qaoa_statistics->max_index = i;
        }
        c_sum += (double) current * classic_prob;
        //Pre-multplying by -I to save time later.
        meta_data->uc[i].imag = -current;
    }
    meta_data->qaoa_statistics->classical_exp = c_sum;
    meta_data->qaoa_statistics->random_exp = c_sum * 1 / classic_prob / pow(2, num_qubits);
}