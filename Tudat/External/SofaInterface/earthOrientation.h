#ifndef TUDAT_SOFAEARTHORIENTATION_H
#define TUDAT_SOFAEARTHORIENTATION_H

extern "C"
{
#include "sofa/src/sofa.h"
#include "sofa/src/sofam.h"
}

#include <map>
#include <iostream>

#include <Eigen/Core>

#include "Tudat/Astrodynamics/BasicAstrodynamics/timeConversions.h"


namespace tudat
{

enum IAUConventions
{
    iau_2000_a,
    iau_2000_b,
    iau_2006
};

namespace sofa_interface
{

//! Function to calculate CIP and CIO locator according to requested IAU conventions
/*!
 *  Function to calculate CIP (Celestial Intermediate Pole, typically denoted as X and Y) and CIO locator
 *  (Celestial Intermediate Origin, typically denoted s) according to requested IAU conventions using Sofa implementation.
 *  See Petit et al. (2010), chap. 5 for more details on requested variables.
 *  Note that this function does not include empirical corrections, published as daily values by the IERS.
 *  \param terrestrialTime Time in TT in seconds since referenceJulianDay julianDay.
 *  \param referenceJulianDay Julian day wrt which tt is referenced (default = J2000)
 *  \param precessionNutationTheory IAU conventions that are to be used for calculation
 *  (i.e. determining which Sofa function to call)
 *  \return Pair of first: Vector of entries X, Y (in that order) CIP values and second: CIO locator.
 */
std::pair< Eigen::Vector2d, double > getPositionOfCipInGcrs(
        const double terrestrialTime, const double referenceJulianDay = basic_astrodynamics::JULIAN_DAY_ON_J2000,
        const IAUConventions precessionNutationTheory = iau_2000_b );

//! Function to calculate GMST according to requested IAU conventions
/*!
 *  Function to calculate GMST (Greenwich Mean Sidereal Time) according to requested IAU conventions
 *  using Sofa implementation.  Note that this function does not include empirical corrections, as published as daily
 *  values by IERS.
 *  \param terrestrialTimeJulianDaysSinceJ2000 Time in TT in seconds since J2000
 *  \param universalTime1JulianDaysSinceJ2000 Time in UT1 in seconds since J2000
 *  \param referenceJulianDay Julian day wrt which input times are referenced (default = J2000)
 *  \param iauConvention IAU conventions that are to be used for calculation (i.e. determining which Sofa function to call)
 *  \return Current GMST (normalized to [0,2 pi]).
 */
double calculateGreenwichMeanSiderealTime(
        const double terrestrialTimeJulianDaysSinceJ2000, const double universalTime1JulianDaysSinceJ2000,
        const double referenceJulianDay = basic_astrodynamics::JULIAN_DAY_ON_J2000,
        const IAUConventions iauConvention = iau_2000_b );

//! Function to calculate ERA (earth rotation angle)
/*!
 *  Function to calculate GMST ERA (earth rotation angle) from current UT1.
 *  The ERA represents one of the Euler angles (between CIO and TIO) for transforming from ITRS to GCRS,
 *  see Petit et al. chap. 5
 *  \param ut1 Time in UT1 in seconds since referenceJulianDay julianDay.
 *  \param referenceJulianDay Julian day wrt which ut1 is referenced (default = J2000)
 *  \return Current Earth rotation angle (normalized to [0,2 pi]).
 */
double calculateEarthRotationAngle(
        const double ut1, const double referenceJulianDay = basic_astrodynamics::JULIAN_DAY_ON_J2000 );

}

}

#endif // TUDAT_SOFAEARTHORIENTATION_H