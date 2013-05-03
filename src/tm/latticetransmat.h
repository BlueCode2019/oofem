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
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef latticetransmat_h

#include "transportmaterial.h"
#include "dictionary.h"
#include "floatarray.h"
#include "floatmatrix.h"
#include "cltypes.h"
#include "matstatus.h"

///@name Input fields for Lattice2d_mt
//@{
#define _IFT_LatticeTransportMaterial_vis "vis"
#define _IFT_LatticeTransportMaterial_k "k"
#define _IFT_LatticeTransportMaterial_thetas "thetas"
#define _IFT_LatticeTransportMaterial_thetar "thetar"
#define _IFT_LatticeTransportMaterial_contype "contype"
#define _IFT_LatticeTransportMaterial_m "m"
#define _IFT_LatticeTransportMaterial_a "a"
#define _IFT_LatticeTransportMaterial_thetam "thetam"
#define _IFT_LatticeTransportMaterial_paev "paev"
#define _IFT_LatticeTransportMaterial_ctor "ctor"
//@}

namespace oofem {
/**
 * This class implements associated Material Status to LatticeTransportMaterial.
 */
class LatticeTransportMaterialStatus : public TransportMaterialStatus
{
protected:
    /// Liquid mass in element
    double mass;

public:
    ///Constructor
    LatticeTransportMaterialStatus(int n, Domain *d, GaussPoint *g);
    /// Destructor
    ~LatticeTransportMaterialStatus() { }

    void   printOutputAt(FILE *, TimeStep *);

    ///Returns pressure
    double givePressure() { return stateVector.at(1); }

    ///Sets the mass
    void setMass(double input) { this->mass = input; }

    ///Returns mass
    double giveMass() { return this->mass; }

    void updateYourself(TimeStep *tStep);

    void initTempStatus();

    const char *giveClassName() const { return "LatticeTransportMaterialStatus"; }

    classType giveClassID() const { return LatticeTransportMaterialStatusClass; }
};

class LatticeTransportMaterial : public TransportMaterial
{
    /**
     *   This class implements a transport constitutive model for saturated and unsaturated porous materials for lattice elements.
     */

protected:

    ///Viscosity of fluid
    double viscosity;

    ///Parameter of van Genuchten law
    double paramM;

    ///Parameter of van Genuchten law
    double paramA;

    ///Intrinsic permeability of porous material
    double permeability;

    ///Porosity of porous material
    double porosity;

    ///Density of fluid
    double density;

    ///Type of conductivity and capcity laws.
    int conType;

    ///Relative saturated water content
    double thetaS;

    ///Residual water content
    double thetaR;

    ///modified water content
    double thetaM;

    ///crack tortuosity
    double crackTortuosity;

    ///suction air entry value
    double suctionAirEntry;

public:

    LatticeTransportMaterial(int n, Domain *d) : TransportMaterial(n, d) {}

    ~LatticeTransportMaterial() {}

    void  giveCharacteristicMatrix(FloatMatrix &answer,
                                   MatResponseForm form,
                                   MatResponseMode mode,
                                   GaussPoint *gp,
                                   TimeStep *atTime) {; }

    virtual double  giveCharacteristicValue(MatResponseMode mode,
                                            GaussPoint *gp,
                                            TimeStep *atTime);

    /**
     * Computes the conductivity.
     * @param stateVector Capillary stress
     * @param gp Integration point.
     * @param stepN Time step.
     */

    double computeConductivity(FloatArray &stateVector, GaussPoint *gp, TimeStep *stepN);

    /**
     * Computes the capacity.
     * @param stateVector Capillary stress
     * @param gp Integration point.
     */

    double computeCapacity(FloatArray &stateVector, GaussPoint *gp);

    /**
     * Computes the mass.
     * @param stateVector Capillary stress
     * @param gp Integration point.
     */

    double computeMass(FloatArray &stateVector, GaussPoint *gp);

    const char *giveClassName() const { return "LatticeTransportMaterial"; }
    classType giveClassID()         const { return LatticeTransportMaterialClass; }

    IRResultType initializeFrom(InputRecord *ir);

    double   give(int, GaussPoint *gp);

    virtual MaterialStatus *CreateStatus(GaussPoint *gp) const;

    MaterialStatus *giveStatus(GaussPoint *gp) const;
};
} // end namespace oofem
#define latticetransmat_h
#endif