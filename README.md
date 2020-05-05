# WR-lite
WR analysis, but lighter

This shiny new repository should serve as a helpful launch pad for a WR analysis.

*Instructions:*

In an area setup for CMSSW run:

```cmsrel CMSSW_10_4_0_patch1
cd CMSSW_10_4_0_patch1/src/
cmsenv
mkdir ExoAnalysis
cd ExoAnalysis
git clone git@github.com:UMN-CMS/WR-lite.git
cd ..
scram b -j 8
