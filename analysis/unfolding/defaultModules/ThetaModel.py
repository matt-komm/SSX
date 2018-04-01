from Module import Module

from ModelClasses import *
import random
import logging
import ROOT
import os
import csv
import sys
import copy

class ThetaModel(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        
    def makeLogNormal(self,mean,unc):
        sigma2 = math.log(1+unc**2/mean**2)
        mu = math.log(mean**2/math.sqrt(unc**2+mean**2))
        #mu = 0.0
        return {"type":"log_normal","config":{"mu": "%4.3f"%(mu), "sigma":"%4.3f"%(math.sqrt(sigma2))}}
        #return {"type":"log_normal","config":{"mu": "%4.3f"%(mu), "sigma":"%4.3f"%(math.sqrt(sigma2)), "range":"("+str(1.*r[0])+","+str(1.*r[1])+")"}}
       
    def makeGaus(self,mean,unc,r=[-3,3]):
        return {"type":"gauss","config":{"mean": "%4.3f"%(mean), "width":"%4.3f"%(unc), "range":"("+str(1.*r[0])+","+str(1.*r[1])+")"}}
        
    def getMeanAndUncertainty(self,dist):
        if dist["type"]=="gauss":
            return [float(dist["config"]["mean"]),float(dist["config"]["width"])]
        elif dist["type"]=="log_normal":
            mu = float(dist["config"]["mu"])
            sigma = float(dist["config"]["sigma"])
            return [math.exp(mu+0.5*sigma**2),math.exp(mu+0.5*sigma**2)*math.sqrt(math.exp(sigma**2)-1)]
        else:
            self._logger.critical("Unknown distribution type '"+dist["type"]+"'")
            sys.exit(1)
        
    def getUncertaintsDict(self):
        uncertaintiesBkg = {
            "TopBkg":self.module("ThetaModel").makeLogNormal(1.0,0.1),
            "WZjets":self.module("ThetaModel").makeLogNormal(1.0,0.3),
            #"WZjets_HF":self.module("ThetaModel").makeGaus(1.0,0.3,r=[0.0,2.0]),
            #"WZjets_LF":self.module("ThetaModel").makeLogNormal(1.0,0.1),
            "QCD_2j1t":self.module("ThetaModel").makeLogNormal(1.0,1.),
            #"QCD_3j1t":self.module("ThetaModel").makeGaus(0.2,0.5),
            "QCD_3j2t":self.module("ThetaModel").makeLogNormal(1.0,1.),
            
            #"lumi":self.module("ThetaModel").makeLogNormal(1.0,0.025),
        }
        uncertainties = {
            "tChannel_pos":self.module("ThetaModel").makeGaus(1.0,10.0,r=[0.1,4.0]),
            "tChannel_neg":self.module("ThetaModel").makeGaus(1.0,10.0,r=[0.1,4.0]),
        }
        
        for uncName in uncertaintiesBkg.keys():
            uncertainties[uncName]=copy.deepcopy(uncertaintiesBkg[uncName])
            # set 1% conservative charge confusion - might be far too high!!!
            uncertainties[uncName+"_ratio"]=self.module("ThetaModel").makeGaus(1.0,0.01)
        return uncertainties
        
    def getFitFileName(self,channels,unfoldingName,postfix):
        return self.module("Samples").getChannelName(channels)+"__"+unfoldingName+"__"+postfix
        
    def getHistogramPath(self,channel,unfoldingName,uncertainty=None):
        if not uncertainty:
            uncertainty = "nominal"
        return self.module("Utils").getOutputFolder(channel+"/"+uncertainty+"/"+unfoldingName)
        
    def getHistogramFile(self,channel,unfoldingName,unfoldingBin=-1,uncertainty="nominal",smooth=False):
        if smooth:
            return self.module("Utils").getHistogramFile("fitHists_smooth",channel,unfoldingName,unfoldingBin,uncertainty)
        else:
            return self.module("Utils").getHistogramFile("fitHists",channel,unfoldingName,unfoldingBin,uncertainty)

   
    def getHistogramName(self,observableName,fitComponentName,unfoldingName,unfoldingBin=-1,uncertainty=None):
        if unfoldingBin<0:
            if uncertainty:
                return observableName+"__"+fitComponentName+"__"+unfoldingName+"__"+uncertainty
            else:
                return observableName+"__"+fitComponentName+"__"+unfoldingName
        else:
            if uncertainty:
                return observableName+"__"+fitComponentName+"__"+unfoldingName+str(unfoldingBin)+"__"+uncertainty
            else:
                return observableName+"__"+fitComponentName+"__"+unfoldingName+str(unfoldingBin)
                                
    def getHistsFromFiles(self,channel,unfoldingName,unfoldingBin=-1,uncertainty=None,smooth=False):
        fileName = self.module("ThetaModel").getHistogramFile(channel,unfoldingName,unfoldingBin,uncertainty,smooth=smooth)
        rootFile = ROOT.TFile(fileName)
        if not rootFile:
            self._logger.critical("Histogram file '"+fileName+"' not found")
            sys.exit(1)
        histDict = {}
        for observableName in self.module("ThetaModel").getObservablesDict(channel).keys():
            histDict[observableName]={}
            #fit components
            for fitComponentName in self.module("ThetaModel").getFitComponentsDict().keys():
                histName = self.module("ThetaModel").getHistogramName(observableName,fitComponentName,unfoldingName,unfoldingBin,uncertainty)
                hist = rootFile.Get(histName)
                if not hist:
                    self._logger.critical("Histogram '"+histName+"' in file '"+fileName+"' not found")
                    sys.exit(1)
                #if hist.GetEntries()<=20 and (not (fitComponentName.find("QCD")>=0 and fitComponentName.find(observableName)<0)):
                #    self._logger.debug("Low number of events ("+str(hist.GetEntries())+") in histogram '"+histName+"' in file '"+fileName+"'")
                histClone = hist.Clone(hist.GetName()+"_clone")
                histClone.SetDirectory(0)
                histDict[observableName][fitComponentName]={"hist":histClone,"name":histName,"file":fileName}
            #data
            histName = self.module("ThetaModel").getHistogramName(observableName,"data",unfoldingName,unfoldingBin)
            hist = rootFile.Get(histName)
            if not hist:
                self._logger.critical("Histogram '"+histName+"' in file '"+fileName+"' not found")
                sys.exit(1)
            #if hist.GetEntries()<=20:
            #    self._logger.warning("Low number of events ("+str(hist.GetEntries())+") in histogram '"+histName+"' in file '"+fileName+"'")
            histClone = hist.Clone(hist.GetName()+"_clone")
            histClone.SetDirectory(0)
            histDict[observableName]["data"]={"hist":histClone,"name":histName,"file":fileName}
            
        return histDict
           
    
    def getBDTtchan(self,channel):
        if channel=="mu":
            return "(TMath::TanH(2.3*(BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost)+6.1*((BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost)>0.0)*TMath::Power(BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost-0.,3)-1.7*((BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost)<-0.1)*TMath::Power(fabs(BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost+0.1),1.4)))"
        elif channel=="ele":
            return "(TMath::TanH(2.3*(BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost)+6.1*((BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost)>0.0)*TMath::Power(BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost-0.,3)-1.8*((BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost)<-0.1)*TMath::Power(fabs(BDTcomb_tch_adaboost020_minnode0100_maxvar3_nCuts50_ntree1000_mix05000_qcdmix00500_invboost+0.1),1.4)))"
        else:
            self._logger.critical("Channel '"+channel+"' unknown!")
            sys.exit(1)
            
    def getBDTttw(self,channel):
        if channel=="mu":
            return "(TMath::TanH(5.*(BDTcomb_ttw_adaboost020_minnode0100_maxvar4_nCuts50_ntree1000_mix05000_invboost+0.16)))"
        elif channel=="ele":
            return "(TMath::TanH(5.2*(BDTcomb_ttw_adaboost020_minnode0100_maxvar4_nCuts50_ntree1000_mix05000_invboost+0.13)))"
        self._logger.critical("Unknown channel: "+str(channel))
        sys.exit(1)
        
    def getObservablesDict(self,channel):
        tch = self.module("ThetaModel").getBDTtchan(channel)
        ttw = self.module("ThetaModel").getBDTttw(channel)
        charge = self.module("Samples").getRecoCharge()
    
        observables = {
            "2j1t": {
                "weight":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "variable":charge+"*((SingleTop_1__mtw_beforePz<50.0)*SingleTop_1__mtw_beforePz+(SingleTop_1__mtw_beforePz>50.0)*((1.0*"+tch+"+0.0*"+ttw+"<0.)*(100.+50.*"+ttw+")+(1.0*"+tch+"+0.0*"+ttw+">0.)*(150.+50.*"+tch+")))",
                "bins":32,
                "range":[-200.,200.]
            },
            #"3j1t": {
            #    "weight":self.module("Samples").getNjets(3)+"*"+self.module("Samples").getNbjets(1),
            #    "variable":charge+"*SingleTop_1__mtw_beforePz",
            #    "bins":10,
            #    "range":[-200,200]
            #},
            "3j2t": {
                "weight":self.module("Samples").getNjets(3)+"*"+self.module("Samples").getNbjets(2),
                "variable":charge+"*SingleTop_1__mtw_beforePz",
                "bins":10,
                "range":[-200.,200.]
            },
        }
        
        return observables
    
    def getFitComponentsDict(self):
        componentsBkg = {
            
            "TopBkg":
            {
                "sets":["tWChannel","TTJets"],
                "uncertainties":["TopBkg"],
                "weight":"1",
                "color":ROOT.kOrange+1
            },
            
            "WZjets":
            {
                "sets":["WJetsAMCex","DYMG"],
                "uncertainties":["WZjets"],
                "weight":"1",
                "color":ROOT.kGreen+1
            },
            
            "QCD_2j1t":
            {
                "sets":["QCD_DD"],
                "uncertainties":["QCD_2j1t"],
                "weight":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "color":ROOT.kGray
            },

            #"QCD_3j1t":
            #{
            #    "sets":["QCD_DD"],
            #    "uncertainties":["QCD_3j1t"],
            #    "weight":self.module("Samples").getNjets(3)+"*"+self.module("Samples").getNbjets(1),
            #    "color":ROOT.kGray
            #},
 
            "QCD_3j2t":
            {
                "sets":["QCD_DD"],
                "uncertainties":["QCD_3j2t"],
                "weight":self.module("Samples").getNjets(3)+"*"+self.module("Samples").getNbjets(2),
                "color":ROOT.kGray
            }
        }
        
        
        # use gen charge as THE charge ratio for signal (no entanglement in unfolding)!
        components = {
            "tChannel_pos":
            {
                "sets":["tChannel"],
                "uncertainties":["tChannel_pos"],
                "weight":self.module("Samples").getGenChargeSelection(1),
                "color":ROOT.kMagenta+1
            },
            "tChannel_neg":
            {
                "sets":["tChannel"],
                "uncertainties":["tChannel_neg"],
                "weight":self.module("Samples").getGenChargeSelection(-1),
                "color":ROOT.kMagenta+1
            }
        }
        
        #use reco charge for backgrounds to add some uncertainty on the charge confusion!!!
        for compName in componentsBkg.keys():
            components[compName+"_pos"]=copy.deepcopy(componentsBkg[compName])
            components[compName+"_pos"]["weight"]+="*"+self.module("Samples").getRecoChargeSelection(1)
            components[compName+"_pos"]["uncertainties"].append(compName+"_ratio")
            components[compName+"_neg"]=copy.deepcopy(componentsBkg[compName])
            components[compName+"_neg"]["weight"]+="*"+self.module("Samples").getRecoChargeSelection(-1)

        return components

        
    def getModel(self,name):
        return Model(name, {"bb_uncertainties":"true"})
        
    
    def makeModel(self,cfgPath,fitSetup,parametersDict,modelName="fit",outputFile="fit",pseudo=False,seed=123):
        self._logger.info("Creating model: "+modelName)
        file = open(cfgPath,"w",20971520)
        
        model=self.module("ThetaModel").getModel(modelName)
        
        for parameterName in sorted(parametersDict.keys()):
            parametersDict[parameterName]["dist"]=Distribution(parameterName, parametersDict[parameterName]["type"], parametersDict[parameterName]["config"])
            file.write(parametersDict[parameterName]["dist"].toConfigString())

        dataDict = {}
        
        for iobs,observableName in enumerate(sorted(fitSetup.keys())):
            fitBins = fitSetup[observableName]["bins"]
            fitRange = fitSetup[observableName]["range"]
        
            observable = Observable(observableName, fitBins, fitRange)
            
            fitComponentsDict = fitSetup[observableName]["components"]

            for icomp,componentName in enumerate(sorted(fitComponentsDict.keys())):
                componentUncertainties = fitComponentsDict[componentName]["yield"]
                component=ObservableComponent(observableName+"__"+componentName+"__"+str(icomp))
                coeff=CoefficientMultiplyFunction()
                for parameterName in componentUncertainties:
                    coeff.addDistribution(parametersDict[parameterName]["dist"],parametersDict[parameterName]["dist"].getParameterName())
                component.setCoefficientFunction(coeff)
                componentHist = RootHistogram(observableName+"__"+componentName,{
                    "zerobin_fillfactor":0.001,
                    "use_errors":"true"
                })
                componentHist.setFileName(fitComponentsDict[componentName]["nominal"]["file"])
                componentHist.setHistoName(fitComponentsDict[componentName]["nominal"]["name"])
                component.setNominalHistogram(componentHist)
                file.write(componentHist.toConfigString())
                for shapeSysDict in fitComponentsDict[componentName]["shape"]:
                    parameterNameShape = shapeSysDict["parameter"]
                    #hardcoded norm of a few systematics
                    fixedShape = ["eleMultiIso","eleMultiVeto","muMulti","tw","dy"]
                    if parameterNameShape in fixedShape:
                        component.addShapeNorm(parameterNameShape)
                    histUp = shapeSysDict["up"]
                    histDown = shapeSysDict["down"]
                    componentHistSysUp = RootHistogram(observableName+"__"+componentName+"__"+parameterNameShape+"Up",{
                        "zerobin_fillfactor":0.001,
                        "use_errors":"true"
                    })
                    componentHistSysUp.setFileName(histUp["file"])
                    componentHistSysUp.setHistoName(histUp["name"])
                    file.write(componentHistSysUp.toConfigString())
                    componentHistSysDown = RootHistogram(observableName+"__"+componentName+"__"+parameterNameShape+"Down",{
                        "zerobin_fillfactor":0.001,
                        "use_errors":"true"
                    })
                    componentHistSysDown.setFileName(histDown["file"])
                    componentHistSysDown.setHistoName(histDown["name"])
                    file.write(componentHistSysDown.toConfigString())
                    component.addUncertaintyHistograms(componentHistSysUp, componentHistSysDown, parametersDict[parameterNameShape]["dist"],parametersDict[parameterNameShape]["dist"].getParameterName())
                
                observable.addComponent(component)
                
                
                
                        
            model.addObservable(observable)
            
            if not pseudo:
                dataHist = RootHistogram(observableName+"__data",{
                    "zerobin_fillfactor":0.001,
                    "use_errors":"true"
                })
                dataDict[observableName]=dataHist
                dataHist.setFileName(fitSetup[observableName]["data"]["file"])
                dataHist.setHistoName(fitSetup[observableName]["data"]["name"])

                file.write(dataHist.toConfigString())
                
            else:
                pass
            
        file.write(model.toConfigString())
        
        file.write("\n")
        file.write("\n")
        
        file.write('''
myminimizer = {
    type = "minimizer_chain";
    minimizers = (
        {
            type = "mcmc_minimizer";
            iterations = 150000;
            burn-in = 50000;
            name = "mcmc_min20";
            stepsize_factor = 1.25;
        },
        {
            type = "mcmc_minimizer";
            iterations = 150000;
            burn-in = 50000;
            name = "mcmc_min10";
            stepsize_factor = 1.0;
        },
        {
            type = "mcmc_minimizer";
            iterations = 150000;
            burn-in = 50000;
            name = "mcmc_min05";
            stepsize_factor = 0.5;
        },
        {
            type = "mcmc_minimizer";
            iterations = 150000;
            burn-in = 50000;
            name = "mcmc_min05";
            stepsize_factor = 0.1;
        }
    );
    last_minimizer = {
        type = "newton_minimizer";
        par_eps = 1e-3; // optional; default is 1e-4'
        maxit = 800000; // optional; default is 10,000'
        improve_cov = true; // optional; default is false'
        force_cov_positive = true; // optional, default is false'
        step_cov = 0.01; // optional; default is 0.1'
    };
};
        ''')
        

        
        
        file.write('pd = {\n')
        file.write('    name= "'+modelName+'";\n')
        file.write('    type = "mle";\n')
        
        parametersCfg = ""
        for parameterName in sorted(parametersDict.keys()):
            parametersCfg+='"'+parameterName+'",'
        parametersCfg=parametersCfg[:-1]
        file.write('    parameters = ('+parametersCfg+');\n')
        file.write('    minimizer = \"@myminimizer\";\n')
        file.write('    write_covariance = true;\n')
        file.write('};\n')

        file.write('main={\n')
        
        if pseudo:
            file.write('    data_source = {\n')
            file.write('        type = "model_source";\n')
            file.write('        name="data";\n')
            file.write('        model = "@'+model.getVarname()+'";\n')
            file.write('        dice_poisson = true; // optional; default is true\n')
            file.write('        dice_template_uncertainties = false; // optional; default is true\n')
            file.write('        dice_rvobs = false; // optional; default is true\n')
            file.write('        parameters-for-nll = {\n') 
            for parameterName in sorted(parametersDict.keys()):
                mean = parametersDict[parameterName]["config"]["mean"]
                file.write('            '+parameterName+' = '+str(mean)+';\n') 
            file.write('        }; //optional; assuming p1, p2, p3 are parameters\n')
            file.write('        rnd_gen = { seed = '+str(seed)+'; }; // optional\n')
            file.write('        };\n')
        else:
        
            file.write('    data_source={\n')
            file.write('        type="histo_source";\n')
            file.write('        name="data";\n')
            for observableName in sorted(dataDict.keys()):
                file.write('        obs_'+observableName+'="@'+dataDict[observableName].getVarname()+'";\n')
            file.write('    };\n')

            

        file.write('    n-events=1;\n')
        file.write('    model="@'+model.getVarname()+'";\n')
        file.write('    output_database={\n')
        file.write('        type="rootfile_database";\n')
        file.write('        filename="'+outputFile+'";\n')
        file.write('    };\n')
        file.write('    producers=("@pd"\n')
        file.write('    );\n')
        file.write('};\n')

        file.write('options = {\n')
        file.write('    plugin_files = ("$THETA_DIR/lib/libplugins.so", "$THETA_DIR/lib/libroot-plugin.so", "$THETA_DIR/lib/liblibtheta.so");\n')
        file.write('};\n')
            
        file.close()

        


