// $Source$
// --------------------------------------------------------------------------------------------------------
// AzElPa.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/21
//
/** @file AzElPa.cpp
 *  @brief Azimuth, elevation and partials calculation.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/AzElPa.hpp"
#include "../include/constants.hpp"
#include <cmath>

using namespace constants;

void AzElPa(Matrix& s, double& Az, double& El, Matrix& dAds, Matrix& dEds) {
    const double pi2 = 2.0 * pi;

    double rho = std::sqrt(s(1) * s(1) + s(2) * s(2));

    // Angles
    Az = std::atan2(s(1), s(2));

    if (Az < 0.0) {
        Az = Az + pi2;
    }

    El = std::atan(s(3) / rho);

    // Partials
    dAds(1) = s(2) / (rho * rho);
    dAds(2) = -s(1) / (rho * rho);
    dAds(3) = 0.0;
    dEds(1) = -s(1) * s(3) / rho;
    dEds(2) = -s(2) * s(3) / rho;
    dEds(3) = rho;

    dEds = dEds / dot(s, s);
}
