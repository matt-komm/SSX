#ifndef __ANGLES_H__
#define __ANGLES_H__

float angle(const pxl::Basic3Vector& v1, const pxl::Basic3Vector& v2)
{
    return (v1.getX()*v2.getX()+v1.getY()*v2.getY()+v1.getZ()*v2.getZ())/(v1.getMag()*v2.getMag());
}

float angleInRestFrame(const pxl::LorentzVector& p1, const pxl::Basic3Vector& boost1, const pxl::LorentzVector& p2, const pxl::Basic3Vector& boost2)
{
    pxl::LorentzVector boostedP1 = p1;
    boostedP1.boost(-boost1);
    pxl::LorentzVector boostedP2 = p2;
    boostedP2.boost(-boost2);

    return angle(boostedP1,boostedP2);
}

pxl::LorentzVector boostToRestFrame(const pxl::Particle& particle, const pxl::Particle& rest)
{
    pxl::LorentzVector boostedP = particle.getVector();
    boostedP.boost(-rest.getBoostVector());
    return boostedP;
}

double calculateMTW(pxl::Particle* lepton, pxl::Particle* met)
{
    return sqrt((lepton->getPt()+met->getPt())*(lepton->getPt()+met->getPt())-(lepton->getPx()+met->getPx())*(lepton->getPx()+met->getPx())-(lepton->getPy()+met->getPy())*(lepton->getPy()+met->getPy()));           
}

void calculateAngles(pxl::EventView* eventView, const std::string& prefix, pxl::Particle* lepton, pxl::Particle* neutrino, pxl::Particle* wboson, pxl::Particle* bjet, pxl::Particle* top, pxl::Particle* lightjet)
{
    if (eventView && lepton && wboson && top)
    {
        //w polarization - helicity basis (l in W system vs. W in top system)
        eventView->setUserRecord(prefix+"cosTheta_wH",angleInRestFrame(lepton->getVector(),wboson->getBoostVector(),wboson->getVector(),top->getBoostVector()));
    }
    
    if (eventView && lepton && wboson && top && lightjet)
    {
        pxl::LorentzVector spectatorQuarkBoosted = boostToRestFrame(*lightjet,*top);
        pxl::LorentzVector leptonBoosted = boostToRestFrame(*lepton,*top);
        pxl::Particle initialQuark;
        initialQuark.setP4(0,0,lightjet->getPz(),std::fabs(lightjet->getPz()));
        //pxl::LorentzVector initialQuarkBoosted = boostToRestFrame(initialQuark,*top);
        
        //top polarization (z)
        eventView->setUserRecord(prefix+"cosTheta_tPLz",angle(leptonBoosted,spectatorQuarkBoosted));
        
        //normal basis (y)
        pxl::Basic3Vector normalAxis = spectatorQuarkBoosted.cross(initialQuark.getVector());
        eventView->setUserRecord(prefix+"cosTheta_tPLy",angle(leptonBoosted,normalAxis));
        
        //transverse basis (x)
        pxl::Basic3Vector transverseAxis = spectatorQuarkBoosted.cross(normalAxis);
        eventView->setUserRecord(prefix+"cosTheta_tPLx",angle(leptonBoosted,transverseAxis));

    }
    if (eventView && top && lightjet && bjet && neutrino)
    {
        //top polarization - bjet
        eventView->setUserRecord(prefix+"cosTheta_tPB",angleInRestFrame(bjet->getVector(),top->getBoostVector(),lightjet->getVector(),top->getBoostVector()));
        //top polarization - neutrino
        eventView->setUserRecord(prefix+"cosTheta_tPN",angleInRestFrame(neutrino->getVector(),top->getBoostVector(),lightjet->getVector(),top->getBoostVector()));                    
    }
}

#endif
