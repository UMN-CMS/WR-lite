#ifndef eventInfo_h
#define eventInfo_h

//CMSSW CLASSES
#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

//ROOT CLASSES
#include "TObjString.h"
//C++ CLASSES
#include <iostream>
//LOCAL CLASSES
#include "eventHistos.h"
#include "eventBits.h"

class eventInfo {
	public:
		eventInfo();
		~eventInfo();
		bool PVselection(edm::Handle<std::vector<reco::Vertex>> vertices);

		int nVtx;
		const reco::Vertex* PVertex;
	
	private:

};

#endif