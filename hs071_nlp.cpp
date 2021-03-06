//
// Created by swsmth on 5/25/20.
//

#include "hs071_nlp.hpp"

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

bool HS071_NLP::get_starting_point(Index n, bool init_x, Number *x, bool init_z, Number *z_L, Number *z_U, Index m, bool init_lambda, Number *lambda) {
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

    // Here, we assume we only have starting values for x, if you code
    // your own NLP, you can provide starting values for the dual variables
    // if you wish
    assert(init_x == true);
    assert(init_z == false);
    assert(init_lambda == false);
    // initialize to the given starting point
    x[0] = 1.0;
    x[1] = 5.0;
    x[2] = 5.0;
    x[3] = 1.0;
    return true;

};

bool HS071_NLP::eval_f(Index n, const Number *x, bool new_x, Number &obj_value){
    // Method to request the value of the objective function.

    // Parameters
    // n	        (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // x	        (in) the values for the primal variables x at which the objective function f(x) is to be evaluated
    // new_x	    (in) false if any evaluation method (eval_*) was previously called with the same values in x, true otherwise. This can be helpful when users have efficient implementations that calculate multiple outputs at once. Ipopt internally caches results from the TNLP and generally, this flag can be ignored.
    // obj_value	(out) storage for the value of the objective function f(x)

    // Returns
    // true if success, false otherwise.

    assert(n == 4);
    obj_value = x[0] * x[3] * (x[0] + x[1] + x[2]) + x[2];
    return true;

};

bool HS071_NLP::eval_grad_f(Index n, const Number *x, bool new_x, Number *grad_f){
    // Method to request the gradient of the objective function.

    // Parameters
    // n	    (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // x	    (in) the values for the primal variables x at which the gradient \grad f(x) is to be evaluated
    // new_x	(in) false if any evaluation method (eval_*) was previously called with the same values in x, true otherwise; see also TNLP::eval_f
    // grad_f	(out) array to store values of the gradient of the objective function \grad f(x). The gradient array is in the same order as the x variables (i.e., the gradient of the objective with respect to x[2] should be put in grad_f[2]).

    // Returns
    // true if success, false otherwise.

    assert(n == 4);
    grad_f[0] = x[0] * x[3] + x[3] * (x[0] + x[1] + x[2]);
    grad_f[1] = x[0] * x[3];
    grad_f[2] = x[0] * x[3] + 1;
    grad_f[3] = x[0] * (x[0] + x[1] + x[2]);
    return true;

};

bool HS071_NLP::eval_g(Index n, const Number *x, bool new_x, Index m, Number *g){
    // Method to request the constraint values.

    // Parameters
    // n	    (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // x	    (in) the values for the primal variables x at which the constraint functions g(x) are to be evaluated
    // new_x	(in) false if any evaluation method (eval_*) was previously called with the same values in x, true otherwise; see also TNLP::eval_f
    // m	    (in) the number of constraints g(x) in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // g	    (out) array to store constraint function values g(x), do not add or subtract the bound values gL or gU.

    // Returns
    // true if success, false otherwise.

    assert(n == 4);
    assert(m == 2);
    g[0] = x[0] * x[1] * x[2] * x[3];
    g[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3];
    return true;

};

