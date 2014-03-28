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

#ifndef trplanstrain_h
#define trplanstrain_h

#include "nlstructuralelement.h"
#include "zznodalrecoverymodel.h"
#include "nodalaveragingrecoverymodel.h"
#include "sprnodalrecoverymodel.h"
#include "spatiallocalizer.h"
#include "directerrorindicatorrc.h"
#include "eleminterpmapperinterface.h"
#include "zzerrorestimator.h"
#include "mmashapefunctprojection.h"
#include "huertaerrorestimator.h"
#include "fei2dtrlin.h"
#include "gausspoint.h"

#define _IFT_TrPlaneStrain_Name "trplanestrain"

namespace oofem {
/**
 * This class implements an triangular three-node  plane-
 * strain elasticity finite element. Each node has 2 degrees of freedom.
 */
class TrPlaneStrain : public StructuralElement, public ZZNodalRecoveryModelInterface,
public NodalAveragingRecoveryModelInterface, public SPRNodalRecoveryModelInterface,
public SpatialLocalizerInterface,
public DirectErrorIndicatorRCInterface,
public EIPrimaryUnknownMapperInterface,
public ZZErrorEstimatorInterface, public ZZRemeshingCriteriaInterface,
public MMAShapeFunctProjectionInterface,
public HuertaErrorEstimatorInterface, public HuertaRemeshingCriteriaInterface
{
protected:
    static FEI2dTrLin interp;
    double area;

public:
    TrPlaneStrain(int n, Domain * d);
    virtual ~TrPlaneStrain() { }

    virtual FEInterpolation *giveInterpolation() const { return & interp; }

    virtual int computeNumberOfDofs() { return 6; }
    virtual void giveDofManDofIDMask(int inode, EquationID, IntArray &) const;

    virtual double giveCharacteristicLenght(GaussPoint *gp, const FloatArray &normalToCrackPlane);

    virtual int testElementExtension(ElementExtension ext) { return ( ext == Element_EdgeLoadSupport ); }
    virtual double computeVolumeAround(GaussPoint *gp);

    virtual Interface *giveInterface(InterfaceType it);

    virtual ElementGeometry *ZZNodalRecoveryMI_giveElementGeometry() { return this; }

    virtual void NodalAveragingRecoveryMI_computeNodalValue(FloatArray &answer, int node,
                                                            InternalStateType type, TimeStep *tStep);
    virtual void NodalAveragingRecoveryMI_computeSideValue(FloatArray &answer, int side,
                                                           InternalStateType type, TimeStep *tStep);

    virtual void SPRNodalRecoveryMI_giveSPRAssemblyPoints(IntArray &pap);
    virtual void SPRNodalRecoveryMI_giveDofMansDeterminedByPatch(IntArray &answer, int pap);
    virtual int SPRNodalRecoveryMI_giveNumberOfIP();
    virtual SPRPatchType SPRNodalRecoveryMI_givePatchType();

    virtual double DirectErrorIndicatorRCI_giveCharacteristicSize();

    virtual ElementGeometry *SpatialLocalizerI_giveElementGeometry() { return this; }
    virtual int SpatialLocalizerI_containsPoint(const FloatArray &coords);
    virtual double SpatialLocalizerI_giveDistanceFromParametricCenter(const FloatArray &coords);

    virtual int EIPrimaryUnknownMI_computePrimaryUnknownVectorAt(ValueModeType u,
                                                                 TimeStep *tStep, const FloatArray &coords,
                                                                 FloatArray &answer);
    virtual void EIPrimaryUnknownMI_givePrimaryUnknownVectorDofID(IntArray &answer);

    // ZZErrorEstimatorInterface
    virtual ElementGeometry *ZZErrorEstimatorI_giveElementGeometry() { return this; }

    // HuertaErrorEstimatorInterface
    virtual BaseElement *HuertaErrorEstimatorI_giveElement() { return this; }

    virtual void HuertaErrorEstimatorI_setupRefinedElementProblem(RefinedElement *refinedElement, int level, int nodeId,
                                                                  IntArray &localNodeIdArray, IntArray &globalNodeIdArray,
                                                                  HuertaErrorEstimatorInterface :: SetupMode sMode, TimeStep *tStep,
                                                                  int &localNodeId, int &localElemId, int &localBcId,
                                                                  IntArray &controlNode, IntArray &controlDof,
                                                                  HuertaErrorEstimator :: AnalysisMode aMode);
    virtual void HuertaErrorEstimatorI_computeLocalCoords(FloatArray &answer, const FloatArray &coords)
    { computeLocalCoordinates(answer, coords); }
    virtual void HuertaErrorEstimatorI_computeNmatrixAt(GaussPoint *gp, FloatMatrix &answer)
    { computeNmatrixAt(* ( gp->giveLocalCoordinates() ), answer); }

    // ZZRemeshingCriteriaInterface
    virtual double ZZRemeshingCriteriaI_giveCharacteristicSize() { return DirectErrorIndicatorRCI_giveCharacteristicSize(); }
    virtual int ZZRemeshingCriteriaI_givePolynOrder() { return 1; };

    // HuertaRemeshingCriteriaInterface
    virtual double HuertaRemeshingCriteriaI_giveCharacteristicSize() { return DirectErrorIndicatorRCI_giveCharacteristicSize(); };
    virtual int HuertaRemeshingCriteriaI_givePolynOrder() { return 1; };

    virtual void MMAShapeFunctProjectionInterface_interpolateIntVarAt(FloatArray &answer, FloatArray &coords,
                                                                      coordType ct, nodalValContainerType &list,
                                                                      InternalStateType type, TimeStep *tStep);

#ifdef __OOFEG
    virtual void drawRawGeometry(oofegGraphicContext &);
    virtual void drawDeformedGeometry(oofegGraphicContext &, UnknownType);
    virtual void drawScalar(oofegGraphicContext &context);
#endif

    // definition & identification
    virtual const char *giveInputRecordName() const { return _IFT_TrPlaneStrain_Name; }
    virtual const char *giveClassName() const { return "TrPlaneStrain"; }
    virtual IRResultType initializeFrom(InputRecord *ir);
    virtual MaterialMode giveMaterialMode() { return _PlaneStrain; }

protected:
    // edge load support
    virtual void computeEgdeNMatrixAt(FloatMatrix &answer, int iedge, GaussPoint *gp);
    virtual void giveEdgeDofMapping(IntArray &answer, int) const;
    virtual double computeEdgeVolumeAround(GaussPoint *gp, int);
    virtual void computeEdgeIpGlobalCoords(FloatArray &answer, GaussPoint *gp, int iEdge);
    virtual int computeLoadLEToLRotationMatrix(FloatMatrix &, int, GaussPoint *gp);
    virtual void computeBmatrixAt(GaussPoint *gp, FloatMatrix &, int = 1, int = ALL_STRAINS);
    virtual void computeBHmatrixAt(GaussPoint *gp, FloatMatrix &);


    virtual void computeGaussPoints();

    virtual int giveApproxOrder() { return 1; }
    virtual int giveNumberOfIPForMassMtrxIntegration() { return 1; }
};
} // end namespace oofem
#endif // trplanstrain_h
