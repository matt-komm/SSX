import json
import math
import numpy

sysDictNames = {
            "stat":"Statistical",
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
        
systematicsProfiled = [
    ['Statistical',['stat']],
    ['\\ttbar normalisation',['TopBkg*Excl']],
    ['\\wzjets normalisation',['WZjets*Excl','dyExcl','twExcl']],
    ['Multijet normalisation',['QCD*Excl']],
    ['Multijet shape',['eleMultiIsoExcl','eleMultiVetoExcl','muMultiExcl']],
    ['Jet energy scale/resolution',['enExcl','resExcl']],
    ['b-tagging/mistagging eff.',['btagExcl','ltagExcl']],
    #['Mistagging efficiencies',[]],
    ['Lepton efficiencies',['eleEffExcl','muEffExcl']],
    ['Others',['puExcl','uncExcl',]],
]

systematics = [
    ['Top quark mass',['topMass']],
    ['PDF+$\\alpS$',['pdf']],
    ['$t$ channel renorm./fact. scale',['tchanScaleME']],
    ['$t$ channel parton shower',['tchanHdampPS','tchanScalePS']],
    ['\\ttbar renorm./fact. scale',['ttbarScaleME']],
    ['\\ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['\\ttbar underlying event tune',['ttbarUE']],
    ['\\ttbar \\pt reweighting',['ttbarPt']],
    ['\\wjets renorm./fact. scale',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    #['Others (\\wjets ME scale, \\ttbar \\pt rew., \\ttbar ME scale)',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    #['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    ['Luminosity',['lumi']],
]

ptSym = "\\rd p_\\textrm{T}"

# u'', u'central', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'', u'gen'

fParton = open("result/final/comb/pt_parton_comb_sysSummary.json")
data = json.load(fParton)

binning = data['binning']
nbins = len(binning)-1
unit = data['unit']

def formatExp(value):
    n = int(math.floor(math.log10(value)))
    if n<2 and n>=1:
        return value,0
    else:
        return value/10**n,n

print "\\hline"
if unit!="":
    print "\\multicolumn{2}{@{}l}{Interval (\\GeV)}"
else:
    print "\\multicolumn{2}{@{}l}{Interval}"
for ibin in range(nbins):
    
    print "& \\multicolumn{2}{l@{}}{[%.1f; %.1f]}"%(binning[ibin],binning[ibin+1])
print "\\\\"
#print "\\hline"

for iobs,obs in enumerate([
    ['sum','\\multicolumn{2}{@{}l}{$\\rd\\sigma_{\\PQt\\text{+}\\PAQt}/'+ptSym+'$ (pb/\\GeV)}' if unit!="" else 'Abs (pb)'],
    #['norm','Norm (1/\\GeV)' if unit!="" else 'Norm'],
    #['ratio','Ratio']
]):
    print obs[1],
    for ibin in range(nbins):
        print " "*4,
        
        val,exp = formatExp(data[obs[0]]['central'][ibin])
        if exp==0:
            print ("& \\multicolumn{2}{c@{}}{%.1f}"%(val)),
        else:
            print ("& \\multicolumn{2}{c@{}}{%.1f$\\times 10^{%i}$}"%(val,exp)),
        #print "& %.1f"%(100.*dataParticle['sum']['total'][ibin]/dataParticle['sum']['central'][ibin]),
    print "\\\\"
    
    print "\\hline"
    
    for isyst,systematic in enumerate(systematicsProfiled):
        if isyst==0:
            print "\\multirow{"+str(len(systematicsProfiled))+"}{*}{\\rotatebox[origin=c]{90}{Profiled uncertainties}}"
        print "& %30s"%(systematic[0]),
        
        for ibin in range(nbins):
            print " "*4,

            centralValue = data[obs[0]]['central'][ibin]
            
            sysValue = 0.
            
            for subsystematic in systematic[1]:
                sysValue += data[obs[0]][subsystematic][ibin]**2
                
            sysValue = math.sqrt(sysValue)
            
            if sysValue/centralValue<0.001:
                print "& %14s"%("${<}$0&1\\%"),
            else:
                print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*sysValue/centralValue)).replace(".","&")),
                
        if isyst==(len(systematicsProfiled)-1):
            print "\\\\[\\cmsTabSkip]"
        else:
            print "\\\\"
        

    for isyst,systematic in enumerate(systematics):
        if isyst==0:
            print "\\multirow{"+str(len(systematics))+"}{*}{\\rotatebox[origin=c]{90}{Externalised uncertainties}}"
        if systematic[0]=='Luminosity' and iobs>0:
            continue
        if iobs==0:
            if systematic[0]=='Luminosity':
                print "& %30s"%(systematic[0]),
            else:
                print "& %30s"%(systematic[0]),
        for ibin in range(nbins):
            print " "*4,

            centralValue = data[obs[0]]['central'][ibin]
            
            sysValue = 0.
            
            for subsystematic in systematic[1]:
                sysValue += data[obs[0]][subsystematic][ibin]**2
                
            sysValue = math.sqrt(sysValue)
            
            if sysValue/centralValue<0.001:
                print "& %14s"%("${<}$0&1\\%"),
            else:
                print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*sysValue/centralValue)).replace(".","&")),
                
        if isyst==(len(systematics)-1):
            print "\\\\[\\cmsTabSkip]"
        else:
            print "\\\\"
        

    print "\\multicolumn{2}{@{}l}{Profiled experimental uncertainties}",
    for ibin in range(nbins):
        print " "*4,
        print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*data[obs[0]]['prof'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&")),
    print "\\\\"

    print "\\multicolumn{2}{@{}l}{Total uncertainties}",
    for ibin in range(nbins):
        print " "*4,
        print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*data[obs[0]]['total'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&")),
    print "\\\\"

    print "\\hline"
     
