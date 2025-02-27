#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;


#pragma link C++ class AliAnalysisTaskFemto+;
#pragma link C++ class AliAnalysisTaskFemtoMJ+;
#pragma link C++ class AliAnalysisTaskFemtoNu+;
#pragma link C++ class AliAnalysisTaskFemtoNu::Builder-;

#pragma link C++ class AliFemtoAnalysis+;
#pragma link C++ class AliFemtoLikeSignAnalysis+;
#pragma link C++ class AliFemtoVertexAnalysis+;
#pragma link C++ class AliFemtoVertexMultAnalysis+;
#pragma link C++ class AliFemtoAnalysisAzimuthal+;
#pragma link C++ class AliFemtoSimpleAnalysis+;
#pragma link C++ class AliFemtoEventAnalysis+;
#pragma link C++ class AliFemtoSpatialSeparationFunction+;
#pragma link C++ class AliFemtoAngularSpatialSeparationFunction+;
#pragma link C++ class AliFemtoAnalysisReactionPlane+;
#pragma link C++ class AliFemtoEventCut+;
#pragma link C++ class AliFemtoSphericityEventCut+;
#pragma link C++ class AliFemtoSpherocityEventCut+;
#pragma link C++ class AliFemtoResultStorage+;
#pragma link C++ class AliFemtoEventReader+;
#pragma link C++ class AliFemtoEventReaderStandard+;
#pragma link C++ class AliFemtoKinkCut+;
#pragma link C++ class AliFemtoPairCut+;
#pragma link C++ class AliFemtoPairCutRejectAll;
#pragma link C++ class AliFemtoKTPairCut+;
#pragma link C++ class AliFemtoParticleCut+;
#pragma link C++ class AliFemtoTrackCut+;
#pragma link C++ class AliFemtoV0Cut+;
#pragma link C++ class AliFemtoXiCut+;
#pragma link C++ class AliFemtoBPLCMS3DCorrFctn+;
#pragma link C++ class AliFemtoBPLCMS3DCorrFctnKK+;
#pragma link C++ class AliFemtoCorrFctn3DLCMSSym+;
#pragma link C++ class AliFemtoQinvCorrFctn+;
#pragma link C++ class AliFemtoCorrFctnNonIdDR+;
#pragma link C++ class AliFemtoCorrFctn3DSpherical+;
#pragma link C++ class AliFemtoCorrFctn+;
#pragma link C++ class AliFemtoBasicEventCut+;
#pragma link C++ class AliFemtoEventCutEstimators+;
#pragma link C++ class AliFemtoBasicTrackCut+;
#pragma link C++ class AliFemtoDummyPairCut+;
#pragma link C++ class AliFemtoCoulomb+;
#pragma link C++ class AliFemtoCutMonitorHandler+;
#pragma link C++ class AliFemtoLorentzVector+;
#pragma link C++ class AliFemtoManager+;
#pragma link C++ class AliFmHelixD+;
#pragma link C++ class AliFmLorentzVectorD+;
#pragma link C++ class AliFmPhysicalHelixD+;
#pragma link C++ class AliFmThreeVectorD+;
#pragma link C++ class AliFmThreeVectorF+;
#pragma link C++ class AliFemtoEventReaderESD+;
#pragma link C++ class AliFemtoEventReaderESDChain+;
#pragma link C++ class AliFemtoEventReaderESDChainKine+;
#pragma link C++ class AliFemtoEventReaderESDChainKineKK+;
#pragma link C++ class AliFemtoModelManager+;
#pragma link C++ class AliFemtoModelWeightGenerator+;
#pragma link C++ class AliFemtoModelWeightGeneratorBasic+;
#pragma link C++ class AliFemtoModelFreezeOutGenerator+;
#pragma link C++ class AliFemtoModelGausLCMSFreezeOutGenerator+;
#pragma link C++ class AliFemtoModelHiddenInfo+;
#pragma link C++ class AliFemtoModelGlobalHiddenInfo+;
#pragma link C++ class AliFemtoModelCorrFctn+;
#pragma link C++ class AliFemtoModelWeightGeneratorLednicky+;
#pragma link C++ class AliFemtoCutMonitorParticleYPt+;
#pragma link C++ class AliFemtoCutMonitorParticleYPt_pion+;
#pragma link C++ class AliFemtoCutMonitorParticleYPt_proton+;
#pragma link C++ class AliFemtoCutMonitorParticleVertPos+;
#pragma link C++ class AliFemtoCutMonitorParticlePID+;
#pragma link C++ class AliFemtoCutMonitorParticlePIDBeta+;
#pragma link C++ class AliFemtoCutMonitorParticlePIDInnerMomentum+;
#pragma link C++ class AliFemtoCutMonitorEventMult+;
#pragma link C++ class AliFemtoCutMonitorEventVertex+;
#pragma link C++ class AliFemtoEventReaderAOD+;
#pragma link C++ class AliFemtoEventReaderAODChain+;
#pragma link C++ class AliFemtoEventReaderAODMultSelection+;
#pragma link C++ class AliFemtoEventReaderAlt;
#pragma link C++ class AliFemtoAODTrackCut+;
#pragma link C++ class AliTwoTrackRes+;
#pragma link C++ class AliFemtoMCTrackCut+;
#pragma link C++ class AliFemtoEventReaderKinematicsChain+;
#pragma link C++ class AliFemtoEventReaderKinematicsChainESD+;
#pragma link C++ class AliFemtoEventReaderAODKinematicsChain+;
#pragma link C++ class AliFemtoV0TrackCut+;
#pragma link C++ class AliFemtoV0PairCut+;
#pragma link C++ class AliFemtoCutMonitorV0+;
#pragma link C++ class AliFemtoV0TrackPairCut+;
#pragma link C++ class AliFemtoCutMonitorCollections+;
#pragma link C++ class AliFemtoV0SharedDaughterCut+;
#pragma link C++ class AliFemtoXiSharedDaughterCut+;
#pragma link C++ class AliFemtoCorrFctnDPhiStarDEta+;
#pragma link C++ class AliFemtoCorrFctnDPhiStarDEtaStar+;
#pragma link C++ class AliFemtoCorrFctnDPhiStarKStarMergedFraction+;
#pragma link C++ class AliFemtoDeltaPtPairCut+;
#pragma link C++ class AliFemtoCorrFctnDPhiStarKStarAverageMergedPointsFraction+;
#pragma link C++ class AliFemtoXiTrackCut+;
#pragma link C++ class AliFemtoXiPairCut+;
#pragma link C++ class AliFemtoXiTrackPairCut+;
#pragma link C++ class AliFemtoXiV0PairCut+;
#pragma link C++ class AliFemtoBetaTPairCut+;
#pragma link C++ class AliFemtoCutMonitorPairBetaT+;
#pragma link C++ class AliFemtoCutMonitorXi+;
#pragma link C++ class AliFemtoMultCorrAnalysis+;
#pragma link C++ class AliFemtoTrioAnalysis+;
#pragma link C++ class AliFemtoTrio+;
#pragma link C++ class AliFemtoTrioCut+;
#pragma link C++ class AliFemtoTrioFctn+;
#pragma link C++ class AliFemtoTrioMinvFctn+;
#pragma link C++ class AliFemtoTrioDEtaDPhiFctn+;
#pragma link C++ class AliFemtoEventReaderNanoAOD+;
#pragma link C++ class AliFemtoEventReaderNanoAODChain+;
#pragma link C++ class AliFemtoEventReaderAODKinematicsMultSelection+;
// Dong-Fang: 2021.9.14
#pragma link C++ class AliFemtoSimpleAnalysisOnlyMixP1+;
#pragma link C++ class AliFemtoVertexMultAnalysisOnlyMixP1+;
#pragma link C++ class AliFemtoCutMonitorParticlePIDpdtHe3+;

#pragma link C++ class AliFemtoPairkTPairCut+;

#pragma link C++ class AliFemtoConfigObject-;
#pragma link C++ class AliFemtoConfigObject::Painter;
#pragma link C++ class AliFemtoConfigObject::BuildMap;
#pragma link C++ class AliFemtoConfigObject::list_iterator;
#pragma link C++ class AliFemtoConfigObject::map_iterator;
#pragma link C++ class std::map<std::string, AliFemtoConfigObject>;
#pragma link C++ class std::vector<AliFemtoConfigObject>;
#pragma link C++ class std::vector<AliFemtoConfigObject>::iterator;
#pragma link C++ class std::vector<std::pair<double, double>>;


// ^ these std:: classes required here for use in ROOT-5 macros (ROOT-6 should be ok)

#endif
