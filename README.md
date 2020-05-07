# WR-lite
WR analysis, but lighter

This shiny new repository should serve as a helpful launch pad for a WR analysis.

*Instructions:*

On a machine setup for CMSSW (in your favorite folder) run:

```
source /local/grid/cmssoft/cms/cmsset_default.sh
cmsrel CMSSW_10_4_0_patch1
cd CMSSW_10_4_0_patch1/src/
cmsenv
mkdir ExoAnalysis
cd ExoAnalysis
git clone git@github.com:UMN-CMS/WR-lite.git
cd ..
scram b -j 8
```
To run the analysis on some sweet WR signal events:

```
source /local/grid/cmssoft/cms/cmsset_default.sh
cd /path_to_working_area/CMSSW_10_4_0_patch1/src/
cmsenv
cd ExoAnalysis/WR-lite
cmsRun python/cfg.py inputFiles=file:WRtoNLtoLLJJ_WR3000_N1600_9.root outputFile=out.root
