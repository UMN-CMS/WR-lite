"""
Creates new root files containing just the TTrees with output data
"""

import ROOT

import numpy as np
from root_numpy import tree2array

ROOT.ROOT.EnableImplicitMT()

def main():
    #Names within ttree
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
    
    #TTree file names
    fileNames = ["WR800N200", "WR800N400", "WR800N600", "WR800N700", 
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
    #Cross sections for different files
    crossSections = [14.46, 10.41, 4.351, 1.473, 
    	6.083, 5.023, 3.323, 1.256, 0.4125,
    	2.511, 1.947, 1.207, .4296, .1406,
    	1.321, 1.11, .825, .4887, .166, .05455,
    	.7256, .6375,.5188, .3731, .2129, .07031,.02318,
    	.4125, .3718, .3192, .2528, .1771, .09803,.03186, .01069,
    	.2217, .1962, .1649, .1281, .08747, .04720, .01517, .005147]
    
    
    for (files, xSec) in zip(fileNames, crossSections):
    
    	# make new root file with new tree
    	file = ROOT.TFile("full"+files+".root", 'recreate')
    	tree = ROOT.TTree("full"+files, "full"+files)
    	 
    	# create 1 dimensional float arrays as fill variables, in this way the float
    	# array serves as a pointer which can be passed to the branch
    
    	 
    	WRMass = np.zeros(1, dtype=float)
    	resolvedNNMass = np.zeros(1, dtype=float)
    	superResolvedNNMass = np.zeros(1, dtype=float)
    	correctNMass = np.zeros(1, dtype=float)
    	treeWeight = np.zeros(1, dtype=float)
    	incorrectNMass = np.zeros(1, dtype=float)
    	leadNMass = np.zeros(1, dtype=float)
    	subNMass = np.zeros(1, dtype=float)
    
    	tree.Branch("WRMass",WRMass,"WRMass/D");
    	tree.Branch("resolvedNNMass",resolvedNNMass,"resolvedNNMass/D");
    	tree.Branch("superResolvedNNMass",superResolvedNNMass,"superResolvedNNMass/D");
    	tree.Branch("correctNMass",correctNMass,"correctNMass/D");
    	tree.Branch("incorrectNMass",incorrectNMass,"incorrectNMass/D");
    	tree.Branch("leadNMass",leadNMass,"leadNMass/D");
    	tree.Branch("subNMass",subNMass,"subNMass/D");
    	tree.Branch("weight",treeWeight,"weight/D");
    	tree.Branch("weight2",treeWeight,"weight2/D");
    
    
    	rootfile= ROOT.TFile.Open(files+".root", "read")
    
    	massTree = rootfile.Get(treeFolder+treeName)
    	countHisto = rootfile.Get(treeFolder+"countHisto")
    	counts = countHisto.GetBinContent(1)
    	print(counts)
    	
    	WRmassArray = tree2array(massTree, branches=wrMassBranch)
    	SRmassArray = tree2array(massTree, branches=SRmassBranch)
    	RmassArray = tree2array(massTree, branches=RmassBranch)
    	correctMassArray = tree2array(massTree, branches=correctMassBranch)
    	incorrectMassArray = tree2array(massTree, branches=incorrectMassBranch)
    	leadMassArray = tree2array(massTree, branches=leadMassBranch)
    	subleadMassArray = tree2array(massTree, branches=subleadMassBranch)
    	weightArray = tree2array(massTree, branches=weightBranch)
    	weightArray = weightArray/float(counts)
    	weightArray = weightArray*xSec
    	
    	print(WRmassArray.shape)
    	print(WRmassArray.shape[0])
    	for i in range(WRmassArray.shape[0]):
    		WRMass[0] = WRmassArray[i]
    		resolvedNNMass[0] = RmassArray[i]
    		superResolvedNNMass[0] = SRmassArray[i]
    		correctNMass[0] = correctMassArray[i]
    		treeWeight[0] = weightArray[i]
    		incorrectNMass[0] = incorrectMassArray[i]
    		leadNMass[0] = leadMassArray[i]
    		subNMass[0] = subleadMassArray[i]
    		tree.Fill()
    
    	 
    	# write the tree into the output file and close the file
    	file.Write()
    	file.Close()
    
if(__name__ == "__main__"):
    main()    
