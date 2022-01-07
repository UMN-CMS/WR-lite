//C++ CLASSES
#include <iostream>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
//LOCAL CLASSES
#include "ExoAnalysis/WR_lite/interface/eventBits.h"
#include "ExoAnalysis/WR_lite/interface/eventHistos.h"

#include "TH1D.h"



eventHistos::eventHistos () {}
  
void eventHistos::book(TFileDirectory histoFolder) {

	m_histoFolder = histoFolder;

	//TTree for further data analysis
	m_massData = m_histoFolder.make<TTree>("massData","massData");
	m_massData->Branch("WRMass",&WRMass,"WRMass/D");
	m_massData->Branch("resolvedNNMass",&resolvedNNMass,"resolvedNNMass/D");
	m_massData->Branch("superResolvedNNMass",&superResolvedNNMass,"superResolvedNNMass/D");
	m_massData->Branch("correctNMass",&correctNMass,"correctNMass/D");
	m_massData->Branch("incorrectNMass",&incorrectNMass,"incorrectNMass/D");
	m_massData->Branch("leadNMass",&leadNMass,"leadNMass/D");
	m_massData->Branch("subNMass",&subNMass,"subNMass/D");
	m_massData->Branch("weight",&treeWeight,"weight/D");


	//General stats histos
	
	//1D
	
	m_nMinusOneHisto = m_histoFolder.make<TH1D>("nMinusOneHisto", "n-1 Plot", 6, 1, 6);

	m_nMinusOneHisto->GetXaxis()->SetBinLabel(1,"jet pt > 40 GeV");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(2,"jet |eta| < 2.4");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(3,"lepton mass > 200 GeV");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(4,"dR > 0.4");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(5,"leading l pt > 60 GeV");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(6,"subleading l pt > 53 GeV");
	
	m_nMinusOneElectronHisto = m_histoFolder.make<TH1D>("nMinusOneElectronHisto", "n-1 Electron Plot", 6, 1, 6);

	m_nMinusOneElectronHisto->GetXaxis()->SetBinLabel(1,"jet pt > 40 GeV");
	m_nMinusOneElectronHisto->GetXaxis()->SetBinLabel(2,"jet |eta| < 2.4");
	m_nMinusOneElectronHisto->GetXaxis()->SetBinLabel(3,"lepton mass > 200 GeV");
	m_nMinusOneElectronHisto->GetXaxis()->SetBinLabel(4,"dR > 0.4");
	m_nMinusOneElectronHisto->GetXaxis()->SetBinLabel(5,"leading l pt > 60 GeV");
	m_nMinusOneElectronHisto->GetXaxis()->SetBinLabel(6,"subleading l pt > 53 GeV");
	
	m_nMinusOneMuonHisto = m_histoFolder.make<TH1D>("nMinusOneMuonHisto", "n-1 Muon Plot", 6, 1, 6);

	m_nMinusOneMuonHisto->GetXaxis()->SetBinLabel(1,"jet pt > 40 GeV");
	m_nMinusOneMuonHisto->GetXaxis()->SetBinLabel(2,"jet |eta| < 2.4");
	m_nMinusOneMuonHisto->GetXaxis()->SetBinLabel(3,"lepton mass > 200 GeV");
	m_nMinusOneMuonHisto->GetXaxis()->SetBinLabel(4,"dR > 0.4");
	m_nMinusOneMuonHisto->GetXaxis()->SetBinLabel(5,"leading l pt > 60 GeV");
	m_nMinusOneMuonHisto->GetXaxis()->SetBinLabel(6,"subleading l pt > 53 GeV");
	
	m_leptonHisto = m_histoFolder.make<TH1D>("leptonHisto", "lepton Distribution" , 13, 1, 13);
	
	m_leptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_leptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_leptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_leptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_leptonHisto->GetXaxis()->SetBinLabel(5,"Nothing, failed Recos one lepton");
	m_leptonHisto->GetXaxis()->SetBinLabel(6,"Nothing, failed Recos bad jets");
	m_leptonHisto->GetXaxis()->SetBinLabel(7,"Nothing, failed Recos other");
	m_leptonHisto->GetXaxis()->SetBinLabel(8,"Nothing, extra leptons");
	m_leptonHisto->GetXaxis()->SetBinLabel(9,"failed Cuts, Electron");
	m_leptonHisto->GetXaxis()->SetBinLabel(10,"failed Cuts, Muon");
	m_leptonHisto->GetXaxis()->SetBinLabel(11,"passed Cuts, Electron");
	m_leptonHisto->GetXaxis()->SetBinLabel(12,"passed Cuts, Muon");
	m_leptonHisto->GetXaxis()->SetBinLabel(13,"passed Cuts, Both");
	
	
	m_failGenleptonHisto = m_histoFolder.make<TH1D>("leptonHistoFail", "lepton Distribution, failed Gen" , 13, 1, 13);
	
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(5,"Nothing, failed Recos one lepton");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(6,"Nothing, failed Recos bad jets");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(7,"Nothing, failed Recos other");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(8,"Nothing, extra leptons");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(9,"failed Cuts, Electron");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(10,"failed Cuts, Muon");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(11,"passed Cuts, Electron");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(12,"passed Cuts, Muon");
	m_failGenleptonHisto->GetXaxis()->SetBinLabel(13,"passed Cuts, Both");
	
	
	m_mixGenleptonHisto = m_histoFolder.make<TH1D>("leptonHistoMix", "lepton Distribution, mixed Gen" , 13, 1, 13);
	
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(5,"Nothing, failed Recos one lepton");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(6,"Nothing, failed Recos bad jets");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(7,"Nothing, failed Recos other");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(8,"Nothing, extra leptons");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(9,"failed Cuts, Electron");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(10,"failed Cuts, Muon");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(11,"passed Cuts, Electron");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(12,"passed Cuts, Muon");
	m_mixGenleptonHisto->GetXaxis()->SetBinLabel(13,"passed Cuts, Both");
	
	m_muonGenleptonHisto = m_histoFolder.make<TH1D>("leptonHistoMuon", "lepton Distribution, muon Gen" , 13, 1, 13);
	
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(5,"Nothing, failed Recos one lepton");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(6,"Nothing, failed Recos bad jets");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(7,"Nothing, failed Recos other");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(8,"Nothing, extra leptons");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(9,"failed Cuts, Electron");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(10,"failed Cuts, Muon");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(11,"passed Cuts, Electron");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(12,"passed Cuts, Muon");
	m_muonGenleptonHisto->GetXaxis()->SetBinLabel(13,"passed Cuts, Both");
	
	m_electronGenleptonHisto = m_histoFolder.make<TH1D>("leptonHistoElectron", "lepton Distribution, electron Gen" , 13, 1, 13);
	
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(5,"Nothing, failed Recos one lepton");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(6,"Nothing, failed Recos bad jets");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(7,"Nothing, failed Recos other");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(8,"Nothing, extra leptons");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(9,"failed Cuts, Electron");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(10,"failed Cuts, Muon");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(11,"passed Cuts, Electron");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(12,"passed Cuts, Muon");
	m_electronGenleptonHisto->GetXaxis()->SetBinLabel(13,"passed Cuts, Both");
	
	m_tauGenleptonHisto = m_histoFolder.make<TH1D>("leptonHistoTau", "lepton Distribution, tau Gen" , 13, 1, 13);
	
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(5,"Nothing, failed Recos one lepton");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(6,"Nothing, failed Recos bad jets");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(7,"Nothing, failed Recos other");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(8,"Nothing, extra leptons");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(9,"failed Cuts, Electron");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(10,"failed Cuts, Muon");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(11,"passed Cuts, Electron");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(12,"passed Cuts, Muon");
	m_tauGenleptonHisto->GetXaxis()->SetBinLabel(13,"passed Cuts, Both");
	
	m_countHisto = m_histoFolder.make<TH1D>("countHisto", "counts" , 1, 1, 1);
	m_countHisto->GetXaxis()->SetBinLabel(1,"count");

	
	
	//2D
	
	//Gen Histos
	
	//1D
	
	m_leadEPtHisto = m_histoFolder.make<TH1D>("leadEPtHisto" , "Lead Electron pt" , 100 , 0 , 2000 );
	m_leadEPtHisto->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_leadMPtHisto = m_histoFolder.make<TH1D>("leadMPtHisto" , "Lead Muon pt" , 100 , 0 , 2000 );
	m_leadMPtHisto->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_leadTPtHisto = m_histoFolder.make<TH1D>("leadTPtHisto" , "Lead Tau pt" , 100 , 0 , 2000 );
	m_leadTPtHisto->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_subleadEPtHisto = m_histoFolder.make<TH1D>("subleadEPtHisto" , "Sublead Electron pt" , 100 , 0 , 2000 );
	m_subleadEPtHisto->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_subleadMPtHisto = m_histoFolder.make<TH1D>("subleadMPtHisto" , "Sublead Muon pt" , 100 , 0 , 2000 );
	m_subleadMPtHisto->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_subleadTPtHisto = m_histoFolder.make<TH1D>("subleadTPtHisto" , "Sublead Tau pt" , 100 , 0 , 2000 );
	m_subleadTPtHisto->GetXaxis()-> SetTitle("Pt (GeV)");
	
	//Reco Histos
	
	//1D
	
	m_subMuJJhisto = m_histoFolder.make<TH1D>("subMuJJhisto" , "Sublead Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_subMuJJhisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	
	m_subElectronJJhisto = m_histoFolder.make<TH1D>("subElectronJJhisto" , "Sublead Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_subElectronJJhisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	
	m_jetjetMassHisto = m_histoFolder.make<TH1D>("jetjetMassHisto" , "Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_jetjetMassHisto->GetXaxis()-> SetTitle("jet + jet (GeV)");
	
	m_ElElMass_sameSign =  m_histoFolder.make<TH1D>("elelSameSignMassHisto" , "m_{ll} (GeV)" , 150 , 50 , 150 );
	m_ElElMass_oppoSign =  m_histoFolder.make<TH1D>("elelOppoSignMassHisto" , "m_{ll} (GeV)" , 150 , 50 , 150 );
	//2D
	
	m_subLeadMuonHisto = m_histoFolder.make<TH2D>("subLeadMuonHisto" , "Sublead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_subLeadMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_subLeadMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_subLeadElectronHisto = m_histoFolder.make<TH2D>("subLeadElectronHisto" , "Sublead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_subLeadElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_subLeadElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_leadMuonHisto = m_histoFolder.make<TH2D>("leadMuonHisto" , "Lead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_leadMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_leadMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_leadElectronHisto = m_histoFolder.make<TH2D>("leadElectronHisto" , "Lead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_leadElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_leadElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_lowEtaElectronHisto = m_histoFolder.make<TH2D>("lowEtaElectronHisto" , "Low eta Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowEtaElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_lowEtaElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_lowEtaMuonHisto = m_histoFolder.make<TH2D>("lowEtaMuonHisto" , "Low eta Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowEtaMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_lowEtaMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_highEtaElectronHisto = m_histoFolder.make<TH2D>("highEtaElectronHisto" , "High eta Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highEtaElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_highEtaElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_highEtaMuonHisto = m_histoFolder.make<TH2D>("highEtaMuonHisto" , "High eta Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highEtaMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_highEtaMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_lowR2MuonHisto = m_histoFolder.make<TH2D>("lowR2MuonHisto" , "Low R^2 Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowR2MuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_lowR2MuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_lowR2ElectronHisto = m_histoFolder.make<TH2D>("lowR2ElectronHisto" , "Low R^2 Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowR2ElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_lowR2ElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_highR2MuonHisto = m_histoFolder.make<TH2D>("highR2MuonHisto" , "High R^2 Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highR2MuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_highR2MuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_highR2ElectronHisto = m_histoFolder.make<TH2D>("highR2ElectronHisto" , "High R^2 Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highR2ElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_highR2ElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	//Matched Reco Histos
	
	//1D
	
	m_l2MuJJhisto = m_histoFolder.make<TH1D>("l2MuJJhisto" , "Matched Lepton + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	
	m_l2ElectronJJhisto = m_histoFolder.make<TH1D>("l2ElectronJJhisto" , "Matched Lepton + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	
	m_electronEtaHisto1 = m_histoFolder.make<TH1D>("electronEtaHisto1" , "lepton Eta Histo" , 100, -3, 3);
	m_electronEtaHisto1->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto1 = m_histoFolder.make<TH1D>("electronPhiHisto1" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_electronPhiHisto1->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1 = m_histoFolder.make<TH1D>("electronDPhiHisto1" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_electronDPhiHisto1->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1 = m_histoFolder.make<TH1D>("electronDRHisto1" , "lepton dR Histo" , 100, 0, 10);
	m_electronDRHisto1->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1 = m_histoFolder.make<TH1D>("electronPtHisto1" , "lepton Pt Histo" , 100, 0, 2000);
	m_electronPtHisto1->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_electronPtHisto1Scaled = m_histoFolder.make<TH1D>("electronPtHisto1Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_electronPtHisto1Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_electron1SphericityHisto = m_histoFolder.make<TH1D>("electron1SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_electron1SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_electronEtaHisto1WR = m_histoFolder.make<TH1D>("electronEtaHisto1WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_electronEtaHisto1WR->GetXaxis()-> SetTitle("eta");
	
	m_electronNMassHisto1 = m_histoFolder.make<TH1D>("electronNMassHisto1" , "lepton N Mass Histo" , 100, 0, 2000);
	m_electronNMassHisto1->GetXaxis()-> SetTitle("N mass (GeV)");
	
	
	
	
	
	m_muonEtaHisto1 = m_histoFolder.make<TH1D>("muonEtaHisto1" , "lepton Eta Histo" , 100, -3, 3);
	m_muonEtaHisto1->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto1 = m_histoFolder.make<TH1D>("muonPhiHisto1" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_muonPhiHisto1->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1 = m_histoFolder.make<TH1D>("muonDPhiHisto1" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_muonDPhiHisto1->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1 = m_histoFolder.make<TH1D>("muonDRHisto1" , "lepton dR Histo" , 100, 0, 10);
	m_muonDRHisto1->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1 = m_histoFolder.make<TH1D>("muonPtHisto1" , "lepton Pt Histo" , 100, 0, 2000);
	m_muonPtHisto1->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_muonPtHisto1Scaled = m_histoFolder.make<TH1D>("muonPtHisto1Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_muonPtHisto1Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_muon1SphericityHisto = m_histoFolder.make<TH1D>("muon1SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_muon1SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_muonEtaHisto1WR = m_histoFolder.make<TH1D>("muonEtaHisto1WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_muonEtaHisto1WR->GetXaxis()-> SetTitle("eta");
	
	m_muonNMassHisto1 = m_histoFolder.make<TH1D>("muonNMassHisto1" , "lepton N Mass Histo" , 100, 0, 2000);
	m_muonNMassHisto1->GetXaxis()-> SetTitle("N mass (GeV)");
	
	
	m_electronEtaHisto2 = m_histoFolder.make<TH1D>("electronEtaHisto2" , "lepton Eta Histo" , 100, -3, 3);
	m_electronEtaHisto2->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto2 = m_histoFolder.make<TH1D>("electronPhiHisto2" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_electronPhiHisto2->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2 = m_histoFolder.make<TH1D>("electronDPhiHisto2" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_electronDPhiHisto2->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2 = m_histoFolder.make<TH1D>("electronDRHisto2" , "lepton dR Histo" , 100, 0, 10);
	m_electronDRHisto2->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2 = m_histoFolder.make<TH1D>("electronPtHisto2" , "lepton Pt Histo" , 100, 0, 2000);
	m_electronPtHisto2->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_electronPtHisto2Scaled = m_histoFolder.make<TH1D>("electronPtHisto2Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_electronPtHisto2Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_electron2SphericityHisto = m_histoFolder.make<TH1D>("electron2SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_electron2SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_electronEtaHisto2WR = m_histoFolder.make<TH1D>("electronEtaHisto2WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_electronEtaHisto2WR->GetXaxis()-> SetTitle("eta");
	
	m_electronNMassHisto2 = m_histoFolder.make<TH1D>("electronNMassHisto2" , "lepton N Mass Histo" , 100, 0, 2000);
	m_electronNMassHisto2->GetXaxis()-> SetTitle("N mass (GeV)");
	
	
	m_muonEtaHisto2 = m_histoFolder.make<TH1D>("muonEtaHisto2" , "lepton Eta Histo" , 100, -3, 3);
	m_muonEtaHisto2->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto2 = m_histoFolder.make<TH1D>("muonPhiHisto2" , "lepton Phi Histo", 100, -3.5, 3.5);
	m_muonPhiHisto2->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2 = m_histoFolder.make<TH1D>("muonDPhiHisto2" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_muonDPhiHisto2->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2 = m_histoFolder.make<TH1D>("muonDRHisto2" , "lepton dR Histo" , 100, 0, 10);
	m_muonDRHisto2->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2 = m_histoFolder.make<TH1D>("muonPtHisto2" , "lepton Pt Histo" , 100, 0, 2000);
	m_muonPtHisto2->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_muonPtHisto2Scaled = m_histoFolder.make<TH1D>("muonPtHisto2Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_muonPtHisto2Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_muon2SphericityHisto = m_histoFolder.make<TH1D>("muon2SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_muon2SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_muonEtaHisto2WR = m_histoFolder.make<TH1D>("muonEtaHisto2WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_muonEtaHisto2WR->GetXaxis()-> SetTitle("eta");
	
	m_muonNMassHisto2 = m_histoFolder.make<TH1D>("muonNMassHisto2" , "lepton N Mass Histo" , 100, 0, 2000);
	m_muonNMassHisto2->GetXaxis()-> SetTitle("N mass (GeV)");
	
	m_electronPhiHisto1WR = m_histoFolder.make<TH1D>("electronPhiHisto1WR" , "lepton Phi Histo WR" , 100, -3.5, 3.5);
	m_electronPhiHisto1WR->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1WR = m_histoFolder.make<TH1D>("electronDPhiHisto1WR" , "lepton dPhi Histo WR" , 100, -6.5, 6.5);
	m_electronDPhiHisto1WR->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1WR = m_histoFolder.make<TH1D>("electronDRHisto1WR" , "lepton dR Histo WR" , 100, 0, 10);
	m_electronDRHisto1WR->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1WR = m_histoFolder.make<TH1D>("electronPtHisto1WR" , "lepton Pt Histo WR" , 100, 0, 2000);
	m_electronPtHisto1WR->GetXaxis()-> SetTitle("Pt (GeV)");
	
	
	
	m_muonPhiHisto1WR = m_histoFolder.make<TH1D>("muonPhiHisto1WR" , "lepton Phi Histo WR" , 100, -3.5, 3.5);
	m_muonPhiHisto1WR->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1WR = m_histoFolder.make<TH1D>("muonDPhiHisto1WR" , "lepton dPhi Histo WR" , 100, -6.5, 6.5);
	m_muonDPhiHisto1WR->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1WR = m_histoFolder.make<TH1D>("muonDRHisto1WR" , "lepton dR Histo WR" , 100, 0, 10);
	m_muonDRHisto1WR->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1WR = m_histoFolder.make<TH1D>("muonPtHisto1WR" , "lepton Pt Histo WR" , 100, 0, 2000);
	m_muonPtHisto1WR->GetXaxis()-> SetTitle("Pt (GeV)");
	
	
	
	m_electronPhiHisto2WR = m_histoFolder.make<TH1D>("electronPhiHisto2WR" , "lepton Phi Histo WR" , 100, -3.5, 3.5);
	m_electronPhiHisto2WR->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2WR = m_histoFolder.make<TH1D>("electronDPhiHisto2WR" , "lepton dPhi Histo WR" , 100, -6.5, 6.5);
	m_electronDPhiHisto2WR->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2WR = m_histoFolder.make<TH1D>("electronDRHisto2WR" , "lepton dR Histo WR" , 100, 0, 10);
	m_electronDRHisto2WR->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2WR = m_histoFolder.make<TH1D>("electronPtHisto2WR" , "lepton Pt Histo WR" , 100, 0, 2000);
	m_electronPtHisto2WR->GetXaxis()-> SetTitle("Pt (GeV)");
	
	
	m_muonPhiHisto2WR = m_histoFolder.make<TH1D>("muonPhiHisto2WR" , "lepton Phi Histo WR", 100, -3.5, 3.5);
	m_muonPhiHisto2WR->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2WR = m_histoFolder.make<TH1D>("muonDPhiHisto2WR" , "lepton dPhi Histo WR" , 100, -6.5, 6.5);
	m_muonDPhiHisto2WR->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2WR = m_histoFolder.make<TH1D>("muonDRHisto2WR" , "lepton dR Histo WR" , 100, 0, 10);
	m_muonDRHisto2WR->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2WR = m_histoFolder.make<TH1D>("muonPtHisto2WR" , "muon Pt Histo WR" , 100, 0, 2000);
	m_muonPtHisto2WR->GetXaxis()-> SetTitle("Pt (GeV)");
	
	
	m_electronEtaHisto1N = m_histoFolder.make<TH1D>("electronEtaHisto1N" , "lepton Eta Histo N" , 100, -3, 3);
	m_electronEtaHisto1N->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto1N = m_histoFolder.make<TH1D>("electronPhiHisto1N" , "lepton Phi Histo N" , 100, -3.5, 3.5);
	m_electronPhiHisto1N->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1N = m_histoFolder.make<TH1D>("electronDPhiHisto1N" , "lepton dPhi Histo N" , 100, -6.5, 6.5);
	m_electronDPhiHisto1N->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1N = m_histoFolder.make<TH1D>("electronDRHisto1N" , "lepton dR Histo N" , 100, 0, 10);
	m_electronDRHisto1N->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1N = m_histoFolder.make<TH1D>("electronPtHisto1N" , "lepton Pt Histo N" , 100, 0, 2000);
	m_electronPtHisto1N->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_muonEtaHisto1N = m_histoFolder.make<TH1D>("muonEtaHisto1N" , "lepton Eta Histo N" , 100, -3, 3);
	m_muonEtaHisto1N->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto1N = m_histoFolder.make<TH1D>("muonPhiHisto1N" , "lepton Phi Histo N" , 100, -3.5, 3.5);
	m_muonPhiHisto1N->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1N = m_histoFolder.make<TH1D>("muonDPhiHisto1N" , "lepton dPhi Histo N" , 100, -6.5, 6.5);
	m_muonDPhiHisto1N->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1N = m_histoFolder.make<TH1D>("muonDRHisto1N" , "lepton dR Histo N" , 100, 0, 10);
	m_muonDRHisto1N->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1N = m_histoFolder.make<TH1D>("muonPtHisto1N" , "lepton Pt Histo N" , 100, 0, 2000);
	m_muonPtHisto1N->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_electronEtaHisto2N = m_histoFolder.make<TH1D>("electronEtaHisto2N" , "lepton Eta Histo N" , 100, -3, 3);
	m_electronEtaHisto2N->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto2N = m_histoFolder.make<TH1D>("electronPhiHisto2N" , "lepton Phi Histo N" , 100, -3.5, 3.5);
	m_electronPhiHisto2N->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2N = m_histoFolder.make<TH1D>("electronDPhiHisto2N" , "lepton dPhi Histo N" , 100, -6.5, 6.5);
	m_electronDPhiHisto2N->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2N = m_histoFolder.make<TH1D>("electronDRHisto2N" , "lepton dR Histo N" , 100, 0, 10);
	m_electronDRHisto2N->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2N = m_histoFolder.make<TH1D>("electronPtHisto2N" , "lepton Pt Histo N" , 100, 0, 2000);
	m_electronPtHisto2N->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_muonEtaHisto2N = m_histoFolder.make<TH1D>("muonEtaHisto2N" , "lepton Eta Histo N" , 100, -3, 3);
	m_muonEtaHisto2N->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto2N = m_histoFolder.make<TH1D>("muonPhiHisto2N" , "lepton Phi Histo N", 100, -3.5, 3.5);
	m_muonPhiHisto2N->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2N = m_histoFolder.make<TH1D>("muonDPhiHisto2N" , "lepton dPhi Histo N" , 100, -6.5, 6.5);
	m_muonDPhiHisto2N->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2N = m_histoFolder.make<TH1D>("muonDRHisto2N" , "lepton dR Histo N" , 100, 0, 10);
	m_muonDRHisto2N->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2N = m_histoFolder.make<TH1D>("muonPtHisto2N" , "lepton Pt Histo N" , 100, 0, 2000);
	m_muonPtHisto2N->GetXaxis()-> SetTitle("Pt (GeV)");
	


	m_electronEtaHisto1L = m_histoFolder.make<TH1D>("electronEtaHisto1L" , "lepton Eta Histo L" , 100, -3, 3);
	m_electronEtaHisto1L->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto1L = m_histoFolder.make<TH1D>("electronPhiHisto1L" , "lepton Phi Histo L" , 100, -3.5, 3.5);
	m_electronPhiHisto1L->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1L = m_histoFolder.make<TH1D>("electronDPhiHisto1L" , "lepton dPhi Histo L" , 100, -6.5, 6.5);
	m_electronDPhiHisto1L->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1L = m_histoFolder.make<TH1D>("electronDRHisto1L" , "lepton dR Histo L" , 100, 0, 10);
	m_electronDRHisto1L->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1L = m_histoFolder.make<TH1D>("electronPtHisto1L" , "lepton Pt Histo L" , 100, 0, 2000);
	m_electronPtHisto1L->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_muonEtaHisto1L = m_histoFolder.make<TH1D>("muonEtaHisto1L" , "lepton Eta Histo L" , 100, -3, 3);
	m_muonEtaHisto1L->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto1L = m_histoFolder.make<TH1D>("muonPhiHisto1L" , "lepton Phi Histo L" , 100, -3.5, 3.5);
	m_muonPhiHisto1L->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1L = m_histoFolder.make<TH1D>("muonDPhiHisto1L" , "lepton dPhi Histo L" , 100, -6.5, 6.5);
	m_muonDPhiHisto1L->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1L = m_histoFolder.make<TH1D>("muonDRHisto1L" , "lepton dR Histo L" , 100, 0, 10);
	m_muonDRHisto1L->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1L = m_histoFolder.make<TH1D>("muonPtHisto1L" , "lepton Pt Histo L" , 100, 0, 2000);
	m_muonPtHisto1L->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_electronEtaHisto2L = m_histoFolder.make<TH1D>("electronEtaHisto2L" , "lepton Eta Histo L" , 100, -3, 3);
	m_electronEtaHisto2L->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto2L = m_histoFolder.make<TH1D>("electronPhiHisto2L" , "lepton Phi Histo L" , 100, -3.5, 3.5);
	m_electronPhiHisto2L->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2L = m_histoFolder.make<TH1D>("electronDPhiHisto2L" , "lepton dPhi Histo L" , 100, -6.5, 6.5);
	m_electronDPhiHisto2L->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2L = m_histoFolder.make<TH1D>("electronDRHisto2L" , "lepton dR Histo L" , 100, 0, 10);
	m_electronDRHisto2L->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2L = m_histoFolder.make<TH1D>("electronPtHisto2L" , "lepton Pt Histo L" , 100, 0, 2000);
	m_electronPtHisto2L->GetXaxis()-> SetTitle("Pt (GeV)");
	
	m_muonEtaHisto2L = m_histoFolder.make<TH1D>("muonEtaHisto2L" , "lepton Eta Histo L" , 100, -3, 3);
	m_muonEtaHisto2L->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto2L = m_histoFolder.make<TH1D>("muonPhiHisto2L" , "lepton Phi Histo L", 100, -3.5, 3.5);
	m_muonPhiHisto2L->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2L = m_histoFolder.make<TH1D>("muonDPhiHisto2L" , "lepton dPhi Histo L" , 100, -6.5, 6.5);
	m_muonDPhiHisto2L->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2L = m_histoFolder.make<TH1D>("muonDRHisto2L" , "lepton dR Histo L" , 100, 0, 10);
	m_muonDRHisto2L->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2L = m_histoFolder.make<TH1D>("muonPtHisto2L" , "lepton Pt Histo L" , 100, 0, 2000);
	m_muonPtHisto2L->GetXaxis()-> SetTitle("Pt (GeV)");
	
	
	//2D
	
	m_matchedMuonHisto = m_histoFolder.make<TH2D>("matchedMuonHisto" , "Matched Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_matchedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_matchedElectronHisto = m_histoFolder.make<TH2D>("matchedElectronHisto" , "Matched Lepton" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_matchedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_matchedMuon1MassHisto = m_histoFolder.make<TH2D>("matchedMuon1MassHisto" , "Matched Lepton 1 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedMuon1MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_matchedMuon1MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_matchedElectron1MassHisto = m_histoFolder.make<TH2D>("matchedElectron1MassHisto" , "Matched Lepton 1 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedElectron1MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_matchedElectron1MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_matchedMuon2MassHisto = m_histoFolder.make<TH2D>("matchedMuon2MassHisto" , "Matched Lepton 2 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedMuon2MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_matchedMuon2MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_matchedElectron2MassHisto = m_histoFolder.make<TH2D>("matchedElectron2MassHisto" , "Matched Lepton 2 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedElectron2MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_matchedElectron2MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	
	//NN Histos
	
	//1D
	
	
	//2D
	
	m_NNResolvedMuonHisto = m_histoFolder.make<TH2D>("NNResolvedMuonHisto" , "Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_NNResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_NNResolvedElectronHisto = m_histoFolder.make<TH2D>("NNResolvedElectronHisto" , "Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_NNResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_notNNResolvedMuonHisto = m_histoFolder.make<TH2D>("notNNResolvedMuonHisto" , "Not Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_notNNResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_notNNResolvedElectronHisto = m_histoFolder.make<TH2D>("notNNResolvedElectronHisto" , "Not Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_notNNResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	

	m_NNSuperResolvedMuonHisto = m_histoFolder.make<TH2D>("NNSuperResolvedMuonHisto" , "Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNSuperResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_NNSuperResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_NNSuperResolvedElectronHisto = m_histoFolder.make<TH2D>("NNSuperResolvedElectronHisto" , "Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNSuperResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_NNSuperResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_notNNSuperResolvedMuonHisto = m_histoFolder.make<TH2D>("notNNSuperResolvedMuonHisto" , "Not Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNSuperResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_notNNSuperResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");
	
	m_notNNSuperResolvedElectronHisto = m_histoFolder.make<TH2D>("notNNSuperResolvedElectronHisto" , "Not Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNSuperResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet (GeV)");
	m_notNNSuperResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet (GeV)");

}

//General histogram filling
void eventHistos::fill(eventBits& event) {

	m_countHisto->Fill("count", event.count);
	if(event.leadLeptonType==11){
		m_leadEPtHisto->Fill(event.leadLeptonPt, event.eventWeight);
	} else if(event.leadLeptonType==13){
		m_leadMPtHisto->Fill(event.leadLeptonPt, event.eventWeight);
	} else if(event.leadLeptonType==15){
		m_leadTPtHisto->Fill(event.leadLeptonPt, event.eventWeight);
	}
	if(event.subleadLeptonType==11){
		m_subleadEPtHisto->Fill(event.subleadLeptonPt, event.eventWeight);
	} else if(event.subleadLeptonType==13){
		m_subleadMPtHisto->Fill(event.subleadLeptonPt, event.eventWeight);
	} else if(event.subleadLeptonType==15){
		m_subleadTPtHisto->Fill(event.subleadLeptonPt, event.eventWeight);
	}
	if(event.mixedLeptons){ // mixed leptons
		m_leptonHisto->Fill("one Electron, one Muon", event.eventWeight);
		if(event.failedGenPtEta){
			m_failGenleptonHisto->Fill("one Electron, one Muon", event.eventWeight);
		} else if(event.mixedGen){
			m_mixGenleptonHisto->Fill("one Electron, one Muon", event.eventWeight);
		} else if(event.electronGen) {
			m_electronGenleptonHisto->Fill("one Electron, one Muon", event.eventWeight);
		} else if(event.muonGen) {
			m_muonGenleptonHisto->Fill("one Electron, one Muon", event.eventWeight);	
		} else if(event.tauGen) {
			m_tauGenleptonHisto->Fill("one Electron, one Muon", event.eventWeight);
		}
	} else if(event.extraLeptons){
		m_leptonHisto->Fill("Nothing, extra leptons", event.eventWeight);
		if(event.failedGenPtEta){
			m_failGenleptonHisto->Fill("Nothing, extra leptons", event.eventWeight);
		} else if(event.mixedGen){
			m_mixGenleptonHisto->Fill("Nothing, extra leptons", event.eventWeight);
		} else if(event.electronGen) {
			m_electronGenleptonHisto->Fill("Nothing, extra leptons", event.eventWeight);
		} else if(event.muonGen) {
			m_muonGenleptonHisto->Fill("Nothing, extra leptons", event.eventWeight);
		} else if(event.tauGen) {
			m_tauGenleptonHisto->Fill("Nothing, extra leptons", event.eventWeight);
		}
	} else { // two electrons or two muons
		if(event.passedElectronReco){ // pass Reco
			m_leptonHisto->Fill("two Electrons", event.eventWeight);
			if(event.sameSignElectrons){
				m_ElElMass_sameSign->Fill(event.leadElectronsubElectronRecoMass, event.eventWeight);
			}else{
				m_ElElMass_oppoSign->Fill(event.leadElectronsubElectronRecoMass, event.eventWeight);
			}
			if(event.failedGenPtEta){
				m_failGenleptonHisto->Fill("two Electrons", event.eventWeight);
			} else if(event.mixedGen){
				m_mixGenleptonHisto->Fill("two Electrons", event.eventWeight);
			} else if(event.electronGen) {
				m_electronGenleptonHisto->Fill("two Electrons", event.eventWeight);
			} else if(event.muonGen) {
				m_muonGenleptonHisto->Fill("two Electrons", event.eventWeight);
			} else if(event.tauGen) {
				m_tauGenleptonHisto->Fill("two Electrons", event.eventWeight);
			}
			if(event.nMinusOneFailElectron.size()==0){ // pass Cuts
				fillElectron(event);
				fillNMinusOnePassElectron(event);
			} else { // fail cuts
				m_leptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				if(event.failedGenPtEta){
					m_failGenleptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				} else if(event.mixedGen){
					m_mixGenleptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				} else if(event.electronGen) {
					m_electronGenleptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				} else if(event.muonGen) {
					m_muonGenleptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				} else if(event.tauGen) {
					m_tauGenleptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				}
				if(event.nMinusOneFailElectron.size()==1){ // fail one cut
					fillNMinusOneFailElectron(event);
				}
			}
		} 
		if(event.passedMuonReco) {
			m_leptonHisto->Fill("two Muons", event.eventWeight);
			if(event.failedGenPtEta){
				m_failGenleptonHisto->Fill("two Muons", event.eventWeight);
			} else if(event.mixedGen){
				m_mixGenleptonHisto->Fill("two Muons", event.eventWeight);
			} else if(event.electronGen) {
				m_electronGenleptonHisto->Fill("two Muons", event.eventWeight);
			} else if(event.muonGen) {
				m_muonGenleptonHisto->Fill("two Muons", event.eventWeight);
			} else if(event.tauGen) {
				m_tauGenleptonHisto->Fill("two Muons", event.eventWeight);
			}
			if(event.nMinusOneFailMuon.size()==0){ // pass Cuts
				fillMuon(event);
				fillNMinusOnePassMuon(event);
			} else { // fail cuts
				m_leptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				if(event.failedGenPtEta){
					m_failGenleptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				} else if(event.mixedGen){
					m_mixGenleptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				} else if(event.electronGen) {
					m_electronGenleptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				} else if(event.muonGen) {
					m_muonGenleptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				} else if(event.tauGen) {
					m_tauGenleptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				}
				if(event.nMinusOneFailMuon.size()==1){ // fail one cut
					fillNMinusOneFailMuon(event);
				}
			}
		}
		if(event.passedElectronReco && event.passedMuonReco){
			m_leptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
			if(event.failedGenPtEta){
				m_failGenleptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
			} else if(event.mixedGen){
				m_mixGenleptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
			} else if(event.electronGen) {
				m_electronGenleptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
			} else if(event.muonGen) {
				m_muonGenleptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
			} else if(event.tauGen) {
				m_tauGenleptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
			}
		} else if(!event.passedElectronReco && !event.passedMuonReco){
			if(event.badJets){
				m_leptonHisto->Fill("Nothing, failed Recos bad jets", event.eventWeight);
				if(event.failedGenPtEta){
					m_failGenleptonHisto->Fill("Nothing, failed Recos bad jets", event.eventWeight);
				} else if(event.mixedGen){
					m_mixGenleptonHisto->Fill("Nothing, failed Recos bad jets", event.eventWeight);
				} else if(event.electronGen) {
					m_electronGenleptonHisto->Fill("Nothing, failed Recos bad jets", event.eventWeight);
				} else if(event.muonGen) {
					m_muonGenleptonHisto->Fill("Nothing, failed Recos bad jets", event.eventWeight);
				} else if(event.tauGen) {
					m_tauGenleptonHisto->Fill("Nothing, failed Recos bad jets", event.eventWeight);
				}
			}
			if(event.oneLepton){
				m_leptonHisto->Fill("Nothing, failed Recos one lepton", event.eventWeight);
				if(event.failedGenPtEta){
					m_failGenleptonHisto->Fill("Nothing, failed Recos one lepton", event.eventWeight);
				} else if(event.mixedGen){
					m_mixGenleptonHisto->Fill("Nothing, failed Recos one lepton", event.eventWeight);
				} else if(event.electronGen) {
					m_electronGenleptonHisto->Fill("Nothing, failed Recos one lepton", event.eventWeight);
				} else if(event.muonGen) {
					m_muonGenleptonHisto->Fill("Nothing, failed Recos one lepton", event.eventWeight);
				} else if(event.tauGen) {
					m_tauGenleptonHisto->Fill("Nothing, failed Recos one lepton", event.eventWeight);
				}	
			}
			if(!event.badJets && !event.oneLepton){
				m_leptonHisto->Fill("Nothing, failed Recos other", event.eventWeight);
				if(event.failedGenPtEta){
					m_failGenleptonHisto->Fill("Nothing, failed Recos other", event.eventWeight);
				} else if(event.mixedGen){
					m_mixGenleptonHisto->Fill("Nothing, failed Recos other", event.eventWeight);
				} else if(event.electronGen) {
					m_electronGenleptonHisto->Fill("Nothing, failed Recos other", event.eventWeight);
				} else if(event.muonGen) {
					m_muonGenleptonHisto->Fill("Nothing, failed Recos other", event.eventWeight);
				} else if(event.tauGen) {
					m_tauGenleptonHisto->Fill("Nothing, failed Recos other", event.eventWeight);
				}
			}
		}
		if(event.passedMuonReco && event.passedElectronReco && event.nMinusOneFailMuon.size()==0 && event.nMinusOneFailElectron.size()==0) { 
			m_leptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			if(event.failedGenPtEta){
				m_failGenleptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			} else if(event.mixedGen){
				m_mixGenleptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			} else if(event.electronGen) {
				m_electronGenleptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			} else if(event.muonGen) {
				m_muonGenleptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			} else if(event.tauGen) {
				m_tauGenleptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			}
		}
	}
	if(event.passedMuonReco && event.nMinusOneFailMuon.size()==0){
		m_massData->Fill();
	} else if (event.passedElectronReco && event.nMinusOneFailElectron.size()==0){
		m_massData->Fill();
	}
}

//Fill muon specific histograms
void eventHistos::fillMuon(eventBits& event){
	double weight = event.eventWeight;

	m_subMuJJhisto->Fill(event.subMuonleadJsubJRecoMass, weight);
	m_l2MuJJhisto->Fill(event.matchedMuonleadJsubJRecoMass, weight);
	m_matchedMuonHisto->Fill(event.matchedMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	m_subLeadMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	m_leadMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	if(!event.passedElectronReco){
		m_leptonHisto->Fill("passed Cuts, Muon", weight);
		if(event.failedGenPtEta){
			m_failGenleptonHisto->Fill("passed Cuts, Muon", weight);
		} else if(event.mixedGen){
			m_mixGenleptonHisto->Fill("passed Cuts, Muon", weight);
		} else if(event.electronGen) {
			m_electronGenleptonHisto->Fill("passed Cuts, Muon", weight);
		} else if(event.muonGen) {
			m_muonGenleptonHisto->Fill("passed Cuts, Muon", weight);
		} else if(event.tauGen) {
			m_tauGenleptonHisto->Fill("passed Cuts, Muon", weight);
		}
	}
	
	m_jetjetMassHisto->Fill(event.leadJsubJRecoMass, weight);
	m_matchedMuon1MassHisto->Fill(event.muon1RecoMass, event.fullRecoMassMuon, weight);
	m_matchedMuon2MassHisto->Fill(event.muon2RecoMass, event.fullRecoMassMuon, weight);

	
	m_muonEtaHisto1->Fill(event.match1MuonEta, weight);
	m_muonPhiHisto1->Fill(event.match1MuonPhi, weight);
	m_muonDPhiHisto1->Fill(event.match1MuonDPhi, weight);
	m_muonDRHisto1->Fill(event.match1MuonDR, weight);
	m_muonPtHisto1->Fill(event.match1MuonPt, weight);
	m_muonPtHisto1Scaled->Fill(event.match1MuonPt/event.WRMass, weight);
	m_muonNMassHisto1->Fill(event.muon1RecoMass,weight);
	
	m_muonEtaHisto2->Fill(event.match2MuonEta, weight);
	m_muonPhiHisto2->Fill(event.match2MuonPhi, weight);
	m_muonDPhiHisto2->Fill(event.match2MuonDPhi, weight);
	m_muonDRHisto2->Fill(event.match2MuonDR, weight);
	m_muonPtHisto2->Fill(event.match2MuonPt, weight);
	m_muonPtHisto2Scaled->Fill(event.match2MuonPt/event.WRMass, weight);
	m_muonNMassHisto2->Fill(event.muon2RecoMass,weight);
	
	m_muonEtaHisto1WR->Fill(event.match1MuonEtaWR, weight);
	m_muonPhiHisto1WR->Fill(event.match1MuonPhiWR, weight);
	m_muonDPhiHisto1WR->Fill(event.match1MuonDPhiWR, weight);
	m_muonDRHisto1WR->Fill(event.match1MuonDRWR, weight);
	m_muonPtHisto1WR->Fill(event.match1MuonPtWR, weight);
	
	m_muonEtaHisto2WR->Fill(event.match2MuonEtaWR, weight);
	m_muonPhiHisto2WR->Fill(event.match2MuonPhiWR, weight);
	m_muonDPhiHisto2WR->Fill(event.match2MuonDPhiWR, weight);
	m_muonDRHisto2WR->Fill(event.match2MuonDRWR, weight);
	m_muonPtHisto2WR->Fill(event.match2MuonPtWR, weight);
	
	m_muonEtaHisto1N->Fill(event.match1MuonEtaJJL1, weight);
	m_muonPhiHisto1N->Fill(event.match1MuonPhiJJL1, weight);
	m_muonDPhiHisto1N->Fill(event.match1MuonDPhiJJL1, weight);
	m_muonDRHisto1N->Fill(event.match1MuonDRJJL1, weight);
	m_muonPtHisto1N->Fill(event.match1MuonPtJJL1, weight);
	
	m_muonEtaHisto2N->Fill(event.match2MuonEtaJJL2, weight);
	m_muonPhiHisto2N->Fill(event.match2MuonPhiJJL2, weight);
	m_muonDPhiHisto2N->Fill(event.match2MuonDPhiJJL2, weight);
	m_muonDRHisto2N->Fill(event.match2MuonDRJJL2, weight);
	m_muonPtHisto2N->Fill(event.match2MuonPtJJL2, weight);
	
	m_muonEtaHisto1L->Fill(event.match1MuonEtaL1, weight);
	m_muonPhiHisto1L->Fill(event.match1MuonPhiL1, weight);
	m_muonDPhiHisto1L->Fill(event.match1MuonDPhiL1, weight);
	m_muonDRHisto1L->Fill(event.match1MuonDRL1, weight);
	m_muonPtHisto1L->Fill(event.match1MuonPtL1, weight);
	
	m_muonEtaHisto2L->Fill(event.match2MuonEtaL2, weight);
	m_muonPhiHisto2L->Fill(event.match2MuonPhiL2, weight);
	m_muonDPhiHisto2L->Fill(event.match2MuonDPhiL2, weight);
	m_muonDRHisto2L->Fill(event.match2MuonDRL2, weight);
	m_muonPtHisto2L->Fill(event.match2MuonPtL2, weight);
	
	m_muon1SphericityHisto->Fill(event.sphericityMuon1, weight);
	m_muon2SphericityHisto->Fill(event.sphericityMuon2, weight);
	
	if(event.nnResolvedPickedLeadMuon){
		m_NNResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	
		WRMass = event.fullRecoMassMuon;
		resolvedNNMass = event.leadMuonleadJsubJRecoMass;
		treeWeight = weight;
		correctNMass = event.matchedMuonleadJsubJRecoMass;
		incorrectNMass = event.muon1RecoMass;
		leadNMass = event.leadMuonleadJsubJRecoMass;
		subNMass = event.subMuonleadJsubJRecoMass;

	} else if(event.nnResolvedPickedSubLeadMuon) {		
		m_notNNResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		

		WRMass = event.fullRecoMassMuon;
		resolvedNNMass = event.subMuonleadJsubJRecoMass;
		treeWeight = weight;
		correctNMass = event.matchedMuonleadJsubJRecoMass;
		incorrectNMass = event.muon1RecoMass;
		leadNMass = event.leadMuonleadJsubJRecoMass;
		subNMass = event.subMuonleadJsubJRecoMass;
		

	}
	if(event.nnSuperResolvedPickedLeadMuon){
		m_NNSuperResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNSuperResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	
		superResolvedNNMass = event.leadMuonleadJsubJRecoMass;

	
	} else if(event.nnSuperResolvedPickedSubLeadMuon) {		
		m_notNNSuperResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNSuperResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	
		superResolvedNNMass = event.subMuonleadJsubJRecoMass;
	} 
	
	if(abs(event.leadRecoMuonEta)<abs(event.subRecoMuonEta)){
		m_lowEtaMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_highEtaMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else {
		m_highEtaMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_lowEtaMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	if(event.leadMuonJJRecodr2 < event.subleadMuonJJRecodr2){
		m_lowR2MuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_highR2MuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else {
		m_highR2MuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_lowR2MuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}	
}

//Fill electron specific histograms
void eventHistos::fillElectron(eventBits& event){
	double weight = event.eventWeight;
	
	m_subElectronJJhisto->Fill(event.subElectronleadJsubJRecoMass, weight);
	m_l2ElectronJJhisto->Fill(event.matchedElectronleadJsubJRecoMass, weight);
	m_matchedElectronHisto->Fill(event.matchedElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	m_subLeadElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	m_leadElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	
	if(!event.passedMuonReco){
		m_leptonHisto->Fill("passed Cuts, Electron", weight);
		if(event.failedGenPtEta){
			m_failGenleptonHisto->Fill("passed Cuts, Electron", weight);
		} else if(event.mixedGen){
			m_mixGenleptonHisto->Fill("passed Cuts, Electron", weight);
		} else if(event.electronGen) {
			m_electronGenleptonHisto->Fill("passed Cuts, Electron", weight);
		} else if(event.muonGen) {
			m_muonGenleptonHisto->Fill("passed Cuts, Electron", weight);
		} else if(event.tauGen) {
			m_tauGenleptonHisto->Fill("passed Cuts, Electron", weight);
		}
	}
	
	m_jetjetMassHisto->Fill(event.leadJsubJRecoMass, weight);
	m_matchedElectron1MassHisto->Fill(event.electron1RecoMass, event.fullRecoMassElectron, weight);
	m_matchedElectron2MassHisto->Fill(event.electron2RecoMass, event.fullRecoMassElectron, weight);
	
	
	m_electronEtaHisto1->Fill(event.match1ElectronEta, weight);
	m_electronPhiHisto1->Fill(event.match1ElectronPhi, weight);
	m_electronDPhiHisto1->Fill(event.match1ElectronDPhi, weight);
	m_electronDRHisto1->Fill(event.match1ElectronDR, weight);
	m_electronPtHisto1->Fill(event.match1ElectronPt, weight);
	m_electronPtHisto1Scaled->Fill(event.match1ElectronPt/event.WRMass, weight);
	m_electronNMassHisto1->Fill(event.electron1RecoMass,weight);
	
	m_electronEtaHisto2->Fill(event.match2ElectronEta, weight);
	m_electronPhiHisto2->Fill(event.match2ElectronPhi, weight);
	m_electronDPhiHisto2->Fill(event.match2ElectronDPhi, weight);
	m_electronDRHisto2->Fill(event.match2ElectronDR, weight);
	m_electronPtHisto2->Fill(event.match2ElectronPt, weight);
	m_electronPtHisto2Scaled->Fill(event.match2ElectronPt/event.WRMass, weight);
	m_electronNMassHisto2->Fill(event.electron2RecoMass,weight);
	
	m_electronEtaHisto1WR->Fill(event.match1ElectronEtaWR, weight);
	m_electronPhiHisto1WR->Fill(event.match1ElectronPhiWR, weight);
	m_electronDPhiHisto1WR->Fill(event.match1ElectronDPhiWR, weight);
	m_electronDRHisto1WR->Fill(event.match1ElectronDRWR, weight);
	m_electronPtHisto1WR->Fill(event.match1ElectronPtWR, weight);
	
	m_electronEtaHisto2WR->Fill(event.match2ElectronEtaWR, weight);
	m_electronPhiHisto2WR->Fill(event.match2ElectronPhiWR, weight);
	m_electronDPhiHisto2WR->Fill(event.match2ElectronDPhiWR, weight);
	m_electronDRHisto2WR->Fill(event.match2ElectronDRWR, weight);
	m_electronPtHisto2WR->Fill(event.match2ElectronPtWR, weight);
	
	m_electronEtaHisto1N->Fill(event.match1ElectronEtaJJL1, weight);
	m_electronPhiHisto1N->Fill(event.match1ElectronPhiJJL1, weight);
	m_electronDPhiHisto1N->Fill(event.match1ElectronDPhiJJL1, weight);
	m_electronDRHisto1N->Fill(event.match1ElectronDRJJL1, weight);
	m_electronPtHisto1N->Fill(event.match1ElectronPtJJL1, weight);
	
	m_electronEtaHisto2N->Fill(event.match2ElectronEtaJJL2, weight);
	m_electronPhiHisto2N->Fill(event.match2ElectronPhiJJL2, weight);
	m_electronDPhiHisto2N->Fill(event.match2ElectronDPhiJJL2, weight);
	m_electronDRHisto2N->Fill(event.match2ElectronDRJJL2, weight);
	m_electronPtHisto2N->Fill(event.match2ElectronPtJJL2, weight);
	
	m_electronEtaHisto1L->Fill(event.match1ElectronEtaL1, weight);
	m_electronPhiHisto1L->Fill(event.match1ElectronPhiL1, weight);
	m_electronDPhiHisto1L->Fill(event.match1ElectronDPhiL1, weight);
	m_electronDRHisto1L->Fill(event.match1ElectronDRL1, weight);
	m_electronPtHisto1L->Fill(event.match1ElectronPtL1, weight);
	
	m_electronEtaHisto2L->Fill(event.match2ElectronEtaL2, weight);
	m_electronPhiHisto2L->Fill(event.match2ElectronPhiL2, weight);
	m_electronDPhiHisto2L->Fill(event.match2ElectronDPhiL2, weight);
	m_electronDRHisto2L->Fill(event.match2ElectronDRL2, weight);
	m_electronPtHisto2L->Fill(event.match2ElectronPtL2, weight);
	
	m_electron1SphericityHisto->Fill(event.sphericityElectron1, weight);
	m_electron2SphericityHisto->Fill(event.sphericityElectron2, weight);

	if(event.nnResolvedPickedLeadElectron){
		m_NNResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		
		WRMass = event.fullRecoMassElectron;
		resolvedNNMass = event.leadElectronleadJsubJRecoMass;
		treeWeight = weight;
		correctNMass = event.matchedElectronleadJsubJRecoMass;
		incorrectNMass = event.electron1RecoMass;
		leadNMass = event.leadElectronleadJsubJRecoMass;
		subNMass = event.subElectronleadJsubJRecoMass;

	} else if(event.nnResolvedPickedSubLeadElectron) {		
		m_notNNResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		
		
		WRMass = event.fullRecoMassElectron;
		resolvedNNMass = event.subElectronleadJsubJRecoMass;
		treeWeight = weight;
		correctNMass = event.matchedElectronleadJsubJRecoMass;
		incorrectNMass = event.electron1RecoMass;
		leadNMass = event.leadElectronleadJsubJRecoMass;
		subNMass = event.subElectronleadJsubJRecoMass;
	}

	if(event.nnSuperResolvedPickedLeadElectron){
		m_NNSuperResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNSuperResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		
		superResolvedNNMass = event.leadElectronleadJsubJRecoMass;
		
	} else if(event.nnSuperResolvedPickedSubLeadElectron) {		
		m_notNNSuperResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNSuperResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	
		superResolvedNNMass = event.subElectronleadJsubJRecoMass;
	} 


	if(abs(event.leadRecoElectronEta)<abs(event.subRecoElectronEta)){
		m_lowEtaElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_highEtaElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);		
	} else {
		m_highEtaElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_lowEtaElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	}
	if(event.leadElectronJJRecodr2<event.subleadElectronJJRecodr2){
		m_lowR2ElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_highR2ElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else {
		m_highR2ElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_lowR2ElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	}
}

//Fill nMinusOne histos if electron fails
void eventHistos::fillNMinusOneFailElectron(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOneFailElectron.begin(); s != event.nMinusOneFailElectron.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneElectronHisto->Fill((*s).c_str(),weight); 
	}
}

//Fill nMinusOne histos if electron passes
void eventHistos::fillNMinusOnePassElectron(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOnePassElectron.begin(); s != event.nMinusOnePassElectron.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneElectronHisto->Fill((*s).c_str(),weight); 
	}
}

//Fill nMinusOne histos if a muon fails
void eventHistos::fillNMinusOneFailMuon(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOneFailMuon.begin(); s != event.nMinusOneFailMuon.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneMuonHisto->Fill((*s).c_str(),weight); 
	}
}

//Fill the n Minus One histos if a muon passes
void eventHistos::fillNMinusOnePassMuon(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOnePassMuon.begin(); s != event.nMinusOnePassMuon.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneMuonHisto->Fill((*s).c_str(),weight); 
	}
}
	
