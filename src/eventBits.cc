#include "ExoAnalysis/WR-lite/interface/eventBits.h"

#include <list>
#include <string>


eventBits::eventBits() {
	//EVENT WEIGHT
	eventWeight = 0.0;
	count = 0.0;

	//EVENT VALUES
	twoElectrons = false;
	twoMuons = false;
	mixedLeptons = false;
	passedElectronReco = false;
	passedMuonReco = false;

	quark1Eta = -10000.0;
	quark1Phi = -10000.0;
	quark1Mass = -10000.0;
	quark1Pt = -10000.0;

	quark2Eta = -10000.0;
	quark2Phi = -10000.0;
	quark2Mass = -10000.0;
	quark2Pt = -10000.0;

	lepton1Eta = -10000.0;
	lepton1Phi = -10000.0;
	lepton1Mass = -10000.0;
	lepton1Pt = -10000.0;
	lepton1Id = -10000;
	
	lepton2Eta = -10000.0;
	lepton2Phi = -10000.0;
	lepton2Mass = -10000.0;
	lepton2Pt = -10000.0;
	lepton2Id = -10000;
	
	leadJetRecoEta = -10000.0;
	leaJetRecoPhi = -10000.0;
	leadJetRecoMass = -10000.0;
	leadJetRecoPt = -10000.0;

	subJetRecoEta = -10000.0;
	subJetRecoPhi = -10000.0;
	subJetRecoMass = -10000.0;
	subJetRecoPt = -10000.0;

	subRecoElectronEta = -10000.0;
	subRecoElectronPhi = -10000.0;
	subRecoElectronMass = -10000.0;
	subRecoElectronPt = -10000.0;
	
	leadRecoElectronEta = -10000.0;
	leadRecoElectronPhi = -10000.0;
	leadRecoElectronMass = -10000.0;
	leadRecoElectronPt = -10000.0;

	subElectronleadElectronRecodr2 = -10000.0;
	subElectronleadJRecodr2 = -10000.0;
	subElectronsubJRecodr2 = -10000.0;
	leadElectronleadJRecodr2 = -10000.0;
	leadElectronsubJRecodr2 = -10000.0;
	leadJsubJdr2 = -10000.0;

	leadElectronsubElectronRecoMass = -10000.0;
	subElectronleadJsubJRecoMass = -10000.0;
	leadElectronleadJsubJRecoMass = -10000.0;
	matchedElectronleadJsubJRecoMass = -10000.0;

	leadJsubJRecoMass = -10000.0;
	electron1RecoMass = -10000.0;
	electron2RecoMass = -10000.0;
	leadJsubJRecoMassError = -10000.0;
	electron1RecoMassError = -10000.0;
	electron2RecoMassError = -10000.0;

	fullRecoMassElectron = -10000.0;

	subRecoMuonEta = -10000.0;
	subRecoMuonPhi = -10000.0;
	subRecoMuonMass = -10000.0;
	subRecoMuonPt = -10000.0;

	leadRecoMuonEta = -10000.0;
	leadRecoMuonPhi = -10000.0;
	leadRecoMuonMass = -10000.0;
	leadRecoMuonPt = -10000.0;

	subMuonleadMuonRecodr2 = -10000.0;
	subMuonleadJRecodr2 = -10000.0;
	subMuonsubJRecodr2 = -10000.0;
	leadMuonleadJRecodr2 = -10000.0;
	leadMuonsubJRecodr2 = -10000.0;

	leadMuonsubMuonRecoMass = -10000.0;
	subMuonleadJsubJRecoMass = -10000.0;
	leadMuonleadJsubJRecoMass = -10000.0;
	matchedMuonleadJsubJRecoMass = -10000.0;

	muon1RecoMass = -10000.0;
	muon2RecoMass = -10000.0;

	fullRecoMassMuon = -10000.0;
	
	
	match1ElectronEta = -10000.0;
	match1ElectronPhi = -10000.0;
	match1ElectronDPhi = -10000.0;
	match1ElectronDR = -10000.0;
	match1ElectronPt = -10000.0;

	match2ElectronEta = -10000.0;
	match2ElectronPhi = -10000.0;
	match2ElectronDPhi = -10000.0;
	match2ElectronDR = -10000.0;
	match2ElectronPt = -10000.0;

	match1MuonEta = -10000.0;
	match1MuonPhi = -10000.0;
	match1MuonDPhi = -10000.0;
	match1MuonDR = -10000.0;
	match1MuonPt = -10000.0;

	match2MuonEta = -10000.0;
	match2MuonPhi = -10000.0;
	match2MuonDPhi = -10000.0;
	match2MuonDR = -10000.0;
	match2MuonPt = -10000.0;
	
	match1ElectronEtaWR = -10000.0;
	match1ElectronPhiWR = -10000.0;
	match1ElectronDPhiWR = -10000.0;
	match1ElectronDRWR = -10000.0;
	match1ElectronPtWR = -10000.0;

	match2ElectronEtaWR = -10000.0;
	match2ElectronPhiWR = -10000.0;
	match2ElectronDPhiWR = -10000.0;
	match2ElectronDRWR = -10000.0;
	match2ElectronPtWR = -10000.0;

	match1MuonEtaWR = -10000.0;
	match1MuonPhiWR = -10000.0;
	match1MuonDPhiWR = -10000.0;
	match1MuonDRWR = -10000.0;
	match1MuonPtWR = -10000.0;

	match2MuonEtaWR = -10000.0;
	match2MuonPhiWR = -10000.0;
	match2MuonDPhiWR = -10000.0;
	match2MuonDRWR = -10000.0;
	match2MuonPtWR = -10000.0;

	match1ElectronEtaJJL1 = -10000.0;
	match1ElectronPhiJJL1 = -10000.0;
	match1ElectronDPhiJJL1 = -10000.0;
	match1ElectronDRJJL1 = -10000.0;
	match1ElectronPtJJL1 = -10000.0;

	match2ElectronEtaJJL2 = -10000.0;
	match2ElectronPhiJJL2 = -10000.0;
	match2ElectronDPhiJJL2 = -10000.0;
	match2ElectronDRJJL2 = -10000.0;
	match2ElectronPtJJL2 = -10000.0;

	match1MuonEtaJJL1 = -10000.0;
	match1MuonPhiJJL1 = -10000.0;
	match1MuonDPhiJJL1 = -10000.0;
	match1MuonDRJJL1 = -10000.0;
	match1MuonPtJJL1 = -10000.0;

	match2MuonEtaJJL2 = -10000.0;
	match2MuonPhiJJL2 = -10000.0;
	match2MuonDPhiJJL2 = -10000.0;
	match2MuonDRJJL2 = -10000.0;
	match2MuonPtJJL2 = -10000.0;

	match1ElectronEtaL1 = -10000.0;
	match1ElectronPhiL1 = -10000.0;
	match1ElectronDPhiL1 = -10000.0;
	match1ElectronDRL1 = -10000.0;
	match1ElectronPtL1 = -10000.0;

	match2ElectronEtaL2 = -10000.0;
	match2ElectronPhiL2 = -10000.0;
	match2ElectronDPhiL2 = -10000.0;
	match2ElectronDRL2 = -10000.0;
	match2ElectronPtL2 = -10000.0;

	match1MuonEtaL1 = -10000.0;
	match1MuonPhiL1 = -10000.0;
	match1MuonDPhiL1 = -10000.0;
	match1MuonDRL1 = -10000.0;
	match1MuonPtL1 = -10000.0;

	match2MuonEtaL2 = -10000.0;
	match2MuonPhiL2 = -10000.0;
	match2MuonDPhiL2 = -10000.0;
	match2MuonDRL2 = -10000.0;
	match2MuonPtL2 = -10000.0;
}

