//
// Created by swsmth on 5/25/20.
//

#ifndef __HS071_NLP_HPP
#define __HS071_NLP_HPP

#include "IpTNLP.hpp"

#include <assert.h>

using namespace Ipopt;

class HS071_NLP: public TNLP {

    // pure virtual methods from Ipopt::TNLP class to be implemented here
    bool get_nlp_info(Index &n, Index &m, Index &nnz_jac_g, Index &nnz_h_lag, IndexStyleEnum &index_style);
    bool get_bounds_info(Index n, Number *x_l, Number *x_u, Index m, Number *g_l, Number *g_u);
    bool get_starting_point (Index n, bool init_x, Number *x, bool init_z, Number *z_L, Number *z_U, Index m, bool init_lambda, Number *lambda);
    bool get_warm_start_iterate (IteratesVector &warm_start_iterate);
    bool eval_f (Index n, const Number *x, bool new_x, Number &obj_value);
    bool eval_grad_f (Index n, const Number *x, bool new_x, Number *grad_f);
    bool eval_g (Index n, const Number *x, bool new_x, Index m, Number *g);
    bool eval_jac_g (Index n, const Number *x, bool new_x, Index m, Index nele_jac, Index *iRow, Index *jCol, Number *values);

};

bool HS071_NLP::get_nlp_info(Index &n, Index &m, Index &nnz_jac_g, Index &nnz_h_lag, IndexStyleEnum &index_style) {
    // Method to request the initial information about the problem.

    // Ipopt uses this information when allocating the arrays that it will later ask you to fill with values.
    // Be careful in this method since incorrect values will cause memory bugs which may be very difficult to find.

    // Parameters
    // n	        (out) Storage for the number of variables x
    // m	        (out) Storage for the number of constraints g(x)
    // nnz_jac_g	(out) Storage for the number of nonzero entries in the Jacobian
    // nnz_h_lag	(out) Storage for the number of nonzero entries in the Hessian
    // index_style	(out) Storage for the index style, the numbering style used for row/col entries in the sparse matrix
    //                    format (TNLP::C_STYLE: 0-based, TNLP::FORTRAN_STYLE: 1-based; see also Triplet Format for Sparse Matrices).

    // The problem described in HS071_NLP.hpp has 4 variables, x[0] through x[3]
    n = 4;
    // one equality constraint and one inequality constraint
    m = 2;
    // in this example the jacobian is dense and contains 8 nonzeros
    nnz_jac_g = 8;
    // the Hessian is also dense and has 16 total nonzeros, but we
    // only need the lower left corner (since it is symmetric)
    nnz_h_lag = 10;
    // use the C style indexing (0-based)
    index_style = TNLP::C_STYLE;
    return true;

};

bool HS071_NLP::get_bounds_info(Index n, Number *x_l, Number *x_u, Index m, Number *g_l, Number *g_u){
    // Method to request bounds on the variables and constraints.

    // Parameters
    // n	(in) the number of variables x in the problem
    // x_l	(out) the lower bounds xL for the variables x
    // x_u	(out) the upper bounds xU for the variables x
    // m	(in) the number of constraints g(x) in the problem
    // g_l	(out) the lower bounds gL for the constraints g(x)
    // g_u	(out) the upper bounds gU for the constraints g(x)

    // Returns
    // true if success, false otherwise.

    // here, the n and m we gave IPOPT in get_nlp_info are passed back to us.
    // If desired, we could assert to make sure they are what we think they are.

    assert(n == 4);
    assert(m == 2);
    // the variables have lower bounds of 1
    for( Index i = 0; i < 4; i++ )
    {
        x_l[i] = 1.0;
    }
    // the variables have upper bounds of 5
    for( Index i = 0; i < 4; i++ )
    {
        x_u[i] = 5.0;
    }
    // the first constraint g1 has a lower bound of 25
    g_l[0] = 25;
    // the first constraint g1 has NO upper bound, here we set it to 2e19.
    // Ipopt interprets any number greater than nlp_upper_bound_inf as
    // infinity. The default value of nlp_upper_bound_inf and nlp_lower_bound_inf
    // is 1e19 and can be changed through ipopt options.
    g_u[0] = 2e19;
    // the second constraint g2 is an equality constraint, so we set the
    // upper and lower bound to the same value
    g_l[1] = g_u[1] = 40.0;
    return true;

};

bool HS071_NLP::get_starting_point (Index n, bool init_x, Number *x, bool init_z, Number *z_L, Number *z_U, Index m, bool init_lambda, Number *lambda) {
    // Method to request the starting point before iterating.

    // Parameters
    // n	        (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // init_x	    (in) if true, this method must provide an initial value for x
    // x	        (out) the initial values for the primal variables x
    // init_z	    (in) if true, this method must provide an initial value for the bound multipliers zL and zU
    // z_L	        (out) the initial values for the bound multipliers zL
    // z_U	        (out) the initial values for the bound multipliers zU
    // m	        (in) the number of constraints g(x) in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // init_lambda	(in) if true, this method must provide an initial value for the constraint multipliers \lambda
    // lambda	    (out) the initial values for the constraint multipliers, \lambda

    // Returns
    // true if success, false otherwise.



};

bool HS071_NLP::get_warm_start_iterate (IteratesVector &warm_start_iterate){

};

bool HS071_NLP::eval_f (Index n, const Number *x, bool new_x, Number &obj_value){

};

bool HS071_NLP::eval_grad_f (Index n, const Number *x, bool new_x, Number *grad_f){

};

bool HS071_NLP::eval_g (Index n, const Number *x, bool new_x, Index m, Number *g){

};

bool HS071_NLP::eval_jac_g (Index n, const Number *x, bool new_x, Index m, Index nele_jac, Index *iRow, Index *jCol, Number *values){

};


#endif //MYEXAMPLE_HS071_NLP_HPP
