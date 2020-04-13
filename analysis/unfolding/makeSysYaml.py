import json
import math
import numpy
import random
import ROOT

systematicsProfiled = [
    ['Statistical',['stat']],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ normalisation',['TopBkg*Excl']],
    ['W/Z/$\\gamma^{\\star}$+jets normalisation',['WZjets*Excl','dyExcl','twExcl']],
    ['Multijet normalisation',['QCD*Excl']],
    ['Multijet shape',['eleMultiIsoExcl','eleMultiVetoExcl','muMultiExcl']],
    ['Jet energy scale and resolution',['enExcl','resExcl']],
    ['b tagging efficiencies and misidentification',['btagExcl','ltagExcl']],
    #['Lepton efficiencies',['eleEffExcl','muEffExcl']],
    ['Others (lepton efficiencies, pileup, unclustered energy)',['puExcl','uncExcl','eleEffExcl','muEffExcl']],
]

systematics = [
    ['Top quark mass',['topMass']],
    ['PDF+$\\alpha_{S}$',['pdf']],
    ['$t$ channel renormalisation and factorisation scales',['tchanScaleME']],
    ['$t$ channel parton shower',['tchanHdampPS','tchanScalePS']],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ renormalisation and factorisation scales',['ttbarScaleME']],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ underlying event tune',['ttbarUE']],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ $p_{\\textrm{T}}$ reweighting',['ttbarPt']],
    ['W+jets renormalisation and factorisation scales',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    #['Luminosity',['lumi']]
    #['Others (\\wjets ME scale, \\ttbar \\pt rew., \\ttbar ME scale)',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    #['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
]




def formatExp(value):
    n = int(math.floor(math.log10(math.fabs(value))))
    if n<2 and n>=1:
        return value,0
    else:
        return value/10**n,n
        
        
