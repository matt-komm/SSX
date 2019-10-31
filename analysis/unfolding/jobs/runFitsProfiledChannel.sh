syst="btag,ltag,eleEff,muEff,en~,res~,pu,unc~,dy,tw,eleMultiIso,eleMultiVeto,muMulti"

#python driver.py -m tasks/makeFitMarginalized -c channels:$1 -c systematics:$syst
#for sys in btag ltag eleEff muEff en~ res~ pu unc~ dy tw eleMultiIso eleMultiVeto muMulti
#    do
#    python driver.py -m tasks/makeFitMarginalized -c channels:$1 -c systematics:$sys -c output:$sys"only"
#    done
python driver.py -m setup/Wjets -m tasks/makeFitMarginalized -c channels:$1 -c systematics:$syst

