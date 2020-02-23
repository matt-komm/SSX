import json
import math
import numpy



systematics = [
    ['Experimental',['prof']],
    ['Top quark mass',['topMass']],
    ['PDF+$\\alpS$',['pdf']],
    ['$t$ channel ME scale',['tchanScaleME']],
    ['$t$ channel parton shower',['tchanHdampPS','tchanScalePS']],
    ['\\ttbar ME scale',['ttbarScaleME']],
    ['\\ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['\\ttbar underlying event tune',['ttbarUE']],
    ['\\ttbar \pt rew.',['ttbarPt']],
    ['\\wjets ME scale',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    #['Others (\\wjets ME scale, \\ttbar \\pt rew., \\ttbar ME scale)',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    #['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    #['Luminosity',['lumi']],
    ['Total',['total']]
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

print "%30s"%"Central values",
for data in [dataMu,dataEle,dataComb]:
    print "& %15s"%(("%5.3f"%(data['central'])).replace(".","&")),

print "\\\\"

for systematic in systematics:


    print "%30s"%systematic[0],
    
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
        