setups = [
    ["pt", {
        'name':"%s-level top quark $p_\\textrm{T}$",
        'locations':{
            'sum':{'parton':'Figure 7, upper row, left column (page 18 of preprint)','particle':'Figure 8, upper row, left column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, upper row, left column (page 20 of preprint)','particle':'Figure 10, upper row, left column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, upper row, left column (page 22 of preprint)','particle':'Figure 12, upper row, left column (page 23 of preprint)'},
        },
        
        'units': "GEV",
        "sum":{"obs": "DSIG(%s)/DPT", "var": "$\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}$", "units": "pb GEV**-1"},
        "norm":{"obs": "1/SIG * DSIG(%s)/DPT", "var": "$1/\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}\\times\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}$", "units": "GEV**-1"},
        "ratio":{"obs": "RATIO(%s/DPT)", "var": "$\\frac{\\textrm{d}\\sigma_{\\textrm{t}}/\\textrm{d}p_{\\textrm{T}}}{\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}}$"},
    }],
    ["y", {
        'name':"%s-level top quark rapidity",
        'locations':{
            'sum':{'parton':'Figure 7, upper row, right column (page 18 of preprint)','particle':'Figure 8, upper row, right column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, upper row, right column (page 20 of preprint)','particle':'Figure 10, upper row, right column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, upper row, right column (page 22 of preprint)','particle':'Figure 12, upper row, right column (page 23 of preprint)'},
        },
        "sum":{"obs": "DSIG(%s)/DABS(ETARAP)", "var": "$\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}|y|$", "units": "pb"},
        "norm":{"obs": "1/SIG * DSIG(%s)/DABS(ETARAP)", "var": "$1/\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}\\times\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}|y|$"},
        "ratio":{"obs": "RATIO(%s/DABS(ETARAP))", "var": "$\\frac{\\textrm{d}\\sigma_{\\textrm{t}}/\\textrm{d}|y|}{\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}|y|}$"},
    }],
    ["lpt", {
        'name':"%s-level charged lepton $p_\\textrm{T}$",
        'locations':{
            'sum':{'parton':'Figure 7, middle row, left column (page 18 of preprint)','particle':'Figure 8, middle row, left column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, middle row, left column (page 20 of preprint)','particle':'Figure 10, middle row, left column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, middle row, left column (page 22 of preprint)','particle':'Figure 12, middle row, left column (page 23 of preprint)'},
        },
        
        'units': "GEV",
        "sum":{"obs": "DSIG(%s)/DPT", "var": "$\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}$", "units": "pb GEV**-1"},
        "norm":{"obs": "1/SIG * DSIG(%s)/DPT", "var": "$1/\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}\\times\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}$", "units": "GEV**-1"},
        "ratio":{"obs": "RATIO(%s/DPT)", "var": "$\\frac{\\textrm{d}\\sigma_{\\textrm{t}}/\\textrm{d}p_{\\textrm{T}}}{\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}}$"},
    }],
    ["leta", {
        'name':"%s-level charged lepton rapidity",
        'locations':{
            'sum':{'parton':'Figure 7, middle row, right column (page 18 of preprint)','particle':'Figure 8, middle row, right column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, middle row, right column (page 20 of preprint)','particle':'Figure 10, middle row, right column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, middle row, right column (page 22 of preprint)','particle':'Figure 12, middle row, right column (page 23 of preprint)'},
        },
        "sum":{"obs": "DSIG(%s)/DABS(ETARAP)", "var": "$\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}|y|$", "units": "pb"},
        "norm":{"obs": "1/SIG * DSIG(%s)/DABS(ETARAP)", "var": "$1/\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}\\times\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}|y|$"},
        "ratio":{"obs": "RATIO(%s/DABS(ETARAP))", "var": "$\\frac{\\textrm{d}\\sigma_{\\textrm{t}}/\\textrm{d}|y|}{\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}|y|}$"},
    }],
    ["wpt", {
        'name':"%s-level W boson $p_\\textrm{T}$",
        'locations':{
            'sum':{'parton':'Figure 7, lower row, left column (page 18 of preprint)','particle':'Figure 8, lower row, left column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, lower row, left column (page 20 of preprint)','particle':'Figure 10, lower row, left column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, lower row, left column (page 22 of preprint)','particle':'Figure 12, lower row, left column (page 23 of preprint)'},
        },
        
        'units': "GEV",
        "sum":{"obs": "DSIG(%s)/DPT", "var": "$\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}$", "units": "pb GEV**-1"},
        "norm":{"obs": "1/SIG * DSIG(%s)/DPT", "var": "$1/\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}\\times\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}$", "units": "GEV**-1"},
        "ratio":{"obs": "RATIO(%s/DPT)", "var": "$\\frac{\\textrm{d}\\sigma_{\\textrm{t}}/\\textrm{d}p_{\\textrm{T}}}{\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{d}p_{\\textrm{T}}}$"},
    }],
    ["cos", {
        'name':"%s-level cosine of the top quark polarisation angle",
        'locations':{
            'sum':{'parton':'Figure 7, lower row, right column (page 18 of preprint)','particle':'Figure 8, lower row, right column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, lower row, right column (page 20 of preprint)','particle':'Figure 10, lower row, right column (page 21 of preprint)'},
        },
        "sum":{"obs": "DSIG(%s)/DCOS(THETA)", "var": "$\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{dcos}\\theta^{\\star}_{\\textrm{pol}}$", "units": "pb"},
        "norm":{"obs": "1/SIG * DSIG(%s)/DCOS(THETA)", "var": "$1/\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}\\times\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{dcos}\\theta^{\\star}_{\\textrm{pol}}$"},
        "ratio":{"obs": "RATIO(%s/DCOS(THETA))", "var": "$\\frac{\\textrm{d}\\sigma_{\\textrm{t}}/\\textrm{dcos}\\theta^{\\star}_{\\textrm{pol}}}{\\textrm{d}\\sigma_{\\textrm{t}+\\bar{\\textrm{t}}}/\\textrm{dcos}\\theta^{\\star}_{\\textrm{pol}}}$"},
    }],
]

