// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedImatthiasdIAnalysisdISSX13dISSXdIPxlModulesdIbuilddIinternaldITMVAdIdict2

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
#include "inc/TMVA/TSpline2.h"
#include "inc/TMVA/TSpline1.h"
#include "inc/TMVA/PDF.h"
#include "inc/TMVA/BinaryTree.h"
#include "inc/TMVA/BinarySearchTreeNode.h"
#include "inc/TMVA/BinarySearchTree.h"
#include "inc/TMVA/Timer.h"
#include "inc/TMVA/RootFinder.h"
#include "inc/TMVA/CrossEntropy.h"
#include "inc/TMVA/DecisionTree.h"
#include "inc/TMVA/DecisionTreeNode.h"
#include "inc/TMVA/MisClassificationError.h"
#include "inc/TMVA/Node.h"
#include "inc/TMVA/SdivSqrtSplusB.h"
#include "inc/TMVA/SeparationBase.h"
#include "inc/TMVA/RegressionVariance.h"
#include "inc/TMVA/Tools.h"
#include "inc/TMVA/Reader.h"
#include "inc/TMVA/GeneticAlgorithm.h"
#include "inc/TMVA/GeneticGenes.h"
#include "inc/TMVA/GeneticPopulation.h"
#include "inc/TMVA/GeneticRange.h"
#include "inc/TMVA/GiniIndex.h"
#include "inc/TMVA/GiniIndexWithLaplace.h"
#include "inc/TMVA/SimulatedAnnealing.h"
#include "inc/TMVA/QuickMVAProbEstimator.h"

// Header files passed via #pragma extra_include

