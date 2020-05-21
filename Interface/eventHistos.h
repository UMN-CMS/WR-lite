#ifndef eventHistos_h
#define eventHistos_h


#include "CommonTools/Utils/interface/TFileDirectory.h"

//ROOT CLASSES
#include "TH1.h"
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
   
  TH1D * l1qqHisto;
  TH1D * l2qqHisto;
  TH1D * llqqHisto;
  TH1D * subLqqHisto;

  TH1D * subMuJJhisto;
  TH1D * l2MuJJhisto;
  
  TH1D * subElectronJJhisto;
  TH1D * l2ElectronJJhisto;
  
  TH1D * nMinusOneHisto;
   
};

#endif
