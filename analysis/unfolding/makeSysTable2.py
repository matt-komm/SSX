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
    ['\\wzjets<br>normalisation',['WZjets*Excl','dyExcl','twExcl']],
    ['Multijet<br>normalisation',['QCD*Excl']],
    ['Multijet shape',['eleMultiIsoExcl','eleMultiVetoExcl','muMultiExcl']],
    ['Jet energy scale<br>and resolution',['enExcl','resExcl']],
    ['\\PQb-tagging/mistagging<br>efficiencies',['btagExcl','ltagExcl']],
    #['Lepton efficiencies',['eleEffExcl','muEffExcl']],
    ['Others',['puExcl','uncExcl','eleEffExcl','muEffExcl']],
]

systematics = [
    ['Top quark mass',['topMass']],
    ['PDF+$\\alpS$',['pdf']],
    ['$t$ channel renorm.<br>and fact. scales',['tchanScaleME']],
    ['$t$ channel parton<br>shower',['tchanHdampPS','tchanScalePS']],
    ['\\ttbar renorm. and<br>fact. scales',['ttbarScaleME']],
    ['\\ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['\\ttbar underlying<br>event tune',['ttbarUE']],
    ['\\ttbar \\pt reweighting',['ttbarPt']],
    ['\\wjets renorm.<br>and fact. scales',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    #['Luminosity',['lumi']]
    #['Others (\\wjets ME scale, \\ttbar \\pt rew., \\ttbar ME scale)',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    #['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
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


#print "\\hline"

varName="top quark \\pt"
levelName = "parton"

headers= [
    "The measured differential absolute cross section in intervals of the "+varName+" at the "+levelName+" level. A breakdown of the systematic uncertainties is given as well. Minor uncertainties (lepton efficiencies, pileup, and unclustered energy) have been grouped into the ``Others'' category.",
    "The measured differential normalised coss section in intervals of "+varName+" at the "+levelName+" level. A breakdown of the systematic uncertainties is given as well. Minor uncertainties (lepton efficiencies, pileup, and unclustered energy) have been grouped into the ``Others'' category.",
    "The measured differential charge ratio in intervals of the "+varName+" at the "+levelName+" level. A breakdown of the systematic uncertainties is given as well. Minor uncertainties (lepton efficiencies, pileup, and unclustered energy) have been grouped into the ``Others'' category.",
]

for iobs,obs in enumerate([
    ['sum','\\multicolumn{2}{@{}l}{$\\dfrac{\\rd\\sigma_{\\PQt\\text{+}\\PAQt}}{'+ptSym+'}$'+(' (pb/\\GeV)}' if unit!="" else ' (pb)}')],
    ['norm','\\multicolumn{2}{@{}l}{$\\dfrac{1}{\\sigma_{\\PQt\\text{+}\\PAQt}}\\dfrac{\\rd\\sigma_{\\PQt\\text{+}\\PAQt}}{'+ptSym+'}$'+(' (1/\\GeV)}' if unit!="" else "}")],
    ['ratio','\\multicolumn{2}{@{}l}{$\\left.\\dfrac{\\rd\\sigma_{\\PQt}}{'+ptSym+'}\\middle /\\dfrac{\\rd\\sigma_{\\PQt\\text{+}\\PAQt}}{'+ptSym+'}\\right.$}'],
]):
    print
    print
    print "\\begin{table*}[h!]"
    print "\\centering"
    print "\\topcaption{"+headers[iobs]+"}"
    print "\\begin{tabular}{@{}l r",
    print " r@{.}l"*nbins,
    print "@{}}"

    print "\\hline"
    if unit!="":
        print "\\multicolumn{2}{@{}l}{"+varName.capitalize()+" interval (\\GeV)}"
    else:
        print "\\multicolumn{2}{@{}l}{Interval}"
    for ibin in range(nbins):
        
        print "& \\multicolumn{2}{l@{}}{[%.1f; %.1f]}"%(binning[ibin],binning[ibin+1])
    print "\\\\"

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
            nbr = len(reduce(lambda x,y: x+"<br>"+y,map(lambda x: x[0],systematicsProfiled)).split("<br>"))
            print "\\multirow{"+str(nbr)+"}{*}{\\rotatebox[origin=c]{90}{Profiled uncertainties}}"
        
        print "& %30s"%(systematic[0].split("<br>")[0]),
        nbr = len(systematic[0].split("<br>"))
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
        for ibr in range(1,nbr):
            print "\\\\"
            print "& %s"%(systematic[0].split("<br>")[ibr])
                
        if isyst==(len(systematicsProfiled)-1):
            print "\\\\"
        else:
            if nbr>1:
                print "\\\\"#[\\cmsTabSkip]"
            else:
                print "\\\\"
       
    print "\\\\[\\cmsTabSkip]"
    
    for isyst,systematic in enumerate(systematics):
        if isyst==0:
            nbr = len(reduce(lambda x,y: x+"<br>"+y,map(lambda x: x[0],systematics)).split("<br>"))
            print "\\multirow{"+str(nbr)+"}{*}{\\rotatebox[origin=c]{90}{Theoretical uncertainties}}"

        print "& %30s"%(systematic[0].split("<br>")[0]),
        nbr = len(systematic[0].split("<br>"))
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
        for ibr in range(1,nbr):
            print "\\\\"
            print "& %s"%(systematic[0].split("<br>")[ibr])
                
        if isyst==(len(systematics)-1):
            print "\\\\"
        else:
            if nbr>1:
                print "\\\\"#[\\cmsTabSkip]"
            else:
                print "\\\\"
    
    print "\\\\[\\cmsTabSkip]"
            
            
    if iobs==0:
        print "\\multicolumn{2}{@{}l}{Luminosity}",
        for ibin in range(nbins):
            print " "*4,

            centralValue = data[obs[0]]['central'][ibin]
            
            sysValue = data[obs[0]]['lumi'][ibin]**2
                
            sysValue = math.sqrt(sysValue)
            
            if sysValue/centralValue<0.001:
                print "& %14s"%("${<}$0&1\\%"),
            else:
                print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*sysValue/centralValue)).replace(".","&")),
                
        print "\\\\[\\cmsTabSkip]"

    

    print "\\multicolumn{2}{@{}l}{Statistical and experimental}",
    for ibin in range(nbins):
        print " "*4,
        print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*data[obs[0]]['prof'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&")),
    print "\\\\"
    
    print "\\multicolumn{2}{@{}l}{uncertainties (profiled)}",
    print "\\\\[\\cmsTabSkip]"
    
    print "\\multicolumn{2}{@{}l}{Total uncertainties}",
    for ibin in range(nbins):
        print " "*4,
        print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*data[obs[0]]['total'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&")),
    print "\\\\"

    print "\\hline"
    print "\\end{tabular}"
    print "\\end{table*}"
     