yamlSubmissionFile = open("submission.yaml","w")

yamlSubmissionFile.write('additional_resources:\n')
yamlSubmissionFile.write('- {description: web page with auxiliary material, location: \'http://cms-results.web.cern.ch/cms-results/public-results/publications/TOP-17-023/index.html\'}\n')
yamlSubmissionFile.write('- {description: archive location of paper, location: \'https://arxiv.org/abs/1907.08330\'}\n')

yamlSubmissionFile.write('comment: \'A measurement is presented of differential cross sections for $t$-channel single top quark and antiquark production in proton-proton collisions at a centre-of-mass energy of $13~\\rm{TeV}$ by the CMS experiment at the LHC. From a data set corresponding to an integrated luminosity of $35.9~\\rm{fb}^{-1}$, events containing one muon or electron and two or three jets are analysed. The cross section is measured as a function of the top quark transverse momentum ($p_{\\rm{T}}$), rapidity, and polarisation angle, the charged lepton $p_{\\rm{T}}$ and rapidity, and the $p_{\\rm{T}}$ of the W boson from the top quark decay. In addition, the charge ratio is measured differentially as a function of the top quark, charged lepton, and W boson kinematic observables. The results are found to be in agreement with standard model predictions using various next-to-leading-order event generators and sets of parton distribution functions. Additionally, the spin asymmetry, sensitive to the top quark polarisation, is determined from the differential distribution of the polarisation angle at parton level to be $0.440 \pm 0.070$, in agreement with the standard model prediction.\'\n')

itable = 1

