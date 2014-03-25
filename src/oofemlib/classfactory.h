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

#ifndef classfactory_h
#define classfactory_h

#include "oofemcfg.h"
#include "sparsemtrxtype.h"
#include "errorestimatortype.h"
#include "doftype.h"
#include "linsystsolvertype.h"
//#include "patch.h" // for PatchType
#include "nodalrecoverymodel.h" // for NodalRecoveryModelType
#include "integrationrule.h" // for IntegrationRuleType
#include "geneigvalsolvertype.h"
#include "materialmappingalgorithmtype.h"
#include "meshpackagetype.h"

#include <map>
#include <string>
#include <cstring>

namespace oofem {
class Domain;
class EngngModel;
class BaseElement;
class DofManager;
class GeneralBoundaryCondition;
class CrossSection;
class Material;
class Function;
class NonlocalBarrier;
class RandomFieldGenerator;
class ExportModule;
class SparseNonLinearSystemNM;
class InitModule;
class TopologyDescription;

class Dof;
class SparseMtrx;
class SparseLinearSystemNM;
class ErrorEstimator;
class InitialCondition;
class Patch;
class NodalRecoveryModel;
class SparseGeneralEigenValueSystemNM;
class IntegrationRule;
class MaterialMappingAlgorithm;
class MesherInterface;

class LoadBalancerMonitor;
class LoadBalancer;

class XfemManager;
class EnrichmentItem;
class EnrichmentFunction;
class EnrichmentDomain;
class BasicGeometry;
class EnrichmentFront;
class PropagationLaw;

class FractureManager;
class FailureCriteriaStatus;
class FailureCriteria;

// Templates to wrap constructors into functions
template< typename T >BaseElement *elemCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >DofManager *dofmanCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >GeneralBoundaryCondition *bcCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >CrossSection *csCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >Material *matCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >EngngModel *engngCreator(int n, EngngModel *m) { return ( new T(n, m) ); }
template< typename T >Function *funcCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >NonlocalBarrier *nlbCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >RandomFieldGenerator *rfgCreator(int n, Domain *d) { return new T(n, d); }
template< typename T >ExportModule *exportCreator(int n, EngngModel *e) { return ( new T(n, e) ); }
template< typename T >SparseNonLinearSystemNM *nonlinCreator(Domain *d, EngngModel *m) { return ( new T(d, m) ); }
template< typename T >InitModule *initCreator(int n, EngngModel *e) { return ( new T(n, e) ); }
template< typename T >TopologyDescription *topologyCreator(Domain *d) { return new T(d); }

template< typename T >Dof *dofCreator(int n, DofManager *dman) { return new T(n, dman); }
template< typename T >SparseMtrx *sparseMtrxCreator() { return new T(); }
template< typename T >SparseLinearSystemNM *sparseLinSolCreator(Domain *d, EngngModel *m) { return new T(d, m); }
template< typename T >ErrorEstimator *errEstCreator(int n, Domain *d) { return new T(n, d); }

template< typename T >LoadBalancer *loadBalancerCreator(Domain *d) { return new T(d); }
template< typename T >LoadBalancerMonitor *loadMonitorCreator(EngngModel *e) { return new T(e); }

// XFEM stuff
template< typename T > EnrichmentItem *enrichItemCreator(int n, XfemManager *x, Domain *d) { return new T(n, x, d); }
template< typename T > EnrichmentFunction *enrichFuncCreator(int n, Domain *d) { return new T(n, d); }
template< typename T > EnrichmentDomain *enrichmentDomainCreator() { return new T(); }
template< typename T > BasicGeometry *geometryCreator() { return new T(); }
template< typename T > EnrichmentFront *enrichFrontCreator() { return new T(); }
template< typename T > PropagationLaw *propagationLawCreator() { return new T(); }


template< typename T > FailureCriteria *failureCriteriaCreator(int n, FractureManager *x) { return new T(n, x); }
template< typename T > FailureCriteriaStatus *failureCriteriaCreator(int n, FailureCriteria *x) { return new T(n, x); }

///@name Macros for registering new components. Unique dummy variables must be created as a result (design flaw in C++).
//@{
#define REGISTER_Element(class ) static bool __dummy_ ## class = GiveClassFactory().registerElement(_IFT_ ## class ## _Name, elemCreator< class > );
#define REGISTER_DofManager(class ) static bool __dummy_ ## class = GiveClassFactory().registerDofManager(_IFT_ ## class ## _Name, dofmanCreator< class > );
#define REGISTER_BoundaryCondition(class ) static bool __dummy_ ## class = GiveClassFactory().registerBoundaryCondition(_IFT_ ## class ## _Name, bcCreator< class > );
#define REGISTER_CrossSection(class ) static bool __dummy_ ## class = GiveClassFactory().registerCrossSection(_IFT_ ## class ## _Name, csCreator< class > );
#define REGISTER_Material(class ) static bool __dummy_ ## class = GiveClassFactory().registerMaterial(_IFT_ ## class ## _Name, matCreator< class > );
#define REGISTER_EngngModel(class ) static bool __dummy_ ## class = GiveClassFactory().registerEngngModel(_IFT_ ## class ## _Name, engngCreator< class > );
#define REGISTER_Function(class ) static bool __dummy_ ## class = GiveClassFactory().registerFunction(_IFT_ ## class ## _Name, funcCreator< class > );
#define REGISTER_NonlocalBarrier(class ) static bool __dummy_ ## class = GiveClassFactory().registerNonlocalBarrier(_IFT_ ## class ## _Name, nlbCreator< class > );
#define REGISTER_RandomFieldGenerator(class ) static bool __dummy_ ## class = GiveClassFactory().registerRandomFieldGenerator(_IFT_ ## class ## _Name, rfgCreator< class > );
#define REGISTER_ExportModule(class ) static bool __dummy_ ## class = GiveClassFactory().registerExportModule(_IFT_ ## class ## _Name, exportCreator< class > );
#define REGISTER_SparseNonLinearSystemNM(class ) static bool __dummy_ ## class = GiveClassFactory().registerSparseNonLinearSystemNM(_IFT_ ## class ## _Name, nonlinCreator< class > );
#define REGISTER_InitModule(class ) static bool __dummy_ ## class = GiveClassFactory().registerInitModule(_IFT_ ## class ## _Name, initCreator< class > );
#define REGISTER_TopologyDescription(class ) static bool __dummy_ ## class = GiveClassFactory().registerTopologyDescription(_IFT_ ## class ## _Name, topologyCreator< class > );
#define REGISTER_LoadMonitor(class ) static bool __dummy_ ## class = GiveClassFactory().registerLoadMonitor(_IFT_ ## class ## _Name, loadMonitorCreator< class > );
#define REGISTER_LoadBalancer(class ) static bool __dummy_ ## class = GiveClassFactory().registerLoadBalancer(_IFT_ ## class ## _Name, loadBalancerCreator< class > );

// These should be converted to use strings.
#define REGISTER_SparseMtrx(class, type) static bool __dummy_ ## class = GiveClassFactory().registerSparseMtrx(type, sparseMtrxCreator< class > );
#define REGISTER_SparseLinSolver(class, type) static bool __dummy_ ## class = GiveClassFactory().registerSparseLinSolver(type, sparseLinSolCreator< class > );
#define REGISTER_ErrorEstimator(class, type) static bool __dummy_ ## class = GiveClassFactory().registerErrorEstimator(type, errEstCreator< class > );

#define REGISTER_EnrichmentItem(class) static bool __dummy_ ## class = GiveClassFactory().registerEnrichmentItem(_IFT_ ## class ## _Name, enrichItemCreator< class > );
#define REGISTER_EnrichmentFunction(class) static bool __dummy_ ## class = GiveClassFactory().registerEnrichmentFunction(_IFT_ ## class ## _Name, enrichFuncCreator< class > );
#define REGISTER_EnrichmentDomain(class) static bool __dummy_ ## class = GiveClassFactory().registerEnrichmentDomain(_IFT_ ## class ## _Name, enrichmentDomainCreator< class > );
#define REGISTER_Geometry(class) static bool __dummy_ ## class = GiveClassFactory().registerGeometry(_IFT_ ## class ## _Name, geometryCreator< class > );
#define REGISTER_EnrichmentFront(class) static bool __dummy_ ## class = GiveClassFactory().registerEnrichmentFront(_IFT_ ## class ## _Name, enrichFrontCreator< class > );
#define REGISTER_PropagationLaw(class) static bool __dummy_ ## class = GiveClassFactory().registerPropagationLaw(_IFT_ ## class ## _Name, propagationLawCreator< class > );

#define REGISTER_FailureCriteria(class) static bool __dummy_ ## class = GiveClassFactory().registerFailureCriteria(_IFT_ ## class ## _Name, failureCriteriaCreator< class > );
#define REGISTER_FailureCriteriaStatus(class) static bool __dummy_ ## class = GiveClassFactory().registerFailureCriteriaStatus(_IFT_ ## class ## _Name, failureCriteriaCreator< class > );
//@}

/**
 * Class Factory allows to register terminal oofem classes, based on their membership
 * (classes representing elements, dof managers, material models, etc)
 * and create them on demand according to their name or id.
 * Global instance of ClassFactory named classFactory is created on startup.
 *
 * @note To register new elements on startup, you must call GiveClassFactory to ensure that the global class factory is created first. This is ensured if you use the corresponding macro.
 */
class OOFEM_EXPORT ClassFactory
{
    struct CaseComp
    {
        int operator() (const std :: string &a, const std :: string &b) const;
    };

private:
    /// Associative container containing element creators with element name as key.
    std :: map < std :: string, BaseElement * ( * )(int, Domain *), CaseComp > elemList;
    /// Associative container containing dofmanager creators with dofmanager  name as key.
    std :: map < std :: string, DofManager * ( * )(int, Domain *), CaseComp > dofmanList;
    /// Associative container containing boundary condition creators with bc  name as key.
    std :: map < std :: string, GeneralBoundaryCondition * ( * )(int, Domain *), CaseComp > bcList;
    /// Associative container containing cross section creators with cross section name as key.
    std :: map < std :: string, CrossSection * ( * )(int, Domain *), CaseComp > csList;
    /// Associative container containing material creators with material name as key.
    std :: map < std :: string, Material * ( * )(int, Domain *), CaseComp > matList;
    /// Associative container containing engng model creators with engng model name as key.
    std :: map< std :: string, EngngModel * ( * )( int, EngngModel * ), CaseComp >engngList;
    /// Associative container containing load time function creators with function name as key.
    std :: map< std :: string, Function * ( * )( int, Domain * ), CaseComp >funcList;
    /// Associative container containing nonlocal barriers creators with barrier name as key.
    std :: map < std :: string, NonlocalBarrier * ( * )(int, Domain *), CaseComp > nlbList;
    /// Associative container containing random field generator creators with names as key.
    std :: map < std :: string, RandomFieldGenerator * ( * )(int, Domain *), CaseComp > rfgList;
    /// Associative container containing export module creators.
    std :: map < std :: string, ExportModule * ( * )(int, EngngModel *), CaseComp > exportList;
    /// Associative container containing nonlinear solver creators.
    std :: map < std :: string, SparseNonLinearSystemNM * ( * )(Domain *, EngngModel *), CaseComp > nonlinList;
    /// Associative container containing init module creators.
    std :: map < std :: string, InitModule * ( * )(int, EngngModel *), CaseComp > initList;
    /// Associative container containing topology description creators.
    std :: map < std :: string, TopologyDescription * ( * )(Domain *), CaseComp > topologyList;
    /// Associative container containing load balancer creators.
#ifdef __PARALLEL_MODE
    std :: map < std :: string, LoadBalancer * ( * )(Domain *), CaseComp > loadBalancerList;
    /// Associative container containing load balancer monitor creators.
    std :: map < std :: string, LoadBalancerMonitor * ( * )(EngngModel *), CaseComp > loadMonitorList;
#endif
    // Internal structures (accessed by hard-coded enum values)
    /// Associative container containing sparse matrix creators.
    std :: map < SparseMtrxType, SparseMtrx * ( * )() > sparseMtrxList;
    /// Associative container containing dof creators.
    std :: map < dofType, Dof * ( * )(int, DofManager *) > dofList;
    /// Associative container containing error estimator creators.
    std :: map < ErrorEstimatorType, ErrorEstimator * ( * )(int, Domain *) > errEstList;
    /// Associative container containing sparse linear solver creators
    std :: map < LinSystSolverType, SparseLinearSystemNM * ( * )(Domain *, EngngModel *) > sparseLinSolList;

