#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveLabel.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include <iostream>

//Collects all the one-d and two-d histograms input into the function call from the many root files created while the analysis is running
void extractHistos(TH1D ** oneDhistograms, TH2D ** twoDhistograms, std::string * oneDhistoNames, std::string * twoDhistoNames, std::string file, double xsec, int fileNumber, int oneDHistoCount, int twoDHistoCount, bool oneDmult, bool twoDmult ) {
	
	TH1::AddDirectory(kFALSE);
	
	double divConstant = 0.0;
			
	for(int i = 1; i<= fileNumber; i++){
		if(access( (file+std::to_string(i)+".root").c_str(), F_OK ) != -1){
			TFile * f = TFile::Open((file+std::to_string(i)+".root").c_str());
			TDirectory * d1 = f->GetDirectory("analysis");
			TDirectory * d = d1->GetDirectory("allEvents");
			TH1D * countHisto = nullptr;
			d->GetObject("countHisto", countHisto);
			divConstant += countHisto->GetBinContent(1);
			if(i==1){
				for(int j = 0; j<oneDHistoCount; j++){
					d->GetObject(oneDhistoNames[j].c_str(), oneDhistograms[j]);
				}
				for(int j = 0; j<twoDHistoCount; j++){
					d->GetObject(twoDhistoNames[j].c_str(), twoDhistograms[j]);
				}
			} else {		
				for(int j = 0; j<oneDHistoCount; j++){
					TH1D * tempHisto = nullptr;
					d->GetObject(oneDhistoNames[j].c_str(), tempHisto);
					oneDhistograms[j]->Add(tempHisto);
				}
				for(int j = 0; j<twoDHistoCount; j++){	
					TH2D * tempHisto = nullptr;
					d->GetObject(twoDhistoNames[j].c_str(), tempHisto);
					twoDhistograms[j]->Add(tempHisto);
				}
			}
			delete f;
		} else {
			std::cout << "Failed to access: " << (file+std::to_string(i)+".root").c_str() << std::endl;
		}
	}
	
	
	double multConstant = xsec*1000.0*35.9/divConstant;
	
	for(int i = 0; i<oneDHistoCount; i++){	
		if(oneDmult == true){
			oneDhistograms[i]->Scale(multConstant);
		} else {
			oneDhistograms[i]->Scale(1/divConstant);			
		}
	}
	
	for(int i = 0; i<twoDHistoCount; i++){	
		if(twoDmult == true){
			twoDhistograms[i]->Scale(multConstant);
		} else {
			twoDhistograms[i]->Scale(1/divConstant);			
		}
	}
	
	
}


//Print correct/incorrect lepton comparison histograms
void printTwo1DHistos(TH1D * histo1, TH1D * histo2, TCanvas * c, std::string input, std::string name, std::string title){
	
	double yMax=0.0;
	double yMin=0.0;
	double xMax=0.0;
	double xMin=0.0;
	double max1 = histo1->GetBinContent(histo1->GetMaximumBin());
	double max2 = histo2->GetBinContent(histo2->GetMaximumBin());

	if(max1>=max2){
		histo1->GetYaxis()->SetRangeUser(0, max1*1.05);
		yMax=max1;
	} else {
		histo1->GetYaxis()->SetRangeUser(0, max2*1.05);
		yMax=max2;
	}
	
	if(histo1->GetXaxis()->GetBinLowEdge(100)>histo2->GetXaxis()->GetBinLowEdge(100)){
		xMax = histo1->GetXaxis()->GetBinLowEdge(100)*100/99;
	} else {
		xMax = histo2->GetXaxis()->GetBinLowEdge(100)*100/99;
	}
	
	
	histo1->SetLineColor(kBlue);
	histo1->SetStats(0);
	histo1->SetTitle(title.c_str());
	histo1->Draw("HIST");
	histo2->SetLineColor(kRed);
	histo2->SetStats(0);
	histo2->SetTitle(title.c_str());
	histo2->Draw("SAME HIST");
	

	std::cout << xMax << ", " << yMax << std::endl;
	std::cout << xMax*0.55/0.7 << ", " << yMax*0.014/0.016 << ", " << xMax*.75/.7 << ", " << yMax*.017/.016 <<  std::endl;
	//TLegend * legendME = new TLegend(xMax*0.55/0.7, yMax*0.014/0.016, xMax*.75/.7, yMax*.017/.016);
	TLegend * legendME = new TLegend(0.55/0.7, 0.013/0.016, .7/.7, .016/.016);
	
	legendME->AddEntry(histo1, "Incorrect Lepton", "L");
	legendME->AddEntry(histo2, "Correct Lepton", "L");
	legendME->Draw();
	c->Print((input+name+".png").c_str());
	c->Clear();
}

