import json
import math
import numpy

sysDictNames = {
            "pdf":"PDF",
            "tchanHdampPS":"$t$-ch. $h_\\mathrm{damp}$",
            "tchanScaleME":"$t$-ch. ME scale",
            "tchanScalePS":"$t$-ch. PS scale",
            "topMass":"Top mass",
            "ttbarHdampPS":"\\ttbar $h_\\mathrm{damp}$",
            "ttbarPt":"\\ttbar \\pt rew.",
            "ttbarScaleFSRPS":"\\ttbar FSR PS scale",
            "ttbarScaleISRPS":"\\ttbar ISR PS scale",
            "ttbarScaleME":"\\ttbar ME scale",
            "ttbarUE":"\\ttbar UE tune",
            "wjetsScaleME":"\\wjets ME scale",
            "tchanColor":"$t$-ch. color reconnection",
            "ttbarColor":"\\ttbar color reconnection",
            "bfrac":"b fragmentation",
            "lumi":"Luminosity"
        }

systematics = [
    ['Statistical and experimental uncertainties',['prof']],
    ['Top quark mass',['topMass']],
    ['PDF+alphaS',['pdf']],
    ['t channel renormalisation/factorisation scales',['tchanScaleME']],
    ['t channel parton shower',['tchanHdampPS','tchanScalePS']],
    ['ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['ttbar underlying event tune',['ttbarUE']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    ['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    ['Luminosity',['lumi']],
    ['Total',['total']],
]



def formatExp(value):
    n = int(math.floor(math.log10(value)))
    if n<2 and n>=1:
        return value,0
    else:
        return value/10**n,n
        
        
setups = [
    ["pt", {
        'name':"%s level top quark PT",
        'locations':{
            'sum':{'parton':'Figure 7, upper row, left column (page 18 of preprint)','particle':'Figure 8, upper row, left column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, upper row, left column (page 20 of preprint)','particle':'Figure 10, upper row, left column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, upper row, left column (page 22 of preprint)','particle':'Figure 12, upper row, left column (page 23 of preprint)'},
        },
        
        'unit': "GEV",
        "sum":{"name": "D(SIG(%s))/DPT", "unit": "pb GEV**-1"},
        "norm":{"name": "1/SIG * D(SIG(%s))/DPT", "unit": "GEV**-1"},
        "ratio":{"name": "RATIO(%s)/DPT"},
    }],
    ["y", {
        'name':"%s level top quark ETARAP",
        'locations':{
            'sum':{'parton':'Figure 7, upper row, right column (page 18 of preprint)','particle':'Figure 8, upper row, right column (page 19 of preprint)'},
            'norm':{'parton':'Figure 9, upper row, right column (page 20 of preprint)','particle':'Figure 10, upper row, right column (page 21 of preprint)'},
            'ratio':{'parton':'Figure 11, upper row, right column (page 22 of preprint)','particle':'Figure 12, upper row, right column (page 23 of preprint)'},
        },
        "sum":{"name": "D(SIG(%s))/ABS(DETARAP)", "unit": "pb"},
        "norm":{"name": "1/SIG * D(SIG(%s))/ABS(DETARAP)"},
        "ratio":{"name": "RATIO(%s)/ABS(DETARAP)"},
    }],
]

yamlSubmissionFile = open("submission.yaml","w")

yamlSubmissionFile.write('additional_resources:\n')
yamlSubmissionFile.write('- {description: web page with auxiliary material, location: \'http://cms-results.web.cern.ch/cms-results/public-results/publications/TOP-17-023/index.html\'}\n')
yamlSubmissionFile.write('- {description: archive location of paper, location: \'https://arxiv.org/abs/1907.08330\'}\n')

yamlSubmissionFile.write('comment: \'A measurement is presented of differential cross sections for $t$-channel single top quark and antiquark production in proton-proton collisions at a centre-of-mass energy of $13~\\rm{TeV}$ by the CMS experiment at the LHC. From a data set corresponding to an integrated luminosity of $35.9~\\rm{fb}^{-1}$, events containing one muon or electron and two or three jets are analysed. The cross section is measured as a function of the top quark transverse momentum ($p_{\\rm{T}}$), rapidity, and polarisation angle, the charged lepton $p_{\\rm{T}}$ and rapidity, and the $p_{\\rm{T}}$ of the W boson from the top quark decay. In addition, the charge ratio is measured differentially as a function of the top quark, charged lepton, and W boson kinematic observables. The results are found to be in agreement with standard model predictions using various next-to-leading-order event generators and sets of parton distribution functions. Additionally, the spin asymmetry, sensitive to the top quark polarisation, is determined from the differential distribution of the polarisation angle at parton level to be $0.440 \pm 0.070$, in agreement with the standard model prediction.\'\n')


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
            yamlSubmissionFile.write('name: ')
            if kind=='sum':
                yamlSubmissionFile.write('Absolute cross section, ')
            elif kind=='norm':
                yamlSubmissionFile.write('Normalised cross section, ')
            elif kind=='ratio':
                yamlSubmissionFile.write('Ratio, ')
                
            yamlSubmissionFile.write((setups[iobs][1]['name']%(level))+'\n')
            yamlSubmissionFile.write('location: '+setups[iobs][1]['locations'][kind][level]+'\n')
            yamlSubmissionFile.write('description: The measured cross sections.\n')
            yamlSubmissionFile.write('keywords:\n')
            yamlSubmissionFile.write('  - {name: reactions, values: [P P --> TOP Q]}\n')
            #yamlSubmissionFile.write('  - {name: observables, values: ['+(setups[iobs][1]['name']%(level.capitalize()))+']}\n')
            yamlSubmissionFile.write('  - {name: observables, values: ['+(setups[iobs][1]['name']%(level.capitalize()))+']}\n')
            yamlSubmissionFile.write('  - {name: cmenergies, values: [13000.0]}\n')
            yamlSubmissionFile.write('  - {name: phrases, values: [Differential Cross Section, Proton-Proton Scattering, Single Top Production]}\n')
            yamlSubmissionFile.write("data_file: "+setups[iobs][0]+"_"+level+"_"+kind+".yaml\n\n")

            
            yamlDataFile = open(setups[iobs][0]+"_"+level+"_"+kind+".yaml","w")
            yamlDataFile.write("independent_variables:\n")
            
            yamlDataFile.write("- header: {name: "+(setups[iobs][1]['name']%(level.capitalize())))
            if setups[iobs][1].has_key('units'):
                yamlDataFile.write(", units: "+(setups[iobs][1]['unit']))
            yamlDataFile.write("}\n")
            yamlDataFile.write("  values:\n")
            for ibin in range(nbins):
                yamlDataFile.write("  - {low: %.1f, high: %.1f}\n"%(binning[ibin],binning[ibin+1]))
                
            yamlDataFile.write('dependent_variables:\n')
            if level == 'parton':
                yamlDataFile.write('- header: {name: '+(setups[iobs][1][kind]['name']%("inclusive")))
            elif level == 'particle':
                yamlDataFile.write('- header: {name: '+(setups[iobs][1][kind]['name']%("fiducial")))
            if setups[iobs][1][kind].has_key('unit'):
                yamlDataFile.write(', units: '+setups[iobs][1][kind]['unit'])
            yamlDataFile.write('}\n')
            
            yamlDataFile.write('  qualifiers:\n')
            yamlDataFile.write('  - {name: RE, value: \'$\\rm{pp}\\ \\to\\ \\rm{tq} + \\bar{\\rm{t}}q$, $\\rm{t} \\to \\ell\\nu \\rm{b} (+ \\nu_{\\tau}\\bar{\\nu}_{\\tau})$, $(\\ell = \\mu,\\rm{e})$\'}\n')
            yamlDataFile.write('  - {name: SQRT(S), units: GEV, value: 13000}\n')
            
            yamlDataFile.write('  values:\n')
            for ibin in range(nbins):
                val,exp = formatExp(data[kind]['central'][ibin])
                if exp==0:
                    yamlDataFile.write('  - value: %.1f\n'%(val))
                else:
                    yamlDataFile.write('  - value: %.2e\n'%(data[kind]['central'][ibin]))
                yamlDataFile.write("    errors:\n")
                
                for sysName,subSysList in systematics:
                    sysVal = 0.
                    for subSys in subSysList:
                        sysVal += data[kind][subSys][ibin]**2
                    sysVal = math.sqrt(sysVal)
                    
                    yamlDataFile.write("    - {symerror: %.2e, label: '%s'}\n"%(sysVal,sysName))
                        
            yamlDataFile.close()
            
yamlSubmissionFile.close()