void eventBits::clear() {
	//EVENT WEIGHT
	eventWeight = 0.0;

	//EVENT VALUES
	twoElectrons = false;
	twoMuons = false;
	mixedLeptons = false;
	passedElectronReco = false;
	passedMuonReco = false;

	nMinusOnePassElectron.clear();
	nMinusOneFailElectron.clear();
	nMinusOnePassMuon.clear();
	nMinusOneFailMuon.clear();

	quark1Eta = -10000.0;
	quark1Phi = -10000.0;
	quark1Mass = -10000.0;
	quark1Pt = -10000.0;

	quark2Eta = -10000.0;
	quark2Phi = -10000.0;
	quark2Mass = -10000.0;
	quark2Pt = -10000.0;

	lepton1Eta = -10000.0;
	lepton1Phi = -10000.0;
	lepton1Mass = -10000.0;
	lepton1Pt = -10000.0;
	lepton1Id = -10000;

	lepton2Eta = -10000.0;
	lepton2Phi = -10000.0;
	lepton2Mass = -10000.0;
	lepton2Pt = -10000.0;
	lepton2Id = -10000;

	leadJetRecoEta = -10000.0;
	leaJetRecoPhi = -10000.0;
	leadJetRecoMass = -10000.0;
	leadJetRecoPt = -10000.0;

	subJetRecoEta = -10000.0;
	subJetRecoPhi = -10000.0;
	subJetRecoMass = -10000.0;
	subJetRecoPt = -10000.0;

	subRecoElectronEta = -10000.0;
	subRecoElectronPhi = -10000.0;
	subRecoElectronMass = -10000.0;
	subRecoElectronPt = -10000.0;
	
	leadRecoElectronEta = -10000.0;
	leadRecoElectronPhi = -10000.0;
	leadRecoElectronMass = -10000.0;
	leadRecoElectronPt = -10000.0;

	subElectronleadElectronRecodr2 = -10000.0;
	subElectronleadJRecodr2 = -10000.0;
	subElectronsubJRecodr2 = -10000.0;
	leadElectronleadJRecodr2 = -10000.0;
	leadElectronsubJRecodr2 = -10000.0;
	leadJsubJdr2 = -10000.0;

	leadElectronsubElectronRecoMass = -10000.0;
	subElectronleadJsubJRecoMass = -10000.0;
	leadElectronleadJsubJRecoMass = -10000.0;
	matchedElectronleadJsubJRecoMass = -10000.0;

	leadJsubJRecoMass = -10000.0;
	electron1RecoMass = -10000.0;
	electron2RecoMass = -10000.0;
	leadJsubJRecoMassError = -10000.0;
	electron1RecoMassError = -10000.0;
	electron2RecoMassError = -10000.0;

	fullRecoMassElectron = -10000.0;

	subRecoMuonEta = -10000.0;
	subRecoMuonPhi = -10000.0;
	subRecoMuonMass = -10000.0;
	subRecoMuonPt = -10000.0;

	leadRecoMuonEta = -10000.0;
	leadRecoMuonPhi = -10000.0;
	leadRecoMuonMass = -10000.0;
	leadRecoMuonPt = -10000.0;

	subMuonleadMuonRecodr2 = -10000.0;
	subMuonleadJRecodr2 = -10000.0;
	subMuonsubJRecodr2 = -10000.0;
	leadMuonleadJRecodr2 = -10000.0;
	leadMuonsubJRecodr2 = -10000.0;

	leadMuonsubMuonRecoMass = -10000.0;
	subMuonleadJsubJRecoMass = -10000.0;
	leadMuonleadJsubJRecoMass = -10000.0;
	matchedMuonleadJsubJRecoMass = -10000.0;

	muon1RecoMass = -10000.0;
	muon2RecoMass = -10000.0;

	fullRecoMassMuon = -10000.0;
	
	match1ElectronEta = -10000.0;
	match1ElectronPhi = -10000.0;
	match1ElectronDPhi = -10000.0;
	match1ElectronDR = -10000.0;
	match1ElectronPt = -10000.0;

	match2ElectronEta = -10000.0;
	match2ElectronPhi = -10000.0;
	match2ElectronDPhi = -10000.0;
	match2ElectronDR = -10000.0;
	match2ElectronPt = -10000.0;

	match1MuonEta = -10000.0;
	match1MuonPhi = -10000.0;
	match1MuonDPhi = -10000.0;
	match1MuonDR = -10000.0;
	match1MuonPt = -10000.0;

	match2MuonEta = -10000.0;
	match2MuonPhi = -10000.0;
	match2MuonDPhi = -10000.0;
	match2MuonDR = -10000.0;
	match2MuonPt = -10000.0;
	
	match1ElectronEtaWR = -10000.0;
	match1ElectronPhiWR = -10000.0;
	match1ElectronDPhiWR = -10000.0;
	match1ElectronDRWR = -10000.0;
	match1ElectronPtWR = -10000.0;

	match2ElectronEtaWR = -10000.0;
	match2ElectronPhiWR = -10000.0;
	match2ElectronDPhiWR = -10000.0;
	match2ElectronDRWR = -10000.0;
	match2ElectronPtWR = -10000.0;

	match1MuonEtaWR = -10000.0;
	match1MuonPhiWR = -10000.0;
	match1MuonDPhiWR = -10000.0;
	match1MuonDRWR = -10000.0;
	match1MuonPtWR = -10000.0;

	match2MuonEtaWR = -10000.0;
	match2MuonPhiWR = -10000.0;
	match2MuonDPhiWR = -10000.0;
	match2MuonDRWR = -10000.0;
	match2MuonPtWR = -10000.0;

	match1ElectronEtaJJL1 = -10000.0;
	match1ElectronPhiJJL1 = -10000.0;
	match1ElectronDPhiJJL1 = -10000.0;
	match1ElectronDRJJL1 = -10000.0;
	match1ElectronPtJJL1 = -10000.0;

	match2ElectronEtaJJL2 = -10000.0;
	match2ElectronPhiJJL2 = -10000.0;
	match2ElectronDPhiJJL2 = -10000.0;
	match2ElectronDRJJL2 = -10000.0;
	match2ElectronPtJJL2 = -10000.0;

	match1MuonEtaJJL1 = -10000.0;
	match1MuonPhiJJL1 = -10000.0;
	match1MuonDPhiJJL1 = -10000.0;
	match1MuonDRJJL1 = -10000.0;
	match1MuonPtJJL1 = -10000.0;

	match2MuonEtaJJL2 = -10000.0;
	match2MuonPhiJJL2 = -10000.0;
	match2MuonDPhiJJL2 = -10000.0;
	match2MuonDRJJL2 = -10000.0;
	match2MuonPtJJL2 = -10000.0;

	match1ElectronEtaL1 = -10000.0;
	match1ElectronPhiL1 = -10000.0;
	match1ElectronDPhiL1 = -10000.0;
	match1ElectronDRL1 = -10000.0;
	match1ElectronPtL1 = -10000.0;

	match2ElectronEtaL2 = -10000.0;
	match2ElectronPhiL2 = -10000.0;
	match2ElectronDPhiL2 = -10000.0;
	match2ElectronDRL2 = -10000.0;
	match2ElectronPtL2 = -10000.0;

	match1MuonEtaL1 = -10000.0;
	match1MuonPhiL1 = -10000.0;
	match1MuonDPhiL1 = -10000.0;
	match1MuonDRL1 = -10000.0;
	match1MuonPtL1 = -10000.0;

	match2MuonEtaL2 = -10000.0;
	match2MuonPhiL2 = -10000.0;
	match2MuonDPhiL2 = -10000.0;
	match2MuonDRL2 = -10000.0;
	match2MuonPtL2 = -10000.0;
	
}