//Print three mass point comparison histograms
void printThree1DHistosMass(TH1D * histo1, TH1D * histo2, TH1D * histo3, TCanvas * c, std::string input, std::string name){
	
	
	
	double max1 = (histo1->GetBinContent(histo1->GetMaximumBin()))/(histo1->Integral(histo1->GetXaxis()->GetFirst(),histo1->GetXaxis()->GetLast()));
	double max2 = (histo2->GetBinContent(histo2->GetMaximumBin()))/(histo2->Integral(histo2->GetXaxis()->GetFirst(),histo2->GetXaxis()->GetLast()));
	double max3 = (histo3->GetBinContent(histo3->GetMaximumBin()))/(histo3->Integral(histo3->GetXaxis()->GetFirst(),histo3->GetXaxis()->GetLast()));
	
	
	if(max1>=max2){
		if(max1>=max3){
			histo1->SetLineColor(kBlue);
			histo1->SetStats(0);
			histo1->DrawNormalized("HIST");
			
			histo3->SetLineColor(kGreen);
			histo3->SetStats(0);
			histo3->DrawNormalized("SAME HIST");	
			
		} else {
			histo3->SetLineColor(kGreen);
			histo3->SetStats(0);
			histo3->DrawNormalized("HIST");	
		
			histo1->SetLineColor(kBlue);
			histo1->SetStats(0);
			histo1->DrawNormalized("SAME HIST");
			
		}
		histo2->SetLineColor(kRed);
		histo2->SetStats(0);
		histo2->DrawNormalized("SAME HIST");
	} else {
		if(max2>=max3){
			histo2->SetLineColor(kRed);
			histo2->SetStats(0);
			histo2->DrawNormalized("HIST");
			
			histo3->SetLineColor(kGreen);
			histo3->SetStats(0);
			histo3->DrawNormalized("SAME HIST");	
		} else {
			histo3->SetLineColor(kGreen);
			histo3->SetStats(0);
			histo3->DrawNormalized("HIST");	
			
			histo2->SetLineColor(kRed);
			histo2->SetStats(0);
			histo2->DrawNormalized("SAME HIST");
		}
		histo1->SetLineColor(kBlue);
		histo1->SetStats(0);
		histo1->DrawNormalized("SAME HIST");
		
	}
	
	TLegend * legendME = new TLegend();
	legendME->AddEntry(histo1, "WR1600_N400", "L");
	legendME->AddEntry(histo2, "WR1600_N1200", "L");
	legendME->AddEntry(histo3, "WR1600_N1500", "L");
	legendME->Draw();
	c->Print((input+name+".png").c_str());
	c->Clear();
}


//Print 1-d histogram
void print1DHistos(TH1D * histo, TCanvas * c, std::string input, std::string name){
	//histo->SetStats(0);
	histo->Draw("HIST");
	c->Print((input+name+".png").c_str());
	c->Clear();
}

//Print 2-d histogram
void print2DHistos(TH2D * histo, TCanvas * c, std::string input, std::string name){
	//histo->SetStats(0);
	histo->Draw("COLZ");
	c->Print((input+name+".png").c_str());
	c->Clear();
}
	
