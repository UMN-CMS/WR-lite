# WR-lite
WR analysis, but lighter, with some machine learning.

*Setup Instructions:*

On a machine setup for CMSSW (in your favorite folder) run:

```
source /local/grid/cmssoft/cms/cmsset_default.sh
cmsrel CMSSW_10_4_0_patch1
cd CMSSW_10_4_0_patch1/src/
cmsenv

git cms-init

git clone https://github.com/Sam-Harper/HEEP.git
cd HEEP
git checkout HEEPV70  #this is currently the default branch for now but may change in the future
cd ..

git cms-merge-topic lathomas:L1Prefiring_M

mkdir ExoAnalysis
cd ExoAnalysis
git clone https://github.com/UMN-CMS/WR-lite.git WR_lite
cd ..
cd ..
scram b -j32
```

*Basic Use*

To run the analysis on some WR signal events:

```
source /local/grid/cmssoft/cms/cmsset_default.sh
cd /path_to_working_area/CMSSW_10_4_0_patch1/src/
cmsenv
cd ExoAnalysis/WR-lite
cmsRun python/cfg.py inputFiles=file:signalFile.root outputFile=out.root isSignal=True
```

To run the analysis on signal and save training data:
```
source /local/grid/cmssoft/cms/cmsset_default.sh
cd /path_to_working_area/CMSSW_10_4_0_patch1/src/
cmsenv
cd ExoAnalysis/WR-lite
cmsRun python/cfg.py inputFiles=file:signalFile.root outputFile=out.root genTrainData=True  trainFile=trainFile.txt isSignal=True
```

To run the analysis on background: 
```
source /local/grid/cmssoft/cms/cmsset_default.sh
cd /path_to_working_area/CMSSW_10_4_0_patch1/src/
cmsenv
cd ExoAnalysis/WR-lite
cmsRun python/cfg.py inputFiles=file:signalFile.root outputFile=out.root
```

For iterating over more files, see the backAnalysis.sh and main.sh files in the misc folder. Naturally, the file location variables will have to be changed before any of them can be used. Further, these scripts assume that you have folders with names like WR2000N800 in existence for all the mass combinations processed.

*Histogram Extraction*
After running the analysis code there will be many root files generated with histograms. These can be extracted using the extractDY.cc, extractTTbar.cc, and extractMain.cc files in the misc folder. They will work without modificiation if you have run the shell scripts from the misc folder first, and you put the files in the directroy containg the directories like WR2000N800. To run them, simply run:
```
root -b
.x extractMain.cc
```
You must exit out of root each time. The ttbar and DY files will be saved in the directory the programs are run in, and the signal histograms will be saved in the directories wih the root files.

*TTree Extraction*
All signal and background root files have TTrees saved in them which can be used to make signal vs. background plots. Assuming you ran the shell scripts, simply go to your top directory, modify the extractRootFiles.sh file to have the correct paths, and run it. This will combine all the root files for each mass point and background type into one file and copy them to the top directory. After this, move the corresponding python programs to the top directory and run the following four commands:

```
python cleanMasses.py
python combineDY.py
python combineTTbar.py
python extract.py
```
Running these commands will format the root files appropriately, then extract for each signal file, for DY, and for ttbar and .npy binary file containing the contents of the TTree. Each entry of the TTree is:
("WRMass", "Super Resolved N mass", "Resolved N mass", "correct N Mass", "incorrect N Mass", "lead N Mass", "sublead N Mass", "weightBranch1", "weightBranch2")

These are all fairly self evident, except the two weight branches. The first weight is obtained by summing over all the weights from the events procesed, and taking the event weight for a specifict event, multiplying it by cross section for the event type, and dividing it by the sum. For the second weight, it is the same, except the number of pre skim events is used instead of the the sum of the processed weights. This means the second weight is on average 10 times smaller than the first.


*Python processing*

This is all the work from the repository which is done in the CMSSW environment. The rest is done in a seperate python 3.6 environment with up to date (as of August 2020) instalations of tensorflow, matplotlib, and numpy.

The most important thing this environment is used for is the training of the neural networks. This is accomplished by copying ml1.txt, ... , ml5.txt into the same directory as fixFile.py. This will combine these 5 files into a .npy binary file and reorder the entries so that all data from the same mass points is togther.

Next, to acutally do the machine learning, run nnByMass.py. First though make sure mlData.npy is in the same folder and that there are two folders named Resolved and SuperResolved in this folder. Running the python script will train a Resolved network using the data with N/WR <0.75, and a Super Resolved network. To generate some perforamcne graphs, run mlPredict.py.

To generate signal/background graphs, use signalPlusBack.py


