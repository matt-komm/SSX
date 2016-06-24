// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedImatthiasdIAnalysisdISSX13dISSXdIPxlModulesdIbuilddIinternaldITMVAdIdict1

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
#include "inc/TMVA/Configurable.h"
#include "inc/TMVA/Event.h"
#include "inc/TMVA/Factory.h"
#include "inc/TMVA/MethodBase.h"
#include "inc/TMVA/MethodCompositeBase.h"
#include "inc/TMVA/MethodANNBase.h"
#include "inc/TMVA/MethodTMlpANN.h"
#include "inc/TMVA/MethodRuleFit.h"
#include "inc/TMVA/MethodCuts.h"
#include "inc/TMVA/MethodFisher.h"
#include "inc/TMVA/MethodKNN.h"
#include "inc/TMVA/MethodCFMlpANN.h"
#include "inc/TMVA/MethodCFMlpANN_Utils.h"
#include "inc/TMVA/MethodLikelihood.h"
#include "inc/TMVA/MethodHMatrix.h"
#include "inc/TMVA/MethodPDERS.h"
#include "inc/TMVA/MethodBDT.h"
#include "inc/TMVA/MethodDT.h"
#include "inc/TMVA/MethodSVM.h"
#include "inc/TMVA/MethodBayesClassifier.h"
#include "inc/TMVA/MethodFDA.h"
#include "inc/TMVA/MethodMLP.h"
#include "inc/TMVA/MethodBoost.h"
#include "inc/TMVA/MethodPDEFoam.h"
#include "inc/TMVA/MethodLD.h"
#include "inc/TMVA/MethodCategory.h"

// Header files passed via #pragma extra_include