bool HS071_NLP::eval_jac_g(Index n, const Number *x, bool new_x, Index m, Index nele_jac, Index *iRow, Index *jCol, Number *values){
    // Method to request either the sparsity structure or the values of the Jacobian of the constraints.

    // The Jacobian is the matrix of derivatives where the derivative of constraint function gi with respect to variable xj is placed in row i and column j. See Triplet Format for Sparse Matrices for a discussion of the sparse matrix format used in this method.

    // Parameters
    // n	    (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // x	    (in) first call: NULL; later calls: the values for the primal variables x at which the constraint Jacobian \grad g(x)T is to be evaluated
    // new_x	(in) false if any evaluation method (eval_*) was previously called with the same values in x, true otherwise; see also TNLP::eval_f
    // m	    (in) the number of constraints g(x) in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // nele_jac	(in) the number of nonzero elements in the Jacobian; it will have the same value that was specified in TNLP::get_nlp_info
    // iRow	    (out) first call: array of length nele_jac to store the row indices of entries in the Jacobian of the constraints; later calls: NULL
    // jCol	    (out) first call: array of length nele_jac to store the column indices of entries in the Jacobian of the constraints; later calls: NULL
    // values	(out) first call: NULL; later calls: array of length nele_jac to store the values of the entries in the Jacobian of the constraints

    // Returns
    // true if success, false otherwise.

    assert(n == 4);
    assert(m == 2);
    if( values == NULL )
    {
        // return the structure of the Jacobian
        // this particular Jacobian is dense
        iRow[0] = 0;
        jCol[0] = 0;
        iRow[1] = 0;
        jCol[1] = 1;
        iRow[2] = 0;
        jCol[2] = 2;
        iRow[3] = 0;
        jCol[3] = 3;
        iRow[4] = 1;
        jCol[4] = 0;
        iRow[5] = 1;
        jCol[5] = 1;
        iRow[6] = 1;
        jCol[6] = 2;
        iRow[7] = 1;
        jCol[7] = 3;
    }
    else
    {
        // return the values of the Jacobian of the constraints
        values[0] = x[1] * x[2] * x[3]; // 0,0
        values[1] = x[0] * x[2] * x[3]; // 0,1
        values[2] = x[0] * x[1] * x[3]; // 0,2
        values[3] = x[0] * x[1] * x[2]; // 0,3
        values[4] = 2 * x[0]; // 1,0
        values[5] = 2 * x[1]; // 1,1
        values[6] = 2 * x[2]; // 1,2
        values[7] = 2 * x[3]; // 1,3
    }
    return true;

};

void HS071_NLP::finalize_solution (SolverReturn status, Index n, const Number *x, const Number *z_L, const Number *z_U, Index m,
                                   const Number *g, const Number *lambda, Number obj_value, const IpoptData *ip_data, IpoptCalculatedQuantities *ip_cq) {
    // This method is called when the algorithm has finished (successfully or not) so the TNLP can digest the outcome, e.g., store/write the solution, if any.

    // Parameters
    // status	(in) gives the status of the algorithm:
    //      - SUCCESS: Algorithm terminated successfully at a locally optimal point, satisfying the convergence tolerances
    //                  (can be specified by options).
    //      - MAXITER_EXCEEDED: Maximum number of iterations exceeded (can be specified by an option).
    //      - CPUTIME_EXCEEDED: Maximum number of CPU seconds exceeded (can be specified by an option).
    //      - STOP_AT_TINY_STEP: Algorithm proceeds with very little progress.
    //      - STOP_AT_ACCEPTABLE_POINT: Algorithm stopped at a point that was converged, not to "desired" tolerances,
    //                                  but to "acceptable" tolerances (see the acceptable-... options).
    //      - LOCAL_INFEASIBILITY: Algorithm converged to a point of local infeasibility. Problem may be infeasible.
    //      - USER_REQUESTED_STOP: The user call-back function TNLP::intermediate_callback returned false, i.e., the
    //                             user code requested a premature termination of the optimization.
    //      - DIVERGING_ITERATES: It seems that the iterates diverge.
    //      - RESTORATION_FAILURE: Restoration phase failed, algorithm doesn't know how to proceed.
    //      - ERROR_IN_STEP_COMPUTATION: An unrecoverable error occurred while Ipopt tried to compute the search direction.
    //      - INVALID_NUMBER_DETECTED: Algorithm received an invalid number (such as NaN or Inf) from the NLP;
    //                                 see also option check_derivatives_for_nan_inf).
    //      - INTERNAL_ERROR: An unknown internal error occurred.

    //    n	        (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    //    x	        (in) the final values for the primal variables
    //    z_L	    (in) the final values for the lower bound multipliers
    //    z_U	    (in) the final values for the upper bound multipliers
    //    m	        (in) the number of constraints g(x) in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    //    g	        (in) the final values of the constraint functions
    //    lambda	(in) the final values of the constraint multipliers
    //    obj_value	(in) the final value of the objective function
    //    ip_data	(in) provided for expert users
    //    ip_cq	    (in) provided for expert users

    // here is where we would store the solution to variables, or write to a file, etc
    // so we could use the solution.
    // For this example, we write the solution to the console
    std::cout << std::endl << std::endl << "Solution of the primal variables, x" << std::endl;
    for( Index i = 0; i < n; i++ )
    {
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }
    std::cout << std::endl << std::endl << "Solution of the bound multipliers, z_L and z_U" << std::endl;
    for( Index i = 0; i < n; i++ )
    {
        std::cout << "z_L[" << i << "] = " << z_L[i] << std::endl;
    }
    for( Index i = 0; i < n; i++ )
    {
        std::cout << "z_U[" << i << "] = " << z_U[i] << std::endl;
    }
    std::cout << std::endl << std::endl << "Objective value" << std::endl;
    std::cout << "f(x*) = " << obj_value << std::endl;
    std::cout << std::endl << "Final value of the constraints:" << std::endl;
    for( Index i = 0; i < m; i++ )
    {
        std::cout << "g(" << i << ") = " << g[i] << std::endl;
    }

};

