// -*- C++ -*-
//
// Package:    ExoAnalysis/WR_MASS_PLOT
// Class:      WR_MASS_PLOT
//
/**\class WR_MASS_PLOT WR_MASS_PLOT.cc ExoAnalysis/WR_MASS_PLOT/plugins/WR_MASS_PLOT.cc
 Description: [one line class summary]
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Evans
//         Created:  Mon, 14 Oct 2019 19:43:16 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "TH1.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

class WR_MASS_PLOT : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit WR_MASS_PLOT(const edm::ParameterSet&);
      ~WR_MASS_PLOT();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      double dR2(double eta1, double eta2, double phi1, double phi2);
      double dPhi(double phi1, double phi2);

      // ----------member data ---------------------------
      TH1D * l1qqHisto;
      TH1D * l2qqHisto;
      TH1D * llqqHisto;
      TH1D * subLqqHisto;

      TH1D * subMuJJhisto;
      TH1D * l2MuJJhisto;
	  
      TH1D * nMinusOneHisto;
      TH1D * totalEventsHisto;

      edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
      edm::EDGetToken m_genParticleToken;
      edm::EDGetToken m_regMuonToken;
      edm::EDGetToken m_AK4recoCHSJetsToken;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
WR_MASS_PLOT::WR_MASS_PLOT(const edm::ParameterSet& iConfig)
 :
  tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))),
  m_genParticleToken(consumes<std::vector<reco::GenParticle>> (iConfig.getParameter<edm::InputTag>("genParticles"))),
  m_regMuonToken (consumes<std::vector<pat::Muon>> (iConfig.getParameter<edm::InputTag>("regMuons"))),
  m_AK4recoCHSJetsToken (consumes<std::vector<pat::Jet>> (iConfig.getParameter<edm::InputTag>("AK4recoCHSJets")))

{
   //now do what ever initialization is needed
  edm::Service<TFileService> fs;

  l1qqHisto = fs->make<TH1D>("l1qq" , "Lepton 1 + Quark + Quark Mass" , 100 , 0 , 6000 );
  l2qqHisto = fs->make<TH1D>("l2qq" , "Lepton 2 + Quark + Quark Mass" , 100 , 0 , 6000 );
  subLqqHisto = fs->make<TH1D>("subLqq" , "Sublead Lepton + Quark + Quark Mass" , 100 , 0 , 6000 );
  llqqHisto = fs->make<TH1D>("llqq" , "Lepton 1 + Lepton 2 + Quark + Quark Mass" , 100 , 0 , 6000 );

  subMuJJhisto = fs->make<TH1D>("subMuJJhisto" , "Sublead Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );
  l2MuJJhisto = fs->make<TH1D>("l2MuJJhisto" , "Lepton 2 Matched Muon + Lead Jet + Sublead Jet Mass" , 50 , 0 , 4000 );

  nMinusOneHisto = fs->make<TH1D>("nMinusOneHisto", "n-1 Plot", 6, 1, 6);
  totalEventsHisto = fs->make<TH1D>("totalEventsHisto", "total Events", 5, 0, 2);

  nMinusOneHisto->GetXaxis()->SetBinLabel(1,"jet pt > 40 GeV");
  nMinusOneHisto->GetXaxis()->SetBinLabel(2,"jet |eta| < 2.4");
  nMinusOneHisto->GetXaxis()->SetBinLabel(3,"lepton mass > 200 GeV");
  nMinusOneHisto->GetXaxis()->SetBinLabel(4,"dR > 0.4");
  nMinusOneHisto->GetXaxis()->SetBinLabel(5,"leading l pt > 60 GeV");
  nMinusOneHisto->GetXaxis()->SetBinLabel(6,"subleading l pt > 53 GeV");


}


WR_MASS_PLOT::~WR_MASS_PLOT()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
WR_MASS_PLOT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::cout << "Starting signalGENidentifier" << std::endl; 
  edm::Handle<std::vector<reco::GenParticle>> genParticles;
  iEvent.getByToken(m_genParticleToken, genParticles);

  //LOOP OVER GEN PARTICLES
  //9900024 WR 9900014 NRu 9900012 NRe 9900016 NRt
  const reco::GenParticle* neutrino = 0;
  const reco::GenParticle* lepton1   = 0;
  const reco::GenParticle* lepton2      = 0;
  const reco::GenParticle* leadLepton   = 0;
  const reco::GenParticle* subleadLepton      = 0;
  std::vector<const reco::GenParticle*> decayQuarks; 
//STATUS: 21 PDGID: 1 MOTHER: 2212
//STATUS: 21 PDGID: -2 MOTHER: 2212
//STATUS: 22 PDGID: -34 MOTHER: 1
//STATUS: 22 PDGID: 9900012 MOTHER: -34
//STATUS: 23 PDGID: 11 MOTHER: -34
//STATUS: 23 PDGID: -11 MOTHER: 9900012
//STATUS: 23 PDGID: 1 MOTHER: 9900012
//STATUS: 23 PDGID: -2 MOTHER: 9900012
//

  const char *label[6]  = {"jet pt > 40 GeV","jet |eta| < 2.4","lepton mass > 200 GeV","dR > 0.4","leading l pt > 60 GeV", "subleading l pt > 53 GeV"};

  for (std::vector<reco::GenParticle>::const_iterator iParticle = genParticles->begin(); iParticle != genParticles->end(); iParticle++) {
    if( ! iParticle->isHardProcess() ) continue;  //ONLY HARD PROCESS AND NOT INCOMING
    if( iParticle->status() == 21 ) continue;
//    std::cout << "STATUS: " << iParticle->status() << " PDGID: " << iParticle->pdgId() << " MOTHER: " << iParticle->mother()->pdgId() << std::endl;
    if( abs( iParticle->mother()->pdgId() ) <= 6 || abs( iParticle->mother()->pdgId() ) == 9900024 || abs( iParticle->mother()->pdgId()) == 34) {//CAME FROM A QUARK(VIRTUAL WR) OR A WR OR A HEAVY W
      if( abs( iParticle->pdgId() ) == 13 || abs( iParticle->pdgId() ) == 11 ) //HERE'S A LEPTON
        lepton1 = &(*iParticle);
      if( abs( iParticle->pdgId() ) == 9900014 || abs( iParticle->pdgId() ) == 9900012) //HERE'S A RIGHT-HANDED NEUTRINO
        neutrino = &(*iParticle);
    }
    if( (abs( iParticle->mother()->pdgId() ) == 9900014) 
     || (abs( iParticle->mother()->pdgId() ) == 9900012)
      ) {//CAME FROM A RIGHT-HANDED NEUTRINO
      if( abs( iParticle->pdgId() ) == 13 || abs( iParticle->pdgId() ) == 11 ) {
        std::cout << "IN HERE" << std::endl;
        std::cout << "STATUS: " << iParticle->status() << " PDGID: " << iParticle->pdgId() << " MOTHER: " << iParticle->mother()->pdgId() << std::endl;
        lepton2 = &(*iParticle);
      }
    }
    if( (abs( iParticle->mother()->pdgId() ) == 9900014) 
     || (abs( iParticle->mother()->pdgId() ) == 9900012)
     || (abs( iParticle->mother()->pdgId() ) == 34)
     || (abs( iParticle->mother()->pdgId() ) == 9900024)
      ) {//CAME FROM A RIGHT-HANDED NEUTRINO
      if( abs( iParticle->pdgId() ) <= 6 ) {//WR DECAY QUARKS
        std::cout << "IN THERE" << std::endl;
        std::cout << "STATUS: " << iParticle->status() << " PDGID: " << iParticle->pdgId() << " MOTHER: " << iParticle->mother()->pdgId() << std::endl;
        decayQuarks.push_back(&(*(iParticle)));
      }
    }
  }
  if ((neutrino == 0) || (lepton1 == 0) || (lepton2 == 0) || (decayQuarks.size() != 2)) {
    std::cout << "WARNING: EVENT NOT UNDERSTOOD" << std::endl;
    for (std::vector<reco::GenParticle>::const_iterator iParticle = genParticles->begin(); iParticle != genParticles->end(); iParticle++) {
      if( ! iParticle->isHardProcess() ) continue;  //ONLY HARD PROCESS AND NOT INCOMING
      std::cout << "STATUS: " << iParticle->status() << " PDGID: " << iParticle->pdgId() << " MOTHER: " << iParticle->mother()->pdgId() << std::endl;
    }
    return;  
  }
  
  
  int nMinusOne[6] = {};
  
  //decay jets have transverse momentum greater than 400 GeV
  if (decayQuarks[0]->pt() <= 40 || decayQuarks[1]->pt() <= 40){
	nMinusOne[0] = 1;
  }
  
  //decay jets have |eta| < 2.4 
  if (decayQuarks[0]->eta() >= 2.4 || decayQuarks[0]->eta() <= -2.4 || decayQuarks[1]->eta() >= 2.4 || decayQuarks[1]->eta() <= -2.4){
	nMinusOne[1] = 1;
  }
  
  //  invariant mass of 2 leptons > 400 GeV
  if ((lepton1->p4()+lepton2->p4()).mass()<=200){
  	nMinusOne[2] = 1;
  }
  
  // check dR > .4 for particle combos
  double lepton1lepton2dr2 = dR2(lepton1->eta(), lepton2->eta(), lepton1->phi(), lepton2->phi());
  double lepton1quark1dr2 = dR2(lepton1->eta(), decayQuarks[0]->eta(), lepton1->phi(), decayQuarks[0]->phi());
  double lepton1quark2dr2 = dR2(lepton1->eta(), decayQuarks[1]->eta(), lepton1->phi(), decayQuarks[1]->phi());
  double lepton2quark1dr2 = dR2(lepton2->eta(), decayQuarks[0]->eta(), lepton2->phi(), decayQuarks[0]->phi());
  double lepton2quark2dr2 = dR2(lepton2->eta(), decayQuarks[1]->eta(), lepton2->phi(), decayQuarks[1]->phi());
  double quark1quark2dr2 = dR2(decayQuarks[0]->eta(), decayQuarks[1]->eta(), decayQuarks[0]->phi(), decayQuarks[1]->phi());
 
  if(lepton1lepton2dr2 <=.16 || lepton1quark1dr2 <=.16 || lepton1quark2dr2 <=.16 || lepton2quark1dr2 <=.16 || lepton2quark2dr2 <=.16 || quark1quark2dr2 <=.16){
	nMinusOne[3] = 1;
  }
  
  totalEventsHisto->Fill(1);

  if (lepton1->pt() > lepton2->pt()){
	//check that leading lepton has pt >60, sub leading pt > 53
    if(lepton1->pt()<=60){
		nMinusOne[4] = 1;
	}
	if(lepton2->pt()<=53){
	    nMinusOne[5] = 1;
	}
	
	int total = 0;
	for(int n =0; n<6; n++){
		total+=nMinusOne[n];
	}
	
	if(total == 1){
		for(int n =0; n<6; n++){
			if(nMinusOne[n] == 1){
				nMinusOneHisto->Fill(label[n],0.0004);
			}
		}
	}
	
	if(total > 0){
		return;
	}
	else{
		for(int n =0; n<6; n++){
			nMinusOneHisto->Fill(label[n],0.0004);
		}
	}
	
    subLqqHisto->Fill((lepton2->p4() + decayQuarks[0]->p4() + decayQuarks[1]->p4()).mass());
  } else {
    
	//check that leading lepton has pt >60, sub leading pt > 53
    if(lepton2->pt()<=60){
		nMinusOne[4] = 1;
	}
	if(lepton1->pt()<=53){
	    nMinusOne[5] = 1;
	}
	
	int total = 0;
	for(int n =0; n<6; n++){
		total+=nMinusOne[n];
	}
	
	if(total == 1){
		for(int n =0; n<6; n++){
			if(nMinusOne[n] == 1){
				nMinusOneHisto->Fill(label[n],0.0004);
			}
		}
	}
	
	if(total > 0){
		return;
	}
	else{
		for(int n =0; n<6; n++){
			nMinusOneHisto->Fill(label[n],0.0004);
		}
	}
	
	subLqqHisto->Fill((lepton1->p4() + decayQuarks[0]->p4() + decayQuarks[1]->p4()).mass());
  }
  l1qqHisto->Fill((lepton1->p4() + decayQuarks[0]->p4() + decayQuarks[1]->p4()).mass());
  l2qqHisto->Fill((lepton2->p4() + decayQuarks[0]->p4() + decayQuarks[1]->p4()).mass());
  llqqHisto->Fill((lepton1->p4() + lepton2->p4() + decayQuarks[0]->p4() + decayQuarks[1]->p4()).mass()); 

  if((abs(lepton1->pdgId()) == 11)|| (abs(lepton2->pdgId()) == 11)) {
    std::cout << "ELECTRONS, BLEH!" << std::endl;
    return;
  }


  //NOW THAT WE HAVE THE REAL PARTICLES, WE'LL GET THE RECO PARTICLES AND MATCH THEM
  edm::Handle<std::vector<pat::Jet>> recoJetsAK4;
  edm::Handle<std::vector<pat::Muon>> regMuons;
  iEvent.getByToken(m_regMuonToken, regMuons);
  iEvent.getByToken(m_AK4recoCHSJetsToken, recoJetsAK4);

  const pat::Muon* matchedMuon = 0;
  const pat::Jet* matchedJet1 = 0;
  const pat::Jet* matchedJet2 = 0;

  const pat::Muon* subleadMuon = 0;
  const pat::Jet* leadJet     = 0;
  const pat::Jet*  subleadJet  = 0;

  int muCount = 0;
  int muMatch = 0;
  int jetCount = 0;
  int q1Match = 0;
  int q2Match = 0;
  for(std::vector<pat::Muon>::const_iterator iMuon = regMuons->begin(); iMuon != regMuons->end(); iMuon++) {
    std::cout << "muons" << std::endl;
    std::cout << iMuon->pt() << std::endl;
    if (muCount == 1) {
      subleadMuon = &(*(iMuon));
    }
    if(muMatch == 0) {
      double matchDR = sqrt(dR2(iMuon->eta(), lepton2->eta(), iMuon->phi(), lepton2->phi()));
      if(matchDR < 0.1)  {
        std::cout << "MUON MATCH" << std::endl;
        matchedMuon = &(*(iMuon));
        muMatch++;
      } 
    }
    muCount++;
  }
  for(std::vector<pat::Jet>::const_iterator iJet = recoJetsAK4->begin(); iJet != recoJetsAK4->end(); iJet++) {
    std::cout << "jets" << std::endl;
    std::cout << iJet->pt() << std::endl;
    if (jetCount == 0) {
      leadJet = &(*(iJet));
    }
    if (jetCount == 1) {
      subleadJet = &(*(iJet));
    }
    double match1DR = sqrt(dR2(iJet->eta(), decayQuarks[0]->eta(), iJet->phi(), decayQuarks[0]->phi()));
    double match2DR = sqrt(dR2(iJet->eta(), decayQuarks[1]->eta(), iJet->phi(), decayQuarks[1]->phi()));
    if(match1DR < 0.4 && q1Match == 0)  {
      std::cout << "Q1 MATCH" << std::endl;
      matchedJet1 = &(*(iJet));
      q1Match++;
    } 
    else if(match2DR < 0.4 && q2Match == 0)  {
      std::cout << "Q2 MATCH" << std::endl;
      matchedJet2 = &(*(iJet));
      q2Match++;
    } 


    jetCount++;
  }

  if(leadJet == 0 || subleadJet == 0 || subleadMuon == 0) {
    std::cout << "WARNING: EVENT CANNOT RESOLVE AT RECO LEVEL. EXITING"<< std::endl;
    return;
  }
  if(muMatch == 0 || q1Match == 0 || q2Match == 0) {
    std::cout << "WARNING: EVENT CANNOT MATCH AT RECO LEVEL. EXITING"<< std::endl;
    return;
  }

  std::cout << leadJet->pt() << std::endl;
  std::cout << subleadJet->pt() << std::endl;
  std::cout << subleadMuon->pt() << std::endl;

//  subMuJJhisto->Fill((subleadMuon->p4() + leadJet->p4() + subleadJet->p4()).mass());
//  l2MuJJhisto ->Fill((matchedMuon->p4() + leadJet->p4() + subleadJet->p4()).mass());
  subMuJJhisto->Fill((subleadMuon->p4() + matchedJet1->p4() + matchedJet2->p4()).mass());
  l2MuJJhisto ->Fill((matchedMuon->p4() + matchedJet1->p4() + matchedJet2->p4()).mass());

}
//HELPERS
double WR_MASS_PLOT::dR2(double eta1, double eta2, double phi1, double phi2) {
    double deta = eta1 - eta2;
    double dphi = dPhi(phi1, phi2);
    return deta*deta + dphi*dphi;
}
double WR_MASS_PLOT::dPhi(double phi1, double phi2) {
    double raw_dphi = phi1 - phi2;
    if (fabs(raw_dphi) < ROOT::Math::Pi()) return raw_dphi;
    double region = std::round(raw_dphi / (2.*ROOT::Math::Pi()));
    return raw_dphi - 2.*ROOT::Math::Pi()*region;
}

// ------------ method called once each job just before starting event loop  ------------
void
WR_MASS_PLOT::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
WR_MASS_PLOT::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
WR_MASS_PLOT::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(WR_MASS_PLOT);
