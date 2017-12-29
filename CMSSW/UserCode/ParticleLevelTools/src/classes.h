#ifndef __ParticleLevelTools_CLASSES_H__
#define __ParticleLevelTools_CLASSES_H__

#include "UserCode/ParticleLevelTools/interface/Jet.h"
#include "DataFormats/Common/interface/Wrapper.h"

#include <vector>

namespace 
{
  plt::Jet dummy1;
  edm::Wrapper<plt::Jet> dummy2;
  std::vector<plt::Jet> dummy3;
  edm::Wrapper<std::vector<plt::Jet>> dummy4;
}



#endif

