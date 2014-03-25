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

#ifndef qtruss1dgrad_h
#define qtruss1dgrad_h

#include "fei1dlin.h"
#include "structuralelement.h"
#include "gaussintegrationrule.h"
#include "graddpelement.h"
#include "qtruss1d.h"

#define _IFT_QTruss1dGrad_Name "qtruss1dgrad"

namespace oofem {
/**
 * This class implements a three-node gradient truss bar element for one-dimensional
 * analysis.
 */
class QTruss1dGrad : public QTruss1d, public GradDpElement
{
protected:
    double length;
    static FEI1dLin interpolation;

public:
    QTruss1dGrad(int n, Domain * d);
    virtual ~QTruss1dGrad() { }

    virtual const char *giveInputRecordName() const { return _IFT_QTruss1dGrad_Name; }
    virtual const char *giveClassName() const { return "QTruss1dGrad"; }

    virtual MaterialMode giveMaterialMode() { return _1dMat; }
    virtual IRResultType initializeFrom(InputRecord *ir);
    virtual int computeNumberOfDofs() { return 5; }
    int getNprimNodes() { return 3; }
    int getNprimVars() { return 1; }
    int getNsecNodes() { return 2; }
    int getNsecVars() { return 1; }

protected:
    virtual void computeBkappaMatrixAt(GaussPoint *gp, FloatMatrix &answer);
    virtual void computeNkappaMatrixAt(GaussPoint *gp, FloatMatrix &answer);
    virtual void computeStiffnessMatrix(FloatMatrix &answer, MatResponseMode rMode, TimeStep *tStep);
    virtual void giveInternalForcesVector(FloatArray &answer, TimeStep *tStep, int useUpdatedGpRecord = 0);
    virtual void computeForceLoadVector(FloatArray &answer, TimeStep *tStep, ValueModeType mode);
    virtual void computeGaussPoints();
    virtual void giveDofManDofIDMask(int inode, EquationID ut, IntArray &answer) const;
    virtual StructuralElement *giveStructuralElement() { return this; }
    virtual NLStructuralElement *giveNLStructuralElement() { return this; }
};
} // end namespace oofem
#endif // truss1d_h
