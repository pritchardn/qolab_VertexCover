/**
 * @author Nicholas Pritchard
 * @date 1/12/18
 */
#include "problem_code.h"

/**
 * @brief To be implemented by the user. This defines the problem investigated by the QAOA
 * @detail In this case, we are counting the number of set bits, representing the number of vertices in a cover.
 * @param i
 * @param num_qubits
 * @param cost_data
 * @return A single integer value
 */
int Cx(int i, int num_qubits, cost_data_t *cost_data){
    unsigned int c;
    for (c = 0; i; i >>= 1) {
        c += i & 1;
    }
    return c;
}

/**
 * @brief An optional function to be implemented by the user. Determines whether a given candidate solution is valid
 * @param i The candidate solution
 * @param cost_data Contains problem dependent data, may or may not be useful
 * @return True if the given solution is valid, false otherwise
 */
bool mask(unsigned int i, cost_data_t *cost_data) {
    return true;
}