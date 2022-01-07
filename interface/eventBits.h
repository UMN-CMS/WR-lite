#ifndef eventBits_h
#define eventBits_h

#include <stdint.h>
#include <list>
#include <string>
#include <iostream>

class eventBits {

public:

	eventBits();
	void clear();
	void checkCutsElectron();
	void checkCutsMuon();

	//EVENT WEIGHT
	double eventWeight;
	double count;

	//EVENT VALUES
	bool twoElectrons;
	bool twoMuons;
	bool mixedLeptons;
	bool passedElectronReco;
	bool passedMuonReco;
	bool sameSignElectrons;
	bool mixedGen;
	bool electronGen;
	bool muonGen;
	bool tauGen;
	bool hasPVertex;
	
	//Failure Conditions
	bool extraLeptons;
	bool failedGenPtEta;
	bool badJets;
	bool oneLepton;
	
    //NN Results
	bool nnResolvedPickedLeadElectron;
	bool nnResolvedPickedLeadMuon;
	bool nnSuperResolvedPickedLeadElectron;
	bool nnSuperResolvedPickedLeadMuon;
	
	bool nnResolvedPickedSubLeadElectron;
	bool nnResolvedPickedSubLeadMuon;
	bool nnSuperResolvedPickedSubLeadElectron;
	bool nnSuperResolvedPickedSubLeadMuon;

	//nMinusOne Information
	std::list<std::string> nMinusOnePassElectron;
	std::list<std::string> nMinusOneFailElectron;
	std::list<std::string> nMinusOnePassMuon;
	std::list<std::string> nMinusOneFailMuon;
	
	//Gen Values
	double leadLeptonPt;
	double leadLeptonType;
	double subleadLeptonPt;
	double subleadLeptonType;
	
	double quark1Eta;
	double quark1Phi;
	double quark1Mass;
	double quark1Pt;

	double quark2Eta;
	double quark2Phi;
	double quark2Mass;
	double quark2Pt;

	double lepton1Eta;
	double lepton1Phi;
	double lepton1Mass;
	double lepton1Pt;
	int lepton1Id;

	double lepton2Eta;
	double lepton2Phi;
	double lepton2Mass;
	double lepton2Pt;
	int lepton2Id;
	
	//Reco values
	
	//Jets
	double leadJetRecoEta;
	double leaJetRecoPhi;
	double leadJetRecoMass;
	double leadJetRecoPt;

	double subJetRecoEta;
	double subJetRecoPhi;
	double subJetRecoMass;
	double subJetRecoPt;

	//Electrons	
	double subRecoElectronEta;
	double subRecoElectronPhi;
	double subRecoElectronMass;
	double subRecoElectronPt;
	double subRecoElectronDPhi;
	double subRecoElectronDR;
	double subRecoElectronEtaWR;
	
	double leadRecoElectronEta;
	double leadRecoElectronPhi;
	double leadRecoElectronMass;
	double leadRecoElectronPt;
	double leadRecoElectronDPhi;
	double leadRecoElectronDR;
	double leadRecoElectronEtaWR;

	//Muons
	double subRecoMuonEta;
	double subRecoMuonPhi;
	double subRecoMuonMass;
	double subRecoMuonPt;
	double subRecoMuonDPhi;
	double subRecoMuonDR;
	double subRecoMuonEtaWR;
	
	double leadRecoMuonEta;
	double leadRecoMuonPhi;
	double leadRecoMuonMass;
	double leadRecoMuonPt;
	double leadRecoMuonDPhi;
	double leadRecoMuonDR;
	double leadRecoMuonEtaWR;
	
	//Combinations
	
	double WRMass;
	double NMass;
	
	double leadJsubJRecoMass;
	double leadJsubJRecoMassError;
	
	
	double subElectronleadElectronRecodr2;
	double subElectronleadJRecodr2;
	double subElectronsubJRecodr2;
	double subleadElectronJJRecodr2;
	double leadElectronleadJRecodr2;
	double leadElectronsubJRecodr2;
	double leadJsubJdr2;
	double leadElectronJJRecodr2;