void extractMain(){
	
	TCanvas * c = new TCanvas();
	c->SetCanvasSize(1200, 600);
	
	
	std::string files[16] = {"WR800_N400/out_WR800N400_", "WR1200_N600/out_WR1200N600_", "WR1200_N1000/out_WR1200N1000_", "WR1600_N400/out_WR1600N400_", "WR1600_N800/out_WR1600N800_", "WR1600_N400/out_WR1600N400_", "WR1600_N1200/out_WR1600N1200_", "WR1600_N1500/out_WR1600N1500_", "WR2000_N600/out_WR2000N600_", "WR2000_N1000/out_WR2000N1000_", "WR2000_N1400/out_WR2000N1400_", "WR2000_N1800/out_WR2000N1800_", "WR800_N200/out_WR800N200_", "WR800_N700/out_WR800N700_", "WR2000_N1900/out_WR2000N1900_","WR800_N600/out_WR800N600_"}; 
				
	const double xsec[16] = {10.41, 1.947, 0.4296, 0.7256, 0.5188, .7256, 0.2129, 0.02318,  0.2217,  0.1649, 0.08748, 0.01517, 14.46, 1.473, .005147, 4.351};
		
	double fileNumber = 28;
	
	TH1D * oneDhistograms1600_400[47];
	for(int i =0; i<47; i++){
		oneDhistograms1600_400[i] = nullptr;
	}
	
	TH1D * oneDhistograms1600_1200[47];
	for(int i =0; i<47; i++){
		oneDhistograms1600_1200[i] = nullptr;
	}
	
	TH1D * oneDhistograms1600_1500[47];
	for(int i =0; i<47; i++){
		oneDhistograms1600_1500[i] = nullptr;
	}
	
	int oneDMatchMerge1[47] = {0,2,3,4,5,6,7,8,9,10,20,21,22,23,24,25,26,27,28,38,39,40,41, 46,47,48,49,54,55,56,57,58,64,65,66,67,68,74,75,76,77,78,84,85,86,87,88};
	int oneDMatchMerge2[47] = {1,11,12,13,14,15,16,17,18,19, 29,30,31,32,33,34,35,36,37,42,43,44,45,50,51,52,53,59,60,61,62,63,69,70,71,72,73,79,80,81,82,83,89,90,91,92,93};
		
	std::string oneDhistoNamesMatch2[94] = {"l2leptonJJhisto", "l2leptonJJhisto", "leptonEtaHisto1", "leptonPhiHisto1", "leptonDPhiHisto1", "leptonDRHisto1", "leptonPtHisto1", "leptonPtHisto1Scaled", "lepton1SphericityHisto", "leptonEtaHisto1WR", "leptonNMassHisto1", //10
		"leptonEtaHisto1", "leptonPhiHisto1", "leptonDPhiHisto1", "leptonDRHisto1", "leptonPtHisto1", "leptonPtHisto1Scaled", "lepton1SphericityHisto", "leptonEtaHisto1WR", "leptonNMassHisto1", //19
		"leptonEtaHisto2", "leptonPhiHisto2", "leptonDPhiHisto2", "leptonDRHisto2", "leptonPtHisto2", "leptonPtHisto2Scaled", "lepton2SphericityHisto", "leptonEtaHisto2WR", "leptonNMassHisto2", //28
		"leptonEtaHisto2", "leptonPhiHisto2", "leptonDPhiHisto2", "leptonDRHisto2", "leptonPtHisto2", "leptonPtHisto2Scaled", "lepton2SphericityHisto", "leptonEtaHisto2WR", "leptonNMassHisto2", //37
		"leptonPhiHisto1WR", "leptonDPhiHisto1WR", "leptonDRHisto1WR", "leptonPtHisto1WR", //41
		"leptonPhiHisto1WR", "leptonDPhiHisto1WR", "leptonDRHisto1WR", "leptonPtHisto1WR", //45
		"leptonPhiHisto2WR", "leptonDPhiHisto2WR", "leptonDRHisto2WR", "leptonPtHisto2WR", //49
		"leptonPhiHisto2WR", "leptonDPhiHisto2WR", "leptonDRHisto2WR", "leptonPtHisto2WR", //53
		"leptonEtaHisto1N", "leptonPhiHisto1N", "leptonDPhiHisto1N", "leptonDRHisto1N", "leptonPtHisto1N", //58
		"leptonEtaHisto1N", "leptonPhiHisto1N", "leptonDPhiHisto1N", "leptonDRHisto1N", "leptonPtHisto1N", //63
		"leptonEtaHisto2N", "leptonPhiHisto2N", "leptonDPhiHisto2N", "leptonDRHisto2N", "leptonPtHisto2N", //68
		"leptonEtaHisto2N", "leptonPhiHisto2N", "leptonDPhiHisto2N", "leptonDRHisto2N", "leptonPtHisto2N", //73
		"leptonEtaHisto1L", "leptonPhiHisto1L", "leptonDPhiHisto1L", "leptonDRHisto1L", "leptonPtHisto1L", //78
		"leptonEtaHisto1L", "leptonPhiHisto1L", "leptonDPhiHisto1L", "leptonDRHisto1L", "leptonPtHisto1L", //83
		"leptonEtaHisto2L", "leptonPhiHisto2L", "leptonDPhiHisto2L", "leptonDRHisto2L", "leptonPtHisto2L", //88
		"leptonEtaHisto2L", "leptonPhiHisto2L", "leptonDPhiHisto2L", "leptonDRHisto2L", "leptonPtHisto2L"}; //93	 
	
	for(int j = 15; j<16; j++){
		
		int oneDHistoGenCount = 6;
		
		std::string oneDhistoNamesGen[6] = {"leadEPtHisto", "leadMPtHisto", "leadTPtHisto", "subleadEPtHisto", "subleadMPtHisto", "subleadTPtHisto"};
		
		TH1D * oneDhistogramsGen[6];
		
		
		int oneDHistoDivCount = 9;
		
		std::string oneDhistoNamesDiv[9] = {"nMinusOneHisto","nMinusOneElectronHisto", "nMinusOneMuonHisto", "leptonHisto", "leptonHistoFail", "leptonHistoMix", "leptonHistoMuon", "leptonHistoElectron", "leptonHistoTau" };
		
		TH1D * oneDhistogramsDiv[9];
		
		for(int i =0; i<oneDHistoDivCount; i++){
			oneDhistogramsDiv[i] = nullptr;
		}
		
		int oneDHistoRecoCount = 3;
		
		std::string oneDhistoNamesReco[3] = {"subMuJJhisto", "subElectronJJhisto", "jetjetMassHisto" };
		std::string oneDhistoNamesReco2[3] = {"subLeptonJJhisto", "subLeptonJJhisto", "jetjetMassHisto" };
		
		int oneDRecoMerge1[2] = {0,2};
		int oneDRecoMerge2[2] = {1,-1};
		
		
		TH1D * oneDhistogramsReco[3];
		
		for(int i =0; i<oneDHistoRecoCount; i++){
			oneDhistogramsReco[i] = nullptr;
		}
	
		
		int oneDHistoMatchCount = 94;
		
		std::string oneDhistoNamesMatch[94] = {"l2MuJJhisto", "l2ElectronJJhisto", "electronEtaHisto1", "electronPhiHisto1", "electronDPhiHisto1", "electronDRHisto1", "electronPtHisto1", "electronPtHisto1Scaled", "electron1SphericityHisto", "electronEtaHisto1WR", "electronNMassHisto1", //10
		"muonEtaHisto1", "muonPhiHisto1", "muonDPhiHisto1", "muonDRHisto1", "muonPtHisto1", "muonPtHisto1Scaled", "muon1SphericityHisto", "muonEtaHisto1WR", "muonNMassHisto1", //19
		"electronEtaHisto2", "electronPhiHisto2", "electronDPhiHisto2", "electronDRHisto2", "electronPtHisto2", "electronPtHisto2Scaled", "electron2SphericityHisto", "electronEtaHisto2WR", "electronNMassHisto2", //28
		"muonEtaHisto2", "muonPhiHisto2", "muonDPhiHisto2", "muonDRHisto2", "muonPtHisto2", "muonPtHisto2Scaled", "muon2SphericityHisto", "muonEtaHisto2WR", "muonNMassHisto2", //37
		"electronPhiHisto1WR", "electronDPhiHisto1WR", "electronDRHisto1WR", "electronPtHisto1WR", //41
		"muonPhiHisto1WR", "muonDPhiHisto1WR", "muonDRHisto1WR", "muonPtHisto1WR", //45
		"electronPhiHisto2WR", "electronDPhiHisto2WR", "electronDRHisto2WR", "electronPtHisto2WR", //49
		"muonPhiHisto2WR", "muonDPhiHisto2WR", "muonDRHisto2WR", "muonPtHisto2WR", //53
		"electronEtaHisto1N", "electronPhiHisto1N", "electronDPhiHisto1N", "electronDRHisto1N", "electronPtHisto1N", //58
		"muonEtaHisto1N", "muonPhiHisto1N", "muonDPhiHisto1N", "muonDRHisto1N", "muonPtHisto1N", //63
		"electronEtaHisto2N", "electronPhiHisto2N", "electronDPhiHisto2N", "electronDRHisto2N", "electronPtHisto2N", //68
		"muonEtaHisto2N", "muonPhiHisto2N", "muonDPhiHisto2N", "muonDRHisto2N", "muonPtHisto2N", //73
		"electronEtaHisto1L", "electronPhiHisto1L", "electronDPhiHisto1L", "electronDRHisto1L", "electronPtHisto1L", //78
		"muonEtaHisto1L", "muonPhiHisto1L", "muonDPhiHisto1L", "muonDRHisto1L", "muonPtHisto1L", //83
		"electronEtaHisto2L", "electronPhiHisto2L", "electronDPhiHisto2L", "electronDRHisto2L", "electronPtHisto2L", //88
		"muonEtaHisto2L", "muonPhiHisto2L", "muonDPhiHisto2L", "muonDRHisto2L", "muonPtHisto2L"}; //93
		
		
		std::string leptonCompNames[23] = {"leptonEtaHisto", "leptonPhiHisto", "leptonDPhiHisto", "leptonDRHisto", "leptonPtHisto", "leptonPtHistoScaled", "leptonSphericityHisto", "leptonEtaHistoWR", "leptonNMassHisto", //0
		"leptonPhiHistoWR", "leptonDPhiHistoWR", "leptonDRHistoWR", "leptonPtHistoWR", //4
		"leptonEtaHistoN", "leptonPhiHistoN", "leptonDPhiHistoN", "leptonDRHistoN", "leptonPtHistoN", //58
		"leptonEtaHistoL", "leptonPhiHistoL", "leptonDPhiHistoL", "leptonDRHistoL", "leptonPtHistoL"}; //78
		
		std::string leptonCompTitles[23] = {"lepton Eta Histo", "lepton Phi Histo", "lepton DPhi Histo", "lepton DR Histo", "lepton Pt Histo", "lepton Pt Histo Scaled", "lepton Sphericity Histo", "lepton Eta Histo WR", "lepton N Mass Histo", //0
		"lepton Phi Histo WR", "lepton DPhi Histo WR", "lepton DR Histo WR", "lepton Pt Histo WR", //4
		"lepton Eta Histo N", "lepton Phi Histo N", "lepton DPhi Histo N", "lepton DR Histo N", "lepton Pt Histo N", //58
		"lepton Eta Histo L", "lepton Phi Histo L", "lepton D Phi Histo L", "lepton DR Histo L", "lepton Pt Histo L"}; //78
		
		int leptonComp1[23] = { 2, 3, 4, 5, 6, 7, 8, 9,10,38,39,40,41,54,55,56,57,58,74,75,76,77,78};
		int leptonComp2[23] = {20,21,22,23,24,25,26,27,28,46,47,48,49,64,65,66,67,68,84,85,86,87,88};
		
		
		
		
		
		
		TH1D * oneDhistogramsMatch[94];
		
		for(int i =0; i<oneDHistoMatchCount; i++){
			oneDhistogramsMatch[i] = nullptr;
		}
		
		int twoDHistoRecoCount = 12;
		
		std::string twoDhistoNamesReco[12] = {"subLeadMuonHisto", "subLeadElectronHisto", "leadMuonHisto","leadElectronHisto", "lowEtaElectronHisto", "lowEtaMuonHisto", "highEtaElectronHisto", "highEtaMuonHisto", "lowR2MuonHisto", "lowR2ElectronHisto", "highR2MuonHisto", "highR2ElectronHisto"};
		
		std::string twoDhistoNamesReco2[12] = {"subLeadleptonHisto", "subLeadleptonHisto", "leadleptonHisto","leadleptonHisto", "lowEtaleptonHisto", "lowEtaleptonHisto", "highEtaleptonHisto", "highEtaleptonHisto", "lowR2leptonHisto", "lowR2leptonHisto", "highR2leptonHisto", "highR2leptonHisto"};
		
		int twoDRecoMerge1[6] = {0,2,4,6,8,10};
		int twoDRecoMerge2[6] = {1,3,5,7,9,11};
		
		TH2D * twoDhistogramsReco[12];
		
		for(int i =0; i<twoDHistoRecoCount; i++){
			twoDhistogramsReco[i] = nullptr;
		}
		
		int twoDHistoMatchCount = 6;
		
		std::string twoDhistoNamesMatch[6] = {"matchedMuonHisto", "matchedElectronHisto", "matchedMuon1MassHisto", "matchedElectron1MassHisto", "matchedMuon2MassHisto", "matchedElectron2MassHisto"};
		
		std::string twoDhistoNamesMatch2[6] = {"matchedleptonHisto", "matchedleptonHisto", "matchedlepton1MassHisto", "matchedlepton1MassHisto", "matchedlepton2MassHisto", "matchedlepton2MassHisto"};
		
		int twoDMatchMerge1[3] = {0,2,4};
		int twoDMatchMerge2[3] = {1,3,5};
		
		TH2D * twoDhistogramsMatch[6];
		
		for(int i =0; i<twoDHistoMatchCount; i++){
			twoDhistogramsMatch[i] = nullptr;
		}
		
		int twoDHistoNNCount = 8;
		
		std::string twoDhistoNamesNN[8] = {"NNResolvedMuonHisto", "NNResolvedElectronHisto","notNNResolvedMuonHisto", "notNNResolvedElectronHisto", "NNSuperResolvedMuonHisto", "NNSuperResolvedElectronHisto", "notNNSuperResolvedMuonHisto", "notNNSuperResolvedElectronHisto"};
		
		std::string twoDhistoNamesNN2[8] = {"NNResolvedleptonHisto", "NNResolvedleptonHisto","notNNResolvedleptonHisto", "notNNResolvedleptonHisto", "NNSuperResolvedleptonHisto", "NNSuperResolvedleptonHisto", "notNNSuperResolvedleptonHisto", "notNNSuperResolvedleptonHisto"};
		
		
		int twoDNNMerge1[4] = {0,2,4,6};
		int twoDNNMerge2[4] = {1,4,5,7};
		
		TH2D * twoDhistogramsNN[8];
		
		for(int i =0; i<twoDHistoNNCount; i++){
			twoDhistogramsNN[i] = nullptr;
		}
		
		
		//Extract and print reco histos
		extractHistos(oneDhistogramsReco, twoDhistogramsReco, oneDhistoNamesReco, twoDhistoNamesReco, files[j], xsec[j], fileNumber, oneDHistoRecoCount, twoDHistoRecoCount, false, false );
		
		oneDhistogramsReco[0]->Add(oneDhistogramsReco[1]);
		print1DHistos(oneDhistogramsReco[0], c, files[j], oneDhistoNamesReco2[0]);
		print1DHistos(oneDhistogramsReco[2], c, files[j], oneDhistoNamesReco2[2]);
		
		for(int i =0; i<twoDHistoRecoCount/2; i++){
			twoDhistogramsReco[twoDRecoMerge1[i]]->Add(twoDhistogramsReco[twoDRecoMerge2[i]]);
			print2DHistos(twoDhistogramsReco[twoDRecoMerge1[i]], c, files[j], twoDhistoNamesReco2[twoDRecoMerge1[i]]);
		}
		
		//Extract and print matched histos
		extractHistos(oneDhistogramsMatch, twoDhistogramsMatch, oneDhistoNamesMatch, twoDhistoNamesMatch, files[j], xsec[j], fileNumber, oneDHistoMatchCount, twoDHistoMatchCount, false, false );
		
		for(int i =0; i<oneDHistoMatchCount/2; i++){
			oneDhistogramsMatch[oneDMatchMerge1[i]]->Add(oneDhistogramsMatch[oneDMatchMerge2[i]]);
			print1DHistos(oneDhistogramsMatch[oneDMatchMerge1[i]], c, files[j], oneDhistoNamesMatch2[oneDMatchMerge1[i]]);
			if(j==5){
				oneDhistograms1600_400[i] =  oneDhistogramsMatch[oneDMatchMerge1[i]];
			} else if(j==6){
				oneDhistograms1600_1200[i] =  oneDhistogramsMatch[oneDMatchMerge1[i]];
			} else if(j==7){
				oneDhistograms1600_1500[i] =  oneDhistogramsMatch[oneDMatchMerge1[i]];
			}
		}
		for(int i =0; i<23;i++){
			printTwo1DHistos(oneDhistogramsMatch[leptonComp1[i]], oneDhistogramsMatch[leptonComp2[i]], c, files[j], leptonCompNames[i], leptonCompTitles[i]);
		}
		
		for(int i =0; i<twoDHistoMatchCount/2; i++){
			twoDhistogramsMatch[twoDMatchMerge1[i]]->Add(twoDhistogramsMatch[twoDMatchMerge2[i]]);
			print2DHistos(twoDhistogramsMatch[twoDMatchMerge1[i]], c, files[j], twoDhistoNamesMatch2[twoDMatchMerge1[i]]);
		}
		
		//Extract and print gen 1-d histos
		extractHistos(oneDhistogramsGen, twoDhistogramsNN, oneDhistoNamesGen, twoDhistoNamesNN, files[j], xsec[j], fileNumber, oneDHistoGenCount, 0);
		
		for(int i =0; i<oneDHistoDivCount; i++){
			print1DHistos(oneDhistogramsDiv[i], c, files[j], oneDhistoNamesDiv[i]);
		}
		
		//Extract and print remaining 1-d histos and 2-d NN histos
		extractHistos(oneDhistogramsDiv, twoDhistogramsNN, oneDhistoNamesDiv, twoDhistoNamesNN, files[j], xsec[j], fileNumber, oneDHistoDivCount, twoDHistoNNCount, false, false );
		
		for(int i =0; i<oneDHistoDivCount; i++){
			print1DHistos(oneDhistogramsDiv[i], c, files[j], oneDhistoNamesDiv[i]);
		}
		
		for(int i =0; i<twoDHistoNNCount/2; i++){
			twoDhistogramsNN[twoDNNMerge1[i]]->Add(twoDhistogramsNN[twoDNNMerge2[i]]);
			print2DHistos(twoDhistogramsNN[twoDNNMerge1[i]], c, files[j], twoDhistoNamesNN2[twoDNNMerge1[i]]);
		}
	}
	
	for(int i =0; i<47; i++){
		printThree1DHistosMass(oneDhistograms1600_400[i], oneDhistograms1600_1200[i], oneDhistograms1600_1500[i],  c, "", oneDhistoNamesMatch2[oneDMatchMerge1[i]]);
	}
}