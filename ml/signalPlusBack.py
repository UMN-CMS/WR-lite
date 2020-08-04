""""
Generates plots combining background with signal.
"""


import numpy as np
import pylab as plt
import matplotlib 
from matplotlib import cm
from matplotlib.colors import ListedColormap

def main():
    #Set font size
    font = {'size'   : 28}
    
    matplotlib.rc('font', **font)
    
    signalNames = ["WR800N200", "WR800N400", "WR800N600", "WR800N700", 
                   "WR1000N200", "WR1000N400", "WR1000N600", "WR1000N800", 
                   "WR1000N900", "WR1200N400", "WR1200N600", "WR1200N800", 
                   "WR1200N1000", "WR1200N1100", "WR1400N400", "WR1400N600", 
                   "WR1400N800", "WR1400N1000", "WR1400N1200", "WR1400N1300", 
                   "WR1600N400", "WR1600N600", "WR1600N800", "WR1600N1000", 
                   "WR1600N1200", "WR1600N1400", "WR1600N1500", "WR1800N400", 
                   "WR1800N600", "WR1800N800", "WR1800N1000", "WR1800N1200", 
                   "WR1800N1400", "WR1800N1600", "WR1800N1700", "WR2000N600", 
                   "WR2000N800", "WR2000N1000", "WR2000N1200", "WR2000N1400", 
                   "WR2000N1600", "WR2000N1800", "WR2000N1900"]

    #Load background files
    dy = np.load("DY.npy")
    ttbar = np.load("ttbar.npy")
    
    #Modify colormap to be white at 0
    viridis = cm.get_cmap('viridis', 256)
    newcolors = viridis(np.linspace(0, 1, 256))
    white = np.array([256/256, 256/256, 256/256, 1])
    newcolors[:1, :] = white
    cmap = ListedColormap(newcolors)
    
    resolvedNdy = []
    superResolvedNdy = []
    leadNdy = []
    subleadNdy = [] 
    WRdy =[]
    weightdy = []
    
    resolvedNttbar = []
    superResolvedNttbar = []
    leadNttbar = []
    subleadNttbar = [] 
    WRttbar =[]
    weightttbar = []
    
    #Extract ttbar background
    for x in range(len(ttbar)):
        resolvedNttbar.append(ttbar[x][2])
        superResolvedNttbar.append(ttbar[x][1])
        WRttbar.append(ttbar[x][0])
        leadNttbar.append(ttbar[x][5])
        subleadNttbar.append(ttbar[x][6])
        weightttbar.append(ttbar[x][-1]*1000.0*35.9)
      
    #Extract dy backgorund
    for x in range(len(dy)):
        resolvedNdy.append(dy[x][2])
        superResolvedNdy.append(dy[x][1])
        WRdy.append(dy[x][0])
        leadNdy.append(dy[x][5])
        subleadNdy.append(dy[x][6])
        weightdy.append(dy[x][-1]*1000.0*35.9)
    resolvedN = resolvedNttbar + resolvedNdy
    superResolvedN = superResolvedNttbar + superResolvedNdy
    leadN = leadNttbar + leadNdy
    subleadN = subleadNttbar + subleadNdy
    WR = WRttbar + WRdy
    weight = weightttbar + weightdy
    #Iterate over the signal samples
    for y in range(len(signalNames)):
        signal = np.load(signalNames[y]+".npy")

        resolvedN2 = []
        superResolvedN2 = []
        leadN2 = []
        subleadN2 = [] 
        WR2 =[]
        weight2=[]
        for x in range(len(signal)):
            resolvedN2.append(signal[x][2])
            superResolvedN2.append(signal[x][1])
            WR2.append(signal[x][0])
            leadN2.append(signal[x][5])
            subleadN2.append(signal[x][6])
            weight2.append(signal[x][-1]*1000.0*35.9)
             
        fSizeX = 13.5
        fSizeY = 9
        xMax=4000
        
        #Generate plots
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist(np.array(WR2), weights=np.array(weight2), bins=100, range=(0, 3000))
        plt.title("WR signal")
        plt.xlabel("m_lljj (GeV)")
        plt.savefig("signalBackground2/"+signalNames[y]+"/WR_signal.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(resolvedN2), np.array(WR2), weights=np.array(weight2), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("NN Resolved Leptons signal")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_signal.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(superResolvedN2), np.array(WR2), weights=np.array(weight2), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("NN Super Resolved Leptons signal")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_signal.png")
        plt.show()
        
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(resolvedN2), np.array(WR2)-np.array(resolvedN2), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [0, 3000]], cmap=cmap)
        plt.title("NN Resolved Leptons signal shifted part 1")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_signal_shift_p1.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(superResolvedN2), np.array(WR2)-np.array(superResolvedN2), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [0, 3000]], cmap=cmap)
        plt.title("NN Super Resolved Leptons signal shifted part 1")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_signal_shift_p1.png")
        plt.show()

        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(resolvedN2), np.log10(np.array(WR2)-np.array(resolvedN2)), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("NN Resolved Leptons signal shifted full\n")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_signal_shift.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(superResolvedN2), np.log10(np.array(WR2)-np.array(superResolvedN2)), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("NN Super Resolved Leptons signal shifted full\n")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_signal_shift.png")
        plt.show()
            
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist([np.array(WRttbar), np.array(WRdy)], weights=[np.array(weightttbar), np.array(weightdy)], bins=100, range=(0, 3000), stacked=True, label=["ttbar", "dy"])
        plt.title("WR background")
        plt.xlabel("m_lljj (GeV)")
        plt.legend()
        plt.savefig("signalBackground2/"+signalNames[y]+"/WR_background.png")
        plt.show()
        
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(resolvedN), np.array(WR), weights=np.array(weight), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("NN Resolved Leptons background")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_background.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(superResolvedN), np.array(WR), weights=np.array(weight), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("NN Super Resolved Leptons background")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_background.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(resolvedN), np.log10(np.array(WR)-np.array(resolvedN)), weights=np.array(weight), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("NN Resolved Leptons background")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_background_shift.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(superResolvedN), np.log10(np.array(WR)-np.array(superResolvedN)), weights=np.array(weight), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("NN Super Resolved Leptons background")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_background_shift.png")
        plt.show()
        
        fSizeX = 13.5
        fSizeY = 9
        xMax=4000
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist([np.array(WRttbar), np.array(WRdy), np.array(WR2)], weights=[np.array(weightttbar), np.array(weightdy), np.array(weight2)], bins=100, range=(0, 3000), stacked=True, label=["ttbar", "dy", "signal"])
        plt.title("WR signal + background")
        plt.xlabel("m_lljj (GeV)")
        plt.legend()
        plt.savefig("signalBackground2/"+signalNames[y]+"/WR_signal_plus_background.png")
        plt.show()
        
        
        resolvedN2 +=resolvedN
        superResolvedN2 +=superResolvedN
        leadN2 +=leadN
        subleadN2 +=subleadN
        WR2 += WR  
        weight2 += weight
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(resolvedN2), np.array(WR2), weights=np.array(weight2), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("NN Resolved Leptons combined")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_combined.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(superResolvedN2), np.array(WR2), weights=np.array(weight2), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("NN Super Resolved Leptons combined")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_combined.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(resolvedN2), np.log10(np.array(WR2)-np.array(resolvedN2)), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("NN Resolved Leptons combined shifted\n")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_Resolved_Leptons_combined_shift.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(superResolvedN2), np.log10(np.array(WR2)-np.array(superResolvedN2)), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("NN Super Resolved Leptons combined shifted\n")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/NN_SuperResolved_Leptons_combined_shift.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(leadN2), np.array(WR2), weights=np.array(weight2), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("Lead Leptons combined")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/Lead_Leptons_combined.png")
        plt.show()
        
        plt.figure(figsize=(fSizeY*2,fSizeY))
        plt.hist2d(np.array(subleadN2), np.array(WR2), weights=np.array(weight2), bins=[100,100], range=[[0,2500], [0, 3000]], cmap=cmap)
        plt.title("Sublead Leptons combined")
        plt.ylabel("m_lljj (GeV)")
        plt.xlabel("m_ljj (GeV)")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/Sublead_Leptons_combined.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(leadN2), np.log10(np.array(WR2)-np.array(leadN2)), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("Lead Leptons combined shifted")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/Lead_Leptons_combined_shift.png")
        plt.show()
        
        plt.figure(figsize=(fSizeX,fSizeY))
        plt.hist2d(np.array(subleadN2), np.log10(np.array(WR2)-np.array(subleadN2)), weights=np.array(weight2), bins=[100,100], range=[[0,xMax], [1, 5]], cmap=cmap)
        plt.title("Sublead Leptons combined shifted")
        plt.colorbar()
        plt.savefig("signalBackground2/"+signalNames[y]+"/Sublead_Leptons_combined_shift.png")
        plt.show()

if(__name__ == "__main__"):
    main()