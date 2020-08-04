address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=/user/kronh006/Version2/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/DYJetsToLL_M-50_HT-800to1200/out_DYJetsToLL_M-50_HT-800to1200_${i}.root > /dev/null &
	if (( $i%14==10 )); then
		wait
	fi
done
