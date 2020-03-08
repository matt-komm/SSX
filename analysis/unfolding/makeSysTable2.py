import json
import math
import numpy
        
systematicsProfiled = [
    ['Statistical',['stat']],
    ['\\ttbar normalisation',['TopBkg*Excl']],
    ['\\wzjets<br>normalisation',['WZjets*Excl','dyExcl','twExcl']],
    ['Multijet<br>normalisation',['QCD*Excl']],
    ['Multijet shape',['eleMultiIsoExcl','eleMultiVetoExcl','muMultiExcl']],
    ['Jet energy scale<br>and resolution',['enExcl','resExcl']],
    ['\\PQb tagging efficiencies<br> and misidentification',['btagExcl','ltagExcl']],
    #['Lepton efficiencies',['eleEffExcl','muEffExcl']],
    ['Others',['puExcl','uncExcl','eleEffExcl','muEffExcl']],
]

systematics = [
    ['Top quark mass',['topMass']],
    ['PDF+$\\alpS$',['pdf']],
    ['$t$ channel renormalisation<br>and factorisation scales',['tchanScaleME']],
    ['$t$ channel parton<br>shower',['tchanHdampPS','tchanScalePS']],
    ['\\ttbar renormalisation<br>and factorisation scales',['ttbarScaleME']],
    ['\\ttbar parton shower',['ttbarScaleISRPS','ttbarScaleFSRPS','ttbarHdampPS']],
    ['\\ttbar underlying<br>event tune',['ttbarUE']],
    ['\\ttbar \\pt reweighting',['ttbarPt']],
    ['\\wjets renormalisation<br>and factorisation scales',['wjetsScaleME']],
    ['Color reconnection', ['tchanColor','ttbarColor']],
    ['Fragmentation model',['bfrac']],
    #['Luminosity',['lumi']]
    #['Others (\\wjets ME scale, \\ttbar \\pt rew., \\ttbar ME scale)',['wjetsScaleME','ttbarPt','ttbarScaleME']],
    #['Others',['wjetsScaleME','ttbarPt','ttbarScaleME']],
]






def formatExp(value):
    n = int(math.floor(math.log10(value)))
    if n<2 and n>=1:
        return value,0
    else:
        return value/10**n,n




levelName = "particle"