for kind in ['sum','norm','ratio']:
    for level in ["parton","particle"]:
        for iobs in range(len(setups)):
    
            fSummary = open("result/final/comb/"+setups[iobs][0]+"_"+level+"_comb_sysSummary.json")
            data = json.load(fSummary)
            
                            
            binning = data['binning']
            nbins = len(binning)-1
            unit = data['unit']
        
        
        
            if kind=='ratio' and setups[iobs][0]=='cos':
                continue
        
            yamlSubmissionFile.write('---\n')
            yamlSubmissionFile.write('name: Table %i\n'%itable)
            itable+=1
            
            
            if kind=='sum':
                yamlSubmissionFile.write("description: 'Differential absolute cross section as a function of the ")
            elif kind=='norm':
                yamlSubmissionFile.write("description: 'Differential normalised cross section as a function of the ")
            elif kind=='ratio':
                yamlSubmissionFile.write("description: 'Differential charge ratio as a function of the ")
            yamlSubmissionFile.write((setups[iobs][1]['name']%(level))+"'\n")
            
            yamlSubmissionFile.write("location: 'Data from "+setups[iobs][1]['locations'][kind][level]+"'\n")
            
            yamlSubmissionFile.write("keywords:\n")
            yamlSubmissionFile.write("  - {name: reactions, values: [P P --> TOP Q]}\n")
            if level == 'parton':
                yamlSubmissionFile.write("  - {name: observables, values: ["+(setups[iobs][1][kind]['obs']%("inclusive"))+"]}\n")
            elif level == 'particle':
                yamlSubmissionFile.write("  - {name: observables, values: ["+(setups[iobs][1][kind]['obs']%("fiducial"))+"]}\n")
            yamlSubmissionFile.write("  - {name: cmenergies, values: [13000.0]}\n")
            yamlSubmissionFile.write("  - {name: phrases, values: [Differential Cross Section, Proton-Proton Scattering, Single Top Production]}\n")
            yamlSubmissionFile.write("data_file: "+setups[iobs][0]+"_"+level+"_"+kind+".yaml\n\n")

            
            yamlDataFile = open(setups[iobs][0]+"_"+level+"_"+kind+".yaml","w")
            yamlDataFile.write("independent_variables:\n")
            
            yamlDataFile.write("- header: {name: '"+(setups[iobs][1]['name']%(level.capitalize()))+"'")
            if setups[iobs][1].has_key('units'):
                yamlDataFile.write(", units: "+(setups[iobs][1]['units']))
            yamlDataFile.write("}\n")
            yamlDataFile.write("  values:\n")
            for ibin in range(nbins):
                yamlDataFile.write("  - {low: %.1f, high: %.1f}\n"%(binning[ibin],binning[ibin+1]))
                
            yamlDataFile.write('dependent_variables:\n')
            if level == 'parton':
                yamlDataFile.write("- header: {name: '"+(setups[iobs][1][kind]['var'])+"'")
            elif level == 'particle':
                yamlDataFile.write("- header: {name: '"+(setups[iobs][1][kind]['var'])+"'")
            if setups[iobs][1][kind].has_key('units'):
                yamlDataFile.write(', units: '+setups[iobs][1][kind]['units'])
            yamlDataFile.write('}\n')
            
            yamlDataFile.write('  qualifiers:\n')
            yamlDataFile.write('  - {name: RE, value: \'$\\rm{pp}\\ \\to\\ \\rm{tq} + \\bar{\\rm{t}}q$, $\\rm{t} \\to \\ell\\nu \\rm{b} (+ \\nu_{\\tau}\\bar{\\nu}_{\\tau})$, $(\\ell = \\mu,\\rm{e})$\'}\n')
            yamlDataFile.write('  - {name: SQRT(S), units: GEV, value: 13000}\n')
            
            yamlDataFile.write('  values:\n')
            for ibin in range(nbins):
                centralVal = data[kind]['central'][ibin]
                val,exp = formatExp(centralVal)
                if exp==0:
                    yamlDataFile.write('  - value: %.1f\n'%(val))
                else:
                    yamlDataFile.write('  - value: %.2e\n'%(centralVal))
                yamlDataFile.write("    errors:\n")
                
                for sysName,subSysList in systematicsProfiled+systematics:
                    sysVal = 0.
                    for subSys in subSysList:
                        sysVal += data[kind][subSys][ibin]**2
                    sysVal = math.sqrt(sysVal)
                    
                    yamlDataFile.write("    - {symerror: %.2e, label: '%s'}\n"%(sysVal,sysName))
                        
                if kind=="sum":
                    yamlDataFile.write("    - {symerror: %.2e, label: '%s'}\n"%(data[kind]['lumi'][ibin],"Luminosity"))
                yamlDataFile.write("    - {symerror: %.2e, label: '%s'}\n"%(data[kind]['prof'][ibin],"Profiled uncertainties only"))
                yamlDataFile.write("    - {symerror: %.2e, label: '%s'}\n"%(data[kind]['total'][ibin],"Total"))
                        
                        
            yamlDataFile.close()
            
            
            
            
            yamlSubmissionFile.write('---\n')
            yamlSubmissionFile.write('name: Table %i\n'%itable)
            itable+=1
            
            
            if kind=='sum':
                yamlSubmissionFile.write("description: 'Covariance of the differential absolute cross section as a function of the ")
            elif kind=='norm':
                yamlSubmissionFile.write("description: 'Covariance of the differential normalised cross section as a function of the ")
            elif kind=='ratio':
                yamlSubmissionFile.write("description: 'Covariance of the differential charge ratio as a function of the ")
            yamlSubmissionFile.write((setups[iobs][1]['name']%(level))+"'\n")
            
            yamlSubmissionFile.write("location: 'Data from additional material on analysis webpage'\n")
            #yamlSubmissionFile.write('location: '+setups[iobs][1]['locations'][kind][level]+'\n')
            
            yamlSubmissionFile.write("keywords:\n")
            yamlSubmissionFile.write("  - {name: reactions, values: [P P --> TOP Q]}\n")
            if level == 'parton':
                yamlSubmissionFile.write("  - {name: observables, values: ["+(setups[iobs][1][kind]['obs']%("inclusive"))+"]}\n")
            elif level == 'particle':
                yamlSubmissionFile.write("  - {name: observables, values: ["+(setups[iobs][1][kind]['obs']%("fiducial"))+"]}\n")
            yamlSubmissionFile.write("  - {name: cmenergies, values: [13000.0]}\n")
            yamlSubmissionFile.write("  - {name: phrases, values: [Differential Cross Section, Proton-Proton Scattering, Single Top Production]}\n")
            yamlSubmissionFile.write("data_file: "+setups[iobs][0]+"_"+level+"_"+kind+"_cov.yaml\n\n")

            
            fCov = ROOT.TFile("result/final/comb/"+setups[iobs][0]+"_"+level+"_comb_hepdata.root")
            if kind=='sum':
                covHist = fCov.Get('xsec_cov')
            if kind=='norm':
                covHist = fCov.Get('xsecnorm_cov')
            if kind=='ratio':
                covHist = fCov.Get('ratio_cov')
            covHist = covHist.Clone(covHist.GetName()+str(random.random()))
            covHist.SetDirectory(0)
            fCov.Close()
                
                
            yamlDataFile = open(setups[iobs][0]+"_"+level+"_"+kind+"_cov.yaml","w")
            yamlDataFile.write("independent_variables:\n")
            
            yamlDataFile.write("- header: {name: '"+(setups[iobs][1]['name']%(level.capitalize()))+"'")
            if setups[iobs][1].has_key('units'):
                yamlDataFile.write(", units: "+(setups[iobs][1]['units']))
            yamlDataFile.write("}\n")
            yamlDataFile.write("  values:\n")
            for ibin in range(nbins):
                for jbin in range(nbins):
                    yamlDataFile.write("  - {low: %.1f, high: %.1f}\n"%(binning[ibin],binning[ibin+1]))
                    
            yamlDataFile.write("- header: {name: '"+(setups[iobs][1]['name']%(level.capitalize()))+"'")
            if setups[iobs][1].has_key('units'):
                yamlDataFile.write(", units: "+(setups[iobs][1]['units']))
            yamlDataFile.write("}\n")
            yamlDataFile.write("  values:\n")
            for ibin in range(nbins):
                for jbin in range(nbins):
                    yamlDataFile.write("  - {low: %.1f, high: %.1f}\n"%(binning[jbin],binning[jbin+1]))
            
            yamlDataFile.write('dependent_variables:\n')
            if level == 'parton':
                yamlDataFile.write("- header: {name: 'Var("+(setups[iobs][1][kind]['var'])+")'")
            elif level == 'particle':
                yamlDataFile.write("- header: {name: 'Var("+(setups[iobs][1][kind]['var'])+")'")
            if setups[iobs][1][kind].has_key('units'):
                yamlDataFile.write(', units: ('+setups[iobs][1][kind]['units']+')**2')
            yamlDataFile.write('}\n')
            
            yamlDataFile.write('  qualifiers:\n')
            yamlDataFile.write('  - {name: RE, value: \'$\\rm{pp}\\ \\to\\ \\rm{tq} + \\bar{\\rm{t}}q$, $\\rm{t} \\to \\ell\\nu \\rm{b} (+ \\nu_{\\tau}\\bar{\\nu}_{\\tau})$, $(\\ell = \\mu,\\rm{e})$\'}\n')
            yamlDataFile.write('  - {name: SQRT(S), units: GEV, value: 13000}\n')

            
            yamlDataFile.write('  values:\n')
            for ibin in range(nbins):
                for jbin in range(nbins):
                    centralVal = covHist.GetBinContent(ibin+1,jbin+1)
                    val,exp = formatExp(centralVal)
                    if exp==0:
                        yamlDataFile.write('  - value: %.1f\n'%(val))
                    else:
                        yamlDataFile.write('  - value: %.2e\n'%(centralVal))
                        
            yamlDataFile.close()


