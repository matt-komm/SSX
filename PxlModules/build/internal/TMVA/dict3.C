// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedImatthiasdIAnalysisdISSX13dISSXdIPxlModulesdIbuilddIinternaldITMVAdIdict3

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "inc/TMVA/Config.h"
#include "inc/TMVA/KDEKernel.h"
#include "inc/TMVA/Interval.h"
#include "inc/TMVA/LogInterval.h"
#include "inc/TMVA/FitterBase.h"
#include "inc/TMVA/MCFitter.h"
#include "inc/TMVA/GeneticFitter.h"
#include "inc/TMVA/SimulatedAnnealingFitter.h"
#include "inc/TMVA/MinuitFitter.h"
#include "inc/TMVA/MinuitWrapper.h"
#include "inc/TMVA/IFitterTarget.h"
#include "inc/TMVA/PDEFoam.h"
#include "inc/TMVA/PDEFoamDecisionTree.h"
#include "inc/TMVA/PDEFoamDensityBase.h"
#include "inc/TMVA/PDEFoamDiscriminantDensity.h"
#include "inc/TMVA/PDEFoamEventDensity.h"
#include "inc/TMVA/PDEFoamTargetDensity.h"
#include "inc/TMVA/PDEFoamDecisionTreeDensity.h"
#include "inc/TMVA/PDEFoamMultiTarget.h"
#include "inc/TMVA/PDEFoamVect.h"
#include "inc/TMVA/PDEFoamCell.h"
#include "inc/TMVA/PDEFoamDiscriminant.h"
#include "inc/TMVA/PDEFoamEvent.h"
#include "inc/TMVA/PDEFoamTarget.h"
#include "inc/TMVA/PDEFoamKernelBase.h"
#include "inc/TMVA/PDEFoamKernelTrivial.h"
#include "inc/TMVA/PDEFoamKernelLinN.h"
#include "inc/TMVA/PDEFoamKernelGauss.h"
#include "inc/TMVA/BDTEventWrapper.h"
#include "inc/TMVA/CCTreeWrapper.h"
#include "inc/TMVA/CCPruner.h"
#include "inc/TMVA/CostComplexityPruneTool.h"
#include "inc/TMVA/SVEvent.h"
#include "inc/TMVA/OptimizeConfigParameters.h"

// Header files passed via #pragma extra_include

