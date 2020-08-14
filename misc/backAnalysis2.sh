address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..103}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-600to800/out_DYJetsToLL_M-50_HT-600to800_${i}.root > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done
