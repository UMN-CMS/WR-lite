import FWCore.ParameterSet.Config as cms

                                    
def setupVIDForHEEPV70(process,useMiniAOD=True):
    #setup the VID with HEEP 7.0
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import switchOnVIDElectronIdProducer
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import setupVIDElectronSelection
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import setupAllVIDIdsInModule
    from PhysicsTools.SelectorUtils.tools.vid_id_tools import DataFormat
    
    # turn on VID producer, indicate data format  to be
    # DataFormat.AOD or DataFormat.MiniAOD, as appropriate
    dataFormat = DataFormat.MiniAOD if useMiniAOD else DataFormat.AOD
    switchOnVIDElectronIdProducer(process, dataFormat)

    # define which IDs we want to produce
    my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff']
    my_id_modules.append('RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff')
                   #add them to the VID producer
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)



def addHEEPV70ElesMiniAOD(process,useStdName=True): 

    setupVIDForHEEPV70(process,useMiniAOD=True)
    
    #if we are making a new slimmedElectrons collection, now we need to customise the input 
    #to the VID and HEEP producers to ignore it and take the old one
    if useStdName:
        process.heepIDVarValueMaps.elesMiniAOD = \
            cms.InputTag("slimmedElectrons",processName=cms.InputTag.skipCurrentProcess())
        process.egmGsfElectronIDs.physicsObjectSrc = \
            cms.InputTag("slimmedElectrons",processName=cms.InputTag.skipCurrentProcess())
    
    
    process.load("ExoAnalysis.WR_lite.addHEEPV70ToEles_cfi") 
    process.heepSequence = cms.Sequence(process.egmGsfElectronIDSequence)
    if useStdName:
        process.heepSequence.insert(1,process.addHEEPToSlimmedElectrons)
    else:
        process.heepSequence.insert(1,process.addHEEPToHEEPElectrons)
        