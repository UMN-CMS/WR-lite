address="/hdfs/cms/user/evans908/wrSkims/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/"
for i in {392..592}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=/user/kronh006/Version2/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/TTTo2L2Nu/out_TTTo2L2Nu_${i}.root > /dev/null &
	if (( $i%14==1 )); then
		wait
	fi
done