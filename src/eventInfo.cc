#include "ExoAnalysis/WR_lite/interface/eventInfo.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//C++ CLASSES
#include <iostream>
#include <algorithm>
//LOCAL CLASSES

#include "DataFormats/VertexReco/interface/Vertex.h"


eventInfo::eventInfo () {


}

eventInfo::~eventInfo() {

}



bool eventInfo::PVselection(edm::Handle<std::vector<reco::Vertex>> vertices) {

	bool isPV = false;
	// Let's check that we have at least one good vertex!
	//std::cout << "Running vertex selection" << std::endl;
	std::vector<const reco::Vertex*> PVertices;
	std::vector<reco::Vertex>::const_iterator firstGoodVertex = vertices->end();

	int Nvtx = 0;

	for (std::vector<reco::Vertex>::const_iterator it=vertices->begin(); it!=vertices->end(); ++it) {
		if (!it->isFake() && it->ndof()>4 && it->position().Rho()<2. && std::abs(it->position().Z())<24.) {
			Nvtx++;
			if(firstGoodVertex == vertices->end()){
				firstGoodVertex = it;
				PVertices.push_back(&(*it));
			}
		}
	}

	nVtx = Nvtx;
		if(firstGoodVertex == vertices->end()){
		std::cout<<"NO GOOD VERTEX" << std::endl;
	return isPV;
	} else {
		isPV = true;
	}

	PVertex = PVertices.at(0);

	return isPV;
}
