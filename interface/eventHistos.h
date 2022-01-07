#ifndef eventHistos_h
#define eventHistos_h


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

//ROOT CLASSES
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
//C++ CLASSES
#include <iostream>
//LOCAL CLASSES
#include "eventHistos.h"
#include "eventBits.h"


class eventHistos {
	public:
	eventHistos();
	void book(TFileDirectory histoFolder);
	void fill(eventBits& event);



	private:
	void fillElectron(eventBits& event);
	void fillMuon(eventBits& event);
	void fillNMinusOnePassElectron(eventBits& event);
	void fillNMinusOneFailElectron(eventBits& event);
	void fillNMinusOnePassMuon(eventBits& event);
	void fillNMinusOneFailMuon(eventBits& event);
	

	TFileDirectory m_histoFolder;

	//METADATA
    
	double WRMass;
	double resolvedNNMass;
	double superResolvedNNMass;
	double correctNMass;
	double treeWeight;
	double incorrectNMass;
	double leadNMass;
	double subNMass;
	
	TTree * m_massData;

	//General stats histos
	
	//1D
	
	TH1D * m_nMinusOneHisto;
	TH1D * m_nMinusOneElectronHisto;
	TH1D * m_nMinusOneMuonHisto;
	TH1D * m_leptonHisto;
	TH1D * m_failGenleptonHisto;
	TH1D * m_mixGenleptonHisto;
	TH1D * m_muonGenleptonHisto;
	TH1D * m_electronGenleptonHisto;
	TH1D * m_tauGenleptonHisto;
	TH1D * m_countHisto;
	
	//2D
	
	//Gen Histos
	
	//1D
	
	TH1D * m_leadEPtHisto;
	TH1D * m_leadMPtHisto;
	TH1D * m_leadTPtHisto;
	TH1D * m_subleadEPtHisto;
	TH1D * m_subleadMPtHisto;
	TH1D * m_subleadTPtHisto;
	
	//Reco Histos
	
	//1D
	
	TH1D * m_subMuJJhisto;
	TH1D * m_subElectronJJhisto;
	TH1D * m_jetjetMassHisto;
	TH1D * m_ElElMass_sameSign;
	TH1D * m_ElElMass_oppoSign;
	
	//2D
	
	TH2D * m_subLeadMuonHisto;
	TH2D * m_subLeadElectronHisto;
	TH2D * m_leadMuonHisto;
	TH2D * m_leadElectronHisto;
	TH2D * m_lowEtaElectronHisto;
	TH2D * m_lowEtaMuonHisto;
	TH2D * m_highEtaElectronHisto;
	TH2D * m_highEtaMuonHisto;
	TH2D * m_lowR2MuonHisto;
	TH2D * m_lowR2ElectronHisto;
	TH2D * m_highR2MuonHisto;
	TH2D * m_highR2ElectronHisto;
	
	//Matched Reco Histos
	
	//1D
	
