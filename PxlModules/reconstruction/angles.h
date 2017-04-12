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
        //w polarization - normal basis
        pxl::Basic3Vector normalAxis = lightjet->getVector().cross(wboson->getVector());
        eventView->setUserRecord(prefix+"cosTheta_wN",angleInRestFrame(lepton->getVector(),wboson->getBoostVector(),normalAxis,wboson->getBoostVector()));
        //w polarization - transvers basis
        pxl::Basic3Vector transverseAxis = wboson->getVector().cross(normalAxis);
        eventView->setUserRecord(prefix+"cosTheta_wT",angleInRestFrame(lepton->getVector(),wboson->getBoostVector(),transverseAxis,wboson->getBoostVector()));

        //top polarization - lepton
        eventView->setUserRecord(prefix+"cosTheta_tPL",angleInRestFrame(lepton->getVector(),top->getBoostVector(),lightjet->getVector(),top->getBoostVector()));
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
