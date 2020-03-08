import json
import math
import numpy

systematicsProfiled = [
    ['Statistical',['stat']],
    ['\\ttbar normalisation',['TopBkg*Excl']],
    ['\\wzjets normalisation',['WZjets*Excl','dyExcl','twExcl']],
    ['Multijet normalisation',['QCD*Excl']],
    ['Multijet shape',['eleMultiIsoExcl','eleMultiVetoExcl','muMultiExcl']],
    ['Jet energy scale/resolution',['enExcl','resExcl']],
    ['\\PQb tagging efficiencies/misidentification',['btagExcl','ltagExcl']],
    ['Others',['puExcl','uncExcl','eleEffExcl','muEffExcl']],
]

systematics = [
    ['Top quark mass',['topMass']],
    ['PDF+$\\alpS$',['pdf']],
    ['$t$ channel renorm./fact. scales',['tchanScaleME']],
    ['$t$ channel parton shower',['tchanHdampPS','tchanScalePS']],
    ['\\ttbar renorm./fact. scales',['ttbarScaleME']],
    ['\\ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['\\ttbar underlying event tune',['ttbarUE']],
    ['\\ttbar \\pt reweighting',['ttbarPt']],
    ['\\wjets renorm./fact. scales',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
]

# u'', u'central', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'gen'

fEle = open("result/final/ele/cos_parton_ele_asymSysSummary.json")
dataEle = json.load(fEle)

fMu = open("result/final/mu/cos_parton_mu_asymSysSummary.json")
dataMu = json.load(fMu)

fComb = open("result/final/comb/cos_parton_comb_asymSysSummary.json")
dataComb = json.load(fComb)


def formatExp(value):
    n = int(math.floor(math.log10(value)))
    if n<2 and n>=1:
        return value,0
    else:
        return value/10**n,n

print "\\hline"

print "%40s"%"Central values",
for data in [dataMu,dataEle,dataComb]:
    print "& %15s"%(("%5.3f"%(data['central'])).replace(".","&")),

print "\\\\"

for systematic in systematicsProfiled:


    print "%40s"%systematic[0],
    
    for data in [dataMu,dataEle,dataComb]:
        sysValue = 0.
        
        for subsystematic in systematic[1]:
            sysValue += data[subsystematic]**2
            
        sysValue = math.sqrt(sysValue)
        
        if sysValue<0.001:
            print "& %15s"%("${<}$0&001"),
        else:
            print "& %15s"%(("${\\pm}$%.3f"%(sysValue)).replace(".","&")),
            
    print "\\\\"

for systematic in systematics:


    print "%40s"%systematic[0],
    
    for data in [dataMu,dataEle,dataComb]:
        sysValue = 0.
        
        for subsystematic in systematic[1]:
            sysValue += data[subsystematic]**2
            
        sysValue = math.sqrt(sysValue)
        
        if sysValue<0.001:
            print "& %15s"%("${<}$0&001"),
        else:
            print "& %15s"%(("${\\pm}$%.3f"%(sysValue)).replace(".","&")),
            
    print "\\\\"
    
        
print "%40s"%"Statistical and experimental uncertainties",
for data in [dataMu,dataEle,dataComb]:
    print "& %15s"%(("%5.3f"%(data['prof'])).replace(".","&")),

print "\\\\"

print "%40s"%"Total uncertainties",
for data in [dataMu,dataEle,dataComb]:
    print "& %15s"%(("%5.3f"%(data['total'])).replace(".","&")),

print "\\\\"