yamlSubmissionFile.write('---\n')
yamlSubmissionFile.write('name: Table %i\n'%itable)
itable+=1
yamlSubmissionFile.write("description: 'Top quark spin asymmetry at the parton level in the muon and electron channel and their combination'\n")
yamlSubmissionFile.write("location: 'Data from Table 2 (page 24 of preprint)'\n")
yamlSubmissionFile.write("keywords:\n")
yamlSubmissionFile.write("  - {name: reactions, values: [P P --> TOP Q]}\n")
yamlSubmissionFile.write("  - {name: observables, values: [ASYM,POL]}\n")
yamlSubmissionFile.write("  - {name: cmenergies, values: [13000.0]}\n")
yamlSubmissionFile.write("  - {name: phrases, values: [Differential Cross Section, Proton-Proton Scattering, Single Top Production,Asymmetry Measurement,Polarization]}\n")
yamlSubmissionFile.write("data_file: spinasym.yaml\n\n")

yamlDataFile = open("spinasym.yaml","w")
yamlDataFile.write("independent_variables: []\n")


asymVal = [0.403,0.446,0.440]
asymUnc = [
    ['Statistical',[0.029,0.038,0.024]],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ normalisation',[0.010,0.007,0.007]],
    ['W/Z/$\\gamma^{\\star}$+jets normalisation',[0.012,0.011,0.012]],
    ['Multijet normalisation',[0.0001,0.0002,0.003]],
    ['Multijet shape',[0.0001,0.003,0.0003]],
    ['Jet energy scale and resolution',[0.008,0.0004,0.0002]],
    ['b tagging efficiencies and misidentification',[0.0003,0.009,0.004]],
    ['Others (lepton efficiencies, pileup, unclustered energy)',[0.0003,0.003,0.005]],
    ['Top quark mass',[0.033,0.063,0.044]],
    ['PDF+$\\alpha_{S}$',[0.011,0.009,0.011]],
    ['$t$ channel renormalisation and factorisation scales',[0.013,0.018,0.020]],
    ['$t$ channel parton shower',[0.030,0.008,0.014]],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ renormalisation and factorisation scales',[0.008,0.019,0.017]],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ parton shower',[0.031,0.037,0.033]],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ underlying event tune',[0.0004,0.014,0.014]],
    ['$\\textrm{t}\\bar{\\textrm{t}}$ $p_{\\textrm{T}}$ reweighting',[0.0002,0.010,0.009]],
    ['W+jets renormalisation and factorisation scales',[0.0003,0.019,0.014]],
    ['Color reconnection', [0.036,0.056,0.031]],
    ['Fragmentation model',[0.011,0.011,0.011]],
    ['Profiled uncertainties only',[0.041,0.047,0.031]],
    ['Total',[0.071,0.099,0.070]],
]
 

