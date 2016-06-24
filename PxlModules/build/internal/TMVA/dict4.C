// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedImatthiasdIAnalysisdISSX13dISSXdIPxlModulesdIbuilddIinternaldITMVAdIdict4

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
#include "inc/TMVA/TNeuron.h"
#include "inc/TMVA/TSynapse.h"
#include "inc/TMVA/TActivationChooser.h"
#include "inc/TMVA/TActivation.h"
#include "inc/TMVA/TActivationSigmoid.h"
#include "inc/TMVA/TActivationIdentity.h"
#include "inc/TMVA/TActivationTanh.h"
#include "inc/TMVA/TActivationRadial.h"
#include "inc/TMVA/TNeuronInputChooser.h"
#include "inc/TMVA/TNeuronInput.h"
#include "inc/TMVA/TNeuronInputSum.h"
#include "inc/TMVA/TNeuronInputSqSum.h"
#include "inc/TMVA/TNeuronInputAbs.h"
#include "inc/TMVA/Types.h"
#include "inc/TMVA/Ranking.h"
#include "inc/TMVA/RuleFit.h"
#include "inc/TMVA/RuleFitAPI.h"
#include "inc/TMVA/IMethod.h"
#include "inc/TMVA/MsgLogger.h"
#include "inc/TMVA/VariableTransformBase.h"
#include "inc/TMVA/VariableIdentityTransform.h"
#include "inc/TMVA/VariableDecorrTransform.h"
#include "inc/TMVA/VariablePCATransform.h"
#include "inc/TMVA/VariableGaussTransform.h"
#include "inc/TMVA/VariableNormalizeTransform.h"
#include "inc/TMVA/VariableRearrangeTransform.h"

// Header files passed via #pragma extra_include

