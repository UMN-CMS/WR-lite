"""
Trains a weighted Resolved neural network and a weighted Super Resolved
neural network.

The Resolved network uses data with N/WR < 0.75 for training and the
Super Resolved uses data with N/WR >= 0.75 for training.

Training weights are determined by the absolute difference in reconstructed
N mass divided by the standard deviation of the correct N masses for the 
current mass point.

The network is set up to train with 2 hidden layers of 20 perceptrons each
using leaky ReLU with an alpha of 0.2 as the activation function between layers
and sigmoid as the output activation function. It trains through 3 cycles with
learning rates of 1e-2, 1e-3, and 1e-4 for 5 epcohs each. The amsgrad
optimizer is used and binary cross entropy is the loss function. To change any
of these, see lines 38-42 and 233-235.
"""
import tensorflow as tf
import numpy as np
import random as rn
import os
from sklearn.model_selection import train_test_split


def main():
    #Set seeds for reproducibility
    os.environ["PYTHONHASHSEED"] = "0"
    np.random.seed(42)
    rn.seed(12345)
    tf.random.set_seed(3)
    
    #Load data
    data = np.load("mlDataV2.npy")
    print(data.shape)
    
    #Trainin parameters placed up here for convenience
    width = 20 #Perceptron  per layer
    hidden = 2 #Number of hidden layers
    alpha=0.2 #Slope value for leaky ReLU
    cycles=3 #Number of training cylces
    epochs=5 #Number of epcoch per training cycle
    
    
    
    #Seperate out the training data into differen WR, N mass combinations
    #Sometimes the ordering is a little mixed up, making this more complicated
    #Also, calculate the standard deviations for the correct N mass values
    print(data.shape)
    weights=[]
    dataSets=[]
    previous=[]
    current=[]
    previousSum=0
    previousSumSquared=0
    previousCount=0
    currentSum=0
    currentSumSquared=0
    currentCount=0
    previousN=0.0
    previousWR=0.0
    currentN=0.0
    currentWR=0.0
    
    for x in range(data.shape[0]):
        if(abs(data[x,17]-currentN)==0):
            current.append(data[x])
            if(data[x,-3]==1):
                currentCount+=1
                currentSum+=data[x,13]
                currentSumSquared+=data[x,13]**2
        elif(abs(data[x,17]-previousN)==0):
            previous.append(data[x])
            if(data[x,-3]==1):
                previousCount+=1
                previousSumSquared+=data[x,13]**2
        else:
            if(previousN!=0.0):
                print("Appending:", previousWR, ",", previousN)
                weights.append([((previousSumSquared/previousCount-(previousSum/previousCount)**2))**0.5]*previousCount*2)
                dataSets.append(np.array(previous))
            previousN = currentN
            previousCount=currentCount
            previousSum=currentSum
            previousSumSquared=currentSumSquared
            currentCount=0
            currentSum=0
            currentSumSquared=0
            currentN = data[x,17]
            currentWR, previousWR = data[x,16], currentWR
            previous = current
            current=[]
            current.append(data[x])
            if(data[x,-3]==1):
                currentCount+=1
                currentSum+=data[x,13]
                currentSumSquared+=data[x,13]**2
    print("Appending:", previousWR, ",", previousN)
    dataSets.append(np.array(previous))
    weights.append([((previousSumSquared/previousCount-(previousSum/previousCount)**2))**0.5]*previousCount*2)
    print("Appending:", currentWR, ",", currentN)
    dataSets.append(np.array(current))
    weights.append([((currentSumSquared/currentCount-(currentSum/currentCount)**2))**0.5]*currentCount*2)
    
    #Names of the different mass combinations
    setNames = ["WR800N400","WR800N600","WR800N700", "WR1000N200", 
                "WR1000N900","WR1000N400", "WR1000N600", "WR1000N800", "WR800N200",  
                "WR1200N400", "WR1200N1100", "WR1200N600", "WR1200N800", "WR1200N1000",
                "WR1400N400", "WR1400N1300", "WR1400N600", "WR1400N800", "WR1400N1000",
                "WR1400N1200",
                "WR1600N400", "WR1600N1500", "WR1600N600", "WR1600N800", 
                "WR1600N1000", "WR1600N1200", "WR1600N1400"
                "WR1800N400", "WR1800N1700", "WR1800N600", "WR1800N800", "WR1800N1000", 
                "WR1800N1200","WR1800N1400", "WR1800N1600",
                "WR2000N600", "WR2000N1900", "WR2000N800", "WR2000N1000", "WR2000N1200", "WR2000N1400",
                "WR2000N1600", "WR2000N1800"]

    #Masses of the different mass combinations
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
    
    dataSets=[] #Will hold two arrays, one for each training set
    temp1=[] #Will become the resolved training set
    temp2=[] #Will become the super resolved training set
    weight1=[]
    weight2=[]
    for x in range(len(massSplits)):
        if(massSplits[x][1]/massSplits[x][0]<0.75):
            temp1.append(dataSets[x])
            weight1.append(weights[x])
        else:
            temp2.append(dataSets[x])
            weight2.append(weights[x])
    weights=[np.concatenate(weight1), np.concatenate(weight2)]
    dataSets.append(np.concatenate(temp1))
    dataSets.append(np.concatenate(temp2))

    
    setNames=["resolved", "superResolved"]
    
    for setNumber in [0,1]: #Train both resolved and super resolved
        dataNormed = np.copy(dataSets[setNumber].T)
        weight = weights[setNumber].T
        for x in range(len(weight)):
            weight[x]=abs(dataNormed[6,x]-dataNormed[13,x])/weight[x]
            if(x<20):
                print(weight[x])
        
        
        
        dataNormed[4] = dataNormed[4]/dataNormed[14] #pt to scaled pt
        dataNormed[11] = dataNormed[11]/dataNormed[14] #pt to scaled pt
        #Only interested in eta, etaWR, dR, pt scaled for each lepton plus
        #the weight and output value
        dataNormed = np.concatenate(
                                [np.reshape(dataNormed[0,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[1,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[3,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[4,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[7,:],(1, len(dataNormed[-3,:]))),                                 
                                 np.reshape(dataNormed[8,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[10,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[11,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(dataNormed[-3,:],(1, len(dataNormed[-3,:]))),
                                 np.reshape(weight, (1, len(weight)))])
        dims=8
        normInfo = np.zeros((dims,2))
        #Normalize the input features to they have 0 mean and unit variance
        for x in range(dims):
            normInfo[x,0] = np.mean(dataNormed[x])
            normInfo[x,1] = np.std(dataNormed[x])
            
            dataNormed[x] = (dataNormed[x] - np.mean(dataNormed[x]))
            dataNormed[x] = dataNormed[x]/(np.std(dataNormed[x]))
            
        #copy data so we can seperate out the inputs and outputs
        newData=[]
        for x in range(dims):
            newData.append(dataNormed[x])
        
            
        inputData=dataNormed[:dims].T
        outputData=dataNormed[dims].T
        
        #Randomly pick an 80-20 train-validation split
        trainIn, valIn, trainOut, valOut = train_test_split(inputData,
                                                            outputData,
                                                            test_size=0.2,
                                                            random_state=42)
        
        tf.random.set_seed(1000) #Set seed
        
        inputDims=dims
        outputDims=1
        
        #Start building the model.
        model = tf.keras.Sequential()
        
        
        model.add(
            tf.keras.layers.Dense(
                width,
                kernel_initializer="glorot_uniform",
                input_shape=(
                    inputDims,
                )))
        model.add(tf.keras.layers.LeakyReLU(alpha=alpha))
        
        for n in range(hidden - 1):
            model.add(
                tf.keras.layers.Dense(
                    width,
                    kernel_initializer="glorot_uniform"))
            model.add(tf.keras.layers.LeakyReLU(alpha=alpha))
        
        model.add(
            tf.keras.layers.Dense(
                outputDims,
                kernel_initializer="glorot_uniform",
                activation="sigmoid"))
        
        #Train for the desired number of cycles
        for x in range(cycles):
            model.compile(optimizer=tf.keras.optimizers.Adam(0.001 * (10**(-x)),
                          amsgrad=True),
                          loss=tf.keras.losses.BinaryCrossentropy())        
        
            model.fit(
                trainIn,
                trainOut,
                validation_data=(
                    valIn,
                    valOut),
                epochs=epochs,
                batch_size=32)
        
        #Extract weights and biases
        weights = []
        biases = []
        for layer in model.layers:
            weightBias = layer.get_weights()
            if(len(weightBias) == 2):
                weights.append(weightBias[0].T)
                bias = weightBias[1]
                bias = np.reshape(bias, (len(bias), 1))
                biases.append(bias)
        
        #Save weights and biases to a text file
        for x in range(len(weights)):
            np.savetxt(setNames[setNumber]+"/weights_"+str(x)+".txt",
                       weights[x], delimiter=",")
            
        for x in range(len(biases)):
            np.savetxt(setNames[setNumber]+"/biases_"+str(x)+".txt",
                       biases[x], delimiter=",")
            
        #Save normalization information to a text file
        np.savetxt(setNames[setNumber]+"/normInfo.txt",
                   normInfo, delimiter=",")
