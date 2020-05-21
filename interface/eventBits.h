#ifndef eventBits_h
#define eventBits_h

#include <stdint.h>
#include <list>
#include <string>

class eventBits {

public:

  eventBits();
  void clear();
  
  
  //EVENT WEIGHT
  double eventWeight;

  //EVENT VALUES
  bool twoElectrons;
  bool twoMuons;
  bool mixedLeptons;
  bool passedReco;
  
  std::list<std::string> nMinusOne;
  
  double jet1Eta;
  double jet1Phi;
  double jet1Mass;
  double jet1Pt;
  
  double jet2Eta;
  double jet2Phi;
  double jet2Mass;
  double jet2Pt;
  
  double lepton1Eta;
  double lepton1Phi;
  double lepton1Mass;
  double lepton1Pt;
  
  double lepton2Eta;
  double lepton2Phi;
  double lepton2Mass;
  double lepton2Pt;
  
  double subLeptonEta;
  double subLeptonPhi;
  double subLeptonMass;
  double subLeptonPt;
  
  double leadLeptonEta;
  double leadLeptonPhi;
  double leadLeptonMass;
  double leadLeptonPt;
  
  double lepton1lepton2dr2;
  double lepton1quark1dr2;
  double lepton1quark2dr2;
  double lepton2quark1dr2;
  double lepton2quark2dr2;
  double quark1quark2dr2;
  
  double lepton1lepton2Mass;
  double quark1quark2Mass;
  
  double lepton1quark1quark2Mass;
  double lepton2quark1quark2Mass;
  
  double leadLeptonquark1quark2Mass;
  double subLeptonquark1quark2Mass;
  
  double fullMass;
  
  double subMuonMatchedJet1Jet2Mass;
  double matchedMuonMatchedJet1Jet2Mass;
  
  double subElectronMatchedJet1Jet2Mass;
  double matchedElectronMatchedJet1Jet2Mass;
  
private:



};
#endif
