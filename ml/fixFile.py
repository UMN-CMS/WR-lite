"""
Extracts data saved from the main root exectuion into a single file.
The five file names are "ml1.txt", "ml2.txt.",
"ml3.txt", "ml4.txt", and "ml5.txt".
Simply change these strings to change the names of the files used.
The data is saved as mlData.npy.

The output data is formated so that each row is:
lepton1Eta, lepton1EtaWR, lepton1DPhi, lepton1DR, lepton1Pt, lepton1sphericity,
lepton1NMass, lepton2Eta, lepton2EtaWR, lepton2DPhi, lepton2DR, lepton2Pt, 
lepton2sphericity, lepton2NMass, label, correct WR mass, correct N Mass.

The label is a 0 if the first lepton is correct and a 1 if the second is
correct. The correct masses are rounded to the nearest 100 GeV.
"""

import numpy as np

def main():
    
    data = np.loadtxt("ml.txt")
        
    dataSets=[]
    previous=[]
    current=[]
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
    print(data.shape)
    
    for x in range(data.shape[0]):
        if(abs(data[x,17]-currentN)==0):
            current.append(data[x])
        elif(abs(data[x,17]-previousN)==0):
            previous.append(data[x])
        else:
            if(previousN!=0.0):
                print("Appending:", previousWR, ",", previousN)
                print(np.array(previous).shape)
                dataSets.append(np.array(previous))
            previousN = currentN
            currentN = data[x,17]
            currentWR, previousWR = data[x,16], currentWR
            previous = current
            current=[]
            current.append(data[x])
    print("Appending:", previousWR, ",", previousN)
    dataSets.append(np.array(previous))
    print(np.array(previous).shape)
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))
    print(np.array(current).shape)
    print(len(dataSets))
    
    previous=[]
    current=[]
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
    data = np.loadtxt("ml2.txt")
    print(data.shape)
    
    for x in range(data.shape[0]):
        if(abs(data[x,17]-currentN)==0):
            current.append(data[x])
        elif(abs(data[x,17]-previousN)==0):
            previous.append(data[x])
        else:
            if(previousN!=0.0):
                print("Appending:", previousWR, ",", previousN)
                print(np.array(previous).shape)
                dataSets.append(np.array(previous))
            previousN = currentN
            currentN = data[x,17]
            currentWR, previousWR = data[x,16], currentWR
            previous = current
            current=[]
            current.append(data[x])
    print("Appending:", previousWR, ",", previousN)
    dataSets.append(np.array(previous))
    print(np.array(previous).shape)
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))
    print(np.array(current).shape)
    print(len(dataSets))
    
    previous=[]
    current=[]
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
    data = np.loadtxt("ml3.txt")
    print(data.shape)
    
    for x in range(data.shape[0]):
        if(abs(data[x,17]-currentN)==0):
            current.append(data[x])
        elif(abs(data[x,17]-previousN)==0):
            previous.append(data[x])
        else:
            if(previousN!=0.0):
                print("Appending:", previousWR, ",", previousN)
                print(np.array(previous).shape)
                dataSets.append(np.array(previous))
            previousN = currentN
            currentN = data[x,17]
            currentWR, previousWR = data[x,16], currentWR
            previous = current
            current=[]
            current.append(data[x])
    print("Appending:", previousWR, ",", previousN)
    dataSets.append(np.array(previous))
    print(np.array(previous).shape)
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))
    print(np.array(current).shape)
    print(len(dataSets))
    
    
    previous=[]
    current=[]
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
    data = np.loadtxt("ml4.txt")
    print(data.shape)
    
    for x in range(data.shape[0]):
        if(abs(data[x,17]-currentN)==0):
            current.append(data[x])
        elif(abs(data[x,17]-previousN)==0):
            previous.append(data[x])
        else:
            if(previousN!=0.0):
                print("Appending:", previousWR, ",", previousN)
                print(np.array(previous).shape)
                dataSets.append(np.array(previous))
            previousN = currentN
            currentN = data[x,17]
            currentWR, previousWR = data[x,16], currentWR
            previous = current
            current=[]
            current.append(data[x])
    print("Appending:", previousWR, ",", previousN)
    dataSets.append(np.array(previous))
    print(np.array(previous).shape)
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))
    print(np.array(current).shape)
    print(len(dataSets))
    
    previous=[]
    current=[]
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
    
    data = np.loadtxt("ml5.txt")
    print(data.shape)
    
    for x in range(data.shape[0]):
        if(abs(data[x,17]-currentN)==0):
            current.append(data[x])
        elif(abs(data[x,17]-previousN)==0):
            previous.append(data[x])
        else:
            if(previousN!=0.0):
                print("Appending:", previousWR, ",", previousN)
                print(np.array(previous).shape)
                dataSets.append(np.array(previous))
            previousN = currentN
            currentN = data[x,17]
            currentWR, previousWR = data[x,16], currentWR
            previous = current
            current=[]
            current.append(data[x])
    print("Appending:", previousWR, ",", previousN)
    dataSets.append(np.array(previous))
    print(np.array(previous).shape)
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))
    print(np.array(current).shape)
    print(len(dataSets))
    
    
    
    
    data=np.concatenate(dataSets)
    print(data.shape)
    np.save("mlData.npy", data)

if(__name__ == "__main__"):
    main()
