"""
Extract root TTrees with background and signal data into .npy files for use in
straight Python
"""

import ROOT
import numpy as np
from root_numpy import tree2array
#import tdrstyle

ROOT.ROOT.EnableImplicitMT()


treeFolder = "analysis/allEvents/"
treeName = "massData"
wrMassBranch = "WRMass"
SRmassBranch = "superResolvedNNMass"
RmassBranch = "resolvedNNMass"
correctMassBranch = "correctNMass"
incorrectMassBranch = "incorrectNMass"
leadMassBranch = "leadNMass"
subleadMassBranch = "subNMass" 
weightBranch =  "weight"


#numpy arrays

fileNames = ["DY", "ttbar",
			  "WR800N200", "WR800N400", "WR800N600", "WR800N700", 
            "WR1000N200", "WR1000N400", "WR1000N600", "WR1000N800", 
            "WR1000N900", "WR1200N400", "WR1200N600", "WR1200N800", 
            "WR1200N1000", "WR1200N1100", "WR1400N400", "WR1400N600", 
            "WR1400N800", "WR1400N1000", "WR1400N1200", "WR1400N1300", 
            "WR1600N400", "WR1600N600", "WR1600N800", "WR1600N1000", 
            "WR1600N1200", "WR1600N1400", "WR1600N1500", "WR1800N400", 
            "WR1800N600", "WR1800N800", "WR1800N1000", "WR1800N1200", 
            "WR1800N1400", "WR1800N1600", "WR1800N1700", "WR2000N600", 
            "WR2000N800", "WR2000N1000", "WR2000N1200", "WR2000N1400", 
            "WR2000N1600", "WR2000N1800", "WR2000N1900"]

for file in fileNames:
	rootfile= ROOT.TFile.Open("full"+file+".root", "read")

	massTree = rootfile.Get("full"+file)

	dataArray = tree2array(massTree, branches=[wrMassBranch,SRmassBranch,RmassBranch,correctMassBranch,incorrectMassBranch,leadMassBranch,subleadMassBranch,weightBranch])
	print(dataArray.shape)
	np.save(file+".npy",dataArray)