	TH1D * m_l2MuJJhisto;
	TH1D * m_l2ElectronJJhisto;
	TH1D * m_electronEtaHisto1;
	TH1D * m_electronPhiHisto1;
	TH1D * m_electronDPhiHisto1;
	TH1D * m_electronDRHisto1;
	TH1D * m_electronPtHisto1;
	TH1D * m_electronPtHisto1Scaled;
	TH1D * m_electron1SphericityHisto;
	TH1D * m_electronEtaHisto1WR;
	TH1D * m_electronNMassHisto1;
	TH1D * m_muonEtaHisto1;
	TH1D * m_muonPhiHisto1;
	TH1D * m_muonDPhiHisto1;
	TH1D * m_muonDRHisto1;
	TH1D * m_muonPtHisto1;
	TH1D * m_muonPtHisto1Scaled;
	TH1D * m_muon1SphericityHisto;
	TH1D * m_muonEtaHisto1WR;
	TH1D * m_muonNMassHisto1;
	TH1D * m_electronEtaHisto2;
	TH1D * m_electronPhiHisto2;
	TH1D * m_electronDPhiHisto2;
	TH1D * m_electronDRHisto2;
	TH1D * m_electronPtHisto2;
	TH1D * m_electronPtHisto2Scaled;
	TH1D * m_electron2SphericityHisto;
	TH1D * m_electronEtaHisto2WR;
	TH1D * m_electronNMassHisto2;
	TH1D * m_muonEtaHisto2;
	TH1D * m_muonPhiHisto2;
	TH1D * m_muonDPhiHisto2;
	TH1D * m_muonDRHisto2;
	TH1D * m_muonPtHisto2;
	TH1D * m_muonPtHisto2Scaled;
	TH1D * m_muon2SphericityHisto;
	TH1D * m_muonEtaHisto2WR;
	TH1D * m_muonNMassHisto2;
	TH1D * m_electronPhiHisto1WR;
	TH1D * m_electronDPhiHisto1WR;
	TH1D * m_electronDRHisto1WR;
	TH1D * m_electronPtHisto1WR;
	TH1D * m_muonPhiHisto1WR;
	TH1D * m_muonDPhiHisto1WR;
	TH1D * m_muonDRHisto1WR;
	TH1D * m_muonPtHisto1WR;
	TH1D * m_electronPhiHisto2WR;
	TH1D * m_electronDPhiHisto2WR;
	TH1D * m_electronDRHisto2WR;
	TH1D * m_electronPtHisto2WR;
	TH1D * m_muonPhiHisto2WR;
	TH1D * m_muonDPhiHisto2WR;
	TH1D * m_muonDRHisto2WR;
	TH1D * m_muonPtHisto2WR;
	TH1D * m_electronEtaHisto1N;
	TH1D * m_electronPhiHisto1N;
	TH1D * m_electronDPhiHisto1N;
	TH1D * m_electronDRHisto1N;
	TH1D * m_electronPtHisto1N;
	TH1D * m_muonEtaHisto1N;
	TH1D * m_muonPhiHisto1N;
	TH1D * m_muonDPhiHisto1N;
	TH1D * m_muonDRHisto1N;
	TH1D * m_muonPtHisto1N;
	TH1D * m_electronEtaHisto2N;
	TH1D * m_electronPhiHisto2N;
	TH1D * m_electronDPhiHisto2N;
	TH1D * m_electronDRHisto2N;
	TH1D * m_electronPtHisto2N;
	TH1D * m_muonEtaHisto2N;
	TH1D * m_muonPhiHisto2N;
	TH1D * m_muonDPhiHisto2N;
	TH1D * m_muonDRHisto2N;
	TH1D * m_muonPtHisto2N;
	TH1D * m_electronEtaHisto1L;
	TH1D * m_electronPhiHisto1L;
	TH1D * m_electronDPhiHisto1L;
	TH1D * m_electronDRHisto1L;
	TH1D * m_electronPtHisto1L;
	TH1D * m_muonEtaHisto1L;
	TH1D * m_muonPhiHisto1L;
	TH1D * m_muonDPhiHisto1L;
	TH1D * m_muonDRHisto1L;
	TH1D * m_muonPtHisto1L;
	TH1D * m_electronEtaHisto2L;
	TH1D * m_electronPhiHisto2L;
	TH1D * m_electronDPhiHisto2L;
	TH1D * m_electronDRHisto2L;
	TH1D * m_electronPtHisto2L;
	TH1D * m_muonEtaHisto2L;
	TH1D * m_muonPhiHisto2L;
	TH1D * m_muonDPhiHisto2L;
	TH1D * m_muonDRHisto2L;
	TH1D * m_muonPtHisto2L;

	
	//2D
	TH2D * m_matchedMuonHisto;
	TH2D * m_matchedElectronHisto;
	TH2D * m_matchedMuon1MassHisto;
	TH2D * m_matchedElectron1MassHisto;
	TH2D * m_matchedMuon2MassHisto;
	TH2D * m_matchedElectron2MassHisto;
	
	
	//NN Histos
	
	//1D
	
	
	//2D
	
	TH2D * m_NNResolvedMuonHisto;
	TH2D * m_NNResolvedElectronHisto;
	TH2D * m_notNNResolvedMuonHisto;
	TH2D * m_notNNResolvedElectronHisto ;
	TH2D * m_NNSuperResolvedMuonHisto;
	TH2D * m_NNSuperResolvedElectronHisto;
	TH2D * m_notNNSuperResolvedMuonHisto;
	TH2D * m_notNNSuperResolvedElectronHisto;


   
};

#endif
