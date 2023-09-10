#CPPFLAGS=  -Wall -g -O -fPIC
CPPFLAGS= -fPIC -g 
EXTRA_INCLUDE := $(shell echo $(ROOT_INCLUDE_PATH) | cut -d ':' -f 79)
UNAME := $(shell uname -m)

all: bin
#all: lib

bin: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.o src/JetResolutionObject.o src/JetResolution.o src/Selector.o src/EventTree.o src/EventPick.o src/RoccoR.o SkimAna SkimAnaData
lib: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.o src/JetResolutionObject.o src/JetResolution.o src/Selector.o src/EventTree.o src/EventPick.o src/RoccoR.o libweight.so

######################## Main library ###############################################
SkimAna: src/PUReweight.o src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp src/RoccoR.o src/KinFit.cpp interface/muSF_reader.h interface/eleSF_reader.h SkimAna.C SkimAna.h
ifeq ($(HOSTNAME), dhep-inlap)
	g++ $(CPPFLAGS) -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -I${CMSSW_RELEASE_BASE}/src -I$(EXTRA_INCLUDE) -L${CMSSW_RELEASE_BASE}/lib/${SCRAM_ARCH} -std=c++17 -D STANDALONE -D MCONLY src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.o src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/RoccoR.o src/JetResolution.cc src/JetResolutionObject.cc SkimAna.C -lPhysicsToolsKinFitter -lEG -lProof
else
	g++ $(CPPFLAGS) -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -I${CMSSW_RELEASE_BASE}/src -L${CMSSW_RELEASE_BASE}/lib/${SCRAM_ARCH} -std=c++17 -D STANDALONE -D MCONLY src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.o src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/RoccoR.o src/JetResolution.cc src/JetResolutionObject.cc SkimAna.C -lPhysicsToolsKinFitter -lEG -lProof
endif

SkimAnaData: src/PUReweight.o src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp src/RoccoR.o src/KinFit.cpp interface/muSF_reader.h interface/eleSF_reader.h SkimAna.C SkimAna.h
ifeq ($(HOSTNAME), dhep-inlap)
	g++ $(CPPFLAGS) -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -I${CMSSW_RELEASE_BASE}/src -I$(EXTRA_INCLUDE) -L${CMSSW_RELEASE_BASE}/lib/${SCRAM_ARCH} -std=c++17 -D STANDALONE  src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.o src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/RoccoR.o src/JetResolution.cc src/JetResolutionObject.cc SkimAna.C -lPhysicsToolsKinFitter -lEG -lProof
else
	g++ $(CPPFLAGS) -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -I${CMSSW_RELEASE_BASE}/src -L${CMSSW_RELEASE_BASE}/lib/${SCRAM_ARCH} -std=c++17 -D STANDALONE  src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.o src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/RoccoR.o src/JetResolution.cc src/JetResolutionObject.cc SkimAna.C -lPhysicsToolsKinFitter -lEG -lProof
endif

libweight.so: src/PUReweight.o src/Selector.o src/EventPick.o src/EventTree.o src/EventJetAna.C interface/EventJetAna.h src/PUReweight.cpp interface/PUReweight.h src/BTagCalibrationStandalone.o interface/ScaleFactorFunction.h src/JECvariation.o src/TopEventCombinatorics.cpp src/RoccoR.o src/KinFit.cpp interface/muSF_reader.h interface/eleSF_reader.h SkimAna.C SkimAna.h
	g++ $(CPPFLAGS) -shared -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventTree.o src/EventPick.o src/Selector.o  src/PUReweight.o src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/RoccoR.o src/JetResolution.o

######################## Main library ###############################################


############################## PU weight ############################################
src/PUReweight.o: src/PUReweight.cpp interface/PUReweight.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/PUReweight.cpp -o src/PUReweight.o
############################## PU weight ############################################


####################### Jet Object files ############################################
######################### Group 1 ############################
src/JECvariation.o: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.cpp
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JECvariation.cpp -o src/JECvariation.o

src/FactorizedJetCorrector.o: src/FactorizedJetCorrector.cpp interface/FactorizedJetCorrector.h interface/JetCorrectorParameters.h interface/SimpleJetCorrector.h src/Utilities.cc
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/FactorizedJetCorrector.cpp -o src/FactorizedJetCorrector.o
#	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 src/Utilities.cc -o src/Utilities.o

src/JetCorrectorParameters.o: src/JetCorrectorParameters.cpp interface/JetCorrectorParameters.h 
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetCorrectorParameters.cpp -o src/JetCorrectorParameters.o

src/SimpleJetCorrector.o: src/JetCorrectorParameters.cpp interface/JetCorrectorParameters.h interface/SimpleJetCorrector.h
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/SimpleJetCorrector.cpp -o src/SimpleJetCorrector.o

