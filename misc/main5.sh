addressTwo="/home/kronh006/Version2/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/"

#Start WR 2000

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N600/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N600/out_WR2000N600_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N1900/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N1900/out_WR2000N1900_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N800/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N800/out_WR2000N800_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N1000/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N1000/out_WR2000N1000_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N1200/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N1200/out_WR2000N1200_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N1400/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N1400/out_WR2000N1400_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N1600/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N1600/out_WR2000N1600_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR2000_N1800/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR2000_N1800/out_WR2000N1800_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done