void eventBits::checkCutsElectron() {
	const char *label[6]  = {"jet pt > 40 GeV","jet |eta| < 2.4","lepton mass > 200 GeV","dR > 0.4","leading l pt > 60 GeV", "subleading l pt > 53 GeV"};
	

	
	//decay jets have transverse momentum greater than 400 GeV
	if (leadJetRecoPt <= 40 || subJetRecoPt <= 40){
		nMinusOneFailElectron.push_back(label[0]);
		std::cout << label[0] << std::endl;
	} else {
		nMinusOnePassElectron.push_back(label[0]);
	}
  
	//decay jets have |eta| < 2.4 
	if (leadJetRecoEta >= 2.4 || leadJetRecoEta <= -2.4 || subJetRecoEta >= 2.4 || subJetRecoEta <= -2.4){
		nMinusOneFailElectron.push_back(label[1]);
		std::cout << label[1] << std::endl;
	} else {
		nMinusOnePassElectron.push_back(label[1]);
	}

	//  invariant mass of 2 leptons > 200 GeV
	
	//std::cout << "leadElectronsubElectronRecoMass" << leadElectronsubElectronRecoMass << std::endl;
	//std::cout << "subElectronleadElectronRecodr2" << subElectronleadElectronRecodr2 << std::endl;
	//std::cout << "subElectronleadJRecodr2" << subElectronleadJRecodr2 << std::endl;
	//std::cout << "subElectronsubJRecodr2" << subElectronsubJRecodr2 << std::endl;
	//std::cout << "leadElectronleadJRecodr2" << leadElectronleadJRecodr2 << std::endl;
	//std::cout << "leadElectronsubJRecodr2" << leadElectronsubJRecodr2 << std::endl;
	//std::cout << "leadRecoElectronPt" << leadRecoElectronPt << std::endl;
	//std::cout << "subRecoElectronPt" << subRecoElectronPt << std::endl;
	
	if (leadElectronsubElectronRecoMass<=200){
		nMinusOneFailElectron.push_back(label[2]);
		//std::cout << label[2] << std::endl;
	} else {
		nMinusOnePassElectron.push_back(label[2]);
	}

	// check dR > .4 for particle combos
	if(subElectronleadElectronRecodr2 <=.16 || subElectronleadJRecodr2 <=.16 || subElectronsubJRecodr2 <=.16 || leadElectronleadJRecodr2 <=.16 || leadElectronsubJRecodr2 <=.16 || leadJsubJdr2 <=.16){
		nMinusOneFailElectron.push_back(label[3]);
		//std::cout << label[3] << std::endl;
	} else {
		nMinusOnePassElectron.push_back(label[3]);
	}
  
    //check that leading lepton has pt >60, sub leading pt > 53
	if(leadRecoElectronPt<=60){
		nMinusOneFailElectron.push_back(label[4]);
		//std::cout << label[4] << std::endl;
	} else {
		nMinusOnePassElectron.push_back(label[4]);
	}
	if(subRecoElectronPt<=53){
		nMinusOneFailElectron.push_back(label[5]);
		//std::cout << label[5] << std::endl;
	} else {
		nMinusOnePassElectron.push_back(label[5]);
	}
	
	////std::cout << nMinusOnePassElectron.size() << std::endl;
	////std::cout << nMinusOneFailElectron.size() << std::endl;
	//if(nMinusOnePassElectron.size()==6){
	//	//std::cout << "2 Electrons Passed" << std::endl;
	//	
	//}
}

