
cd Version3/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/DYJetsToLL_M-50_HT-100to200  

rm DY100to200.root
hadd DY100to200.root *.root

cd ../DYJetsToLL_M-50_HT-1200to2500  
rm DY1200to2500.root
hadd DY1200to2500.root *.root

cd ../DYJetsToLL_M-50_HT-200to400  
rm DY200to400.root
hadd DY200to400.root *.root 

cd ../DYJetsToLL_M-50_HT-2500toInf 
rm DY2500toInf.root
hadd DY2500toInf.root *.root

cd ../DYJetsToLL_M-50_HT-400to600 
rm DY400to600.root
hadd DY400to600.root *.root  

cd ../DYJetsToLL_M-50_HT-600to800 
rm DY600to800.root
hadd DY600to800.root *.root
  
cd ../DYJetsToLL_M-50_HT-800to1200 
rm DY800to1200.root
hadd DY800to1200.root *.root     
     
cd ../TTTo2L2Nu    
rm TTTo2L2Nu.root
hadd TTTo2L2Nu.root *.root
 
cd ..
scp -r DY*/DY*.root /home/kronh006
scp -r TT*/TT*.root /home/kronh006

cd ..
cd ..
cd ..
cd ..
cd ..



cd Version2/CMSSW_10_4_0_patch1/src/ExoAnalysis/WR_lite/WR1000_N200
rm WR1000N200.root
hadd WR1000N200.root *.root    
            
cd ../WR1000_N400   
rm WR1000N400.root
hadd WR1000N400.root *.root    
              
cd ../WR1000_N600          
rm WR1000N600.root
hadd WR1000N600.root *.root    

cd ../WR1000_N800                 
rm WR1000N800.root
hadd WR1000N800.root *.root    

cd ../WR1000_N900                  
rm WR1000N900.root
hadd WR1000N900.root *.root    

cd ../WR1200_N1000                
rm WR1200N1000.root
hadd WR1200N1000.root *.root    

cd ../WR1200_N1100                
rm WR1200N1100.root
hadd WR1200N1100.root *.root    

cd ../WR1200_N400                
rm WR1200N400.root
hadd WR1200N400.root *.root    

cd ../WR1200_N600                
rm WR1200N600.root
hadd WR1200N600.root *.root    

cd ../WR1200_N800            
rm WR1200N800.root
hadd WR1200N800.root *.root    

cd ../WR1400_N1000          
rm WR1400N1000.root
hadd WR1400N1000.root *.root    

cd ../WR1400_N1200    
rm WR1400N1200.root
hadd WR1400N1200.root *.root    

cd ../WR1400_N1300          
rm WR1400N1300.root
hadd WR1400N1300.root *.root    

cd ../WR1400_N400          
rm WR1400N400.root
hadd WR1400N400.root *.root    

cd ../WR1400_N600           
rm WR1400N600.root
hadd WR1400N600.root *.root    

cd ../WR1400_N800                
rm WR1400N800.root
hadd WR1400N800.root *.root    

cd ../WR1600_N1000              
rm WR1600N1000.root
hadd WR1600N1000.root *.root    

cd ../WR1600_N1200              
rm WR1600N1200.root
hadd WR1600N1200.root *.root    

cd ../WR1600_N1400                  
rm WR1600N1400.root
hadd WR1600N1400.root *.root    

cd ../WR1600_N1500                   
rm WR1600N1500.root
hadd WR1600N1500.root *.root    

cd ../WR1600_N400                    
rm WR1600N400.root
hadd WR1600N400.root *.root    

cd ../WR1600_N600                    
rm WR1600N600.root
hadd WR1600N600.root *.root    

cd ../WR1600_N800                    
rm WR1600N800.root
hadd WR1600N800.root *.root    

cd ../WR1800_N1000                   
rm WR1800N1000.root
hadd WR1800N1000.root *.root    

cd ../WR1800_N1200                   
rm WR1800N1200.root
hadd WR1800N1200.root *.root    

cd ../WR1800_N1400                   
rm WR1800N1400.root
hadd WR1800N1400.root *.root    

cd ../WR1800_N1600                   
rm WR1800N1600.root
hadd WR1800N1600.root *.root    

cd ../WR1800_N1700                   
rm WR1800N1700.root
hadd WR1800N1700.root *.root    

cd ../WR1800_N400                    
rm WR1800N400.root
hadd WR1800N400.root *.root    

cd ../WR1800_N600                    
rm WR1800N600.root
hadd WR1800N600.root *.root    

cd ../WR1800_N800                    
rm WR1800N800.root
hadd WR1800N800.root *.root    

cd ../WR2000_N1000                   
rm WR2000N1000.root
hadd WR2000N1000.root *.root    

cd ../WR2000_N1200                   
rm WR2000N1200.root
hadd WR2000N1200.root *.root    

cd ../WR2000_N1400            
rm WR2000N1400.root
hadd WR2000N1400.root *.root    

cd ../WR2000_N1600 
rm WR2000N1600.root
hadd WR2000N1600.root *.root    

cd ../WR2000_N1800 
rm WR2000N1800.root
hadd WR2000N1800.root *.root    

cd ../WR2000_N1900
rm WR2000N1900.root
hadd WR2000N1900.root *.root    

cd ../WR2000_N600
rm WR2000N600.root
hadd WR2000N600.root *.root    

cd ../WR2000_N800
rm WR2000N800.root
hadd WR2000N800.root *.root    

cd ../WR800_N200
rm WR800N200.root
hadd WR800N200.root *.root    

cd ../WR800_N400
rm WR800N400.root
hadd WR800N400.root *.root    

cd ../WR800_N600
rm WR800N600.root
hadd WR800N600.root *.root    

cd ../WR800_N700
rm WR800N700.root
hadd WR800N700.root *.root    

cd ..


scp -r WR*/WR*.root /home/kronh006
scp WR2000_N1900/WR2000N1900.root /home/kronh006

cd ..
cd ..
cd ..
cd ..
cd ..