	double leadElectronsubElectronRecoMass;
	double subElectronleadJsubJRecoMass;
	double leadElectronleadJsubJRecoMass;
	double matchedElectronleadJsubJRecoMass;

	double subMuonleadMuonRecodr2;
	double subMuonleadJRecodr2;
	double subMuonsubJRecodr2;
	double subleadMuonJJRecodr2;
	double leadMuonleadJRecodr2;
	double leadMuonsubJRecodr2;
	double leadMuonJJRecodr2;

	double leadMuonsubMuonRecoMass;
	double subMuonleadJsubJRecoMass;
	double leadMuonleadJsubJRecoMass;
	double matchedMuonleadJsubJRecoMass;

    double fullRecoMassElectron;
	double fullRecoMassMuon;
	
	//Matched Reco values
	
	//Electrons
	
	double sphericityElectron1;
	double sphericityElectron2;
	
	double match1ElectronEta;
	double match1ElectronPhi;
	double match1ElectronDPhi;
	double match1ElectronDR;
	double match1ElectronPt;

	double match1ElectronEtaWR;
	double match1ElectronPhiWR;
	double match1ElectronDPhiWR;
	double match1ElectronDRWR;
	double match1ElectronPtWR;
	
	double match1ElectronEtaL1;
	double match1ElectronPhiL1;
	double match1ElectronDPhiL1;
	double match1ElectronDRL1;
	double match1ElectronPtL1;
	
	double match1ElectronEtaJJL1;
	double match1ElectronPhiJJL1;
	double match1ElectronDPhiJJL1;
	double match1ElectronDRJJL1;
	double match1ElectronPtJJL1;
	
	
	
	double match2ElectronEta;
	double match2ElectronPhi;
	double match2ElectronDPhi;
	double match2ElectronDR;
	double match2ElectronPt;
	
	double match2ElectronEtaWR;
	double match2ElectronPhiWR;
	double match2ElectronDPhiWR;
	double match2ElectronDRWR;
	double match2ElectronPtWR;
	
	double match2ElectronEtaL2;
	double match2ElectronPhiL2;
	double match2ElectronDPhiL2;
	double match2ElectronDRL2;
	double match2ElectronPtL2;
	
	double match2ElectronEtaJJL2;
	double match2ElectronPhiJJL2;
	double match2ElectronDPhiJJL2;
	double match2ElectronDRJJL2;
	double match2ElectronPtJJL2;

	//Muons
	
	double sphericityMuon1;
	double sphericityMuon2;
	
	double match1MuonEta;
	double match1MuonPhi;
	double match1MuonDPhi;
	double match1MuonDR;
	double match1MuonPt;
	
	double match1MuonEtaWR;
	double match1MuonPhiWR;
	double match1MuonDPhiWR;
	double match1MuonDRWR;
	double match1MuonPtWR;
	
	double match1MuonEtaL1;
	double match1MuonPhiL1;
	double match1MuonDPhiL1;
	double match1MuonDRL1;
	double match1MuonPtL1;
	
	double match1MuonEtaJJL1;
	double match1MuonPhiJJL1;
	double match1MuonDPhiJJL1;
	double match1MuonDRJJL1;
	double match1MuonPtJJL1;

	double match2MuonEta;
	double match2MuonPhi;
	double match2MuonDPhi;
	double match2MuonDR;
	double match2MuonPt;
	
	double match2MuonEtaL2;
	double match2MuonPhiL2;
	double match2MuonDPhiL2;
	double match2MuonDRL2;
	double match2MuonPtL2;
	
	double match2MuonEtaJJL2;
	double match2MuonPhiJJL2;
	double match2MuonDPhiJJL2;
	double match2MuonDRJJL2;
	double match2MuonPtJJL2;

	double match2MuonEtaWR;
	double match2MuonPhiWR;
	double match2MuonDPhiWR;
	double match2MuonDRWR;
	double match2MuonPtWR;

	
	//Combinations
	double electron1RecoMass;
	double electron2RecoMass;
    
	double muon1RecoMass;
	double muon2RecoMass;


private:



};
#endif