void eventBits::checkCutsMuon() {
	const char *label[6]  = {"jet pt > 40 GeV","jet |eta| < 2.4","lepton mass > 200 GeV","dR > 0.4","leading l pt > 60 GeV", "subleading l pt > 53 GeV"};
		
	//decay jets have transverse momentum greater than 400 GeV
	if (leadJetRecoPt <= 40 || subJetRecoPt <= 40){
		nMinusOneFailMuon.push_back(label[0]);
	} else {
		nMinusOnePassMuon.push_back(label[0]);
	}
  
	//decay jets have |eta| < 2.4 
	if (leadJetRecoEta >= 2.4 || leadJetRecoEta <= -2.4 || subJetRecoEta >= 2.4 || subJetRecoEta <= -2.4){
		nMinusOneFailMuon.push_back(label[1]);
	} else {
		nMinusOnePassMuon.push_back(label[1]);
	}

	//  invariant mass of 2 leptons > 200 GeV
	if (leadMuonsubMuonRecoMass<=200){
		nMinusOneFailMuon.push_back(label[2]);
	} else {
		nMinusOnePassMuon.push_back(label[2]);
	}

	// check dR > .4 for particle combos
	if(subMuonleadMuonRecodr2 <=.16 || subMuonleadJRecodr2 <=.16 || subMuonsubJRecodr2 <=.16 || leadMuonleadJRecodr2 <=.16 || leadMuonsubJRecodr2 <=.16 || leadJsubJdr2 <=.16){
		nMinusOneFailMuon.push_back(label[3]);
	} else {
		nMinusOnePassMuon.push_back(label[3]);
	}
  
    //check that leading lepton has pt >60, sub leading pt > 53
	if(leadRecoMuonPt<=60){
		nMinusOneFailMuon.push_back(label[4]);
	} else {
		nMinusOnePassMuon.push_back(label[4]);
	}
	if(subRecoMuonPt<=53){
		nMinusOneFailMuon.push_back(label[5]);
	} else {
		nMinusOnePassMuon.push_back(label[5]);
	}  
	
	////std::cout << nMinusOnePassMuon.size() << std::endl;
	////std::cout << nMinusOneFailMuon.size() << std::endl;
	//if(nMinusOnePassMuon.size()==6){
	//	//std::cout << "2 Muons Passed" << std::endl;
	//}
}
	
