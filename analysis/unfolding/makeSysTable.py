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
    ['Experimental',['prof']],
    ['Top quark mass',['topMass']],
    #['PDF+$\\alpS$',['pdf']],
    ['PDF+$\\alpS$ tch',['pdftch']],
    ['PDF+$\\alpS$ bkg',['pdfBkg']],
    ['$t$ channel ME scale',['tchanScaleME']],
    ['$t$ channel parton shower',['tchanHdampPS','tchanScalePS']],
    #['\\ttbar ME scale',['ttbarScaleME']],
    ['\\ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['\\ttbar underlying event tune',['ttbarUE']],
    #['\\ttbar \pt rew.',['ttbarPt']],
    #['\\wjets ME scale',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    #['Others (\\wjets ME scale, \\ttbar \\pt rew., \\ttbar ME scale)',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    ['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    ['Luminosity',['lumi']],
]

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
print "\\hline"

for iobs,obs in enumerate([
    ['sum','Abs (pb/\\GeV)' if unit!="" else 'Abs (pb)'],
    ['norm','Norm (1/\\GeV)' if unit!="" else 'Norm'],
    ['ratio','Ratio']
]):
    if iobs==0:
        print "\\multicolumn{2}{@{}l}{Central values} \\\\"
    print "\\multicolumn{2}{r}{"+obs[1]+"}",
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

for systematic in systematics:
    for iobs,obs in enumerate([
        ['sum','Abs'],
        ['norm','Norm'],
        ['ratio','Ratio']
    ]):
        if systematic[0]=='Luminosity' and iobs>0:
            continue
        if iobs==0:
            if systematic[0]=='Luminosity':
                print systematic[0]
            else:
                print "\\multirow[t]{3}{0.16\\textwidth}{"+systematic[0]+"}"
        print "& "+obs[1],
        for ibin in range(nbins):
            print " "*4,

            centralValue = data[obs[0]]['central'][ibin]
            
            sysValue = 0.
            
            for subsystematic in systematic[1]:
                sysValue += data[obs[0]][subsystematic][ibin]**2
                
            sysValue = math.sqrt(sysValue)
            
            if sysValue/centralValue<0.001:
                print ("& ${<}$0&1"),
            else:
                print ("& ${\\pm}$%.1f"%(100.*sysValue/centralValue)).replace(".","&"),
                
            #print "& %.1f"%(100.*sysValueParticle/centralValuePaticle),
            
            print "\\%",
            
        if systematic[0]=='Luminosity' or iobs==2:
            print "\\\\[\\cmsTabSkip]"
        else:
            print "\\\\"

for iobs,obs in enumerate([
    ['sum','Abs'],
    ['norm','Norm'],
    ['ratio','Ratio']
]):
    if iobs==0:
        print "\\multirow[t]{3}{0.16\\textwidth}{Total}"
    print "& "+obs[1],
    for ibin in range(nbins):
        print " "*4,
        print ("& $\\pm$%.1f"%(100.*data[obs[0]]['total'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&"),
        print "\\%",
    print "\\\\"

print "\\hline"
     
