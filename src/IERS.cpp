// $Source$
// --------------------------------------------------------------------------------------------------------
// IERS.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/21
//
/** @file IERS.cpp
 *  @brief Function to manage IERS time and polar motion data.
 *
 *  @author Daniel Vallés Belloso
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/IERS.hpp"
#include "../include/SAT_Const.hpp"

using namespace consts;

void IERS(Matrix& eop, double Mjd_UTC, char interp,
          double& x_pole, double& y_pole, double& UT1_UTC, double& LOD, 
          double& dpsi, double& deps, double& dx_pole, double& dy_pole, double& TAI_UTC) {

    if (interp == 'l') {
        // Linear interpolation
        double mjd = floor(Mjd_UTC);
        int i = -1;

        for (int j = 0; j < eop.n_column; ++j) {
            if (mjd == eop(4, j)) {
                i = j;
                break;
            }
        }

        if (i == -1) {
            cout << "MJD not found in the EOP matrix." << endl;
            exit(EXIT_FAILURE);
        }

        Matrix preeop = extract_column(eop, i);
        Matrix nexteop = extract_column(eop, i+1);

        double mfme = 1440 * (Mjd_UTC - floor(Mjd_UTC));
        double fixf = mfme / 1440;

        // Setting of IERS Earth rotation parameters
        x_pole = preeop(5) + (nexteop(5) - preeop(5)) * fixf;
        y_pole = preeop(6) + (nexteop(6) - preeop(6)) * fixf;
        UT1_UTC = preeop(7) + (nexteop(7) - preeop(7)) * fixf;
        LOD = preeop(8) + (nexteop(8) - preeop(8)) * fixf;
        dpsi = preeop(9) + (nexteop(9) - preeop(9)) * fixf;
        deps = preeop(10) + (nexteop(10) - preeop(10)) * fixf;
        dx_pole = preeop(11) + (nexteop(11) - preeop(11)) * fixf;
        dy_pole = preeop(12) + (nexteop(12) - preeop(12)) * fixf;
        TAI_UTC = preeop(13);

        x_pole = x_pole / Arcs;  // Convert to rad
        y_pole = y_pole / Arcs;  // Convert to rad
        dpsi = dpsi / Arcs;
        deps = deps / Arcs;
        dx_pole = dx_pole / Arcs;
        dy_pole = dy_pole / Arcs;

    } else if (interp == 'n') {
        // No interpolation
        double mjd = floor(Mjd_UTC);
        int i = -1;

        for (int j = 0; j < eop.n_column; ++j) {
            if (mjd == eop(4, j)) {
                i = j;
                break;
            }
        }

        if (i == -1) {
            cout << "MJD not found in the EOP matrix." << endl;
            exit(EXIT_FAILURE);
        }

        Matrix eop_col = extract_column(eop,i);

        // Setting of IERS Earth rotation parameters
        x_pole = eop_col(5) / Arcs;  // Convert to rad
        y_pole = eop_col(6) / Arcs;  // Convert to rad
        UT1_UTC = eop_col(7);  // UT1-UTC time difference [s]
        LOD = eop_col(8);  // Length of day [s]
        dpsi = eop_col(9) / Arcs;
        deps = eop_col(10) / Arcs;
        dx_pole = eop_col(11) / Arcs;  // Convert to rad
        dy_pole = eop_col(12) / Arcs;  // Convert to rad
        TAI_UTC = eop_col(13);  // TAI-UTC time difference [s]
    }
}