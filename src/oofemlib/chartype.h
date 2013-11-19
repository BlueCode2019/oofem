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

#ifndef chartype_h
#define chartype_h

#include "enumitem.h"

namespace oofem {
/**
 * Type representing kind of characteristic value (of scalar, vector or tensorial character) or
 * unknown, which is required, requested, returned, or passed to/from various general services.
 * It typically describes the physical meaning of corresponding component.
 * Typically, many top base classes declare general services for requesting or computing
 * some "characteristic" values of given type. Then only one service for all values of sane type
 * (like vector, scalar) is declared, passing the type of required value (of CharType type) as parameter.
 * Particular implementation based on passed CharType value, usually invokes corresponding specialized services
 * and returns result. If passed CharType value is of unsupported value, error is generated.
 * @see ValueModeType type.
 */
#define CharType_DEF                              \
    ENUM_ITEM_WITH_VALUE(UnknownCharType,0)                    \
    ENUM_ITEM_WITH_VALUE(StiffnessMatrix,1)                    \
    ENUM_ITEM_WITH_VALUE(TangentStiffnessMatrix,2)             \
    ENUM_ITEM_WITH_VALUE(SecantStiffnessMatrix,3)              \
    ENUM_ITEM_WITH_VALUE(ElasticStiffnessMatrix,4)             \
    ENUM_ITEM_WITH_VALUE(MassMatrix,5)                         \
    ENUM_ITEM_WITH_VALUE(LumpedMassMatrix,6)                   \
    ENUM_ITEM_WITH_VALUE(EffectiveStiffnessMatrix,7)           \
    ENUM_ITEM_WITH_VALUE(EffectiveMassMatrix,8)                \
    ENUM_ITEM_WITH_VALUE(ConductivityMatrix,9)                 \
    ENUM_ITEM_WITH_VALUE(CapacityMatrix,10)                    \
    ENUM_ITEM_WITH_VALUE(InitialStressMatrix,11)               \
    ENUM_ITEM_WITH_VALUE(HeatAndMoistureCharMatrix,12)         \
    /* CBS */                                                  \
    ENUM_ITEM_WITH_VALUE(IntermediateConvectionTerm,50)        \
    ENUM_ITEM_WITH_VALUE(IntermediateDiffusionTerm,51)         \
    ENUM_ITEM_WITH_VALUE(DensityRhsVelocityTerms,52)           \
    ENUM_ITEM_WITH_VALUE(DensityRhsPressureTerms,53)           \
    ENUM_ITEM_WITH_VALUE(DensityPrescribedTractionPressure,54) \
    ENUM_ITEM_WITH_VALUE(NumberOfNodalPrescribedTractionPressureContributions,55)   \
    ENUM_ITEM_WITH_VALUE(PressureLhs,56)                                            \
    ENUM_ITEM_WITH_VALUE(CorrectionRhs,57)                                          \
    ENUM_ITEM_WITH_VALUE(CriticalTimeStep,58)                                       \
    ENUM_ITEM_WITH_VALUE(PrescribedVelocityRhsVector,59)                            \
    ENUM_ITEM_WITH_VALUE(PrescribedDensityRhsVector,60)                             \
    /* characteristic vectors */                                                         \
    ENUM_ITEM_WITH_VALUE(ExternalForcesVector,150)                                       \
    ENUM_ITEM_WITH_VALUE(InternalForcesVector,151)                                       \
    ENUM_ITEM_WITH_VALUE(LastEquilibratedInternalForcesVector,152)                       \
    ENUM_ITEM_WITH_VALUE(ElementBCTransportVector,153)                                   \
    ENUM_ITEM_WITH_VALUE(ElementInternalSourceVector,154)                                \
    ENUM_ITEM_WITH_VALUE(LHSBCMatrix,155) /* LHS due to Boundary Conditions (Transport problems) */                       \
    ENUM_ITEM_WITH_VALUE(NSTP_MidpointLhs,156) /* NonStationaryTransportProblem - LHS for midpoint discretization alg. */ \
    ENUM_ITEM_WITH_VALUE(NSTP_MidpointRhs,157) /* NonStationaryTransportProblem - RHS for midpoint discretization alg. */ \
    ENUM_ITEM_WITH_VALUE(IntSourceLHSMatrix,158) /* LHS due to material internal source (Transport problems) */           \
    ENUM_ITEM_WITH_VALUE(PrescribedRhsVector,159)                                \
    /* PFEM */	\
    ENUM_ITEM_WITH_VALUE(AuxVelocityLhs,200)                                     \
    ENUM_ITEM_WITH_VALUE(VelocityLhs,201)                                        \
    ENUM_ITEM_WITH_VALUE(LoadVector,202)                                         \
      /*for pressureLhs see CBS */					         \
    ENUM_ITEM_WITH_VALUE(PressureGradientMatrix,203)                             \
    ENUM_ITEM_WITH_VALUE(DivergenceMatrix,204)					 \
    ENUM_ITEM_WITH_VALUE(PFEMSubstitutionMatrix,205)                             \
    ENUM_ITEM_WITH_VALUE(VelocityLaplacianMatrix,206)                            \
    ENUM_ITEM_WITH_VALUE(PressureLaplacianMatrix,207)	                         \
    ENUM_ITEM_WITH_VALUE(StabilizedLaplacianMatrix,208)                          \
    ENUM_ITEM_WITH_VALUE(StabilizationGradientMatrix,209)	                 \
    ENUM_ITEM_WITH_VALUE(StabilizationMassMatrix,210)	                         \
    ENUM_ITEM_WITH_VALUE(InvertedStabilizationMassMatrix,211)	                 \
    /* PFEM vectors */  \
    ENUM_ITEM_WITH_VALUE(PressureGradientVector,212)		                 \
    ENUM_ITEM_WITH_VALUE(MassVelocityVector,213)		                 \
    ENUM_ITEM_WITH_VALUE(MassAuxVelocityVector,214)		                 \
    ENUM_ITEM_WITH_VALUE(StabilizedLaplacePressureVector,215)		         \
    ENUM_ITEM_WITH_VALUE(LaplacePressureVector,216)		                 \
    ENUM_ITEM_WITH_VALUE(LaplaceVelocityVector,217)		                 \
    ENUM_ITEM_WITH_VALUE(DivergenceVelocityVector,218)		                 \
    ENUM_ITEM_WITH_VALUE(QMhat_invQTpressureVector,219)


enum CharType {
    CharType_DEF
};

#undef ENUM_ITEM
#undef ENUM_ITEM_WITH_VALUE
#undef enumitem_h


const char *__CharTypeToString(CharType _value);
} // end namespace oofem
#endif // chartype_h