namespace TMVA {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *TMVA_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("TMVA", 0 /*version*/, "TMVA/TSynapse.h", 43,
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
   static void *new_TMVAcLcLTNeuron(void *p = 0);
   static void *newArray_TMVAcLcLTNeuron(Long_t size, void *p);
   static void delete_TMVAcLcLTNeuron(void *p);
   static void deleteArray_TMVAcLcLTNeuron(void *p);
   static void destruct_TMVAcLcLTNeuron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TNeuron*)
   {
      ::TMVA::TNeuron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TNeuron >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TNeuron", ::TMVA::TNeuron::Class_Version(), "inc/TMVA/TNeuron.h", 61,
                  typeid(::TMVA::TNeuron), DefineBehavior(ptr, ptr),
                  &::TMVA::TNeuron::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TNeuron) );
      instance.SetNew(&new_TMVAcLcLTNeuron);
      instance.SetNewArray(&newArray_TMVAcLcLTNeuron);
      instance.SetDelete(&delete_TMVAcLcLTNeuron);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTNeuron);
      instance.SetDestructor(&destruct_TMVAcLcLTNeuron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TNeuron*)
   {
      return GenerateInitInstanceLocal((::TMVA::TNeuron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TNeuron*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTSynapse(void *p = 0);
   static void *newArray_TMVAcLcLTSynapse(Long_t size, void *p);
   static void delete_TMVAcLcLTSynapse(void *p);
   static void deleteArray_TMVAcLcLTSynapse(void *p);
   static void destruct_TMVAcLcLTSynapse(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TSynapse*)
   {
      ::TMVA::TSynapse *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TSynapse >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TSynapse", ::TMVA::TSynapse::Class_Version(), "TMVA/TSynapse.h", 48,
                  typeid(::TMVA::TSynapse), DefineBehavior(ptr, ptr),
                  &::TMVA::TSynapse::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TSynapse) );
      instance.SetNew(&new_TMVAcLcLTSynapse);
      instance.SetNewArray(&newArray_TMVAcLcLTSynapse);
      instance.SetDelete(&delete_TMVAcLcLTSynapse);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTSynapse);
      instance.SetDestructor(&destruct_TMVAcLcLTSynapse);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TSynapse*)
   {
      return GenerateInitInstanceLocal((::TMVA::TSynapse*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TSynapse*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTActivationChooser(void *p = 0);
   static void *newArray_TMVAcLcLTActivationChooser(Long_t size, void *p);
   static void delete_TMVAcLcLTActivationChooser(void *p);
   static void deleteArray_TMVAcLcLTActivationChooser(void *p);
   static void destruct_TMVAcLcLTActivationChooser(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TActivationChooser*)
   {
      ::TMVA::TActivationChooser *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TActivationChooser >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TActivationChooser", ::TMVA::TActivationChooser::Class_Version(), "inc/TMVA/TActivationChooser.h", 46,
                  typeid(::TMVA::TActivationChooser), DefineBehavior(ptr, ptr),
                  &::TMVA::TActivationChooser::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TActivationChooser) );
      instance.SetNew(&new_TMVAcLcLTActivationChooser);
      instance.SetNewArray(&newArray_TMVAcLcLTActivationChooser);
      instance.SetDelete(&delete_TMVAcLcLTActivationChooser);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTActivationChooser);
      instance.SetDestructor(&destruct_TMVAcLcLTActivationChooser);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TActivationChooser*)
   {
      return GenerateInitInstanceLocal((::TMVA::TActivationChooser*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TActivationChooser*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLTActivation(void *p);
   static void deleteArray_TMVAcLcLTActivation(void *p);
   static void destruct_TMVAcLcLTActivation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TActivation*)
   {
      ::TMVA::TActivation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TActivation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TActivation", ::TMVA::TActivation::Class_Version(), "TMVA/TActivation.h", 46,
                  typeid(::TMVA::TActivation), DefineBehavior(ptr, ptr),
                  &::TMVA::TActivation::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TActivation) );
      instance.SetDelete(&delete_TMVAcLcLTActivation);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTActivation);
      instance.SetDestructor(&destruct_TMVAcLcLTActivation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TActivation*)
   {
      return GenerateInitInstanceLocal((::TMVA::TActivation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TActivation*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTActivationSigmoid(void *p = 0);
   static void *newArray_TMVAcLcLTActivationSigmoid(Long_t size, void *p);
   static void delete_TMVAcLcLTActivationSigmoid(void *p);
   static void deleteArray_TMVAcLcLTActivationSigmoid(void *p);
   static void destruct_TMVAcLcLTActivationSigmoid(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TActivationSigmoid*)
   {
      ::TMVA::TActivationSigmoid *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TActivationSigmoid >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TActivationSigmoid", ::TMVA::TActivationSigmoid::Class_Version(), "inc/TMVA/TActivationSigmoid.h", 48,
                  typeid(::TMVA::TActivationSigmoid), DefineBehavior(ptr, ptr),
                  &::TMVA::TActivationSigmoid::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TActivationSigmoid) );
      instance.SetNew(&new_TMVAcLcLTActivationSigmoid);
      instance.SetNewArray(&newArray_TMVAcLcLTActivationSigmoid);
      instance.SetDelete(&delete_TMVAcLcLTActivationSigmoid);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTActivationSigmoid);
      instance.SetDestructor(&destruct_TMVAcLcLTActivationSigmoid);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TActivationSigmoid*)
   {
      return GenerateInitInstanceLocal((::TMVA::TActivationSigmoid*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TActivationSigmoid*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTActivationIdentity(void *p = 0);
   static void *newArray_TMVAcLcLTActivationIdentity(Long_t size, void *p);
   static void delete_TMVAcLcLTActivationIdentity(void *p);
   static void deleteArray_TMVAcLcLTActivationIdentity(void *p);
   static void destruct_TMVAcLcLTActivationIdentity(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TActivationIdentity*)
   {
      ::TMVA::TActivationIdentity *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TActivationIdentity >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TActivationIdentity", ::TMVA::TActivationIdentity::Class_Version(), "inc/TMVA/TActivationIdentity.h", 48,
                  typeid(::TMVA::TActivationIdentity), DefineBehavior(ptr, ptr),
                  &::TMVA::TActivationIdentity::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TActivationIdentity) );
      instance.SetNew(&new_TMVAcLcLTActivationIdentity);
      instance.SetNewArray(&newArray_TMVAcLcLTActivationIdentity);
      instance.SetDelete(&delete_TMVAcLcLTActivationIdentity);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTActivationIdentity);
      instance.SetDestructor(&destruct_TMVAcLcLTActivationIdentity);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TActivationIdentity*)
   {
      return GenerateInitInstanceLocal((::TMVA::TActivationIdentity*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TActivationIdentity*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTActivationTanh(void *p = 0);
   static void *newArray_TMVAcLcLTActivationTanh(Long_t size, void *p);
   static void delete_TMVAcLcLTActivationTanh(void *p);
   static void deleteArray_TMVAcLcLTActivationTanh(void *p);
   static void destruct_TMVAcLcLTActivationTanh(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TActivationTanh*)
   {
      ::TMVA::TActivationTanh *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TActivationTanh >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TActivationTanh", ::TMVA::TActivationTanh::Class_Version(), "inc/TMVA/TActivationTanh.h", 48,
                  typeid(::TMVA::TActivationTanh), DefineBehavior(ptr, ptr),
                  &::TMVA::TActivationTanh::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TActivationTanh) );
      instance.SetNew(&new_TMVAcLcLTActivationTanh);
      instance.SetNewArray(&newArray_TMVAcLcLTActivationTanh);
      instance.SetDelete(&delete_TMVAcLcLTActivationTanh);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTActivationTanh);
      instance.SetDestructor(&destruct_TMVAcLcLTActivationTanh);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TActivationTanh*)
   {
      return GenerateInitInstanceLocal((::TMVA::TActivationTanh*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TActivationTanh*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTActivationRadial(void *p = 0);
   static void *newArray_TMVAcLcLTActivationRadial(Long_t size, void *p);
   static void delete_TMVAcLcLTActivationRadial(void *p);
   static void deleteArray_TMVAcLcLTActivationRadial(void *p);
   static void destruct_TMVAcLcLTActivationRadial(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TActivationRadial*)
   {
      ::TMVA::TActivationRadial *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TActivationRadial >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TActivationRadial", ::TMVA::TActivationRadial::Class_Version(), "inc/TMVA/TActivationRadial.h", 48,
                  typeid(::TMVA::TActivationRadial), DefineBehavior(ptr, ptr),
                  &::TMVA::TActivationRadial::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TActivationRadial) );
      instance.SetNew(&new_TMVAcLcLTActivationRadial);
      instance.SetNewArray(&newArray_TMVAcLcLTActivationRadial);
      instance.SetDelete(&delete_TMVAcLcLTActivationRadial);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTActivationRadial);
      instance.SetDestructor(&destruct_TMVAcLcLTActivationRadial);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TActivationRadial*)
   {
      return GenerateInitInstanceLocal((::TMVA::TActivationRadial*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TActivationRadial*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTNeuronInputChooser(void *p = 0);
   static void *newArray_TMVAcLcLTNeuronInputChooser(Long_t size, void *p);
   static void delete_TMVAcLcLTNeuronInputChooser(void *p);
   static void deleteArray_TMVAcLcLTNeuronInputChooser(void *p);
   static void destruct_TMVAcLcLTNeuronInputChooser(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TNeuronInputChooser*)
   {
      ::TMVA::TNeuronInputChooser *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TNeuronInputChooser >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TNeuronInputChooser", ::TMVA::TNeuronInputChooser::Class_Version(), "inc/TMVA/TNeuronInputChooser.h", 66,
                  typeid(::TMVA::TNeuronInputChooser), DefineBehavior(ptr, ptr),
                  &::TMVA::TNeuronInputChooser::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TNeuronInputChooser) );
      instance.SetNew(&new_TMVAcLcLTNeuronInputChooser);
      instance.SetNewArray(&newArray_TMVAcLcLTNeuronInputChooser);
      instance.SetDelete(&delete_TMVAcLcLTNeuronInputChooser);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTNeuronInputChooser);
      instance.SetDestructor(&destruct_TMVAcLcLTNeuronInputChooser);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TNeuronInputChooser*)
   {
      return GenerateInitInstanceLocal((::TMVA::TNeuronInputChooser*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TNeuronInputChooser*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLTNeuronInput(void *p);
   static void deleteArray_TMVAcLcLTNeuronInput(void *p);
   static void destruct_TMVAcLcLTNeuronInput(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TNeuronInput*)
   {
      ::TMVA::TNeuronInput *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TNeuronInput >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TNeuronInput", ::TMVA::TNeuronInput::Class_Version(), "TMVA/TNeuronInput.h", 46,
                  typeid(::TMVA::TNeuronInput), DefineBehavior(ptr, ptr),
                  &::TMVA::TNeuronInput::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TNeuronInput) );
      instance.SetDelete(&delete_TMVAcLcLTNeuronInput);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTNeuronInput);
      instance.SetDestructor(&destruct_TMVAcLcLTNeuronInput);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TNeuronInput*)
   {
      return GenerateInitInstanceLocal((::TMVA::TNeuronInput*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TNeuronInput*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTNeuronInputSum(void *p = 0);
   static void *newArray_TMVAcLcLTNeuronInputSum(Long_t size, void *p);
   static void delete_TMVAcLcLTNeuronInputSum(void *p);
   static void deleteArray_TMVAcLcLTNeuronInputSum(void *p);
   static void destruct_TMVAcLcLTNeuronInputSum(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TNeuronInputSum*)
   {
      ::TMVA::TNeuronInputSum *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TNeuronInputSum >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TNeuronInputSum", ::TMVA::TNeuronInputSum::Class_Version(), "inc/TMVA/TNeuronInputSum.h", 52,
                  typeid(::TMVA::TNeuronInputSum), DefineBehavior(ptr, ptr),
                  &::TMVA::TNeuronInputSum::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TNeuronInputSum) );
      instance.SetNew(&new_TMVAcLcLTNeuronInputSum);
      instance.SetNewArray(&newArray_TMVAcLcLTNeuronInputSum);
      instance.SetDelete(&delete_TMVAcLcLTNeuronInputSum);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTNeuronInputSum);
      instance.SetDestructor(&destruct_TMVAcLcLTNeuronInputSum);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TNeuronInputSum*)
   {
      return GenerateInitInstanceLocal((::TMVA::TNeuronInputSum*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSum*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTNeuronInputSqSum(void *p = 0);
   static void *newArray_TMVAcLcLTNeuronInputSqSum(Long_t size, void *p);
   static void delete_TMVAcLcLTNeuronInputSqSum(void *p);
   static void deleteArray_TMVAcLcLTNeuronInputSqSum(void *p);
   static void destruct_TMVAcLcLTNeuronInputSqSum(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TNeuronInputSqSum*)
   {
      ::TMVA::TNeuronInputSqSum *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TNeuronInputSqSum >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TNeuronInputSqSum", ::TMVA::TNeuronInputSqSum::Class_Version(), "inc/TMVA/TNeuronInputSqSum.h", 54,
                  typeid(::TMVA::TNeuronInputSqSum), DefineBehavior(ptr, ptr),
                  &::TMVA::TNeuronInputSqSum::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TNeuronInputSqSum) );
      instance.SetNew(&new_TMVAcLcLTNeuronInputSqSum);
      instance.SetNewArray(&newArray_TMVAcLcLTNeuronInputSqSum);
      instance.SetDelete(&delete_TMVAcLcLTNeuronInputSqSum);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTNeuronInputSqSum);
      instance.SetDestructor(&destruct_TMVAcLcLTNeuronInputSqSum);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TNeuronInputSqSum*)
   {
      return GenerateInitInstanceLocal((::TMVA::TNeuronInputSqSum*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSqSum*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTNeuronInputAbs(void *p = 0);
   static void *newArray_TMVAcLcLTNeuronInputAbs(Long_t size, void *p);
   static void delete_TMVAcLcLTNeuronInputAbs(void *p);
   static void deleteArray_TMVAcLcLTNeuronInputAbs(void *p);
   static void destruct_TMVAcLcLTNeuronInputAbs(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TNeuronInputAbs*)
   {
      ::TMVA::TNeuronInputAbs *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TNeuronInputAbs >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TNeuronInputAbs", ::TMVA::TNeuronInputAbs::Class_Version(), "inc/TMVA/TNeuronInputAbs.h", 70,
                  typeid(::TMVA::TNeuronInputAbs), DefineBehavior(ptr, ptr),
                  &::TMVA::TNeuronInputAbs::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TNeuronInputAbs) );
      instance.SetNew(&new_TMVAcLcLTNeuronInputAbs);
      instance.SetNewArray(&newArray_TMVAcLcLTNeuronInputAbs);
      instance.SetDelete(&delete_TMVAcLcLTNeuronInputAbs);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTNeuronInputAbs);
      instance.SetDestructor(&destruct_TMVAcLcLTNeuronInputAbs);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TNeuronInputAbs*)
   {
      return GenerateInitInstanceLocal((::TMVA::TNeuronInputAbs*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TNeuronInputAbs*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLTypes_Dictionary();
   static void TMVAcLcLTypes_TClassManip(TClass*);
   static void delete_TMVAcLcLTypes(void *p);
   static void deleteArray_TMVAcLcLTypes(void *p);
   static void destruct_TMVAcLcLTypes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Types*)
   {
      ::TMVA::Types *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::Types));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Types", "TMVA/Types.h", 74,
                  typeid(::TMVA::Types), DefineBehavior(ptr, ptr),
                  &TMVAcLcLTypes_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Types) );
      instance.SetDelete(&delete_TMVAcLcLTypes);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTypes);
      instance.SetDestructor(&destruct_TMVAcLcLTypes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Types*)
   {
      return GenerateInitInstanceLocal((::TMVA::Types*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Types*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLTypes_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::Types*)0x0)->GetClass();
      TMVAcLcLTypes_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLTypes_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLRanking(void *p = 0);
   static void *newArray_TMVAcLcLRanking(Long_t size, void *p);
   static void delete_TMVAcLcLRanking(void *p);
   static void deleteArray_TMVAcLcLRanking(void *p);
   static void destruct_TMVAcLcLRanking(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Ranking*)
   {
      ::TMVA::Ranking *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Ranking >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Ranking", ::TMVA::Ranking::Class_Version(), "inc/TMVA/Ranking.h", 50,
                  typeid(::TMVA::Ranking), DefineBehavior(ptr, ptr),
                  &::TMVA::Ranking::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Ranking) );
      instance.SetNew(&new_TMVAcLcLRanking);
      instance.SetNewArray(&newArray_TMVAcLcLRanking);
      instance.SetDelete(&delete_TMVAcLcLRanking);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLRanking);
      instance.SetDestructor(&destruct_TMVAcLcLRanking);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Ranking*)
   {
      return GenerateInitInstanceLocal((::TMVA::Ranking*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Ranking*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLRuleFit(void *p = 0);
   static void *newArray_TMVAcLcLRuleFit(Long_t size, void *p);
   static void delete_TMVAcLcLRuleFit(void *p);
   static void deleteArray_TMVAcLcLRuleFit(void *p);
   static void destruct_TMVAcLcLRuleFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::RuleFit*)
   {
      ::TMVA::RuleFit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::RuleFit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::RuleFit", ::TMVA::RuleFit::Class_Version(), "inc/TMVA/RuleFit.h", 52,
                  typeid(::TMVA::RuleFit), DefineBehavior(ptr, ptr),
                  &::TMVA::RuleFit::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::RuleFit) );
      instance.SetNew(&new_TMVAcLcLRuleFit);
      instance.SetNewArray(&newArray_TMVAcLcLRuleFit);
      instance.SetDelete(&delete_TMVAcLcLRuleFit);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLRuleFit);
      instance.SetDestructor(&destruct_TMVAcLcLRuleFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::RuleFit*)
   {
      return GenerateInitInstanceLocal((::TMVA::RuleFit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::RuleFit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLRuleFitAPI(void *p);
   static void deleteArray_TMVAcLcLRuleFitAPI(void *p);
   static void destruct_TMVAcLcLRuleFitAPI(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::RuleFitAPI*)
   {
      ::TMVA::RuleFitAPI *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::RuleFitAPI >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::RuleFitAPI", ::TMVA::RuleFitAPI::Class_Version(), "inc/TMVA/RuleFitAPI.h", 50,
                  typeid(::TMVA::RuleFitAPI), DefineBehavior(ptr, ptr),
                  &::TMVA::RuleFitAPI::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::RuleFitAPI) );
      instance.SetDelete(&delete_TMVAcLcLRuleFitAPI);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLRuleFitAPI);
      instance.SetDestructor(&destruct_TMVAcLcLRuleFitAPI);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::RuleFitAPI*)
   {
      return GenerateInitInstanceLocal((::TMVA::RuleFitAPI*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::RuleFitAPI*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLIMethod(void *p);
   static void deleteArray_TMVAcLcLIMethod(void *p);
   static void destruct_TMVAcLcLIMethod(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::IMethod*)
   {
      ::TMVA::IMethod *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::IMethod >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::IMethod", ::TMVA::IMethod::Class_Version(), "inc/TMVA/IMethod.h", 62,
                  typeid(::TMVA::IMethod), DefineBehavior(ptr, ptr),
                  &::TMVA::IMethod::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::IMethod) );
      instance.SetDelete(&delete_TMVAcLcLIMethod);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLIMethod);
      instance.SetDestructor(&destruct_TMVAcLcLIMethod);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::IMethod*)
   {
      return GenerateInitInstanceLocal((::TMVA::IMethod*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::IMethod*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLMsgLogger(void *p = 0);
   static void *newArray_TMVAcLcLMsgLogger(Long_t size, void *p);
   static void delete_TMVAcLcLMsgLogger(void *p);
   static void deleteArray_TMVAcLcLMsgLogger(void *p);
   static void destruct_TMVAcLcLMsgLogger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MsgLogger*)
   {
      ::TMVA::MsgLogger *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MsgLogger >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MsgLogger", ::TMVA::MsgLogger::Class_Version(), "TMVA/MsgLogger.h", 63,
                  typeid(::TMVA::MsgLogger), DefineBehavior(ptr, ptr),
                  &::TMVA::MsgLogger::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MsgLogger) );
      instance.SetNew(&new_TMVAcLcLMsgLogger);
      instance.SetNewArray(&newArray_TMVAcLcLMsgLogger);
      instance.SetDelete(&delete_TMVAcLcLMsgLogger);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMsgLogger);
      instance.SetDestructor(&destruct_TMVAcLcLMsgLogger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MsgLogger*)
   {
      return GenerateInitInstanceLocal((::TMVA::MsgLogger*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MsgLogger*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariableTransformBase(void *p);
   static void deleteArray_TMVAcLcLVariableTransformBase(void *p);
   static void destruct_TMVAcLcLVariableTransformBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariableTransformBase*)
   {
      ::TMVA::VariableTransformBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariableTransformBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariableTransformBase", ::TMVA::VariableTransformBase::Class_Version(), "inc/TMVA/VariableTransformBase.h", 67,
                  typeid(::TMVA::VariableTransformBase), DefineBehavior(ptr, ptr),
                  &::TMVA::VariableTransformBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariableTransformBase) );
      instance.SetDelete(&delete_TMVAcLcLVariableTransformBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariableTransformBase);
      instance.SetDestructor(&destruct_TMVAcLcLVariableTransformBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariableTransformBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariableTransformBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariableTransformBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariableIdentityTransform(void *p);
   static void deleteArray_TMVAcLcLVariableIdentityTransform(void *p);
   static void destruct_TMVAcLcLVariableIdentityTransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariableIdentityTransform*)
   {
      ::TMVA::VariableIdentityTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariableIdentityTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariableIdentityTransform", ::TMVA::VariableIdentityTransform::Class_Version(), "inc/TMVA/VariableIdentityTransform.h", 45,
                  typeid(::TMVA::VariableIdentityTransform), DefineBehavior(ptr, ptr),
                  &::TMVA::VariableIdentityTransform::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariableIdentityTransform) );
      instance.SetDelete(&delete_TMVAcLcLVariableIdentityTransform);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariableIdentityTransform);
      instance.SetDestructor(&destruct_TMVAcLcLVariableIdentityTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariableIdentityTransform*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariableIdentityTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariableIdentityTransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariableDecorrTransform(void *p);
   static void deleteArray_TMVAcLcLVariableDecorrTransform(void *p);
   static void destruct_TMVAcLcLVariableDecorrTransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariableDecorrTransform*)
   {
      ::TMVA::VariableDecorrTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariableDecorrTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariableDecorrTransform", ::TMVA::VariableDecorrTransform::Class_Version(), "inc/TMVA/VariableDecorrTransform.h", 53,
                  typeid(::TMVA::VariableDecorrTransform), DefineBehavior(ptr, ptr),
                  &::TMVA::VariableDecorrTransform::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariableDecorrTransform) );
      instance.SetDelete(&delete_TMVAcLcLVariableDecorrTransform);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariableDecorrTransform);
      instance.SetDestructor(&destruct_TMVAcLcLVariableDecorrTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariableDecorrTransform*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariableDecorrTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariableDecorrTransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariablePCATransform(void *p);
   static void deleteArray_TMVAcLcLVariablePCATransform(void *p);
   static void destruct_TMVAcLcLVariablePCATransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariablePCATransform*)
   {
      ::TMVA::VariablePCATransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariablePCATransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariablePCATransform", ::TMVA::VariablePCATransform::Class_Version(), "inc/TMVA/VariablePCATransform.h", 50,
                  typeid(::TMVA::VariablePCATransform), DefineBehavior(ptr, ptr),
                  &::TMVA::VariablePCATransform::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariablePCATransform) );
      instance.SetDelete(&delete_TMVAcLcLVariablePCATransform);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariablePCATransform);
      instance.SetDestructor(&destruct_TMVAcLcLVariablePCATransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariablePCATransform*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariablePCATransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariablePCATransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariableGaussTransform(void *p);
   static void deleteArray_TMVAcLcLVariableGaussTransform(void *p);
   static void destruct_TMVAcLcLVariableGaussTransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariableGaussTransform*)
   {
      ::TMVA::VariableGaussTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariableGaussTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariableGaussTransform", ::TMVA::VariableGaussTransform::Class_Version(), "inc/TMVA/VariableGaussTransform.h", 86,
                  typeid(::TMVA::VariableGaussTransform), DefineBehavior(ptr, ptr),
                  &::TMVA::VariableGaussTransform::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariableGaussTransform) );
      instance.SetDelete(&delete_TMVAcLcLVariableGaussTransform);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariableGaussTransform);
      instance.SetDestructor(&destruct_TMVAcLcLVariableGaussTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariableGaussTransform*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariableGaussTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariableGaussTransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariableNormalizeTransform(void *p);
   static void deleteArray_TMVAcLcLVariableNormalizeTransform(void *p);
   static void destruct_TMVAcLcLVariableNormalizeTransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariableNormalizeTransform*)
   {
      ::TMVA::VariableNormalizeTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariableNormalizeTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariableNormalizeTransform", ::TMVA::VariableNormalizeTransform::Class_Version(), "inc/TMVA/VariableNormalizeTransform.h", 50,
                  typeid(::TMVA::VariableNormalizeTransform), DefineBehavior(ptr, ptr),
                  &::TMVA::VariableNormalizeTransform::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariableNormalizeTransform) );
      instance.SetDelete(&delete_TMVAcLcLVariableNormalizeTransform);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariableNormalizeTransform);
      instance.SetDestructor(&destruct_TMVAcLcLVariableNormalizeTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariableNormalizeTransform*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariableNormalizeTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariableNormalizeTransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLVariableRearrangeTransform(void *p);
   static void deleteArray_TMVAcLcLVariableRearrangeTransform(void *p);
   static void destruct_TMVAcLcLVariableRearrangeTransform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::VariableRearrangeTransform*)
   {
      ::TMVA::VariableRearrangeTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::VariableRearrangeTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::VariableRearrangeTransform", ::TMVA::VariableRearrangeTransform::Class_Version(), "inc/TMVA/VariableRearrangeTransform.h", 43,
                  typeid(::TMVA::VariableRearrangeTransform), DefineBehavior(ptr, ptr),
                  &::TMVA::VariableRearrangeTransform::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::VariableRearrangeTransform) );
      instance.SetDelete(&delete_TMVAcLcLVariableRearrangeTransform);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLVariableRearrangeTransform);
      instance.SetDestructor(&destruct_TMVAcLcLVariableRearrangeTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::VariableRearrangeTransform*)
   {
      return GenerateInitInstanceLocal((::TMVA::VariableRearrangeTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::VariableRearrangeTransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TNeuron::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeuron::Class_Name()
{
   return "TMVA::TNeuron";
}

//______________________________________________________________________________
const char *TNeuron::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuron*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNeuron::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuron*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeuron::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuron*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeuron::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuron*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TSynapse::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSynapse::Class_Name()
{
   return "TMVA::TSynapse";
}

//______________________________________________________________________________
const char *TSynapse::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSynapse*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSynapse::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSynapse*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSynapse::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSynapse*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSynapse::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSynapse*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TActivationChooser::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TActivationChooser::Class_Name()
{
   return "TMVA::TActivationChooser";
}

//______________________________________________________________________________
const char *TActivationChooser::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationChooser*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TActivationChooser::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationChooser*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TActivationChooser::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationChooser*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TActivationChooser::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationChooser*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TActivation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TActivation::Class_Name()
{
   return "TMVA::TActivation";
}

//______________________________________________________________________________
const char *TActivation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TActivation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TActivation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TActivation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivation*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TActivationSigmoid::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TActivationSigmoid::Class_Name()
{
   return "TMVA::TActivationSigmoid";
}

//______________________________________________________________________________
const char *TActivationSigmoid::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationSigmoid*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TActivationSigmoid::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationSigmoid*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TActivationSigmoid::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationSigmoid*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TActivationSigmoid::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationSigmoid*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TActivationIdentity::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TActivationIdentity::Class_Name()
{
   return "TMVA::TActivationIdentity";
}

//______________________________________________________________________________
const char *TActivationIdentity::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationIdentity*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TActivationIdentity::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationIdentity*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TActivationIdentity::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationIdentity*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TActivationIdentity::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationIdentity*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TActivationTanh::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TActivationTanh::Class_Name()
{
   return "TMVA::TActivationTanh";
}

//______________________________________________________________________________
const char *TActivationTanh::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationTanh*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TActivationTanh::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationTanh*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TActivationTanh::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationTanh*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TActivationTanh::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationTanh*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TActivationRadial::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TActivationRadial::Class_Name()
{
   return "TMVA::TActivationRadial";
}

//______________________________________________________________________________
const char *TActivationRadial::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationRadial*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TActivationRadial::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationRadial*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TActivationRadial::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationRadial*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TActivationRadial::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TActivationRadial*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TNeuronInputChooser::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeuronInputChooser::Class_Name()
{
   return "TMVA::TNeuronInputChooser";
}

//______________________________________________________________________________
const char *TNeuronInputChooser::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputChooser*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNeuronInputChooser::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputChooser*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeuronInputChooser::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputChooser*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeuronInputChooser::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputChooser*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TNeuronInput::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeuronInput::Class_Name()
{
   return "TMVA::TNeuronInput";
}

//______________________________________________________________________________
const char *TNeuronInput::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInput*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNeuronInput::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInput*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeuronInput::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInput*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeuronInput::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInput*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TNeuronInputSum::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeuronInputSum::Class_Name()
{
   return "TMVA::TNeuronInputSum";
}

//______________________________________________________________________________
const char *TNeuronInputSum::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSum*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNeuronInputSum::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSum*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeuronInputSum::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSum*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeuronInputSum::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSum*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TNeuronInputSqSum::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeuronInputSqSum::Class_Name()
{
   return "TMVA::TNeuronInputSqSum";
}

//______________________________________________________________________________
const char *TNeuronInputSqSum::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSqSum*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNeuronInputSqSum::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSqSum*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeuronInputSqSum::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSqSum*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeuronInputSqSum::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputSqSum*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TNeuronInputAbs::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TNeuronInputAbs::Class_Name()
{
   return "TMVA::TNeuronInputAbs";
}

//______________________________________________________________________________
const char *TNeuronInputAbs::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputAbs*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TNeuronInputAbs::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputAbs*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TNeuronInputAbs::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputAbs*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TNeuronInputAbs::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TNeuronInputAbs*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Ranking::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Ranking::Class_Name()
{
   return "TMVA::Ranking";
}

//______________________________________________________________________________
const char *Ranking::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Ranking*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Ranking::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Ranking*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Ranking::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Ranking*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Ranking::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Ranking*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr RuleFit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RuleFit::Class_Name()
{
   return "TMVA::RuleFit";
}

//______________________________________________________________________________
const char *RuleFit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RuleFit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RuleFit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RuleFit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFit*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr RuleFitAPI::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RuleFitAPI::Class_Name()
{
   return "TMVA::RuleFitAPI";
}

//______________________________________________________________________________
const char *RuleFitAPI::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFitAPI*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RuleFitAPI::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFitAPI*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RuleFitAPI::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFitAPI*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RuleFitAPI::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RuleFitAPI*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr IMethod::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *IMethod::Class_Name()
{
   return "TMVA::IMethod";
}

//______________________________________________________________________________
const char *IMethod::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IMethod*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int IMethod::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IMethod*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *IMethod::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IMethod*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *IMethod::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::IMethod*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MsgLogger::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MsgLogger::Class_Name()
{
   return "TMVA::MsgLogger";
}

//______________________________________________________________________________
const char *MsgLogger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MsgLogger*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MsgLogger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MsgLogger*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MsgLogger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MsgLogger*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MsgLogger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MsgLogger*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariableTransformBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariableTransformBase::Class_Name()
{
   return "TMVA::VariableTransformBase";
}

//______________________________________________________________________________
const char *VariableTransformBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableTransformBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariableTransformBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableTransformBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariableTransformBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableTransformBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariableTransformBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableTransformBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariableIdentityTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariableIdentityTransform::Class_Name()
{
   return "TMVA::VariableIdentityTransform";
}

//______________________________________________________________________________
const char *VariableIdentityTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableIdentityTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariableIdentityTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableIdentityTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariableIdentityTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableIdentityTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariableIdentityTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableIdentityTransform*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariableDecorrTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariableDecorrTransform::Class_Name()
{
   return "TMVA::VariableDecorrTransform";
}

//______________________________________________________________________________
const char *VariableDecorrTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableDecorrTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariableDecorrTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableDecorrTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariableDecorrTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableDecorrTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariableDecorrTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableDecorrTransform*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariablePCATransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariablePCATransform::Class_Name()
{
   return "TMVA::VariablePCATransform";
}

//______________________________________________________________________________
const char *VariablePCATransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariablePCATransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariablePCATransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariablePCATransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariablePCATransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariablePCATransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariablePCATransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariablePCATransform*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariableGaussTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariableGaussTransform::Class_Name()
{
   return "TMVA::VariableGaussTransform";
}

//______________________________________________________________________________
const char *VariableGaussTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableGaussTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariableGaussTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableGaussTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariableGaussTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableGaussTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariableGaussTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableGaussTransform*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariableNormalizeTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariableNormalizeTransform::Class_Name()
{
   return "TMVA::VariableNormalizeTransform";
}

//______________________________________________________________________________
const char *VariableNormalizeTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableNormalizeTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariableNormalizeTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableNormalizeTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariableNormalizeTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableNormalizeTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariableNormalizeTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableNormalizeTransform*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr VariableRearrangeTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *VariableRearrangeTransform::Class_Name()
{
   return "TMVA::VariableRearrangeTransform";
}

//______________________________________________________________________________
const char *VariableRearrangeTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableRearrangeTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int VariableRearrangeTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableRearrangeTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VariableRearrangeTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableRearrangeTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VariableRearrangeTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::VariableRearrangeTransform*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
void TNeuron::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TNeuron.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TNeuron::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TNeuron::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTNeuron(void *p) {
      return  p ? new(p) ::TMVA::TNeuron : new ::TMVA::TNeuron;
   }
   static void *newArray_TMVAcLcLTNeuron(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::TNeuron[nElements] : new ::TMVA::TNeuron[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTNeuron(void *p) {
      delete ((::TMVA::TNeuron*)p);
   }
   static void deleteArray_TMVAcLcLTNeuron(void *p) {
      delete [] ((::TMVA::TNeuron*)p);
   }
   static void destruct_TMVAcLcLTNeuron(void *p) {
      typedef ::TMVA::TNeuron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TNeuron

namespace TMVA {
//______________________________________________________________________________
void TSynapse::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TSynapse.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TSynapse::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TSynapse::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTSynapse(void *p) {
      return  p ? new(p) ::TMVA::TSynapse : new ::TMVA::TSynapse;
   }
   static void *newArray_TMVAcLcLTSynapse(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::TSynapse[nElements] : new ::TMVA::TSynapse[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTSynapse(void *p) {
      delete ((::TMVA::TSynapse*)p);
   }
   static void deleteArray_TMVAcLcLTSynapse(void *p) {
      delete [] ((::TMVA::TSynapse*)p);
   }
   static void destruct_TMVAcLcLTSynapse(void *p) {
      typedef ::TMVA::TSynapse current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TSynapse

namespace TMVA {
//______________________________________________________________________________
void TActivationChooser::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TActivationChooser.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TActivationChooser::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TActivationChooser::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTActivationChooser(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationChooser : new ::TMVA::TActivationChooser;
   }
   static void *newArray_TMVAcLcLTActivationChooser(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationChooser[nElements] : new ::TMVA::TActivationChooser[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTActivationChooser(void *p) {
      delete ((::TMVA::TActivationChooser*)p);
   }
   static void deleteArray_TMVAcLcLTActivationChooser(void *p) {
      delete [] ((::TMVA::TActivationChooser*)p);
   }
   static void destruct_TMVAcLcLTActivationChooser(void *p) {
      typedef ::TMVA::TActivationChooser current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TActivationChooser

namespace TMVA {
//______________________________________________________________________________
void TActivation::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TActivation.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TActivation::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TActivation::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLTActivation(void *p) {
      delete ((::TMVA::TActivation*)p);
   }
   static void deleteArray_TMVAcLcLTActivation(void *p) {
      delete [] ((::TMVA::TActivation*)p);
   }
   static void destruct_TMVAcLcLTActivation(void *p) {
      typedef ::TMVA::TActivation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TActivation

namespace TMVA {
//______________________________________________________________________________
void TActivationSigmoid::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TActivationSigmoid.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TActivationSigmoid::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TActivationSigmoid::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTActivationSigmoid(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationSigmoid : new ::TMVA::TActivationSigmoid;
   }
   static void *newArray_TMVAcLcLTActivationSigmoid(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationSigmoid[nElements] : new ::TMVA::TActivationSigmoid[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTActivationSigmoid(void *p) {
      delete ((::TMVA::TActivationSigmoid*)p);
   }
   static void deleteArray_TMVAcLcLTActivationSigmoid(void *p) {
      delete [] ((::TMVA::TActivationSigmoid*)p);
   }
   static void destruct_TMVAcLcLTActivationSigmoid(void *p) {
      typedef ::TMVA::TActivationSigmoid current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TActivationSigmoid

namespace TMVA {
//______________________________________________________________________________
void TActivationIdentity::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TActivationIdentity.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TActivationIdentity::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TActivationIdentity::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTActivationIdentity(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationIdentity : new ::TMVA::TActivationIdentity;
   }
   static void *newArray_TMVAcLcLTActivationIdentity(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationIdentity[nElements] : new ::TMVA::TActivationIdentity[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTActivationIdentity(void *p) {
      delete ((::TMVA::TActivationIdentity*)p);
   }
   static void deleteArray_TMVAcLcLTActivationIdentity(void *p) {
      delete [] ((::TMVA::TActivationIdentity*)p);
   }
   static void destruct_TMVAcLcLTActivationIdentity(void *p) {
      typedef ::TMVA::TActivationIdentity current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TActivationIdentity

namespace TMVA {
//______________________________________________________________________________
void TActivationTanh::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TActivationTanh.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TActivationTanh::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TActivationTanh::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTActivationTanh(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationTanh : new ::TMVA::TActivationTanh;
   }
   static void *newArray_TMVAcLcLTActivationTanh(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationTanh[nElements] : new ::TMVA::TActivationTanh[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTActivationTanh(void *p) {
      delete ((::TMVA::TActivationTanh*)p);
   }
   static void deleteArray_TMVAcLcLTActivationTanh(void *p) {
      delete [] ((::TMVA::TActivationTanh*)p);
   }
   static void destruct_TMVAcLcLTActivationTanh(void *p) {
      typedef ::TMVA::TActivationTanh current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TActivationTanh

namespace TMVA {
//______________________________________________________________________________
void TActivationRadial::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TActivationRadial.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TActivationRadial::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TActivationRadial::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTActivationRadial(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationRadial : new ::TMVA::TActivationRadial;
   }
   static void *newArray_TMVAcLcLTActivationRadial(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TActivationRadial[nElements] : new ::TMVA::TActivationRadial[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTActivationRadial(void *p) {
      delete ((::TMVA::TActivationRadial*)p);
   }
   static void deleteArray_TMVAcLcLTActivationRadial(void *p) {
      delete [] ((::TMVA::TActivationRadial*)p);
   }
   static void destruct_TMVAcLcLTActivationRadial(void *p) {
      typedef ::TMVA::TActivationRadial current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TActivationRadial

namespace TMVA {
//______________________________________________________________________________
void TNeuronInputChooser::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TNeuronInputChooser.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TNeuronInputChooser::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TNeuronInputChooser::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTNeuronInputChooser(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputChooser : new ::TMVA::TNeuronInputChooser;
   }
   static void *newArray_TMVAcLcLTNeuronInputChooser(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputChooser[nElements] : new ::TMVA::TNeuronInputChooser[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTNeuronInputChooser(void *p) {
      delete ((::TMVA::TNeuronInputChooser*)p);
   }
   static void deleteArray_TMVAcLcLTNeuronInputChooser(void *p) {
      delete [] ((::TMVA::TNeuronInputChooser*)p);
   }
   static void destruct_TMVAcLcLTNeuronInputChooser(void *p) {
      typedef ::TMVA::TNeuronInputChooser current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TNeuronInputChooser

namespace TMVA {
//______________________________________________________________________________
void TNeuronInput::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TNeuronInput.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TNeuronInput::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TNeuronInput::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLTNeuronInput(void *p) {
      delete ((::TMVA::TNeuronInput*)p);
   }
   static void deleteArray_TMVAcLcLTNeuronInput(void *p) {
      delete [] ((::TMVA::TNeuronInput*)p);
   }
   static void destruct_TMVAcLcLTNeuronInput(void *p) {
      typedef ::TMVA::TNeuronInput current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TNeuronInput

namespace TMVA {
//______________________________________________________________________________
void TNeuronInputSum::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TNeuronInputSum.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TNeuronInputSum::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TNeuronInputSum::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTNeuronInputSum(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputSum : new ::TMVA::TNeuronInputSum;
   }
   static void *newArray_TMVAcLcLTNeuronInputSum(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputSum[nElements] : new ::TMVA::TNeuronInputSum[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTNeuronInputSum(void *p) {
      delete ((::TMVA::TNeuronInputSum*)p);
   }
   static void deleteArray_TMVAcLcLTNeuronInputSum(void *p) {
      delete [] ((::TMVA::TNeuronInputSum*)p);
   }
   static void destruct_TMVAcLcLTNeuronInputSum(void *p) {
      typedef ::TMVA::TNeuronInputSum current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TNeuronInputSum

namespace TMVA {
//______________________________________________________________________________
void TNeuronInputSqSum::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TNeuronInputSqSum.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TNeuronInputSqSum::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TNeuronInputSqSum::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTNeuronInputSqSum(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputSqSum : new ::TMVA::TNeuronInputSqSum;
   }
   static void *newArray_TMVAcLcLTNeuronInputSqSum(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputSqSum[nElements] : new ::TMVA::TNeuronInputSqSum[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTNeuronInputSqSum(void *p) {
      delete ((::TMVA::TNeuronInputSqSum*)p);
   }
   static void deleteArray_TMVAcLcLTNeuronInputSqSum(void *p) {
      delete [] ((::TMVA::TNeuronInputSqSum*)p);
   }
   static void destruct_TMVAcLcLTNeuronInputSqSum(void *p) {
      typedef ::TMVA::TNeuronInputSqSum current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TNeuronInputSqSum

namespace TMVA {
//______________________________________________________________________________
void TNeuronInputAbs::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TNeuronInputAbs.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TNeuronInputAbs::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TNeuronInputAbs::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTNeuronInputAbs(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputAbs : new ::TMVA::TNeuronInputAbs;
   }
   static void *newArray_TMVAcLcLTNeuronInputAbs(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::TNeuronInputAbs[nElements] : new ::TMVA::TNeuronInputAbs[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTNeuronInputAbs(void *p) {
      delete ((::TMVA::TNeuronInputAbs*)p);
   }
   static void deleteArray_TMVAcLcLTNeuronInputAbs(void *p) {
      delete [] ((::TMVA::TNeuronInputAbs*)p);
   }
   static void destruct_TMVAcLcLTNeuronInputAbs(void *p) {
      typedef ::TMVA::TNeuronInputAbs current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TNeuronInputAbs

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLTypes(void *p) {
      delete ((::TMVA::Types*)p);
   }
   static void deleteArray_TMVAcLcLTypes(void *p) {
      delete [] ((::TMVA::Types*)p);
   }
   static void destruct_TMVAcLcLTypes(void *p) {
      typedef ::TMVA::Types current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Types

namespace TMVA {
//______________________________________________________________________________
void Ranking::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Ranking.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Ranking::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Ranking::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLRanking(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Ranking : new ::TMVA::Ranking;
   }
   static void *newArray_TMVAcLcLRanking(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::Ranking[nElements] : new ::TMVA::Ranking[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLRanking(void *p) {
      delete ((::TMVA::Ranking*)p);
   }
   static void deleteArray_TMVAcLcLRanking(void *p) {
      delete [] ((::TMVA::Ranking*)p);
   }
   static void destruct_TMVAcLcLRanking(void *p) {
      typedef ::TMVA::Ranking current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Ranking

namespace TMVA {
//______________________________________________________________________________
void RuleFit::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::RuleFit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::RuleFit::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::RuleFit::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLRuleFit(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::RuleFit : new ::TMVA::RuleFit;
   }
   static void *newArray_TMVAcLcLRuleFit(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::RuleFit[nElements] : new ::TMVA::RuleFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLRuleFit(void *p) {
      delete ((::TMVA::RuleFit*)p);
   }
   static void deleteArray_TMVAcLcLRuleFit(void *p) {
      delete [] ((::TMVA::RuleFit*)p);
   }
   static void destruct_TMVAcLcLRuleFit(void *p) {
      typedef ::TMVA::RuleFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::RuleFit

namespace TMVA {
//______________________________________________________________________________
void RuleFitAPI::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::RuleFitAPI.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::RuleFitAPI::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::RuleFitAPI::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLRuleFitAPI(void *p) {
      delete ((::TMVA::RuleFitAPI*)p);
   }
   static void deleteArray_TMVAcLcLRuleFitAPI(void *p) {
      delete [] ((::TMVA::RuleFitAPI*)p);
   }
   static void destruct_TMVAcLcLRuleFitAPI(void *p) {
      typedef ::TMVA::RuleFitAPI current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::RuleFitAPI

namespace TMVA {
//______________________________________________________________________________
void IMethod::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::IMethod.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::IMethod::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::IMethod::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLIMethod(void *p) {
      delete ((::TMVA::IMethod*)p);
   }
   static void deleteArray_TMVAcLcLIMethod(void *p) {
      delete [] ((::TMVA::IMethod*)p);
   }
   static void destruct_TMVAcLcLIMethod(void *p) {
      typedef ::TMVA::IMethod current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::IMethod

namespace TMVA {
//______________________________________________________________________________
void MsgLogger::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MsgLogger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MsgLogger::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MsgLogger::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLMsgLogger(void *p) {
      return  p ? new(p) ::TMVA::MsgLogger : new ::TMVA::MsgLogger;
   }
   static void *newArray_TMVAcLcLMsgLogger(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::MsgLogger[nElements] : new ::TMVA::MsgLogger[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLMsgLogger(void *p) {
      delete ((::TMVA::MsgLogger*)p);
   }
   static void deleteArray_TMVAcLcLMsgLogger(void *p) {
      delete [] ((::TMVA::MsgLogger*)p);
   }
   static void destruct_TMVAcLcLMsgLogger(void *p) {
      typedef ::TMVA::MsgLogger current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MsgLogger

namespace TMVA {
//______________________________________________________________________________
void VariableTransformBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariableTransformBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariableTransformBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariableTransformBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariableTransformBase(void *p) {
      delete ((::TMVA::VariableTransformBase*)p);
   }
   static void deleteArray_TMVAcLcLVariableTransformBase(void *p) {
      delete [] ((::TMVA::VariableTransformBase*)p);
   }
   static void destruct_TMVAcLcLVariableTransformBase(void *p) {
      typedef ::TMVA::VariableTransformBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariableTransformBase

namespace TMVA {
//______________________________________________________________________________
void VariableIdentityTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariableIdentityTransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariableIdentityTransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariableIdentityTransform::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariableIdentityTransform(void *p) {
      delete ((::TMVA::VariableIdentityTransform*)p);
   }
   static void deleteArray_TMVAcLcLVariableIdentityTransform(void *p) {
      delete [] ((::TMVA::VariableIdentityTransform*)p);
   }
   static void destruct_TMVAcLcLVariableIdentityTransform(void *p) {
      typedef ::TMVA::VariableIdentityTransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariableIdentityTransform

namespace TMVA {
//______________________________________________________________________________
void VariableDecorrTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariableDecorrTransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariableDecorrTransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariableDecorrTransform::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariableDecorrTransform(void *p) {
      delete ((::TMVA::VariableDecorrTransform*)p);
   }
   static void deleteArray_TMVAcLcLVariableDecorrTransform(void *p) {
      delete [] ((::TMVA::VariableDecorrTransform*)p);
   }
   static void destruct_TMVAcLcLVariableDecorrTransform(void *p) {
      typedef ::TMVA::VariableDecorrTransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariableDecorrTransform

namespace TMVA {
//______________________________________________________________________________
void VariablePCATransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariablePCATransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariablePCATransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariablePCATransform::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariablePCATransform(void *p) {
      delete ((::TMVA::VariablePCATransform*)p);
   }
   static void deleteArray_TMVAcLcLVariablePCATransform(void *p) {
      delete [] ((::TMVA::VariablePCATransform*)p);
   }
   static void destruct_TMVAcLcLVariablePCATransform(void *p) {
      typedef ::TMVA::VariablePCATransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariablePCATransform

namespace TMVA {
//______________________________________________________________________________
void VariableGaussTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariableGaussTransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariableGaussTransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariableGaussTransform::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariableGaussTransform(void *p) {
      delete ((::TMVA::VariableGaussTransform*)p);
   }
   static void deleteArray_TMVAcLcLVariableGaussTransform(void *p) {
      delete [] ((::TMVA::VariableGaussTransform*)p);
   }
   static void destruct_TMVAcLcLVariableGaussTransform(void *p) {
      typedef ::TMVA::VariableGaussTransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariableGaussTransform

namespace TMVA {
//______________________________________________________________________________
void VariableNormalizeTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariableNormalizeTransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariableNormalizeTransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariableNormalizeTransform::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariableNormalizeTransform(void *p) {
      delete ((::TMVA::VariableNormalizeTransform*)p);
   }
   static void deleteArray_TMVAcLcLVariableNormalizeTransform(void *p) {
      delete [] ((::TMVA::VariableNormalizeTransform*)p);
   }
   static void destruct_TMVAcLcLVariableNormalizeTransform(void *p) {
      typedef ::TMVA::VariableNormalizeTransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariableNormalizeTransform

namespace TMVA {
//______________________________________________________________________________
void VariableRearrangeTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::VariableRearrangeTransform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::VariableRearrangeTransform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::VariableRearrangeTransform::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLVariableRearrangeTransform(void *p) {
      delete ((::TMVA::VariableRearrangeTransform*)p);
   }
   static void deleteArray_TMVAcLcLVariableRearrangeTransform(void *p) {
      delete [] ((::TMVA::VariableRearrangeTransform*)p);
   }
   static void destruct_TMVAcLcLVariableRearrangeTransform(void *p) {
      typedef ::TMVA::VariableRearrangeTransform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::VariableRearrangeTransform

namespace ROOT {
   static TClass *maplETStringcOTMVAcLcLTypescLcLEMVAgR_Dictionary();
   static void maplETStringcOTMVAcLcLTypescLcLEMVAgR_TClassManip(TClass*);
   static void *new_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p = 0);
   static void *newArray_maplETStringcOTMVAcLcLTypescLcLEMVAgR(Long_t size, void *p);
   static void delete_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p);
   static void deleteArray_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p);
   static void destruct_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TMVA::Types::EMVA>*)
   {
      map<TString,TMVA::Types::EMVA> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TMVA::Types::EMVA>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TMVA::Types::EMVA>", -2, "map", 96,
                  typeid(map<TString,TMVA::Types::EMVA>), DefineBehavior(ptr, ptr),
                  &maplETStringcOTMVAcLcLTypescLcLEMVAgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TMVA::Types::EMVA>) );
      instance.SetNew(&new_maplETStringcOTMVAcLcLTypescLcLEMVAgR);
      instance.SetNewArray(&newArray_maplETStringcOTMVAcLcLTypescLcLEMVAgR);
      instance.SetDelete(&delete_maplETStringcOTMVAcLcLTypescLcLEMVAgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTMVAcLcLTypescLcLEMVAgR);
      instance.SetDestructor(&destruct_maplETStringcOTMVAcLcLTypescLcLEMVAgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TMVA::Types::EMVA> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<TString,TMVA::Types::EMVA>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTMVAcLcLTypescLcLEMVAgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TMVA::Types::EMVA>*)0x0)->GetClass();
      maplETStringcOTMVAcLcLTypescLcLEMVAgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTMVAcLcLTypescLcLEMVAgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) map<TString,TMVA::Types::EMVA> : new map<TString,TMVA::Types::EMVA>;
   }
   static void *newArray_maplETStringcOTMVAcLcLTypescLcLEMVAgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) map<TString,TMVA::Types::EMVA>[nElements] : new map<TString,TMVA::Types::EMVA>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p) {
      delete ((map<TString,TMVA::Types::EMVA>*)p);
   }
   static void deleteArray_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p) {
      delete [] ((map<TString,TMVA::Types::EMVA>*)p);
   }
   static void destruct_maplETStringcOTMVAcLcLTypescLcLEMVAgR(void *p) {
      typedef map<TString,TMVA::Types::EMVA> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TMVA::Types::EMVA>

namespace {
  void TriggerDictionaryInitialization_dict4_Impl() {
    static const char* headers[] = {
"inc/TMVA/TNeuron.h",
"inc/TMVA/TSynapse.h",
"inc/TMVA/TActivationChooser.h",
"inc/TMVA/TActivation.h",
"inc/TMVA/TActivationSigmoid.h",
"inc/TMVA/TActivationIdentity.h",
"inc/TMVA/TActivationTanh.h",
"inc/TMVA/TActivationRadial.h",
"inc/TMVA/TNeuronInputChooser.h",
"inc/TMVA/TNeuronInput.h",
"inc/TMVA/TNeuronInputSum.h",
"inc/TMVA/TNeuronInputSqSum.h",
"inc/TMVA/TNeuronInputAbs.h",
"inc/TMVA/Types.h",
"inc/TMVA/Ranking.h",
"inc/TMVA/RuleFit.h",
"inc/TMVA/RuleFitAPI.h",
"inc/TMVA/IMethod.h",
"inc/TMVA/MsgLogger.h",
"inc/TMVA/VariableTransformBase.h",
"inc/TMVA/VariableIdentityTransform.h",
"inc/TMVA/VariableDecorrTransform.h",
"inc/TMVA/VariablePCATransform.h",
"inc/TMVA/VariableGaussTransform.h",
"inc/TMVA/VariableNormalizeTransform.h",
"inc/TMVA/VariableRearrangeTransform.h",
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
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Neuron class used by MethodANNBase derivative ANNs)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuron.h")))  TNeuron;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Synapse class used by MethodANNBase and derivatives)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuron.h")))  TSynapse;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Class for choosing activation functions)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TActivationChooser.h")))  TActivationChooser;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface for TNeuron activation function classes)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuron.h")))  TActivation;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Sigmoid activation function for TNeuron)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TActivationSigmoid.h")))  TActivationSigmoid;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Identity activation function for TNeuron)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TActivationIdentity.h")))  TActivationIdentity;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Tanh sigmoid activation function for TNeuron)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TActivationTanh.h")))  TActivationTanh;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Radial basis activation function for TNeuron)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TActivationRadial.h")))  TActivationRadial;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Class for choosing neuron input functions)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuronInputChooser.h")))  TNeuronInputChooser;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface for TNeuron input calculation classes)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuronInputChooser.h")))  TNeuronInput;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Calculates weighted sum of neuron inputs)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuronInputChooser.h")))  TNeuronInputSum;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Calculates square of  weighted sum of neuron inputs)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuronInputChooser.h")))  TNeuronInputSqSum;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Calculates the sum of the absolute values of the weighted inputs)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuronInputChooser.h")))  TNeuronInputAbs;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/TNeuron.h")))  Types;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Method-specific ranking for input variables)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Ranking.h")))  Ranking;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Calculations for Friedman's RuleFit method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/RuleFit.h")))  RuleFit;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Friedman's RuleFit method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/RuleFitAPI.h")))  RuleFitAPI;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Method Interface)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/IMethod.h")))  IMethod;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Ostringstream derivative to redirect and format logging output)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/RuleFitAPI.h")))  MsgLogger;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Base class for variable transformations)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariableTransformBase.h")))  VariableTransformBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Variable transformation: identity)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariableIdentityTransform.h")))  VariableIdentityTransform;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Variable transformation: decorrelation)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariableDecorrTransform.h")))  VariableDecorrTransform;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Variable transformation: Principal Value Composition)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariablePCATransform.h")))  VariablePCATransform;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Variable transformation: Gauss transformation)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariableGaussTransform.h")))  VariableGaussTransform;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Variable transformation: normalization)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariableNormalizeTransform.h")))  VariableNormalizeTransform;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Variable transformation: normalization)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/VariableRearrangeTransform.h")))  VariableRearrangeTransform;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "inc/TMVA/TNeuron.h"
#include "inc/TMVA/TSynapse.h"
#include "inc/TMVA/TActivationChooser.h"
#include "inc/TMVA/TActivation.h"
#include "inc/TMVA/TActivationSigmoid.h"
#include "inc/TMVA/TActivationIdentity.h"
#include "inc/TMVA/TActivationTanh.h"
#include "inc/TMVA/TActivationRadial.h"
#include "inc/TMVA/TNeuronInputChooser.h"
#include "inc/TMVA/TNeuronInput.h"
#include "inc/TMVA/TNeuronInputSum.h"
#include "inc/TMVA/TNeuronInputSqSum.h"
#include "inc/TMVA/TNeuronInputAbs.h"
#include "inc/TMVA/Types.h"
#include "inc/TMVA/Ranking.h"
#include "inc/TMVA/RuleFit.h"
#include "inc/TMVA/RuleFitAPI.h"
#include "inc/TMVA/IMethod.h"
#include "inc/TMVA/MsgLogger.h"
#include "inc/TMVA/VariableTransformBase.h"
#include "inc/TMVA/VariableIdentityTransform.h"
#include "inc/TMVA/VariableDecorrTransform.h"
#include "inc/TMVA/VariablePCATransform.h"
#include "inc/TMVA/VariableGaussTransform.h"
#include "inc/TMVA/VariableNormalizeTransform.h"
#include "inc/TMVA/VariableRearrangeTransform.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TMVA::IMethod", payloadCode, "@",
"TMVA::MsgLogger", payloadCode, "@",
"TMVA::Ranking", payloadCode, "@",
"TMVA::RuleFit", payloadCode, "@",
"TMVA::RuleFitAPI", payloadCode, "@",
"TMVA::TActivation", payloadCode, "@",
"TMVA::TActivationChooser", payloadCode, "@",
"TMVA::TActivationIdentity", payloadCode, "@",
"TMVA::TActivationRadial", payloadCode, "@",
"TMVA::TActivationSigmoid", payloadCode, "@",
"TMVA::TActivationTanh", payloadCode, "@",
"TMVA::TNeuron", payloadCode, "@",
"TMVA::TNeuronInput", payloadCode, "@",
"TMVA::TNeuronInputAbs", payloadCode, "@",
"TMVA::TNeuronInputChooser", payloadCode, "@",
"TMVA::TNeuronInputSqSum", payloadCode, "@",
"TMVA::TNeuronInputSum", payloadCode, "@",
"TMVA::TSynapse", payloadCode, "@",
"TMVA::Types", payloadCode, "@",
"TMVA::VariableDecorrTransform", payloadCode, "@",
"TMVA::VariableGaussTransform", payloadCode, "@",
"TMVA::VariableIdentityTransform", payloadCode, "@",
"TMVA::VariableNormalizeTransform", payloadCode, "@",
"TMVA::VariablePCATransform", payloadCode, "@",
"TMVA::VariableRearrangeTransform", payloadCode, "@",
"TMVA::VariableTransformBase", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dict4",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict4_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict4_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict4() {
  TriggerDictionaryInitialization_dict4_Impl();
}
