import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.parseArguments()


process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        options.inputFiles
    )
)

process.demo = cms.EDAnalyzer('WR_MASS_PLOT',
  tracks = cms.untracked.InputTag('ctfWithMaterialTracks'),
  genParticles = cms.InputTag("prunedGenParticles"),
  AK4recoCHSJets = cms.InputTag("slimmedJets"),
  regMuons = cms.InputTag("slimmedMuons"),
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string(options.outputFile)
)

process.p = cms.Path(process.demo)
