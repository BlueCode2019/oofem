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

#ifndef tet1bubblestokes_h
#define tet1bubblestokes_h

#include "fmelement.h"
#include "domain.h"
#include "zznodalrecoverymodel.h"
#include "spatiallocalizer.h"
#include "eleminterpmapperinterface.h"
#include "elementinternaldofman.h"

#define _IFT_Tet1BubbleStokes_Name "tet1bubblestokes"

namespace oofem {
class FEI3dTetLin;

/**
 * Tetrahedral element for Stokes flow using Bubble basis function for stabilization.
 * Linear+Bubble interpolation of velocity, and linear interpolation of pressures.
 * The element is exported as a linear tetrahedron (bubble dofs are not exported).
 * It can deal with nonlinear material models, but it is assumed that the fluid is without memory (which is usually the case).
 *
 * @author Mikael Öhman
 */
class Tet1BubbleStokes : public FMElement,
public ZZNodalRecoveryModelInterface,
public SpatialLocalizerInterface,
public EIPrimaryUnknownMapperInterface
{
protected:
    /// Interpolation for pressure
    static FEI3dTetLin interp;
    /// Ordering of dofs in element. Used to assemble the element stiffness
    static IntArray momentum_ordering, conservation_ordering;
    /// Ordering of dofs on edges. Used to assemble edge loads
    static IntArray edge_ordering [ 6 ];
    /// Ordering of dofs on surfaces. Used to assemble surface loads
    static IntArray surf_ordering [ 4 ];
    /// Dummy variable
    static bool __initialized;
    /// Convenient vectors for the ordering of the dofs in the local stiffness matrix.
    static bool initOrdering() {
        momentum_ordering.setValues(15,  1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 14, 15, 17, 18, 19);
        conservation_ordering.setValues(4, 4, 8, 12, 16);

        surf_ordering [ 0 ].setValues(9,  1, 2, 3,  9, 10, 11,  5,  6,  7);
        surf_ordering [ 1 ].setValues(9,  1, 2, 3,  5,  6,  7, 13, 14, 15);
        surf_ordering [ 2 ].setValues(9,  5, 6, 7,  9, 10, 11, 13, 14, 15);
        surf_ordering [ 3 ].setValues(9,  1, 2, 3, 13, 14, 15,  9, 10, 11);
        return true;
    }

    /// The extra dofs from the bubble
    ElementDofManager *bubble;
    // Coordinates associated with the bubble dofs.
    //FloatArray bubbleCoord; // Assumed fixed at 0 for now (i.e. only linear geometry)

public:
    Tet1BubbleStokes(int n, Domain * d);
    virtual ~Tet1BubbleStokes();

    virtual double computeVolumeAround(GaussPoint *gp);

    virtual void computeGaussPoints();

    virtual void giveCharacteristicVector(FloatArray &answer, CharType type, ValueModeType mode, TimeStep *tStep);
    virtual void giveCharacteristicMatrix(FloatMatrix &answer, CharType type, TimeStep *tStep);

    void computeInternalForcesVector(FloatArray &answer, TimeStep *tStep);
    void computeStiffnessMatrix(FloatMatrix &answer, TimeStep *tStep);

    void computeExternalForcesVector(FloatArray &answer, TimeStep *tStep);
    virtual void computeLoadVector(FloatArray &answer, Load *load, CharType type, ValueModeType mode, TimeStep *tStep);
    virtual void computeBoundaryLoadVector(FloatArray &answer, BoundaryLoad *load, int boundary, CharType type, ValueModeType mode, TimeStep *tStep);

    virtual const char *giveClassName() const { return "Tet1BubbleStokes"; }
    virtual const char *giveInputRecordName() const { return _IFT_Tet1BubbleStokes_Name; }
    virtual MaterialMode giveMaterialMode() { return _3dFlow; }

    virtual int computeNumberOfDofs();

    virtual int giveNumberOfInternalDofManagers() const { return 1; }
    virtual DofManager *giveInternalDofManager(int i) const { return bubble; }
    virtual void giveInternalDofManDofIDMask(int i, EquationID eid, IntArray &answer) const;

    virtual FEInterpolation *giveInterpolation() const;
    virtual FEInterpolation *giveInterpolation(DofIDItem id) const;

    virtual void giveDofManDofIDMask(int inode, EquationID eid, IntArray &answer) const;

    virtual void updateYourself(TimeStep *tStep);

    virtual Interface *giveInterface(InterfaceType it);

    // Spatial localizer interface:
    virtual ElementGeometry *SpatialLocalizerI_giveElementGeometry() { return this; }
    virtual int SpatialLocalizerI_containsPoint(const FloatArray &coords);
    virtual double SpatialLocalizerI_giveDistanceFromParametricCenter(const FloatArray &coords);

    // Element interpolation interface:
    virtual int EIPrimaryUnknownMI_computePrimaryUnknownVectorAt(ValueModeType u,
                                                                 TimeStep *tStep, const FloatArray &coords, FloatArray &answer);
    virtual void EIPrimaryUnknownMI_computePrimaryUnknownVectorAtLocal(ValueModeType u,
                                                                       TimeStep *tStep, const FloatArray &coords, FloatArray &answer);
    virtual void EIPrimaryUnknownMI_givePrimaryUnknownVectorDofID(IntArray &answer);

    virtual ElementGeometry *ZZNodalRecoveryMI_giveElementGeometry() { return this; }
};
} // end namespace oofem
#endif // tet1bubblestokes_h
