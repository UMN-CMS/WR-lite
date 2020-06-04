#include "TROOT.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

void genHistos(const std::string& input, double crossSec) {
        
		
		TFile * f = new TFile((input+".root").c_str());
        TDirectory * d1 = f->GetDirectory("demo");
        TDirectory * d = d1->GetDirectory("allEvents");
        TCanvas * c = new TCanvas();
		c->SetCanvasSize(1200, 600);
		
		TH1D * countHisto = nullptr;
        d->GetObject("countHisto", countHisto);
		//int k = countHisto->GetXaxis()->FindBin("count");
        double divConstant=countHisto->GetBinContent(1);
		
		
		double multConstant = crossSec*1000.0*35.9/divConstant;
		
		
		TH1D * jetjetMassHisto = nullptr;
		d->GetObject("jetjetMassHisto", jetjetMassHisto);
		jetjetMassHisto->Scale(multConstant);
        jetjetMassHisto->Draw("HIST");
        c->Print((input+"_jetjetMassHisto.png").c_str());
        c->Clear();
		
		TH1D * matchedL1MassHisto = nullptr;
		d->GetObject("matchedL1MassHisto", matchedL1MassHisto);
		matchedL1MassHisto->Scale(multConstant);
        matchedL1MassHisto->Draw("HIST");
        c->Print((input+"_matchedL1MassHisto.png").c_str());
        c->Clear();
		
		TH1D * matchedL2MassHisto = nullptr;
		d->GetObject("matchedL2MassHisto", matchedL2MassHisto);
		matchedL2MassHisto->Scale(multConstant);
        matchedL2MassHisto->Draw("HIST");
        c->Print((input+"_matchedL2MassHisto.png").c_str());
        c->Clear();
		/*
		/TH1D * jetjetMassErrorHisto = nullptr;
		d->GetObject("jetjetMassErrorHisto", jetjetMassErrorHisto);
		jetjetMassErrorHisto->Scale(multConstant);
        jetjetMassErrorHisto->Draw("HIST");
        c->Print((input+"_jetjetMassErrorHisto.png").c_str());
        c->Clear();
		
		TH1D * matchedL1MassErrorHisto = nullptr;
		d->GetObject("matchedL1MassErrorHisto", matchedL1MassErrorHisto);
		matchedL1MassErrorHisto->Scale(multConstant);
        matchedL1MassErrorHisto->Draw("HIST");
        c->Print((input+"_matchedL1MassErrorHisto.png").c_str());
        c->Clear();
		
		TH1D * matchedL2MassErrorHisto = nullptr;
		d->GetObject("matchedL2MassErrorHisto", matchedL2MassErrorHisto);
		matchedL2MassErrorHisto->Scale(multConstant);
        matchedL2MassErrorHisto->Draw("HIST");
        c->Print((input+"_matchedL2MassErrorHisto.png").c_str());
        c->Clear();
		
        TH1D * l1qqHist = nullptr;
        d->GetObject("l1qq", l1qqHist);
		l1qqHist->Scale(multConstant);
        l1qqHist->Draw("HIST");
        c->Print((input+"_l1qqHist.png").c_str());
        c->Clear();

        TH1D * l2qqHist = nullptr;
        d->GetObject("l2qq", l2qqHist);
		l2qqHist->Scale(multConstant);
        l2qqHist->Draw("HIST");
        c->Print((input+"_l2qqHist.png").c_str());
        c->Clear();

        TH1D * subLqqHist = nullptr;
		d->GetObject("subLqq", subLqqHist);
		subLqqHist->Scale(multConstant);
		subLqqHist->Draw("HIST");
		c->Print((input+"_subLqqHist.png").c_str());                                                                                                             
		c->Clear();

        TH1D * llqqHist = nullptr;
        d->GetObject("llqq", llqqHist);
		llqqHist->Scale(multConstant);
        llqqHist->Draw("HIST");
        c->Print((input+"_llqqHist.png").c_str());
        c->Clear();
		*/
		
        TH1D * subMuJJhisto = nullptr;
        d->GetObject("subMuJJhisto", subMuJJhisto);
		subMuJJhisto->Scale(multConstant);
        subMuJJhisto->Draw("HIST");
        c->Print((input+"_subMuJJhisto.png").c_str());
        c->Clear();

        TH1D * l2MuJJhisto = nullptr;
        d->GetObject("l2MuJJhisto", l2MuJJhisto);
		l2MuJJhisto->Scale(multConstant);
        l2MuJJhisto->Draw("HIST");
        c->Print((input+"_l2MuJJhisto.png").c_str());
        c->Clear();

        TH1D * subElectronJJhisto = nullptr;
        d->GetObject("subElectronJJhisto", subElectronJJhisto);
		subElectronJJhisto->Scale(multConstant);
		subElectronJJhisto->Draw("HIST");
		c->Print((input+"_subElectronJJhisto.png").c_str());
		c->Clear();
		
		TH1D * l2ElectronJJhisto = nullptr;
        d->GetObject("l2ElectronJJhisto", l2ElectronJJhisto);
		l2ElectronJJhisto->Scale(multConstant);
        l2ElectronJJhisto->Draw("HIST");
        c->Print((input+"_l2ElectronJJhisto.png").c_str());
        c->Clear();

        TH1D * nMinusOneHisto = nullptr;
        d->GetObject("nMinusOneHisto", nMinusOneHisto);
		nMinusOneHisto->Scale(1/divConstant);
        nMinusOneHisto->Draw();
        c->Print((input+"_nMinusOneHisto.png").c_str());
        c->Clear();
		
		TH1D * nMinusOneElectronHisto = nullptr;
        d->GetObject("nMinusOneElectronHisto", nMinusOneElectronHisto);
		nMinusOneElectronHisto->Scale(1/divConstant);
        nMinusOneElectronHisto->Draw();
        c->Print((input+"_nMinusOneElectronHisto.png").c_str());
        c->Clear();
		
		TH1D * nMinusOneMuonHisto = nullptr;
        d->GetObject("nMinusOneMuonHisto", nMinusOneMuonHisto);
		nMinusOneMuonHisto->Scale(1/divConstant);
        nMinusOneMuonHisto->Draw();
        c->Print((input+"_nMinusOneMuonHisto.png").c_str());
        c->Clear();
		
		TH1D * leptonHisto = nullptr;
        d->GetObject("leptonHisto", leptonHisto);
        leptonHisto->SetStats(0);
		leptonHisto->Scale(1/divConstant);
		leptonHisto->Draw();
        c->Print((input+"_leptonHisto.png").c_str());
        c->Clear();
		
		
		TH2D * lepton2Histo = nullptr;
		d->GetObject("lepton2Histo", lepton2Histo);
        lepton2Histo->SetStats(0);
		lepton2Histo->Scale(multConstant);
		lepton2Histo->Draw("COLZ");
        c->Print((input+"_lepton2Histo.png").c_str());
        c->Clear();
		
		TH2D * matchedMuonHisto = nullptr;
		d->GetObject("matchedMuonHisto", matchedMuonHisto);
        matchedMuonHisto->SetStats(0);
		matchedMuonHisto->Scale(multConstant);
		matchedMuonHisto->Draw("COLZ");
        c->Print((input+"_matchedMuonHisto.png").c_str());
        c->Clear();
		
		TH2D * matchedElectronHisto = nullptr;
		d->GetObject("matchedElectronHisto", matchedElectronHisto);
        matchedElectronHisto->SetStats(0);
		matchedElectronHisto->Scale(multConstant);
		matchedElectronHisto->Draw("COLZ");
        c->Print((input+"_matchedElectronHisto.png").c_str());
        c->Clear();
		
		TH2D * subLeadMuonHisto = nullptr;
		d->GetObject("subLeadMuonHisto", subLeadMuonHisto);
        subLeadMuonHisto->SetStats(0);
		subLeadMuonHisto->Scale(multConstant);
		subLeadMuonHisto->Draw("COLZ");
        c->Print((input+"_subLeadMuonHisto.png").c_str());
        c->Clear();
		
		TH2D * subLeadElectronHisto = nullptr;
		d->GetObject("subLeadElectronHisto", subLeadElectronHisto);
        subLeadElectronHisto->SetStats(0);
		subLeadElectronHisto->Scale(multConstant);
		subLeadElectronHisto->Draw("COLZ");
		c->Print((input+"_subLeadElectronHisto.png").c_str());
        c->Clear();
		
		TH2D * leadMuonHisto = nullptr;
		d->GetObject("leadMuonHisto", leadMuonHisto);
        leadMuonHisto->SetStats(0);
		leadMuonHisto->Scale(multConstant);
		leadMuonHisto->Draw("COLZ");
		c->Print((input+"_leadMuonHisto.png").c_str());
        c->Clear();
		
		TH2D * leadElectronHisto = nullptr;
		d->GetObject("leadElectronHisto", leadElectronHisto);
        leadElectronHisto->SetStats(0);
		leadElectronHisto->Scale(multConstant);
		leadElectronHisto->Draw("COLZ");
		c->Print((input+"_leadElectronHisto.png").c_str());
        c->Clear();
		
		TH2D * lowEtaMuonHisto = nullptr;
		d->GetObject("lowEtaMuonHisto", lowEtaMuonHisto);
        lowEtaMuonHisto->SetStats(0);
		lowEtaMuonHisto->Scale(multConstant);
		lowEtaMuonHisto->Draw("COLZ");
		c->Print((input+"_lowEtaMuonHisto.png").c_str());
        c->Clear();
		
		TH2D * lowEtaElectronHisto = nullptr;
		d->GetObject("lowEtaElectronHisto", lowEtaElectronHisto);
        lowEtaElectronHisto->SetStats(0);
		lowEtaElectronHisto->Scale(multConstant);
		lowEtaElectronHisto->Draw("COLZ");
		c->Print((input+"_lowEtaElectronHisto.png").c_str());
        c->Clear();
		
		TH2D * highEtaMuonHisto = nullptr;
		d->GetObject("highEtaMuonHisto", highEtaMuonHisto);
        highEtaMuonHisto->SetStats(0);
		highEtaMuonHisto->Scale(multConstant);
		highEtaMuonHisto->Draw("COLZ");
		c->Print((input+"_highEtaMuonHisto.png").c_str());
        c->Clear();
		
		TH2D * highEtaElectronHisto = nullptr;
		d->GetObject("highEtaElectronHisto", highEtaElectronHisto);
        highEtaElectronHisto->SetStats(0);
		highEtaElectronHisto->Scale(multConstant);
		highEtaElectronHisto->Draw("COLZ");
		c->Print((input+"_highEtaElectronHisto.png").c_str());
        c->Clear();
		
		TH2D * lowR2MuonHisto = nullptr;
		d->GetObject("lowR2MuonHisto", lowR2MuonHisto);
        lowR2MuonHisto->SetStats(0);
		lowR2MuonHisto->Scale(multConstant);
		lowR2MuonHisto->Draw("COLZ");
		c->Print((input+"_lowR2MuonHisto.png").c_str());
        c->Clear();
		
		TH2D * lowR2ElectronHisto = nullptr;
		d->GetObject("lowR2ElectronHisto", lowR2ElectronHisto);
        lowR2ElectronHisto->SetStats(0);
		lowR2ElectronHisto->Scale(multConstant);
		lowR2ElectronHisto->Draw("COLZ");
		c->Print((input+"_lowR2ElectronHisto.png").c_str());
        c->Clear();
		
		TH2D * highR2MuonHisto = nullptr;
		d->GetObject("highR2MuonHisto", highR2MuonHisto);
        highR2MuonHisto->SetStats(0);
		highR2MuonHisto->Scale(multConstant);
		highR2MuonHisto->Draw("COLZ");
		c->Print((input+"_highR2MuonHisto.png").c_str());
        c->Clear();
		
		TH2D * highR2ElectronHisto = nullptr;
		d->GetObject("highR2ElectronHisto", highR2ElectronHisto);
        highR2ElectronHisto->SetStats(0);
		highR2ElectronHisto->Scale(multConstant);
		highR2ElectronHisto->Draw("COLZ");
		c->Print((input+"_highR2ElectronHisto.png").c_str());
        c->Clear();
		
		
}
void extractHistos(){
		genHistos("out_long_WR800_N400", 10.41);
		genHistos("out_long_WR1200_N600", 1.947);
		genHistos("out_long_WR1200_N1000", 0.4296);
        genHistos("out_long_WR1600_N400", 0.7256);
        genHistos("out_long_WR1600_N800", 0.5188);
        genHistos("out_long_WR1600_N1200", 0.2129);
        genHistos("out_long_WR2000_N600", 0.2217);
        genHistos("out_long_WR2000_N1000", 0.1649);
        genHistos("out_long_WR2000_N1400", 0.08748);
        genHistos("out_long_WR2000_N1800", 0.01517);
		//genHistos("test", 147.4);
		
}
