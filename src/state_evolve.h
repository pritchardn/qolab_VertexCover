/**
 * @author Nicholas Pritchard
 * @date 1/07/18
 */

#ifndef QOLAB_STATE_EVOLVE_H
#define QOLAB_STATE_EVOLVE_H
#include "globals.h"

double evolve(unsigned num_params, const double *x, double *grad, qaoa_data_t *meta_spec);

double evolve_restricted(unsigned num_params, const double *x, double *grad, qaoa_data_t *meta_spec);

#endif //QOLAB_STATE_EVOLVE_H
