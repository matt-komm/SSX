import FWCore.ParameterSet.Config as cms

process = cms.Process("TestProcess")
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/00000/004A0552-3929-E611-BD44-0025905A48F0.root'
    )
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2) )

process.plain=cms.Path()
process.filtered=cms.Path()

process.muonSelector = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("slimmedMuons"),
    minNumber = cms.uint32(1)
)

process.plain+=process.muonSelector
process.filtered+=process.muonSelector

process.jetSelector = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("slimmedJets"),
    cut = cms.string("pt>20")
)

process.filtered+=process.jetSelector



process.endpath=cms.EndPath()

process.triggerTest=cms.EDAnalyzer('TriggerTest')
process.endpath+=process.triggerTest