namespace TMVA {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *TMVA_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("TMVA", 0 /*version*/, "inc/TMVA/Config.h", 47,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &TMVA_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *TMVA_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Config*)
   {
      ::TMVA::Config *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Config >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Config", ::TMVA::Config::Class_Version(), "inc/TMVA/Config.h", 51,
                  typeid(::TMVA::Config), DefineBehavior(ptr, ptr),
                  &::TMVA::Config::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Config) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Config*)
   {
      return GenerateInitInstanceLocal((::TMVA::Config*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Config*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLConfigcLcLVariablePlotting_Dictionary();
   static void TMVAcLcLConfigcLcLVariablePlotting_TClassManip(TClass*);
   static void *new_TMVAcLcLConfigcLcLVariablePlotting(void *p = 0);
   static void *newArray_TMVAcLcLConfigcLcLVariablePlotting(Long_t size, void *p);
   static void delete_TMVAcLcLConfigcLcLVariablePlotting(void *p);
   static void deleteArray_TMVAcLcLConfigcLcLVariablePlotting(void *p);
   static void destruct_TMVAcLcLConfigcLcLVariablePlotting(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Config::VariablePlotting*)
   {
      ::TMVA::Config::VariablePlotting *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::Config::VariablePlotting));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Config::VariablePlotting", "inc/TMVA/Config.h", 79,
                  typeid(::TMVA::Config::VariablePlotting), DefineBehavior(ptr, ptr),
                  &TMVAcLcLConfigcLcLVariablePlotting_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Config::VariablePlotting) );
      instance.SetNew(&new_TMVAcLcLConfigcLcLVariablePlotting);
      instance.SetNewArray(&newArray_TMVAcLcLConfigcLcLVariablePlotting);
      instance.SetDelete(&delete_TMVAcLcLConfigcLcLVariablePlotting);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLConfigcLcLVariablePlotting);
      instance.SetDestructor(&destruct_TMVAcLcLConfigcLcLVariablePlotting);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Config::VariablePlotting*)
   {
      return GenerateInitInstanceLocal((::TMVA::Config::VariablePlotting*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Config::VariablePlotting*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLConfigcLcLVariablePlotting_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::Config::VariablePlotting*)0x0)->GetClass();
      TMVAcLcLConfigcLcLVariablePlotting_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLConfigcLcLVariablePlotting_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLConfigcLcLIONames_Dictionary();
   static void TMVAcLcLConfigcLcLIONames_TClassManip(TClass*);
   static void *new_TMVAcLcLConfigcLcLIONames(void *p = 0);
   static void *newArray_TMVAcLcLConfigcLcLIONames(Long_t size, void *p);
   static void delete_TMVAcLcLConfigcLcLIONames(void *p);
   static void deleteArray_TMVAcLcLConfigcLcLIONames(void *p);
   static void destruct_TMVAcLcLConfigcLcLIONames(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Config::IONames*)
   {
      ::TMVA::Config::IONames *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::Config::IONames));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Config::IONames", "inc/TMVA/Config.h", 92,
                  typeid(::TMVA::Config::IONames), DefineBehavior(ptr, ptr),
                  &TMVAcLcLConfigcLcLIONames_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Config::IONames) );
      instance.SetNew(&new_TMVAcLcLConfigcLcLIONames);
      instance.SetNewArray(&newArray_TMVAcLcLConfigcLcLIONames);
      instance.SetDelete(&delete_TMVAcLcLConfigcLcLIONames);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLConfigcLcLIONames);
      instance.SetDestructor(&destruct_TMVAcLcLConfigcLcLIONames);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Config::IONames*)
   {
      return GenerateInitInstanceLocal((::TMVA::Config::IONames*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Config::IONames*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLConfigcLcLIONames_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::Config::IONames*)0x0)->GetClass();
      TMVAcLcLConfigcLcLIONames_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLConfigcLcLIONames_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLKDEKernel(void *p = 0);
   static void *newArray_TMVAcLcLKDEKernel(Long_t size, void *p);
   static void delete_TMVAcLcLKDEKernel(void *p);
   static void deleteArray_TMVAcLcLKDEKernel(void *p);
   static void destruct_TMVAcLcLKDEKernel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::KDEKernel*)
   {
      ::TMVA::KDEKernel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::KDEKernel >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::KDEKernel", ::TMVA::KDEKernel::Class_Version(), "inc/TMVA/KDEKernel.h", 48,
                  typeid(::TMVA::KDEKernel), DefineBehavior(ptr, ptr),
                  &::TMVA::KDEKernel::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::KDEKernel) );
      instance.SetNew(&new_TMVAcLcLKDEKernel);
      instance.SetNewArray(&newArray_TMVAcLcLKDEKernel);
      instance.SetDelete(&delete_TMVAcLcLKDEKernel);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLKDEKernel);
      instance.SetDestructor(&destruct_TMVAcLcLKDEKernel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::KDEKernel*)
   {
      return GenerateInitInstanceLocal((::TMVA::KDEKernel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::KDEKernel*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLInterval(void *p);
   static void deleteArray_TMVAcLcLInterval(void *p);
   static void destruct_TMVAcLcLInterval(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Interval*)
   {
      ::TMVA::Interval *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Interval >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Interval", ::TMVA::Interval::Class_Version(), "inc/TMVA/Interval.h", 63,
                  typeid(::TMVA::Interval), DefineBehavior(ptr, ptr),
                  &::TMVA::Interval::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Interval) );
      instance.SetDelete(&delete_TMVAcLcLInterval);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLInterval);
      instance.SetDestructor(&destruct_TMVAcLcLInterval);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Interval*)
   {
      return GenerateInitInstanceLocal((::TMVA::Interval*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Interval*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLLogInterval(void *p);
   static void deleteArray_TMVAcLcLLogInterval(void *p);
   static void destruct_TMVAcLcLLogInterval(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::LogInterval*)
   {
      ::TMVA::LogInterval *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::LogInterval >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::LogInterval", ::TMVA::LogInterval::Class_Version(), "inc/TMVA/LogInterval.h", 87,
                  typeid(::TMVA::LogInterval), DefineBehavior(ptr, ptr),
                  &::TMVA::LogInterval::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::LogInterval) );
      instance.SetDelete(&delete_TMVAcLcLLogInterval);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLLogInterval);
      instance.SetDestructor(&destruct_TMVAcLcLLogInterval);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::LogInterval*)
   {
      return GenerateInitInstanceLocal((::TMVA::LogInterval*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::LogInterval*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLFitterBase(void *p);
   static void deleteArray_TMVAcLcLFitterBase(void *p);
   static void destruct_TMVAcLcLFitterBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::FitterBase*)
   {
      ::TMVA::FitterBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::FitterBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::FitterBase", ::TMVA::FitterBase::Class_Version(), "inc/TMVA/FitterBase.h", 57,
                  typeid(::TMVA::FitterBase), DefineBehavior(ptr, ptr),
                  &::TMVA::FitterBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::FitterBase) );
      instance.SetDelete(&delete_TMVAcLcLFitterBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLFitterBase);
      instance.SetDestructor(&destruct_TMVAcLcLFitterBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::FitterBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::FitterBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::FitterBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMCFitter(void *p);
   static void deleteArray_TMVAcLcLMCFitter(void *p);
   static void destruct_TMVAcLcLMCFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MCFitter*)
   {
      ::TMVA::MCFitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MCFitter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MCFitter", ::TMVA::MCFitter::Class_Version(), "inc/TMVA/MCFitter.h", 45,
                  typeid(::TMVA::MCFitter), DefineBehavior(ptr, ptr),
                  &::TMVA::MCFitter::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MCFitter) );
      instance.SetDelete(&delete_TMVAcLcLMCFitter);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMCFitter);
      instance.SetDestructor(&destruct_TMVAcLcLMCFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MCFitter*)
   {
      return GenerateInitInstanceLocal((::TMVA::MCFitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MCFitter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLGeneticFitter(void *p);
   static void deleteArray_TMVAcLcLGeneticFitter(void *p);
   static void destruct_TMVAcLcLGeneticFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GeneticFitter*)
   {
      ::TMVA::GeneticFitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GeneticFitter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GeneticFitter", ::TMVA::GeneticFitter::Class_Version(), "inc/TMVA/GeneticFitter.h", 45,
                  typeid(::TMVA::GeneticFitter), DefineBehavior(ptr, ptr),
                  &::TMVA::GeneticFitter::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GeneticFitter) );
      instance.SetDelete(&delete_TMVAcLcLGeneticFitter);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGeneticFitter);
      instance.SetDestructor(&destruct_TMVAcLcLGeneticFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GeneticFitter*)
   {
      return GenerateInitInstanceLocal((::TMVA::GeneticFitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GeneticFitter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLSimulatedAnnealingFitter(void *p);
   static void deleteArray_TMVAcLcLSimulatedAnnealingFitter(void *p);
   static void destruct_TMVAcLcLSimulatedAnnealingFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::SimulatedAnnealingFitter*)
   {
      ::TMVA::SimulatedAnnealingFitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::SimulatedAnnealingFitter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::SimulatedAnnealingFitter", ::TMVA::SimulatedAnnealingFitter::Class_Version(), "inc/TMVA/SimulatedAnnealingFitter.h", 49,
                  typeid(::TMVA::SimulatedAnnealingFitter), DefineBehavior(ptr, ptr),
                  &::TMVA::SimulatedAnnealingFitter::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::SimulatedAnnealingFitter) );
      instance.SetDelete(&delete_TMVAcLcLSimulatedAnnealingFitter);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLSimulatedAnnealingFitter);
      instance.SetDestructor(&destruct_TMVAcLcLSimulatedAnnealingFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::SimulatedAnnealingFitter*)
   {
      return GenerateInitInstanceLocal((::TMVA::SimulatedAnnealingFitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealingFitter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMinuitFitter(void *p);
   static void deleteArray_TMVAcLcLMinuitFitter(void *p);
   static void destruct_TMVAcLcLMinuitFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MinuitFitter*)
   {
      ::TMVA::MinuitFitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MinuitFitter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MinuitFitter", ::TMVA::MinuitFitter::Class_Version(), "inc/TMVA/MinuitFitter.h", 51,
                  typeid(::TMVA::MinuitFitter), DefineBehavior(ptr, ptr),
                  &::TMVA::MinuitFitter::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MinuitFitter) );
      instance.SetDelete(&delete_TMVAcLcLMinuitFitter);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMinuitFitter);
      instance.SetDestructor(&destruct_TMVAcLcLMinuitFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MinuitFitter*)
   {
      return GenerateInitInstanceLocal((::TMVA::MinuitFitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MinuitFitter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMinuitWrapper(void *p);
   static void deleteArray_TMVAcLcLMinuitWrapper(void *p);
   static void destruct_TMVAcLcLMinuitWrapper(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MinuitWrapper*)
   {
      ::TMVA::MinuitWrapper *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MinuitWrapper >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MinuitWrapper", ::TMVA::MinuitWrapper::Class_Version(), "inc/TMVA/MinuitWrapper.h", 49,
                  typeid(::TMVA::MinuitWrapper), DefineBehavior(ptr, ptr),
                  &::TMVA::MinuitWrapper::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MinuitWrapper) );
      instance.SetDelete(&delete_TMVAcLcLMinuitWrapper);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMinuitWrapper);
      instance.SetDestructor(&destruct_TMVAcLcLMinuitWrapper);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MinuitWrapper*)
   {
      return GenerateInitInstanceLocal((::TMVA::MinuitWrapper*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MinuitWrapper*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLIFitterTarget(void *p);
   static void deleteArray_TMVAcLcLIFitterTarget(void *p);
   static void destruct_TMVAcLcLIFitterTarget(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::IFitterTarget*)
   {
      ::TMVA::IFitterTarget *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::IFitterTarget >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::IFitterTarget", ::TMVA::IFitterTarget::Class_Version(), "TMVA/IFitterTarget.h", 46,
                  typeid(::TMVA::IFitterTarget), DefineBehavior(ptr, ptr),
                  &::TMVA::IFitterTarget::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::IFitterTarget) );
      instance.SetDelete(&delete_TMVAcLcLIFitterTarget);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLIFitterTarget);
      instance.SetDestructor(&destruct_TMVAcLcLIFitterTarget);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::IFitterTarget*)
   {
      return GenerateInitInstanceLocal((::TMVA::IFitterTarget*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::IFitterTarget*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoam(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoam(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoam(void *p);
   static void deleteArray_TMVAcLcLPDEFoam(void *p);
   static void destruct_TMVAcLcLPDEFoam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoam*)
   {
      ::TMVA::PDEFoam *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoam >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoam", ::TMVA::PDEFoam::Class_Version(), "inc/TMVA/PDEFoam.h", 104,
                  typeid(::TMVA::PDEFoam), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoam::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoam) );
      instance.SetNew(&new_TMVAcLcLPDEFoam);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoam);
      instance.SetDelete(&delete_TMVAcLcLPDEFoam);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoam);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoam*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoam*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoam*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamEvent(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamEvent(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamEvent(void *p);
   static void deleteArray_TMVAcLcLPDEFoamEvent(void *p);
   static void destruct_TMVAcLcLPDEFoamEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamEvent*)
   {
      ::TMVA::PDEFoamEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamEvent", ::TMVA::PDEFoamEvent::Class_Version(), "TMVA/PDEFoamEvent.h", 40,
                  typeid(::TMVA::PDEFoamEvent), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamEvent) );
      instance.SetNew(&new_TMVAcLcLPDEFoamEvent);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamEvent);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamEvent);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamEvent);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamEvent*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamDiscriminant(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamDiscriminant(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamDiscriminant(void *p);
   static void deleteArray_TMVAcLcLPDEFoamDiscriminant(void *p);
   static void destruct_TMVAcLcLPDEFoamDiscriminant(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamDiscriminant*)
   {
      ::TMVA::PDEFoamDiscriminant *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamDiscriminant >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamDiscriminant", ::TMVA::PDEFoamDiscriminant::Class_Version(), "TMVA/PDEFoamDiscriminant.h", 40,
                  typeid(::TMVA::PDEFoamDiscriminant), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamDiscriminant::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamDiscriminant) );
      instance.SetNew(&new_TMVAcLcLPDEFoamDiscriminant);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamDiscriminant);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamDiscriminant);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamDiscriminant);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamDiscriminant);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamDiscriminant*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamDiscriminant*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminant*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamTarget(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamTarget(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamTarget(void *p);
   static void deleteArray_TMVAcLcLPDEFoamTarget(void *p);
   static void destruct_TMVAcLcLPDEFoamTarget(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamTarget*)
   {
      ::TMVA::PDEFoamTarget *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamTarget >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamTarget", ::TMVA::PDEFoamTarget::Class_Version(), "inc/TMVA/PDEFoamTarget.h", 40,
                  typeid(::TMVA::PDEFoamTarget), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamTarget::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamTarget) );
      instance.SetNew(&new_TMVAcLcLPDEFoamTarget);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamTarget);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamTarget);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamTarget);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamTarget);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamTarget*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamTarget*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamTarget*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamMultiTarget(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamMultiTarget(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamMultiTarget(void *p);
   static void deleteArray_TMVAcLcLPDEFoamMultiTarget(void *p);
   static void destruct_TMVAcLcLPDEFoamMultiTarget(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamMultiTarget*)
   {
      ::TMVA::PDEFoamMultiTarget *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamMultiTarget >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamMultiTarget", ::TMVA::PDEFoamMultiTarget::Class_Version(), "inc/TMVA/PDEFoamMultiTarget.h", 45,
                  typeid(::TMVA::PDEFoamMultiTarget), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamMultiTarget::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamMultiTarget) );
      instance.SetNew(&new_TMVAcLcLPDEFoamMultiTarget);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamMultiTarget);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamMultiTarget);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamMultiTarget);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamMultiTarget);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamMultiTarget*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamMultiTarget*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamMultiTarget*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamDecisionTree(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamDecisionTree(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamDecisionTree(void *p);
   static void deleteArray_TMVAcLcLPDEFoamDecisionTree(void *p);
   static void destruct_TMVAcLcLPDEFoamDecisionTree(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamDecisionTree*)
   {
      ::TMVA::PDEFoamDecisionTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamDecisionTree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamDecisionTree", ::TMVA::PDEFoamDecisionTree::Class_Version(), "inc/TMVA/PDEFoamDecisionTree.h", 43,
                  typeid(::TMVA::PDEFoamDecisionTree), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamDecisionTree::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamDecisionTree) );
      instance.SetNew(&new_TMVAcLcLPDEFoamDecisionTree);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamDecisionTree);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamDecisionTree);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamDecisionTree);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamDecisionTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamDecisionTree*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamDecisionTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTree*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLPDEFoamDensityBase(void *p);
   static void deleteArray_TMVAcLcLPDEFoamDensityBase(void *p);
   static void destruct_TMVAcLcLPDEFoamDensityBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamDensityBase*)
   {
      ::TMVA::PDEFoamDensityBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamDensityBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamDensityBase", ::TMVA::PDEFoamDensityBase::Class_Version(), "TMVA/PDEFoamDensityBase.h", 53,
                  typeid(::TMVA::PDEFoamDensityBase), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamDensityBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamDensityBase) );
      instance.SetDelete(&delete_TMVAcLcLPDEFoamDensityBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamDensityBase);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamDensityBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamDensityBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamDensityBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamDensityBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamDiscriminantDensity(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamDiscriminantDensity(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamDiscriminantDensity(void *p);
   static void deleteArray_TMVAcLcLPDEFoamDiscriminantDensity(void *p);
   static void destruct_TMVAcLcLPDEFoamDiscriminantDensity(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamDiscriminantDensity*)
   {
      ::TMVA::PDEFoamDiscriminantDensity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamDiscriminantDensity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamDiscriminantDensity", ::TMVA::PDEFoamDiscriminantDensity::Class_Version(), "inc/TMVA/PDEFoamDiscriminantDensity.h", 43,
                  typeid(::TMVA::PDEFoamDiscriminantDensity), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamDiscriminantDensity::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamDiscriminantDensity) );
      instance.SetNew(&new_TMVAcLcLPDEFoamDiscriminantDensity);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamDiscriminantDensity);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamDiscriminantDensity);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamDiscriminantDensity);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamDiscriminantDensity);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamDiscriminantDensity*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamDiscriminantDensity*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminantDensity*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamEventDensity(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamEventDensity(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamEventDensity(void *p);
   static void deleteArray_TMVAcLcLPDEFoamEventDensity(void *p);
   static void destruct_TMVAcLcLPDEFoamEventDensity(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamEventDensity*)
   {
      ::TMVA::PDEFoamEventDensity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamEventDensity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamEventDensity", ::TMVA::PDEFoamEventDensity::Class_Version(), "inc/TMVA/PDEFoamEventDensity.h", 43,
                  typeid(::TMVA::PDEFoamEventDensity), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamEventDensity::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamEventDensity) );
      instance.SetNew(&new_TMVAcLcLPDEFoamEventDensity);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamEventDensity);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamEventDensity);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamEventDensity);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamEventDensity);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamEventDensity*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamEventDensity*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamEventDensity*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamTargetDensity(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamTargetDensity(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamTargetDensity(void *p);
   static void deleteArray_TMVAcLcLPDEFoamTargetDensity(void *p);
   static void destruct_TMVAcLcLPDEFoamTargetDensity(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamTargetDensity*)
   {
      ::TMVA::PDEFoamTargetDensity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamTargetDensity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamTargetDensity", ::TMVA::PDEFoamTargetDensity::Class_Version(), "inc/TMVA/PDEFoamTargetDensity.h", 43,
                  typeid(::TMVA::PDEFoamTargetDensity), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamTargetDensity::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamTargetDensity) );
      instance.SetNew(&new_TMVAcLcLPDEFoamTargetDensity);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamTargetDensity);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamTargetDensity);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamTargetDensity);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamTargetDensity);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamTargetDensity*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamTargetDensity*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamTargetDensity*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamDecisionTreeDensity(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamDecisionTreeDensity(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamDecisionTreeDensity(void *p);
   static void deleteArray_TMVAcLcLPDEFoamDecisionTreeDensity(void *p);
   static void destruct_TMVAcLcLPDEFoamDecisionTreeDensity(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamDecisionTreeDensity*)
   {
      ::TMVA::PDEFoamDecisionTreeDensity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamDecisionTreeDensity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamDecisionTreeDensity", ::TMVA::PDEFoamDecisionTreeDensity::Class_Version(), "inc/TMVA/PDEFoamDecisionTreeDensity.h", 52,
                  typeid(::TMVA::PDEFoamDecisionTreeDensity), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamDecisionTreeDensity::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamDecisionTreeDensity) );
      instance.SetNew(&new_TMVAcLcLPDEFoamDecisionTreeDensity);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamDecisionTreeDensity);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamDecisionTreeDensity);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamDecisionTreeDensity);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamDecisionTreeDensity);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamDecisionTreeDensity*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamDecisionTreeDensity*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTreeDensity*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamVect(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamVect(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamVect(void *p);
   static void deleteArray_TMVAcLcLPDEFoamVect(void *p);
   static void destruct_TMVAcLcLPDEFoamVect(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamVect*)
   {
      ::TMVA::PDEFoamVect *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamVect >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamVect", ::TMVA::PDEFoamVect::Class_Version(), "TMVA/PDEFoamVect.h", 38,
                  typeid(::TMVA::PDEFoamVect), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamVect::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamVect) );
      instance.SetNew(&new_TMVAcLcLPDEFoamVect);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamVect);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamVect);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamVect);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamVect);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamVect*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamVect*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamVect*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamCell(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamCell(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamCell(void *p);
   static void deleteArray_TMVAcLcLPDEFoamCell(void *p);
   static void destruct_TMVAcLcLPDEFoamCell(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamCell*)
   {
      ::TMVA::PDEFoamCell *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamCell >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamCell", ::TMVA::PDEFoamCell::Class_Version(), "TMVA/PDEFoamCell.h", 47,
                  typeid(::TMVA::PDEFoamCell), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamCell::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamCell) );
      instance.SetNew(&new_TMVAcLcLPDEFoamCell);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamCell);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamCell);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamCell);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamCell);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamCell*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamCell*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamCell*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLPDEFoamKernelBase(void *p);
   static void deleteArray_TMVAcLcLPDEFoamKernelBase(void *p);
   static void destruct_TMVAcLcLPDEFoamKernelBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamKernelBase*)
   {
      ::TMVA::PDEFoamKernelBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamKernelBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamKernelBase", ::TMVA::PDEFoamKernelBase::Class_Version(), "TMVA/PDEFoamKernelBase.h", 42,
                  typeid(::TMVA::PDEFoamKernelBase), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamKernelBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamKernelBase) );
      instance.SetDelete(&delete_TMVAcLcLPDEFoamKernelBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamKernelBase);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamKernelBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamKernelBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamKernelBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamKernelTrivial(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamKernelTrivial(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamKernelTrivial(void *p);
   static void deleteArray_TMVAcLcLPDEFoamKernelTrivial(void *p);
   static void destruct_TMVAcLcLPDEFoamKernelTrivial(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamKernelTrivial*)
   {
      ::TMVA::PDEFoamKernelTrivial *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamKernelTrivial >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamKernelTrivial", ::TMVA::PDEFoamKernelTrivial::Class_Version(), "inc/TMVA/PDEFoamKernelTrivial.h", 41,
                  typeid(::TMVA::PDEFoamKernelTrivial), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamKernelTrivial::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamKernelTrivial) );
      instance.SetNew(&new_TMVAcLcLPDEFoamKernelTrivial);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamKernelTrivial);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamKernelTrivial);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamKernelTrivial);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamKernelTrivial);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamKernelTrivial*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamKernelTrivial*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelTrivial*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLPDEFoamKernelLinN(void *p = 0);
   static void *newArray_TMVAcLcLPDEFoamKernelLinN(Long_t size, void *p);
   static void delete_TMVAcLcLPDEFoamKernelLinN(void *p);
   static void deleteArray_TMVAcLcLPDEFoamKernelLinN(void *p);
   static void destruct_TMVAcLcLPDEFoamKernelLinN(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamKernelLinN*)
   {
      ::TMVA::PDEFoamKernelLinN *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamKernelLinN >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamKernelLinN", ::TMVA::PDEFoamKernelLinN::Class_Version(), "inc/TMVA/PDEFoamKernelLinN.h", 41,
                  typeid(::TMVA::PDEFoamKernelLinN), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamKernelLinN::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamKernelLinN) );
      instance.SetNew(&new_TMVAcLcLPDEFoamKernelLinN);
      instance.SetNewArray(&newArray_TMVAcLcLPDEFoamKernelLinN);
      instance.SetDelete(&delete_TMVAcLcLPDEFoamKernelLinN);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamKernelLinN);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamKernelLinN);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamKernelLinN*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamKernelLinN*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelLinN*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLPDEFoamKernelGauss(void *p);
   static void deleteArray_TMVAcLcLPDEFoamKernelGauss(void *p);
   static void destruct_TMVAcLcLPDEFoamKernelGauss(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDEFoamKernelGauss*)
   {
      ::TMVA::PDEFoamKernelGauss *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDEFoamKernelGauss >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDEFoamKernelGauss", ::TMVA::PDEFoamKernelGauss::Class_Version(), "inc/TMVA/PDEFoamKernelGauss.h", 41,
                  typeid(::TMVA::PDEFoamKernelGauss), DefineBehavior(ptr, ptr),
                  &::TMVA::PDEFoamKernelGauss::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDEFoamKernelGauss) );
      instance.SetDelete(&delete_TMVAcLcLPDEFoamKernelGauss);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDEFoamKernelGauss);
      instance.SetDestructor(&destruct_TMVAcLcLPDEFoamKernelGauss);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDEFoamKernelGauss*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDEFoamKernelGauss*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelGauss*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLBDTEventWrapper_Dictionary();
   static void TMVAcLcLBDTEventWrapper_TClassManip(TClass*);
   static void delete_TMVAcLcLBDTEventWrapper(void *p);
   static void deleteArray_TMVAcLcLBDTEventWrapper(void *p);
   static void destruct_TMVAcLcLBDTEventWrapper(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::BDTEventWrapper*)
   {
      ::TMVA::BDTEventWrapper *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::BDTEventWrapper));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::BDTEventWrapper", "inc/TMVA/BDTEventWrapper.h", 31,
                  typeid(::TMVA::BDTEventWrapper), DefineBehavior(ptr, ptr),
                  &TMVAcLcLBDTEventWrapper_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::BDTEventWrapper) );
      instance.SetDelete(&delete_TMVAcLcLBDTEventWrapper);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLBDTEventWrapper);
      instance.SetDestructor(&destruct_TMVAcLcLBDTEventWrapper);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::BDTEventWrapper*)
   {
      return GenerateInitInstanceLocal((::TMVA::BDTEventWrapper*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::BDTEventWrapper*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLBDTEventWrapper_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::BDTEventWrapper*)0x0)->GetClass();
      TMVAcLcLBDTEventWrapper_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLBDTEventWrapper_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLCCTreeWrapper_Dictionary();
   static void TMVAcLcLCCTreeWrapper_TClassManip(TClass*);
   static void delete_TMVAcLcLCCTreeWrapper(void *p);
   static void deleteArray_TMVAcLcLCCTreeWrapper(void *p);
   static void destruct_TMVAcLcLCCTreeWrapper(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::CCTreeWrapper*)
   {
      ::TMVA::CCTreeWrapper *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::CCTreeWrapper));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::CCTreeWrapper", "inc/TMVA/CCTreeWrapper.h", 46,
                  typeid(::TMVA::CCTreeWrapper), DefineBehavior(ptr, ptr),
                  &TMVAcLcLCCTreeWrapper_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::CCTreeWrapper) );
      instance.SetDelete(&delete_TMVAcLcLCCTreeWrapper);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLCCTreeWrapper);
      instance.SetDestructor(&destruct_TMVAcLcLCCTreeWrapper);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::CCTreeWrapper*)
   {
      return GenerateInitInstanceLocal((::TMVA::CCTreeWrapper*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::CCTreeWrapper*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLCCTreeWrapper_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::CCTreeWrapper*)0x0)->GetClass();
      TMVAcLcLCCTreeWrapper_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLCCTreeWrapper_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLCCPruner_Dictionary();
   static void TMVAcLcLCCPruner_TClassManip(TClass*);
   static void delete_TMVAcLcLCCPruner(void *p);
   static void deleteArray_TMVAcLcLCCPruner(void *p);
   static void destruct_TMVAcLcLCCPruner(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::CCPruner*)
   {
      ::TMVA::CCPruner *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::CCPruner));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::CCPruner", "inc/TMVA/CCPruner.h", 65,
                  typeid(::TMVA::CCPruner), DefineBehavior(ptr, ptr),
                  &TMVAcLcLCCPruner_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::CCPruner) );
      instance.SetDelete(&delete_TMVAcLcLCCPruner);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLCCPruner);
      instance.SetDestructor(&destruct_TMVAcLcLCCPruner);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::CCPruner*)
   {
      return GenerateInitInstanceLocal((::TMVA::CCPruner*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::CCPruner*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLCCPruner_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::CCPruner*)0x0)->GetClass();
      TMVAcLcLCCPruner_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLCCPruner_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLCostComplexityPruneTool_Dictionary();
   static void TMVAcLcLCostComplexityPruneTool_TClassManip(TClass*);
   static void *new_TMVAcLcLCostComplexityPruneTool(void *p = 0);
   static void *newArray_TMVAcLcLCostComplexityPruneTool(Long_t size, void *p);
   static void delete_TMVAcLcLCostComplexityPruneTool(void *p);
   static void deleteArray_TMVAcLcLCostComplexityPruneTool(void *p);
   static void destruct_TMVAcLcLCostComplexityPruneTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::CostComplexityPruneTool*)
   {
      ::TMVA::CostComplexityPruneTool *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::CostComplexityPruneTool));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::CostComplexityPruneTool", "inc/TMVA/CostComplexityPruneTool.h", 71,
                  typeid(::TMVA::CostComplexityPruneTool), DefineBehavior(ptr, ptr),
                  &TMVAcLcLCostComplexityPruneTool_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::CostComplexityPruneTool) );
      instance.SetNew(&new_TMVAcLcLCostComplexityPruneTool);
      instance.SetNewArray(&newArray_TMVAcLcLCostComplexityPruneTool);
      instance.SetDelete(&delete_TMVAcLcLCostComplexityPruneTool);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLCostComplexityPruneTool);
      instance.SetDestructor(&destruct_TMVAcLcLCostComplexityPruneTool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::CostComplexityPruneTool*)
   {
      return GenerateInitInstanceLocal((::TMVA::CostComplexityPruneTool*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::CostComplexityPruneTool*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLCostComplexityPruneTool_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::CostComplexityPruneTool*)0x0)->GetClass();
      TMVAcLcLCostComplexityPruneTool_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLCostComplexityPruneTool_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLSVEvent(void *p = 0);
   static void *newArray_TMVAcLcLSVEvent(Long_t size, void *p);
   static void delete_TMVAcLcLSVEvent(void *p);
   static void deleteArray_TMVAcLcLSVEvent(void *p);
   static void destruct_TMVAcLcLSVEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::SVEvent*)
   {
      ::TMVA::SVEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::SVEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::SVEvent", ::TMVA::SVEvent::Class_Version(), "inc/TMVA/SVEvent.h", 42,
                  typeid(::TMVA::SVEvent), DefineBehavior(ptr, ptr),
                  &::TMVA::SVEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::SVEvent) );
      instance.SetNew(&new_TMVAcLcLSVEvent);
      instance.SetNewArray(&newArray_TMVAcLcLSVEvent);
      instance.SetDelete(&delete_TMVAcLcLSVEvent);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLSVEvent);
      instance.SetDestructor(&destruct_TMVAcLcLSVEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::SVEvent*)
   {
      return GenerateInitInstanceLocal((::TMVA::SVEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::SVEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLOptimizeConfigParameters(void *p);
   static void deleteArray_TMVAcLcLOptimizeConfigParameters(void *p);
   static void destruct_TMVAcLcLOptimizeConfigParameters(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::OptimizeConfigParameters*)
   {
      ::TMVA::OptimizeConfigParameters *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::OptimizeConfigParameters >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::OptimizeConfigParameters", ::TMVA::OptimizeConfigParameters::Class_Version(), "inc/TMVA/OptimizeConfigParameters.h", 63,
                  typeid(::TMVA::OptimizeConfigParameters), DefineBehavior(ptr, ptr),
                  &::TMVA::OptimizeConfigParameters::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::OptimizeConfigParameters) );
      instance.SetDelete(&delete_TMVAcLcLOptimizeConfigParameters);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLOptimizeConfigParameters);
      instance.SetDestructor(&destruct_TMVAcLcLOptimizeConfigParameters);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::OptimizeConfigParameters*)
   {
      return GenerateInitInstanceLocal((::TMVA::OptimizeConfigParameters*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::OptimizeConfigParameters*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Config::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Config::Class_Name()
{
   return "TMVA::Config";
}

//______________________________________________________________________________
const char *Config::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Config*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Config::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Config*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Config::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Config*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Config::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Config*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr KDEKernel::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KDEKernel::Class_Name()
{
   return "TMVA::KDEKernel";
}

//______________________________________________________________________________
const char *KDEKernel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::KDEKernel*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KDEKernel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::KDEKernel*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KDEKernel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::KDEKernel*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KDEKernel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::KDEKernel*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Interval::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Interval::Class_Name()
{
   return "TMVA::Interval";
}

//______________________________________________________________________________
const char *Interval::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Interval*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Interval::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Interval*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Interval::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Interval*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Interval::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Interval*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr LogInterval::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *LogInterval::Class_Name()
{
   return "TMVA::LogInterval";
}

//______________________________________________________________________________
const char *LogInterval::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::LogInterval*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int LogInterval::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::LogInterval*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *LogInterval::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::LogInterval*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *LogInterval::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::LogInterval*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr FitterBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FitterBase::Class_Name()
{
   return "TMVA::FitterBase";
}

//______________________________________________________________________________
const char *FitterBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::FitterBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FitterBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::FitterBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FitterBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::FitterBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FitterBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::FitterBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MCFitter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MCFitter::Class_Name()
{
   return "TMVA::MCFitter";
}

//______________________________________________________________________________
const char *MCFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MCFitter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MCFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MCFitter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MCFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MCFitter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MCFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MCFitter*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GeneticFitter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GeneticFitter::Class_Name()
{
   return "TMVA::GeneticFitter";
}

//______________________________________________________________________________
const char *GeneticFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticFitter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GeneticFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticFitter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GeneticFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticFitter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GeneticFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticFitter*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr SimulatedAnnealingFitter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SimulatedAnnealingFitter::Class_Name()
{
   return "TMVA::SimulatedAnnealingFitter";
}

//______________________________________________________________________________
const char *SimulatedAnnealingFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealingFitter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SimulatedAnnealingFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealingFitter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SimulatedAnnealingFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealingFitter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SimulatedAnnealingFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealingFitter*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MinuitFitter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MinuitFitter::Class_Name()
{
   return "TMVA::MinuitFitter";
}

//______________________________________________________________________________
const char *MinuitFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitFitter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MinuitFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitFitter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MinuitFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitFitter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MinuitFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitFitter*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MinuitWrapper::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MinuitWrapper::Class_Name()
{
   return "TMVA::MinuitWrapper";
}

//______________________________________________________________________________
const char *MinuitWrapper::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitWrapper*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MinuitWrapper::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitWrapper*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MinuitWrapper::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitWrapper*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MinuitWrapper::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MinuitWrapper*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr IFitterTarget::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *IFitterTarget::Class_Name()
{
   return "TMVA::IFitterTarget";
}

//______________________________________________________________________________
const char *IFitterTarget::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IFitterTarget*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int IFitterTarget::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IFitterTarget*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *IFitterTarget::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IFitterTarget*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *IFitterTarget::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IFitterTarget*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoam::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoam::Class_Name()
{
   return "TMVA::PDEFoam";
}

//______________________________________________________________________________
const char *PDEFoam::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoam*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoam::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoam*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoam::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoam*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoam::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoam*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamEvent::Class_Name()
{
   return "TMVA::PDEFoamEvent";
}

//______________________________________________________________________________
const char *PDEFoamEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEvent*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamDiscriminant::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamDiscriminant::Class_Name()
{
   return "TMVA::PDEFoamDiscriminant";
}

//______________________________________________________________________________
const char *PDEFoamDiscriminant::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminant*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamDiscriminant::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminant*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamDiscriminant::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminant*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamDiscriminant::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminant*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamTarget::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamTarget::Class_Name()
{
   return "TMVA::PDEFoamTarget";
}

//______________________________________________________________________________
const char *PDEFoamTarget::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTarget*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamTarget::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTarget*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamTarget::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTarget*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamTarget::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTarget*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamMultiTarget::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamMultiTarget::Class_Name()
{
   return "TMVA::PDEFoamMultiTarget";
}

//______________________________________________________________________________
const char *PDEFoamMultiTarget::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamMultiTarget*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamMultiTarget::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamMultiTarget*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamMultiTarget::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamMultiTarget*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamMultiTarget::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamMultiTarget*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamDecisionTree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamDecisionTree::Class_Name()
{
   return "TMVA::PDEFoamDecisionTree";
}

//______________________________________________________________________________
const char *PDEFoamDecisionTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamDecisionTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamDecisionTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamDecisionTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTree*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamDensityBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamDensityBase::Class_Name()
{
   return "TMVA::PDEFoamDensityBase";
}

//______________________________________________________________________________
const char *PDEFoamDensityBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDensityBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamDensityBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDensityBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamDensityBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDensityBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamDensityBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDensityBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamDiscriminantDensity::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamDiscriminantDensity::Class_Name()
{
   return "TMVA::PDEFoamDiscriminantDensity";
}

//______________________________________________________________________________
const char *PDEFoamDiscriminantDensity::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminantDensity*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamDiscriminantDensity::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminantDensity*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamDiscriminantDensity::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminantDensity*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamDiscriminantDensity::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDiscriminantDensity*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamEventDensity::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamEventDensity::Class_Name()
{
   return "TMVA::PDEFoamEventDensity";
}

//______________________________________________________________________________
const char *PDEFoamEventDensity::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEventDensity*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamEventDensity::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEventDensity*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamEventDensity::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEventDensity*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamEventDensity::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamEventDensity*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamTargetDensity::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamTargetDensity::Class_Name()
{
   return "TMVA::PDEFoamTargetDensity";
}

//______________________________________________________________________________
const char *PDEFoamTargetDensity::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTargetDensity*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamTargetDensity::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTargetDensity*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamTargetDensity::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTargetDensity*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamTargetDensity::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamTargetDensity*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamDecisionTreeDensity::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamDecisionTreeDensity::Class_Name()
{
   return "TMVA::PDEFoamDecisionTreeDensity";
}

//______________________________________________________________________________
const char *PDEFoamDecisionTreeDensity::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTreeDensity*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamDecisionTreeDensity::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTreeDensity*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamDecisionTreeDensity::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTreeDensity*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamDecisionTreeDensity::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamDecisionTreeDensity*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamVect::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamVect::Class_Name()
{
   return "TMVA::PDEFoamVect";
}

//______________________________________________________________________________
const char *PDEFoamVect::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamVect*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamVect::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamVect*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamVect::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamVect*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamVect::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamVect*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamCell::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamCell::Class_Name()
{
   return "TMVA::PDEFoamCell";
}

//______________________________________________________________________________
const char *PDEFoamCell::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamCell*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamCell::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamCell*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamCell::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamCell*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamCell::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamCell*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamKernelBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamKernelBase::Class_Name()
{
   return "TMVA::PDEFoamKernelBase";
}

//______________________________________________________________________________
const char *PDEFoamKernelBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamKernelBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamKernelBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamKernelBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamKernelTrivial::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamKernelTrivial::Class_Name()
{
   return "TMVA::PDEFoamKernelTrivial";
}

//______________________________________________________________________________
const char *PDEFoamKernelTrivial::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelTrivial*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamKernelTrivial::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelTrivial*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamKernelTrivial::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelTrivial*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamKernelTrivial::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelTrivial*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamKernelLinN::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamKernelLinN::Class_Name()
{
   return "TMVA::PDEFoamKernelLinN";
}

//______________________________________________________________________________
const char *PDEFoamKernelLinN::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelLinN*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamKernelLinN::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelLinN*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamKernelLinN::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelLinN*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamKernelLinN::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelLinN*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDEFoamKernelGauss::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDEFoamKernelGauss::Class_Name()
{
   return "TMVA::PDEFoamKernelGauss";
}

//______________________________________________________________________________
const char *PDEFoamKernelGauss::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelGauss*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDEFoamKernelGauss::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelGauss*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDEFoamKernelGauss::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelGauss*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDEFoamKernelGauss::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDEFoamKernelGauss*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr SVEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SVEvent::Class_Name()
{
   return "TMVA::SVEvent";
}

//______________________________________________________________________________
const char *SVEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SVEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SVEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SVEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SVEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SVEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SVEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SVEvent*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr OptimizeConfigParameters::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OptimizeConfigParameters::Class_Name()
{
   return "TMVA::OptimizeConfigParameters";
}

//______________________________________________________________________________
const char *OptimizeConfigParameters::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::OptimizeConfigParameters*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OptimizeConfigParameters::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::OptimizeConfigParameters*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OptimizeConfigParameters::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::OptimizeConfigParameters*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OptimizeConfigParameters::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::OptimizeConfigParameters*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
void Config::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Config.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Config::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Config::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
} // end of namespace ROOT for class ::TMVA::Config

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLConfigcLcLVariablePlotting(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Config::VariablePlotting : new ::TMVA::Config::VariablePlotting;
   }
   static void *newArray_TMVAcLcLConfigcLcLVariablePlotting(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Config::VariablePlotting[nElements] : new ::TMVA::Config::VariablePlotting[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLConfigcLcLVariablePlotting(void *p) {
      delete ((::TMVA::Config::VariablePlotting*)p);
   }
   static void deleteArray_TMVAcLcLConfigcLcLVariablePlotting(void *p) {
      delete [] ((::TMVA::Config::VariablePlotting*)p);
   }
   static void destruct_TMVAcLcLConfigcLcLVariablePlotting(void *p) {
      typedef ::TMVA::Config::VariablePlotting current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Config::VariablePlotting

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLConfigcLcLIONames(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Config::IONames : new ::TMVA::Config::IONames;
   }
   static void *newArray_TMVAcLcLConfigcLcLIONames(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Config::IONames[nElements] : new ::TMVA::Config::IONames[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLConfigcLcLIONames(void *p) {
      delete ((::TMVA::Config::IONames*)p);
   }
   static void deleteArray_TMVAcLcLConfigcLcLIONames(void *p) {
      delete [] ((::TMVA::Config::IONames*)p);
   }
   static void destruct_TMVAcLcLConfigcLcLIONames(void *p) {
      typedef ::TMVA::Config::IONames current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Config::IONames

namespace TMVA {
//______________________________________________________________________________
void KDEKernel::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::KDEKernel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::KDEKernel::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::KDEKernel::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLKDEKernel(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::KDEKernel : new ::TMVA::KDEKernel;
   }
   static void *newArray_TMVAcLcLKDEKernel(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::KDEKernel[nElements] : new ::TMVA::KDEKernel[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLKDEKernel(void *p) {
      delete ((::TMVA::KDEKernel*)p);
   }
   static void deleteArray_TMVAcLcLKDEKernel(void *p) {
      delete [] ((::TMVA::KDEKernel*)p);
   }
   static void destruct_TMVAcLcLKDEKernel(void *p) {
      typedef ::TMVA::KDEKernel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::KDEKernel

namespace TMVA {
//______________________________________________________________________________
void Interval::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Interval.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Interval::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Interval::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLInterval(void *p) {
      delete ((::TMVA::Interval*)p);
   }
   static void deleteArray_TMVAcLcLInterval(void *p) {
      delete [] ((::TMVA::Interval*)p);
   }
   static void destruct_TMVAcLcLInterval(void *p) {
      typedef ::TMVA::Interval current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Interval

namespace TMVA {
//______________________________________________________________________________
void LogInterval::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::LogInterval.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::LogInterval::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::LogInterval::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLLogInterval(void *p) {
      delete ((::TMVA::LogInterval*)p);
   }
   static void deleteArray_TMVAcLcLLogInterval(void *p) {
      delete [] ((::TMVA::LogInterval*)p);
   }
   static void destruct_TMVAcLcLLogInterval(void *p) {
      typedef ::TMVA::LogInterval current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::LogInterval

namespace TMVA {
//______________________________________________________________________________
void FitterBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::FitterBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::FitterBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::FitterBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLFitterBase(void *p) {
      delete ((::TMVA::FitterBase*)p);
   }
   static void deleteArray_TMVAcLcLFitterBase(void *p) {
      delete [] ((::TMVA::FitterBase*)p);
   }
   static void destruct_TMVAcLcLFitterBase(void *p) {
      typedef ::TMVA::FitterBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::FitterBase

namespace TMVA {
//______________________________________________________________________________
void MCFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MCFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MCFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MCFitter::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMCFitter(void *p) {
      delete ((::TMVA::MCFitter*)p);
   }
   static void deleteArray_TMVAcLcLMCFitter(void *p) {
      delete [] ((::TMVA::MCFitter*)p);
   }
   static void destruct_TMVAcLcLMCFitter(void *p) {
      typedef ::TMVA::MCFitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MCFitter

namespace TMVA {
//______________________________________________________________________________
void GeneticFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GeneticFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GeneticFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GeneticFitter::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLGeneticFitter(void *p) {
      delete ((::TMVA::GeneticFitter*)p);
   }
   static void deleteArray_TMVAcLcLGeneticFitter(void *p) {
      delete [] ((::TMVA::GeneticFitter*)p);
   }
   static void destruct_TMVAcLcLGeneticFitter(void *p) {
      typedef ::TMVA::GeneticFitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GeneticFitter

namespace TMVA {
//______________________________________________________________________________
void SimulatedAnnealingFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::SimulatedAnnealingFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::SimulatedAnnealingFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::SimulatedAnnealingFitter::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLSimulatedAnnealingFitter(void *p) {
      delete ((::TMVA::SimulatedAnnealingFitter*)p);
   }
   static void deleteArray_TMVAcLcLSimulatedAnnealingFitter(void *p) {
      delete [] ((::TMVA::SimulatedAnnealingFitter*)p);
   }
   static void destruct_TMVAcLcLSimulatedAnnealingFitter(void *p) {
      typedef ::TMVA::SimulatedAnnealingFitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::SimulatedAnnealingFitter

namespace TMVA {
//______________________________________________________________________________
void MinuitFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MinuitFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MinuitFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MinuitFitter::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMinuitFitter(void *p) {
      delete ((::TMVA::MinuitFitter*)p);
   }
   static void deleteArray_TMVAcLcLMinuitFitter(void *p) {
      delete [] ((::TMVA::MinuitFitter*)p);
   }
   static void destruct_TMVAcLcLMinuitFitter(void *p) {
      typedef ::TMVA::MinuitFitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MinuitFitter

namespace TMVA {
//______________________________________________________________________________
void MinuitWrapper::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MinuitWrapper.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MinuitWrapper::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MinuitWrapper::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMinuitWrapper(void *p) {
      delete ((::TMVA::MinuitWrapper*)p);
   }
   static void deleteArray_TMVAcLcLMinuitWrapper(void *p) {
      delete [] ((::TMVA::MinuitWrapper*)p);
   }
   static void destruct_TMVAcLcLMinuitWrapper(void *p) {
      typedef ::TMVA::MinuitWrapper current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MinuitWrapper

namespace TMVA {
//______________________________________________________________________________
void IFitterTarget::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::IFitterTarget.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::IFitterTarget::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::IFitterTarget::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLIFitterTarget(void *p) {
      delete ((::TMVA::IFitterTarget*)p);
   }
   static void deleteArray_TMVAcLcLIFitterTarget(void *p) {
      delete [] ((::TMVA::IFitterTarget*)p);
   }
   static void destruct_TMVAcLcLIFitterTarget(void *p) {
      typedef ::TMVA::IFitterTarget current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::IFitterTarget

namespace TMVA {
//______________________________________________________________________________
void PDEFoam::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoam.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoam::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoam::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoam(void *p) {
      return  p ? new(p) ::TMVA::PDEFoam : new ::TMVA::PDEFoam;
   }
   static void *newArray_TMVAcLcLPDEFoam(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoam[nElements] : new ::TMVA::PDEFoam[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoam(void *p) {
      delete ((::TMVA::PDEFoam*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoam(void *p) {
      delete [] ((::TMVA::PDEFoam*)p);
   }
   static void destruct_TMVAcLcLPDEFoam(void *p) {
      typedef ::TMVA::PDEFoam current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoam

namespace TMVA {
//______________________________________________________________________________
void PDEFoamEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamEvent::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamEvent(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamEvent : new ::TMVA::PDEFoamEvent;
   }
   static void *newArray_TMVAcLcLPDEFoamEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamEvent[nElements] : new ::TMVA::PDEFoamEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamEvent(void *p) {
      delete ((::TMVA::PDEFoamEvent*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamEvent(void *p) {
      delete [] ((::TMVA::PDEFoamEvent*)p);
   }
   static void destruct_TMVAcLcLPDEFoamEvent(void *p) {
      typedef ::TMVA::PDEFoamEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamEvent

namespace TMVA {
//______________________________________________________________________________
void PDEFoamDiscriminant::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamDiscriminant.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamDiscriminant::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamDiscriminant::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamDiscriminant(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamDiscriminant : new ::TMVA::PDEFoamDiscriminant;
   }
   static void *newArray_TMVAcLcLPDEFoamDiscriminant(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamDiscriminant[nElements] : new ::TMVA::PDEFoamDiscriminant[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamDiscriminant(void *p) {
      delete ((::TMVA::PDEFoamDiscriminant*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamDiscriminant(void *p) {
      delete [] ((::TMVA::PDEFoamDiscriminant*)p);
   }
   static void destruct_TMVAcLcLPDEFoamDiscriminant(void *p) {
      typedef ::TMVA::PDEFoamDiscriminant current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamDiscriminant

namespace TMVA {
//______________________________________________________________________________
void PDEFoamTarget::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamTarget.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamTarget::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamTarget::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamTarget(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamTarget : new ::TMVA::PDEFoamTarget;
   }
   static void *newArray_TMVAcLcLPDEFoamTarget(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamTarget[nElements] : new ::TMVA::PDEFoamTarget[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamTarget(void *p) {
      delete ((::TMVA::PDEFoamTarget*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamTarget(void *p) {
      delete [] ((::TMVA::PDEFoamTarget*)p);
   }
   static void destruct_TMVAcLcLPDEFoamTarget(void *p) {
      typedef ::TMVA::PDEFoamTarget current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamTarget

namespace TMVA {
//______________________________________________________________________________
void PDEFoamMultiTarget::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamMultiTarget.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamMultiTarget::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamMultiTarget::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamMultiTarget(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamMultiTarget : new ::TMVA::PDEFoamMultiTarget;
   }
   static void *newArray_TMVAcLcLPDEFoamMultiTarget(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamMultiTarget[nElements] : new ::TMVA::PDEFoamMultiTarget[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamMultiTarget(void *p) {
      delete ((::TMVA::PDEFoamMultiTarget*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamMultiTarget(void *p) {
      delete [] ((::TMVA::PDEFoamMultiTarget*)p);
   }
   static void destruct_TMVAcLcLPDEFoamMultiTarget(void *p) {
      typedef ::TMVA::PDEFoamMultiTarget current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamMultiTarget

namespace TMVA {
//______________________________________________________________________________
void PDEFoamDecisionTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamDecisionTree.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamDecisionTree::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamDecisionTree::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamDecisionTree(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamDecisionTree : new ::TMVA::PDEFoamDecisionTree;
   }
   static void *newArray_TMVAcLcLPDEFoamDecisionTree(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamDecisionTree[nElements] : new ::TMVA::PDEFoamDecisionTree[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamDecisionTree(void *p) {
      delete ((::TMVA::PDEFoamDecisionTree*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamDecisionTree(void *p) {
      delete [] ((::TMVA::PDEFoamDecisionTree*)p);
   }
   static void destruct_TMVAcLcLPDEFoamDecisionTree(void *p) {
      typedef ::TMVA::PDEFoamDecisionTree current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamDecisionTree

namespace TMVA {
//______________________________________________________________________________
void PDEFoamDensityBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamDensityBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamDensityBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamDensityBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamDensityBase(void *p) {
      delete ((::TMVA::PDEFoamDensityBase*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamDensityBase(void *p) {
      delete [] ((::TMVA::PDEFoamDensityBase*)p);
   }
   static void destruct_TMVAcLcLPDEFoamDensityBase(void *p) {
      typedef ::TMVA::PDEFoamDensityBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamDensityBase

namespace TMVA {
//______________________________________________________________________________
void PDEFoamDiscriminantDensity::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamDiscriminantDensity.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamDiscriminantDensity::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamDiscriminantDensity::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamDiscriminantDensity(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamDiscriminantDensity : new ::TMVA::PDEFoamDiscriminantDensity;
   }
   static void *newArray_TMVAcLcLPDEFoamDiscriminantDensity(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamDiscriminantDensity[nElements] : new ::TMVA::PDEFoamDiscriminantDensity[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamDiscriminantDensity(void *p) {
      delete ((::TMVA::PDEFoamDiscriminantDensity*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamDiscriminantDensity(void *p) {
      delete [] ((::TMVA::PDEFoamDiscriminantDensity*)p);
   }
   static void destruct_TMVAcLcLPDEFoamDiscriminantDensity(void *p) {
      typedef ::TMVA::PDEFoamDiscriminantDensity current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamDiscriminantDensity

namespace TMVA {
//______________________________________________________________________________
void PDEFoamEventDensity::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamEventDensity.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamEventDensity::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamEventDensity::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamEventDensity(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamEventDensity : new ::TMVA::PDEFoamEventDensity;
   }
   static void *newArray_TMVAcLcLPDEFoamEventDensity(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamEventDensity[nElements] : new ::TMVA::PDEFoamEventDensity[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamEventDensity(void *p) {
      delete ((::TMVA::PDEFoamEventDensity*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamEventDensity(void *p) {
      delete [] ((::TMVA::PDEFoamEventDensity*)p);
   }
   static void destruct_TMVAcLcLPDEFoamEventDensity(void *p) {
      typedef ::TMVA::PDEFoamEventDensity current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamEventDensity

namespace TMVA {
//______________________________________________________________________________
void PDEFoamTargetDensity::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamTargetDensity.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamTargetDensity::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamTargetDensity::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamTargetDensity(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamTargetDensity : new ::TMVA::PDEFoamTargetDensity;
   }
   static void *newArray_TMVAcLcLPDEFoamTargetDensity(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamTargetDensity[nElements] : new ::TMVA::PDEFoamTargetDensity[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamTargetDensity(void *p) {
      delete ((::TMVA::PDEFoamTargetDensity*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamTargetDensity(void *p) {
      delete [] ((::TMVA::PDEFoamTargetDensity*)p);
   }
   static void destruct_TMVAcLcLPDEFoamTargetDensity(void *p) {
      typedef ::TMVA::PDEFoamTargetDensity current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamTargetDensity

namespace TMVA {
//______________________________________________________________________________
void PDEFoamDecisionTreeDensity::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamDecisionTreeDensity.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamDecisionTreeDensity::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamDecisionTreeDensity::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamDecisionTreeDensity(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamDecisionTreeDensity : new ::TMVA::PDEFoamDecisionTreeDensity;
   }
   static void *newArray_TMVAcLcLPDEFoamDecisionTreeDensity(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamDecisionTreeDensity[nElements] : new ::TMVA::PDEFoamDecisionTreeDensity[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamDecisionTreeDensity(void *p) {
      delete ((::TMVA::PDEFoamDecisionTreeDensity*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamDecisionTreeDensity(void *p) {
      delete [] ((::TMVA::PDEFoamDecisionTreeDensity*)p);
   }
   static void destruct_TMVAcLcLPDEFoamDecisionTreeDensity(void *p) {
      typedef ::TMVA::PDEFoamDecisionTreeDensity current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamDecisionTreeDensity

namespace TMVA {
//______________________________________________________________________________
void PDEFoamVect::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamVect.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamVect::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamVect::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamVect(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamVect : new ::TMVA::PDEFoamVect;
   }
   static void *newArray_TMVAcLcLPDEFoamVect(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamVect[nElements] : new ::TMVA::PDEFoamVect[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamVect(void *p) {
      delete ((::TMVA::PDEFoamVect*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamVect(void *p) {
      delete [] ((::TMVA::PDEFoamVect*)p);
   }
   static void destruct_TMVAcLcLPDEFoamVect(void *p) {
      typedef ::TMVA::PDEFoamVect current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamVect

namespace TMVA {
//______________________________________________________________________________
void PDEFoamCell::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamCell.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamCell::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamCell::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamCell(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamCell : new ::TMVA::PDEFoamCell;
   }
   static void *newArray_TMVAcLcLPDEFoamCell(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamCell[nElements] : new ::TMVA::PDEFoamCell[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamCell(void *p) {
      delete ((::TMVA::PDEFoamCell*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamCell(void *p) {
      delete [] ((::TMVA::PDEFoamCell*)p);
   }
   static void destruct_TMVAcLcLPDEFoamCell(void *p) {
      typedef ::TMVA::PDEFoamCell current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamCell

namespace TMVA {
//______________________________________________________________________________
void PDEFoamKernelBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamKernelBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamKernelBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamKernelBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamKernelBase(void *p) {
      delete ((::TMVA::PDEFoamKernelBase*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamKernelBase(void *p) {
      delete [] ((::TMVA::PDEFoamKernelBase*)p);
   }
   static void destruct_TMVAcLcLPDEFoamKernelBase(void *p) {
      typedef ::TMVA::PDEFoamKernelBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamKernelBase

namespace TMVA {
//______________________________________________________________________________
void PDEFoamKernelTrivial::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamKernelTrivial.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamKernelTrivial::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamKernelTrivial::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamKernelTrivial(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamKernelTrivial : new ::TMVA::PDEFoamKernelTrivial;
   }
   static void *newArray_TMVAcLcLPDEFoamKernelTrivial(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamKernelTrivial[nElements] : new ::TMVA::PDEFoamKernelTrivial[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamKernelTrivial(void *p) {
      delete ((::TMVA::PDEFoamKernelTrivial*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamKernelTrivial(void *p) {
      delete [] ((::TMVA::PDEFoamKernelTrivial*)p);
   }
   static void destruct_TMVAcLcLPDEFoamKernelTrivial(void *p) {
      typedef ::TMVA::PDEFoamKernelTrivial current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamKernelTrivial

namespace TMVA {
//______________________________________________________________________________
void PDEFoamKernelLinN::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamKernelLinN.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamKernelLinN::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamKernelLinN::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLPDEFoamKernelLinN(void *p) {
      return  p ? new(p) ::TMVA::PDEFoamKernelLinN : new ::TMVA::PDEFoamKernelLinN;
   }
   static void *newArray_TMVAcLcLPDEFoamKernelLinN(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::PDEFoamKernelLinN[nElements] : new ::TMVA::PDEFoamKernelLinN[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamKernelLinN(void *p) {
      delete ((::TMVA::PDEFoamKernelLinN*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamKernelLinN(void *p) {
      delete [] ((::TMVA::PDEFoamKernelLinN*)p);
   }
   static void destruct_TMVAcLcLPDEFoamKernelLinN(void *p) {
      typedef ::TMVA::PDEFoamKernelLinN current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamKernelLinN

namespace TMVA {
//______________________________________________________________________________
void PDEFoamKernelGauss::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDEFoamKernelGauss.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDEFoamKernelGauss::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDEFoamKernelGauss::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDEFoamKernelGauss(void *p) {
      delete ((::TMVA::PDEFoamKernelGauss*)p);
   }
   static void deleteArray_TMVAcLcLPDEFoamKernelGauss(void *p) {
      delete [] ((::TMVA::PDEFoamKernelGauss*)p);
   }
   static void destruct_TMVAcLcLPDEFoamKernelGauss(void *p) {
      typedef ::TMVA::PDEFoamKernelGauss current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDEFoamKernelGauss

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLBDTEventWrapper(void *p) {
      delete ((::TMVA::BDTEventWrapper*)p);
   }
   static void deleteArray_TMVAcLcLBDTEventWrapper(void *p) {
      delete [] ((::TMVA::BDTEventWrapper*)p);
   }
   static void destruct_TMVAcLcLBDTEventWrapper(void *p) {
      typedef ::TMVA::BDTEventWrapper current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::BDTEventWrapper

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLCCTreeWrapper(void *p) {
      delete ((::TMVA::CCTreeWrapper*)p);
   }
   static void deleteArray_TMVAcLcLCCTreeWrapper(void *p) {
      delete [] ((::TMVA::CCTreeWrapper*)p);
   }
   static void destruct_TMVAcLcLCCTreeWrapper(void *p) {
      typedef ::TMVA::CCTreeWrapper current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::CCTreeWrapper

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLCCPruner(void *p) {
      delete ((::TMVA::CCPruner*)p);
   }
   static void deleteArray_TMVAcLcLCCPruner(void *p) {
      delete [] ((::TMVA::CCPruner*)p);
   }
   static void destruct_TMVAcLcLCCPruner(void *p) {
      typedef ::TMVA::CCPruner current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::CCPruner

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLCostComplexityPruneTool(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::CostComplexityPruneTool : new ::TMVA::CostComplexityPruneTool;
   }
   static void *newArray_TMVAcLcLCostComplexityPruneTool(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::CostComplexityPruneTool[nElements] : new ::TMVA::CostComplexityPruneTool[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLCostComplexityPruneTool(void *p) {
      delete ((::TMVA::CostComplexityPruneTool*)p);
   }
   static void deleteArray_TMVAcLcLCostComplexityPruneTool(void *p) {
      delete [] ((::TMVA::CostComplexityPruneTool*)p);
   }
   static void destruct_TMVAcLcLCostComplexityPruneTool(void *p) {
      typedef ::TMVA::CostComplexityPruneTool current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::CostComplexityPruneTool

namespace TMVA {
//______________________________________________________________________________
void SVEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::SVEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::SVEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::SVEvent::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLSVEvent(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::SVEvent : new ::TMVA::SVEvent;
   }
   static void *newArray_TMVAcLcLSVEvent(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::SVEvent[nElements] : new ::TMVA::SVEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLSVEvent(void *p) {
      delete ((::TMVA::SVEvent*)p);
   }
   static void deleteArray_TMVAcLcLSVEvent(void *p) {
      delete [] ((::TMVA::SVEvent*)p);
   }
   static void destruct_TMVAcLcLSVEvent(void *p) {
      typedef ::TMVA::SVEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::SVEvent

namespace TMVA {
//______________________________________________________________________________
void OptimizeConfigParameters::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::OptimizeConfigParameters.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::OptimizeConfigParameters::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::OptimizeConfigParameters::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLOptimizeConfigParameters(void *p) {
      delete ((::TMVA::OptimizeConfigParameters*)p);
   }
   static void deleteArray_TMVAcLcLOptimizeConfigParameters(void *p) {
      delete [] ((::TMVA::OptimizeConfigParameters*)p);
   }
   static void destruct_TMVAcLcLOptimizeConfigParameters(void *p) {
      typedef ::TMVA::OptimizeConfigParameters current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::OptimizeConfigParameters

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_dict3_Impl() {
    static const char* headers[] = {
"inc/TMVA/Config.h",
"inc/TMVA/KDEKernel.h",
"inc/TMVA/Interval.h",
"inc/TMVA/LogInterval.h",
"inc/TMVA/FitterBase.h",
"inc/TMVA/MCFitter.h",
"inc/TMVA/GeneticFitter.h",
"inc/TMVA/SimulatedAnnealingFitter.h",
"inc/TMVA/MinuitFitter.h",
"inc/TMVA/MinuitWrapper.h",
"inc/TMVA/IFitterTarget.h",
"inc/TMVA/PDEFoam.h",
"inc/TMVA/PDEFoamDecisionTree.h",
"inc/TMVA/PDEFoamDensityBase.h",
"inc/TMVA/PDEFoamDiscriminantDensity.h",
"inc/TMVA/PDEFoamEventDensity.h",
"inc/TMVA/PDEFoamTargetDensity.h",
"inc/TMVA/PDEFoamDecisionTreeDensity.h",
"inc/TMVA/PDEFoamMultiTarget.h",
"inc/TMVA/PDEFoamVect.h",
"inc/TMVA/PDEFoamCell.h",
"inc/TMVA/PDEFoamDiscriminant.h",
"inc/TMVA/PDEFoamEvent.h",
"inc/TMVA/PDEFoamTarget.h",
"inc/TMVA/PDEFoamKernelBase.h",
"inc/TMVA/PDEFoamKernelTrivial.h",
"inc/TMVA/PDEFoamKernelLinN.h",
"inc/TMVA/PDEFoamKernelGauss.h",
"inc/TMVA/BDTEventWrapper.h",
"inc/TMVA/CCTreeWrapper.h",
"inc/TMVA/CCPruner.h",
"inc/TMVA/CostComplexityPruneTool.h",
"inc/TMVA/SVEvent.h",
"inc/TMVA/OptimizeConfigParameters.h",
0
    };
    static const char* includePaths[] = {
"/opt/root/include",
"/home/matthias/Analysis/SSX13/SSX/PxlModules/internal/TMVA/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Singleton class for global configuration settings)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Config.h")))  Config;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Kernel density estimator for PDF smoothing)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/KDEKernel.h")))  KDEKernel;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interval definition, continous and discrete)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Interval.h")))  Interval;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interval definition, continous and discrete)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/LogInterval.h")))  LogInterval;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Baseclass for fitters)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/FitterBase.h")))  FitterBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Fitter using Monte Carlo sampling of parameters)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MCFitter.h")))  MCFitter;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Fitter using a Genetic Algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GeneticFitter.h")))  GeneticFitter;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Fitter using a Simulated Annealing Algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/SimulatedAnnealingFitter.h")))  SimulatedAnnealingFitter;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Fitter using a Genetic Algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MinuitFitter.h")))  MinuitFitter;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Wrapper around TMinuit)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MinuitWrapper.h")))  MinuitWrapper;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(base class for a fitter "target")ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MinuitFitter.h")))  IFitterTarget;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Tree of PDEFoamCells)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoam.h")))  PDEFoam;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Tree of PDEFoamCells)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamMultiTarget.h")))  PDEFoamEvent;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Tree of PDEFoamCells)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamDecisionTree.h")))  PDEFoamDiscriminant;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Tree of PDEFoamCells)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamTarget.h")))  PDEFoamTarget;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Tree of PDEFoamCells)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamMultiTarget.h")))  PDEFoamMultiTarget;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Decision tree like PDEFoam)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamDecisionTree.h")))  PDEFoamDecisionTree;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(PDEFoam event density interface)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoam.h")))  PDEFoamDensityBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Class for Discriminant density)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamDiscriminantDensity.h")))  PDEFoamDiscriminantDensity;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Class for Event density)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamEventDensity.h")))  PDEFoamEventDensity;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Class for Target density)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamTargetDensity.h")))  PDEFoamTargetDensity;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Class for decision tree like PDEFoam density)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamDecisionTreeDensity.h")))  PDEFoamDecisionTreeDensity;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(n-dimensional vector with dynamical allocation)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoam.h")))  PDEFoamVect;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Single cell of FOAM)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoam.h")))  PDEFoamCell;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(PDEFoam kernel interface)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoam.h")))  PDEFoamKernelBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(trivial PDEFoam kernel estimator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamKernelTrivial.h")))  PDEFoamKernelTrivial;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(next neighbor PDEFoam kernel estimator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamKernelLinN.h")))  PDEFoamKernelLinN;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Gaussian PDEFoam kernel estimator)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDEFoamKernelGauss.h")))  PDEFoamKernelGauss;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/BDTEventWrapper.h")))  BDTEventWrapper;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/CCTreeWrapper.h")))  CCTreeWrapper;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/CCPruner.h")))  CCPruner;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/CostComplexityPruneTool.h")))  CostComplexityPruneTool;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Event for SVM)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/SVEvent.h")))  SVEvent;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface to different separation critiera used in training algorithms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/OptimizeConfigParameters.h")))  OptimizeConfigParameters;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "inc/TMVA/Config.h"
#include "inc/TMVA/KDEKernel.h"
#include "inc/TMVA/Interval.h"
#include "inc/TMVA/LogInterval.h"
#include "inc/TMVA/FitterBase.h"
#include "inc/TMVA/MCFitter.h"
#include "inc/TMVA/GeneticFitter.h"
#include "inc/TMVA/SimulatedAnnealingFitter.h"
#include "inc/TMVA/MinuitFitter.h"
#include "inc/TMVA/MinuitWrapper.h"
#include "inc/TMVA/IFitterTarget.h"
#include "inc/TMVA/PDEFoam.h"
#include "inc/TMVA/PDEFoamDecisionTree.h"
#include "inc/TMVA/PDEFoamDensityBase.h"
#include "inc/TMVA/PDEFoamDiscriminantDensity.h"
#include "inc/TMVA/PDEFoamEventDensity.h"
#include "inc/TMVA/PDEFoamTargetDensity.h"
#include "inc/TMVA/PDEFoamDecisionTreeDensity.h"
#include "inc/TMVA/PDEFoamMultiTarget.h"
#include "inc/TMVA/PDEFoamVect.h"
#include "inc/TMVA/PDEFoamCell.h"
#include "inc/TMVA/PDEFoamDiscriminant.h"
#include "inc/TMVA/PDEFoamEvent.h"
#include "inc/TMVA/PDEFoamTarget.h"
#include "inc/TMVA/PDEFoamKernelBase.h"
#include "inc/TMVA/PDEFoamKernelTrivial.h"
#include "inc/TMVA/PDEFoamKernelLinN.h"
#include "inc/TMVA/PDEFoamKernelGauss.h"
#include "inc/TMVA/BDTEventWrapper.h"
#include "inc/TMVA/CCTreeWrapper.h"
#include "inc/TMVA/CCPruner.h"
#include "inc/TMVA/CostComplexityPruneTool.h"
#include "inc/TMVA/SVEvent.h"
#include "inc/TMVA/OptimizeConfigParameters.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TMVA::BDTEventWrapper", payloadCode, "@",
"TMVA::CCPruner", payloadCode, "@",
"TMVA::CCTreeWrapper", payloadCode, "@",
"TMVA::Config", payloadCode, "@",
"TMVA::Config::IONames", payloadCode, "@",
"TMVA::Config::VariablePlotting", payloadCode, "@",
"TMVA::CostComplexityPruneTool", payloadCode, "@",
"TMVA::FitterBase", payloadCode, "@",
"TMVA::GeneticFitter", payloadCode, "@",
"TMVA::IFitterTarget", payloadCode, "@",
"TMVA::Interval", payloadCode, "@",
"TMVA::KDEKernel", payloadCode, "@",
"TMVA::LogInterval", payloadCode, "@",
"TMVA::MCFitter", payloadCode, "@",
"TMVA::MinuitFitter", payloadCode, "@",
"TMVA::MinuitWrapper", payloadCode, "@",
"TMVA::OptimizeConfigParameters", payloadCode, "@",
"TMVA::PDEFoam", payloadCode, "@",
"TMVA::PDEFoamCell", payloadCode, "@",
"TMVA::PDEFoamDecisionTree", payloadCode, "@",
"TMVA::PDEFoamDecisionTreeDensity", payloadCode, "@",
"TMVA::PDEFoamDensityBase", payloadCode, "@",
"TMVA::PDEFoamDiscriminant", payloadCode, "@",
"TMVA::PDEFoamDiscriminantDensity", payloadCode, "@",
"TMVA::PDEFoamEvent", payloadCode, "@",
"TMVA::PDEFoamEventDensity", payloadCode, "@",
"TMVA::PDEFoamKernelBase", payloadCode, "@",
"TMVA::PDEFoamKernelGauss", payloadCode, "@",
"TMVA::PDEFoamKernelLinN", payloadCode, "@",
"TMVA::PDEFoamKernelTrivial", payloadCode, "@",
"TMVA::PDEFoamMultiTarget", payloadCode, "@",
"TMVA::PDEFoamTarget", payloadCode, "@",
"TMVA::PDEFoamTargetDensity", payloadCode, "@",
"TMVA::PDEFoamVect", payloadCode, "@",
"TMVA::SVEvent", payloadCode, "@",
"TMVA::SimulatedAnnealingFitter", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dict3",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict3_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict3_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict3() {
  TriggerDictionaryInitialization_dict3_Impl();
}
