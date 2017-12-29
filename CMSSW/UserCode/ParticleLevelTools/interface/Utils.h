#ifndef __ParticleLevelTools_Utils_H__
#define __ParticleLevelTools_Utils_H__

namespace plt
{

bool isBHadron(const int pdgId)
{
    unsigned int absPdgId = std::abs(pdgId);
    if ( absPdgId <= 100 ) return false; // Fundamental particles and MC internals
    if ( absPdgId >= 1000000000 ) return false; // Nuclei, +-10LZZZAAAI

    // General form of PDG ID is 7 digit form
    // +- n nr nL nq1 nq2 nq3 nJ
    //const int nJ = absPdgId % 10; // Spin
    const int nq3 = (absPdgId / 10) % 10;
    const int nq2 = (absPdgId / 100) % 10;
    const int nq1 = (absPdgId / 1000) % 10;

    if ( nq3 == 0 ) return false; // Diquarks
    if ( nq1 == 0 and nq2 == 5 ) return true; // B mesons
    if ( nq1 == 5 ) return true; // B baryons

    return false;
}

}

#endif