    // XFEM:
    /// Associative container containing enrichment item creators
    std :: map < std :: string, EnrichmentItem * ( * )(int, XfemManager *, Domain *), CaseComp > enrichItemList;
    /// Associative container containing enrichment function creators
    std :: map < std :: string, EnrichmentFunction * ( * )(int, Domain *), CaseComp > enrichFuncList;
    /// Associative container containing geometry creators
    std :: map < std :: string, BasicGeometry * ( * )(), CaseComp > geometryList;
    /// Associative container containing enrichment-domain creators
    std :: map < std :: string, EnrichmentDomain * ( * )(), CaseComp > enrichmentDomainList;
    /// Associative container containing enrichment front creators
    std :: map < std :: string, EnrichmentFront * ( * )(), CaseComp > enrichmentFrontList;
    /// Associative container containing propagation law creators
    std :: map < std :: string, PropagationLaw * ( * )(), CaseComp > propagationLawList;


    /// Associative container containing failure criteria creators
    std :: map < std :: string, FailureCriteria * ( * )(int, FractureManager *), CaseComp > failureCriteriaList;
    std :: map < std :: string, FailureCriteriaStatus * ( * )(int, FailureCriteria *), CaseComp > failureCriteriaStatusList;

public:
    /// Constructor, registers all classes
    ClassFactory();