namespace TMVA {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *TMVA_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("TMVA", 0 /*version*/, "TMVA/Types.h", 53,
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
   static void *new_TMVAcLcLConfigurable(void *p = 0);
   static void *newArray_TMVAcLcLConfigurable(Long_t size, void *p);
   static void delete_TMVAcLcLConfigurable(void *p);
   static void deleteArray_TMVAcLcLConfigurable(void *p);
   static void destruct_TMVAcLcLConfigurable(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Configurable*)
   {
      ::TMVA::Configurable *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Configurable >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Configurable", ::TMVA::Configurable::Class_Version(), "inc/TMVA/Configurable.h", 51,
                  typeid(::TMVA::Configurable), DefineBehavior(ptr, ptr),
                  &::TMVA::Configurable::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Configurable) );
      instance.SetNew(&new_TMVAcLcLConfigurable);
      instance.SetNewArray(&newArray_TMVAcLcLConfigurable);
      instance.SetDelete(&delete_TMVAcLcLConfigurable);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLConfigurable);
      instance.SetDestructor(&destruct_TMVAcLcLConfigurable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Configurable*)
   {
      return GenerateInitInstanceLocal((::TMVA::Configurable*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Configurable*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLEvent_Dictionary();
   static void TMVAcLcLEvent_TClassManip(TClass*);
   static void *new_TMVAcLcLEvent(void *p = 0);
   static void *newArray_TMVAcLcLEvent(Long_t size, void *p);
   static void delete_TMVAcLcLEvent(void *p);
   static void deleteArray_TMVAcLcLEvent(void *p);
   static void destruct_TMVAcLcLEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Event*)
   {
      ::TMVA::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::Event));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Event", "inc/TMVA/Event.h", 52,
                  typeid(::TMVA::Event), DefineBehavior(ptr, ptr),
                  &TMVAcLcLEvent_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Event) );
      instance.SetNew(&new_TMVAcLcLEvent);
      instance.SetNewArray(&newArray_TMVAcLcLEvent);
      instance.SetDelete(&delete_TMVAcLcLEvent);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLEvent);
      instance.SetDestructor(&destruct_TMVAcLcLEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Event*)
   {
      return GenerateInitInstanceLocal((::TMVA::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Event*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::Event*)0x0)->GetClass();
      TMVAcLcLEvent_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLkNNcLcLEvent_Dictionary();
   static void TMVAcLcLkNNcLcLEvent_TClassManip(TClass*);
   static void *new_TMVAcLcLkNNcLcLEvent(void *p = 0);
   static void *newArray_TMVAcLcLkNNcLcLEvent(Long_t size, void *p);
   static void delete_TMVAcLcLkNNcLcLEvent(void *p);
   static void deleteArray_TMVAcLcLkNNcLcLEvent(void *p);
   static void destruct_TMVAcLcLkNNcLcLEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::kNN::Event*)
   {
      ::TMVA::kNN::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::kNN::Event));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::kNN::Event", "TMVA/ModulekNN.h", 67,
                  typeid(::TMVA::kNN::Event), DefineBehavior(ptr, ptr),
                  &TMVAcLcLkNNcLcLEvent_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::kNN::Event) );
      instance.SetNew(&new_TMVAcLcLkNNcLcLEvent);
      instance.SetNewArray(&newArray_TMVAcLcLkNNcLcLEvent);
      instance.SetDelete(&delete_TMVAcLcLkNNcLcLEvent);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLkNNcLcLEvent);
      instance.SetDestructor(&destruct_TMVAcLcLkNNcLcLEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::kNN::Event*)
   {
      return GenerateInitInstanceLocal((::TMVA::kNN::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::kNN::Event*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLkNNcLcLEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::kNN::Event*)0x0)->GetClass();
      TMVAcLcLkNNcLcLEvent_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLkNNcLcLEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLFactory(void *p);
   static void deleteArray_TMVAcLcLFactory(void *p);
   static void destruct_TMVAcLcLFactory(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Factory*)
   {
      ::TMVA::Factory *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Factory >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Factory", ::TMVA::Factory::Class_Version(), "inc/TMVA/Factory.h", 77,
                  typeid(::TMVA::Factory), DefineBehavior(ptr, ptr),
                  &::TMVA::Factory::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Factory) );
      instance.SetDelete(&delete_TMVAcLcLFactory);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLFactory);
      instance.SetDestructor(&destruct_TMVAcLcLFactory);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Factory*)
   {
      return GenerateInitInstanceLocal((::TMVA::Factory*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Factory*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodBase(void *p);
   static void deleteArray_TMVAcLcLMethodBase(void *p);
   static void destruct_TMVAcLcLMethodBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodBase*)
   {
      ::TMVA::MethodBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodBase", ::TMVA::MethodBase::Class_Version(), "inc/TMVA/MethodBase.h", 91,
                  typeid(::TMVA::MethodBase), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodBase) );
      instance.SetDelete(&delete_TMVAcLcLMethodBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodBase);
      instance.SetDestructor(&destruct_TMVAcLcLMethodBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodCompositeBase(void *p);
   static void deleteArray_TMVAcLcLMethodCompositeBase(void *p);
   static void destruct_TMVAcLcLMethodCompositeBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodCompositeBase*)
   {
      ::TMVA::MethodCompositeBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodCompositeBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodCompositeBase", ::TMVA::MethodCompositeBase::Class_Version(), "inc/TMVA/MethodCompositeBase.h", 52,
                  typeid(::TMVA::MethodCompositeBase), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodCompositeBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodCompositeBase) );
      instance.SetDelete(&delete_TMVAcLcLMethodCompositeBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodCompositeBase);
      instance.SetDestructor(&destruct_TMVAcLcLMethodCompositeBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodCompositeBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodCompositeBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodCompositeBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodANNBase(void *p);
   static void deleteArray_TMVAcLcLMethodANNBase(void *p);
   static void destruct_TMVAcLcLMethodANNBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodANNBase*)
   {
      ::TMVA::MethodANNBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodANNBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodANNBase", ::TMVA::MethodANNBase::Class_Version(), "inc/TMVA/MethodANNBase.h", 80,
                  typeid(::TMVA::MethodANNBase), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodANNBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodANNBase) );
      instance.SetDelete(&delete_TMVAcLcLMethodANNBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodANNBase);
      instance.SetDestructor(&destruct_TMVAcLcLMethodANNBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodANNBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodANNBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodANNBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodTMlpANN(void *p);
   static void deleteArray_TMVAcLcLMethodTMlpANN(void *p);
   static void destruct_TMVAcLcLMethodTMlpANN(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodTMlpANN*)
   {
      ::TMVA::MethodTMlpANN *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodTMlpANN >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodTMlpANN", ::TMVA::MethodTMlpANN::Class_Version(), "inc/TMVA/MethodTMlpANN.h", 51,
                  typeid(::TMVA::MethodTMlpANN), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodTMlpANN::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodTMlpANN) );
      instance.SetDelete(&delete_TMVAcLcLMethodTMlpANN);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodTMlpANN);
      instance.SetDestructor(&destruct_TMVAcLcLMethodTMlpANN);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodTMlpANN*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodTMlpANN*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodTMlpANN*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodRuleFit(void *p);
   static void deleteArray_TMVAcLcLMethodRuleFit(void *p);
   static void destruct_TMVAcLcLMethodRuleFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodRuleFit*)
   {
      ::TMVA::MethodRuleFit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodRuleFit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodRuleFit", ::TMVA::MethodRuleFit::Class_Version(), "inc/TMVA/MethodRuleFit.h", 57,
                  typeid(::TMVA::MethodRuleFit), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodRuleFit::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodRuleFit) );
      instance.SetDelete(&delete_TMVAcLcLMethodRuleFit);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodRuleFit);
      instance.SetDestructor(&destruct_TMVAcLcLMethodRuleFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodRuleFit*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodRuleFit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodRuleFit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodCuts(void *p);
   static void deleteArray_TMVAcLcLMethodCuts(void *p);
   static void destruct_TMVAcLcLMethodCuts(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodCuts*)
   {
      ::TMVA::MethodCuts *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodCuts >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodCuts", ::TMVA::MethodCuts::Class_Version(), "inc/TMVA/MethodCuts.h", 75,
                  typeid(::TMVA::MethodCuts), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodCuts::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodCuts) );
      instance.SetDelete(&delete_TMVAcLcLMethodCuts);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodCuts);
      instance.SetDestructor(&destruct_TMVAcLcLMethodCuts);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodCuts*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodCuts*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodCuts*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodFisher(void *p);
   static void deleteArray_TMVAcLcLMethodFisher(void *p);
   static void destruct_TMVAcLcLMethodFisher(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodFisher*)
   {
      ::TMVA::MethodFisher *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodFisher >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodFisher", ::TMVA::MethodFisher::Class_Version(), "inc/TMVA/MethodFisher.h", 58,
                  typeid(::TMVA::MethodFisher), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodFisher::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodFisher) );
      instance.SetDelete(&delete_TMVAcLcLMethodFisher);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodFisher);
      instance.SetDestructor(&destruct_TMVAcLcLMethodFisher);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodFisher*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodFisher*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodFisher*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodKNN(void *p);
   static void deleteArray_TMVAcLcLMethodKNN(void *p);
   static void destruct_TMVAcLcLMethodKNN(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodKNN*)
   {
      ::TMVA::MethodKNN *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodKNN >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodKNN", ::TMVA::MethodKNN::Class_Version(), "inc/TMVA/MethodKNN.h", 60,
                  typeid(::TMVA::MethodKNN), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodKNN::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodKNN) );
      instance.SetDelete(&delete_TMVAcLcLMethodKNN);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodKNN);
      instance.SetDestructor(&destruct_TMVAcLcLMethodKNN);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodKNN*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodKNN*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodKNN*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodCFMlpANN(void *p);
   static void deleteArray_TMVAcLcLMethodCFMlpANN(void *p);
   static void destruct_TMVAcLcLMethodCFMlpANN(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodCFMlpANN*)
   {
      ::TMVA::MethodCFMlpANN *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodCFMlpANN >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodCFMlpANN", ::TMVA::MethodCFMlpANN::Class_Version(), "inc/TMVA/MethodCFMlpANN.h", 100,
                  typeid(::TMVA::MethodCFMlpANN), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodCFMlpANN::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodCFMlpANN) );
      instance.SetDelete(&delete_TMVAcLcLMethodCFMlpANN);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodCFMlpANN);
      instance.SetDestructor(&destruct_TMVAcLcLMethodCFMlpANN);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodCFMlpANN*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodCFMlpANN*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodCFMlpANN_Utils(void *p);
   static void deleteArray_TMVAcLcLMethodCFMlpANN_Utils(void *p);
   static void destruct_TMVAcLcLMethodCFMlpANN_Utils(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodCFMlpANN_Utils*)
   {
      ::TMVA::MethodCFMlpANN_Utils *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodCFMlpANN_Utils >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodCFMlpANN_Utils", ::TMVA::MethodCFMlpANN_Utils::Class_Version(), "TMVA/MethodCFMlpANN_Utils.h", 60,
                  typeid(::TMVA::MethodCFMlpANN_Utils), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodCFMlpANN_Utils::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodCFMlpANN_Utils) );
      instance.SetDelete(&delete_TMVAcLcLMethodCFMlpANN_Utils);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodCFMlpANN_Utils);
      instance.SetDestructor(&destruct_TMVAcLcLMethodCFMlpANN_Utils);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodCFMlpANN_Utils*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodCFMlpANN_Utils*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN_Utils*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodLikelihood(void *p);
   static void deleteArray_TMVAcLcLMethodLikelihood(void *p);
   static void destruct_TMVAcLcLMethodLikelihood(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodLikelihood*)
   {
      ::TMVA::MethodLikelihood *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodLikelihood >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodLikelihood", ::TMVA::MethodLikelihood::Class_Version(), "inc/TMVA/MethodLikelihood.h", 64,
                  typeid(::TMVA::MethodLikelihood), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodLikelihood::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodLikelihood) );
      instance.SetDelete(&delete_TMVAcLcLMethodLikelihood);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodLikelihood);
      instance.SetDestructor(&destruct_TMVAcLcLMethodLikelihood);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodLikelihood*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodLikelihood*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodLikelihood*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodHMatrix(void *p);
   static void deleteArray_TMVAcLcLMethodHMatrix(void *p);
   static void destruct_TMVAcLcLMethodHMatrix(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodHMatrix*)
   {
      ::TMVA::MethodHMatrix *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodHMatrix >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodHMatrix", ::TMVA::MethodHMatrix::Class_Version(), "inc/TMVA/MethodHMatrix.h", 62,
                  typeid(::TMVA::MethodHMatrix), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodHMatrix::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodHMatrix) );
      instance.SetDelete(&delete_TMVAcLcLMethodHMatrix);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodHMatrix);
      instance.SetDestructor(&destruct_TMVAcLcLMethodHMatrix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodHMatrix*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodHMatrix*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodHMatrix*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodPDERS(void *p);
   static void deleteArray_TMVAcLcLMethodPDERS(void *p);
   static void destruct_TMVAcLcLMethodPDERS(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodPDERS*)
   {
      ::TMVA::MethodPDERS *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodPDERS >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodPDERS", ::TMVA::MethodPDERS::Class_Version(), "inc/TMVA/MethodPDERS.h", 67,
                  typeid(::TMVA::MethodPDERS), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodPDERS::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodPDERS) );
      instance.SetDelete(&delete_TMVAcLcLMethodPDERS);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodPDERS);
      instance.SetDestructor(&destruct_TMVAcLcLMethodPDERS);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodPDERS*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodPDERS*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodPDERS*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodBDT(void *p);
   static void deleteArray_TMVAcLcLMethodBDT(void *p);
   static void destruct_TMVAcLcLMethodBDT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodBDT*)
   {
      ::TMVA::MethodBDT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodBDT >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodBDT", ::TMVA::MethodBDT::Class_Version(), "inc/TMVA/MethodBDT.h", 63,
                  typeid(::TMVA::MethodBDT), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodBDT::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodBDT) );
      instance.SetDelete(&delete_TMVAcLcLMethodBDT);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodBDT);
      instance.SetDestructor(&destruct_TMVAcLcLMethodBDT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodBDT*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodBDT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodBDT*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodDT(void *p);
   static void deleteArray_TMVAcLcLMethodDT(void *p);
   static void destruct_TMVAcLcLMethodDT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodDT*)
   {
      ::TMVA::MethodDT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodDT >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodDT", ::TMVA::MethodDT::Class_Version(), "inc/TMVA/MethodDT.h", 61,
                  typeid(::TMVA::MethodDT), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodDT::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodDT) );
      instance.SetDelete(&delete_TMVAcLcLMethodDT);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodDT);
      instance.SetDestructor(&destruct_TMVAcLcLMethodDT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodDT*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodDT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodDT*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodSVM(void *p);
   static void deleteArray_TMVAcLcLMethodSVM(void *p);
   static void destruct_TMVAcLcLMethodSVM(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodSVM*)
   {
      ::TMVA::MethodSVM *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodSVM >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodSVM", ::TMVA::MethodSVM::Class_Version(), "inc/TMVA/MethodSVM.h", 64,
                  typeid(::TMVA::MethodSVM), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodSVM::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodSVM) );
      instance.SetDelete(&delete_TMVAcLcLMethodSVM);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodSVM);
      instance.SetDestructor(&destruct_TMVAcLcLMethodSVM);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodSVM*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodSVM*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodSVM*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodBayesClassifier(void *p);
   static void deleteArray_TMVAcLcLMethodBayesClassifier(void *p);
   static void destruct_TMVAcLcLMethodBayesClassifier(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodBayesClassifier*)
   {
      ::TMVA::MethodBayesClassifier *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodBayesClassifier >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodBayesClassifier", ::TMVA::MethodBayesClassifier::Class_Version(), "inc/TMVA/MethodBayesClassifier.h", 48,
                  typeid(::TMVA::MethodBayesClassifier), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodBayesClassifier::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodBayesClassifier) );
      instance.SetDelete(&delete_TMVAcLcLMethodBayesClassifier);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodBayesClassifier);
      instance.SetDestructor(&destruct_TMVAcLcLMethodBayesClassifier);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodBayesClassifier*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodBayesClassifier*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodBayesClassifier*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodFDA(void *p);
   static void deleteArray_TMVAcLcLMethodFDA(void *p);
   static void destruct_TMVAcLcLMethodFDA(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodFDA*)
   {
      ::TMVA::MethodFDA *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodFDA >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodFDA", ::TMVA::MethodFDA::Class_Version(), "inc/TMVA/MethodFDA.h", 64,
                  typeid(::TMVA::MethodFDA), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodFDA::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodFDA) );
      instance.SetDelete(&delete_TMVAcLcLMethodFDA);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodFDA);
      instance.SetDestructor(&destruct_TMVAcLcLMethodFDA);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodFDA*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodFDA*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodFDA*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodMLP(void *p);
   static void deleteArray_TMVAcLcLMethodMLP(void *p);
   static void destruct_TMVAcLcLMethodMLP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodMLP*)
   {
      ::TMVA::MethodMLP *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodMLP >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodMLP", ::TMVA::MethodMLP::Class_Version(), "inc/TMVA/MethodMLP.h", 93,
                  typeid(::TMVA::MethodMLP), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodMLP::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodMLP) );
      instance.SetDelete(&delete_TMVAcLcLMethodMLP);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodMLP);
      instance.SetDestructor(&destruct_TMVAcLcLMethodMLP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodMLP*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodMLP*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodMLP*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodBoost(void *p);
   static void deleteArray_TMVAcLcLMethodBoost(void *p);
   static void destruct_TMVAcLcLMethodBoost(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodBoost*)
   {
      ::TMVA::MethodBoost *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodBoost >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodBoost", ::TMVA::MethodBoost::Class_Version(), "inc/TMVA/MethodBoost.h", 60,
                  typeid(::TMVA::MethodBoost), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodBoost::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodBoost) );
      instance.SetDelete(&delete_TMVAcLcLMethodBoost);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodBoost);
      instance.SetDestructor(&destruct_TMVAcLcLMethodBoost);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodBoost*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodBoost*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodBoost*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodPDEFoam(void *p);
   static void deleteArray_TMVAcLcLMethodPDEFoam(void *p);
   static void destruct_TMVAcLcLMethodPDEFoam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodPDEFoam*)
   {
      ::TMVA::MethodPDEFoam *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodPDEFoam >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodPDEFoam", ::TMVA::MethodPDEFoam::Class_Version(), "inc/TMVA/MethodPDEFoam.h", 99,
                  typeid(::TMVA::MethodPDEFoam), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodPDEFoam::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodPDEFoam) );
      instance.SetDelete(&delete_TMVAcLcLMethodPDEFoam);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodPDEFoam);
      instance.SetDestructor(&destruct_TMVAcLcLMethodPDEFoam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodPDEFoam*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodPDEFoam*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodPDEFoam*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodLD(void *p);
   static void deleteArray_TMVAcLcLMethodLD(void *p);
   static void destruct_TMVAcLcLMethodLD(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodLD*)
   {
      ::TMVA::MethodLD *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodLD >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodLD", ::TMVA::MethodLD::Class_Version(), "inc/TMVA/MethodLD.h", 54,
                  typeid(::TMVA::MethodLD), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodLD::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodLD) );
      instance.SetDelete(&delete_TMVAcLcLMethodLD);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodLD);
      instance.SetDestructor(&destruct_TMVAcLcLMethodLD);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodLD*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodLD*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodLD*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLMethodCategory(void *p);
   static void deleteArray_TMVAcLcLMethodCategory(void *p);
   static void destruct_TMVAcLcLMethodCategory(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MethodCategory*)
   {
      ::TMVA::MethodCategory *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MethodCategory >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MethodCategory", ::TMVA::MethodCategory::Class_Version(), "inc/TMVA/MethodCategory.h", 60,
                  typeid(::TMVA::MethodCategory), DefineBehavior(ptr, ptr),
                  &::TMVA::MethodCategory::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MethodCategory) );
      instance.SetDelete(&delete_TMVAcLcLMethodCategory);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMethodCategory);
      instance.SetDestructor(&destruct_TMVAcLcLMethodCategory);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MethodCategory*)
   {
      return GenerateInitInstanceLocal((::TMVA::MethodCategory*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MethodCategory*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Configurable::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Configurable::Class_Name()
{
   return "TMVA::Configurable";
}

//______________________________________________________________________________
const char *Configurable::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Configurable*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Configurable::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Configurable*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Configurable::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Configurable*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Configurable::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Configurable*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Factory::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Factory::Class_Name()
{
   return "TMVA::Factory";
}

//______________________________________________________________________________
const char *Factory::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Factory*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Factory::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Factory*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Factory::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Factory*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Factory::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Factory*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodBase::Class_Name()
{
   return "TMVA::MethodBase";
}

//______________________________________________________________________________
const char *MethodBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodCompositeBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodCompositeBase::Class_Name()
{
   return "TMVA::MethodCompositeBase";
}

//______________________________________________________________________________
const char *MethodCompositeBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCompositeBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodCompositeBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCompositeBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodCompositeBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCompositeBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodCompositeBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCompositeBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodANNBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodANNBase::Class_Name()
{
   return "TMVA::MethodANNBase";
}

//______________________________________________________________________________
const char *MethodANNBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodANNBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodANNBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodANNBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodANNBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodANNBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodANNBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodANNBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodTMlpANN::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodTMlpANN::Class_Name()
{
   return "TMVA::MethodTMlpANN";
}

//______________________________________________________________________________
const char *MethodTMlpANN::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodTMlpANN*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodTMlpANN::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodTMlpANN*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodTMlpANN::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodTMlpANN*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodTMlpANN::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodTMlpANN*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodRuleFit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodRuleFit::Class_Name()
{
   return "TMVA::MethodRuleFit";
}

//______________________________________________________________________________
const char *MethodRuleFit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodRuleFit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodRuleFit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodRuleFit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodRuleFit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodRuleFit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodRuleFit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodRuleFit*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodCuts::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodCuts::Class_Name()
{
   return "TMVA::MethodCuts";
}

//______________________________________________________________________________
const char *MethodCuts::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCuts*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodCuts::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCuts*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodCuts::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCuts*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodCuts::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCuts*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodFisher::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodFisher::Class_Name()
{
   return "TMVA::MethodFisher";
}

//______________________________________________________________________________
const char *MethodFisher::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFisher*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodFisher::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFisher*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodFisher::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFisher*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodFisher::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFisher*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodKNN::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodKNN::Class_Name()
{
   return "TMVA::MethodKNN";
}

//______________________________________________________________________________
const char *MethodKNN::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodKNN*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodKNN::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodKNN*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodKNN::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodKNN*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodKNN::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodKNN*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodCFMlpANN::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodCFMlpANN::Class_Name()
{
   return "TMVA::MethodCFMlpANN";
}

//______________________________________________________________________________
const char *MethodCFMlpANN::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodCFMlpANN::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodCFMlpANN::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodCFMlpANN::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodCFMlpANN_Utils::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodCFMlpANN_Utils::Class_Name()
{
   return "TMVA::MethodCFMlpANN_Utils";
}

//______________________________________________________________________________
const char *MethodCFMlpANN_Utils::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN_Utils*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodCFMlpANN_Utils::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN_Utils*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodCFMlpANN_Utils::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN_Utils*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodCFMlpANN_Utils::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCFMlpANN_Utils*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodLikelihood::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodLikelihood::Class_Name()
{
   return "TMVA::MethodLikelihood";
}

//______________________________________________________________________________
const char *MethodLikelihood::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLikelihood*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodLikelihood::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLikelihood*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodLikelihood::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLikelihood*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodLikelihood::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLikelihood*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodHMatrix::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodHMatrix::Class_Name()
{
   return "TMVA::MethodHMatrix";
}

//______________________________________________________________________________
const char *MethodHMatrix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodHMatrix*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodHMatrix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodHMatrix*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodHMatrix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodHMatrix*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodHMatrix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodHMatrix*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodPDERS::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodPDERS::Class_Name()
{
   return "TMVA::MethodPDERS";
}

//______________________________________________________________________________
const char *MethodPDERS::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDERS*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodPDERS::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDERS*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodPDERS::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDERS*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodPDERS::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDERS*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodBDT::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodBDT::Class_Name()
{
   return "TMVA::MethodBDT";
}

//______________________________________________________________________________
const char *MethodBDT::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBDT*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodBDT::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBDT*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodBDT::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBDT*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodBDT::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBDT*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodDT::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodDT::Class_Name()
{
   return "TMVA::MethodDT";
}

//______________________________________________________________________________
const char *MethodDT::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodDT*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodDT::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodDT*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodDT::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodDT*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodDT::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodDT*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodSVM::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodSVM::Class_Name()
{
   return "TMVA::MethodSVM";
}

//______________________________________________________________________________
const char *MethodSVM::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodSVM*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodSVM::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodSVM*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodSVM::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodSVM*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodSVM::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodSVM*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodBayesClassifier::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodBayesClassifier::Class_Name()
{
   return "TMVA::MethodBayesClassifier";
}

//______________________________________________________________________________
const char *MethodBayesClassifier::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBayesClassifier*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodBayesClassifier::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBayesClassifier*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodBayesClassifier::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBayesClassifier*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodBayesClassifier::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBayesClassifier*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodFDA::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodFDA::Class_Name()
{
   return "TMVA::MethodFDA";
}

//______________________________________________________________________________
const char *MethodFDA::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFDA*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodFDA::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFDA*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodFDA::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFDA*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodFDA::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodFDA*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodMLP::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodMLP::Class_Name()
{
   return "TMVA::MethodMLP";
}

//______________________________________________________________________________
const char *MethodMLP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodMLP*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodMLP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodMLP*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodMLP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodMLP*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodMLP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodMLP*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodBoost::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodBoost::Class_Name()
{
   return "TMVA::MethodBoost";
}

//______________________________________________________________________________
const char *MethodBoost::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBoost*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodBoost::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBoost*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodBoost::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBoost*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodBoost::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodBoost*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodPDEFoam::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodPDEFoam::Class_Name()
{
   return "TMVA::MethodPDEFoam";
}

//______________________________________________________________________________
const char *MethodPDEFoam::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDEFoam*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodPDEFoam::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDEFoam*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodPDEFoam::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDEFoam*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodPDEFoam::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodPDEFoam*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodLD::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodLD::Class_Name()
{
   return "TMVA::MethodLD";
}

//______________________________________________________________________________
const char *MethodLD::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLD*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodLD::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLD*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodLD::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLD*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodLD::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodLD*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MethodCategory::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MethodCategory::Class_Name()
{
   return "TMVA::MethodCategory";
}

//______________________________________________________________________________
const char *MethodCategory::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCategory*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MethodCategory::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCategory*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MethodCategory::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCategory*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MethodCategory::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MethodCategory*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
void Configurable::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Configurable.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Configurable::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Configurable::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLConfigurable(void *p) {
      return  p ? new(p) ::TMVA::Configurable : new ::TMVA::Configurable;
   }
   static void *newArray_TMVAcLcLConfigurable(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::Configurable[nElements] : new ::TMVA::Configurable[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLConfigurable(void *p) {
      delete ((::TMVA::Configurable*)p);
   }
   static void deleteArray_TMVAcLcLConfigurable(void *p) {
      delete [] ((::TMVA::Configurable*)p);
   }
   static void destruct_TMVAcLcLConfigurable(void *p) {
      typedef ::TMVA::Configurable current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Configurable

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLEvent(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Event : new ::TMVA::Event;
   }
   static void *newArray_TMVAcLcLEvent(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Event[nElements] : new ::TMVA::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLEvent(void *p) {
      delete ((::TMVA::Event*)p);
   }
   static void deleteArray_TMVAcLcLEvent(void *p) {
      delete [] ((::TMVA::Event*)p);
   }
   static void destruct_TMVAcLcLEvent(void *p) {
      typedef ::TMVA::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Event

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLkNNcLcLEvent(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::kNN::Event : new ::TMVA::kNN::Event;
   }
   static void *newArray_TMVAcLcLkNNcLcLEvent(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::kNN::Event[nElements] : new ::TMVA::kNN::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLkNNcLcLEvent(void *p) {
      delete ((::TMVA::kNN::Event*)p);
   }
   static void deleteArray_TMVAcLcLkNNcLcLEvent(void *p) {
      delete [] ((::TMVA::kNN::Event*)p);
   }
   static void destruct_TMVAcLcLkNNcLcLEvent(void *p) {
      typedef ::TMVA::kNN::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::kNN::Event

namespace TMVA {
//______________________________________________________________________________
void Factory::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Factory.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Factory::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Factory::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLFactory(void *p) {
      delete ((::TMVA::Factory*)p);
   }
   static void deleteArray_TMVAcLcLFactory(void *p) {
      delete [] ((::TMVA::Factory*)p);
   }
   static void destruct_TMVAcLcLFactory(void *p) {
      typedef ::TMVA::Factory current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Factory

namespace TMVA {
//______________________________________________________________________________
void MethodBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodBase(void *p) {
      delete ((::TMVA::MethodBase*)p);
   }
   static void deleteArray_TMVAcLcLMethodBase(void *p) {
      delete [] ((::TMVA::MethodBase*)p);
   }
   static void destruct_TMVAcLcLMethodBase(void *p) {
      typedef ::TMVA::MethodBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodBase

namespace TMVA {
//______________________________________________________________________________
void MethodCompositeBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodCompositeBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodCompositeBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodCompositeBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodCompositeBase(void *p) {
      delete ((::TMVA::MethodCompositeBase*)p);
   }
   static void deleteArray_TMVAcLcLMethodCompositeBase(void *p) {
      delete [] ((::TMVA::MethodCompositeBase*)p);
   }
   static void destruct_TMVAcLcLMethodCompositeBase(void *p) {
      typedef ::TMVA::MethodCompositeBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodCompositeBase

namespace TMVA {
//______________________________________________________________________________
void MethodANNBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodANNBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodANNBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodANNBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodANNBase(void *p) {
      delete ((::TMVA::MethodANNBase*)p);
   }
   static void deleteArray_TMVAcLcLMethodANNBase(void *p) {
      delete [] ((::TMVA::MethodANNBase*)p);
   }
   static void destruct_TMVAcLcLMethodANNBase(void *p) {
      typedef ::TMVA::MethodANNBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodANNBase

namespace TMVA {
//______________________________________________________________________________
void MethodTMlpANN::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodTMlpANN.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodTMlpANN::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodTMlpANN::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodTMlpANN(void *p) {
      delete ((::TMVA::MethodTMlpANN*)p);
   }
   static void deleteArray_TMVAcLcLMethodTMlpANN(void *p) {
      delete [] ((::TMVA::MethodTMlpANN*)p);
   }
   static void destruct_TMVAcLcLMethodTMlpANN(void *p) {
      typedef ::TMVA::MethodTMlpANN current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodTMlpANN

namespace TMVA {
//______________________________________________________________________________
void MethodRuleFit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodRuleFit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodRuleFit::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodRuleFit::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodRuleFit(void *p) {
      delete ((::TMVA::MethodRuleFit*)p);
   }
   static void deleteArray_TMVAcLcLMethodRuleFit(void *p) {
      delete [] ((::TMVA::MethodRuleFit*)p);
   }
   static void destruct_TMVAcLcLMethodRuleFit(void *p) {
      typedef ::TMVA::MethodRuleFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodRuleFit

namespace TMVA {
//______________________________________________________________________________
void MethodCuts::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodCuts.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodCuts::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodCuts::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodCuts(void *p) {
      delete ((::TMVA::MethodCuts*)p);
   }
   static void deleteArray_TMVAcLcLMethodCuts(void *p) {
      delete [] ((::TMVA::MethodCuts*)p);
   }
   static void destruct_TMVAcLcLMethodCuts(void *p) {
      typedef ::TMVA::MethodCuts current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodCuts

namespace TMVA {
//______________________________________________________________________________
void MethodFisher::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodFisher.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodFisher::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodFisher::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodFisher(void *p) {
      delete ((::TMVA::MethodFisher*)p);
   }
   static void deleteArray_TMVAcLcLMethodFisher(void *p) {
      delete [] ((::TMVA::MethodFisher*)p);
   }
   static void destruct_TMVAcLcLMethodFisher(void *p) {
      typedef ::TMVA::MethodFisher current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodFisher

namespace TMVA {
//______________________________________________________________________________
void MethodKNN::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodKNN.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodKNN::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodKNN::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodKNN(void *p) {
      delete ((::TMVA::MethodKNN*)p);
   }
   static void deleteArray_TMVAcLcLMethodKNN(void *p) {
      delete [] ((::TMVA::MethodKNN*)p);
   }
   static void destruct_TMVAcLcLMethodKNN(void *p) {
      typedef ::TMVA::MethodKNN current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodKNN

namespace TMVA {
//______________________________________________________________________________
void MethodCFMlpANN::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodCFMlpANN.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodCFMlpANN::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodCFMlpANN::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodCFMlpANN(void *p) {
      delete ((::TMVA::MethodCFMlpANN*)p);
   }
   static void deleteArray_TMVAcLcLMethodCFMlpANN(void *p) {
      delete [] ((::TMVA::MethodCFMlpANN*)p);
   }
   static void destruct_TMVAcLcLMethodCFMlpANN(void *p) {
      typedef ::TMVA::MethodCFMlpANN current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodCFMlpANN

namespace TMVA {
//______________________________________________________________________________
void MethodCFMlpANN_Utils::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodCFMlpANN_Utils.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodCFMlpANN_Utils::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodCFMlpANN_Utils::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodCFMlpANN_Utils(void *p) {
      delete ((::TMVA::MethodCFMlpANN_Utils*)p);
   }
   static void deleteArray_TMVAcLcLMethodCFMlpANN_Utils(void *p) {
      delete [] ((::TMVA::MethodCFMlpANN_Utils*)p);
   }
   static void destruct_TMVAcLcLMethodCFMlpANN_Utils(void *p) {
      typedef ::TMVA::MethodCFMlpANN_Utils current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodCFMlpANN_Utils

namespace TMVA {
//______________________________________________________________________________
void MethodLikelihood::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodLikelihood.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodLikelihood::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodLikelihood::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodLikelihood(void *p) {
      delete ((::TMVA::MethodLikelihood*)p);
   }
   static void deleteArray_TMVAcLcLMethodLikelihood(void *p) {
      delete [] ((::TMVA::MethodLikelihood*)p);
   }
   static void destruct_TMVAcLcLMethodLikelihood(void *p) {
      typedef ::TMVA::MethodLikelihood current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodLikelihood

namespace TMVA {
//______________________________________________________________________________
void MethodHMatrix::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodHMatrix.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodHMatrix::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodHMatrix::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodHMatrix(void *p) {
      delete ((::TMVA::MethodHMatrix*)p);
   }
   static void deleteArray_TMVAcLcLMethodHMatrix(void *p) {
      delete [] ((::TMVA::MethodHMatrix*)p);
   }
   static void destruct_TMVAcLcLMethodHMatrix(void *p) {
      typedef ::TMVA::MethodHMatrix current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodHMatrix

namespace TMVA {
//______________________________________________________________________________
void MethodPDERS::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodPDERS.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodPDERS::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodPDERS::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodPDERS(void *p) {
      delete ((::TMVA::MethodPDERS*)p);
   }
   static void deleteArray_TMVAcLcLMethodPDERS(void *p) {
      delete [] ((::TMVA::MethodPDERS*)p);
   }
   static void destruct_TMVAcLcLMethodPDERS(void *p) {
      typedef ::TMVA::MethodPDERS current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodPDERS

namespace TMVA {
//______________________________________________________________________________
void MethodBDT::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodBDT.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodBDT::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodBDT::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodBDT(void *p) {
      delete ((::TMVA::MethodBDT*)p);
   }
   static void deleteArray_TMVAcLcLMethodBDT(void *p) {
      delete [] ((::TMVA::MethodBDT*)p);
   }
   static void destruct_TMVAcLcLMethodBDT(void *p) {
      typedef ::TMVA::MethodBDT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodBDT

namespace TMVA {
//______________________________________________________________________________
void MethodDT::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodDT.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodDT::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodDT::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodDT(void *p) {
      delete ((::TMVA::MethodDT*)p);
   }
   static void deleteArray_TMVAcLcLMethodDT(void *p) {
      delete [] ((::TMVA::MethodDT*)p);
   }
   static void destruct_TMVAcLcLMethodDT(void *p) {
      typedef ::TMVA::MethodDT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodDT

namespace TMVA {
//______________________________________________________________________________
void MethodSVM::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodSVM.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodSVM::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodSVM::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodSVM(void *p) {
      delete ((::TMVA::MethodSVM*)p);
   }
   static void deleteArray_TMVAcLcLMethodSVM(void *p) {
      delete [] ((::TMVA::MethodSVM*)p);
   }
   static void destruct_TMVAcLcLMethodSVM(void *p) {
      typedef ::TMVA::MethodSVM current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodSVM

namespace TMVA {
//______________________________________________________________________________
void MethodBayesClassifier::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodBayesClassifier.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodBayesClassifier::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodBayesClassifier::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodBayesClassifier(void *p) {
      delete ((::TMVA::MethodBayesClassifier*)p);
   }
   static void deleteArray_TMVAcLcLMethodBayesClassifier(void *p) {
      delete [] ((::TMVA::MethodBayesClassifier*)p);
   }
   static void destruct_TMVAcLcLMethodBayesClassifier(void *p) {
      typedef ::TMVA::MethodBayesClassifier current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodBayesClassifier

namespace TMVA {
//______________________________________________________________________________
void MethodFDA::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodFDA.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodFDA::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodFDA::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodFDA(void *p) {
      delete ((::TMVA::MethodFDA*)p);
   }
   static void deleteArray_TMVAcLcLMethodFDA(void *p) {
      delete [] ((::TMVA::MethodFDA*)p);
   }
   static void destruct_TMVAcLcLMethodFDA(void *p) {
      typedef ::TMVA::MethodFDA current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodFDA

namespace TMVA {
//______________________________________________________________________________
void MethodMLP::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodMLP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodMLP::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodMLP::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodMLP(void *p) {
      delete ((::TMVA::MethodMLP*)p);
   }
   static void deleteArray_TMVAcLcLMethodMLP(void *p) {
      delete [] ((::TMVA::MethodMLP*)p);
   }
   static void destruct_TMVAcLcLMethodMLP(void *p) {
      typedef ::TMVA::MethodMLP current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodMLP

namespace TMVA {
//______________________________________________________________________________
void MethodBoost::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodBoost.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodBoost::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodBoost::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodBoost(void *p) {
      delete ((::TMVA::MethodBoost*)p);
   }
   static void deleteArray_TMVAcLcLMethodBoost(void *p) {
      delete [] ((::TMVA::MethodBoost*)p);
   }
   static void destruct_TMVAcLcLMethodBoost(void *p) {
      typedef ::TMVA::MethodBoost current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodBoost

namespace TMVA {
//______________________________________________________________________________
void MethodPDEFoam::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodPDEFoam.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodPDEFoam::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodPDEFoam::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodPDEFoam(void *p) {
      delete ((::TMVA::MethodPDEFoam*)p);
   }
   static void deleteArray_TMVAcLcLMethodPDEFoam(void *p) {
      delete [] ((::TMVA::MethodPDEFoam*)p);
   }
   static void destruct_TMVAcLcLMethodPDEFoam(void *p) {
      typedef ::TMVA::MethodPDEFoam current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodPDEFoam

namespace TMVA {
//______________________________________________________________________________
void MethodLD::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodLD.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodLD::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodLD::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodLD(void *p) {
      delete ((::TMVA::MethodLD*)p);
   }
   static void deleteArray_TMVAcLcLMethodLD(void *p) {
      delete [] ((::TMVA::MethodLD*)p);
   }
   static void destruct_TMVAcLcLMethodLD(void *p) {
      typedef ::TMVA::MethodLD current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodLD

namespace TMVA {
//______________________________________________________________________________
void MethodCategory::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MethodCategory.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MethodCategory::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MethodCategory::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLMethodCategory(void *p) {
      delete ((::TMVA::MethodCategory*)p);
   }
   static void deleteArray_TMVAcLcLMethodCategory(void *p) {
      delete [] ((::TMVA::MethodCategory*)p);
   }
   static void destruct_TMVAcLcLMethodCategory(void *p) {
      typedef ::TMVA::MethodCategory current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MethodCategory

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 214,
                  typeid(vector<float>), DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEfloatmUgR_Dictionary();
   static void vectorlEfloatmUgR_TClassManip(TClass*);
   static void *new_vectorlEfloatmUgR(void *p = 0);
   static void *newArray_vectorlEfloatmUgR(Long_t size, void *p);
   static void delete_vectorlEfloatmUgR(void *p);
   static void deleteArray_vectorlEfloatmUgR(void *p);
   static void destruct_vectorlEfloatmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float*>*)
   {
      vector<float*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float*>", -2, "vector", 214,
                  typeid(vector<float*>), DefineBehavior(ptr, ptr),
                  &vectorlEfloatmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float*>) );
      instance.SetNew(&new_vectorlEfloatmUgR);
      instance.SetNewArray(&newArray_vectorlEfloatmUgR);
      instance.SetDelete(&delete_vectorlEfloatmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatmUgR);
      instance.SetDestructor(&destruct_vectorlEfloatmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float*>*)0x0)->GetClass();
      vectorlEfloatmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float*> : new vector<float*>;
   }
   static void *newArray_vectorlEfloatmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float*>[nElements] : new vector<float*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatmUgR(void *p) {
      delete ((vector<float*>*)p);
   }
   static void deleteArray_vectorlEfloatmUgR(void *p) {
      delete [] ((vector<float*>*)p);
   }
   static void destruct_vectorlEfloatmUgR(void *p) {
      typedef vector<float*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float*>

namespace {
  void TriggerDictionaryInitialization_dict1_Impl() {
    static const char* headers[] = {
"inc/TMVA/Configurable.h",
"inc/TMVA/Event.h",
"inc/TMVA/Factory.h",
"inc/TMVA/MethodBase.h",
"inc/TMVA/MethodCompositeBase.h",
"inc/TMVA/MethodANNBase.h",
"inc/TMVA/MethodTMlpANN.h",
"inc/TMVA/MethodRuleFit.h",
"inc/TMVA/MethodCuts.h",
"inc/TMVA/MethodFisher.h",
"inc/TMVA/MethodKNN.h",
"inc/TMVA/MethodCFMlpANN.h",
"inc/TMVA/MethodCFMlpANN_Utils.h",
"inc/TMVA/MethodLikelihood.h",
"inc/TMVA/MethodHMatrix.h",
"inc/TMVA/MethodPDERS.h",
"inc/TMVA/MethodBDT.h",
"inc/TMVA/MethodDT.h",
"inc/TMVA/MethodSVM.h",
"inc/TMVA/MethodBayesClassifier.h",
"inc/TMVA/MethodFDA.h",
"inc/TMVA/MethodMLP.h",
"inc/TMVA/MethodBoost.h",
"inc/TMVA/MethodPDEFoam.h",
"inc/TMVA/MethodLD.h",
"inc/TMVA/MethodCategory.h",
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
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Virtual base class for all TMVA method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Configurable.h")))  Configurable;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/Event.h")))  Event;}
namespace TMVA{namespace kNN{class __attribute__((annotate("$clingAutoload$inc/TMVA/MethodKNN.h")))  Event;}}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(The factory creates all MVA methods, and performs their training and testing)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Factory.h")))  Factory;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Virtual base class for all TMVA method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodBase.h")))  MethodBase;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/MethodCompositeBase.h")))  MethodCompositeBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Base class for TMVA ANNs)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodANNBase.h")))  MethodANNBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of interface for TMultiLayerPerceptron)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodTMlpANN.h")))  MethodTMlpANN;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Friedman's RuleFit method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodRuleFit.h")))  MethodRuleFit;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Multivariate optimisation of signal efficiency)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodCuts.h")))  MethodCuts;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Analysis of Fisher discriminant (Fisher or Mahalanobis approach))ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodFisher.h")))  MethodFisher;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(k Nearest Neighbour classifier)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodKNN.h")))  MethodKNN;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface for Clermond-Ferrand artificial neural network)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodCFMlpANN.h")))  MethodCFMlpANN;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of Clermond-Ferrand artificial neural network)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodCFMlpANN.h")))  MethodCFMlpANN_Utils;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Likelihood analysis ("non-parametric approach"))ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodLikelihood.h")))  MethodLikelihood;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(H-Matrix method, a simple comparison of chi-squared estimators for signal and background)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodHMatrix.h")))  MethodHMatrix;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Multi-dimensional probability density estimator range search (PDERS) method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodPDERS.h")))  MethodPDERS;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Analysis of Boosted Decision Trees)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodBDT.h")))  MethodBDT;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Analysis of Decision Trees)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodDT.h")))  MethodDT;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Support Vector Machine)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodSVM.h")))  MethodSVM;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Friedman's BayesClassifier method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodBayesClassifier.h")))  MethodBayesClassifier;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Function Discriminant Analysis)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodFDA.h")))  MethodFDA;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Multi-layer perceptron implemented specifically for TMVA)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodMLP.h")))  MethodMLP;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/MethodBoost.h")))  MethodBoost;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Multi-dimensional probability density estimator using TFoam (PDE-Foam))ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodPDEFoam.h")))  MethodPDEFoam;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Linear discriminant analysis)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MethodLD.h")))  MethodLD;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/MethodCategory.h")))  MethodCategory;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "inc/TMVA/Configurable.h"
#include "inc/TMVA/Event.h"
#include "inc/TMVA/Factory.h"
#include "inc/TMVA/MethodBase.h"
#include "inc/TMVA/MethodCompositeBase.h"
#include "inc/TMVA/MethodANNBase.h"
#include "inc/TMVA/MethodTMlpANN.h"
#include "inc/TMVA/MethodRuleFit.h"
#include "inc/TMVA/MethodCuts.h"
#include "inc/TMVA/MethodFisher.h"
#include "inc/TMVA/MethodKNN.h"
#include "inc/TMVA/MethodCFMlpANN.h"
#include "inc/TMVA/MethodCFMlpANN_Utils.h"
#include "inc/TMVA/MethodLikelihood.h"
#include "inc/TMVA/MethodHMatrix.h"
#include "inc/TMVA/MethodPDERS.h"
#include "inc/TMVA/MethodBDT.h"
#include "inc/TMVA/MethodDT.h"
#include "inc/TMVA/MethodSVM.h"
#include "inc/TMVA/MethodBayesClassifier.h"
#include "inc/TMVA/MethodFDA.h"
#include "inc/TMVA/MethodMLP.h"
#include "inc/TMVA/MethodBoost.h"
#include "inc/TMVA/MethodPDEFoam.h"
#include "inc/TMVA/MethodLD.h"
#include "inc/TMVA/MethodCategory.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TMVA::Configurable", payloadCode, "@",
"TMVA::Event", payloadCode, "@",
"TMVA::Factory", payloadCode, "@",
"TMVA::MethodANNBase", payloadCode, "@",
"TMVA::MethodBDT", payloadCode, "@",
"TMVA::MethodBase", payloadCode, "@",
"TMVA::MethodBayesClassifier", payloadCode, "@",
"TMVA::MethodBoost", payloadCode, "@",
"TMVA::MethodCFMlpANN", payloadCode, "@",
"TMVA::MethodCFMlpANN_Utils", payloadCode, "@",
"TMVA::MethodCategory", payloadCode, "@",
"TMVA::MethodCompositeBase", payloadCode, "@",
"TMVA::MethodCuts", payloadCode, "@",
"TMVA::MethodDT", payloadCode, "@",
"TMVA::MethodFDA", payloadCode, "@",
"TMVA::MethodFisher", payloadCode, "@",
"TMVA::MethodHMatrix", payloadCode, "@",
"TMVA::MethodKNN", payloadCode, "@",
"TMVA::MethodLD", payloadCode, "@",
"TMVA::MethodLikelihood", payloadCode, "@",
"TMVA::MethodMLP", payloadCode, "@",
"TMVA::MethodPDEFoam", payloadCode, "@",
"TMVA::MethodPDERS", payloadCode, "@",
"TMVA::MethodRuleFit", payloadCode, "@",
"TMVA::MethodSVM", payloadCode, "@",
"TMVA::MethodTMlpANN", payloadCode, "@",
"TMVA::kNN::Event", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dict1",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict1_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict1_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict1() {
  TriggerDictionaryInitialization_dict1_Impl();
}
