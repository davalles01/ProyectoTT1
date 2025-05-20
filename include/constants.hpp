// $Header$
// --------------------------------------------------------------------------------------------------------
// constatns.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file constatns.hpp
 *  @brief Definition of some useful mathematical constants.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cmath>
#include <limits>

namespace constants {
    /// @brief The value of π (pi)
    inline constexpr double pi = M_PI;

    /// @brief Machine epsilon for double precision
    inline constexpr double eps = std::numeric_limits<double>::epsilon();

    /// @brief Equatorial radius of Earth in meters (WGS-84)
    inline constexpr double R_Earth = 6378136.3;

    /// @brief Flattening of the Earth (WGS-84)
    inline constexpr double f_Earth = 1.0 / 298.257223563;

}

#endif // CONSTANTS_HPP