    /**
     * Creates new instance of element corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  Element number.
     * @param domain Domain assigned to new element.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    BaseElement *createElement(const char *name, int num, Domain *domain);
    /**
     * Registers a new element in the class factory.
     * @param name Keyword string.
     */
    bool registerElement( const char *name, BaseElement * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of Dof manager corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  dofmanager number.
     * @param domain Domain assigned to new instance.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    DofManager *createDofManager(const char *name, int num, Domain *domain);
    /**
     * Registers a new dof manager in the class factory.
     * @param name Keyword string.
     */
    bool registerDofManager( const char *name, DofManager * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of boundary condition corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  number of new object.
     * @param domain Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    GeneralBoundaryCondition *createBoundaryCondition(const char *name, int num, Domain *domain);
    /**
     * Registers a new boundary condition in the class factory.
     * @param name Keyword string.
     */
    bool registerBoundaryCondition( const char *name, GeneralBoundaryCondition * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of cross section corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  object's number.
     * @param domain Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    CrossSection *createCrossSection(const char *name, int num, Domain *domain);
    /**
     * Registers a new cross section in the class factory.
     * @param name Keyword string.
     */
    bool registerCrossSection( const char *name, CrossSection * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of material corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  material number.
     * @param domain Domain assigned to new material.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    Material *createMaterial(const char *name, int num, Domain *domain);
    /**
     * Registers a new material in the class factory.
     * @param name Keyword string.
     */
    bool registerMaterial( const char *name, Material * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of engng model corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  Engng model number.
     * @param master Master engineering model (used for multiscale modeling).
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    EngngModel *createEngngModel(const char *name, int num, EngngModel *master);
    /**
     * Registers a new engineering model in the class factory.
     * @param name Keyword string.
     */
    bool registerEngngModel( const char *name, EngngModel * ( *creator )( int, EngngModel * ) );
    /**
     * Creates new instance of load time function corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  object's number.
     * @param domain Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    Function *createFunction(const char *name, int num, Domain *domain);
    /**
     * Registers a new load time function in the class factory.
     * @param name Keyword string.
     */
    bool registerFunction( const char *name, Function * ( * creator )( int, Domain * ) );
    /**
     * Creates new instance of nonlocal barrier corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  object's number.
     * @param domain Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    NonlocalBarrier *createNonlocalBarrier(const char *name, int num, Domain *domain);
    /**
     * Registers a new nonlocal barrier in the class factory.
     * @param name Keyword string.
     */
    bool registerNonlocalBarrier( const char *name, NonlocalBarrier * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of random field generator corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  object's number.
     * @param domain Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    RandomFieldGenerator *createRandomFieldGenerator(const char *name, int num, Domain *domain);
    /**
     * Registers a new random field generator in the class factory.
     * @param name Keyword string.
     */
    bool registerRandomFieldGenerator( const char *name, RandomFieldGenerator * ( *creator )( int, Domain * ) );
    /**
     * Creates new instance of export module corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  Export module number.
     * @param emodel Engineering model that object belongs to.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    ExportModule *createExportModule(const char *name, int num, EngngModel *emodel);
    /**
     * Registers a new export module in the class factory.
     * @param name Keyword string.
     */
    bool registerExportModule( const char *name, ExportModule * ( *creator )( int, EngngModel * ) );
    /**
     * Creates new instance of nonlinear solver corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param domain Domain assigned to new object.
     * @param emodel Engineering model that object belongs to.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    SparseNonLinearSystemNM *createNonLinearSolver(const char *name, Domain *domain, EngngModel *emodel);
    /**
     * Registers a new nonlinear solver in the class factory.
     * @param name Keyword string.
     */
    bool registerSparseNonLinearSystemNM( const char *name, SparseNonLinearSystemNM * ( *creator )( Domain *, EngngModel * ) );
    /**
     * Creates new instance of init module corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param num  Init module number.
     * @param emodel Engineering model that object belongs to.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    InitModule *createInitModule(const char *name, int num, EngngModel *emodel);
    /**
     * Registers a new init module in the class factory.
     * @param name Keyword string.
     */
    bool registerInitModule( const char *name, InitModule * ( *creator )( int, EngngModel * ) );
    /**
     * Creates new instance of Initial Condition corresponding to given type.
     * @param name Keyword string determining the type of new instance.
     * @param num  object's number.
     * @param d Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    InitialCondition *createInitialCondition(const char *name, int num, Domain *d);
    /**
     * Creates new instance of topology description corresponding to given keyword.
     * @param name Keyword string determining the type of new instance.
     * @param domain Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    TopologyDescription *createTopology(const char *name, Domain *domain);
    /**
     * Registers a new topology description in the class factory.
     * @param name Keyword string.
     */
    bool registerTopologyDescription( const char *name, TopologyDescription * ( *creator )( Domain * ) );

    /**
     * Creates new instance of sparse matrix corresponding to given keyword.
     * @param type SparseMtrxType id determining the type of new instance.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    SparseMtrx *createSparseMtrx(SparseMtrxType type);
    /**
     * Registers a sparse matrix type.
     * @param type SparseMtrxType id determining the type of new instance.
     */
    bool registerSparseMtrx( SparseMtrxType type, SparseMtrx * ( * )() );
    /**
     * Creates new instance of DOF corresponding to given keyword.
     * @param type ID determining the type of new instance.
     * @param num  object's number.
     * @param dman Dof manager assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    Dof *createDof(dofType type, int num, DofManager *dman);
    /**
     * Creates new instance of SparseLinearSystemNM corresponding
     * to given type.
     * @param st LinSystSolverType id determining the type of new instance.
     * @param d Domain assigned to new object.
     * @param m EngngModel  assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    SparseLinearSystemNM *createSparseLinSolver(LinSystSolverType st, Domain *d, EngngModel *m);
    /**
     * Registers a sparse linear system solver.
     * @param type LinSystSolverType id determining the type of new instance.
     */
    bool registerSparseLinSolver( LinSystSolverType type, SparseLinearSystemNM * ( * )(Domain *, EngngModel *) );
    /**
     * Creates new instance of ErrorEstimator corresponding
     * to given type.
     * @param type ErrorEstimatorType id determining the type of new instance.
     * @param num  object's number.
     * @param d Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    ErrorEstimator *createErrorEstimator(ErrorEstimatorType type, int num, Domain *d);
    /**
     * Registers a new  error estimator.
     * @param type ErrorEstimatorType id determining the type of new instance.
     */
    bool registerErrorEstimator( ErrorEstimatorType type, ErrorEstimator * ( * )(int, Domain *) );
    /**
     * Creates new instance of nodal recovery model corresponding to given type.
     * @param type ID determining the type of new instance.
     * @param d Domain assigned to new object.
     * @return Newly allocated object of requested type, null if keyword not supported.
     */
    NodalRecoveryModel *createNodalRecoveryModel(NodalRecoveryModel :: NodalRecoveryModelType type, Domain *d);

    // XFEM:
    EnrichmentItem *createEnrichmentItem(const char *name, int num, XfemManager *xm, Domain *domain);
    bool registerEnrichmentItem( const char *name, EnrichmentItem * ( *creator )( int, XfemManager *, Domain * ) );

    EnrichmentFunction *createEnrichmentFunction(const char *name, int num, Domain *domain);
    bool registerEnrichmentFunction( const char *name, EnrichmentFunction * ( *creator )( int, Domain * ) );

    EnrichmentDomain *createEnrichmentDomain(const char *name);
    bool registerEnrichmentDomain( const char *name, EnrichmentDomain * ( *creator )( ) );

    EnrichmentFront *createEnrichmentFront(const char *name);
    bool registerEnrichmentFront( const char *name, EnrichmentFront * ( *creator )( ) );

    PropagationLaw *createPropagationLaw(const char *name);
    bool registerPropagationLaw( const char *name, PropagationLaw * ( *creator )( ) );

    BasicGeometry *createGeometry(const char *name);
    bool registerGeometry( const char *name, BasicGeometry * ( *creator )( ) );


    // Failure module (in development!)
    FailureCriteria *createFailureCriteria(const char *name, int num, FractureManager *fracManager);
    bool registerFailureCriteria( const char *name, FailureCriteria * ( *creator )( int, FractureManager * ) );

    FailureCriteriaStatus *createFailureCriteriaStatus(const char *name, int num, FailureCriteria *critManager);
    bool registerFailureCriteriaStatus( const char *name, FailureCriteriaStatus * ( *creator )( int, FailureCriteria * ) );


    SparseGeneralEigenValueSystemNM *createGeneralizedEigenValueSolver(GenEigvalSolverType st, Domain *d, EngngModel *m);
    IntegrationRule *createIRule(IntegrationRuleType type, int number, ElementGeometry *e);
    MaterialMappingAlgorithm *createMaterialMappingAlgorithm(MaterialMappingAlgorithmType type);
    MesherInterface *createMesherInterface(MeshPackageType type, Domain *d);

#ifdef __PARALLEL_MODE
    LoadBalancerMonitor *createLoadBalancerMonitor(const char *name, EngngModel *e);
    LoadBalancer *createLoadBalancer(const char *name, Domain *d);
#endif
};

extern ClassFactory &classFactory;

/**
 * This function must be used by all code that run at link time to ensure that the classFactory is constructed first.
 * See "static initialization order fiasco" for explanation.
 */
ClassFactory &GiveClassFactory();
} // end namespace oofem
#endif // clasfactort_h
