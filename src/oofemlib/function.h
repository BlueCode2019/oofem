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

#ifndef function_h
#define function_h

#include "femcmpnn.h"
#include "domain.h"
#include "valuemodetype.h"
#include "floatarray.h"

#include <map>
#include <algorithm>

///@name Input fields for Function
//@{
#define _IFT_Function_initialvalue "initialvalue" ///@todo Deprecated
//@}

namespace oofem {
class FloatArray;
class IntArray;

/**
 * Wrapper for values of varying types.
 * Used in lists of function arguments.
 */
class OOFEM_EXPORT FunctionArgument
{
public:
    enum FunctionArgumentType {
        FAT_double,
        FAT_FloatArray,
        FAT_int,
        FAT_IntArray,
    };

    /// Determines which of the types the instance points towards.
    FunctionArgumentType type;

    double val0;
    FloatArray val1;
    int val2;
    IntArray val3;

    FunctionArgument(double val) : type(FAT_double), val0(val), val1(), val2(0), val3() { }
    FunctionArgument(FloatArray val) : type(FAT_FloatArray),  val0(0), val1(std::move(val)), val2(0), val3() { }
    FunctionArgument(int val) : type(FAT_int),  val0(0), val1(), val2(val), val3() { }
    FunctionArgument(IntArray val) : type(FAT_IntArray),  val0(0), val1(), val2(0), val3(std::move(val)) { }
};

/**
 * Abstract base class representing a function with vector input and output.
 * It is useful in many scenarios, in particular describing the load/b.c. amplitude in time.
 */
class OOFEM_EXPORT Function : public FEMComponent
{
protected:
    /**
     * By default, the increment of receiver is computed as a difference between values evaluated at given solution step and in previous step.
     * However, if the solution step is the first step, the difference is typically set to the total value of receiver at the first step.
     * This is quite natural, as a loading with constant time function is expected to be applied at first step.
     * In certain cases, this default behavior has to be changed. The initial value (set by default to zero)
     * allows to set initial value of receiver. This initial value is used only when the increment of receiver is evaluated at first step,
     * when result is defined as value of receiver at given step minus the initial value.
     * This allows to correctly handle temperature loading, that is specified with respect to some reference temperature.
     * In this case, the initial value should be set to the reference temperature, allowing to obtain correct temperate increment in first step.
     */
    double initialValue;

public:
    /**
     * Constructor. Creates load time function with given number, belonging to given domain.
     * @param n Load time function number.
     * @param d Domain to which new object will belongs.
     */
    Function(int n, Domain * d);
    /// Destructor
    virtual ~Function() { }

    /**
     * Returns the value of load time function at given time. Abstract service.
     * Must be implemented by derived classes.
     * @param tStep Time. Incremental and total mode uses intrinsic time from giveIntrinsicTime.
     * @param mode Determines the mode of the requested value.
     * @return Load time function value.
     */
    double evaluate(TimeStep *tStep, ValueModeType mode);

    /**
     * Returns the Returns the value of the function at given time.
     * @param valDict Dictionary with values.
     * @param answer Function value.
     */
    virtual void evaluate(FloatArray &answer, std :: map< std :: string, FunctionArgument > &valDict);

    /**
     * Returns the value of the function at given time.
     * @param t Time.
     * @return @f$ f(t) @f$.
     */
    virtual double evaluateAtTime(double t);
    /**
     * Returns the first time derivative of the function at given time.
     * @param t Time.
     * @return @f$ f'(t) @f$.
     */
    virtual double evaluateVelocityAtTime(double t) = 0;
    /**
     * Returns the second time derivative of the function at given time.
     * @param t Time.
     * @return @f$ f''(t) @f$.
     */
    virtual double evaluateAccelerationAtTime(double t) = 0;

    // Overloaded methods:
    virtual IRResultType initializeFrom(InputRecord *ir);
    virtual void giveInputRecord(DynamicInputRecord &input);
};
} // end namespace oofem
#endif // function_h
