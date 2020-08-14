#!/bin/bash

address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..20}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-100to200/out_DYJetsToLL_M-50_HT-100to200_${i}.root > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..12}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-200to400/out_DYJetsToLL_M-50_HT-200to400_${i}.root > /dev/null &
	if (( $i%7==1 )); then
		wait
	fi
done

wait

address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..9}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-400to600/out_DYJetsToLL_M-50_HT-400to600_${i}.root > /dev/null &
done

wait

address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..28}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-800to1200/out_DYJetsToLL_M-50_HT-800to1200_${i}.root > /dev/null &
	if (( $i%7==0 )); then
		wait
	fi
done


wait

address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..8}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-1200to2500/out_DYJetsToLL_M-50_HT-1200to2500_${i}.root > /dev/null &
	if (( $i%7==3 )); then
		wait
	fi
done



address="/hdfs/cms/user/evans908/wrSkims/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/"
for i in {1..4}
do
	cmsRun python/cfg.py inputFiles=file:${address}skimmedOut_${i}.root  outputFile=DYJetsToLL_M-50_HT-2500toInf/out_DYJetsToLL_M-50_HT-2500toInf_${i}.root > /dev/null &
	if (( $i%7==2 )); then
		wait
	fi
done