for var in [
    ["result/final/comb/pt_"+levelName+"_comb_sysSummary.json","\\rd p_\\textrm{T}","top quark \\pt"],
    ["result/final/comb/y_"+levelName+"_comb_sysSummary.json","\\rd \\abs{y}","top quark rapidity"],
    ["result/final/comb/lpt_"+levelName+"_comb_sysSummary.json","\\rd p_\\textrm{T}","charged lepton \\pt"],
    ["result/final/comb/leta_"+levelName+"_comb_sysSummary.json","\\rd \\abs{y}","charged lepton rapidity"],
    ["result/final/comb/wpt_"+levelName+"_comb_sysSummary.json","\\rd p_\\textrm{T}","W boson \\pt"],
    ["result/final/comb/cos_"+levelName+"_comb_sysSummary.json","\\rd \\cospol","polarisation angle"],
]:
    symbol = var[1]#"\\rd p_\\textrm{T}"
    varName= var[2]#"top quark \\pt"
    
    
    headers= {
        'sum':"The measured differential absolute cross section in intervals of the "+varName+" at the "+levelName+" level. A breakdown of the systematic uncertainties is given as well. Minor uncertainties (lepton efficiencies, pileup, and unclustered energy) have been grouped into the ``Others'' category.",
        'norm':"The measured differential normalised coss section in intervals of "+varName+" at the "+levelName+" level. A breakdown of the systematic uncertainties is given as well. Minor uncertainties (lepton efficiencies, pileup, and unclustered energy) have been grouped into the ``Others'' category.",
        'ratio':"The measured differential charge ratio in intervals of the "+varName+" at the "+levelName+" level. A breakdown of the systematic uncertainties is given as well. Minor uncertainties (lepton efficiencies, pileup, and unclustered energy) have been grouped into the ``Others'' category.",
    }

    
    fParton = open(var[0])
    data = json.load(fParton)

    binning = data['binning']
    nbins = len(binning)-1
    unit = data['unit']

    for iobs,obs in enumerate([
        ['sum','\\multicolumn{2}{@{}l}{$\\dfrac{\\rd\\sigma_{\\PQt\\text{+}\\PAQt}}{'+symbol+'}$'+(' (pb/\\GeV)}' if unit!="" else ' (pb)}')],
        #['norm','\\multicolumn{2}{@{}l}{$\\dfrac{1}{\\sigma_{\\PQt\\text{+}\\PAQt}}\\dfrac{\\rd\\sigma_{\\PQt\\text{+}\\PAQt}}{'+symbol+'}$'+(' (1/\\GeV)}' if unit!="" else "}")],
        #['ratio','\\multicolumn{2}{@{}l}{$\\left.\\dfrac{\\rd\\sigma_{\\PQt}}{'+symbol+'}\\middle /\\dfrac{\\rd\\sigma_{\\PQt\\text{+}\\PAQt}}{'+symbol+'}\\right.$}'],
    ]):
        print
        print
        print "\\begin{table*}[h!]"
        print "\\centering"
        print "\\topcaption{"+headers[obs[0]]+"}"
        print "\\begin{tabular}{@{}l r",
        print " r@{.}l"*nbins,
        print "@{}}"

        print "\\hline"
        if unit!="":
            print "\\multicolumn{2}{@{}l}{"+varName.capitalize()+" interval (\\GeV)}"
        else:
            print "\\multicolumn{2}{@{}l}{"+varName.capitalize()+" interval}"
        for ibin in range(nbins):
            if unit=="":
                print "& \\multicolumn{2}{c@{}}{[%.1f; %.1f]}"%(binning[ibin],binning[ibin+1])
            else:
                print "& \\multicolumn{2}{c@{}}{[%.0f; %.0f]}"%(binning[ibin],binning[ibin+1])
        print "\\\\"

        print obs[1],
        
        maxExp = max(map(lambda x:math.log10(x),data[obs[0]]['central']))
        minExp = min(map(lambda x:math.log10(x),data[obs[0]]['central']))
        
            
        
        for ibin in range(nbins):
            print " "*4,
            value = data[obs[0]]['central'][ibin]
            val,exp = formatExp(value)
            if minExp>=math.log10(0.106):
                if value<1.02:
                    print ("& \\multicolumn{2}{c@{}}{%.2f}"%(value)),
                else:
                    print ("& \\multicolumn{2}{c@{}}{%.1f}"%(value)),
            else:
                print ("& \\multicolumn{2}{c@{}}{%.1f$\\times 10^{%i}$}"%(val,exp)),

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
                    print "\\\\[\\cmsTabSkip]"
                else:
                    print "\\\\[\\cmsTabSkip]"
           
        print "\\hline"
        
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
                    print "\\\\[\\cmsTabSkip]"
                else:
                    print "\\\\[\\cmsTabSkip]"
        
        print "\\hline"
                
                
        if obs[0]=="sum":
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

        

        print "\\multicolumn{2}{@{}l}{Profiled uncertainties only}",
        for ibin in range(nbins):
            print " "*4,
            print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*data[obs[0]]['prof'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&")),
        print "\\\\"
        
        print "\\multicolumn{2}{@{}l}{(statistical+experimental)}",
        print "\\\\[\\cmsTabSkip]"
        
        print "\\multicolumn{2}{@{}l}{Total uncertainties}",
        for ibin in range(nbins):
            print " "*4,
            print "& %14s"%(("${\\pm}$%.1f\\%%"%(100.*data[obs[0]]['total'][ibin]/data[obs[0]]['central'][ibin])).replace(".","&")),
        print "\\\\"

        print "\\hline"
        print "\\end{tabular}"
        print "\\end{table*}"
         
