#include "ExoAnalysis/WR-lite/interface/eventBits.h"

#include <list>
#include <string>


eventBits::eventBits() {
  //EVENT WEIGHT
  eventWeight = 0.0;

  //EVENT VALUES
  twoElectrons = false;
  twoMuons = false;
  mixedLeptons = false;
  passedReco = false;
  
  jet1Eta = -10000.0;
  jet1Phi = -10000.0;
  jet1Mass = -10000.0;
  jet1Pt = -10000.0;
  
  jet2Eta = -10000.0;
  jet2Phi = -10000.0;
  jet2Mass = -10000.0;
  jet2Pt = -10000.0;
  
  lepton1Eta = -10000.0;
  lepton1Phi = -10000.0;
  lepton1Mass = -10000.0;
  lepton1Pt = -10000.0;
  
  lepton2Eta = -10000.0;
  lepton2Phi = -10000.0;
  lepton2Mass = -10000.0;
  lepton2Pt = -10000.0;
  
  subLeptonEta = -10000.0;
  subLeptonPhi = -10000.0;
  subLeptonMass = -10000.0;
  subLeptonPt = -10000.0;
  
  leadLeptonEta = -10000.0;
  leadLeptonPhi = -10000.0;
  leadLeptonMass = -10000.0;
  leadLeptonPt = -10000.0;
  
  lepton1lepton2dr2 = -10000.0;
  lepton1quark1dr2 = -10000.0;
  lepton1quark2dr2 = -10000.0;
  lepton2quark1dr2 = -10000.0;
  lepton2quark2dr2 = -10000.0;
  quark1quark2dr2 = -10000.0;
  
  lepton1lepton2Mass = -10000.0;
  quark1quark2Mass = -10000.0;
  
  lepton1quark1quark2Mass = -10000.0;
  lepton2quark1quark2Mass = -10000.0;
  
  fullMass = -10000.0;
  
  subMuonMatchedJet1Jet2Mass = -10000.0;
  matchedMuonMatchedJet1Jet2Mass = -10000.0;
  
  subElectronMatchedJet1Jet2Mass = -10000.0;
  matchedElectronMatchedJet1Jet2Mass = -10000.0;
}

void eventBits::clear() {
  //EVENT WEIGHT
  eventWeight = 0.0;

  //EVENT VALUES
  twoElectrons = false;
  twoMuons = false;
  mixedLeptons = false;
  passedReco = false;
  
  nMinusOne.clear();
  
  jet1Eta = -10000.0;
  jet1Phi = -10000.0;
  jet1Mass = -10000.0;
  jet1Pt = -10000.0;
  
  jet2Eta = -10000.0;
  jet2Phi = -10000.0;
  jet2Mass = -10000.0;
  jet2Pt = -10000.0;
  
  lepton1Eta = -10000.0;
  lepton1Phi = -10000.0;
  lepton1Mass = -10000.0;
  lepton1Pt = -10000.0;
  
  lepton2Eta = -10000.0;
  lepton2Phi = -10000.0;
  lepton2Mass = -10000.0;
  lepton2Pt = -10000.0;
  
  subLeptonEta = -10000.0;
  subLeptonPhi = -10000.0;
  subLeptonMass = -10000.0;
  subLeptonPt = -10000.0;
  
  leadLeptonEta = -10000.0;
  leadLeptonPhi = -10000.0;
  leadLeptonMass = -10000.0;
  leadLeptonPt = -10000.0;
  
  lepton1lepton2dr2 = -10000.0;
  lepton1quark1dr2 = -10000.0;
  lepton1quark2dr2 = -10000.0;
  lepton2quark1dr2 = -10000.0;
  lepton2quark2dr2 = -10000.0;
  quark1quark2dr2 = -10000.0;
  
  lepton1lepton2Mass = -10000.0;
  quark1quark2Mass = -10000.0;
  
  lepton1quark1quark2Mass = -10000.0;
  lepton2quark1quark2Mass = -10000.0;
  
  fullMass = -10000.0;
  
  subMuonMatchedJet1Jet2Mass = -10000.0;
  matchedMuonMatchedJet1Jet2Mass = -10000.0;
  
  subElectronMatchedJet1Jet2Mass = -10000.0;
  matchedElectronMatchedJet1Jet2Mass = -10000.0;
}
