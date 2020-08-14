address="/hdfs/cms/user/evans908/wrSkims/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/"
for i in {1..195}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=TTTo2L2Nu/out_TTTo2L2Nu_${i}.root > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done
