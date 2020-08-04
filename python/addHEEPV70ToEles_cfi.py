import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.slimming.modifiedElectrons_cfi import modifiedElectrons
from ExoAnalysis.WR_lite.heepV70Modifier_cfi import heep_modifications

heepElectrons = modifiedElectrons.clone()
heepElectrons.modifierConfig.modifications = heep_modifications

slimmedHEEPElectrons = heepElectrons.clone()

addHEEPToSlimmedElectrons = cms.Sequence( slimmedHEEPElectrons )
addHEEPToHEEPElectrons = cms.Sequence( heepElectrons )