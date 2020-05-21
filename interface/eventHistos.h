#ifndef eventHistos_h
#define eventHistos_h


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

//ROOT CLASSES
#include "TH1D.h"
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
  void fillAll(eventBits& event);
  void fillNMinusOne(eventBits& event);
  
 
  TFileDirectory m_histoFolder;
  
  //METADATA
  

  //GEN PLOTS
   
  TH1D * m_l1qqHisto;
  TH1D * m_l2qqHisto;
  TH1D * m_llqqHisto;
  TH1D * m_subLqqHisto;

  TH1D * m_subMuJJhisto;
  TH1D * m_l2MuJJhisto;
  
  TH1D * m_subElectronJJhisto;
  TH1D * m_l2ElectronJJhisto;
  
  TH1D * m_nMinusOneHisto;
   
};

#endif
