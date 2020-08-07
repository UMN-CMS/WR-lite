addressTwo="/home/kronh006/Version2/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/"
# Start WR 1200


address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1200_N400/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1200_N400/out_WR1200N400_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1200_N1100/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1200_N1100/out_WR1200N1100_${i}.root isSignal=True> /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1200_N600/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1200_N600/out_WR1200N600_${i}.root isSignal=True> /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1200_N800/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1200_N800/out_WR1200N800_${i}.root isSignal=True> /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1200_N1000/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1200_N1000/out_WR1200N1000_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


# Start WR 1400


address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1400_N400/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1400_N400/out_WR1400N400_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1400_N1300/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1400_N1300/out_WR1400N1300_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1400_N600/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1400_N600/out_WR1400N600_${i}.root isSignal=Truet > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done

address="/hdfs/cms/user/krohn045/WR_SignalSamples/WR1400_N800/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}MINIAOD_${i}.root  outputFile=${addressTwo}WR1400_N800/out_WR1400N800_${i}.root isSignal=True > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done
