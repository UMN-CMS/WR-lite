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
#include <fstream>

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
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/GenJet.h"

#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

#include "HEEP/VID/interface/CutNrs.h"
#include "HEEP/VID/interface/VIDCutCodes.h"

#include "TLorentzVector.h"
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TVectorD.h>
#include <cmath>

#include "TH1.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "ExoAnalysis/WR_lite/interface/eventBits.h"
#include "ExoAnalysis/WR_lite/interface/eventInfo.h"
#include "ExoAnalysis/WR_lite/interface/eventHistos.h"
#include "ExoAnalysis/WR_lite/interface/neuralNet.h"

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
		double transverseSphericity(math::XYZTLorentzVector p1, math::XYZTLorentzVector p2, math::XYZTLorentzVector p3);
		void saveElectronData(eventBits * myRECOevent, double matched1Mass, double matched2Mass);
		void saveMuonData(eventBits * myRECOevent, double matched1Mass, double matched2Mass);
		
		
		eventHistos m_allEvents;
		neuralNet networkResolved = neuralNet("/home/kronh006/Version3/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/data/Resolved");
		neuralNet networkSuperResolved = neuralNet("/home/kronh006/Version3/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/data/SuperResolved");

		// ----------member data ---------------------------

		edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
		edm::EDGetToken m_genParticleToken;
		edm::EDGetToken m_highMuonToken;
		edm::EDGetToken m_highElectronToken;
		edm::EDGetToken m_AK4recoCHSJetsToken;
		edm::EDGetToken m_genEventInfoToken;
		edm::EDGetToken m_offlineVerticesToken;
		
		std::string m_dataSaveFile;
		bool m_isSignal;
		bool m_genTrainData;
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
	m_highMuonToken (consumes<std::vector<pat::Muon>> (iConfig.getParameter<edm::InputTag>("highMuons"))),
	m_highElectronToken (consumes<std::vector<pat::Electron>> (iConfig.getParameter<edm::InputTag>("highElectrons"))),
	m_AK4recoCHSJetsToken (consumes<std::vector<pat::Jet>> (iConfig.getParameter<edm::InputTag>("AK4recoCHSJets"))),
	m_genEventInfoToken (consumes<GenEventInfoProduct> (iConfig.getParameter<edm::InputTag>("genInfo"))),
	m_offlineVerticesToken (consumes<std::vector<reco::Vertex>> (iConfig.getParameter<edm::InputTag>("vertices"))),
	m_dataSaveFile (iConfig.getUntrackedParameter<std::string>("trainFile")),
	m_isSignal (iConfig.getUntrackedParameter<bool>("isSignal")),
	m_genTrainData (iConfig.getUntrackedParameter<bool>("genTrainData"))
{
   //now do what ever initialization is needed
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
	bool background = !m_isSignal;
	std::cout << "background: " << background << std::endl;
	eventBits myRECOevent;
	eventInfo myEvent;
	
	edm::Handle<GenEventInfoProduct> eventInfo;
	iEvent.getByToken(m_genEventInfoToken, eventInfo);
  
	myRECOevent.count = eventInfo->weight()/fabs(eventInfo->weight());
	myRECOevent.eventWeight = eventInfo->weight();
	
	
	edm::Handle<std::vector<reco::Vertex>> vertices;
	iEvent.getByToken(m_offlineVerticesToken, vertices);
	if(!vertices.isValid()) {
		throw cms::Exception("Vertex collection not valid!");
	}
	
	myRECOevent.hasPVertex = myEvent.PVselection(vertices);
	
	//Extract Gen information for later matching in signal region
	if(!background){		
		edm::Handle<std::vector<reco::GenParticle>> genParticles;
		iEvent.getByToken(m_genParticleToken, genParticles);

		//LOOP OVER GEN PARTICLES
		//9900024 WR 9900014 NRu 9900012 NRe 9900016 NRt
		const reco::GenParticle* neutrino = 0;
		const reco::GenParticle* lepton1   = 0;
		const reco::GenParticle* lepton2      = 0;
		std::vector<const reco::GenParticle*> decayQuarks; 
    
		for (std::vector<reco::GenParticle>::const_iterator iParticle = genParticles->begin(); iParticle != genParticles->end(); iParticle++) {
			if( ! iParticle->isHardProcess() ) continue;  //ONLY HARD PROCESS AND NOT INCOMING
			if( iParticle->status() == 21 ) continue;
				    std::cout << "STATUS: " << iParticle->status() << " PDGID: " << iParticle->pdgId() << " MOTHER: " << iParticle->mother()->pdgId() << std::endl;
			if( abs( iParticle->mother()->pdgId() ) <= 6 || abs( iParticle->mother()->pdgId() ) == 9900024 || abs( iParticle->mother()->pdgId()) == 34) {//CAME FROM A QUARK(VIRTUAL WR) OR A WR OR A HEAVY W
				if( abs( iParticle->pdgId() ) == 13 || abs( iParticle->pdgId() ) == 11 ) //HERE'S A LEPtON
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
		
		std::cout << "Gen lepton1: " << lepton1->p4() << ", "<< lepton1->pt() << std::endl;
		std::cout << "Gen lepton2: " << lepton2->p4() << ", "<< lepton2->pt() << std::endl;
		std::cout << "Gen quark1: " << decayQuarks[0]->p4() << ", "<< decayQuarks[0]->pt() << std::endl;
		std::cout << "Gen quark2: " << decayQuarks[1]->p4() << ", "<< decayQuarks[1]->pt() << std::endl;
		
		//Save gen information to the event object
		myRECOevent.quark1Eta = decayQuarks[0]->eta();
		myRECOevent.quark1Phi = decayQuarks[0]->phi();
		myRECOevent.quark1Mass = decayQuarks[0]->p4().mass();
		myRECOevent.quark1Pt = decayQuarks[0]->pt();

		myRECOevent.quark2Eta = decayQuarks[1]->eta();
		myRECOevent.quark2Phi = decayQuarks[1]->phi();
		myRECOevent.quark2Mass = decayQuarks[1]->p4().mass();
		myRECOevent.quark2Pt = decayQuarks[1]->pt();

		myRECOevent.lepton1Eta = lepton1->eta();
		myRECOevent.lepton1Phi = lepton1->phi();
		myRECOevent.lepton1Mass = lepton1->p4().mass();
		myRECOevent.lepton1Pt = lepton1->pt();
		myRECOevent.lepton1Id = lepton1->pdgId();
		
		myRECOevent.lepton2Eta = lepton2->eta();
		myRECOevent.lepton2Phi = lepton2->phi();
		myRECOevent.lepton2Mass = lepton2->p4().mass();
		myRECOevent.lepton2Pt = lepton2->pt();
		myRECOevent.lepton2Id = lepton2->pdgId();
		
		myRECOevent.WRMass = (decayQuarks[0]->p4()+decayQuarks[1]->p4()+lepton2->p4()+ lepton1->p4()).mass();
		myRECOevent.NMass = (decayQuarks[0]->p4()+decayQuarks[1]->p4()+lepton2->p4()).mass();
		
	//Extract gen information for background events to determine distribution	
	} else {
		edm::Handle<std::vector<reco::GenParticle>> genParticles;
		iEvent.getByToken(m_genParticleToken, genParticles);

        int lepton1 = 0;
		int lepton2 = 0;
		int lepton1Cuts = 0;
		int lepton2Cuts = 0;
		int lepton1ID = 0;
		int lepton2ID = 0;

		for (std::vector<reco::GenParticle>::const_iterator iParticle = genParticles->begin(); iParticle != genParticles->end(); iParticle++) {
			if( ! iParticle->isHardProcess() ) continue;  //ONLY HARD PROCESS AND NOT INCOMING
			if( abs( iParticle->pdgId() ) == 13 || abs( iParticle->pdgId() ) == 11 || abs( iParticle->pdgId() ) == 15) {//HERE'S A LEPtON
				if(fabs(iParticle->eta()) < 2.4 && iParticle->pt() > 53 ){
					if(lepton1Cuts==0){
						lepton1Cuts=1;
					} else if(lepton2Cuts==0){
						lepton2Cuts=1;
					}
				}
				if(lepton1==0){
					myRECOevent.leadLeptonPt = iParticle->pt();
					myRECOevent.leadLeptonType = fabs(iParticle->pdgId()*1.0);
					lepton1=1;
					lepton1ID = abs(iParticle->pdgId());
				} else if(lepton2==0){
					myRECOevent.subleadLeptonPt = iParticle->pt();
					myRECOevent.subleadLeptonType = fabs(iParticle->pdgId()*1.0);
					lepton2=1;
					lepton2ID = abs(iParticle->pdgId());
				}
			}
		}
	
		if ((lepton1 == 0) || (lepton2 == 0)) {
			myRECOevent.failedGenPtEta = true; 
		} else if(lepton1ID != lepton2ID) {
			myRECOevent.mixedGen = true;
		} else if(lepton1ID == 11){
			myRECOevent.electronGen = true;
		} else if(lepton1ID == 13){
			myRECOevent.muonGen = true;
		} else {
			myRECOevent.tauGen = true;
		}	
	}
	
	if(!background && abs(myRECOevent.lepton1Id)!=abs(myRECOevent.lepton2Id)){ //Two different leptons
		myRECOevent.mixedLeptons = true;    
	} else { //start doing reco
	
		//NOW THAT WE HAVE THE REAL PARTICLES, WE'LL GET THE RECO PARTICLES AND MATCH THEM
		
		edm::Handle<std::vector<pat::Jet>> recoJetsAK4;  
		iEvent.getByToken(m_AK4recoCHSJetsToken, recoJetsAK4);  
		const pat::Jet* leadJet = 0;
		const pat::Jet* subleadJet = 0;
		int jetCount = 0;
		int q1Match = 0;
		int q2Match = 0;
		
		const pat::Electron* matchedElectron = 0;
		const pat::Electron* matchedElectronL1 = 0;
		const pat::Electron* subleadElectron = 0;
		const pat::Electron* leadElectron = 0;
		
		int elCount = 0;
		int el1Match = 0;
		int el2Match = 0;
		
		const pat::Muon* matchedMuon = 0;
		const pat::Muon* matchedMuonL1 = 0;
		const pat::Muon* leadMuon = 0;
		const pat::Muon* subleadMuon = 0;
		
		int muCount = 0;
		int mu1Match = 0;
		int mu2Match = 0;
		
		math::XYZTLorentzVector combinedJetsP4;
		math::XYZTLorentzVector lepton1P4;
		math::XYZTLorentzVector lepton2P4;

		math::XYZTLorentzVector allParticlesP4Boost;
		math::XYZTLorentzVector lepton1P4Boost;
		math::XYZTLorentzVector lepton2P4Boost;
		math::XYZTLorentzVector jetsPlusLepton1P4Boost;
		math::XYZTLorentzVector jetsPlusLepton2P4Boost;
		math::XYZTLorentzVector jetsPlusLeadLeptonP4Boost;
		math::XYZTLorentzVector jetsPlusSubLeptonP4Boost;
		
		//Get jets with maximum pt, match with gen if not background
		for(std::vector<pat::Jet>::const_iterator iJet = recoJetsAK4->begin(); iJet != recoJetsAK4->end(); iJet++) {
			//Make sure jets are not around leptons
			//if ( fabs(iJet->eta()) > 2.4) continue;
			double NHF  =                iJet->neutralHadronEnergyFraction();
			double NEMF =                iJet->neutralEmEnergyFraction();
			double CHF  =                iJet->chargedHadronEnergyFraction();
			double CEMF =                iJet->chargedEmEnergyFraction();
			double NumConst =            iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
			double MUF      =            iJet->muonEnergyFraction();
			double EUF      =            iJet->electronEnergyFraction();
			double CHM      =            iJet->chargedMultiplicity(); 
			//APPLYING TIGHT QUALITY CUTS
			if (NHF > .9) continue;
			if (NEMF > .9) continue;
			if (NumConst <= 1) continue;
			if (MUF >= .8) continue; //MAKE SURE THE AREN'T MUONS
			if (EUF >= .8) continue; //MAKE SURE THE AREN'T ELECTRONS
			//ADDITIONAL CUTS BECAUSE OF TIGHT ETA CUT
			if (CHF == 0) continue;
			if (CHM == 0) continue;
			//if (CEMF > .99) continue;
			if (CEMF > .90)  continue; 
			
			if (jetCount == 0) {
				leadJet = &(*(iJet));
			} else if (jetCount == 1) {
				subleadJet = &(*(iJet));
			}
			// Match jets with gen information if not background
			if(!background){
				double match1DR = sqrt(dR2(iJet->eta(), myRECOevent.quark1Eta, iJet->phi(), myRECOevent.quark1Phi));
				double match2DR = sqrt(dR2(iJet->eta(), myRECOevent.quark2Eta, iJet->phi(), myRECOevent.quark2Phi));
				if(match1DR < 0.4 && q1Match == 0)  {
					q1Match++;
				} 
				else if(match2DR < 0.4 && q2Match == 0)  {
					q2Match++;
				}
			}
			jetCount++;
		}
	 
		//Electron Reco		
		if(background || (abs(myRECOevent.lepton1Id) == 11 && abs(myRECOevent.lepton2Id) == 11)) {
			
			myRECOevent.twoElectrons = true;
			
			edm::Handle<std::vector<pat::Electron>> highElectrons;
			iEvent.getByToken(m_highElectronToken, highElectrons);
			
			for(std::vector<pat::Electron>::const_iterator iElectron = highElectrons->begin(); iElectron != highElectrons->end(); iElectron++) {
				if(fabs(iElectron->eta()) > 2.4) continue;
				if(iElectron->pt() < 53 ) continue;
				const vid::CutFlowResult* vidResult =  iElectron->userData<vid::CutFlowResult>("heepElectronID_HEEPV70");
				if(background && vidResult == NULL) {
					std::cout << "ERROR CANNOT FIND ELECTRON VID RESULTS" << std::endl;
					continue;
				}
				const bool heepIDVID = vidResult->cutFlowPassed();
				if (heepIDVID == false) continue;

				if (elCount == 0) {
					leadElectron = &(*(iElectron));
				}
				if (elCount == 1) {
					subleadElectron = &(*(iElectron));
				}
				if (elCount == 2){
					myRECOevent.extraLeptons = true;
				}
				// If not background, do gen matching
				if(!background){ 
					double match1DR = sqrt(dR2(iElectron->eta(), myRECOevent.lepton1Eta, iElectron->phi(), myRECOevent.lepton1Phi));
					double match2DR = sqrt(dR2(iElectron->eta(), myRECOevent.lepton2Eta, iElectron->phi(), myRECOevent.lepton2Phi));
					
					if(el1Match == 0 && match1DR < 0.1) {
						el1Match++;
						matchedElectronL1 = &(*(iElectron));
					}
					else if(el2Match == 0 && match2DR < 0.1)  {
						matchedElectron = &(*(iElectron));
						el2Match++; 
					}
				}
				elCount++;
			}
	  
	  	    //If background, check that there are two jets and two electrons, otherwise check that particles match gen particles
			if((leadJet != 0 && subleadJet != 0 && leadElectron != 0 && subleadElectron != 0 && el1Match != 0 && el2Match != 0 && q1Match != 0 && q2Match != 0) ||
				(background && leadJet != 0 && subleadJet != 0 && leadElectron != 0 && subleadElectron != 0)){
				std::cout << "lead jet" << leadJet->p4() << ", "<< leadJet->pt() << std::endl;
				std::cout << "sublead jet" << subleadJet->p4() << ", "<< subleadJet->pt() << std::endl;
				std::cout << "lead lepton" << leadElectron->p4() << ", "<< leadElectron->pt() << std::endl;
				std::cout << "sublead lepton" << subleadElectron->p4() << ", "<< subleadElectron->pt() << std::endl;
				//calculate boosts
				combinedJetsP4 = subleadJet->p4() + leadJet->p4();
				std::cout << "combined" << combinedJetsP4 << std::endl;
				allParticlesP4Boost = -(combinedJetsP4 + leadElectron->p4() + subleadElectron->p4());
				jetsPlusLeadLeptonP4Boost = -(combinedJetsP4 + leadElectron->p4());
				jetsPlusSubLeptonP4Boost = -(combinedJetsP4 + subleadElectron->p4());
				//boosts of gen particles
				if(!background){
					lepton1P4 = matchedElectronL1->p4();
					lepton2P4 = matchedElectron->p4();
					
					jetsPlusLepton1P4Boost = -(combinedJetsP4 + lepton1P4);
					jetsPlusLepton2P4Boost = -(combinedJetsP4 + lepton2P4);
					lepton1P4Boost = -(lepton1P4);
					lepton2P4Boost = -(lepton2P4);
				}
				
				
				myRECOevent.passedElectronReco = true;
				
				//Collect information on reconstructed particles
				myRECOevent.leadJetRecoEta = leadJet->eta();
				myRECOevent.leaJetRecoPhi = leadJet->phi();
				myRECOevent.leadJetRecoMass = leadJet->p4().mass();
				myRECOevent.leadJetRecoPt = leadJet->pt();

				myRECOevent.subJetRecoEta = subleadJet->eta();
				myRECOevent.subJetRecoPhi = subleadJet->phi();
				myRECOevent.subJetRecoMass = subleadJet->p4().mass();
				myRECOevent.subJetRecoPt = subleadJet->pt();

				myRECOevent.subRecoElectronEta = subleadElectron->eta();
				myRECOevent.subRecoElectronPhi = subleadElectron->phi();
				myRECOevent.subRecoElectronMass = subleadElectron->p4().mass();
				myRECOevent.subRecoElectronPt = subleadElectron->pt();

				myRECOevent.leadRecoElectronEta = leadElectron->eta();
				myRECOevent.leadRecoElectronPhi = leadElectron->phi();
				myRECOevent.leadRecoElectronMass = leadElectron->p4().mass();
				myRECOevent.leadRecoElectronPt = leadElectron->pt();

				
				myRECOevent.subElectronleadElectronRecodr2 = dR2(subleadElectron->eta(), leadElectron->eta(), subleadElectron->phi(), leadElectron->phi());
				myRECOevent.subElectronleadJRecodr2 = dR2(subleadElectron->eta(), leadJet->eta(), subleadElectron->phi(), leadJet->phi());
				myRECOevent.subElectronsubJRecodr2 = dR2(subleadElectron->eta(), subleadJet->eta(), subleadElectron->phi(), subleadJet->phi());
				myRECOevent.subleadElectronJJRecodr2 = dR2(subleadElectron->eta(), (subleadJet->p4()+leadJet->p4()).eta(), subleadElectron->phi(), (subleadJet->p4()+leadJet->p4()).phi());
				myRECOevent.leadElectronleadJRecodr2 = dR2(leadElectron->eta(), leadJet->eta(), leadElectron->phi(), leadJet->phi());
				myRECOevent.leadElectronsubJRecodr2 = dR2(leadElectron->eta(), subleadJet->eta(), leadElectron->phi(), subleadJet->phi());
				myRECOevent.leadElectronJJRecodr2 = dR2(leadElectron->eta(), (subleadJet->p4()+leadJet->p4()).eta(), leadElectron->phi(), (subleadJet->p4()+leadJet->p4()).phi());
				myRECOevent.leadJsubJdr2 = dR2(leadJet->eta(), subleadJet->eta(), leadJet->phi(), subleadJet->phi());

				myRECOevent.leadElectronsubElectronRecoMass = (subleadElectron->p4() + leadElectron->p4()).mass();
				myRECOevent.subElectronleadJsubJRecoMass = (subleadElectron->p4() + leadJet->p4() + subleadJet->p4()).mass();
				myRECOevent.leadElectronleadJsubJRecoMass = (leadElectron->p4() + leadJet->p4() + subleadJet->p4()).mass();
				
				myRECOevent.subRecoElectronDR = sqrt(dR2(subleadElectron->eta(), combinedJetsP4.eta(), subleadElectron->phi(), combinedJetsP4.phi()));
				myRECOevent.subRecoElectronEtaWR = (subleadElectron->p4()+allParticlesP4Boost).eta();
				
				myRECOevent.leadRecoElectronDR = sqrt(dR2(leadElectron->eta(), combinedJetsP4.eta(), leadElectron->phi(), combinedJetsP4.phi()));
				myRECOevent.leadRecoElectronEtaWR = (leadElectron->p4()+allParticlesP4Boost).eta();
				
				myRECOevent.fullRecoMassElectron = (leadElectron->p4() + subleadElectron->p4() + leadJet->p4() + subleadJet->p4()).mass();
				
				//Neural network input
				double predictIn[1][8] = {{myRECOevent.subRecoElectronEta,
				myRECOevent.subRecoElectronEtaWR,
				myRECOevent.subRecoElectronDR,
				myRECOevent.subRecoElectronPt/myRECOevent.fullRecoMassElectron, 
				myRECOevent.leadRecoElectronEta,
				myRECOevent.leadRecoElectronEtaWR,
				myRECOevent.leadRecoElectronDR,
				myRECOevent.leadRecoElectronPt/myRECOevent.fullRecoMassElectron}};
				
				//Neural network output
				double predictOut[1][1] = {{0.0}};
				
				//Collect prediction for resolved region
				std::cout << "resolved" << std::endl;
				networkResolved.predict(&predictIn[0][0], &predictOut[0][0], 1);
				
				if(predictOut[0][0]==1.0){
					myRECOevent.nnResolvedPickedLeadElectron = true;
				} else {
					myRECOevent.nnResolvedPickedSubLeadElectron = true;
				}
				
				std::cout << "super resolved" << std::endl;
				//Collect prediction for super resolved region
				networkSuperResolved.predict(&predictIn[0][0], &predictOut[0][0], 1);

				if(predictOut[0][0]==1.0){
					myRECOevent.nnSuperResolvedPickedLeadElectron = true;
				} else {
					myRECOevent.nnSuperResolvedPickedSubLeadElectron = true;
				}
				
				//Check whether the event passes the reco cuts which filter background
				myRECOevent.checkCutsElectron();
				
				//Collect information on matced leptons if background
				if(!background){
					myRECOevent.matchedElectronleadJsubJRecoMass = (matchedElectron->p4() + leadJet->p4() + subleadJet->p4()).mass();
					myRECOevent.electron1RecoMass = (leadJet->p4() + subleadJet->p4() + matchedElectronL1->p4()).mass();
					myRECOevent.electron2RecoMass = (leadJet->p4() + subleadJet->p4() + matchedElectron->p4()).mass();
					
					
					myRECOevent.match1ElectronEta = matchedElectronL1->eta();
					myRECOevent.match1ElectronPhi = matchedElectronL1->phi();
					myRECOevent.match1ElectronDPhi = dPhi(matchedElectronL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1ElectronDR = sqrt(dR2(matchedElectronL1->eta(), combinedJetsP4.eta(), matchedElectronL1->phi(), combinedJetsP4.phi()));
					myRECOevent.match1ElectronPt = matchedElectronL1->pt();
					
					myRECOevent.match2ElectronEta = matchedElectron->eta();
					myRECOevent.match2ElectronPhi = matchedElectron->phi();
					myRECOevent.match2ElectronDPhi = dPhi(matchedElectron->phi(), combinedJetsP4.phi());
					myRECOevent.match2ElectronDR = sqrt(dR2(matchedElectron->eta(), combinedJetsP4.eta(), matchedElectron->phi(), combinedJetsP4.phi()));
					myRECOevent.match2ElectronPt = matchedElectron->pt();
					
					
					myRECOevent.match1ElectronEtaL1 = (matchedElectronL1->p4()+lepton1P4Boost).eta();
					myRECOevent.match1ElectronPhiL1 = (matchedElectronL1->p4()+lepton1P4Boost).phi();
					myRECOevent.match1ElectronDPhiL1 = dPhi(matchedElectronL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1ElectronDRL1 = sqrt(dR2((matchedElectronL1->p4()+lepton1P4Boost).eta(), (combinedJetsP4+lepton1P4Boost).eta(), (matchedElectronL1->p4()+lepton1P4Boost).phi(), (combinedJetsP4+lepton1P4Boost).phi()));
					myRECOevent.match1ElectronPtL1 = (matchedElectronL1->p4()+lepton1P4Boost).pt();

					myRECOevent.match2ElectronEtaL2 = (matchedElectron->p4()+lepton2P4Boost).eta();
					myRECOevent.match2ElectronPhiL2 = (matchedElectron->p4()+lepton2P4Boost).phi();
					myRECOevent.match2ElectronDPhiL2 = dPhi(matchedElectron->phi(), combinedJetsP4.phi());
					myRECOevent.match2ElectronDRL2 = sqrt(dR2((matchedElectron->p4()+lepton2P4Boost).eta(), (combinedJetsP4+lepton2P4Boost).eta(), (matchedElectron->p4()+lepton2P4Boost).phi(), (combinedJetsP4+lepton2P4Boost).phi()));
					myRECOevent.match2ElectronPtL2 = (matchedElectron->p4()+lepton2P4Boost).pt();
					
					myRECOevent.match1ElectronEtaJJL1 = (matchedElectronL1->p4()+jetsPlusLepton1P4Boost).eta();
					myRECOevent.match1ElectronPhiJJL1 = (matchedElectronL1->p4()+jetsPlusLepton1P4Boost).phi();
					myRECOevent.match1ElectronDPhiJJL1 = dPhi(matchedElectronL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1ElectronDRJJL1 = sqrt(dR2((matchedElectronL1->p4()+jetsPlusLepton1P4Boost).eta(), (combinedJetsP4+jetsPlusLepton1P4Boost).eta(), (matchedElectronL1->p4()+jetsPlusLepton1P4Boost).phi(), (combinedJetsP4+jetsPlusLepton1P4Boost).phi()));
					myRECOevent.match1ElectronPtJJL1 = (matchedElectronL1->p4()+jetsPlusLepton1P4Boost).pt();
					
					myRECOevent.match2ElectronEtaJJL2 = (matchedElectron->p4()+jetsPlusLepton2P4Boost).eta();
					myRECOevent.match2ElectronPhiJJL2 = (matchedElectron->p4()+jetsPlusLepton2P4Boost).phi();
					myRECOevent.match2ElectronDPhiJJL2 = dPhi(matchedElectron->phi(), combinedJetsP4.phi());
					myRECOevent.match2ElectronDRJJL2 = sqrt(dR2((matchedElectron->p4()+jetsPlusLepton2P4Boost).eta(), (combinedJetsP4+jetsPlusLepton2P4Boost).eta(), (matchedElectron->p4()+jetsPlusLepton2P4Boost).phi(), (combinedJetsP4+jetsPlusLepton2P4Boost).phi()));
					myRECOevent.match2ElectronPtJJL2 = (matchedElectron->p4()+jetsPlusLepton2P4Boost).pt();
					
					myRECOevent.match1ElectronEtaWR = (matchedElectronL1->p4()+allParticlesP4Boost).eta();
					myRECOevent.match1ElectronPhiWR = (matchedElectronL1->p4()+allParticlesP4Boost).phi();
					myRECOevent.match1ElectronDPhiWR = dPhi(matchedElectronL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1ElectronDRWR = sqrt(dR2((matchedElectronL1->p4()+allParticlesP4Boost).eta(), (combinedJetsP4+allParticlesP4Boost).eta(), (matchedElectronL1->p4()+allParticlesP4Boost).phi(), (combinedJetsP4+allParticlesP4Boost).phi()));
					myRECOevent.match1ElectronPtWR = (matchedElectronL1->p4()+allParticlesP4Boost).pt();

					myRECOevent.match2ElectronEtaWR = (matchedElectron->p4()+allParticlesP4Boost).eta();
					myRECOevent.match2ElectronPhiWR = (matchedElectron->p4()+allParticlesP4Boost).phi();
					myRECOevent.match2ElectronDPhiWR = dPhi(matchedElectron->phi(), combinedJetsP4.phi());
					myRECOevent.match2ElectronDRWR = sqrt(dR2((matchedElectron->p4()+allParticlesP4Boost).eta(), (combinedJetsP4+allParticlesP4Boost).eta(), (matchedElectron->p4()+allParticlesP4Boost).phi(), (combinedJetsP4+allParticlesP4Boost).phi()));
					myRECOevent.match2ElectronPtWR = (matchedElectron->p4()+allParticlesP4Boost).pt();
					
					myRECOevent.leadJsubJRecoMass = (leadJet->p4() + subleadJet->p4()).mass();				
					
					myRECOevent.sphericityElectron1 = transverseSphericity(matchedElectronL1->p4(), leadJet->p4(), subleadJet->p4());
					myRECOevent.sphericityElectron2 = transverseSphericity(matchedElectron->p4(), leadJet->p4(), subleadJet->p4());	 
					
					//Save electron data to a text file
					if(myRECOevent.nMinusOneFailElectron.size()==0 && m_genTrainData){
						saveElectronData(&myRECOevent, (matchedElectronL1->p4() + leadJet->p4() + subleadJet->p4()).mass(),(matchedElectron->p4() + leadJet->p4() + subleadJet->p4()).mass());
					}	
				}
			}	
     	}
			
		//Perform reco on muons
		if(background || (abs(myRECOevent.lepton1Id) == 13 && (abs(myRECOevent.lepton2Id) == 13))) {
			myRECOevent.twoMuons = true;
			
			edm::Handle<std::vector<pat::Muon>> highMuons;
			iEvent.getByToken(m_highMuonToken, highMuons);
			
			for(std::vector<pat::Muon>::const_iterator iMuon = highMuons->begin(); iMuon != highMuons->end(); iMuon++) {
				if( background && (iMuon->tunePMuonBestTrack()->pt() < 53 || fabs(iMuon->eta()) > 2.4) ) continue; //preliminary pt cut to speed the loop, and the eta cut
				if(!background || (( iMuon->isHighPtMuon(*myEvent.PVertex)) && (iMuon->isolationR03().sumPt/iMuon->pt() < .1))) {
					if (muCount == 0) {
						leadMuon = &(*(iMuon));
					}
					if (muCount == 1) {
						subleadMuon = &(*(iMuon));
					}
					if (muCount == 2){
						myRECOevent.extraLeptons = true;
					}
					double match1DR = sqrt(dR2(iMuon->eta(), myRECOevent.lepton1Eta, iMuon->phi(), myRECOevent.lepton1Phi));
					double match2DR = sqrt(dR2(iMuon->eta(), myRECOevent.lepton2Eta, iMuon->phi(), myRECOevent.lepton2Phi));
					
					if(mu1Match == 0 && match1DR < 0.1) {
						mu1Match++;
						matchedMuonL1 = &(*(iMuon));
					}
					else if(mu2Match == 0 && match2DR < 0.1)  {
						matchedMuon = &(*(iMuon));
						mu2Match++; 
					}
					muCount++;
				}
			}
		  
		    //Check whether we have a viable muon event
			if((leadJet != 0 && subleadJet != 0 && leadMuon != 0 && subleadMuon != 0 && mu1Match != 0 && mu2Match != 0 && q1Match != 0 && q2Match != 0) ||
				(background && leadJet != 0 && subleadJet != 0 && leadMuon != 0 && subleadMuon != 0)) {
				
				std::cout << "lead jet" << leadJet->p4() << ", "<< leadJet->pt() << std::endl;
				std::cout << "sublead jet" << subleadJet->p4() << ", "<< subleadJet->pt() << std::endl;
				std::cout << "lead lepton" << leadMuon->p4() << ", "<< leadMuon->pt() << std::endl;
				std::cout << "sublead lepton" << subleadMuon->p4() << ", "<< subleadMuon->pt() << std::endl;
				
				//Boosting information
				combinedJetsP4 = subleadJet->p4() + leadJet->p4();
				allParticlesP4Boost = -(combinedJetsP4 + leadMuon->p4() + subleadMuon->p4());
				jetsPlusLeadLeptonP4Boost = -(combinedJetsP4 + leadMuon->p4());
				jetsPlusSubLeptonP4Boost = -(combinedJetsP4 + subleadMuon->p4());
				//Boosting information for matched muons
				if(!background){
					lepton1P4 = matchedMuonL1->p4();
					lepton2P4 = matchedMuon->p4();
					jetsPlusLepton1P4Boost = -(combinedJetsP4 + lepton1P4);
					jetsPlusLepton2P4Boost = -(combinedJetsP4 + lepton2P4);
					lepton1P4Boost = -(lepton1P4);
					lepton2P4Boost = -(lepton2P4);
				}
				
				//Collect reco muon information
				myRECOevent.passedMuonReco = true;
				
				myRECOevent.leadJetRecoEta = leadJet->eta();
				myRECOevent.leaJetRecoPhi = leadJet->phi();
				myRECOevent.leadJetRecoMass = leadJet->p4().mass();
				myRECOevent.leadJetRecoPt = leadJet->pt();

				myRECOevent.subJetRecoEta = subleadJet->eta();
				myRECOevent.subJetRecoPhi = subleadJet->phi();
				myRECOevent.subJetRecoMass = subleadJet->p4().mass();
				myRECOevent.subJetRecoPt = subleadJet->pt();

				myRECOevent.subRecoMuonEta = subleadMuon->eta();
				myRECOevent.subRecoMuonPhi = subleadMuon->phi();
				myRECOevent.subRecoMuonMass = subleadMuon->p4().mass();
				myRECOevent.subRecoMuonPt = subleadMuon->pt();

				myRECOevent.leadRecoMuonEta = leadMuon->eta();
				myRECOevent.leadRecoMuonPhi = leadMuon->phi();
				myRECOevent.leadRecoMuonMass = leadMuon->p4().mass();
				myRECOevent.leadRecoMuonPt = leadMuon->pt();

				myRECOevent.subMuonleadMuonRecodr2 = dR2(subleadMuon->eta(), leadMuon->eta(), subleadMuon->phi(), leadMuon->phi());
				myRECOevent.subMuonleadJRecodr2 = dR2(subleadMuon->eta(), leadJet->eta(), subleadMuon->phi(), leadJet->phi());
				myRECOevent.subMuonsubJRecodr2 = dR2(subleadMuon->eta(), subleadJet->eta(), subleadMuon->phi(), subleadJet->phi());
				myRECOevent.subleadMuonJJRecodr2 = dR2(subleadMuon->eta(), (subleadJet->p4()+leadJet->p4()).eta(),subleadMuon->phi(), (subleadJet->p4()+leadJet->p4()).phi());
				myRECOevent.leadMuonleadJRecodr2 = dR2(leadMuon->eta(), leadJet->eta(), leadMuon->phi(), leadJet->phi());
				myRECOevent.leadMuonsubJRecodr2 = dR2(leadMuon->eta(), subleadJet->eta(), leadMuon->phi(), subleadJet->phi());
				myRECOevent.leadJsubJdr2 = dR2(leadJet->eta(), subleadJet->eta(), leadJet->phi(), subleadJet->phi());
				myRECOevent.leadMuonJJRecodr2 = dR2(leadMuon->eta(), (subleadJet->p4()+leadJet->p4()).eta(),leadMuon->phi(), (subleadJet->p4()+leadJet->p4()).phi());

				myRECOevent.leadMuonsubMuonRecoMass = (subleadMuon->p4() + leadMuon->p4()).mass();
				myRECOevent.subMuonleadJsubJRecoMass = (subleadMuon->p4() + leadJet->p4() + subleadJet->p4()).mass();
				myRECOevent.leadMuonleadJsubJRecoMass = (leadMuon->p4() + leadJet->p4() + subleadJet->p4()).mass();

				myRECOevent.leadJsubJRecoMass = (leadJet->p4() + subleadJet->p4()).mass();

				myRECOevent.fullRecoMassMuon = (leadMuon->p4() + subleadMuon->p4() + leadJet->p4() + subleadJet->p4()).mass();
				
				myRECOevent.subRecoMuonDR = sqrt(dR2(subleadMuon->eta(), combinedJetsP4.eta(), subleadMuon->phi(), combinedJetsP4.phi()));
				myRECOevent.subRecoMuonEtaWR = (subleadMuon->p4()+allParticlesP4Boost).eta();
				
				myRECOevent.leadRecoMuonDR = sqrt(dR2(leadMuon->eta(), combinedJetsP4.eta(), leadMuon->phi(), combinedJetsP4.phi()));
				myRECOevent.leadRecoMuonEtaWR = (leadMuon->p4()+allParticlesP4Boost).eta();
				
				//Neural network input
				double predictIn[1][8] = {{myRECOevent.subRecoMuonEta,
				myRECOevent.subRecoMuonEtaWR,
				myRECOevent.subRecoMuonDR,
				myRECOevent.subRecoMuonPt/myRECOevent.fullRecoMassMuon, 
				myRECOevent.leadRecoMuonEta,
				myRECOevent.leadRecoMuonEtaWR,
				myRECOevent.leadRecoMuonDR,
				myRECOevent.leadRecoMuonPt/myRECOevent.fullRecoMassMuon}};
				
				//Neural network output
				double predictOut[1][1] = {{0.0}};
				
				//Resolved network prediction
				std::cout << "resolved" << std::endl;
				networkResolved.predict(&predictIn[0][0], &predictOut[0][0], 1);
				
				
				if(predictOut[0][0]==1.0){
					myRECOevent.nnResolvedPickedLeadMuon = true;
				} else {
					myRECOevent.nnResolvedPickedSubLeadMuon = true;
				}
				
				//Super Resolved network prediction
				std::cout << "super resolved" << std::endl;
				networkSuperResolved.predict(&predictIn[0][0], &predictOut[0][0], 1);

				
				if(predictOut[0][0]==1.0){
					myRECOevent.nnSuperResolvedPickedLeadMuon = true;
				} else {
					myRECOevent.nnSuperResolvedPickedSubLeadMuon = true;
				}
				
				//Check whether the muons passed reco
				myRECOevent.checkCutsMuon();
				
				//Extract information on matched muons if not background
				if(!background){
					myRECOevent.matchedMuonleadJsubJRecoMass = (matchedMuon->p4() + leadJet->p4() + subleadJet->p4()).mass();
					myRECOevent.muon1RecoMass = (matchedMuonL1->p4()+leadJet->p4() + subleadJet->p4()).mass();
					myRECOevent.muon2RecoMass = (matchedMuon->p4()+leadJet->p4() + subleadJet->p4()).mass();
					
					myRECOevent.match1MuonEta = matchedMuonL1->eta();
					myRECOevent.match1MuonPhi = matchedMuonL1->phi();
					myRECOevent.match1MuonDPhi = dPhi(matchedMuonL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1MuonDR = sqrt(dR2(matchedMuonL1->eta(), combinedJetsP4.eta(), matchedMuonL1->phi(), combinedJetsP4.phi()));
					myRECOevent.match1MuonPt = matchedMuonL1->pt();

					myRECOevent.match2MuonEta = matchedMuon->eta();
					myRECOevent.match2MuonPhi = matchedMuon->phi();
					myRECOevent.match2MuonDPhi = dPhi(matchedMuon->phi(), combinedJetsP4.phi());
					myRECOevent.match2MuonDR = sqrt(dR2(matchedMuon->eta(), combinedJetsP4.eta(), matchedMuon->phi(), combinedJetsP4.phi()));
					myRECOevent.match2MuonPt = matchedMuon->pt();
					

					myRECOevent.match1MuonEtaL1 = (matchedMuonL1->p4()+lepton1P4Boost).eta();
					myRECOevent.match1MuonPhiL1 = (matchedMuonL1->p4()+lepton1P4Boost).phi();
					myRECOevent.match1MuonDPhiL1 = dPhi(matchedMuonL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1MuonDRL1 = sqrt(dR2((matchedMuonL1->p4()+lepton1P4Boost).eta(), (combinedJetsP4+lepton1P4Boost).eta(), (matchedMuonL1->p4()+lepton1P4Boost).phi(), (combinedJetsP4+lepton1P4Boost).phi()));
					myRECOevent.match1MuonPtL1 = (matchedMuonL1->p4()+lepton1P4Boost).pt();

					myRECOevent.match2MuonEtaL2 = (matchedMuon->p4()+lepton2P4Boost).eta();
					myRECOevent.match2MuonPhiL2 = (matchedMuon->p4()+lepton2P4Boost).phi();
					myRECOevent.match2MuonDPhiL2 = dPhi(matchedMuon->phi(), combinedJetsP4.phi());
					myRECOevent.match2MuonDRL2 = sqrt(dR2((matchedMuon->p4()+lepton2P4Boost).eta(), (combinedJetsP4+lepton2P4Boost).eta(), (matchedMuon->p4()+lepton2P4Boost).phi(), (combinedJetsP4+lepton2P4Boost).phi()));
					myRECOevent.match2MuonPtL2 = (matchedMuon->p4()+lepton2P4Boost).pt();
					
					myRECOevent.match1MuonEtaJJL1 = (matchedMuonL1->p4()+jetsPlusLepton1P4Boost).eta();
					myRECOevent.match1MuonPhiJJL1 = (matchedMuonL1->p4()+jetsPlusLepton1P4Boost).phi();
					myRECOevent.match1MuonDPhiJJL1 = dPhi(matchedMuonL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1MuonDRJJL1 = sqrt(dR2((matchedMuonL1->p4()+jetsPlusLepton1P4Boost).eta(), (combinedJetsP4+jetsPlusLepton1P4Boost).eta(), (matchedMuonL1->p4()+jetsPlusLepton1P4Boost).phi(), (combinedJetsP4+jetsPlusLepton1P4Boost).phi()));
					myRECOevent.match1MuonPtJJL1 = (matchedMuonL1->p4()+jetsPlusLepton1P4Boost).pt();

					myRECOevent.match2MuonEtaJJL2 = (matchedMuon->p4()+jetsPlusLepton2P4Boost).eta();
					myRECOevent.match2MuonPhiJJL2 = (matchedMuon->p4()+jetsPlusLepton2P4Boost).phi();
					myRECOevent.match2MuonDPhiJJL2 = dPhi(matchedMuon->phi(), combinedJetsP4.phi());
					myRECOevent.match2MuonDRJJL2 = sqrt(dR2((matchedMuon->p4()+jetsPlusLepton2P4Boost).eta(), (combinedJetsP4+jetsPlusLepton2P4Boost).eta(), (matchedMuon->p4()+jetsPlusLepton2P4Boost).phi(), (combinedJetsP4+jetsPlusLepton2P4Boost).phi()));
					myRECOevent.match2MuonPtJJL2 = (matchedMuon->p4()+jetsPlusLepton2P4Boost).pt();
					
					myRECOevent.match1MuonEtaWR = (matchedMuonL1->p4()+allParticlesP4Boost).eta();
					myRECOevent.match1MuonPhiWR = (matchedMuonL1->p4()+allParticlesP4Boost).phi();
					myRECOevent.match1MuonDPhiWR = dPhi(matchedMuonL1->phi(), combinedJetsP4.phi());
					myRECOevent.match1MuonDRWR = sqrt(dR2((matchedMuonL1->p4()+allParticlesP4Boost).eta(), (combinedJetsP4+allParticlesP4Boost).eta(), (matchedMuonL1->p4()+allParticlesP4Boost).phi(), (combinedJetsP4+allParticlesP4Boost).phi()));
					myRECOevent.match1MuonPtWR = (matchedMuonL1->p4()+allParticlesP4Boost).pt();

					myRECOevent.match2MuonEtaWR = (matchedMuon->p4()+allParticlesP4Boost).eta();
					myRECOevent.match2MuonPhiWR = (matchedMuon->p4()+allParticlesP4Boost).phi();
					myRECOevent.match2MuonDPhiWR = dPhi(matchedMuon->phi(), combinedJetsP4.phi());
					myRECOevent.match2MuonDRWR = sqrt(dR2((matchedMuon->p4()+allParticlesP4Boost).eta(), (combinedJetsP4+allParticlesP4Boost).eta(), (matchedMuon->p4()+allParticlesP4Boost).phi(), (combinedJetsP4+allParticlesP4Boost).phi()));
					myRECOevent.match2MuonPtWR = (matchedMuon->p4()+allParticlesP4Boost).pt();
					
					myRECOevent.sphericityMuon1 = transverseSphericity(matchedMuonL1->p4(), leadJet->p4(), subleadJet->p4());//+jetsPlusLepton1P4Boost);
					myRECOevent.sphericityMuon2 = transverseSphericity(matchedMuon->p4(), leadJet->p4(), subleadJet->p4());//+jetsPlusLepton1P4Boost);					
					
					
					//Save muon data to a text file
					if (myRECOevent.nMinusOneFailMuon.size()==0 && m_genTrainData){
						saveMuonData(&myRECOevent, (matchedMuonL1->p4() + leadJet->p4() + subleadJet->p4()).mass(),(matchedMuon->p4() + leadJet->p4() + subleadJet->p4()).mass());
					}	
				}
			}		
		}
		
		//Check some other ways in which the event may fail
		if(subleadJet == 0){
			myRECOevent.badJets = true;
		} else if(leadMuon != 0 && subleadMuon == 0){
			myRECOevent.oneLepton = true;
		} else if(leadElectron != 0 && subleadElectron == 0){
			myRECOevent.oneLepton = true;
		}
		
		if((background && leadJet != 0 && subleadJet != 0 && leadMuon != 0 && leadElectron != 0 && subleadElectron == 0 && subleadMuon == 0)){
			myRECOevent.mixedLeptons = true;
		} else if(background && leadJet != 0 && subleadJet != 0 && leadMuon != 0 && leadElectron != 0 && subleadElectron != 0 && subleadMuon == 0){
			myRECOevent.extraLeptons = true;
		} else if(background && leadJet != 0 && subleadJet != 0 && leadMuon != 0 && leadElectron != 0 && subleadElectron == 0 && subleadMuon != 0){
			myRECOevent.extraLeptons = true;
		}
	}
	//Fill the histograms
    m_allEvents.fill(myRECOevent);

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

double WR_MASS_PLOT::transverseSphericity(math::XYZTLorentzVector p1, math::XYZTLorentzVector p2, math::XYZTLorentzVector p3){
	double sphericity [3*3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	double momentumArray [3*3] = {p1.Px(), p1.Py(), p1.Pz(), p2.Px(), p2.Py(), p2.Pz(), p3.Px(), p3.Py(), p3.Pz()};
	double pi2 = pow(p1.Px(),2) + pow(p1.Py(),2) + pow(p1.Pz(),2) + pow(p2.Px(),2) + pow(p2.Py(),2) + pow(p2.Pz(),2) + pow(p3.Px(),2) + pow(p3.Py(),2) + pow(p3.Pz(),2);

	for(int a=0; a<3; a++){
		for(int b=0; b<3; b++){
			sphericity[a+b*3]+=momentumArray[0+a]*momentumArray[0+b];
			sphericity[a+b*3]+=momentumArray[3+a]*momentumArray[3+b];
			sphericity[a+b*3]+=momentumArray[6+a]*momentumArray[6+b];
			sphericity[a+b*3]/=pi2;
		}
	}
	
	TMatrixDSym sphericityTensor(3, sphericity);
	TMatrixDSymEigen sphericityEigenvalues(sphericityTensor);
	TVectorD eigenval = sphericityEigenvalues.GetEigenValues();
	return(2*eigenval[1]/(eigenval[0]+eigenval[1])); 
}

void WR_MASS_PLOT::saveElectronData(eventBits * myRECOevent,double matched1Mass, double matched2Mass){
		std::ofstream myfile;
		myfile.open (m_dataSaveFile, std::ios_base::app);
		myfile << myRECOevent->match1ElectronEta << "\t";					
		myfile << myRECOevent->match1ElectronEtaWR << "\t";
		myfile << myRECOevent->match1ElectronDPhi << "\t";
		myfile << myRECOevent->match1ElectronDR << "\t";
		myfile << myRECOevent->match1ElectronPt << "\t";
		myfile << myRECOevent->sphericityElectron1 << "\t";
		myfile << matched1Mass << "\t";
		myfile << myRECOevent->match2ElectronEta << "\t";
		myfile << myRECOevent->match2ElectronEtaWR << "\t";
		myfile << myRECOevent->match2ElectronDPhi << "\t";
		myfile << myRECOevent->match2ElectronDR << "\t";
		myfile << myRECOevent->match2ElectronPt << "\t";
		myfile << myRECOevent->sphericityElectron2 << "\t";
		myfile << matched2Mass << "\t";
		myfile << myRECOevent->fullRecoMassElectron << "\t";
		myfile << 1.0 << "\t";
		myfile << round(myRECOevent->WRMass/100.0)*100.0 << "\t";
		myfile << round(myRECOevent->NMass/100.0)*100.0 << "\n";

		
		myfile << myRECOevent->match2ElectronEta << "\t";
		myfile << myRECOevent->match2ElectronEtaWR << "\t";
		myfile << myRECOevent->match2ElectronDPhi << "\t";
		myfile << myRECOevent->match2ElectronDR << "\t";
		myfile << myRECOevent->match2ElectronPt << "\t";
		myfile << myRECOevent->sphericityElectron2 << "\t";
		myfile << matched2Mass << "\t";
		myfile << myRECOevent->match1ElectronEta << "\t";					
		myfile << myRECOevent->match1ElectronEtaWR << "\t";
		myfile << myRECOevent->match1ElectronDPhi << "\t";
		myfile << myRECOevent->match1ElectronDR << "\t";
		myfile << myRECOevent->match1ElectronPt << "\t";
		myfile << myRECOevent->sphericityElectron1 << "\t";
		myfile << matched1Mass << "\t";
		myfile << myRECOevent->fullRecoMassElectron << "\t";
		myfile << 0.0 << "\t";
		myfile << round(myRECOevent->WRMass/100.0)*100.0 << "\t";
		myfile << round(myRECOevent->NMass/100.0)*100.0 << "\n";

		myfile.close();
}


void WR_MASS_PLOT::saveMuonData(eventBits * myRECOevent, double matched1Mass, double matched2Mass){
		std::ofstream myfile;
		myfile.open (m_dataSaveFile, std::ios_base::app);
		myfile << myRECOevent->match1MuonEta << "\t";					
		myfile << myRECOevent->match1MuonEtaWR << "\t";
		myfile << myRECOevent->match1MuonDPhi << "\t";
		myfile << myRECOevent->match1MuonDR << "\t";
		myfile << myRECOevent->match1MuonPt << "\t";
		myfile << myRECOevent->sphericityMuon1 << "\t";
		myfile << matched1Mass << "\t";
		myfile << myRECOevent->match2MuonEta << "\t";
		myfile << myRECOevent->match2MuonEtaWR << "\t";
		myfile << myRECOevent->match2MuonDPhi << "\t";
		myfile << myRECOevent->match2MuonDR << "\t";
		myfile << myRECOevent->match2MuonPt << "\t";
		myfile << myRECOevent->sphericityMuon2 << "\t";
		myfile << matched2Mass << "\t";
		myfile << myRECOevent->fullRecoMassMuon << "\t";
		myfile << 1.0 << "\t";
		myfile << round(myRECOevent->WRMass/100.0)*100.0 << "\t";
		myfile << round(myRECOevent->NMass/100.0)*100.0 << "\n";

		
		myfile << myRECOevent->match2MuonEta << "\t";
		myfile << myRECOevent->match2MuonEtaWR << "\t";
		myfile << myRECOevent->match2MuonDPhi << "\t";
		myfile << myRECOevent->match2MuonDR << "\t";
		myfile << myRECOevent->match2MuonPt << "\t";
		myfile << myRECOevent->sphericityMuon2 << "\t";
		myfile << matched2Mass << "\t";
		myfile << myRECOevent->match1MuonEta << "\t";					
		myfile << myRECOevent->match1MuonEtaWR << "\t";
		myfile << myRECOevent->match1MuonDPhi << "\t";
		myfile << myRECOevent->match1MuonDR << "\t";
		myfile << myRECOevent->match1MuonPt << "\t";
		myfile << myRECOevent->sphericityMuon1 << "\t";
		myfile << matched1Mass << "\t";
		myfile << myRECOevent->fullRecoMassMuon << "\t";
		myfile << 0.0 << "\t";
		myfile << round(myRECOevent->WRMass/100.0)*100.0 << "\t";
		myfile << round(myRECOevent->NMass/100.0)*100.0 << "\n";

		myfile.close();
}


// ------------ method called once each job just before starting event loop  ------------
void
WR_MASS_PLOT::beginJob() {
	edm::Service<TFileService> fs; 
	m_allEvents.book((fs->mkdir("allEvents")));
}

// ------------ method called once each job just after ending the event loop  ------------
void
WR_MASS_PLOT::endJob() {
	
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