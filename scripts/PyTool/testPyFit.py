#!/usr/bin/python

import ROOT
import math
import random
import numpy
import pyfit



data = ROOT.TH1D("data","",1,-1,1)
data.SetBinContent(1,100)
pred = ROOT.TH1D("pred","",1,-1,1)
pred.SetBinContent(1,1)
pred.SetBinError(1,0.1)

fit = ROOT.PyFit.MLFit(True)
obs = ROOT.PyFit.Observable(data)
par = ROOT.PyFit.Parameter("testz")


comp = ROOT.PyFit.ConstShapeComponent(pred)
comp.addSFParameter(par)
obs.addComponent(comp)
fit.addObservable(obs)
fit.addParameter(par)
'''
xvalues = numpy.linspace(50,150,50)
yvalues = numpy.zeros(len(xvalues))
for i,x in enumerate(xvalues):
    par.setScaleFactor(x)
    yvalues[i]=-math.exp(-fit.globalNll())
    #print yvalues[i]
graph = ROOT.TGraph(len(xvalues),xvalues,yvalues)
graph.Draw("APL")
ROOT.gPad.WaitPrimitive()
'''
#par.setScaleFactor(100.0)
fit.minimize()

#print obs,par,comp

#obs.getPrediction(parameters).getLikelihood(dataHist)
