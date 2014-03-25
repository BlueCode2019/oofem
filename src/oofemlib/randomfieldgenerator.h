/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef randomfieldgenerator_h
#define randomfieldgenerator_h

#include "floatarray.h"
#include "gausspoint.h"

namespace oofem {
class OOFEM_EXPORT RandomFieldGenerator : public FEMComponent
{
public:
    /// Constructor. Creates empty RandomFieldGenerator.
    RandomFieldGenerator(int n, Domain * d) : FEMComponent(n, d) { }
    /// Destructor.
    virtual ~RandomFieldGenerator() { }
    /**
     * Generates random value.
     */
    virtual void generateRandomValue(double &value, FloatArray *position) {; }
    virtual void generateRandomValueAt(double &value, GaussPoint *gp) {
        FloatArray globalCoordinates;
        if ( gp->giveElementGeometry()->computeGlobalCoordinates( globalCoordinates, * ( gp->giveLocalCoordinates() ) ) ) {
            this->generateRandomValue(value, & globalCoordinates);
        } else {
            OOFEM_ERROR("RandomFieldGenerator::generateRandomValue computeGlobalCoordinates failed");
        }
    }

    virtual IRResultType initializeFrom(InputRecord *ir) { return IRRT_OK; }
};
} // end namespace oofem
#endif
