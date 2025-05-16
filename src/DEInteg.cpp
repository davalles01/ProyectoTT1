// $Source$
// --------------------------------------------------------------------------------------------------------
// DEInteg.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/14
//
/** @file DEInteg.cpp
 *  @brief DEInteg function header.
 *
 *  Integrates a system of ordinary differential equations (ODEs) using the variable-order, 
 *  variable-step multistep method by Shampine & Gordon.
 *
 *  Reference: Shampine, L. F., & Gordon, M. K. (1975). 
 *  Computer Solution of Ordinary Differential Equations: The Initial Value Problem.
 *  Freeman and Company, San Francisco.
 *
 *  @author Daniel Vallés
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/DEInteg.hpp"
#include <cmath>

Matrix DEInteg(Matrix f(double x, Matrix y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix y){

    double twou  = 2*eps;
    double fouru = 4*eps;

    enum DE_STATE {
        DE_INIT     = 1,
        DE_DONE     = 2,
        DE_BADACC   = 3,
        DE_NUMSTEPS = 4,
        DE_STIFF    = 5,
        DE_INVPARAM = 6
    };

    DE_STATE State_ = DE_INIT;
    bool PermitTOUT = true;
    int told = 0;

    Matrix two(14), gstr(14);
    two(1)  = 1.0; two(2)  = 2.0; two(3)  = 4.0; two(4)  = 8.0; two(5)  = 16.0; two(6)  = 32.0; two(7)  = 64.0;
    two(8)  = 128.0; two(9)  = 256.0; two(10) = 512.0; two(11) = 1024.0; two(12) = 2048.0; two(13) = 4096.0; two(14) = 8192.0;

    gstr(1)  = 1.0; gstr(2)  = 0.5; gstr(3)  = 0.0833; gstr(4)  = 0.0417; gstr(5)  = 0.0264; gstr(6)  = 0.0188; gstr(7)  = 0.0143;
    gstr(8)  = 0.0114; gstr(9)  = 0.00936; gstr(10) = 0.00789; gstr(11) = 0.00679; gstr(12) = 0.00592; gstr(13) = 0.00524; gstr(14) = 0.00468;

    Matrix yy    = zeros(n_eqn,1);    
    Matrix wt    = zeros(n_eqn,1);
    Matrix p     = zeros(n_eqn,1);
    Matrix yp    = zeros(n_eqn,1);
    Matrix phi   = zeros(n_eqn,17);
    Matrix g     = zeros(14,1);
    Matrix sig   = zeros(14,1);
    Matrix rho   = zeros(14,1);
    Matrix w     = zeros(13,1);
    Matrix alpha = zeros(13,1);
    Matrix beta  = zeros(13,1);
    Matrix v     = zeros(13,1);
    Matrix psi_  = zeros(13,1);

    if(t==tout){
        return transpose(y);
    }

    double epsilon = max(relerr,abserr);

    if ((relerr < 0.0) ||                    // Negative relative error bound
    (abserr < 0.0) ||                    // Negative absolute error bound
    (epsilon <= 0.0) ||                  // Both error bounds are non-positive
    (State_ > DE_INVPARAM) ||            // Invalid status flag
    ((State_ != DE_INIT) && (t != told)) // Wrong state with mismatched t
   ) {
        State_ = DE_INVPARAM;                // Set error code
        return transpose(y);                 // Exit
    }


    double del    = tout - t;
    double absdel = abs(del);

    double tend   = t + 100.0*del;
    if (!PermitTOUT){
        tend = tout;
    }

    double nostep = 0;
    double kle4   = 0;
    bool stiff  = false;
    double releps = relerr/epsilon;
    double abseps = abserr/epsilon;

    double delsgn;
    bool OldPermit = false;
    double x;
    double h;
    bool start;
    
    if  ( (State_== DE_INIT) || (!OldPermit) || (delsgn*del<=0.0) ){
        
        start  = true;
        x      = t;
        yy     = y;
        delsgn = sign_(1.0, del);
        h      = sign_( max(fouru*abs(x), abs(tout-x)), tout-x );
    }

    int kold = 0;
    bool crash, nornd;

    while (true) { // Start step loop
        
        // If already past output point, interpolate solution and return
        if (abs(x - t) >= absdel) {
            Matrix yout = zeros(n_eqn, 1);
            Matrix ypout = zeros(n_eqn, 1);
    
            g(2,1) = 1.0;
            rho(2,1) = 1.0;
            double hi = tout - x;
            int ki = kold + 1;
            
            // Initialize w[*] for computing g[*]
            for (int i = 1; i <= ki; ++i) {
                double temp1 = static_cast<double>(i);
                w(i + 1,1) = 1.0 / temp1;
            }
    
            // Compute g[*]
            double term = 0.0;
            for (int j = 2; j <= ki; ++j) {
                double psijm1 = psi_(j,1);
                double gamma = (hi + term) / psijm1;
                double eta = hi / psijm1;
                for (int i = 1; i <= ki + 1 - j; ++i) {
                    w(i + 1,1) = gamma * w(i + 1,1) - eta * w(i + 2,1);
                }
                g(j + 1,1) = w(2,1);
                rho(j + 1,1) = gamma * rho(j,1);
                term = psijm1;
            }
            
            // Interpolate for the solution yout and for
            // the derivative of the solution ypout
            for (int j = 1; j <= ki; ++j) {
                int i = ki + 1 - j;
                Matrix aux_phi = extract_column(phi,i + 1);
                yout  = yout  + transpose(aux_phi) * g(i + 1,1);
                ypout = ypout + transpose(aux_phi) * rho(i + 1,1);
            }
            
            yout = y + yout * hi;
            y = yout;
            
            State_ = DE_DONE;  // Set return code
            t = tout;          // Set independent variable
            told = t;          // Store independent variable
            OldPermit = PermitTOUT;
            return transpose(y);          // Normal exit
        }
        
        // If cannot go past output point and sufficiently close, extrapolate and return
        if (!PermitTOUT && (abs(tout - x) < fouru * abs(x))) {
            
            h = tout - x; 
            Matrix yp_aux1 = f(x, transpose(yy));
            yp = transpose(yp_aux1);
            y = yy + yp * h;             // Extrapolate vector from x to tout
            
            State_ = DE_DONE;            // Set return code
            t = tout;                    // Set independent variable
            told = t;                    // Store independent variable
            OldPermit = PermitTOUT;
            return transpose(y);        // Normal exit
        }
        
        // Limit step size, set weight vector and take a step
        h = sign_(min(abs(h), abs(tend - x)), h);
        for (int l = 1; l <= n_eqn; ++l) {
            wt(l,1) = releps * abs(yy(l,1)) + abseps;
        }
        
        //Begin Block 0
        // Check if step size too small for machine precision
        if (abs(h) < fouru * abs(x)) {
            h = sign_(fouru * abs(x), h);
            crash = true;
            return transpose(y);  // Exit
        }

        double p5eps = 0.5 * epsilon;
        crash = false;
        g(2,1) = 1.0;
        g(3,1) = 0.5;
        sig(2,1) = 1.0;

        int ifail = 0;
        
        // If error tolerance is too small, increase it to an acceptable value.
        double round = 0.0;
        for (int l = 1; l <= n_eqn; ++l) {
            round += (y(l,1) * y(l,1)) / (wt(l,1) * wt(l,1));
        }
        round = twou * sqrt(round);
        if (p5eps < round) {
            epsilon = 2.0 * round * (1.0 + fouru);
            crash = true;
            return transpose(y);
        }

        int k;
        double hold;
        
        if (start) {
            // Initialize. Compute appropriate step size for first step.
            Matrix yp_aux2 = f(x, transpose(y)); 
            yp = transpose(yp_aux2);
            
            double sum = 0.0;
            for (int l = 1; l <= n_eqn; ++l) {
                phi(l, 2) = yp(l,1);
                phi(l, 3) = 0.0;
                sum += (yp(l,1) * yp(l,1)) / (wt(l,1) * wt(l,1));
            }
            sum = sqrt(sum);
            double absh = abs(h);
            if (epsilon < 16.0 * sum * h * h) {
                absh = 0.25 * sqrt(epsilon / sum);
            }
            h = sign_(max(absh, fouru * abs(x)), h);
            hold = 0.0;
            double hnew = 0.0;
            k = 1;
            kold = 0;
            start = false;
            bool phase1 = true;
            nornd = true;
            if (p5eps <= 100.0 * round) {
                nornd = false;
                for (int l = 1; l <= n_eqn; ++l) {
                    phi(l, 16) = 0.0;
                }
            }
        }
        
        int ns, nsp1, kp1, kp2, km1, km2, knew;
        double xold, absh;
        double realns, temp1, temp2, temp3, temp4, temp5, temp6;
        bool phase1;
        double erk, erkm1, erkm2;

        while (true) {

            // Begin block 1

            // Compute coefficients of formulas for this step. Avoid computing
            // those quantities not changed when step size is not changed.

            kp1 = k + 1;
            kp2 = k + 2;
            km1 = k - 1;
            km2 = k - 2;

            // ns is the number of steps taken with size h, including the current one.
            // When k < ns, no coefficients change.

            if (h != hold) {
                ns = 0;
            }
            if (ns <= kold) {
                ns = ns + 1;
            }
            nsp1 = ns + 1;

            

            if (k >= ns) {
                // Compute those components of alpha[*], beta[*], psi[*], sig[*]
                // which are changed
                beta(ns + 1,1) = 1.0;
                realns = static_cast<double>(ns);
                alpha(ns + 1,1) = 1.0 / realns;
                temp1 = h * realns;
                sig(nsp1 + 1,1) = 1.0;

                if (k >= nsp1) {
                    for (int i = nsp1; i <= k; ++i) {
                        int im1 = i - 1;
                        temp2 = psi_(im1 + 1,1);
                        psi_(im1 + 1,1) = temp1;
                        beta(i + 1,1) = beta(im1 + 1,1) * psi_(im1 + 1,1) / temp2;
                        temp1 = temp2 + h;
                        alpha(i + 1,1) = h / temp1;
                        double reali = static_cast<double>(i);
                        sig(i + 2,1) = reali * alpha(i + 1,1) * sig(i + 1,1);
                    }
                }
                psi_(k + 1,1) = temp1;
                
                // Compute coefficients g[*]; initialize v[*] and set w[*].
                if (ns > 1) {
                    // If order was raised, update diagonal part of v[*]
                    if (k > kold) {
                        temp4 = k * kp1;
                        v(k + 1,1) = 1.0 / temp4;
                        int nsm2 = ns - 2;
                        for (int j = 1; j <= nsm2; ++j) {
                            int i = k - j;
                            v(i + 1,1) = v(i + 1,1) - alpha(j + 2,1) * v(i + 2,1);
                        }
                    }

                    // Update V[*] and set W[*]
                    int limit1 = kp1 - ns;
                    temp5 = alpha(ns + 1,1);
                    for (int iq = 1; iq <= limit1; ++iq) {
                        v(iq + 1,1) = v(iq + 1,1) - temp5 * v(iq + 2,1);
                        w(iq + 1,1) = v(iq + 1,1);
                    }
                    g(nsp1 + 1,1) = w(2,1);
                } else {
                    for (int iq = 1; iq <= k; ++iq) {
                        temp3 = iq * (iq + 1);
                        v(iq + 1,1) = 1.0 / temp3;
                        w(iq + 1,1) = v(iq + 1,1);
                    }
                }

                // Compute the g[*] in the work vector w[*]
                int nsp2 = ns + 2;
                if (kp1 >= nsp2) {
                    for (int i = nsp2; i <= kp1; ++i) {
                        int limit2 = kp2 - i;
                        temp6 = alpha(i,1);
                        for (int iq = 1; iq <= limit2; ++iq) {
                            w(iq + 1,1) = w(iq + 1,1) - temp6 * w(iq + 2,1);
                        }
                        g(i + 1,1) = w(2,1);
                    }
                }
            }

            // Begin block 2

            // Predict a solution p(*), evaluate derivatives using predicted
            // solution, estimate local error at order k and errors at orders
            // k, k-1, k-2 as if constant step size were used.

            // Change phi to phi star
            if (k >= nsp1) {
                for (int i = nsp1; i <= k; ++i) {
                    double temp1 = beta(i + 1, 1);
                    for (int l = 1; l <= n_eqn; ++l) {
                        phi(l, i + 1) = temp1 * phi(l, i + 1);
                    }
                }
            }
            
            // Predict solution and differences
            for (int l = 1; l <= n_eqn; ++l) {
                phi(l, kp2 + 1) = phi(l, kp1 + 1);
                phi(l, kp1 + 1) = 0.0;
                p(l, 1) = 0.0;
            }
            for (int j = 1; j <= k; ++j) {
                int i = kp1 - j;
                int ip1 = i + 1;
                double temp2 = g(i + 1, 1);
                for (int l = 1; l <= n_eqn; ++l) {
                    p(l, 1) += temp2 * phi(l, i + 1);
                    phi(l, i + 1) += phi(l, ip1 + 1);
                }
            }
            if (nornd) {
                p = y + p * h;
            } else {
                for (int l = 1; l <= n_eqn; ++l) {
                    double tau = h * p(l,1) - phi(l, 16);
                    p(l, 1) = y(l,1) + tau;
                    phi(l, 17) = (p(l,1) - y(l,1)) - tau;
                }
            }
            xold = x;
            x += h;
            absh = abs(h);

            Matrix yp_aux3 = f(x, transpose(p));
            yp = transpose(yp_aux3);

            // Estimate errors at orders k, k-1, k-2
            erkm2 = 0.0;
            erkm1 = 0.0;
            erk   = 0.0;
            
            for (int l = 1; l <= n_eqn; ++l) {
                double temp3 = 1.0 / wt(l,1);
                double temp4 = yp(l,1) - phi(l, 2); // phi(l,1+1)
                
                if (km2 > 0) {
                    double term = (phi(l, km1 + 1) + temp4) * temp3;
                    erkm2 += term * term;
                }
                if (km2 >= 0) {
                    double term = (phi(l, k + 1) + temp4) * temp3;
                    erkm1 += term * term;
                }
                double term = temp4 * temp3;
                erk += term * term;
            }
            if (km2 > 0) {
                erkm2 = absh * sig(km1 + 1, 1) * gstr(km2 + 1) * sqrt(erkm2);
            }
            if (km2 >= 0) {
                erkm1 = absh * sig(k + 1, 1) * gstr(km1 + 1) * sqrt(erkm1);
            }

            double temp5 = absh * sqrt(erk);
            double err = temp5 * (g(k + 1, 1) - g(kp1 + 1, 1));
            erk = temp5 * sig(kp1 + 1, 1) * gstr(k + 1);

            knew = k;

            // Test if order should be lowered
            if (km2 > 0) {
                if (max(erkm1, erkm2) <= erk) {
                    knew = km1;
                }
            }
            if (km2 == 0) {
                if (erkm1 <= 0.5 * erk) {
                    knew = km1;
                }
            }
            // End block 2

            // If step is successful continue with block 4, otherwise repeat
            // blocks 1 and 2 after executing block 3

            bool success = (err <= epsilon);
            
            
            if (!success) {

                // Begin block 3

                // The step is unsuccessful. Restore x, phi(*,*), psi_. If
                // 3rd consecutive failure, set order to 1. If step fails more
                // than 3 times, consider an optimal step size. Double error
                // tolerance and return if estimated step size is too small
                // for machine precision.

                // Restore x, phi(*,*) and psi_
                phase1 = false;
                x = xold;

                for (int i = 1; i <= k; ++i) {
                    double temp1 = 1.0 / beta(i + 1, 1);
                    int ip1 = i + 1;
                    for (int l = 1; l <= n_eqn; ++l) {
                        phi(l, i + 1) = temp1 * (phi(l, i + 1) - phi(l, ip1 + 1));
                    }
                }

                if (k >= 2) {
                    for (int i = 2; i <= k; ++i) {
                        psi_(i, 1) = psi_(i + 1, 1) - h;
                    }
                }

                // On third failure, set order to one.
                // Thereafter, use optimal step size
                ++ifail;
                double temp2 = 0.5;

                if (ifail > 3) {
                    if (p5eps < 0.25 * erk) {
                        temp2 = sqrt(p5eps / erk);
                    }
                }

                if (ifail >= 3) {
                    knew = 1;
                }

                h = temp2 * h;
                k = knew;

                if (abs(h) < fouru * abs(x)) {
                    crash = true;
                    h = sign_(fouru * abs(x), h);
                    epsilon *= 2.0;
                    return transpose(y); // Exit
                }

                // End block 3, return to start of block 1
            }

            if (success) {
                break;
            }
        }

        // Begin block 4
        //
        // The step is successful. Correct the predicted solution, evaluate
        // the derivatives using the corrected solution and update the
        // differences. Determine best order and step size for next step.
        //
        
        kold = k;
        hold = h;

        // Correct and evaluate
        temp1 = h * g(kp1 + 1, 1);

        if (nornd) {
            for (int l = 1; l <= n_eqn; ++l) {
                y(l, 1) = p(l, 1) + temp1 * (yp(l, 1) - phi(l, 2));
            }
        } else {
            for (int l = 1; l <= n_eqn; ++l) {
                double rho_ = temp1 * (yp(l, 1) - phi(l, 2)) - phi(l, 17);
                y(l, 1) = p(l, 1) + rho_;
                phi(l, 16) = (y(l, 1) - p(l, 1)) - rho_;
            }
        }

        Matrix yp_aux4 = f(x, transpose(y));
        yp = transpose(yp_aux4);

        // Update differences for next step
        for (int l = 1; l <= n_eqn; ++l) {
            phi(l, kp1 + 1) = yp(l, 1) - phi(l, 2);
            phi(l, kp2 + 1) = phi(l, kp1 + 1) - phi(l, kp2 + 1);
        }
        for (int i = 1; i <= k; ++i) {
            for (int l = 1; l <= n_eqn; ++l) {
                phi(l, i + 1) = phi(l, i + 1) + phi(l, kp1 + 1);
            }
        }

        // Estimate error at order k+1 unless:
        // - in first phase when always raise order,
        // - already decided to lower order,
        // - step size not constant so estimate unreliable

        double erkp1 = 0.0;
        if ((knew == km1) || (k == 12)) {
            phase1 = false;
        }

        if (phase1) {
            k = kp1;
            erk = erkp1;
        } else {
            if (knew == km1) {
                // lower order
                k = km1;
                erk = erkm1;
            } else {
                if (kp1 <= ns) {
                    for (int l = 1; l <= n_eqn; ++l) {
                        double temp_phi = phi(l, kp2 + 1) / wt(l, 1);
                        erkp1 += temp_phi * temp_phi;
                    }
                    erkp1 = absh * gstr(kp1 + 1) * sqrt(erkp1);

                    // Using estimated error at order k+1, determine
                    // appropriate order for next step
                    if (k > 1) {
                        if (erkm1 <= min(erk, erkp1)) {
                            // lower order
                            k = km1;
                            erk = erkm1;
                        } else if ((erkp1 < erk) && (k != 12)) {
                            // raise order
                            k = kp1;
                            erk = erkp1;
                        }
                    } else if (erkp1 < 0.5 * erk) {
                        // raise order
                        k = kp1;
                        erk = erkp1;
                    }
                }
            }
        }

        double hnew;
        // With new order determine appropriate step size for next step
        if (phase1 || (p5eps >= erk * two(k + 2))) {
            hnew = 2.0 * h;
        } else if (p5eps < erk) {
            double temp2 = k + 1;
            double r = p5eps / pow(erk, 1.0 / temp2);
            hnew = absh * max(0.5, min(0.9, r));
            hnew = sign_(max(hnew, fouru * abs(x)), h);
        } else {
            hnew = h;
        }
        h = hnew;

        // End block 4

        // Test for too small tolerances
        if (crash) {
            State_ = DE_STATE::DE_BADACC;

            // Modify relative and absolute accuracy requirements
            relerr = epsilon * releps;
            abserr = epsilon * abseps;

            // Copy last step
            y = yy;
            t = x;
            told = t;
            OldPermit = true;

            return transpose(y);  // Weak failure exit
        }

        ++nostep;  // Count total number of steps

        // Count number of consecutive steps taken with the order of
        // the method being less or equal to four and test for stiffness
        ++kle4;
        if (kold > 4) {
            kle4 = 0;
        }
        if (kle4 >= 50) {
            stiff = true;
        }
    }

    return transpose(y);
}