yamlDataFile.write('dependent_variables:\n')
for ivar,var in enumerate([
    ['$A_{\\mu}$'],
    ['$A_{\\textrm{e}}$'],
    ['$A_{\\mu+\\textrm{e}}$']
]):
    yamlDataFile.write("- header: {name: '"+var[0]+"'}\n")
    yamlDataFile.write('  qualifiers:\n')
    yamlDataFile.write('  - {name: RE, value: \'$\\rm{pp}\\ \\to\\ \\rm{tq} + \\bar{\\rm{t}}q$, $\\rm{t} \\to \\ell\\nu \\rm{b} (+ \\nu_{\\tau}\\bar{\\nu}_{\\tau})$, $(\\ell = \\mu,\\rm{e})$\'}\n')
    yamlDataFile.write('  - {name: SQRT(S), units: GEV, value: 13000}\n')
    yamlDataFile.write('  values:\n')
    yamlDataFile.write('  - value: %.3f\n'%(asymVal[ivar]))
    yamlDataFile.write("    errors:\n")
    for asymSys in asymUnc:
        if asymSys[1][ivar]<0.001:
            yamlDataFile.write("    - {symerror: %.4f, label: '%s'}\n"%(asymSys[1][ivar],asymSys[0]))
        else:
            yamlDataFile.write("    - {symerror: %.3f, label: '%s'}\n"%(asymSys[1][ivar],asymSys[0]))
yamlDataFile.close()



            
yamlSubmissionFile.close()


