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


	m_l1qqHisto = m_histoFolder.make<TH1D>("l1qq" , "Lepton 1 + Quark + Quark Mass" , 100 , 0 , 6000 );
	m_l2qqHisto = m_histoFolder.make<TH1D>("l2qq" , "Lepton 2 + Quark + Quark Mass" , 100 , 0 , 6000 );
	m_subLqqHisto = m_histoFolder.make<TH1D>("subLqq" , "Sublead Lepton + Quark + Quark Mass" , 100 , 0 , 6000 );
	m_llqqHisto = m_histoFolder.make<TH1D>("llqq" , "Lepton 1 + Lepton 2 + Quark + Quark Mass" , 100 , 0 , 6000 );

	m_subMuJJhisto = m_histoFolder.make<TH1D>("subMuJJhisto" , "Sublead Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_l2MuJJhisto = m_histoFolder.make<TH1D>("l2MuJJhisto" , "Lepton 2 Matched Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );

	m_subElectronJJhisto = m_histoFolder.make<TH1D>("subElectronJJhisto" , "Sublead Electron + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
	m_l2ElectronJJhisto = m_histoFolder.make<TH1D>("l2ElectronJJhisto" , "Lepton 2 Matched Electron + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );

	m_nMinusOneHisto = m_histoFolder.make<TH1D>("nMinusOneHisto", "n-1 Plot", 6, 1, 6);

	m_nMinusOneHisto->GetXaxis()->SetBinLabel(1,"jet pt > 40 GeV");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(2,"jet |eta| < 2.4");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(3,"lepton mass > 200 GeV");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(4,"dR > 0.4");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(5,"leading l pt > 60 GeV");
	m_nMinusOneHisto->GetXaxis()->SetBinLabel(6,"subleading l pt > 53 GeV");


}

void eventHistos::fill(eventBits& event) {
  if(event.nMinusOne.size()==6){
	fillAll(event);
	fillNMinusOne(event);
   } else if(event.nMinusOne.size()==1){
	fillNMinusOne(event);
  }
}


void eventHistos::fillAll(eventBits& event){
	double weight = 0.0;
	weight = event.eventWeight;
	
	m_l1qqHisto->Fill(event.lepton1quark1quark2Mass, weight);
	m_l2qqHisto->Fill(event.lepton2quark1quark2Mass, weight);
	m_subLqqHisto->Fill(event.subLeptonquark1quark2Mass, weight);
	m_llqqHisto->Fill(event.fullMass, weight);
	
	if(event.passedReco && event.twoMuons){
		m_subMuJJhisto->Fill(event.subMuonMatchedJet1Jet2Mass, weight);
		m_l2MuJJhisto->Fill(event.matchedMuonMatchedJet1Jet2Mass, weight);
	} else if(event.passedReco && event.twoElectrons) {
		m_subElectronJJhisto->Fill(event.subElectronMatchedJet1Jet2Mass, weight);
		m_l2ElectronJJhisto->Fill(event.matchedElectronMatchedJet1Jet2Mass, weight);
	}	
}

void eventHistos::fillNMinusOne(eventBits& event){
	double weight = 0.0;
	weight = event.eventWeight;
	
	for(std::list<std::string>::iterator s = event.nMinusOne.begin(); s != event.nMinusOne.end(); s++) {
	  m_nMinusOneHisto->Fill((*s).c_str(),weight); 
	}
	
}
	

