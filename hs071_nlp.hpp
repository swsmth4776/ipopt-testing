//
// Created by swsmth on 5/25/20.
//

#ifndef __HS071_NLP_HPP
#define __HS071_NLP_HPP

#include "IpTNLP.hpp"

#include <assert.h>
#include <iostream>

using namespace Ipopt;

class HS071_NLP: public TNLP {

    // pure virtual methods from Ipopt::TNLP class to be implemented here
    bool get_nlp_info(Index &n, Index &m, Index &nnz_jac_g, Index &nnz_h_lag, IndexStyleEnum &index_style);
    bool get_bounds_info(Index n, Number *x_l, Number *x_u, Index m, Number *g_l, Number *g_u);
    bool get_starting_point (Index n, bool init_x, Number *x, bool init_z, Number *z_L, Number *z_U, Index m,
                                bool init_lambda, Number *lambda);
    bool eval_f (Index n, const Number *x, bool new_x, Number &obj_value);
    bool eval_grad_f (Index n, const Number *x, bool new_x, Number *grad_f);
    bool eval_g (Index n, const Number *x, bool new_x, Index m, Number *g);
    bool eval_jac_g (Index n, const Number *x, bool new_x, Index m, Index nele_jac, Index *iRow, Index *jCol, Number *values);
    void finalize_solution (SolverReturn status, Index n, const Number *x, const Number *z_L, const Number *z_U, Index m,
            const Number *g, const Number *lambda, Number obj_value, const IpoptData *ip_data, IpoptCalculatedQuantities *ip_cq);

    // function for evaluting the Hessian of the Lagrangian
    bool eval_h(Index n, const Number *x, bool new_x, Number obj_factor, Index m, const Number *lambda, bool new_lambda,
                    Index nele_hess, Index *iRow, Index *jCol, Number *values);

};

#endif //__HS071_NLP_HPP
