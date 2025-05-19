// $Source$
// --------------------------------------------------------------------------------------------------------
// It4_tests.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/14
//
/** @file It4_tests.cpp
 *  @brief Tests for all iteration 4 functions
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/DEInteg.hpp"
#include "../include/Accel.hpp"
#include "../include/Mjday.hpp"
#include "../include/global.hpp"
#include <assert.h>
#include <iostream>

using namespace std;

void DEInteg_test(){

    double Mjd0 = Mjday(1995,1,29,02,38,0);

    Matrix Y0_apr(6);
    Y0_apr(1) = 6221398.24674587; Y0_apr(2) = 2867713.77142113; Y0_apr(3) = 3006156.19827565; 
    Y0_apr(4) = 4645.04675261818; Y0_apr(5) = -2752.21554475399; Y0_apr(6) = -7507.99862282957;

    Matrix expected_Y(6);
    expected_Y(1) = 5542556.62930487; expected_Y(2) = 3213514.81521648; expected_Y(3) = 3990893.08798422;
    expected_Y(4) = 5394.06783381377; expected_Y(5) = -2365.21310034617; expected_Y(6) = -7061.84483659256;

    Matrix Y = DEInteg(Accel,0,-(obs(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,transpose(Y0_apr));

    assert(equals(Y, expected_Y));
}

void DEInteg_test2(){

    double t = 572.99998998642;
    double t_old = 568.000017106533;

    Matrix Y_old(6);
    Y_old(1) = 7098603.48613637; Y_old(2) = 1310605.81357207; Y_old(3) = 46419.1857559918; 
    Y_old(4) = 613.67034949965;  Y_old(5) = -3077.70988865027; Y_old(6) = -6735.86854200982;

    Matrix expected_Y(6);
    expected_Y(1) = 7101577.66491799; expected_Y(2) = 1295200.03374753; expected_Y(3) = 12739.5577727397;
    expected_Y(4) = 576.005002658814; expected_Y(5) = -3084.62184178477; expected_Y(6) = -6736.02586895252;


    Matrix Y = DEInteg(Accel,0,t-t_old,1e-13,1e-6,6,transpose(Y_old));

    assert(equals(Y, expected_Y));
}

void It4_tests(){
    
    DEInteg_test();
    DEInteg_test2();

    cout << "All Iteration 4 tests passed successfully." << endl;
}