namespace TMVA {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *TMVA_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("TMVA", 0 /*version*/, "inc/TMVA/TSpline2.h", 43,
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
   static void delete_TMVAcLcLTSpline2(void *p);
   static void deleteArray_TMVAcLcLTSpline2(void *p);
   static void destruct_TMVAcLcLTSpline2(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TSpline2*)
   {
      ::TMVA::TSpline2 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TSpline2 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TSpline2", ::TMVA::TSpline2::Class_Version(), "inc/TMVA/TSpline2.h", 45,
                  typeid(::TMVA::TSpline2), DefineBehavior(ptr, ptr),
                  &::TMVA::TSpline2::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TSpline2) );
      instance.SetDelete(&delete_TMVAcLcLTSpline2);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTSpline2);
      instance.SetDestructor(&destruct_TMVAcLcLTSpline2);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TSpline2*)
   {
      return GenerateInitInstanceLocal((::TMVA::TSpline2*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TSpline2*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLTSpline1(void *p);
   static void deleteArray_TMVAcLcLTSpline1(void *p);
   static void destruct_TMVAcLcLTSpline1(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::TSpline1*)
   {
      ::TMVA::TSpline1 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::TSpline1 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::TSpline1", ::TMVA::TSpline1::Class_Version(), "inc/TMVA/TSpline1.h", 45,
                  typeid(::TMVA::TSpline1), DefineBehavior(ptr, ptr),
                  &::TMVA::TSpline1::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::TSpline1) );
      instance.SetDelete(&delete_TMVAcLcLTSpline1);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTSpline1);
      instance.SetDestructor(&destruct_TMVAcLcLTSpline1);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::TSpline1*)
   {
      return GenerateInitInstanceLocal((::TMVA::TSpline1*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::TSpline1*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLPDF(void *p);
   static void deleteArray_TMVAcLcLPDF(void *p);
   static void destruct_TMVAcLcLPDF(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::PDF*)
   {
      ::TMVA::PDF *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::PDF >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::PDF", ::TMVA::PDF::Class_Version(), "inc/TMVA/PDF.h", 68,
                  typeid(::TMVA::PDF), DefineBehavior(ptr, ptr),
                  &::TMVA::PDF::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::PDF) );
      instance.SetDelete(&delete_TMVAcLcLPDF);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLPDF);
      instance.SetDestructor(&destruct_TMVAcLcLPDF);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::PDF*)
   {
      return GenerateInitInstanceLocal((::TMVA::PDF*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::PDF*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLBinaryTree(void *p);
   static void deleteArray_TMVAcLcLBinaryTree(void *p);
   static void destruct_TMVAcLcLBinaryTree(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::BinaryTree*)
   {
      ::TMVA::BinaryTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::BinaryTree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::BinaryTree", ::TMVA::BinaryTree::Class_Version(), "inc/TMVA/BinaryTree.h", 68,
                  typeid(::TMVA::BinaryTree), DefineBehavior(ptr, ptr),
                  &::TMVA::BinaryTree::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::BinaryTree) );
      instance.SetDelete(&delete_TMVAcLcLBinaryTree);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLBinaryTree);
      instance.SetDestructor(&destruct_TMVAcLcLBinaryTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::BinaryTree*)
   {
      return GenerateInitInstanceLocal((::TMVA::BinaryTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::BinaryTree*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLBinarySearchTreeNode(void *p = 0);
   static void *newArray_TMVAcLcLBinarySearchTreeNode(Long_t size, void *p);
   static void delete_TMVAcLcLBinarySearchTreeNode(void *p);
   static void deleteArray_TMVAcLcLBinarySearchTreeNode(void *p);
   static void destruct_TMVAcLcLBinarySearchTreeNode(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::BinarySearchTreeNode*)
   {
      ::TMVA::BinarySearchTreeNode *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::BinarySearchTreeNode >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::BinarySearchTreeNode", ::TMVA::BinarySearchTreeNode::Class_Version(), "inc/TMVA/BinarySearchTreeNode.h", 57,
                  typeid(::TMVA::BinarySearchTreeNode), DefineBehavior(ptr, ptr),
                  &::TMVA::BinarySearchTreeNode::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::BinarySearchTreeNode) );
      instance.SetNew(&new_TMVAcLcLBinarySearchTreeNode);
      instance.SetNewArray(&newArray_TMVAcLcLBinarySearchTreeNode);
      instance.SetDelete(&delete_TMVAcLcLBinarySearchTreeNode);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLBinarySearchTreeNode);
      instance.SetDestructor(&destruct_TMVAcLcLBinarySearchTreeNode);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::BinarySearchTreeNode*)
   {
      return GenerateInitInstanceLocal((::TMVA::BinarySearchTreeNode*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::BinarySearchTreeNode*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLBinarySearchTree(void *p = 0);
   static void *newArray_TMVAcLcLBinarySearchTree(Long_t size, void *p);
   static void delete_TMVAcLcLBinarySearchTree(void *p);
   static void deleteArray_TMVAcLcLBinarySearchTree(void *p);
   static void destruct_TMVAcLcLBinarySearchTree(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::BinarySearchTree*)
   {
      ::TMVA::BinarySearchTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::BinarySearchTree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::BinarySearchTree", ::TMVA::BinarySearchTree::Class_Version(), "inc/TMVA/BinarySearchTree.h", 71,
                  typeid(::TMVA::BinarySearchTree), DefineBehavior(ptr, ptr),
                  &::TMVA::BinarySearchTree::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::BinarySearchTree) );
      instance.SetNew(&new_TMVAcLcLBinarySearchTree);
      instance.SetNewArray(&newArray_TMVAcLcLBinarySearchTree);
      instance.SetDelete(&delete_TMVAcLcLBinarySearchTree);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLBinarySearchTree);
      instance.SetDestructor(&destruct_TMVAcLcLBinarySearchTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::BinarySearchTree*)
   {
      return GenerateInitInstanceLocal((::TMVA::BinarySearchTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::BinarySearchTree*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLTimer(void *p = 0);
   static void *newArray_TMVAcLcLTimer(Long_t size, void *p);
   static void delete_TMVAcLcLTimer(void *p);
   static void deleteArray_TMVAcLcLTimer(void *p);
   static void destruct_TMVAcLcLTimer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Timer*)
   {
      ::TMVA::Timer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Timer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Timer", ::TMVA::Timer::Class_Version(), "inc/TMVA/Timer.h", 62,
                  typeid(::TMVA::Timer), DefineBehavior(ptr, ptr),
                  &::TMVA::Timer::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Timer) );
      instance.SetNew(&new_TMVAcLcLTimer);
      instance.SetNewArray(&newArray_TMVAcLcLTimer);
      instance.SetDelete(&delete_TMVAcLcLTimer);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTimer);
      instance.SetDestructor(&destruct_TMVAcLcLTimer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Timer*)
   {
      return GenerateInitInstanceLocal((::TMVA::Timer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Timer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLRootFinder(void *p);
   static void deleteArray_TMVAcLcLRootFinder(void *p);
   static void destruct_TMVAcLcLRootFinder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::RootFinder*)
   {
      ::TMVA::RootFinder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::RootFinder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::RootFinder", ::TMVA::RootFinder::Class_Version(), "inc/TMVA/RootFinder.h", 49,
                  typeid(::TMVA::RootFinder), DefineBehavior(ptr, ptr),
                  &::TMVA::RootFinder::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::RootFinder) );
      instance.SetDelete(&delete_TMVAcLcLRootFinder);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLRootFinder);
      instance.SetDestructor(&destruct_TMVAcLcLRootFinder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::RootFinder*)
   {
      return GenerateInitInstanceLocal((::TMVA::RootFinder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::RootFinder*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLCrossEntropy(void *p = 0);
   static void *newArray_TMVAcLcLCrossEntropy(Long_t size, void *p);
   static void delete_TMVAcLcLCrossEntropy(void *p);
   static void deleteArray_TMVAcLcLCrossEntropy(void *p);
   static void destruct_TMVAcLcLCrossEntropy(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::CrossEntropy*)
   {
      ::TMVA::CrossEntropy *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::CrossEntropy >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::CrossEntropy", ::TMVA::CrossEntropy::Class_Version(), "inc/TMVA/CrossEntropy.h", 45,
                  typeid(::TMVA::CrossEntropy), DefineBehavior(ptr, ptr),
                  &::TMVA::CrossEntropy::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::CrossEntropy) );
      instance.SetNew(&new_TMVAcLcLCrossEntropy);
      instance.SetNewArray(&newArray_TMVAcLcLCrossEntropy);
      instance.SetDelete(&delete_TMVAcLcLCrossEntropy);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLCrossEntropy);
      instance.SetDestructor(&destruct_TMVAcLcLCrossEntropy);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::CrossEntropy*)
   {
      return GenerateInitInstanceLocal((::TMVA::CrossEntropy*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::CrossEntropy*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLDecisionTree(void *p = 0);
   static void *newArray_TMVAcLcLDecisionTree(Long_t size, void *p);
   static void delete_TMVAcLcLDecisionTree(void *p);
   static void deleteArray_TMVAcLcLDecisionTree(void *p);
   static void destruct_TMVAcLcLDecisionTree(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::DecisionTree*)
   {
      ::TMVA::DecisionTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::DecisionTree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::DecisionTree", ::TMVA::DecisionTree::Class_Version(), "inc/TMVA/DecisionTree.h", 72,
                  typeid(::TMVA::DecisionTree), DefineBehavior(ptr, ptr),
                  &::TMVA::DecisionTree::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::DecisionTree) );
      instance.SetNew(&new_TMVAcLcLDecisionTree);
      instance.SetNewArray(&newArray_TMVAcLcLDecisionTree);
      instance.SetDelete(&delete_TMVAcLcLDecisionTree);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLDecisionTree);
      instance.SetDestructor(&destruct_TMVAcLcLDecisionTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::DecisionTree*)
   {
      return GenerateInitInstanceLocal((::TMVA::DecisionTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::DecisionTree*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLDecisionTreeNode(void *p = 0);
   static void *newArray_TMVAcLcLDecisionTreeNode(Long_t size, void *p);
   static void delete_TMVAcLcLDecisionTreeNode(void *p);
   static void deleteArray_TMVAcLcLDecisionTreeNode(void *p);
   static void destruct_TMVAcLcLDecisionTreeNode(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::DecisionTreeNode*)
   {
      ::TMVA::DecisionTreeNode *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::DecisionTreeNode >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::DecisionTreeNode", ::TMVA::DecisionTreeNode::Class_Version(), "TMVA/DecisionTreeNode.h", 120,
                  typeid(::TMVA::DecisionTreeNode), DefineBehavior(ptr, ptr),
                  &::TMVA::DecisionTreeNode::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::DecisionTreeNode) );
      instance.SetNew(&new_TMVAcLcLDecisionTreeNode);
      instance.SetNewArray(&newArray_TMVAcLcLDecisionTreeNode);
      instance.SetDelete(&delete_TMVAcLcLDecisionTreeNode);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLDecisionTreeNode);
      instance.SetDestructor(&destruct_TMVAcLcLDecisionTreeNode);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::DecisionTreeNode*)
   {
      return GenerateInitInstanceLocal((::TMVA::DecisionTreeNode*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::DecisionTreeNode*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLMisClassificationError(void *p = 0);
   static void *newArray_TMVAcLcLMisClassificationError(Long_t size, void *p);
   static void delete_TMVAcLcLMisClassificationError(void *p);
   static void deleteArray_TMVAcLcLMisClassificationError(void *p);
   static void destruct_TMVAcLcLMisClassificationError(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::MisClassificationError*)
   {
      ::TMVA::MisClassificationError *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::MisClassificationError >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::MisClassificationError", ::TMVA::MisClassificationError::Class_Version(), "inc/TMVA/MisClassificationError.h", 48,
                  typeid(::TMVA::MisClassificationError), DefineBehavior(ptr, ptr),
                  &::TMVA::MisClassificationError::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::MisClassificationError) );
      instance.SetNew(&new_TMVAcLcLMisClassificationError);
      instance.SetNewArray(&newArray_TMVAcLcLMisClassificationError);
      instance.SetDelete(&delete_TMVAcLcLMisClassificationError);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLMisClassificationError);
      instance.SetDestructor(&destruct_TMVAcLcLMisClassificationError);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::MisClassificationError*)
   {
      return GenerateInitInstanceLocal((::TMVA::MisClassificationError*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::MisClassificationError*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLNode(void *p);
   static void deleteArray_TMVAcLcLNode(void *p);
   static void destruct_TMVAcLcLNode(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Node*)
   {
      ::TMVA::Node *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Node >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Node", ::TMVA::Node::Class_Version(), "TMVA/Node.h", 60,
                  typeid(::TMVA::Node), DefineBehavior(ptr, ptr),
                  &::TMVA::Node::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Node) );
      instance.SetDelete(&delete_TMVAcLcLNode);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLNode);
      instance.SetDestructor(&destruct_TMVAcLcLNode);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Node*)
   {
      return GenerateInitInstanceLocal((::TMVA::Node*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Node*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLSdivSqrtSplusB(void *p = 0);
   static void *newArray_TMVAcLcLSdivSqrtSplusB(Long_t size, void *p);
   static void delete_TMVAcLcLSdivSqrtSplusB(void *p);
   static void deleteArray_TMVAcLcLSdivSqrtSplusB(void *p);
   static void destruct_TMVAcLcLSdivSqrtSplusB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::SdivSqrtSplusB*)
   {
      ::TMVA::SdivSqrtSplusB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::SdivSqrtSplusB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::SdivSqrtSplusB", ::TMVA::SdivSqrtSplusB::Class_Version(), "inc/TMVA/SdivSqrtSplusB.h", 46,
                  typeid(::TMVA::SdivSqrtSplusB), DefineBehavior(ptr, ptr),
                  &::TMVA::SdivSqrtSplusB::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::SdivSqrtSplusB) );
      instance.SetNew(&new_TMVAcLcLSdivSqrtSplusB);
      instance.SetNewArray(&newArray_TMVAcLcLSdivSqrtSplusB);
      instance.SetDelete(&delete_TMVAcLcLSdivSqrtSplusB);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLSdivSqrtSplusB);
      instance.SetDestructor(&destruct_TMVAcLcLSdivSqrtSplusB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::SdivSqrtSplusB*)
   {
      return GenerateInitInstanceLocal((::TMVA::SdivSqrtSplusB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::SdivSqrtSplusB*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLSeparationBase(void *p);
   static void deleteArray_TMVAcLcLSeparationBase(void *p);
   static void destruct_TMVAcLcLSeparationBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::SeparationBase*)
   {
      ::TMVA::SeparationBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::SeparationBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::SeparationBase", ::TMVA::SeparationBase::Class_Version(), "TMVA/SeparationBase.h", 88,
                  typeid(::TMVA::SeparationBase), DefineBehavior(ptr, ptr),
                  &::TMVA::SeparationBase::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::SeparationBase) );
      instance.SetDelete(&delete_TMVAcLcLSeparationBase);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLSeparationBase);
      instance.SetDestructor(&destruct_TMVAcLcLSeparationBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::SeparationBase*)
   {
      return GenerateInitInstanceLocal((::TMVA::SeparationBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::SeparationBase*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLRegressionVariance(void *p = 0);
   static void *newArray_TMVAcLcLRegressionVariance(Long_t size, void *p);
   static void delete_TMVAcLcLRegressionVariance(void *p);
   static void deleteArray_TMVAcLcLRegressionVariance(void *p);
   static void destruct_TMVAcLcLRegressionVariance(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::RegressionVariance*)
   {
      ::TMVA::RegressionVariance *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::RegressionVariance >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::RegressionVariance", ::TMVA::RegressionVariance::Class_Version(), "TMVA/RegressionVariance.h", 70,
                  typeid(::TMVA::RegressionVariance), DefineBehavior(ptr, ptr),
                  &::TMVA::RegressionVariance::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::RegressionVariance) );
      instance.SetNew(&new_TMVAcLcLRegressionVariance);
      instance.SetNewArray(&newArray_TMVAcLcLRegressionVariance);
      instance.SetDelete(&delete_TMVAcLcLRegressionVariance);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLRegressionVariance);
      instance.SetDestructor(&destruct_TMVAcLcLRegressionVariance);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::RegressionVariance*)
   {
      return GenerateInitInstanceLocal((::TMVA::RegressionVariance*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::RegressionVariance*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *TMVAcLcLTools_Dictionary();
   static void TMVAcLcLTools_TClassManip(TClass*);
   static void delete_TMVAcLcLTools(void *p);
   static void deleteArray_TMVAcLcLTools(void *p);
   static void destruct_TMVAcLcLTools(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Tools*)
   {
      ::TMVA::Tools *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TMVA::Tools));
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Tools", "inc/TMVA/Tools.h", 88,
                  typeid(::TMVA::Tools), DefineBehavior(ptr, ptr),
                  &TMVAcLcLTools_Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Tools) );
      instance.SetDelete(&delete_TMVAcLcLTools);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLTools);
      instance.SetDestructor(&destruct_TMVAcLcLTools);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Tools*)
   {
      return GenerateInitInstanceLocal((::TMVA::Tools*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Tools*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TMVAcLcLTools_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TMVA::Tools*)0x0)->GetClass();
      TMVAcLcLTools_TClassManip(theClass);
   return theClass;
   }

   static void TMVAcLcLTools_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLReader(void *p = 0);
   static void *newArray_TMVAcLcLReader(Long_t size, void *p);
   static void delete_TMVAcLcLReader(void *p);
   static void deleteArray_TMVAcLcLReader(void *p);
   static void destruct_TMVAcLcLReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::Reader*)
   {
      ::TMVA::Reader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::Reader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::Reader", ::TMVA::Reader::Class_Version(), "inc/TMVA/Reader.h", 73,
                  typeid(::TMVA::Reader), DefineBehavior(ptr, ptr),
                  &::TMVA::Reader::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::Reader) );
      instance.SetNew(&new_TMVAcLcLReader);
      instance.SetNewArray(&newArray_TMVAcLcLReader);
      instance.SetDelete(&delete_TMVAcLcLReader);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLReader);
      instance.SetDestructor(&destruct_TMVAcLcLReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::Reader*)
   {
      return GenerateInitInstanceLocal((::TMVA::Reader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::Reader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLGeneticAlgorithm(void *p);
   static void deleteArray_TMVAcLcLGeneticAlgorithm(void *p);
   static void destruct_TMVAcLcLGeneticAlgorithm(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GeneticAlgorithm*)
   {
      ::TMVA::GeneticAlgorithm *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GeneticAlgorithm >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GeneticAlgorithm", ::TMVA::GeneticAlgorithm::Class_Version(), "inc/TMVA/GeneticAlgorithm.h", 56,
                  typeid(::TMVA::GeneticAlgorithm), DefineBehavior(ptr, ptr),
                  &::TMVA::GeneticAlgorithm::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GeneticAlgorithm) );
      instance.SetDelete(&delete_TMVAcLcLGeneticAlgorithm);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGeneticAlgorithm);
      instance.SetDestructor(&destruct_TMVAcLcLGeneticAlgorithm);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GeneticAlgorithm*)
   {
      return GenerateInitInstanceLocal((::TMVA::GeneticAlgorithm*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GeneticAlgorithm*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLGeneticGenes(void *p = 0);
   static void *newArray_TMVAcLcLGeneticGenes(Long_t size, void *p);
   static void delete_TMVAcLcLGeneticGenes(void *p);
   static void deleteArray_TMVAcLcLGeneticGenes(void *p);
   static void destruct_TMVAcLcLGeneticGenes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GeneticGenes*)
   {
      ::TMVA::GeneticGenes *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GeneticGenes >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GeneticGenes", ::TMVA::GeneticGenes::Class_Version(), "TMVA/GeneticGenes.h", 43,
                  typeid(::TMVA::GeneticGenes), DefineBehavior(ptr, ptr),
                  &::TMVA::GeneticGenes::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GeneticGenes) );
      instance.SetNew(&new_TMVAcLcLGeneticGenes);
      instance.SetNewArray(&newArray_TMVAcLcLGeneticGenes);
      instance.SetDelete(&delete_TMVAcLcLGeneticGenes);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGeneticGenes);
      instance.SetDestructor(&destruct_TMVAcLcLGeneticGenes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GeneticGenes*)
   {
      return GenerateInitInstanceLocal((::TMVA::GeneticGenes*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GeneticGenes*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLGeneticPopulation(void *p);
   static void deleteArray_TMVAcLcLGeneticPopulation(void *p);
   static void destruct_TMVAcLcLGeneticPopulation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GeneticPopulation*)
   {
      ::TMVA::GeneticPopulation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GeneticPopulation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GeneticPopulation", ::TMVA::GeneticPopulation::Class_Version(), "TMVA/GeneticPopulation.h", 58,
                  typeid(::TMVA::GeneticPopulation), DefineBehavior(ptr, ptr),
                  &::TMVA::GeneticPopulation::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GeneticPopulation) );
      instance.SetDelete(&delete_TMVAcLcLGeneticPopulation);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGeneticPopulation);
      instance.SetDestructor(&destruct_TMVAcLcLGeneticPopulation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GeneticPopulation*)
   {
      return GenerateInitInstanceLocal((::TMVA::GeneticPopulation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GeneticPopulation*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLGeneticRange(void *p);
   static void deleteArray_TMVAcLcLGeneticRange(void *p);
   static void destruct_TMVAcLcLGeneticRange(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GeneticRange*)
   {
      ::TMVA::GeneticRange *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GeneticRange >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GeneticRange", ::TMVA::GeneticRange::Class_Version(), "TMVA/GeneticRange.h", 44,
                  typeid(::TMVA::GeneticRange), DefineBehavior(ptr, ptr),
                  &::TMVA::GeneticRange::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GeneticRange) );
      instance.SetDelete(&delete_TMVAcLcLGeneticRange);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGeneticRange);
      instance.SetDestructor(&destruct_TMVAcLcLGeneticRange);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GeneticRange*)
   {
      return GenerateInitInstanceLocal((::TMVA::GeneticRange*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GeneticRange*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLGiniIndex(void *p = 0);
   static void *newArray_TMVAcLcLGiniIndex(Long_t size, void *p);
   static void delete_TMVAcLcLGiniIndex(void *p);
   static void deleteArray_TMVAcLcLGiniIndex(void *p);
   static void destruct_TMVAcLcLGiniIndex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GiniIndex*)
   {
      ::TMVA::GiniIndex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GiniIndex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GiniIndex", ::TMVA::GiniIndex::Class_Version(), "inc/TMVA/GiniIndex.h", 65,
                  typeid(::TMVA::GiniIndex), DefineBehavior(ptr, ptr),
                  &::TMVA::GiniIndex::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GiniIndex) );
      instance.SetNew(&new_TMVAcLcLGiniIndex);
      instance.SetNewArray(&newArray_TMVAcLcLGiniIndex);
      instance.SetDelete(&delete_TMVAcLcLGiniIndex);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGiniIndex);
      instance.SetDestructor(&destruct_TMVAcLcLGiniIndex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GiniIndex*)
   {
      return GenerateInitInstanceLocal((::TMVA::GiniIndex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GiniIndex*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLGiniIndexWithLaplace(void *p = 0);
   static void *newArray_TMVAcLcLGiniIndexWithLaplace(Long_t size, void *p);
   static void delete_TMVAcLcLGiniIndexWithLaplace(void *p);
   static void deleteArray_TMVAcLcLGiniIndexWithLaplace(void *p);
   static void destruct_TMVAcLcLGiniIndexWithLaplace(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::GiniIndexWithLaplace*)
   {
      ::TMVA::GiniIndexWithLaplace *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::GiniIndexWithLaplace >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::GiniIndexWithLaplace", ::TMVA::GiniIndexWithLaplace::Class_Version(), "inc/TMVA/GiniIndexWithLaplace.h", 61,
                  typeid(::TMVA::GiniIndexWithLaplace), DefineBehavior(ptr, ptr),
                  &::TMVA::GiniIndexWithLaplace::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::GiniIndexWithLaplace) );
      instance.SetNew(&new_TMVAcLcLGiniIndexWithLaplace);
      instance.SetNewArray(&newArray_TMVAcLcLGiniIndexWithLaplace);
      instance.SetDelete(&delete_TMVAcLcLGiniIndexWithLaplace);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLGiniIndexWithLaplace);
      instance.SetDestructor(&destruct_TMVAcLcLGiniIndexWithLaplace);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::GiniIndexWithLaplace*)
   {
      return GenerateInitInstanceLocal((::TMVA::GiniIndexWithLaplace*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::GiniIndexWithLaplace*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TMVAcLcLSimulatedAnnealing(void *p);
   static void deleteArray_TMVAcLcLSimulatedAnnealing(void *p);
   static void destruct_TMVAcLcLSimulatedAnnealing(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::SimulatedAnnealing*)
   {
      ::TMVA::SimulatedAnnealing *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::SimulatedAnnealing >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::SimulatedAnnealing", ::TMVA::SimulatedAnnealing::Class_Version(), "inc/TMVA/SimulatedAnnealing.h", 54,
                  typeid(::TMVA::SimulatedAnnealing), DefineBehavior(ptr, ptr),
                  &::TMVA::SimulatedAnnealing::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::SimulatedAnnealing) );
      instance.SetDelete(&delete_TMVAcLcLSimulatedAnnealing);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLSimulatedAnnealing);
      instance.SetDestructor(&destruct_TMVAcLcLSimulatedAnnealing);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::SimulatedAnnealing*)
   {
      return GenerateInitInstanceLocal((::TMVA::SimulatedAnnealing*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealing*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMVAcLcLQuickMVAProbEstimator(void *p = 0);
   static void *newArray_TMVAcLcLQuickMVAProbEstimator(Long_t size, void *p);
   static void delete_TMVAcLcLQuickMVAProbEstimator(void *p);
   static void deleteArray_TMVAcLcLQuickMVAProbEstimator(void *p);
   static void destruct_TMVAcLcLQuickMVAProbEstimator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMVA::QuickMVAProbEstimator*)
   {
      ::TMVA::QuickMVAProbEstimator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMVA::QuickMVAProbEstimator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMVA::QuickMVAProbEstimator", ::TMVA::QuickMVAProbEstimator::Class_Version(), "inc/TMVA/QuickMVAProbEstimator.h", 12,
                  typeid(::TMVA::QuickMVAProbEstimator), DefineBehavior(ptr, ptr),
                  &::TMVA::QuickMVAProbEstimator::Dictionary, isa_proxy, 4,
                  sizeof(::TMVA::QuickMVAProbEstimator) );
      instance.SetNew(&new_TMVAcLcLQuickMVAProbEstimator);
      instance.SetNewArray(&newArray_TMVAcLcLQuickMVAProbEstimator);
      instance.SetDelete(&delete_TMVAcLcLQuickMVAProbEstimator);
      instance.SetDeleteArray(&deleteArray_TMVAcLcLQuickMVAProbEstimator);
      instance.SetDestructor(&destruct_TMVAcLcLQuickMVAProbEstimator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMVA::QuickMVAProbEstimator*)
   {
      return GenerateInitInstanceLocal((::TMVA::QuickMVAProbEstimator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMVA::QuickMVAProbEstimator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TSpline2::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSpline2::Class_Name()
{
   return "TMVA::TSpline2";
}

//______________________________________________________________________________
const char *TSpline2::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline2*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSpline2::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline2*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSpline2::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline2*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSpline2::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline2*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr TSpline1::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSpline1::Class_Name()
{
   return "TMVA::TSpline1";
}

//______________________________________________________________________________
const char *TSpline1::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline1*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSpline1::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline1*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSpline1::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline1*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSpline1::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::TSpline1*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr PDF::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PDF::Class_Name()
{
   return "TMVA::PDF";
}

//______________________________________________________________________________
const char *PDF::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDF*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PDF::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDF*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PDF::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDF*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PDF::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::PDF*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr BinaryTree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BinaryTree::Class_Name()
{
   return "TMVA::BinaryTree";
}

//______________________________________________________________________________
const char *BinaryTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinaryTree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BinaryTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinaryTree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BinaryTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinaryTree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BinaryTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinaryTree*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr BinarySearchTreeNode::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BinarySearchTreeNode::Class_Name()
{
   return "TMVA::BinarySearchTreeNode";
}

//______________________________________________________________________________
const char *BinarySearchTreeNode::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTreeNode*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BinarySearchTreeNode::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTreeNode*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BinarySearchTreeNode::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTreeNode*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BinarySearchTreeNode::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTreeNode*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr BinarySearchTree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BinarySearchTree::Class_Name()
{
   return "TMVA::BinarySearchTree";
}

//______________________________________________________________________________
const char *BinarySearchTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BinarySearchTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BinarySearchTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BinarySearchTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::BinarySearchTree*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Timer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Timer::Class_Name()
{
   return "TMVA::Timer";
}

//______________________________________________________________________________
const char *Timer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Timer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Timer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Timer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Timer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Timer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Timer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Timer*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr RootFinder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RootFinder::Class_Name()
{
   return "TMVA::RootFinder";
}

//______________________________________________________________________________
const char *RootFinder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RootFinder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RootFinder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RootFinder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RootFinder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RootFinder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RootFinder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RootFinder*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr CrossEntropy::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CrossEntropy::Class_Name()
{
   return "TMVA::CrossEntropy";
}

//______________________________________________________________________________
const char *CrossEntropy::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::CrossEntropy*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CrossEntropy::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::CrossEntropy*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CrossEntropy::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::CrossEntropy*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CrossEntropy::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::CrossEntropy*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr DecisionTree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DecisionTree::Class_Name()
{
   return "TMVA::DecisionTree";
}

//______________________________________________________________________________
const char *DecisionTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DecisionTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DecisionTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DecisionTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTree*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr DecisionTreeNode::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DecisionTreeNode::Class_Name()
{
   return "TMVA::DecisionTreeNode";
}

//______________________________________________________________________________
const char *DecisionTreeNode::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTreeNode*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DecisionTreeNode::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTreeNode*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DecisionTreeNode::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTreeNode*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DecisionTreeNode::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::DecisionTreeNode*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr MisClassificationError::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MisClassificationError::Class_Name()
{
   return "TMVA::MisClassificationError";
}

//______________________________________________________________________________
const char *MisClassificationError::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MisClassificationError*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MisClassificationError::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MisClassificationError*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MisClassificationError::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MisClassificationError*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MisClassificationError::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::MisClassificationError*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Node::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Node::Class_Name()
{
   return "TMVA::Node";
}

//______________________________________________________________________________
const char *Node::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Node*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Node::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Node*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Node::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Node*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Node::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Node*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr SdivSqrtSplusB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SdivSqrtSplusB::Class_Name()
{
   return "TMVA::SdivSqrtSplusB";
}

//______________________________________________________________________________
const char *SdivSqrtSplusB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SdivSqrtSplusB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SdivSqrtSplusB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SdivSqrtSplusB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SdivSqrtSplusB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SdivSqrtSplusB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SdivSqrtSplusB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SdivSqrtSplusB*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr SeparationBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SeparationBase::Class_Name()
{
   return "TMVA::SeparationBase";
}

//______________________________________________________________________________
const char *SeparationBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SeparationBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SeparationBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SeparationBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SeparationBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SeparationBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SeparationBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SeparationBase*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr RegressionVariance::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RegressionVariance::Class_Name()
{
   return "TMVA::RegressionVariance";
}

//______________________________________________________________________________
const char *RegressionVariance::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RegressionVariance*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RegressionVariance::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RegressionVariance*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RegressionVariance::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RegressionVariance*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RegressionVariance::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::RegressionVariance*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr Reader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Reader::Class_Name()
{
   return "TMVA::Reader";
}

//______________________________________________________________________________
const char *Reader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Reader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Reader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Reader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Reader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Reader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Reader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::Reader*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GeneticAlgorithm::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GeneticAlgorithm::Class_Name()
{
   return "TMVA::GeneticAlgorithm";
}

//______________________________________________________________________________
const char *GeneticAlgorithm::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticAlgorithm*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GeneticAlgorithm::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticAlgorithm*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GeneticAlgorithm::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticAlgorithm*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GeneticAlgorithm::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticAlgorithm*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GeneticGenes::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GeneticGenes::Class_Name()
{
   return "TMVA::GeneticGenes";
}

//______________________________________________________________________________
const char *GeneticGenes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticGenes*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GeneticGenes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticGenes*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GeneticGenes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticGenes*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GeneticGenes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticGenes*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GeneticPopulation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GeneticPopulation::Class_Name()
{
   return "TMVA::GeneticPopulation";
}

//______________________________________________________________________________
const char *GeneticPopulation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticPopulation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GeneticPopulation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticPopulation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GeneticPopulation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticPopulation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GeneticPopulation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticPopulation*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GeneticRange::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GeneticRange::Class_Name()
{
   return "TMVA::GeneticRange";
}

//______________________________________________________________________________
const char *GeneticRange::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticRange*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GeneticRange::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticRange*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GeneticRange::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticRange*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GeneticRange::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GeneticRange*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GiniIndex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GiniIndex::Class_Name()
{
   return "TMVA::GiniIndex";
}

//______________________________________________________________________________
const char *GiniIndex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GiniIndex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GiniIndex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GiniIndex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndex*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr GiniIndexWithLaplace::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GiniIndexWithLaplace::Class_Name()
{
   return "TMVA::GiniIndexWithLaplace";
}

//______________________________________________________________________________
const char *GiniIndexWithLaplace::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndexWithLaplace*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GiniIndexWithLaplace::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndexWithLaplace*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GiniIndexWithLaplace::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndexWithLaplace*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GiniIndexWithLaplace::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::GiniIndexWithLaplace*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr SimulatedAnnealing::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SimulatedAnnealing::Class_Name()
{
   return "TMVA::SimulatedAnnealing";
}

//______________________________________________________________________________
const char *SimulatedAnnealing::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealing*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SimulatedAnnealing::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealing*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SimulatedAnnealing::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealing*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SimulatedAnnealing::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::SimulatedAnnealing*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
atomic_TClass_ptr QuickMVAProbEstimator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *QuickMVAProbEstimator::Class_Name()
{
   return "TMVA::QuickMVAProbEstimator";
}

//______________________________________________________________________________
const char *QuickMVAProbEstimator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::QuickMVAProbEstimator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int QuickMVAProbEstimator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMVA::QuickMVAProbEstimator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *QuickMVAProbEstimator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::QuickMVAProbEstimator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *QuickMVAProbEstimator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMVA::QuickMVAProbEstimator*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TMVA
namespace TMVA {
//______________________________________________________________________________
void TSpline2::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TSpline2.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TSpline2::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TSpline2::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLTSpline2(void *p) {
      delete ((::TMVA::TSpline2*)p);
   }
   static void deleteArray_TMVAcLcLTSpline2(void *p) {
      delete [] ((::TMVA::TSpline2*)p);
   }
   static void destruct_TMVAcLcLTSpline2(void *p) {
      typedef ::TMVA::TSpline2 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TSpline2

namespace TMVA {
//______________________________________________________________________________
void TSpline1::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::TSpline1.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::TSpline1::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::TSpline1::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLTSpline1(void *p) {
      delete ((::TMVA::TSpline1*)p);
   }
   static void deleteArray_TMVAcLcLTSpline1(void *p) {
      delete [] ((::TMVA::TSpline1*)p);
   }
   static void destruct_TMVAcLcLTSpline1(void *p) {
      typedef ::TMVA::TSpline1 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::TSpline1

namespace TMVA {
//______________________________________________________________________________
void PDF::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::PDF.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::PDF::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::PDF::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLPDF(void *p) {
      delete ((::TMVA::PDF*)p);
   }
   static void deleteArray_TMVAcLcLPDF(void *p) {
      delete [] ((::TMVA::PDF*)p);
   }
   static void destruct_TMVAcLcLPDF(void *p) {
      typedef ::TMVA::PDF current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::PDF

namespace TMVA {
//______________________________________________________________________________
void BinaryTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::BinaryTree.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::BinaryTree::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::BinaryTree::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLBinaryTree(void *p) {
      delete ((::TMVA::BinaryTree*)p);
   }
   static void deleteArray_TMVAcLcLBinaryTree(void *p) {
      delete [] ((::TMVA::BinaryTree*)p);
   }
   static void destruct_TMVAcLcLBinaryTree(void *p) {
      typedef ::TMVA::BinaryTree current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::BinaryTree

namespace TMVA {
//______________________________________________________________________________
void BinarySearchTreeNode::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::BinarySearchTreeNode.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::BinarySearchTreeNode::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::BinarySearchTreeNode::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLBinarySearchTreeNode(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::BinarySearchTreeNode : new ::TMVA::BinarySearchTreeNode;
   }
   static void *newArray_TMVAcLcLBinarySearchTreeNode(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::BinarySearchTreeNode[nElements] : new ::TMVA::BinarySearchTreeNode[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLBinarySearchTreeNode(void *p) {
      delete ((::TMVA::BinarySearchTreeNode*)p);
   }
   static void deleteArray_TMVAcLcLBinarySearchTreeNode(void *p) {
      delete [] ((::TMVA::BinarySearchTreeNode*)p);
   }
   static void destruct_TMVAcLcLBinarySearchTreeNode(void *p) {
      typedef ::TMVA::BinarySearchTreeNode current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::BinarySearchTreeNode

namespace TMVA {
//______________________________________________________________________________
void BinarySearchTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::BinarySearchTree.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::BinarySearchTree::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::BinarySearchTree::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLBinarySearchTree(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::BinarySearchTree : new ::TMVA::BinarySearchTree;
   }
   static void *newArray_TMVAcLcLBinarySearchTree(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::BinarySearchTree[nElements] : new ::TMVA::BinarySearchTree[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLBinarySearchTree(void *p) {
      delete ((::TMVA::BinarySearchTree*)p);
   }
   static void deleteArray_TMVAcLcLBinarySearchTree(void *p) {
      delete [] ((::TMVA::BinarySearchTree*)p);
   }
   static void destruct_TMVAcLcLBinarySearchTree(void *p) {
      typedef ::TMVA::BinarySearchTree current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::BinarySearchTree

namespace TMVA {
//______________________________________________________________________________
void Timer::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Timer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Timer::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Timer::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLTimer(void *p) {
      return  p ? new(p) ::TMVA::Timer : new ::TMVA::Timer;
   }
   static void *newArray_TMVAcLcLTimer(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::Timer[nElements] : new ::TMVA::Timer[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLTimer(void *p) {
      delete ((::TMVA::Timer*)p);
   }
   static void deleteArray_TMVAcLcLTimer(void *p) {
      delete [] ((::TMVA::Timer*)p);
   }
   static void destruct_TMVAcLcLTimer(void *p) {
      typedef ::TMVA::Timer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Timer

namespace TMVA {
//______________________________________________________________________________
void RootFinder::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::RootFinder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::RootFinder::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::RootFinder::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLRootFinder(void *p) {
      delete ((::TMVA::RootFinder*)p);
   }
   static void deleteArray_TMVAcLcLRootFinder(void *p) {
      delete [] ((::TMVA::RootFinder*)p);
   }
   static void destruct_TMVAcLcLRootFinder(void *p) {
      typedef ::TMVA::RootFinder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::RootFinder

namespace TMVA {
//______________________________________________________________________________
void CrossEntropy::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::CrossEntropy.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::CrossEntropy::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::CrossEntropy::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLCrossEntropy(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::CrossEntropy : new ::TMVA::CrossEntropy;
   }
   static void *newArray_TMVAcLcLCrossEntropy(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::CrossEntropy[nElements] : new ::TMVA::CrossEntropy[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLCrossEntropy(void *p) {
      delete ((::TMVA::CrossEntropy*)p);
   }
   static void deleteArray_TMVAcLcLCrossEntropy(void *p) {
      delete [] ((::TMVA::CrossEntropy*)p);
   }
   static void destruct_TMVAcLcLCrossEntropy(void *p) {
      typedef ::TMVA::CrossEntropy current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::CrossEntropy

namespace TMVA {
//______________________________________________________________________________
void DecisionTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::DecisionTree.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::DecisionTree::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::DecisionTree::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLDecisionTree(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::DecisionTree : new ::TMVA::DecisionTree;
   }
   static void *newArray_TMVAcLcLDecisionTree(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::DecisionTree[nElements] : new ::TMVA::DecisionTree[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLDecisionTree(void *p) {
      delete ((::TMVA::DecisionTree*)p);
   }
   static void deleteArray_TMVAcLcLDecisionTree(void *p) {
      delete [] ((::TMVA::DecisionTree*)p);
   }
   static void destruct_TMVAcLcLDecisionTree(void *p) {
      typedef ::TMVA::DecisionTree current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::DecisionTree

namespace TMVA {
//______________________________________________________________________________
void DecisionTreeNode::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::DecisionTreeNode.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::DecisionTreeNode::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::DecisionTreeNode::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLDecisionTreeNode(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::DecisionTreeNode : new ::TMVA::DecisionTreeNode;
   }
   static void *newArray_TMVAcLcLDecisionTreeNode(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::DecisionTreeNode[nElements] : new ::TMVA::DecisionTreeNode[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLDecisionTreeNode(void *p) {
      delete ((::TMVA::DecisionTreeNode*)p);
   }
   static void deleteArray_TMVAcLcLDecisionTreeNode(void *p) {
      delete [] ((::TMVA::DecisionTreeNode*)p);
   }
   static void destruct_TMVAcLcLDecisionTreeNode(void *p) {
      typedef ::TMVA::DecisionTreeNode current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::DecisionTreeNode

namespace TMVA {
//______________________________________________________________________________
void MisClassificationError::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::MisClassificationError.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::MisClassificationError::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::MisClassificationError::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLMisClassificationError(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::MisClassificationError : new ::TMVA::MisClassificationError;
   }
   static void *newArray_TMVAcLcLMisClassificationError(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::MisClassificationError[nElements] : new ::TMVA::MisClassificationError[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLMisClassificationError(void *p) {
      delete ((::TMVA::MisClassificationError*)p);
   }
   static void deleteArray_TMVAcLcLMisClassificationError(void *p) {
      delete [] ((::TMVA::MisClassificationError*)p);
   }
   static void destruct_TMVAcLcLMisClassificationError(void *p) {
      typedef ::TMVA::MisClassificationError current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::MisClassificationError

namespace TMVA {
//______________________________________________________________________________
void Node::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Node.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Node::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Node::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLNode(void *p) {
      delete ((::TMVA::Node*)p);
   }
   static void deleteArray_TMVAcLcLNode(void *p) {
      delete [] ((::TMVA::Node*)p);
   }
   static void destruct_TMVAcLcLNode(void *p) {
      typedef ::TMVA::Node current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Node

namespace TMVA {
//______________________________________________________________________________
void SdivSqrtSplusB::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::SdivSqrtSplusB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::SdivSqrtSplusB::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::SdivSqrtSplusB::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLSdivSqrtSplusB(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::SdivSqrtSplusB : new ::TMVA::SdivSqrtSplusB;
   }
   static void *newArray_TMVAcLcLSdivSqrtSplusB(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::SdivSqrtSplusB[nElements] : new ::TMVA::SdivSqrtSplusB[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLSdivSqrtSplusB(void *p) {
      delete ((::TMVA::SdivSqrtSplusB*)p);
   }
   static void deleteArray_TMVAcLcLSdivSqrtSplusB(void *p) {
      delete [] ((::TMVA::SdivSqrtSplusB*)p);
   }
   static void destruct_TMVAcLcLSdivSqrtSplusB(void *p) {
      typedef ::TMVA::SdivSqrtSplusB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::SdivSqrtSplusB

namespace TMVA {
//______________________________________________________________________________
void SeparationBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::SeparationBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::SeparationBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::SeparationBase::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLSeparationBase(void *p) {
      delete ((::TMVA::SeparationBase*)p);
   }
   static void deleteArray_TMVAcLcLSeparationBase(void *p) {
      delete [] ((::TMVA::SeparationBase*)p);
   }
   static void destruct_TMVAcLcLSeparationBase(void *p) {
      typedef ::TMVA::SeparationBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::SeparationBase

namespace TMVA {
//______________________________________________________________________________
void RegressionVariance::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::RegressionVariance.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::RegressionVariance::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::RegressionVariance::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLRegressionVariance(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::RegressionVariance : new ::TMVA::RegressionVariance;
   }
   static void *newArray_TMVAcLcLRegressionVariance(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::RegressionVariance[nElements] : new ::TMVA::RegressionVariance[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLRegressionVariance(void *p) {
      delete ((::TMVA::RegressionVariance*)p);
   }
   static void deleteArray_TMVAcLcLRegressionVariance(void *p) {
      delete [] ((::TMVA::RegressionVariance*)p);
   }
   static void destruct_TMVAcLcLRegressionVariance(void *p) {
      typedef ::TMVA::RegressionVariance current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::RegressionVariance

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLTools(void *p) {
      delete ((::TMVA::Tools*)p);
   }
   static void deleteArray_TMVAcLcLTools(void *p) {
      delete [] ((::TMVA::Tools*)p);
   }
   static void destruct_TMVAcLcLTools(void *p) {
      typedef ::TMVA::Tools current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Tools

namespace TMVA {
//______________________________________________________________________________
void Reader::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::Reader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::Reader::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::Reader::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLReader(void *p) {
      return  p ? new(p) ::TMVA::Reader : new ::TMVA::Reader;
   }
   static void *newArray_TMVAcLcLReader(Long_t nElements, void *p) {
      return p ? new(p) ::TMVA::Reader[nElements] : new ::TMVA::Reader[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLReader(void *p) {
      delete ((::TMVA::Reader*)p);
   }
   static void deleteArray_TMVAcLcLReader(void *p) {
      delete [] ((::TMVA::Reader*)p);
   }
   static void destruct_TMVAcLcLReader(void *p) {
      typedef ::TMVA::Reader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::Reader

namespace TMVA {
//______________________________________________________________________________
void GeneticAlgorithm::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GeneticAlgorithm.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GeneticAlgorithm::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GeneticAlgorithm::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLGeneticAlgorithm(void *p) {
      delete ((::TMVA::GeneticAlgorithm*)p);
   }
   static void deleteArray_TMVAcLcLGeneticAlgorithm(void *p) {
      delete [] ((::TMVA::GeneticAlgorithm*)p);
   }
   static void destruct_TMVAcLcLGeneticAlgorithm(void *p) {
      typedef ::TMVA::GeneticAlgorithm current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GeneticAlgorithm

namespace TMVA {
//______________________________________________________________________________
void GeneticGenes::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GeneticGenes.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GeneticGenes::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GeneticGenes::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLGeneticGenes(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::GeneticGenes : new ::TMVA::GeneticGenes;
   }
   static void *newArray_TMVAcLcLGeneticGenes(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::GeneticGenes[nElements] : new ::TMVA::GeneticGenes[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLGeneticGenes(void *p) {
      delete ((::TMVA::GeneticGenes*)p);
   }
   static void deleteArray_TMVAcLcLGeneticGenes(void *p) {
      delete [] ((::TMVA::GeneticGenes*)p);
   }
   static void destruct_TMVAcLcLGeneticGenes(void *p) {
      typedef ::TMVA::GeneticGenes current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GeneticGenes

namespace TMVA {
//______________________________________________________________________________
void GeneticPopulation::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GeneticPopulation.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GeneticPopulation::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GeneticPopulation::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLGeneticPopulation(void *p) {
      delete ((::TMVA::GeneticPopulation*)p);
   }
   static void deleteArray_TMVAcLcLGeneticPopulation(void *p) {
      delete [] ((::TMVA::GeneticPopulation*)p);
   }
   static void destruct_TMVAcLcLGeneticPopulation(void *p) {
      typedef ::TMVA::GeneticPopulation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GeneticPopulation

namespace TMVA {
//______________________________________________________________________________
void GeneticRange::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GeneticRange.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GeneticRange::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GeneticRange::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLGeneticRange(void *p) {
      delete ((::TMVA::GeneticRange*)p);
   }
   static void deleteArray_TMVAcLcLGeneticRange(void *p) {
      delete [] ((::TMVA::GeneticRange*)p);
   }
   static void destruct_TMVAcLcLGeneticRange(void *p) {
      typedef ::TMVA::GeneticRange current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GeneticRange

namespace TMVA {
//______________________________________________________________________________
void GiniIndex::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GiniIndex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GiniIndex::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GiniIndex::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLGiniIndex(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::GiniIndex : new ::TMVA::GiniIndex;
   }
   static void *newArray_TMVAcLcLGiniIndex(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::GiniIndex[nElements] : new ::TMVA::GiniIndex[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLGiniIndex(void *p) {
      delete ((::TMVA::GiniIndex*)p);
   }
   static void deleteArray_TMVAcLcLGiniIndex(void *p) {
      delete [] ((::TMVA::GiniIndex*)p);
   }
   static void destruct_TMVAcLcLGiniIndex(void *p) {
      typedef ::TMVA::GiniIndex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GiniIndex

namespace TMVA {
//______________________________________________________________________________
void GiniIndexWithLaplace::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::GiniIndexWithLaplace.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::GiniIndexWithLaplace::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::GiniIndexWithLaplace::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLGiniIndexWithLaplace(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::GiniIndexWithLaplace : new ::TMVA::GiniIndexWithLaplace;
   }
   static void *newArray_TMVAcLcLGiniIndexWithLaplace(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::GiniIndexWithLaplace[nElements] : new ::TMVA::GiniIndexWithLaplace[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLGiniIndexWithLaplace(void *p) {
      delete ((::TMVA::GiniIndexWithLaplace*)p);
   }
   static void deleteArray_TMVAcLcLGiniIndexWithLaplace(void *p) {
      delete [] ((::TMVA::GiniIndexWithLaplace*)p);
   }
   static void destruct_TMVAcLcLGiniIndexWithLaplace(void *p) {
      typedef ::TMVA::GiniIndexWithLaplace current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::GiniIndexWithLaplace

namespace TMVA {
//______________________________________________________________________________
void SimulatedAnnealing::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::SimulatedAnnealing.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::SimulatedAnnealing::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::SimulatedAnnealing::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrapper around operator delete
   static void delete_TMVAcLcLSimulatedAnnealing(void *p) {
      delete ((::TMVA::SimulatedAnnealing*)p);
   }
   static void deleteArray_TMVAcLcLSimulatedAnnealing(void *p) {
      delete [] ((::TMVA::SimulatedAnnealing*)p);
   }
   static void destruct_TMVAcLcLSimulatedAnnealing(void *p) {
      typedef ::TMVA::SimulatedAnnealing current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::SimulatedAnnealing

namespace TMVA {
//______________________________________________________________________________
void QuickMVAProbEstimator::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMVA::QuickMVAProbEstimator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMVA::QuickMVAProbEstimator::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMVA::QuickMVAProbEstimator::Class(),this);
   }
}

} // namespace TMVA
namespace ROOT {
   // Wrappers around operator new
   static void *new_TMVAcLcLQuickMVAProbEstimator(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::QuickMVAProbEstimator : new ::TMVA::QuickMVAProbEstimator;
   }
   static void *newArray_TMVAcLcLQuickMVAProbEstimator(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMVA::QuickMVAProbEstimator[nElements] : new ::TMVA::QuickMVAProbEstimator[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMVAcLcLQuickMVAProbEstimator(void *p) {
      delete ((::TMVA::QuickMVAProbEstimator*)p);
   }
   static void deleteArray_TMVAcLcLQuickMVAProbEstimator(void *p) {
      delete [] ((::TMVA::QuickMVAProbEstimator*)p);
   }
   static void destruct_TMVAcLcLQuickMVAProbEstimator(void *p) {
      typedef ::TMVA::QuickMVAProbEstimator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMVA::QuickMVAProbEstimator

namespace {
  void TriggerDictionaryInitialization_dict2_Impl() {
    static const char* headers[] = {
"inc/TMVA/TSpline2.h",
"inc/TMVA/TSpline1.h",
"inc/TMVA/PDF.h",
"inc/TMVA/BinaryTree.h",
"inc/TMVA/BinarySearchTreeNode.h",
"inc/TMVA/BinarySearchTree.h",
"inc/TMVA/Timer.h",
"inc/TMVA/RootFinder.h",
"inc/TMVA/CrossEntropy.h",
"inc/TMVA/DecisionTree.h",
"inc/TMVA/DecisionTreeNode.h",
"inc/TMVA/MisClassificationError.h",
"inc/TMVA/Node.h",
"inc/TMVA/SdivSqrtSplusB.h",
"inc/TMVA/SeparationBase.h",
"inc/TMVA/RegressionVariance.h",
"inc/TMVA/Tools.h",
"inc/TMVA/Reader.h",
"inc/TMVA/GeneticAlgorithm.h",
"inc/TMVA/GeneticGenes.h",
"inc/TMVA/GeneticPopulation.h",
"inc/TMVA/GeneticRange.h",
"inc/TMVA/GiniIndex.h",
"inc/TMVA/GiniIndexWithLaplace.h",
"inc/TMVA/SimulatedAnnealing.h",
"inc/TMVA/QuickMVAProbEstimator.h",
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
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Quadratic interpolation class (using quadrax))ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TSpline2.h")))  TSpline2;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Linear interpolation class)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/TSpline1.h")))  TSpline1;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(PDF wrapper for histograms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/PDF.h")))  PDF;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Base class for BinarySearch and Decision Trees)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/BinaryTree.h")))  BinaryTree;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Node for the BinarySearchTree)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/BinarySearchTreeNode.h")))  BinarySearchTreeNode;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Binary search tree including volume search method)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/BinarySearchTree.h")))  BinarySearchTree;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Timing information for training and evaluation of MVA methods)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Timer.h")))  Timer;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Root finding using Brents algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/RootFinder.h")))  RootFinder;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of the CrossEntropy as separation criterion)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/CrossEntropy.h")))  CrossEntropy;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(implementation of a Decision Tree)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/DecisionTree.h")))  DecisionTree;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Node for the Decision Tree)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/DecisionTree.h")))  DecisionTreeNode;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of the MisClassificationError as separation criterion)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/MisClassificationError.h")))  MisClassificationError;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Node for the BinarySearch or Decision Trees)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/BinaryTree.h")))  Node;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of the SdivSqrtSplusB as separation criterion)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/SdivSqrtSplusB.h")))  SdivSqrtSplusB;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface to different separation critiera used in training algorithms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/CrossEntropy.h")))  SeparationBase;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface to different separation critiera used in training algorithms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/DecisionTree.h")))  RegressionVariance;}
namespace TMVA{class __attribute__((annotate("$clingAutoload$inc/TMVA/Tools.h")))  Tools;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interpret the trained MVAs in an analysis context)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/Reader.h")))  Reader;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Genetic algorithm controller)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GeneticAlgorithm.h")))  GeneticAlgorithm;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Genes definition for genetic algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GeneticAlgorithm.h")))  GeneticGenes;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Population definition for genetic algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GeneticAlgorithm.h")))  GeneticPopulation;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Range definition for genetic algorithm)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GeneticAlgorithm.h")))  GeneticRange;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of the GiniIndex as separation criterion)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GiniIndex.h")))  GiniIndex;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Implementation of the GiniIndexWithLaplace as separation criterion)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/GiniIndexWithLaplace.h")))  GiniIndexWithLaplace;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Base class for Simulated Annealing fitting)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/SimulatedAnnealing.h")))  SimulatedAnnealing;}
namespace TMVA{class __attribute__((annotate(R"ATTRDUMP(Interface to different separation critiera used in training algorithms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$inc/TMVA/QuickMVAProbEstimator.h")))  QuickMVAProbEstimator;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "inc/TMVA/TSpline2.h"
#include "inc/TMVA/TSpline1.h"
#include "inc/TMVA/PDF.h"
#include "inc/TMVA/BinaryTree.h"
#include "inc/TMVA/BinarySearchTreeNode.h"
#include "inc/TMVA/BinarySearchTree.h"
#include "inc/TMVA/Timer.h"
#include "inc/TMVA/RootFinder.h"
#include "inc/TMVA/CrossEntropy.h"
#include "inc/TMVA/DecisionTree.h"
#include "inc/TMVA/DecisionTreeNode.h"
#include "inc/TMVA/MisClassificationError.h"
#include "inc/TMVA/Node.h"
#include "inc/TMVA/SdivSqrtSplusB.h"
#include "inc/TMVA/SeparationBase.h"
#include "inc/TMVA/RegressionVariance.h"
#include "inc/TMVA/Tools.h"
#include "inc/TMVA/Reader.h"
#include "inc/TMVA/GeneticAlgorithm.h"
#include "inc/TMVA/GeneticGenes.h"
#include "inc/TMVA/GeneticPopulation.h"
#include "inc/TMVA/GeneticRange.h"
#include "inc/TMVA/GiniIndex.h"
#include "inc/TMVA/GiniIndexWithLaplace.h"
#include "inc/TMVA/SimulatedAnnealing.h"
#include "inc/TMVA/QuickMVAProbEstimator.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TMVA::BinarySearchTree", payloadCode, "@",
"TMVA::BinarySearchTreeNode", payloadCode, "@",
"TMVA::BinaryTree", payloadCode, "@",
"TMVA::CrossEntropy", payloadCode, "@",
"TMVA::DecisionTree", payloadCode, "@",
"TMVA::DecisionTreeNode", payloadCode, "@",
"TMVA::GeneticAlgorithm", payloadCode, "@",
"TMVA::GeneticGenes", payloadCode, "@",
"TMVA::GeneticPopulation", payloadCode, "@",
"TMVA::GeneticRange", payloadCode, "@",
"TMVA::GiniIndex", payloadCode, "@",
"TMVA::GiniIndexWithLaplace", payloadCode, "@",
"TMVA::MisClassificationError", payloadCode, "@",
"TMVA::Node", payloadCode, "@",
"TMVA::PDF", payloadCode, "@",
"TMVA::QuickMVAProbEstimator", payloadCode, "@",
"TMVA::Reader", payloadCode, "@",
"TMVA::RegressionVariance", payloadCode, "@",
"TMVA::RootFinder", payloadCode, "@",
"TMVA::SdivSqrtSplusB", payloadCode, "@",
"TMVA::SeparationBase", payloadCode, "@",
"TMVA::SimulatedAnnealing", payloadCode, "@",
"TMVA::TSpline1", payloadCode, "@",
"TMVA::TSpline2", payloadCode, "@",
"TMVA::Timer", payloadCode, "@",
"TMVA::Tools", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dict2",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict2_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict2_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict2() {
  TriggerDictionaryInitialization_dict2_Impl();
}
