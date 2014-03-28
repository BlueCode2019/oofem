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

#ifndef TRPLANSTRSSXFEM_H_
#define TRPLANSTRSSXFEM_H_

#include "trplanstrss.h"
#include "xfem/xfemelementinterface.h"
#include "vtkxmlexportmodule.h"


#define _IFT_TrPlaneStress2dXFEM_Name "trplanestress2dxfem"

namespace oofem {
/*
 *		trplanstrssxfem.h
 *
 *
 *      Class: TrPlaneStress2dXFEM
 *      Description: 3-node triangle with XFEM kinematics
 *      @author Erik Svenning
 *
 */

class TrPlaneStress2dXFEM : public TrPlaneStress2d, public XfemElementInterface, public VTKXMLExportModuleElementInterface
{
protected:
    virtual void updateYourself(TimeStep *tStep);
    virtual void postInitialize();


public:

    TrPlaneStress2dXFEM(int n, Domain * d) : TrPlaneStress2d(n, d), XfemElementInterface(this), VTKXMLExportModuleElementInterface() { }

    virtual ~TrPlaneStress2dXFEM();


    virtual int checkConsistency();

    virtual int testElementExtension(ElementExtension ext) { return ( ( ext == Element_EdgeLoadSupport ) ? 1 : 0 ); }

    virtual Interface *giveInterface(InterfaceType it);

    virtual const char *giveInputRecordName() const { return _IFT_TrPlaneStress2dXFEM_Name; }
    virtual const char *giveClassName() const { return "TrPlaneStress2dXFEM"; }

    virtual int computeNumberOfDofs();
    virtual void computeGaussPoints();
    virtual void computeNmatrixAt(const FloatArray &iLocCoord, FloatMatrix &answer);
    virtual void computeBmatrixAt(GaussPoint *gp, FloatMatrix &answer,
                                  int lowerIndx = 1, int upperIndx = ALL_STRAINS);
    virtual void computeBHmatrixAt(GaussPoint *gp, FloatMatrix &answer);
    virtual void giveDofManDofIDMask(int inode, EquationID ut, IntArray &answer) const;
    virtual void computeConstitutiveMatrixAt(FloatMatrix &answer, MatResponseMode rMode, GaussPoint *, TimeStep *tStep);
    virtual void computeStressVector(FloatArray &answer, const FloatArray &strain, GaussPoint *gp, TimeStep *tStep);
    virtual void computeStiffnessMatrix(FloatMatrix &answer, MatResponseMode rMode, TimeStep *tStep);
    virtual void giveInternalForcesVector(FloatArray &answer, TimeStep *tStep, int useUpdatedGpRecord);

    virtual void computeConsistentMassMatrix(FloatMatrix &answer, TimeStep *tStep, double &mass, const double *ipDensity = NULL) { XfemElementInterface :: XfemElementInterface_computeConsistentMassMatrix(answer, tStep, mass, ipDensity); }

    //    virtual Element_Geometry_Type giveGeometryType() const;

#ifdef __OOFEG
    // TODO: Implement OOFEG functions
    virtual void drawRawGeometry(oofegGraphicContext &);
    //void drawDeformedGeometry(oofegGraphicContext &, UnknownType);
    virtual void drawScalar(oofegGraphicContext &context);
    //virtual void drawSpecial(oofegGraphicContext &);
#endif

    virtual IRResultType initializeFrom(InputRecord *ir);
    virtual MaterialMode giveMaterialMode();
    virtual void giveInputRecord(DynamicInputRecord &input);

    // For mapping of primary unknowns
    virtual int EIPrimaryUnknownMI_computePrimaryUnknownVectorAt(ValueModeType u,
                                                                 TimeStep *tStep, const FloatArray &coords,
                                                                 FloatArray &answer);
    virtual void EIPrimaryUnknownMI_givePrimaryUnknownVectorDofID(IntArray &answer);
};
} /* namespace oofem */
#endif /* TRPLANSTRSSXFEM_H_ */
