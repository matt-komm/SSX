from Module import Module

import logging
import ROOT
import json
import sys
import numpy

class Plots(Module):
    def __init__(self,options=[]):
        Module.__init__(self,options)
        self._logger = logging.getLogger(__file__)
        self._logger.setLevel(logging.DEBUG)
        self._processDict = {}
        self._processDict["mu"] = {}
        self._processDict["ele"] = {}
        
    
    def getHistSetups(self,channel):
        mtwSelection = "(SingleTop_1__mtw_beforePz>50.)"
        srSelection = "(SingleTop_1__mtw_beforePz>50.)*("+self.module("ThetaModel").getBDTtchan(channel)+">0.7)"
        bgSelection = "(SingleTop_1__mtw_beforePz>50.)*("+self.module("ThetaModel").getBDTtchan(channel)+"<0.0)"
        return [
            {
                "obsname":"2j1t",
                "name":"mtw2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__mtw_beforePz",
                "xtitle":"m#lower[0.3]{#scale[0.7]{T}}(W) (GeV)",
                "ytitle":"Events / bin",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1),
                "binning":numpy.linspace(0,200,num=21),
                "legendPos":"R",
                "normalize":False,
                "logy":False,
                "cut":"",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"bdtttw2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":self.module("ThetaModel").getBDTttw(channel),
                "xtitle":"BDT#lower[0.3]{#scale[0.7]{tt/W}} discriminant",
                "ytitle":"Events / bin",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+bgSelection,
                "binning":numpy.linspace(-1,1,num=21),
                "legendPos":"L",
                "normalize":False,
                "logy":False,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }<#kern[-0.6]{ }0",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"bdttch2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":self.module("ThetaModel").getBDTtchan(channel),
                "xtitle":"BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}} discriminant",
                "ytitle":"Events / bin",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+mtwSelection,
                "binning":numpy.linspace(-1,1,num=21),
                "legendPos":"R",
                "normalize":False,
                "logy":False,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"3j2t",
                "name":"mtw3j2t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_3j2t_pos","QCD_3j2t_neg"],
                "var":"SingleTop_1__mtw_beforePz",
                "xtitle":"m#lower[0.3]{#scale[0.7]{T}}(W) (GeV)",
                "ytitle":"Events / bin",
                "selection":self.module("Samples").getNjets(3)+"*"+self.module("Samples").getNbjets(2),
                "binning":numpy.linspace(0,200,num=21),
                "legendPos":"R",
                "normalize":False,
                "logy":False,
                "cut":"",
                "region":"3j2b",
                "resRange":0.2
            },
            {
                "obsname":"2j0t",
                "name":"mtw2j0t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j0t_pos","QCD_2j0t_neg"],
                "var":"SingleTop_1__mtw_beforePz",
                "xtitle":"m#lower[0.3]{#scale[0.7]{T}}(W) (GeV)",
                "ytitle":"Events / bin",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(0),
                "binning":numpy.linspace(0,200,num=21),
                "legendPos":"R",
                "normalize":False,
                "logy":False,
                "cut":"",
                "region":"2j0b",
                "resRange":0.1
            },
            
            {
                "obsname":"2j1t",
                "name":"pt2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__Top_1__Pt",
                "xtitle":"Top quark p#scale[0.7]{#lower[0.3]{T}} (GeV)",
                "ytitle":"#LT#kern[-0.5]{ }Events#kern[-0.5]{ }#GT / GeV",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.,50.,80.,120.,180.,300.]),
                "legendPos":"R",
                "normalize":True,
                "logy":True,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }>#kern[-0.6]{ }0.7",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"y2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"fabs(SingleTop_1__Top_1__Y)",
                "xtitle":"Top quark |y|",
                "ytitle":"#LT#kern[-0.5]{ }Events#kern[-0.5]{ }#GT",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.,0.2,0.5,0.8,1.3,2.6]),
                "legendPos":"R",
                "normalize":True,
                "logy":False,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }>#kern[-0.6]{ }0.7",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"cos2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__cosTheta_tPLz",
                "xtitle":"cos#kern[0.1]{#theta}#scale[0.7]{#lower[0.28]{pol.}}#kern[-1.1]{*}",
                "ytitle":"#LT#kern[-0.5]{ }Events#kern[-0.5]{ }#GT",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([-1.0,-0.6,-0.3,0.0,0.3,0.6,1.0]),
                "legendPos":"L",
                "normalize":True,
                "logy":False,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }>#kern[-0.6]{ }0.7",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"lpt2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__TightLepton_1__Pt",
                "xtitle":"Lepton p#scale[0.7]{#lower[0.3]{T}} (GeV)",
                "ytitle":"#LT#kern[-0.5]{ }Events#kern[-0.5]{ }#GT / GeV",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([26.,35.,45.,60.,85.,200.]),
                "legendPos":"R",
                "normalize":True,
                "logy":True,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }>#kern[-0.6]{ }0.7",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"leta2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"fabs(SingleTop_1__TightLepton_1__Eta)",
                "xtitle":"Lepton |#eta|",
                "ytitle":"#LT#kern[-0.5]{ }Events#kern[-0.5]{ }#GT",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.0,0.4,0.8,1.5,1.9,2.4]),
                "legendPos":"R",
                "normalize":True,
                "logy":False,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }>#kern[-0.6]{ }0.7",
                "region":"2j1b",
                "resRange":0.2
            },
            {
                "obsname":"2j1t",
                "name":"wpt2j1t",
                "comp":["tChannel_pos","tChannel_neg","TopBkg_pos","TopBkg_neg","WZjets_pos","WZjets_neg","QCD_2j1t_pos","QCD_2j1t_neg"],
                "var":"SingleTop_1__W_1__Pt",
                "xtitle":"W p#scale[0.7]{#lower[0.3]{T}} (GeV)",
                "ytitle":"#LT#kern[-0.5]{ }Events#kern[-0.5]{ }#GT / GeV",
                "selection":self.module("Samples").getNjets(2)+"*"+self.module("Samples").getNbjets(1)+"*"+srSelection,
                "binning":numpy.array([0.,35.,55.,80.,140.,250.]),
                "legendPos":"R",
                "normalize":True,
                "logy":True,
                "cut":"m#lower[0.3]{#scale[0.7]{T}}(W)#kern[-0.6]{ }>#kern[-0.6]{ }50#kern[-0.5]{ }GeV, BDT#lower[0.3]{#scale[0.7]{#it{t}-ch}}#kern[-0.6]{ }>#kern[-0.6]{ }0.7",
                "region":"2j1b",
                "resRange":0.2
            }
        ]
        