bool HS071_NLP::eval_h(Index n, const Number *x, bool new_x, Number obj_factor, Index m, const Number *lambda, bool new_lambda,
                       Index nele_hess, Index *iRow, Index *jCol, Number *values) {

    // Method to request either the sparsity structure or the values of the Hessian of the Lagrangian.

    // Parameters
    // n	        (in) the number of variables x in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // x	        (in) first call: NULL; later calls: the values for the primal variables x at which the Hessian is to be evaluated
    // new_x	    (in) false if any evaluation method (eval_*) was previously called with the same values in x, true otherwise; see also TNLP::eval_f
    // obj_factor	(in) factor σf in front of the objective term in the Hessian
    // m	        (in) the number of constraints g(x) in the problem; it will have the same value that was specified in TNLP::get_nlp_info
    // lambda	    (in) the values for the constraint multipliers λ at which the Hessian is to be evaluated
    // new_lambda	(in) false if any evaluation method was previously called with the same values in lambda, true otherwise
    // nele_hess	(in) the number of nonzero elements in the Hessian; it will have the same value that was specified in TNLP::get_nlp_info
    // iRow	        (out) first call: array of length nele_hess to store the row indices of entries in the Hessian; later calls: NULL
    // jCol	        (out) first call: array of length nele_hess to store the column indices of entries in the Hessian; later calls: NULL
    // values	    (out) first call: NULL; later calls: array of length nele_hess to store the values of the entries in the Hessian

    // Returns
    // true if success, false otherwise.

    assert(n == 4);
    assert(m == 2);
    if( values == NULL )
    {
        // return the structure. This is a symmetric matrix, fill the lower left
        // triangle only.
        // the hessian for this problem is actually dense
        Index idx = 0;
        for( Index row = 0; row < 4; row++ )
        {
            for( Index col = 0; col <= row; col++ )
            {
                iRow[idx] = row;
                jCol[idx] = col;
                idx++;
            }
        }
        assert(idx == nele_hess);
    }
    else
    {
        // return the values. This is a symmetric matrix, fill the lower left
        // triangle only
        // fill the objective portion
        values[0] = obj_factor * (2 * x[3]); // 0,0
        values[1] = obj_factor * (x[3]);     // 1,0
        values[2] = 0.;                      // 1,1
        values[3] = obj_factor * (x[3]);     // 2,0
        values[4] = 0.;                      // 2,1
        values[5] = 0.;                      // 2,2
        values[6] = obj_factor * (2 * x[0] + x[1] + x[2]); // 3,0
        values[7] = obj_factor * (x[0]);                   // 3,1
        values[8] = obj_factor * (x[0]);                   // 3,2
        values[9] = 0.;                                    // 3,3
        // add the portion for the first constraint
        values[1] += lambda[0] * (x[2] * x[3]); // 1,0
        values[3] += lambda[0] * (x[1] * x[3]); // 2,0
        values[4] += lambda[0] * (x[0] * x[3]); // 2,1
        values[6] += lambda[0] * (x[1] * x[2]); // 3,0
        values[7] += lambda[0] * (x[0] * x[2]); // 3,1
        values[8] += lambda[0] * (x[0] * x[1]); // 3,2
        // add the portion for the second constraint
        values[0] += lambda[1] * 2; // 0,0
        values[2] += lambda[1] * 2; // 1,1
        values[5] += lambda[1] * 2; // 2,2
        values[9] += lambda[1] * 2; // 3,3
    }
    return true;

};