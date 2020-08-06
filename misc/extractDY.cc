#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveLabel.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include <iostream>

//Collects all the one-d and two-d histograms input into the function call from the many root files created while the analysis is running
void extractHistos(TH1D ** oneDhistograms, TH2D ** twoDhistograms, std::string * oneDhistoNames, std::string * twoDhistoNames, int oneDHistoCount, int twoDHistoCount, bool oneDmult, bool twoDmult ) {
	
	TH1::AddDirectory(kFALSE);
	
	
	const char * files[7] = { "DYJetsToLL_M-50_HT-100to200/out_DYJetsToLL_M-50_HT-100to200_", "DYJetsToLL_M-50_HT-200to400/out_DYJetsToLL_M-50_HT-200to400_", "DYJetsToLL_M-50_HT-400to600/out_DYJetsToLL_M-50_HT-400to600_", "DYJetsToLL_M-50_HT-600to800/out_DYJetsToLL_M-50_HT-600to800_", "DYJetsToLL_M-50_HT-800to1200/out_DYJetsToLL_M-50_HT-800to1200_" , "DYJetsToLL_M-50_HT-1200to2500/out_DYJetsToLL_M-50_HT-1200to2500_" , "DYJetsToLL_M-50_HT-2500toInf/out_DYJetsToLL_M-50_HT-2500toInf_"}; 
		
	const double xsec[7] = {147.4,  40.99, 5.678, 2.198, 0.6304, 0.1514, 0.003565};
		
	const int fileCount[7] = {20 , 12, 9, 103, 28, 8, 4};
	
	double divConstantFinal = 0.0;
	
	for(int k = 0; k<7; k++){
		double divConstant = 0.0;
		for(int i = 1; i<= fileCount[k]; i++){
			if(access( (files[k]+std::to_string(i)+".root").c_str(), F_OK ) != -1){
				TFile * f = TFile::Open((files[k]+std::to_string(i)+".root").c_str());
				TDirectory * d1 = f->GetDirectory("analysis");
				TDirectory * d = d1->GetDirectory("allEvents");
				TH1D * countHisto = nullptr;
				d->GetObject("countHisto", countHisto);
				divConstant+=countHisto->GetBinContent(1);
				delete f;
			}
		}
		
		divConstantFinal+=xsec[k];
		
		
		for(int i = 1; i<= fileCount[k]; i++){
			if(access( (files[k]+std::to_string(i)+".root").c_str(), F_OK ) != -1){
				TFile * f = TFile::Open((files[k]+std::to_string(i)+".root").c_str());
				TDirectory * d1 = f->GetDirectory("analysis");
				TDirectory * d = d1->GetDirectory("allEvents");
				TH1D * countHisto = nullptr;
				d->GetObject("countHisto", countHisto);
				if(i==1 and k==0){
					for(int j = 0; j<oneDHistoCount; j++){
						d->GetObject(oneDhistoNames[j].c_str(), oneDhistograms[j]);
						oneDhistograms[j]->Scale(xsec[k]/divConstant);
					}
					for(int j = 0; j<twoDHistoCount; j++){
						d->GetObject(twoDhistoNames[j].c_str(), twoDhistograms[j]);
						twoDhistograms[j]->Scale(xsec[k]/divConstant);
					}
				} else {		
					for(int j = 0; j<oneDHistoCount; j++){
						TH1D * tempHisto = nullptr;
						d->GetObject(oneDhistoNames[j].c_str(), tempHisto);
						oneDhistograms[j]->Add(tempHisto, xsec[k]/divConstant);
					}
					for(int j = 0; j<twoDHistoCount; j++){	
						TH2D * tempHisto = nullptr;
						d->GetObject(twoDhistoNames[j].c_str(), tempHisto);
						twoDhistograms[j]->Add(tempHisto, xsec[k]/divConstant);
					}
				}
				delete f;
			} else {
				std::cout << "Failed to access: " << (files[k]+std::to_string(i)+".root").c_str() << std::endl;
			}
		}
		
		/*for(int j = 0; j<oneDHistoCount; j++){
			oneDhistograms[j]->Scale(xsec[k]/divConstant);
		}
		for(int j = 0; j<twoDHistoCount; j++){
			twoDhistograms[j]->Scale(xsec[k]/divConstant);
		}
		divConstantFinal+=xsec[k];*/
	}	
		
	double multConstant = 1000.0*35.9;
	
	for(int i = 0; i<oneDHistoCount; i++){	
		if(oneDmult == true){
			oneDhistograms[i]->Scale(multConstant);
		} else {
			oneDhistograms[i]->Scale(1/divConstantFinal);			
		}
	}
	
	for(int i = 0; i<twoDHistoCount; i++){	
		if(twoDmult == true){
			twoDhistograms[i]->Scale(multConstant);
		} else {
			twoDhistograms[i]->Scale(1/divConstantFinal);			
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
	histo->SetStats(0);
	histo->Draw("HIST");
	c->Print((input+name+".png").c_str());
	c->Clear();
}

//Print 2-d histogram
void print2DHistos(TH2D * histo, TCanvas * c, std::string input, std::string name){
	histo->SetStats(0);
	histo->Draw("COLZ");
	c->Print((input+name+".png").c_str());
	c->Clear();
}
	
void extractDY(){
	
	TCanvas * c = new TCanvas();
	c->SetCanvasSize(1200, 600);
	
	
	int oneDHistoGenCount = 6;
		
	std::string oneDhistoNamesGen[6] = {"leadEPtHisto", "leadMPtHisto", "leadTPtHisto", "subleadEPtHisto", "subleadMPtHisto", "subleadTPtHisto"};
	
	TH1D * oneDhistogramsGen[6];
	
	
	int oneDHistoDivCount = 6;
		
	std::string oneDhistoNamesDiv[6] = {"leptonHisto", "leptonHistoFail", "leptonHistoMix", "leptonHistoMuon", "leptonHistoElectron", "leptonHistoTau" };
	
	TH1D * oneDhistogramsDiv[6];
	
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
	
	
	
	
	
	
	int twoDHistoRecoCount = 12;
	
	std::string twoDhistoNamesReco[12] = {"subLeadMuonHisto", "subLeadElectronHisto", "leadMuonHisto","leadElectronHisto", "lowEtaElectronHisto", "lowEtaMuonHisto", "highEtaElectronHisto", "highEtaMuonHisto", "lowR2MuonHisto", "lowR2ElectronHisto", "highR2MuonHisto", "highR2ElectronHisto"};
	
	std::string twoDhistoNamesReco2[12] = {"subLeadleptonHisto", "subLeadleptonHisto", "leadleptonHisto","leadleptonHisto", "lowEtaleptonHisto", "lowEtaleptonHisto", "highEtaleptonHisto", "highEtaleptonHisto", "lowR2leptonHisto", "lowR2leptonHisto", "highR2leptonHisto", "highR2leptonHisto"};
	
	int twoDRecoMerge1[6] = {0,2,4,6,8,10};
	int twoDRecoMerge2[6] = {1,3,5,7,9,11};
	
	TH2D * twoDhistogramsReco[12];
	
	for(int i =0; i<twoDHistoRecoCount; i++){
		twoDhistogramsReco[i] = nullptr;
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
	
	
	//Extract and print reco histostrue
	extractHistos(oneDhistogramsReco, twoDhistogramsReco, oneDhistoNamesReco, twoDhistoNamesReco, oneDHistoRecoCount, twoDHistoRecoCount, true, true );
	
	oneDhistogramsReco[0]->Add(oneDhistogramsReco[1]);
	print1DHistos(oneDhistogramsReco[0], c, "DY_", oneDhistoNamesReco2[0]);
	print1DHistos(oneDhistogramsReco[2], c, "DY_", oneDhistoNamesReco2[2]);
	
	for(int i =0; i<twoDHistoRecoCount/2; i++){
		twoDhistogramsReco[twoDRecoMerge1[i]]->Add(twoDhistogramsReco[twoDRecoMerge2[i]]);
		print2DHistos(twoDhistogramsReco[twoDRecoMerge1[i]], c, "DY_", twoDhistoNamesReco2[twoDRecoMerge1[i]]);
	}
	
	
	//Extract and print gen 1-d histos
	extractHistos(oneDhistogramsGen, twoDhistogramsNN, oneDhistoNamesGen, twoDhistoNamesNN, oneDHistoGenCount, 0, true, true);
		
	for(int i =0; i<oneDHistoGenCount; i++){
		print1DHistos(oneDhistogramsGen[i], c, "DY_", oneDhistoNamesGen[i]);
	}
	
	//Extract and print remaining 1-d histos and 2-d NN histos
	extractHistos(oneDhistogramsDiv, twoDhistogramsNN, oneDhistoNamesDiv, twoDhistoNamesNN, oneDHistoDivCount, twoDHistoNNCount, false, true );
	
	for(int i =0; i<oneDHistoDivCount; i++){
		print1DHistos(oneDhistogramsDiv[i], c, "DY_", oneDhistoNamesDiv[i]);
	}
	
	for(int i =0; i<twoDHistoNNCount/2; i++){
		twoDhistogramsNN[twoDNNMerge1[i]]->Add(twoDhistogramsNN[twoDNNMerge2[i]]);
		print2DHistos(twoDhistogramsNN[twoDNNMerge1[i]], c, "DY_", twoDhistoNamesNN2[twoDNNMerge1[i]]);
	}
}