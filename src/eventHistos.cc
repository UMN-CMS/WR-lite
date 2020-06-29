//C++ CLASSES
#include <iostream>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
////LOCAL CLASSES
#include "ExoAnalysis/WR-lite/interface/eventBits.h"
#include "ExoAnalysis/WR-lite/interface/eventHistos.h"

#include "TH1D.h"



eventHistos::eventHistos () {}
  
void eventHistos::book(TFileDirectory histoFolder) {

	m_histoFolder = histoFolder;


	m_subMuJJhisto = m_histoFolder.make<TH1D>("subMuJJhisto" , "Sublead Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_l2MuJJhisto = m_histoFolder.make<TH1D>("l2MuJJhisto" , "Matched Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	
	m_jetjetMassHisto = m_histoFolder.make<TH1D>("jetjetMassHisto" , "Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_matchedL1MassHisto = m_histoFolder.make<TH1D>("matchedL1MassHisto" , "Matched L1 lepton Mass" , 50 , 0 , 4000 );
	m_matchedL2MassHisto = m_histoFolder.make<TH1D>("matchedL2MassHisto" , "Matched L2 lepton Mass" , 50 , 0 , 4000 );
	
	m_subElectronJJhisto = m_histoFolder.make<TH1D>("subElectronJJhisto" , "Sublead Electron + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_l2ElectronJJhisto = m_histoFolder.make<TH1D>("l2ElectronJJhisto" , "Matched Electron + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );

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
	
	m_leptonHisto = m_histoFolder.make<TH1D>("leptonHisto", "lepton Distribution" , 10, 1, 10);
	
	m_leptonHisto->GetXaxis()->SetBinLabel(1,"two Electrons");
	m_leptonHisto->GetXaxis()->SetBinLabel(2,"two Muons");
	m_leptonHisto->GetXaxis()->SetBinLabel(3,"one Electron, one Muon");
	m_leptonHisto->GetXaxis()->SetBinLabel(4,"two Electrons and two Muons");
	m_leptonHisto->GetXaxis()->SetBinLabel(5,"Nothing");
	m_leptonHisto->GetXaxis()->SetBinLabel(6,"failed Cuts, Electron");
	m_leptonHisto->GetXaxis()->SetBinLabel(7,"failed Cuts, Muon");
	m_leptonHisto->GetXaxis()->SetBinLabel(8,"passed Cuts, Electron");
	m_leptonHisto->GetXaxis()->SetBinLabel(9,"passed Cuts, Muon");
	m_leptonHisto->GetXaxis()->SetBinLabel(10,"passed Cuts, Both");
	
	m_countHisto = m_histoFolder.make<TH1D>("countHisto", "counts" , 1, 1, 1);
	m_countHisto->GetXaxis()->SetBinLabel(1,"count");
	
	
	m_correctNNHisto = m_histoFolder.make<TH1D>("correctNNHisto", "Fraction Correct NN" , 6, 1, 6);
	m_correctNNHisto->GetXaxis()->SetBinLabel(1,"correct");
	m_correctNNHisto->GetXaxis()->SetBinLabel(2,"incorrect");
	m_correctNNHisto->GetXaxis()->SetBinLabel(3,"counted out cuts");
	m_correctNNHisto->GetXaxis()->SetBinLabel(4,"correct and passed cuts");
	m_correctNNHisto->GetXaxis()->SetBinLabel(5,"incorrect and passed cuts");
	m_correctNNHisto->GetXaxis()->SetBinLabel(6,"counted in cuts");
	
	
	m_lepton2Histo = m_histoFolder.make<TH2D>("lepton2Histo" , "Lepton 2" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lepton2Histo->GetXaxis()-> SetTitle("lepton + quark + quark");
	m_lepton2Histo->GetYaxis()-> SetTitle("lepton + lepton + quark + quark");
	
	m_matchedMuonHisto = m_histoFolder.make<TH2D>("matchedMuonHisto" , "Matched Muon" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_matchedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_matchedElectronHisto = m_histoFolder.make<TH2D>("matchedElectronHisto" , "Matched Electron" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_matchedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_matchedMuon1MassHisto = m_histoFolder.make<TH2D>("matchedMuon1MassHisto" , "Matched Muon 1 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedMuon1MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_matchedMuon1MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_matchedElectron1MassHisto = m_histoFolder.make<TH2D>("matchedElectron1MassHisto" , "Matched Electron 1 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedElectron1MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_matchedElectron1MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_matchedMuon2MassHisto = m_histoFolder.make<TH2D>("matchedMuon2MassHisto" , "Matched Muon 2 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedMuon2MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_matchedMuon2MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_matchedElectron2MassHisto = m_histoFolder.make<TH2D>("matchedElectron2MassHisto" , "Matched Electron 2 Mass" , 100, 0, 6000, 100 , 0 , 6000 );
	m_matchedElectron2MassHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_matchedElectron2MassHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_subLeadMuonHisto = m_histoFolder.make<TH2D>("subLeadMuonHisto" , "Sublead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_subLeadMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_subLeadMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_subLeadElectronHisto = m_histoFolder.make<TH2D>("subLeadElectronHisto" , "Sublead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_subLeadElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_subLeadElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_leadMuonHisto = m_histoFolder.make<TH2D>("leadMuonHisto" , "Lead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_leadMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_leadMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_leadElectronHisto = m_histoFolder.make<TH2D>("leadElectronHisto" , "Lead Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_leadElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_leadElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_lowEtaElectronHisto = m_histoFolder.make<TH2D>("lowEtaElectronHisto" , "Low eta Electron" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowEtaElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_lowEtaElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_lowEtaMuonHisto = m_histoFolder.make<TH2D>("lowEtaMuonHisto" , "Low eta Muon" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowEtaMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_lowEtaMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_highEtaElectronHisto = m_histoFolder.make<TH2D>("highEtaElectronHisto" , "High eta Electron" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highEtaElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_highEtaElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_highEtaMuonHisto = m_histoFolder.make<TH2D>("highEtaMuonHisto" , "High eta Muon" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highEtaMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_highEtaMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_lowR2MuonHisto = m_histoFolder.make<TH2D>("lowR2MuonHisto" , "Low R^2 Muon" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowR2MuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_lowR2MuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_lowR2ElectronHisto = m_histoFolder.make<TH2D>("lowR2ElectronHisto" , "Low R^2 Electron" , 100, 0, 6000, 100 , 0 , 6000 );
	m_lowR2ElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_lowR2ElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_highR2MuonHisto = m_histoFolder.make<TH2D>("highR2MuonHisto" , "High R^2 Muon" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highR2MuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_highR2MuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_highR2ElectronHisto = m_histoFolder.make<TH2D>("highR2ElectronHisto" , "High R^2 Electron" , 100, 0, 6000, 100 , 0 , 6000 );
	m_highR2ElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_highR2ElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	
	
	m_NNResolvedMuonHisto = m_histoFolder.make<TH2D>("NNResolvedMuonHisto" , "Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNResolvedElectronHisto = m_histoFolder.make<TH2D>("NNResolvedElectronHisto" , "Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNResolvedMuonHisto = m_histoFolder.make<TH2D>("notNNResolvedMuonHisto" , "Not Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNResolvedElectronHisto = m_histoFolder.make<TH2D>("notNNResolvedElectronHisto" , "Not Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	
	m_NNLowMidMuonHisto = m_histoFolder.make<TH2D>("NNLowMidMuonHisto" , "Low Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNLowMidMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNLowMidMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNLowMidElectronHisto = m_histoFolder.make<TH2D>("NNLowMidElectronHisto" , "Low Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNLowMidElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNLowMidElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNLowMidMuonHisto = m_histoFolder.make<TH2D>("notNNLowMidMuonHisto" , "Not Low Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNLowMidMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNLowMidMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNLowMidElectronHisto = m_histoFolder.make<TH2D>("notNNLowMidElectronHisto" , "Not Low Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNLowMidElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNLowMidElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNMidMuonHisto = m_histoFolder.make<TH2D>("NNMidMuonHisto" , "Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNMidMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNMidMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNMidElectronHisto = m_histoFolder.make<TH2D>("NNMidElectronHisto" , "Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNMidElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNMidElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNMidMuonHisto = m_histoFolder.make<TH2D>("notNNMidMuonHisto" , "Not Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNMidMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNMidMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNMidElectronHisto = m_histoFolder.make<TH2D>("notNNMidElectronHisto" , "Not Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNMidElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNMidElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	
	m_NNHighMidMuonHisto = m_histoFolder.make<TH2D>("NNHighMidMuonHisto" , "High Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNHighMidMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNHighMidMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNHighMidElectronHisto = m_histoFolder.make<TH2D>("NNHighMidElectronHisto" , "High Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNHighMidElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNHighMidElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNHighMidMuonHisto = m_histoFolder.make<TH2D>("notNNHighMidMuonHisto" , "Not High Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNHighMidMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNHighMidMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNHighMidElectronHisto = m_histoFolder.make<TH2D>("notNNHighMidElectronHisto" , "Not High Mid NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNHighMidElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNHighMidElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNSuperResolvedMuonHisto = m_histoFolder.make<TH2D>("NNSuperResolvedMuonHisto" , "Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNSuperResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNSuperResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_NNSuperResolvedElectronHisto = m_histoFolder.make<TH2D>("NNSuperResolvedElectronHisto" , "Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_NNSuperResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_NNSuperResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNSuperResolvedMuonHisto = m_histoFolder.make<TH2D>("notNNSuperResolvedMuonHisto" , "Not Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNSuperResolvedMuonHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNSuperResolvedMuonHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	m_notNNSuperResolvedElectronHisto = m_histoFolder.make<TH2D>("notNNSuperResolvedElectronHisto" , "Not Super Resolved NN Lepton" , 100, 0, 2500, 100 , 0 , 3000 );
	m_notNNSuperResolvedElectronHisto->GetXaxis()-> SetTitle("lepton + jet + jet");
	m_notNNSuperResolvedElectronHisto->GetYaxis()-> SetTitle("lepton + lepton + jet + jet");
	
	
	m_electronEtaHisto1 = m_histoFolder.make<TH1D>("electronEtaHisto1" , "lepton Eta Histo" , 100, -3, 3);
	m_electronEtaHisto1->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto1 = m_histoFolder.make<TH1D>("electronPhiHisto1" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_electronPhiHisto1->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1 = m_histoFolder.make<TH1D>("electronDPhiHisto1" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_electronDPhiHisto1->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1 = m_histoFolder.make<TH1D>("electronDRHisto1" , "lepton dR Histo" , 100, 0, 10);
	m_electronDRHisto1->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1 = m_histoFolder.make<TH1D>("electronPtHisto1" , "lepton Pt Histo" , 100, 0, 2000);
	m_electronPtHisto1->GetXaxis()-> SetTitle("Pt");
	
	m_electronPtHisto1Scaled = m_histoFolder.make<TH1D>("electronPtHisto1Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_electronPtHisto1Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_electron1SphericityHisto = m_histoFolder.make<TH1D>("electron1SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_electron1SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_electronEtaHisto1WR = m_histoFolder.make<TH1D>("electronEtaHisto1WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_electronEtaHisto1WR->GetXaxis()-> SetTitle("eta");
	
	m_electronNMassHisto1 = m_histoFolder.make<TH1D>("electronNMassHisto1" , "lepton N Mass Histo" , 100, 0, 2000);
	m_electronNMassHisto1->GetXaxis()-> SetTitle("N mass");
	
	
	
	
	
	m_muonEtaHisto1 = m_histoFolder.make<TH1D>("muonEtaHisto1" , "lepton Eta Histo" , 100, -3, 3);
	m_muonEtaHisto1->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto1 = m_histoFolder.make<TH1D>("muonPhiHisto1" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_muonPhiHisto1->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1 = m_histoFolder.make<TH1D>("muonDPhiHisto1" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_muonDPhiHisto1->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1 = m_histoFolder.make<TH1D>("muonDRHisto1" , "lepton dR Histo" , 100, 0, 10);
	m_muonDRHisto1->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1 = m_histoFolder.make<TH1D>("muonPtHisto1" , "lepton Pt Histo" , 100, 0, 2000);
	m_muonPtHisto1->GetXaxis()-> SetTitle("Pt");
	
	m_muonPtHisto1Scaled = m_histoFolder.make<TH1D>("muonPtHisto1Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_muonPtHisto1Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_muon1SphericityHisto = m_histoFolder.make<TH1D>("muon1SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_muon1SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_muonEtaHisto1WR = m_histoFolder.make<TH1D>("muonEtaHisto1WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_muonEtaHisto1WR->GetXaxis()-> SetTitle("eta");
	
	m_muonNMassHisto1 = m_histoFolder.make<TH1D>("muonNMassHisto1" , "lepton N Mass Histo" , 100, 0, 2000);
	m_muonNMassHisto1->GetXaxis()-> SetTitle("N mass");
	
	
	m_electronEtaHisto2 = m_histoFolder.make<TH1D>("electronEtaHisto2" , "lepton Eta Histo" , 100, -3, 3);
	m_electronEtaHisto2->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto2 = m_histoFolder.make<TH1D>("electronPhiHisto2" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_electronPhiHisto2->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2 = m_histoFolder.make<TH1D>("electronDPhiHisto2" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_electronDPhiHisto2->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2 = m_histoFolder.make<TH1D>("electronDRHisto2" , "lepton dR Histo" , 100, 0, 10);
	m_electronDRHisto2->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2 = m_histoFolder.make<TH1D>("electronPtHisto2" , "lepton Pt Histo" , 100, 0, 2000);
	m_electronPtHisto2->GetXaxis()-> SetTitle("Pt");
	
	m_electronPtHisto2Scaled = m_histoFolder.make<TH1D>("electronPtHisto2Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_electronPtHisto2Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_electron2SphericityHisto = m_histoFolder.make<TH1D>("electron2SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_electron2SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity");
	
	m_electronEtaHisto2WR = m_histoFolder.make<TH1D>("electronEtaHisto2WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_electronEtaHisto2WR->GetXaxis()-> SetTitle("eta");
	
	m_electronNMassHisto2 = m_histoFolder.make<TH1D>("electronNMassHisto2" , "lepton N Mass Histo" , 100, 0, 2000);
	m_electronNMassHisto2->GetXaxis()-> SetTitle("N mass");
	
	
	m_muonEtaHisto2 = m_histoFolder.make<TH1D>("muonEtaHisto2" , "lepton Eta Histo" , 100, -3, 3);
	m_muonEtaHisto2->GetXaxis()-> SetTitle("eta"); //
	
	m_muonPhiHisto2 = m_histoFolder.make<TH1D>("muonPhiHisto2" , "lepton Phi Histo", 100, -3.5, 3.5);
	m_muonPhiHisto2->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2 = m_histoFolder.make<TH1D>("muonDPhiHisto2" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_muonDPhiHisto2->GetXaxis()-> SetTitle("dPhi"); //
	
	m_muonDRHisto2 = m_histoFolder.make<TH1D>("muonDRHisto2" , "lepton dR Histo" , 100, 0, 10);
	m_muonDRHisto2->GetXaxis()-> SetTitle("dR"); //
	
	m_muonPtHisto2 = m_histoFolder.make<TH1D>("muonPtHisto2" , "lepton Pt Histo" , 100, 0, 2000);
	m_muonPtHisto2->GetXaxis()-> SetTitle("Pt"); //
	
	m_muonPtHisto2Scaled = m_histoFolder.make<TH1D>("muonPtHisto2Scaled" , "lepton Pt Scaled Histo" , 100, 0, 0.7);
	m_muonPtHisto2Scaled->GetXaxis()-> SetTitle("Pt Scaled");
	
	m_muon2SphericityHisto = m_histoFolder.make<TH1D>("muon2SphericityHisto" , "lepton sphericity Histo" , 100, 0, 1);
	m_muon2SphericityHisto->GetXaxis()-> SetTitle("transverse sphericity"); //
	
	m_muonEtaHisto2WR = m_histoFolder.make<TH1D>("muonEtaHisto2WR" , "lepton Eta Histo WR" , 100, -3, 3);
	m_muonEtaHisto2WR->GetXaxis()-> SetTitle("eta"); //
	
	m_muonNMassHisto2 = m_histoFolder.make<TH1D>("muonNMassHisto2" , "lepton N Mass Histo" , 100, 0, 2000);
	m_muonNMassHisto2->GetXaxis()-> SetTitle("N mass");
	
	
	m_electronEtaHistoNN = m_histoFolder.make<TH1D>("electronEtaHistoNN" , "lepton Eta Histo" , 100, -3, 3);
	m_electronEtaHistoNN->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHistoNN = m_histoFolder.make<TH1D>("electronPhiHistoNN" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_electronPhiHistoNN->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHistoNN = m_histoFolder.make<TH1D>("electronDPhiHistoNN" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_electronDPhiHistoNN->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHistoNN = m_histoFolder.make<TH1D>("electronDRHistoNN" , "lepton dR Histo" , 100, 0, 10);
	m_electronDRHistoNN->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHistoNN = m_histoFolder.make<TH1D>("electronPtHistoNN" , "lepton Pt Histo" , 100, 0, 2000);
	m_electronPtHistoNN->GetXaxis()-> SetTitle("Pt");
	
	m_electronSphericityHistoNN = m_histoFolder.make<TH1D>("electronSphericityHistoNN" , "lepton sphericity Histo" , 100, 0, 1);
	m_electronSphericityHistoNN->GetXaxis()-> SetTitle("transverse sphericity"); //
	
	m_electronEtaHistoWRNN = m_histoFolder.make<TH1D>("electronEtaHistoWRNN" , "lepton Eta Histo WR" , 100, -3, 3);
	m_electronEtaHistoWRNN->GetXaxis()-> SetTitle("eta"); //
	
	m_electronNMassHistoNN = m_histoFolder.make<TH1D>("electronNMassHistoNN" , "lepton N Mass Histo" , 100, 0, 2000);
	m_electronNMassHistoNN->GetXaxis()-> SetTitle("N mass");
	
	
	m_muonEtaHistoNN = m_histoFolder.make<TH1D>("muonEtaHistoNN" , "lepton Eta Histo" , 100, -3, 3);
	m_muonEtaHistoNN->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHistoNN = m_histoFolder.make<TH1D>("muonPhiHistoNN" , "lepton Phi Histo" , 100, -3.5, 3.5);
	m_muonPhiHistoNN->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHistoNN = m_histoFolder.make<TH1D>("muonDPhiHistoNN" , "lepton dPhi Histo" , 100, -6.5, 6.5);
	m_muonDPhiHistoNN->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHistoNN = m_histoFolder.make<TH1D>("muonDRHistoNN" , "lepton dR Histo" , 100, 0, 10);
	m_muonDRHistoNN->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHistoNN = m_histoFolder.make<TH1D>("muonPtHistoNN" , "lepton Pt Histo" , 100, 0, 2000);
	m_muonPtHistoNN->GetXaxis()-> SetTitle("Pt");
	
	m_muonSphericityHistoNN = m_histoFolder.make<TH1D>("muonSphericityHistoNN" , "lepton sphericity Histo" , 100, 0, 1);
	m_muonSphericityHistoNN->GetXaxis()-> SetTitle("transverse sphericity"); //
	
	m_muonEtaHistoWRNN = m_histoFolder.make<TH1D>("muonEtaHistoWRNN" , "lepton Eta Histo WR" , 100, -3, 3);
	m_muonEtaHistoWRNN->GetXaxis()-> SetTitle("eta"); //
	
	m_muonNMassHistoNN = m_histoFolder.make<TH1D>("muonNMassHistoNN" , "lepton N Mass Histo" , 100, 0, 2000);
	m_muonNMassHistoNN->GetXaxis()-> SetTitle("N mass");
	
	
	
	
	
	
	
	
	
	
	
	m_electronPhiHisto1WR = m_histoFolder.make<TH1D>("electronPhiHisto1WR" , "electron Phi Histo WR" , 100, -3.5, 3.5);
	m_electronPhiHisto1WR->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1WR = m_histoFolder.make<TH1D>("electronDPhiHisto1WR" , "electron dPhi Histo WR" , 100, -6.5, 6.5);
	m_electronDPhiHisto1WR->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1WR = m_histoFolder.make<TH1D>("electronDRHisto1WR" , "electron dR Histo WR" , 100, 0, 10);
	m_electronDRHisto1WR->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1WR = m_histoFolder.make<TH1D>("electronPtHisto1WR" , "electron Pt Histo WR" , 100, 0, 2000);
	m_electronPtHisto1WR->GetXaxis()-> SetTitle("Pt");
	
	
	
	m_muonPhiHisto1WR = m_histoFolder.make<TH1D>("muonPhiHisto1WR" , "muon Phi Histo WR" , 100, -3.5, 3.5);
	m_muonPhiHisto1WR->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1WR = m_histoFolder.make<TH1D>("muonDPhiHisto1WR" , "muon dPhi Histo WR" , 100, -6.5, 6.5);
	m_muonDPhiHisto1WR->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1WR = m_histoFolder.make<TH1D>("muonDRHisto1WR" , "muon dR Histo WR" , 100, 0, 10);
	m_muonDRHisto1WR->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1WR = m_histoFolder.make<TH1D>("muonPtHisto1WR" , "muon Pt Histo WR" , 100, 0, 2000);
	m_muonPtHisto1WR->GetXaxis()-> SetTitle("Pt");
	
	
	
	m_electronPhiHisto2WR = m_histoFolder.make<TH1D>("electronPhiHisto2WR" , "electron Phi Histo WR" , 100, -3.5, 3.5);
	m_electronPhiHisto2WR->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2WR = m_histoFolder.make<TH1D>("electronDPhiHisto2WR" , "electron dPhi Histo WR" , 100, -6.5, 6.5);
	m_electronDPhiHisto2WR->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2WR = m_histoFolder.make<TH1D>("electronDRHisto2WR" , "electron dR Histo WR" , 100, 0, 10);
	m_electronDRHisto2WR->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2WR = m_histoFolder.make<TH1D>("electronPtHisto2WR" , "electron Pt Histo WR" , 100, 0, 2000);
	m_electronPtHisto2WR->GetXaxis()-> SetTitle("Pt");
	
	
	
	m_muonPhiHisto2WR = m_histoFolder.make<TH1D>("muonPhiHisto2WR" , "muon Phi Histo WR", 100, -3.5, 3.5);
	m_muonPhiHisto2WR->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2WR = m_histoFolder.make<TH1D>("muonDPhiHisto2WR" , "muon dPhi Histo WR" , 100, -6.5, 6.5);
	m_muonDPhiHisto2WR->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2WR = m_histoFolder.make<TH1D>("muonDRHisto2WR" , "muon dR Histo WR" , 100, 0, 10);
	m_muonDRHisto2WR->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2WR = m_histoFolder.make<TH1D>("muonPtHisto2WR" , "muon Pt Histo WR" , 100, 0, 2000);
	m_muonPtHisto2WR->GetXaxis()-> SetTitle("Pt");
	
	
	
	
	
	
	m_electronEtaHisto1N = m_histoFolder.make<TH1D>("electronEtaHisto1N" , "electron Eta Histo N" , 100, -3, 3);
	m_electronEtaHisto1N->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto1N = m_histoFolder.make<TH1D>("electronPhiHisto1N" , "electron Phi Histo N" , 100, -3.5, 3.5);
	m_electronPhiHisto1N->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1N = m_histoFolder.make<TH1D>("electronDPhiHisto1N" , "electron dPhi Histo N" , 100, -6.5, 6.5);
	m_electronDPhiHisto1N->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1N = m_histoFolder.make<TH1D>("electronDRHisto1N" , "electron dR Histo N" , 100, 0, 10);
	m_electronDRHisto1N->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1N = m_histoFolder.make<TH1D>("electronPtHisto1N" , "electron Pt Histo N" , 100, 0, 2000);
	m_electronPtHisto1N->GetXaxis()-> SetTitle("Pt");
	
	m_muonEtaHisto1N = m_histoFolder.make<TH1D>("muonEtaHisto1N" , "muon Eta Histo N" , 100, -3, 3);
	m_muonEtaHisto1N->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto1N = m_histoFolder.make<TH1D>("muonPhiHisto1N" , "muon Phi Histo N" , 100, -3.5, 3.5);
	m_muonPhiHisto1N->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1N = m_histoFolder.make<TH1D>("muonDPhiHisto1N" , "muon dPhi Histo N" , 100, -6.5, 6.5);
	m_muonDPhiHisto1N->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1N = m_histoFolder.make<TH1D>("muonDRHisto1N" , "muon dR Histo N" , 100, 0, 10);
	m_muonDRHisto1N->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1N = m_histoFolder.make<TH1D>("muonPtHisto1N" , "muon Pt Histo N" , 100, 0, 2000);
	m_muonPtHisto1N->GetXaxis()-> SetTitle("Pt");
	
	m_electronEtaHisto2N = m_histoFolder.make<TH1D>("electronEtaHisto2N" , "electron Eta Histo N" , 100, -3, 3);
	m_electronEtaHisto2N->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto2N = m_histoFolder.make<TH1D>("electronPhiHisto2N" , "electron Phi Histo N" , 100, -3.5, 3.5);
	m_electronPhiHisto2N->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2N = m_histoFolder.make<TH1D>("electronDPhiHisto2N" , "electron dPhi Histo N" , 100, -6.5, 6.5);
	m_electronDPhiHisto2N->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2N = m_histoFolder.make<TH1D>("electronDRHisto2N" , "electron dR Histo N" , 100, 0, 10);
	m_electronDRHisto2N->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2N = m_histoFolder.make<TH1D>("electronPtHisto2N" , "electron Pt Histo N" , 100, 0, 2000);
	m_electronPtHisto2N->GetXaxis()-> SetTitle("Pt");
	
	m_muonEtaHisto2N = m_histoFolder.make<TH1D>("muonEtaHisto2N" , "muon Eta Histo N" , 100, -3, 3);
	m_muonEtaHisto2N->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto2N = m_histoFolder.make<TH1D>("muonPhiHisto2N" , "muon Phi Histo N", 100, -3.5, 3.5);
	m_muonPhiHisto2N->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2N = m_histoFolder.make<TH1D>("muonDPhiHisto2N" , "muon dPhi Histo N" , 100, -6.5, 6.5);
	m_muonDPhiHisto2N->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2N = m_histoFolder.make<TH1D>("muonDRHisto2N" , "muon dR Histo N" , 100, 0, 10);
	m_muonDRHisto2N->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2N = m_histoFolder.make<TH1D>("muonPtHisto2N" , "muon Pt Histo N" , 100, 0, 2000);
	m_muonPtHisto2N->GetXaxis()-> SetTitle("Pt");
	


	m_electronEtaHisto1L = m_histoFolder.make<TH1D>("electronEtaHisto1L" , "electron Eta Histo L" , 100, -3, 3);
	m_electronEtaHisto1L->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto1L = m_histoFolder.make<TH1D>("electronPhiHisto1L" , "electron Phi Histo L" , 100, -3.5, 3.5);
	m_electronPhiHisto1L->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto1L = m_histoFolder.make<TH1D>("electronDPhiHisto1L" , "electron dPhi Histo L" , 100, -6.5, 6.5);
	m_electronDPhiHisto1L->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto1L = m_histoFolder.make<TH1D>("electronDRHisto1L" , "electron dR Histo L" , 100, 0, 10);
	m_electronDRHisto1L->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto1L = m_histoFolder.make<TH1D>("electronPtHisto1L" , "electron Pt Histo L" , 100, 0, 2000);
	m_electronPtHisto1L->GetXaxis()-> SetTitle("Pt");
	
	m_muonEtaHisto1L = m_histoFolder.make<TH1D>("muonEtaHisto1L" , "muon Eta Histo L" , 100, -3, 3);
	m_muonEtaHisto1L->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto1L = m_histoFolder.make<TH1D>("muonPhiHisto1L" , "muon Phi Histo L" , 100, -3.5, 3.5);
	m_muonPhiHisto1L->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto1L = m_histoFolder.make<TH1D>("muonDPhiHisto1L" , "muon dPhi Histo L" , 100, -6.5, 6.5);
	m_muonDPhiHisto1L->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto1L = m_histoFolder.make<TH1D>("muonDRHisto1L" , "muon dR Histo L" , 100, 0, 10);
	m_muonDRHisto1L->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto1L = m_histoFolder.make<TH1D>("muonPtHisto1L" , "muon Pt Histo L" , 100, 0, 2000);
	m_muonPtHisto1L->GetXaxis()-> SetTitle("Pt");
	
	m_electronEtaHisto2L = m_histoFolder.make<TH1D>("electronEtaHisto2L" , "electron Eta Histo L" , 100, -3, 3);
	m_electronEtaHisto2L->GetXaxis()-> SetTitle("eta");
	
	m_electronPhiHisto2L = m_histoFolder.make<TH1D>("electronPhiHisto2L" , "electron Phi Histo L" , 100, -3.5, 3.5);
	m_electronPhiHisto2L->GetXaxis()-> SetTitle("phi");
	
	m_electronDPhiHisto2L = m_histoFolder.make<TH1D>("electronDPhiHisto2L" , "electron dPhi Histo L" , 100, -6.5, 6.5);
	m_electronDPhiHisto2L->GetXaxis()-> SetTitle("dPhi");
	
	m_electronDRHisto2L = m_histoFolder.make<TH1D>("electronDRHisto2L" , "electron dR Histo L" , 100, 0, 10);
	m_electronDRHisto2L->GetXaxis()-> SetTitle("dR");
	
	m_electronPtHisto2L = m_histoFolder.make<TH1D>("electronPtHisto2L" , "electron Pt Histo L" , 100, 0, 2000);
	m_electronPtHisto2L->GetXaxis()-> SetTitle("Pt");
	
	m_muonEtaHisto2L = m_histoFolder.make<TH1D>("muonEtaHisto2L" , "muon Eta Histo L" , 100, -3, 3);
	m_muonEtaHisto2L->GetXaxis()-> SetTitle("eta");
	
	m_muonPhiHisto2L = m_histoFolder.make<TH1D>("muonPhiHisto2L" , "muon Phi Histo L", 100, -3.5, 3.5);
	m_muonPhiHisto2L->GetXaxis()-> SetTitle("phi");
	
	m_muonDPhiHisto2L = m_histoFolder.make<TH1D>("muonDPhiHisto2L" , "muon dPhi Histo L" , 100, -6.5, 6.5);
	m_muonDPhiHisto2L->GetXaxis()-> SetTitle("dPhi");
	
	m_muonDRHisto2L = m_histoFolder.make<TH1D>("muonDRHisto2L" , "muon dR Histo L" , 100, 0, 10);
	m_muonDRHisto2L->GetXaxis()-> SetTitle("dR");
	
	m_muonPtHisto2L = m_histoFolder.make<TH1D>("muonPtHisto2L" , "muon Pt Histo L" , 100, 0, 2000);
	m_muonPtHisto2L->GetXaxis()-> SetTitle("Pt");
	
	
	
	
	
	
	/*
	m_electron1SphericityHisto = m_histoFolder.make<TH1D>("electron1SphericityHisto" , "electron sphericity Histo" , 100, 0, 1);
	m_electron1SphericityHisto->GetXaxis()-> SetTitle("sphericity");
	
	m_electron2SphericityHisto = m_histoFolder.make<TH1D>("electron2SphericityHisto" , "electron sphericity Histo" , 100, 0, 1);
	m_electron2SphericityHisto->GetXaxis()-> SetTitle("sphericity");
	
	m_muon1SphericityHisto = m_histoFolder.make<TH1D>("muon1SphericityHisto" , "muon sphericity Histo" , 100, 0, 1);
	m_muon1SphericityHisto->GetXaxis()-> SetTitle("sphericity");
	
	m_muon2SphericityHisto = m_histoFolder.make<TH1D>("muon2SphericityHisto" , "muon sphericity Histo" , 100, 0, 1);
	m_muon2SphericityHisto->GetXaxis()-> SetTitle("sphericity");
	*/

}

void eventHistos::fill(eventBits& event) {
	m_countHisto->Fill("count", event.count);
	//std::cout << "count2 " << event.count << std::endl;
	
	if(event.mixedLeptons){ // mixed leptons
		m_leptonHisto->Fill("one Electron, one Muon", event.eventWeight);  
	} else { // two electrons or two muons
		if(event.passedElectronReco){ // pass Reco
			m_leptonHisto->Fill("two Electrons", event.eventWeight);

			////std::cout << "passed Electron Reco" << std::endl;
			if(event.nMinusOneFailElectron.size()==0){ // pass Cuts
				////std::cout << "passed Electron Cuts" << std::endl;
				fillElectron(event);
				fillNMinusOnePassElectron(event);
				
				if(event.correctNN){
					m_correctNNHisto->Fill("correct and passed cuts", event.eventWeight);
					m_correctNNHisto->Fill("counted in cuts", event.eventWeight);
				} else {
					m_correctNNHisto->Fill("incorrect and passed cuts", event.eventWeight);
					m_correctNNHisto->Fill("counted in cuts", event.eventWeight);
				}
				
				
			} else { // fail cuts
			    ////std::cout << "failed Electron Cuts" << std::endl;
				m_leptonHisto->Fill("failed Cuts, Electron", event.eventWeight);
				
				if(event.nMinusOneFailElectron.size()==1){ // fail one cut
					////std::cout << "However, only 1 cut" << std::endl;
					fillNMinusOneFailElectron(event);
				}
			}
			if(event.correctNN){
				m_correctNNHisto->Fill("correct", event.eventWeight);
				m_correctNNHisto->Fill("counted out cuts", event.eventWeight);
			} else {
				m_correctNNHisto->Fill("incorrect", event.eventWeight);
				m_correctNNHisto->Fill("counted out cuts", event.eventWeight);
			}
			
			
		} else if(event.twoElectrons) {// fail Reco
			m_leptonHisto->Fill("failed Electron Reco", event.eventWeight);
		}
		if(event.passedMuonReco) {
			m_leptonHisto->Fill("two Muons", event.eventWeight);
	

			////std::cout << "passed Muon Reco" << std::endl;
			if(event.nMinusOneFailMuon.size()==0){ // pass Cuts
			    //std::cout << "passed Muon Cuts" << std::endl;
				fillMuon(event);
				fillNMinusOnePassMuon(event);
				
				if(event.correctNN){
					m_correctNNHisto->Fill("correct and passed cuts", event.eventWeight);
					m_correctNNHisto->Fill("counted in cuts", event.eventWeight);
				} else {
					m_correctNNHisto->Fill("incorrect and passed cuts", event.eventWeight);
					m_correctNNHisto->Fill("counted in cuts", event.eventWeight);
				}
				
			} else { // fail cuts
			    ////std::cout << "failed Muon Cuts" << std::endl;
				m_leptonHisto->Fill("failed Cuts, Muon", event.eventWeight);
				
				if(event.nMinusOneFailMuon.size()==1){ // fail one cut
					////std::cout << "However, only 1 cut" << std::endl;
					fillNMinusOneFailMuon(event);
				}
			}
			
			if(event.correctNN){
				m_correctNNHisto->Fill("correct", event.eventWeight);
				m_correctNNHisto->Fill("counted out cuts", event.eventWeight);
			} else {
				m_correctNNHisto->Fill("incorrect", event.eventWeight);
				m_correctNNHisto->Fill("counted out cuts", event.eventWeight);
			}

		} else if(event.twoMuons){
			m_leptonHisto->Fill("failed Muon Reco", event.eventWeight);
		}

		if(event.passedElectronReco && event.passedMuonReco){
			m_leptonHisto->Fill("two Electrons and two Muons", event.eventWeight);
	
		} else if(!event.passedElectronReco && !event.passedMuonReco){
			m_leptonHisto->Fill("Nothing", event.eventWeight);
		}
		if(event.passedMuonReco && event.passedElectronReco && event.nMinusOneFailMuon.size()==0 && event.nMinusOneFailElectron.size()==0) { 
			////std::cout << "passed both electron and muon cuts and reco" << std::endl;
			m_leptonHisto->Fill("passed Cuts, Both", event.eventWeight);
			
		}
	}
}


void eventHistos::fillMuon(eventBits& event){
	double weight = event.eventWeight;
	std::cout << "weight Muon" << weight << std::endl;

	m_subMuJJhisto->Fill(event.subMuonleadJsubJRecoMass, weight);
	m_l2MuJJhisto->Fill(event.matchedMuonleadJsubJRecoMass, weight);
	m_matchedMuonHisto->Fill(event.matchedMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	m_subLeadMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	m_leadMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	if(!event.passedElectronReco){
		m_leptonHisto->Fill("passed Cuts, Muon", weight);
	}
	
	m_jetjetMassHisto->Fill(event.leadJsubJRecoMass, weight);
	m_matchedMuon1MassHisto->Fill(event.muon1RecoMass, weight);
	m_matchedMuon2MassHisto->Fill(event.muon2RecoMass, weight);

	
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
	
	
	/*m_muonEtaHistoNN->Fill(event.leadRecoMuonEta, weight);
		m_muonPhiHistoNN->Fill(event.leadRecoMuonPhi, weight);
		m_muonDPhiHistoNN->Fill(event.leadRecoMuonDPhi, weight);
		m_muonDRHistoNN->Fill(event.leadRecoMuonDR, weight);
		m_muonPtHistoNN->Fill(event.leadRecoMuonPt, weight);
		m_muonSphericityHistoNN->Fill(event.sphericityLeadMuon, weight);
		m_muonEtaHistoWRNN->Fill(event.leadRecoMuonEtaWR, weight);
		m_muonNMassHistoNN->Fill(event.leadMuonleadJsubJRecoMass, weight);*/
	
	/*m_muonEtaHistoNN->Fill(event.subRecoMuonEta, weight);
		m_muonPhiHistoNN->Fill(event.subRecoMuonPhi, weight);
		m_muonDPhiHistoNN->Fill(event.subRecoMuonDPhi, weight);
		m_muonDRHistoNN->Fill(event.subRecoMuonDR, weight);
		m_muonPtHistoNN->Fill(event.subRecoMuonPt, weight);
		m_muonSphericityHistoNN->Fill(event.sphericitySubMuon, weight);
		m_muonEtaHistoWRNN->Fill(event.subRecoMuonEtaWR, weight);
		m_muonNMassHistoNN->Fill(event.subMuonleadJsubJRecoMass, weight);*/
	if(event.nnResolvedPickedLeadMuon){
		m_NNResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else if(event.nnResolvedPickedSubLeadMuon) {		
		m_notNNResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	if(event.nnLowMidPickedLeadMuon){
		m_NNLowMidMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNLowMidMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else if(event.nnLowMidPickedSubLeadMuon) {		
		m_notNNLowMidMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNLowMidMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	if(event.nnMidPickedLeadMuon){
		m_NNMidMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNMidMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else if(event.nnMidPickedSubLeadMuon) {		
		m_notNNMidMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNMidMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	if(event.nnHighMidPickedLeadMuon){
		m_NNHighMidMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNHighMidMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else if(event.nnHighMidPickedSubLeadMuon) {		
		m_notNNHighMidMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNHighMidMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	if(event.nnSuperResolvedPickedLeadMuon){
		m_NNSuperResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_notNNSuperResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else if(event.nnSuperResolvedPickedSubLeadMuon) {		
		m_notNNSuperResolvedMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_NNSuperResolvedMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} 
		
	
	
	
	if(abs(event.leadRecoMuonEta)<abs(event.subRecoMuonEta)){
		m_lowEtaMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_highEtaMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else {
		m_highEtaMuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_lowEtaMuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	if(event.leadMuonleadJRecodr2 + event.leadMuonsubJRecodr2 < event.subMuonleadJRecodr2 + event.subMuonsubJRecodr2){
		m_lowR2MuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_highR2MuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	} else {
		m_highR2MuonHisto->Fill(event.leadMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
		m_lowR2MuonHisto->Fill(event.subMuonleadJsubJRecoMass, event.fullRecoMassMuon, weight);
	}
	
}


void eventHistos::fillElectron(eventBits& event){
	double weight = event.eventWeight;
	std::cout << "weight Electron" << weight << "" << event.subElectronleadJsubJRecoMass << "" << event.leadElectronleadJsubJRecoMass << "" << event.fullRecoMassElectron << std::endl;
		
	m_subElectronJJhisto->Fill(event.subElectronleadJsubJRecoMass, weight);
	m_l2ElectronJJhisto->Fill(event.matchedElectronleadJsubJRecoMass, weight);
	m_matchedElectronHisto->Fill(event.matchedElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	m_subLeadElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	m_leadElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	
	if(!event.passedMuonReco){
		m_leptonHisto->Fill("passed Cuts, Electron", weight);
	}
	
	m_jetjetMassHisto->Fill(event.leadJsubJRecoMass, weight);
	m_matchedElectron1MassHisto->Fill(event.electron1RecoMass, weight);
	m_matchedElectron2MassHisto->Fill(event.electron2RecoMass, weight);
	
	
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
	
	/*
	if(event.nnPickedLeadElectron){
		m_electronEtaHistoNN->Fill(event.leadRecoElectronEta, weight);
		m_electronPhiHistoNN->Fill(event.leadRecoElectronPhi, weight);
		m_electronDPhiHistoNN->Fill(event.leadRecoElectronDPhi, weight);
		m_electronDRHistoNN->Fill(event.leadRecoElectronDR, weight);
		m_electronPtHistoNN->Fill(event.leadRecoElectronPt, weight);
		m_electronSphericityHistoNN->Fill(event.sphericityLeadElectron, weight);
		m_electronEtaHistoWRNN->Fill(event.leadRecoElectronEtaWR, weight);
		m_electronNMassHistoNN->Fill(event.leadElectronleadJsubJRecoMass, weight);
		
		m_NNElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		
	} else {
		m_electronEtaHistoNN->Fill(event.subRecoElectronEta, weight);
		m_electronPhiHistoNN->Fill(event.subRecoElectronPhi, weight);
		m_electronDPhiHistoNN->Fill(event.subRecoElectronDPhi, weight);
		m_electronDRHistoNN->Fill(event.subRecoElectronDR, weight);
		m_electronPtHistoNN->Fill(event.subRecoElectronPt, weight);
		m_electronSphericityHistoNN->Fill(event.sphericitySubElectron, weight);
		m_electronEtaHistoWRNN->Fill(event.subRecoElectronEtaWR, weight);
		m_electronNMassHistoNN->Fill(event.subElectronleadJsubJRecoMass, weight);
		
		m_NNElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	}*/
	
	if(event.nnResolvedPickedLeadElectron){
		m_NNResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else if(event.nnResolvedPickedSubLeadElectron) {		
		m_notNNResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} 
	if(event.nnLowMidPickedLeadElectron){
		m_NNLowMidElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNLowMidElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else if(event.nnLowMidPickedSubLeadElectron) {		
		m_notNNLowMidElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNLowMidElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	}
	if(event.nnMidPickedLeadElectron){
		m_NNMidElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNMidElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else if(event.nnMidPickedSubLeadElectron) {		
		m_notNNMidElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNMidElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} 
	if(event.nnHighMidPickedLeadElectron){
		m_NNHighMidElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNHighMidElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else if(event.nnHighMidPickedSubLeadElectron) {		
		m_notNNHighMidElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNHighMidElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	}
	if(event.nnSuperResolvedPickedLeadElectron){
		m_NNSuperResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_notNNSuperResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else if(event.nnSuperResolvedPickedSubLeadElectron) {		
		m_notNNSuperResolvedElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_NNSuperResolvedElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} 
	
	
	
	
	
	if(abs(event.leadRecoElectronEta)<abs(event.subRecoElectronEta)){
		m_lowEtaElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_highEtaElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		std::cout << "highEtaElectronHisto" << std::endl;
		std::cout << event.subElectronleadJsubJRecoMass << std::endl;
		std::cout << event.fullRecoMassElectron << std::endl;
		std::cout << weight << std::endl;
		
		
		
	} else {
		m_highEtaElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_lowEtaElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		std::cout << "highEtaElectronHisto" << std::endl;
		std::cout << event.leadElectronleadJsubJRecoMass << std::endl;
		std::cout << event.fullRecoMassElectron << std::endl;
		std::cout << weight << std::endl;
	}
	if(event.leadElectronleadJRecodr2+event.leadElectronsubJRecodr2<event.subElectronleadJRecodr2+event.subElectronsubJRecodr2){
		m_lowR2ElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_highR2ElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	} else {
		m_highR2ElectronHisto->Fill(event.leadElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
		m_lowR2ElectronHisto->Fill(event.subElectronleadJsubJRecoMass, event.fullRecoMassElectron, weight);
	}
}

void eventHistos::fillNMinusOneFailElectron(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOneFailElectron.begin(); s != event.nMinusOneFailElectron.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneElectronHisto->Fill((*s).c_str(),weight); 
	}
}

void eventHistos::fillNMinusOnePassElectron(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOnePassElectron.begin(); s != event.nMinusOnePassElectron.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneElectronHisto->Fill((*s).c_str(),weight); 
	}
}

void eventHistos::fillNMinusOneFailMuon(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOneFailMuon.begin(); s != event.nMinusOneFailMuon.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneMuonHisto->Fill((*s).c_str(),weight); 
	}
}

void eventHistos::fillNMinusOnePassMuon(eventBits& event){
	double weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOnePassMuon.begin(); s != event.nMinusOnePassMuon.end(); s++) {
		m_nMinusOneHisto->Fill((*s).c_str(),weight); 
		m_nMinusOneMuonHisto->Fill((*s).c_str(),weight); 
	}
}
	