src/JetCorrectionUncertainty.o: src/JetCorrectionUncertainty.cpp interface/JetCorrectionUncertainty.h src/SimpleJetCorrectionUncertainty.cpp interface/SimpleJetCorrectionUncertainty.h
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetCorrectionUncertainty.cpp -o src/JetCorrectionUncertainty.o 
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/SimpleJetCorrectionUncertainty.cpp -o src/SimpleJetCorrectionUncertainty.o
######################### Group 2 ############################
src/JetResolutionObject.o: src/JetResolutionObject.cc interface/JetResolutionObject.h
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetResolutionObject.cc -o src/JetResolutionObject.o

src/JetResolution.o: interface/JetResolution.h src/JetResolution.cc
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/JetResolution.cc -o src/JetResolution.o
####################### Jet Object files ############################################

############################## Btag library #########################################
src/BTagCalibrationStandalone.o: src/BTagCalibrationStandalone.cpp interface/BTagCalibrationStandalone.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/BTagCalibrationStandalone.cpp -o src/BTagCalibrationStandalone.o
############################## Btag library #########################################


######################## Event Tree, Pick and Selector ##############################
src/EventPick.o: src/Selector.o src/EventPick.cpp interface/EventPick.h
ifeq ($(HOSTNAME), dhep-inlap)
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -I$(EXTRA_INCLUDE) -std=c++17 -D STANDALONE src/EventPick.cpp -o src/EventPick.o
else
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventPick.cpp -o src/EventPick.o
endif

src/Selector.o: src/EventTree.o src/Selector.cpp interface/Selector.h
ifeq ($(HOSTNAME), dhep-inlap)
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -I$(EXTRA_INCLUDE) -std=c++17 -D STANDALONE src/Selector.cpp -o src/Selector.o
else
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/Selector.cpp -o src/Selector.o
endif
#	g++ $(CPPFLAGS) -c -I `root-config --incdir` -std=c++17 -D STANDALONE src/Utils.cc src/JetResolution.cc src/JetResolutionObject.cc  src/Selector.cpp

src/EventTree.o: src/EventTree.cpp interface/EventTree.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventTree.cpp -o src/EventTree.o

src/Selector_gen.o: src/EventTree.o src/Selector_gen.cpp interface/Selector.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/Selector_gen.cpp -o src/Selector_gen.o

src/EventPick_gen.o: src/Selector_gen.o src/EventPick_gen.cpp interface/EventPick.h
	g++ $(CPPFLAGS) -c -I`root-config --incdir` -std=c++17 -D STANDALONE src/EventPick_gen.cpp -o src/EventPick_gen.o

######################## Event Tree, Pick and Selector ##############################


######################## RCorr library ###############################################
src/RoccoR.o: src/RoccoR.cc interface/RoccoR.h
ifeq ($(HOSTNAME), dhep-inlap)
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -I$(EXTRA_INCLUDE) -std=c++17 -D STANDALONE src/RoccoR.cc -o src/RoccoR.o
else
	g++ $(CPPFLAGS) -c `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE src/RoccoR.cc -o src/RoccoR.o
endif
######################## RCorr library ###############################################


######################## Old tests ##################################################
#makeNtuple: src/Selector.o src/EventPick.o src/EventTree.o makeNtuple.C src/OverlapRemove.cpp interface/makeNtuple.h src/ReaderPileupSF.cpp interface/ReaderPileupSF.h src/BTagCalibrationStandalone.o interface/ReaderLumiSF.h src/JECvariation.o src/TopEventCombinatorics.cpp interface/ReaderMuSF.h interface/ReaderEleSF.h interface/ReaderPhoSF.h 
#	g++ -o makeNtuple `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE makeNtuple.C src/EventTree.o src/EventPick.o src/ParsePhotonID.cpp src/Selector.o src/OverlapRemove.cpp src/ReaderPileupSF.cpp src/BTagCalibrationStandalone.o src/Utils.cc src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/SimpleJetCorrectionUncertainty.o src/JECvariation.o src/JetResolution.cc src/JetResolutionObject.cc src/METzCalculator.cpp src/TopEventCombinatorics.cpp 

#all: src/FactorizedJetCorrector.o src/JetCorrectorParameters.o src/SimpleJetCorrector.o src/JetCorrectionUncertainty.o src/JECvariation.o src/JetResolutionObject.o src/JetResolution.o src/Selector.o src/EventTree.o src/EventPick.o makeNtuple #makeCutflows 
######################## Old tests ##################################################

clean:
	rm src/*.o *.so *.root SkimAna SkimAnaData

