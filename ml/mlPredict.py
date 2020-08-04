"""
Makes predictions from saved nerual networks.
Put the names of the network folders in the list on line 111 and put the names
as they should appear in the list on line 113.
Graphs will be generated of interpolated and then relaxed accuracy and metric
for each mass network. Additionally, the metric will be plotted for each
mass point and each network. 
"""

from math import ceil
import numpy as np
import pylab as plt
import matplotlib
from matplotlib import cm
from matplotlib.colors import ListedColormap

def matrixMult(a, b, dim1, dim2, dim3):
    newMatrix = np.matmul(b,a.T)
    return(newMatrix)
    
def matrixAdd(a, b, dim1, dim2):
    newMatrix = np.add(a,b.T[0])

    return(newMatrix)
    
def leakyReLU(a, dim1, dim2):
    newMatrix = np.where(a<0, a*0.2, a)
    return(newMatrix)

def sigmoid(a, dim1, dim2):
    newMatrix = np.exp(a)/(np.exp(a)+1)
    return(newMatrix)
    
def roundPredictions(a, dim1, dim2):
    newMatrix = np.where(a<0.5, 0.0, 1.0)
    return(newMatrix)


def main():
    
    #Modify color map to be white for 0
    viridis = cm.get_cmap('viridis', 256)
    newcolors = viridis(np.linspace(0, 1, 256))
    white = np.array([256/256, 256/256, 256/256, 1])
    newcolors[:1, :] = white
    cmap = ListedColormap(newcolors)
    
    #Set font size to 22
    font = {'size'   : 22}
    matplotlib.rc('font', **font)
    
    #Collect data
    data = np.load("mlDataV2.npy")
    print(data.shape)
    
    dataSets=[]
    previous=[]
    current=[]
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
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
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))


    setNames = ["WR800N400","WR800N600","WR800N700", "WR1000N200", 
                "WR1000N900","WR1000N400", "WR1000N600", "WR1000N800", "WR800N200",  
                "WR1200N400", "WR1200N1100", "WR1200N600", "WR1200N800", "WR1200N1000",
                "WR1400N400", "WR1400N1300", "WR1400N600", "WR1400N800", "WR1400N1000",
                "WR1400N1200",
                "WR1600N400", "WR1600N1500", "WR1600N600", "WR1600N800", 
                "WR1600N1000", "WR1600N1200", "WR1600N1400",
                "WR1800N400", "WR1800N1700", "WR1800N600", "WR1800N800", "WR1800N1000", 
                "WR1800N1200","WR1800N1400", "WR1800N1600",
                "WR2000N600", "WR2000N1900", "WR2000N800", "WR2000N1000", "WR2000N1200", "WR2000N1400",
                "WR2000N1600", "WR2000N1800"]
    
    massSplits = [[800,400],[800,600],[800,700],[1000,200],
                [1000,900],[1000,400],[1000,600],[1000,800],[800,200],
                [1200,400],[1200,1100],[1200,600],[1200,800],[1200,1000],
                [1400,400],[1400,1300],[1400,600],[1400,800],[1400,1000],
                [1400,1200],
                [1600,400],[1600,1500],[1600,600],[1600,800], 
                [1600,1000],[1600,1200],[1600,1400],
                [1800,400],[1800,1700],[1800,600],[1800,800],[1800,1000], 
                [1800,1200],[1800,1400],[1800,1600],
                [2000,600],[2000,1900],[2000,800],[2000,1000],[2000,1200],[2000,1400],
                [2000,1600],[2000,1800]]
    
    #Names of folders with the neural networks    
    setNamesShort = ["resolvedWeighted3", "superResolvedWeighted3"] 
    #Names of networks to print on graphs
    setNamesPrint= ["resolved", "super resolved"] 
    base = 2     
    
    
    for (names, titleNames) in zip(setNamesShort, setNamesPrint):
        xVals=[]
        yVals=[]
        accuracies=np.zeros((185, 125))
        metric=np.zeros((185, 125))
        metric2=np.zeros((185, 125))
        weights = []
        biases = []
        
        xVals=[]
        yVals=[]
        
        #Load network
        for x in range(3):
            weights.append(np.loadtxt(names+"/weights_"+str(x)+".txt", delimiter = ","))
            biases.append(np.loadtxt(names+"/biases_"+str(x)+".txt", delimiter = ","))
            if(x<2):
                biases[x] = biases[x].reshape((biases[x].shape[0]),1)
            else:
                biases[x]  = biases[x].reshape(1,1)
                weights[x] = np.reshape(weights[x], (1,20))
        
        
        for setNumber in range(len(setNames)):
            data = dataSets[setNumber].T
            correctLeptonsWR=[]
            incorrectLeptonsWR=[]
            correctLeptonsN=[]
            incorrectLeptonsN=[]
            
            dataT = data.T
            #Collect the correct and incorrect WR, N masses
            for x in range(len(dataT)):
                if(dataT[x, -3]==0):
                    correctLeptonsWR.append(dataT[x,14])
                    correctLeptonsN.append(dataT[x,6])
                    incorrectLeptonsWR.append(dataT[x,14])
                    incorrectLeptonsN.append(dataT[x,13])
                else:
                    correctLeptonsWR.append(dataT[x,14])
                    correctLeptonsN.append(dataT[x,13])
                    incorrectLeptonsWR.append(dataT[x,14])
                    incorrectLeptonsN.append(dataT[x,6])
                    
            dataNormed = np.copy(data)
            dataNormed[4] = dataNormed[4]/dataNormed[14]
            dataNormed[11] = dataNormed[11]/dataNormed[14]
            
            dataNormed = np.concatenate(
                                     [np.reshape(dataNormed[0,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[1,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[3,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[4,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[7,:],(1, len(dataNormed[-3,:]))),                                     
                                     np.reshape(dataNormed[8,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[10,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[11,:],(1, len(dataNormed[-3,:]))),
                                     np.reshape(dataNormed[-3,:],(1, len(dataNormed[-3,:])))])
            dims=8
            
            #Normalize data
            normInfo = np.loadtxt(names+"/normInfo.txt", delimiter = ",")
            for x in range(dims):                
                dataNormed[x]=(dataNormed[x]-normInfo[x,0])/normInfo[x,1]

            newData=[]
            for x in range(dims):
                newData.append(dataNormed[x])
            
                
            inputVal=dataNormed[:dims].T
            outputData=dataNormed[dims:].T
            
            #Perform predictions
            for x in range(3):
                inputVal = matrixMult(weights[x], inputVal, weights[x].shape[0], inputVal.shape[1], inputVal.shape[0])
                inputVal = matrixAdd(inputVal, biases[x], inputVal.shape[0], inputVal.shape[1])
                if(x==2):
                    inputVal = sigmoid(inputVal, inputVal.shape[0], inputVal.shape[1])        
                else:
                    inputVal = leakyReLU(inputVal, inputVal.shape[0], inputVal.shape[1])
            inputVal=roundPredictions(inputVal, inputVal.shape[0], inputVal.shape[1])
            correctCount = 0
            incorrectCount = 0
            metricTemp=[]
            for x in range(len(outputData)):
                if(outputData[x,0]==inputVal[x,0]):
                    correctCount+=1
                    metricTemp.append(0)
                else:
                    incorrectCount+=1
                    metricTemp.append(abs(correctLeptonsN[x]-incorrectLeptonsN[x]))

            correctLeptonsN = np.array(correctLeptonsN)
            sigma = np.sqrt(np.sum(correctLeptonsN**2)/len(correctLeptonsN) - (np.sum(correctLeptonsN)/len(correctLeptonsN))**2)
            
            #Plot of metric for individual mass point
            plt.figure(figsize=(9,6))
            plt.hist(np.power(base, -np.array(metricTemp)/sigma), bins=50)
            plt.title("Metric of " + titleNames + "\nfor "+ setNames[setNumber])
            plt.tight_layout()
            plt.savefig("metric/Metric_of_" + names + "_for_masses_"+ setNames[setNumber]+ "_base_"+str(base)+".png")
            plt.show()
            plt.figure(figsize=(9,6))
            plt.hist(np.power(base, -np.array(metricTemp)/sigma), bins=50, cumulative=True, density=True)
            plt.title("Metric of " + titleNames + "\nfor " + setNames[setNumber]+" cummulative")
            plt.tight_layout()
            plt.savefig("metric/Metric_of_" + names + "_for_masses_"+ setNames[setNumber]+ "_base_"+str(base)+"_cummulative.png")
            plt.show()

            xVals.append(massSplits[setNumber][0])
            yVals.append(massSplits[setNumber][1])

            accuracies[yVals[-1]//10-18,xVals[-1]//10-78]=correctCount/len(outputData)
            metric2[yVals[-1]//10-18,xVals[-1]//10-78]=np.mean(np.array(metricTemp)/sigma)
            metricTemp = np.mean(np.power(base, -np.array(metricTemp)/sigma))
            metric[yVals[-1]//10-18,xVals[-1]//10-78]=metricTemp
        
        #Interpolate vertical lines throug the data points
        for x in range(124):
            for y in range(179):
                
                if(x%20==2 and accuracies[y,x]==0 and y<x+40):
                    bottom=((y-2)//20)*20+2
                    top=bottom+20
                    if(accuracies[bottom,x]==0.0):
                        continue
                    accuracies[y,x] = (accuracies[top,x] - accuracies[bottom,x])*(y-bottom)/20 + accuracies[bottom,x]
                    metric[y,x] = (metric[top,x] - metric[bottom,x])*(y-bottom)/20 + metric[bottom,x]
                    metric2[y,x] = (metric2[top,x] - metric2[bottom,x])*(y-bottom)/20 + metric2[bottom,x]
                    
                elif(x%20==2 and accuracies[y,x]==0 and y<x+50 and y>=x/5):
                    bottom=((y-2)//10)*10+2
                    top=bottom+10
                    accuracies[y,x] = (accuracies[top,x] - accuracies[bottom,x])*(y-bottom)/10 + accuracies[bottom,x]
                    metric[y,x] = (metric[top,x] - metric[bottom,x])*(y-bottom)/10 + metric[bottom,x]
                    metric2[y,x] = (metric2[top,x] - metric2[bottom,x])*(y-bottom)/10 + metric2[bottom,x]
                           
                
        #Interpolate horizontal lines through the interpolated vertical ones      
        for x in range(124):
            for y in range(179):
                if(x%20!=2 and accuracies[y,x]==0):
                    left=((x-2)//20)*20+2
                    right=left+20
                    if(left<0 or right > 124 or accuracies[y, left]==0.0 or accuracies[y, right]==0.0):
                        continue
                    accuracies[y,x] = (accuracies[y, right] - accuracies[y, left])*(x-left)/20 + accuracies[y,left]
                    metric[y,x] = (metric[y, right] - metric[y, left])*(x-left)/20 + metric[y,left]
                    metric2[y,x] = (metric2[y, right] - metric2[y, left])*(x-left)/20 + metric2[y,left]

         
        for x in range(3,123):
            #Interpolate along the upper diagonal and vertically between this
            #line and the nearest filled one below
            if(x%20!=2):
                y=x+50
                bottom = ((y-12)//20)*20+12
                top=bottom+20
                left=((x-2)//20)*20+2
                right=left+20
                accuracies[y,x] = (accuracies[top,right] - accuracies[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(800)**0.5 + accuracies[bottom,left]
                metric[y,x] = (metric[top,right] - metric[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(800)**0.5 + metric[bottom,left]
                metric2[y,x] = (metric2[top,right] - metric2[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(800)**0.5 + metric2[bottom,left]
                
                for n in range(bottom+1,y):
                    accuracies[n,x] = (accuracies[y,x]-accuracies[bottom,x])*(n-bottom)/(y-bottom)+accuracies[bottom,x]
                    metric[n,x] = (metric[y,x]-metric[bottom,x])*(n-bottom)/(y-bottom)+metric[bottom,x]
                    metric2[n,x] = (metric2[y,x]-metric2[bottom,x])*(n-bottom)/(y-bottom)+metric2[bottom,x]
            
            #Interpolate along the first bottom diagonal and fill up
            if(x>22 and x<102):
                y=(x-2)/4-3
                bottom = 2
                top=22
                left=22
                right=102
                valA= (accuracies[top,right] - accuracies[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(80**2+20**2)**0.5 + accuracies[bottom,left]
                valM= (metric[top,right] - metric[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(80**2+20**2)**0.5 + metric[bottom,left]
                valM2= (metric2[top,right] - metric2[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(80**2+20**2)**0.5 + metric2[bottom,left]
                
                startVal=ceil(y)
                if(x%4!=2):
                    startVal+=1
                startVal-=1
                for n in range(startVal, top):
                    accuracies[n,x] = (accuracies[top,x]-valA)*(n-y)/(top-startVal)+valA
                    metric[n,x] = (metric[top,x]-valM)*(n-y)/(top-startVal)+valM
                    metric2[n,x] = (metric2[top,x]-valM2)*(n-y)/(top-startVal)+valM2
            
            #Interpolate along the second bottom diagonal and fill up
            if(x>102 and x <122):
                y=x-80
                bottom = ((y-2)//20)*20+12
                top=bottom+20
                left=((x-2)//20)*20+2
                right=left+20
                accuracies[y,x] = (accuracies[top,right] - accuracies[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(800)**0.5 + accuracies[bottom,left]
                metric[y,x] = (metric[top,right] - metric[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(800)**0.5 + metric[bottom,left]
                metric2[y,x] = (metric2[top,right] - metric2[bottom,left])*((y-bottom)**2+(x-left)**2)**0.5/(800)**0.5 + metric2[bottom,left]
               
                for n in range(y+1, top):
                    accuracies[n,x] = (accuracies[top,x]-accuracies[y,x])*(n-y)/(top-y)+accuracies[y,x]
                    metric[n,x] = (metric[top,x]-metric[y,x])*(n-y)/(top-y)+metric[y,x]
                    metric2[n,x] = (metric2[top,x]-metric2[y,x])*(n-y)/(top-y)+metric2[y,x]

        for x in range(2,124):
            #Extrapolate up from the top diagonal, just continue with the value
            #along the diagonal
            for n in range(x+51, min(x+61,183)):
                accuracies[n,x] = accuracies[x+50, x] 
                metric[n,x] = metric[x+50, x] 
                metric2[n,x] = metric2[x+50, x] 
            #Extrapolate down below first diagonal
            if(x>102):
                for n in range(2, x-80):
                    accuracies[n,x] = accuracies[x-80, x] 
                    metric[n,x] = metric[x-80, x]  
                    metric2[n,x] = metric2[x-80, x]
            #Extrapolate down below second diagonal
            if(x>22 and x<102):
                if(x%4==2):   
                    for n in range(2, int((x-2)/4-2)):
                        accuracies[n,x] = accuracies[ int((x-2)/4-2), x]
                        metric[n,x] = metric[ int((x-2)/4-2), x]
                        metric2[n,x] = metric2[ int((x-2)/4-2), x]
                else:          
                    for n in range(2, int((x-2)/4-1)):
                        accuracies[n,x] = accuracies[ int((x-2)/4-1), x] 
                        metric[n,x] = metric[ int((x-2)/4-1), x] 
                        metric2[n,x] = metric2[ int((x-2)/4-1), x]                 
          
        #Perform relaxation to smooth out the graph
        for n in range(50):
            for x in range(3, 122):
                for y in range(2,184):
                    if((x%20!=2 or y%20!=2) and not (x>120 and y==x-80) and not( x>22 and x<102 and y ==ceil((x-2)/4-3)) and not y==x+50 and not y>x+59 and not(x>2 and x<22 and y==2)):
                        if(y!=2):
                            accuracies[y,x]=(accuracies[y,x-1]+accuracies[y,x+1]+accuracies[y+1,x]+accuracies[y-1,x])/4
                            metric[y,x]=(metric[y,x-1]+metric[y,x+1]+metric[y+1,x]+metric[y-1,x])/4
                            metric2[y,x]=(metric2[y,x-1]+metric2[y,x+1]+metric2[y+1,x]+metric2[y-1,x])/4
                        else:
                            accuracies[y,x]=(accuracies[y,x-1]+accuracies[y,x+1]+accuracies[y+1,x])/3
                            metric[y,x]=(metric[y,x-1]+metric[y,x+1]+metric[y+1,x])/3
                            metric2[y,x]=(metric2[y,x-1]+metric2[y,x+1]+metric2[y+1,x])/3


        #Make plots
        plt.figure(figsize=(9,13.5))
        plt.imshow(accuracies, cmap=cmap, origin="lower", extent=(775,2025, 175, 2025), vmin=0.0, vmax=1.0)
        plt.plot([800,2000], [800,2000], label="1")
        plt.plot([800,2000], [700,1750], label="0.875")
        plt.plot([800,2000], [600,1500], label="0.75")
        plt.plot([800,2000], [500,1250], label="0.625")
        plt.plot([800,2000], [400,1000], label="0.5")
        plt.title("Accuracy of\n" + titleNames )
        plt.xlabel("WR Mass (GeV)")
        plt.ylabel("N Mass (GeV)")
        plt.colorbar()
        plt.legend()
        plt.scatter(xVals, yVals, marker="x", color="r")
        plt.tight_layout()
        plt.savefig("metric/Accuracy_of_" + names+".png")
        plt.show()
                

        
        plt.figure(figsize=(9,13.5))
        plt.imshow(metric, cmap=cmap, origin="lower", extent=(775,2025, 175, 2025), vmin=0.0, vmax=1.0)
        plt.plot([800,2000], [800,2000], label="1")
        plt.plot([800,2000], [700,1750], label="0.875")
        plt.plot([800,2000], [600,1500], label="0.75")
        plt.plot([800,2000], [500,1250], label="0.625")
        plt.plot([800,2000], [400,1000], label="0.5")
        plt.title("Metric of\n" + titleNames)
        plt.xlabel("WR Mass (GeV)")
        plt.ylabel("N Mass (GeV)")
        plt.colorbar()
        plt.legend()
        plt.scatter(xVals, yVals, marker="x", color="r")
        plt.tight_layout()
        plt.savefig("metric/Metric_of_" + names+ "_base_" + str(base)+".png")
        plt.show()
        
        plt.figure(figsize=(9,13.5))
        plt.imshow(metric2, cmap=cmap, origin="lower", extent=(775,2025, 175, 2025))
        plt.plot([800,2000], [800,2000], label="1")
        plt.plot([800,2000], [700,1750], label="0.875")
        plt.plot([800,2000], [600,1500], label="0.75")
        plt.plot([800,2000], [500,1250], label="0.625")
        plt.plot([800,2000], [400,1000], label="0.5")
        plt.title("No power Metric of\n" + titleNames )
        plt.xlabel("WR Mass (GeV)")
        plt.ylabel("N Mass (GeV)")
        plt.colorbar()
        plt.legend()
        plt.scatter(xVals, yVals, marker="x", color="r")
        plt.tight_layout()
        plt.savefig("metric/No_power_Metric_of_" + names+ ".png")
        plt.show()
        
        
if(__name__ == "__main__"):
    main()