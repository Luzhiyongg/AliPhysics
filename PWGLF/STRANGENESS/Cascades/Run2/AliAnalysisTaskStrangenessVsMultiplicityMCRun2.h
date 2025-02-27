/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Modified version of AliAnalysisTaskCheckCascade.h
// Used bits of code from AliAnalysisTaskCheckPerformanceStrange
//
// --- David Dobrigkeit Chinellato
//
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#ifndef AliAnalysisTaskStrangenessVsMultiplicityMCRun2_H
#define AliAnalysisTaskStrangenessVsMultiplicityMCRun2_H

class TList;
class TH1F;
class TH2F;
class TH3F;
class TVector3;
class THnSparse;
class TRandom3;
class TProfile;

class AliESDpid;
class AliESDtrackCuts;
class AliAnalysisUtils;
class AliESDEvent;
class AliPhysicsSelection;
class AliCFContainer;
class AliV0Result;
class AliCascadeResult;
class AliExternalTrackParam;

//#include "TString.h"
//#include "AliESDtrackCuts.h"
//#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"
#include "AliTrackReference.h"
#include "AliAnalysisTaskWeakDecayVertexer.h"

//include ML classes
#include "AliMachineLearning.h"
#include "AliNeuralNetwork.h"
#include "AliBDT.h"

class AliAnalysisTaskStrangenessVsMultiplicityMCRun2 : public AliAnalysisTaskSE {
public:
  AliAnalysisTaskStrangenessVsMultiplicityMCRun2();
  AliAnalysisTaskStrangenessVsMultiplicityMCRun2(Bool_t lSaveEventTree, Bool_t lSaveV0Tree, Bool_t lSaveCascadeTree, const char *name, TString lExtraOptions = "");
  virtual ~AliAnalysisTaskStrangenessVsMultiplicityMCRun2();
  
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   Terminate(Option_t *);
  Double_t MyRapidity(Double_t rE, Double_t rPz) const;
  
  //Fix on-the-fly v0s
  void CheckChargeV0(AliESDv0 *v0);
  
  void SetSaveV0s                (Bool_t lSaveV0s        = kTRUE ) {
    fkSaveV0Tree        = lSaveV0s;
  }
  void SetSaveCascades           (Bool_t lSaveCascades   = kTRUE ) {
    fkSaveCascadeTree   = lSaveCascades;
  }
  void SetPreselectDedx (Bool_t lPreselectDedx= kTRUE ) {
    fkPreselectDedx   = lPreselectDedx;
  }
  void SetPreselectPID (Bool_t lPreselectPID = kTRUE ) {
    fkPreselectPID   = lPreselectPID;
  }
  void SetAlwaysKeepTrue (Bool_t lAlwaysKeepTrue = kTRUE ) {
    fkAlwaysKeepTrue   = lAlwaysKeepTrue;
  }
  void SetSaveEverything           (Bool_t lSaveEverything   = kTRUE ) {
    fkSaveEverything = lSaveEverything; //danger ... use cautiously
  }
  void SetUseOnTheFlyV0Cascading( Bool_t lUseOnTheFlyV0Cascading = kTRUE ){
    //Highly experimental, use with care!
    fkUseOnTheFlyV0Cascading = lUseOnTheFlyV0Cascading;
  }
  void SetDoImprovedCascadeVertexFinding( Bool_t lOpt = kTRUE ){
    //Highly experimental, use with care!
    fkDoImprovedCascadeVertexFinding = lOpt;
  }
  void SetIfImprovedPerformInitialLinearPropag( Bool_t lOpt = kTRUE ){
    //Highly experimental, use with care!
    fkIfImprovedPerformInitialLinearPropag = lOpt;
  }
  void SetIfImprovedExtraPrecisionFactor( Double_t lOpt ){
    //Highly experimental, use with care!
    fkIfImprovedExtraPrecisionFactor = lOpt;
  }
  void SetDoStrangenessTracking ( Bool_t lOpt = kTRUE) {
    fkDoStrangenessTracking = lOpt;
  }
  void SetAddPVToRecPointFinder ( Bool_t lOpt = kTRUE) {
    fkAddPVToRecPointFinder = lOpt;
  }
  void SetUseLayer1 ( Bool_t lOpt = kTRUE) {
    fkUseLayer1 = lOpt;
  }
  void SetUseLayer2 ( Bool_t lOpt = kTRUE) {
    fkUseLayer2 = lOpt;
  }
  void SetDistanceLayer1 ( Float_t lOpt ) {
    fkDistanceLayer1 = lOpt;
  }
  void SetDistanceLayer2 ( Float_t lOpt ) {
    fkDistanceLayer2 = lOpt;
  }
  
  
  //---------------------------------------------------------------------------------------
  //Task Configuration: trigger selection
  void SetSelectedTriggerClass(AliVEvent::EOfflineTriggerTypes trigType) { fTrigType = trigType;}
  //---------------------------------------------------------------------------------------
  //Task Configuration: Meant to enable quick re-execution of vertexer if needed
  void SetRunVertexers ( Bool_t lRunVertexers = kTRUE) {
    fkRunVertexers = lRunVertexers;
  }
  void SetUseLightVertexers ( Bool_t lUseLightVertexers = kTRUE) {
    fkUseLightVertexer = lUseLightVertexers;
  }
  void SetDoV0Refit ( Bool_t lDoV0Refit = kTRUE) {
    fkDoV0Refit = lDoV0Refit;
  }
  void SetExtraCleanup ( Bool_t lExtraCleanup = kTRUE) {
    fkExtraCleanup = lExtraCleanup;
  }
  void SetExtraCleanupRapidity ( Bool_t lExtraCleanupRapidity = kTRUE) {
    fkExtraCleanupRapidity = lExtraCleanupRapidity;
  }
  void SetSaveVertex ( Bool_t lVal = kTRUE) {
    fkSaveVertex = lVal;
  }
  void SetHypertritonMode ( Bool_t lOpt = kTRUE) {
    fkHypertritonMode = lOpt;
  }
  void SetHeavyDaughterPID ( Bool_t lOpt = kTRUE) {
    fkHeavyDaughterPID = lOpt;
  }
  void SetSandboxV0Prongs ( Bool_t lOpt = kTRUE) {
    fkSandboxV0Prongs = lOpt;
  }
  void SetSaveMCInfoAtTPC ( Bool_t lVal = kTRUE) {
    fkSaveMCInfoTPC = lVal;
  }
  //---------------------------------------------------------------------------------------
  void SetUseExtraEvSels ( Bool_t lUseExtraEvSels = kTRUE) {
    fkDoExtraEvSels = lUseExtraEvSels;
  }
  void SetPileupRejectionMode ( Int_t lMode = 1 ){
    //mode switch
    // 0 -> no rejection
    // 1 -> Ionut
    // 2 -> Anti-Ionut
    fkPileupRejectionMode = lMode;
  }
  void SetUseOldCentrality ( Bool_t lUseOldCent = kTRUE) {
    fkUseOldCentrality = lUseOldCent;
  }
  void SetMaxPVR2D ( Float_t lOpt = 1e+5) {
    fkMaxPVR2D = lOpt;
  }
  //---------------------------------------------------------------------------------------
  //Task Configuration: Skip Event Selections after trigger (VZERO test)
  void SetDownScaleEvent ( Bool_t lOpt = kTRUE, Float_t lVal = 0.001) {
    fkDownScaleEvent = lOpt;
    fDownScaleFactorEvent = lVal;
  }
  void SetDownScaleV0 ( Bool_t lOpt = kTRUE, Float_t lVal = 0.001) {
    fkDownScaleV0 = lOpt;
    fDownScaleFactorV0 = lVal;
  }
  void SetDownScaleCascade ( Bool_t lOpt = kTRUE, Float_t lVal = 0.001 ) {
    fkDownScaleCascade = lOpt;
    fDownScaleFactorCascade = lVal;
  }
  //---------------------------------------------------------------------------------------
  //Setters for the V0 Vertexer Parameters
  void SetV0VertexerMaxChisquare   ( Double_t lParameter ) {
    fV0VertexerSels[0] = lParameter;
  }
  void SetV0VertexerDCAFirstToPV   ( Double_t lParameter ) {
    fV0VertexerSels[1] = lParameter;
  }
  void SetV0VertexerDCASecondtoPV  ( Double_t lParameter ) {
    fV0VertexerSels[2] = lParameter;
  }
  void SetV0VertexerDCAV0Daughters ( Double_t lParameter ) {
    fV0VertexerSels[3] = lParameter;
  }
  void SetV0VertexerCosinePA       ( Double_t lParameter ) {
    fV0VertexerSels[4] = lParameter;
  }
  void SetV0VertexerMinRadius      ( Double_t lParameter ) {
    fV0VertexerSels[5] = lParameter;
  }
  void SetV0VertexerMaxRadius      ( Double_t lParameter ) {
    fV0VertexerSels[6] = lParameter;
  }
  //---------------------------------------------------------------------------------------
  //Setters for the Cascade Vertexer Parameters
  void SetCascVertexerMaxChisquare         ( Double_t lParameter ) {
    fCascadeVertexerSels[0] = lParameter;
  }
  void SetCascVertexerMinV0ImpactParameter ( Double_t lParameter ) {
    fCascadeVertexerSels[1] = lParameter;
  }
  void SetCascVertexerV0MassWindow         ( Double_t lParameter ) {
    fCascadeVertexerSels[2] = lParameter;
  }
  void SetCascVertexerDCABachToPV          ( Double_t lParameter ) {
    fCascadeVertexerSels[3] = lParameter;
  }
  void SetCascVertexerDCACascadeDaughters  ( Double_t lParameter ) {
    fCascadeVertexerSels[4] = lParameter;
  }
  void SetCascVertexerCascadeCosinePA      ( Double_t lParameter ) {
    fCascadeVertexerSels[5] = lParameter;
  }
  void SetCascVertexerCascadeMinRadius     ( Double_t lParameter ) {
    fCascadeVertexerSels[6] = lParameter;
  }
  void SetCascVertexerCascadeMaxRadius     ( Double_t lParameter ) {
    fCascadeVertexerSels[7] = lParameter;
  }
  //---------------------------------------------------------------------------------------
  void SetMinPt     ( Float_t lMinPt ) {
    fMinPtToSave = lMinPt;
  }
  void SetMaxPt     ( Float_t lMaxPt ) {
    fMaxPtToSave = lMaxPt;
  }
  void SetLambdaWindowParameters     ( Double_t *fMeanPars, Double_t *fSigmaPars ) {
    for(Int_t ipar=0; ipar<5; ipar++) fLambdaMassMean[ipar]  = fMeanPars[ipar];
    for(Int_t ipar=0; ipar<4; ipar++) fLambdaMassSigma[ipar] = fSigmaPars[ipar];
  }
  void SetLambdaWindowParametersStandard (){
    fLambdaMassMean[0] =  1.15768e+00;
    fLambdaMassMean[1] = -4.15945e-02;
    fLambdaMassMean[2] = -7.14294e-04;
    fLambdaMassMean[3] = -1.62793e-02;
    fLambdaMassMean[4] = -7.84067e+00;
    fLambdaMassSigma[0] = 1.30345e-03;
    fLambdaMassSigma[1] = 2.89679e-04;
    fLambdaMassSigma[2] = 1.52661e-03;
    fLambdaMassSigma[3] =-2.58251e+00;
  }
  
  
  void SetSibCutDcaV0ToPrimVertex( Float_t lSibCutDcaV0ToPrimVertex ){
    fSibCutDcaV0ToPrimVertex = lSibCutDcaV0ToPrimVertex;
  }
  void SetSibCutDcaV0Daughters( Float_t lSibCutDcaV0Daughters ){
    fSibCutDcaV0Daughters = lSibCutDcaV0Daughters;
  }
  void SetSibCutV0CosineOfPointingAngle( Float_t lSibCutV0CosineOfPointingAngle ){
    fSibCutV0CosineOfPointingAngle = lSibCutV0CosineOfPointingAngle;
  }
  void SetSibCutV0Radius( Float_t lSibCutV0Radius ){
    fSibCutV0Radius = lSibCutV0Radius;
  }
  void SetSibCutDcaPosToPrimVertex( Float_t lSibCutDcaPosToPrimVertex ){
    fSibCutDcaPosToPrimVertex = lSibCutDcaPosToPrimVertex;
  }
  void SetSibCutDcaNegToPrimVertex( Float_t lSibCutDcaNegToPrimVertex ){
    fSibCutDcaNegToPrimVertex = lSibCutDcaNegToPrimVertex;
  }
  void SetSibCutInvMassK0s( Float_t lSibCutInvMassK0s ){
    fSibCutInvMassK0s = lSibCutInvMassK0s;
  }
  
  //---------------------------------------------------------------------------------------
  //Superlight mode: add another configuration, please
  void AddConfiguration( AliV0Result      *lV0Result      );
  void AddConfiguration( AliCascadeResult *lCascadeResult );
  //---------------------------------------------------------------------------------------
  //Functions for analysis Bookkeepinp
  // 1- Configure standard vertexing
  void SetupStandardVertexing();
  void SetupLooseVertexing();
  // 2- Standard Topological Selection QA Sweeps
  void AddTopologicalQAV0(Int_t lRecNumberOfSteps = 100);
  void AddTopologicalQACascade(Int_t lRecNumberOfSteps = 100 , TString lSweepOptions = "");
  // 3 - Standard analysis configurations + systematics
  void AddStandardV0Configuration(Bool_t lUseFull = kFALSE, Bool_t lDoSweepLooseTight = kFALSE, Int_t lSweepFullNumb = 0);
  void AddStandardV0RadiusSweep();
  void AddStandardCascadeConfiguration(Bool_t lUseFull=kFALSE, Bool_t lDoSystematics = kTRUE);
  void AddCascadeConfiguration276TeV();
  void AddCascadeConfigurationPreliminaryCrosscheck();
  //---------------------------------------------------------------------------------------
  Float_t GetDCAz(AliESDtrack *lTrack);
  Float_t GetCosPA(AliESDtrack *lPosTrack, AliESDtrack *lNegTrack, AliESDEvent *lEvent);
  //---------------------------------------------------------------------------------------
  
  Double_t PropagateToDCA(AliESDv0 *v, AliExternalTrackParam *t, Double_t b);
  //Helper functions
  Double_t Det(Double_t a00, Double_t a01, Double_t a10, Double_t a11) const;
  Double_t Det(Double_t a00,Double_t a01,Double_t a02,
               Double_t a10,Double_t a11,Double_t a12,
               Double_t a20,Double_t a21,Double_t a22) const;
  void Evaluate(const Double_t *h, Double_t t,
                Double_t r[3],  //radius vector
                Double_t g[3],  //first defivatives
                Double_t gg[3]); //second derivatives
  Double_t GetErrorInPosition(AliExternalTrackParam *t1) const;
  //---------------------------------------------------------------------------------------
  void SetSaveSpecificCascadeConfig(TString lConfig){
    fkConfigToSave = lConfig;
    fkSaveSpecificConfig = kTRUE;
  }
  //---------------------------------------------------------------------------------------
  //Function to load ML models 
  void Create_ML_Model(TString FileName, TString ModelType, TString Particle);
  //---------------------------------------------------------------------------------------
 
private:
  // Note : In ROOT, "//!" means "do not stream the data from Master node to Worker node" ...
  // your data member object is created on the worker nodes and streaming is not needed.
  // http://root.cern.ch/download/doc/11InputOutput.pdf, page 14
  TList  *fListHist;      //! List of event histograms
  TList  *fListK0Short;        // List of V0 histograms
  TList  *fListLambda;        // List of V0 histograms
  TList  *fListAntiLambda;        // List of V0 histograms
  TList  *fListXiMinus;   // List of XiMinus outputs
  TList  *fListXiPlus;   // List of XiPlus outputs
  TList  *fListOmegaMinus;   // List of XiMinus outputs
  TList  *fListOmegaPlus;   // List of XiPlus outputs
  TTree  *fTreeEvent;              //! Output Tree, Events
  TTree  *fTreeV0;              //! Output Tree, V0s
  TTree  *fTreeCascade;              //! Output Tree, Cascades
  
  AliPIDResponse *fPIDResponse;     // PID response object
  AliESDtrackCuts *fESDtrackCuts;   // ESD track cuts used for primary track definition
  AliESDtrackCuts *fESDtrackCutsITSsa2010;  // ESD track cuts used for ITSsa track definition
  AliESDtrackCuts *fESDtrackCutsGlobal2015; // ESD track cuts used for global track definition
  AliAnalysisUtils *fUtils;         // analysis utils (for MV pileup selection)
  
  AliEventCuts fEventCuts;                 /// Event cuts class
  AliEventCuts fEventCutsStrictAntipileup; /// Event cuts class
  
  TRandom3 *fRand;
  TString fkCentralityEstimator;
  
  //Objects Controlling Task Behaviour
  Bool_t fkSaveEventTree;           //if true, save Event TTree
  Bool_t fkDownScaleEvent;
  Double_t fDownScaleFactorEvent;
  Bool_t fkSaveV0Tree;              //if true, save TTree
  Bool_t fkDownScaleV0;
  Double_t fDownScaleFactorV0;
  Bool_t fkSaveEverything;
  Bool_t fkPreselectDedx;
  Bool_t fkPreselectPID;
  Bool_t fkAlwaysKeepTrue;
  Bool_t fkUseOnTheFlyV0Cascading;
  Bool_t fkDoImprovedCascadeVertexFinding;
  Bool_t fkIfImprovedPerformInitialLinearPropag;
  Double_t fkIfImprovedExtraPrecisionFactor;
  Bool_t fkDebugWrongPIDForTracking; //if true, add extra information to TTrees for debugging
  Bool_t fkDebugBump; //if true, add extra information to TTrees for debugging
  Bool_t fkDebugParenthood; //if true, add extra info to TTrees (full parenthood) for debugging
  Bool_t fkDebugOOBPileup; // if true, add extra information to TTrees for pileup study
  Bool_t fkDoExtraEvSels; //use AliEventCuts for event selection
  Int_t fkPileupRejectionMode; //pileup rejection mode (0=none, 1=ionut, 2=anti-ionut)
  Bool_t fkUseOldCentrality; //if true, use AliCentrality instead of AliMultSelection
  Float_t fkMaxPVR2D;
  
  Bool_t fkSaveCascadeTree;         //if true, save TTree
  Bool_t fkDownScaleCascade;
  Double_t fDownScaleFactorCascade;
  
  Float_t fMinPtToSave; //minimum pt above which we keep candidates in TTree output
  Float_t fMaxPtToSave; //maximum pt below which we keep candidates in TTree output
  
  //if true, save sandbox mode info (beware large files!)
  Bool_t fkSandboxMode;
  
  //if true, fill cascade TTree with a config with a given name
  Bool_t fkSaveSpecificConfig;
  TString fkConfigToSave;
  
  //Cuts for Sibling Tagging
  Float_t fSibCutDcaV0ToPrimVertex      ;
  Float_t fSibCutDcaV0Daughters         ;
  Float_t fSibCutV0CosineOfPointingAngle;
  Float_t fSibCutV0Radius             ;
  Float_t fSibCutDcaPosToPrimVertex   ;
  Float_t fSibCutDcaNegToPrimVertex   ;
  Float_t fSibCutInvMassK0s           ;
  //Objects Controlling Task Behaviour: has to be streamed!
  Bool_t    fkRunVertexers;           // if true, re-run vertexer with loose cuts *** only for CASCADES! ***
  Bool_t    fkUseLightVertexer;       // if true, use AliLightVertexers instead of regular ones
  Bool_t    fkDoV0Refit;              // if true, will invoke AliESDv0::Refit() to improve precision
  Bool_t    fkExtraCleanup;           //if true, perform pre-rejection of useless candidates before going through configs
  Bool_t    fkExtraCleanupRapidity;    // if true, select candidates only within |y|<0.5 (logical OR in mass hypo)
  Bool_t    fkSaveVertex;              // if true, save ESD vertex
  Bool_t	fkSaveMCInfoTPC;			// if true, save MC info at the entrance of the TPC
  Bool_t    fkDoStrangenessTracking;   //if true, will attempt to attach ITS recpoints to cascade trajectory
  Bool_t fkAddPVToRecPointFinder;
  Bool_t    fkUseLayer1; //if true, use layer 1
  Bool_t    fkUseLayer2; //if true, use layer 2
  Float_t   fkDistanceLayer1;
  Float_t   fkDistanceLayer2;
  AliAnalysisTaskWeakDecayVertexer *fWDV; //helper
  
  Bool_t fkHypertritonMode; //if true, save everything in hypertriton mass window
  Bool_t fkHeavyDaughterPID; //if true, save everything that has perfect PID in heavy daughters (akin to dedx)
  Bool_t fkSandboxV0Prongs; //if true, sandbox mode will save the V0 prongs and not ESD track parametrizations
  
  AliVEvent::EOfflineTriggerTypes fTrigType; // trigger type
  
  Double_t  fV0VertexerSels[7];        // Array to store the 7 values for the different selections V0 related
  Double_t  fCascadeVertexerSels[8];   // Array to store the 8 values for the different selections Casc. related
  
  Double_t fLambdaMassMean[5]; //Array to store the lambda mass mean parametrization
  //[0]+[1]*TMath::Exp([2]*x)+[3]*TMath::Exp([4]*x)
  
  Double_t fLambdaMassSigma[4]; //Array to store the lambda mass sigma parametrization
  //[0]+[1]*x+[2]*TMath::Exp([3]*x)
  
  //===========================================================================================
  //   Pointers to ML Classes
  //===========================================================================================
  AliNeuralNetwork* fXiMinusNN;
  AliNeuralNetwork* fXiPlusNN;
  AliNeuralNetwork* fOmegaMinusNN;
  AliNeuralNetwork* fOmegaPlusNN;

  AliBDT* fXiMinusBDT;
  AliBDT* fXiPlusBDT;
  AliBDT* fOmegaMinusBDT;
  AliBDT* fOmegaPlusBDT;

  //===========================================================================================
  //   Variables for Event Tree
  //===========================================================================================
  Float_t fCentrality; //!
  Bool_t fMVPileupFlag; //!
  Bool_t fOOBPileupFlag; //!
  
  //TOF info for OOB pileuo study
  Int_t  fNTOFClusters;  //!
  Int_t  fNTOFMatches;   //!
  Int_t  fNTracksITSsa2010; //!
  Int_t  fNTracksGlobal2015; //!
  Int_t  fNTracksGlobal2015TriggerPP; //!
  
  //V0 info for OOB pileup study
  Float_t fAmplitudeV0A; //!
  Float_t fAmplitudeV0C; //!
  
  //===========================================================================================
  //   Variables for V0 Tree
  //===========================================================================================
  Float_t fTreeVariableChi2V0;         //!
  Float_t fTreeVariableDcaV0Daughters; //!
  Float_t fTreeVariableDcaV0ToPrimVertex; //!
  Float_t fTreeVariableDcaPosToPrimVertex; //!
  Float_t fTreeVariableDcaNegToPrimVertex; //!
  Float_t fTreeVariableV0CosineOfPointingAngle; //!
  Float_t fTreeVariableV0Radius; //!
  Float_t fTreeVariablePt; //!
  Float_t fTreeVariablePtMC; //!
  Float_t fTreeVariableRapK0Short; //!
  Float_t fTreeVariableRapLambda; //!
  Float_t fTreeVariableRapMC; //!
  Float_t fTreeVariableInvMassK0s; //!
  Float_t fTreeVariableInvMassLambda; //!
  Float_t fTreeVariableInvMassAntiLambda; //!
  Float_t fTreeVariableAlphaV0; //!
  Float_t fTreeVariablePtArmV0;//!
  Float_t fTreeVariableNegEta; //!
  Float_t fTreeVariablePosEta; //!
  
  Float_t fTreeVariableNSigmasPosProton; //!
  Float_t fTreeVariableNSigmasPosPion; //!
  Float_t fTreeVariableNSigmasNegProton; //!
  Float_t fTreeVariableNSigmasNegPion; //!
  
  Float_t fTreeVariableDistOverTotMom;//!
  Int_t   fTreeVariableLeastNbrCrossedRows;//!
  Float_t fTreeVariableLeastRatioCrossedRowsOverFindable;//!
  Float_t fTreeVariableMaxChi2PerCluster; //!
  Float_t fTreeVariableMinTrackLength; //!
  
  //Variables for debugging Wrong PID hypothesis in tracking bug
  // more info at: https://alice.its.cern.ch/jira/browse/PWGPP-218
  Int_t fTreeVariablePosPIDForTracking; //! uses AliPID EParticleType code (0=electron, 1=muon, 2=pion, etc)
  Int_t fTreeVariableNegPIDForTracking; //!
  Float_t fTreeVariablePosdEdx; //!
  Float_t fTreeVariableNegdEdx; //!
  Float_t fTreeVariablePosInnerP; //!
  Float_t fTreeVariableNegInnerP; //!
  //Decay Length issue debugging: ULong_t with track status
  ULong64_t fTreeVariableNegTrackStatus; //!
  ULong64_t fTreeVariablePosTrackStatus; //!
  Float_t fTreeVariableNegDCAz; //!
  Float_t fTreeVariablePosDCAz; //!
  
  //Cluster information for all daughter tracks
  Bool_t fTreeVariablePosITSClusters0;
  Bool_t fTreeVariablePosITSClusters1;
  Bool_t fTreeVariablePosITSClusters2;
  Bool_t fTreeVariablePosITSClusters3;
  Bool_t fTreeVariablePosITSClusters4;
  Bool_t fTreeVariablePosITSClusters5;
  
  Bool_t fTreeVariableNegITSClusters0;
  Bool_t fTreeVariableNegITSClusters1;
  Bool_t fTreeVariableNegITSClusters2;
  Bool_t fTreeVariableNegITSClusters3;
  Bool_t fTreeVariableNegITSClusters4;
  Bool_t fTreeVariableNegITSClusters5;
  
  //Cluster information for all daughter tracks
  Bool_t fTreeVariablePosITSSharedClusters0;
  Bool_t fTreeVariablePosITSSharedClusters1;
  Bool_t fTreeVariablePosITSSharedClusters2;
  Bool_t fTreeVariablePosITSSharedClusters3;
  Bool_t fTreeVariablePosITSSharedClusters4;
  Bool_t fTreeVariablePosITSSharedClusters5;
  
  Bool_t fTreeVariableNegITSSharedClusters0;
  Bool_t fTreeVariableNegITSSharedClusters1;
  Bool_t fTreeVariableNegITSSharedClusters2;
  Bool_t fTreeVariableNegITSSharedClusters3;
  Bool_t fTreeVariableNegITSSharedClusters4;
  Bool_t fTreeVariableNegITSSharedClusters5;
  
  Int_t fTreeVariablePosTPCNClusters;
  Int_t fTreeVariableNegTPCNClusters;
  Int_t fTreeVariablePosTPCNClustersShared;
  Int_t fTreeVariableNegTPCNClustersShared;
  
  Bool_t fTreeVariableIsCowboy; //store if V0 is cowboy-like or sailor-like in XY plane
  Int_t fTreeVariableRunNumber; //store run number for random stuff
  
  //Variables for OOB pileup study (high-multiplicity triggers pp 13 TeV - 2016 data)
  Float_t fTreeVariableNegTOFExpTDiff;      //!
  Float_t fTreeVariablePosTOFExpTDiff;      //!
  Float_t fTreeVariableNegTOFSignal;      //!
  Float_t fTreeVariablePosTOFSignal;      //!
  Int_t   fTreeVariableNegTOFBCid; //!
  Int_t   fTreeVariablePosTOFBCid; //!
  //Event info
  Float_t fTreeVariableAmplitudeV0A; //!
  Float_t fTreeVariableAmplitudeV0C; //!
  
  //Event Multiplicity Variables
  Float_t fTreeVariableCentrality; //!
  Bool_t fTreeVariableMVPileupFlag; //!
  Bool_t fTreeVariableOOBPileupFlag; //!
  
  //MC exclusive Characteristics: 7, also required for feeddown tests
  Float_t fTreeVariablePtMother; //!
  Float_t fTreeVariableRapMother; //!
  Int_t fTreeVariablePID; //!
  Int_t fTreeVariablePIDPositive; //!
  Int_t fTreeVariablePIDNegative; //!
  Int_t fTreeVariablePIDMother; //!
  Int_t fTreeVariablePrimaryStatus; //!
  Int_t fTreeVariablePrimaryStatusMother; //!
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  //Sandbox V0
  Float_t fTreeVariablePrimVertexX;
  Float_t fTreeVariablePrimVertexY;
  Float_t fTreeVariablePrimVertexZ;
  
  AliExternalTrackParam *fTreeVariablePosTrack;
  AliExternalTrackParam *fTreeVariableNegTrack;
  AliESDVertex *fTreeVariableAliESDvertex;
  
  Float_t fTreeVariableMagneticField;
  
  Float_t fTreeVariableNegCreationX;
  Float_t fTreeVariableNegCreationY;
  Float_t fTreeVariableNegCreationZ;
  Float_t fTreeVariablePosCreationX;
  Float_t fTreeVariablePosCreationY;
  Float_t fTreeVariablePosCreationZ;
  
  Float_t fTreeVariableNegPx; //!
  Float_t fTreeVariableNegPy; //!
  Float_t fTreeVariableNegPz; //!
  Float_t fTreeVariablePosPx; //!
  Float_t fTreeVariablePosPy; //!
  Float_t fTreeVariablePosPz; //!
  
  Float_t fTreeVariableNegPxMC; //!
  Float_t fTreeVariableNegPyMC; //!
  Float_t fTreeVariableNegPzMC; //!
  Float_t fTreeVariablePosPxMC; //!
  Float_t fTreeVariablePosPyMC; //!
  Float_t fTreeVariablePosPzMC; //!
  
  Int_t   fTreeVariablePIDNegativeMother;         //!
  Int_t   fTreeVariablePIDPositiveMother;         //!
  Int_t   fTreeVariablePIDNegativeGrandMother;         //!
  Int_t   fTreeVariablePIDPositiveGrandMother;         //!
  
  Int_t fTreeVariableNegLabel; //!
  Int_t fTreeVariablePosLabel; //!
  Int_t fTreeVariableNegLabelMother; //!
  Int_t fTreeVariablePosLabelMother; //!
  Int_t fTreeVariableNegLabelGrandMother; //!
  Int_t fTreeVariablePosLabelGrandMother; //!
  
  Bool_t fTreeVariableIsPhysicalPrimaryNegative;
  Bool_t fTreeVariableIsPhysicalPrimaryPositive;
  Bool_t fTreeVariableIsPhysicalPrimaryNegativeMother;
  Bool_t fTreeVariableIsPhysicalPrimaryPositiveMother;
  Bool_t fTreeVariableIsPhysicalPrimaryNegativeGrandMother;
  Bool_t fTreeVariableIsPhysicalPrimaryPositiveGrandMother;
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  
  AliTrackReference* fTreeVariablePosTrackRef;
  AliTrackReference* fTreeVariableNegTrackRef;
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  
  //===========================================================================================
  //   Variables for Cascade Candidate Tree
  //===========================================================================================
  Int_t fTreeCascVarRunNumber;      //!
  Int_t fTreeCascVarCharge;         //!
  Float_t fTreeCascVarMassAsXi;     //!
  Float_t fTreeCascVarMassAsOmega;  //!
  Float_t fTreeCascVarPt;           //!
  Float_t fTreeCascVarPtMC;         //!
  Float_t fTreeCascVarRapXi;        //!
  Float_t fTreeCascVarRapOmega;     //!
  Float_t fTreeCascVarRapMC;        //!
  Float_t fTreeCascVarNegEta;       //!
  Float_t fTreeCascVarPosEta;       //!
  Float_t fTreeCascVarBachEta;      //!
  Float_t fTreeCascVarDCACascDaughters; //!
  Float_t fTreeCascVarDCABachToPrimVtx; //!
  Float_t fTreeCascVarDCAV0Daughters;   //!
  Float_t fTreeCascVarDCAV0ToPrimVtx;   //!
  Float_t fTreeCascVarDCAPosToPrimVtx;  //!
  Float_t fTreeCascVarDCANegToPrimVtx;  //!
  Float_t fTreeCascVarCascCosPointingAngle;         //!
  Float_t fTreeCascVarCascDCAtoPVxy;         //!
  Float_t fTreeCascVarCascDCAtoPVz;         //!
  Float_t fTreeCascVarCascDCAtoPVxyTracked;         //!
  Float_t fTreeCascVarCascDCAtoPVzTracked;         //!
  Float_t fTreeCascVarCascRadius;                   //!
  Float_t fTreeCascVarLayer1_AddedHitD;
  Float_t fTreeCascVarLayer1_TrueHitD;
  Float_t fTreeCascVarLayer2_AddedHitD;
  Float_t fTreeCascVarLayer2_TrueHitD;
  Float_t fTreeCascVarV0Mass;                       //!
  Float_t fTreeCascVarV0CosPointingAngle;           //!
  Float_t fTreeCascVarV0CosPointingAngleSpecial;    //!
  Float_t fTreeCascVarV0Radius;                     //!
  Float_t fTreeCascVarDCABachToBaryon;              //!
  Float_t fTreeCascVarWrongCosPA;                   //!
  Int_t   fTreeCascVarLeastNbrClusters;             //!
  Int_t fTreeCascVarLeastNbrCrossedRows;
  Float_t fTreeCascVarNbrCrossedRowsOverLength;
  Float_t fTreeCascVarDistOverTotMom;               //!
  Float_t fTreeCascVarMaxChi2PerCluster; //!
  Float_t fTreeCascVarMinTrackLength; //!
  
  //-------------------------------------------
  //ML Prediction
  Double_t fTreeCascVarMLNNPredXiMinus; //!
  Double_t fTreeCascVarMLNNPredXiPlus; //!
  Double_t fTreeCascVarMLNNPredOmegaMinus; //!
  Double_t fTreeCascVarMLNNPredOmegaPlus; //!

  Double_t fTreeCascVarMLBDTPredXiMinus; //!
  Double_t fTreeCascVarMLBDTPredXiPlus; //!
  Double_t fTreeCascVarMLBDTPredOmegaMinus; //!
  Double_t fTreeCascVarMLBDTPredOmegaPlus; //!
  //-------------------------------------------

  //TPC dEdx
  Float_t fTreeCascVarNegNSigmaPion;   //!
  Float_t fTreeCascVarNegNSigmaProton; //!
  Float_t fTreeCascVarPosNSigmaPion;   //!
  Float_t fTreeCascVarPosNSigmaProton; //!
  Float_t fTreeCascVarBachNSigmaPion;  //!
  Float_t fTreeCascVarBachNSigmaKaon;  //!
  
  //ChiSquares
  Float_t fTreeCascVarChiSquareV0;
  Float_t fTreeCascVarChiSquareCascade;
  
  //Variables for debugging Wrong PID hypothesis in tracking bug
  // more info at: https://alice.its.cern.ch/jira/browse/PWGPP-218
  Int_t fTreeCascVarPosPIDForTracking; //! uses AliPID EParticleType code (0=electron, 1=muon, 2=pion, etc)
  Int_t fTreeCascVarNegPIDForTracking; //!
  Int_t fTreeCascVarBachPIDForTracking; //!
  Float_t fTreeCascVarNegInnerP; //!
  Float_t fTreeCascVarPosInnerP; //!
  Float_t fTreeCascVarBachInnerP; //!
  Float_t fTreeCascVarNegdEdx; //!
  Float_t fTreeCascVarPosdEdx; //!
  Float_t fTreeCascVarBachdEdx; //!
  
  //Decay Length issue debugging: ULong_t with track status
  ULong64_t fTreeCascVarNegTrackStatus; //!
  ULong64_t fTreeCascVarPosTrackStatus; //!
  ULong64_t fTreeCascVarBachTrackStatus; //!
  Float_t fTreeCascVarNegDCAz; //!
  Float_t fTreeCascVarPosDCAz; //!
  Float_t fTreeCascVarBachDCAz; //!
  
  //Variables for debugging the invariant mass bump
  //Full momentum information
  Float_t fTreeCascVarNegPx; //!
  Float_t fTreeCascVarNegPy; //!
  Float_t fTreeCascVarNegPz; //!
  Float_t fTreeCascVarPosPx; //!
  Float_t fTreeCascVarPosPy; //!
  Float_t fTreeCascVarPosPz; //!
  Float_t fTreeCascVarBachPx; //!
  Float_t fTreeCascVarBachPy; //!
  Float_t fTreeCascVarBachPz; //!
  
  Float_t fTreeCascVarNegPxMC; //!
  Float_t fTreeCascVarNegPyMC; //!
  Float_t fTreeCascVarNegPzMC; //!
  Float_t fTreeCascVarPosPxMC; //!
  Float_t fTreeCascVarPosPyMC; //!
  Float_t fTreeCascVarPosPzMC; //!
  Float_t fTreeCascVarBachPxMC; //!
  Float_t fTreeCascVarBachPyMC; //!
  Float_t fTreeCascVarBachPzMC; //!
  
  Float_t fTreeCascVarV0DecayX; //!
  Float_t fTreeCascVarV0DecayY; //!
  Float_t fTreeCascVarV0DecayZ; //!
  Float_t fTreeCascVarCascadeDecayX; //!
  Float_t fTreeCascVarCascadeDecayY; //!
  Float_t fTreeCascVarCascadeDecayZ; //!
  
  Float_t fTreeCascVarV0DecayXMC; //!
  Float_t fTreeCascVarV0DecayYMC; //!
  Float_t fTreeCascVarV0DecayZMC; //!
  Float_t fTreeCascVarCascadeDecayXMC; //!
  Float_t fTreeCascVarCascadeDecayYMC; //!
  Float_t fTreeCascVarCascadeDecayZMC; //!
  
  //Vars for studying cascade decay point calculations
  Float_t fTreeCascVarBachelorDCAptX; //!
  Float_t fTreeCascVarBachelorDCAptY; //!
  Float_t fTreeCascVarBachelorDCAptZ; //!
  Float_t fTreeCascVarV0DCAptX; //!
  Float_t fTreeCascVarV0DCAptY; //!
  Float_t fTreeCascVarV0DCAptZ; //!
  Float_t fTreeCascVarDCADaughters_Test; //!
  Float_t fTreeCascVarBachelorDCAptSigmaX2; //
  Float_t fTreeCascVarBachelorDCAptSigmaY2; //
  Float_t fTreeCascVarBachelorDCAptSigmaZ2; //
  Float_t fTreeCascVarV0DCAptUncertainty_V0Pos; //
  Float_t fTreeCascVarV0DCAptUncertainty_V0Ang; //
  
  Float_t fTreeCascVarV0DCAptPosSigmaX2; //
  Float_t fTreeCascVarV0DCAptPosSigmaY2; //
  Float_t fTreeCascVarV0DCAptPosSigmaZ2; //
  Float_t fTreeCascVarV0DCAptPosSigmaSnp2; //
  Float_t fTreeCascVarV0DCAptPosSigmaTgl2; //
  
  Float_t fTreeCascVarV0DCAptNegSigmaX2; //
  Float_t fTreeCascVarV0DCAptNegSigmaY2; //
  Float_t fTreeCascVarV0DCAptNegSigmaZ2; //
  Float_t fTreeCascVarV0DCAptNegSigmaSnp2; //
  Float_t fTreeCascVarV0DCAptNegSigmaTgl2; //
  
  //Extended information: uncertainties at point closest to pV
  Float_t fTreeCascVarBachDCAPVSigmaX2; //
  Float_t fTreeCascVarBachDCAPVSigmaY2; //
  Float_t fTreeCascVarBachDCAPVSigmaZ2; //
  Float_t fTreeCascVarPosDCAPVSigmaX2; //
  Float_t fTreeCascVarPosDCAPVSigmaY2; //
  Float_t fTreeCascVarPosDCAPVSigmaZ2; //
  Float_t fTreeCascVarNegDCAPVSigmaX2; //
  Float_t fTreeCascVarNegDCAPVSigmaY2; //
  Float_t fTreeCascVarNegDCAPVSigmaZ2; //
  
  Float_t fTreeCascVarPrimVertexX;
  Float_t fTreeCascVarPrimVertexY;
  Float_t fTreeCascVarPrimVertexZ;
  
  Float_t fTreeCascVarMagField; // for X-checks
  
  Float_t fTreeCascVarV0Lifetime; //! //V0 lifetime (actually, mL/p)
  Float_t fTreeCascVarV0ChiSquare; //! //V0 chi2 (defined only for on-the-fly or refitted offline)
  
  //Track Labels (check for duplicates, etc)
  Int_t fTreeCascVarNegIndex; //!
  Int_t fTreeCascVarPosIndex; //!
  Int_t fTreeCascVarBachIndex; //!
  Int_t fTreeCascVarNegLabel; //!
  Int_t fTreeCascVarPosLabel; //!
  Int_t fTreeCascVarBachLabel; //!
  Int_t fTreeCascVarNegLabelMother; //!
  Int_t fTreeCascVarPosLabelMother; //!
  Int_t fTreeCascVarBachLabelMother; //!
  Int_t fTreeCascVarNegLabelGrandMother; //!
  Int_t fTreeCascVarPosLabelGrandMother; //!
  Int_t fTreeCascVarBachLabelGrandMother; //!
  //Event Number (check same-event index mixups)
  ULong64_t fTreeCascVarEventNumber; //!
  
  //Variables for OOB pileup study (high-multiplicity triggers pp 13 TeV - 2016 data)
  Float_t fTreeCascVarNegTOFExpTDiff; //!
  Float_t fTreeCascVarPosTOFExpTDiff; //!
  Float_t fTreeCascVarBachTOFExpTDiff; //!
  Float_t fTreeCascVarNegTOFSignal; //!
  Float_t fTreeCascVarPosTOFSignal; //!
  Float_t fTreeCascVarBachTOFSignal; //!
  Int_t   fTreeCascVarNegTOFBCid; //!
  Int_t   fTreeCascVarPosTOFBCid; //!
  Int_t   fTreeCascVarBachTOFBCid; //!
  //Event info
  Float_t fTreeCascVarAmplitudeV0A; //!
  Float_t fTreeCascVarAmplitudeV0C; //!
  
  //Event Multiplicity Variables
  Float_t fTreeCascVarCentrality; //!
  Bool_t fTreeCascVarMVPileupFlag; //!
  Bool_t fTreeCascVarOOBPileupFlag; //!
  
  //MC-only Variables
  
  Int_t   fTreeCascVarPID;         //!
  Int_t   fTreeCascVarPIDNegative;         //!
  Int_t   fTreeCascVarPIDPositive;         //!
  Int_t   fTreeCascVarPIDBachelor;         //!
  Int_t   fTreeCascVarPIDNegativeMother;         //!
  Int_t   fTreeCascVarPIDPositiveMother;         //!
  Int_t   fTreeCascVarPIDBachelorMother;         //!
  Int_t   fTreeCascVarPIDNegativeGrandMother;         //!
  Int_t   fTreeCascVarPIDPositiveGrandMother;         //!
  Int_t   fTreeCascVarPIDBachelorGrandMother;         //!
  
  Int_t   fTreeCascVarBachCousinStatus;         //!
  Int_t   fTreeCascVarV0BachSibIsValid;         //!
  Int_t   fTreeCascVarBachV0Tagging;         //!
  Int_t   fTreeCascVarV0NegSibIsValid;         //!
  Int_t   fTreeCascVarNegV0Tagging;         //!
  Int_t   fTreeCascVarV0PosSibIsValid;         //!
  Int_t   fTreeCascVarPosV0Tagging;         //!
  
  AliTrackReference* fTreeCascVarBachTrackRef;
  AliTrackReference* fTreeCascVarPosTrackRef;
  AliTrackReference* fTreeCascVarNegTrackRef;
  
  //Bachelor Sibling Testing Variables
  Float_t fTreeCascVarBachSibPt; //!
  Float_t fTreeCascVarBachSibDcaV0ToPrimVertex; //!
  Float_t fTreeCascVarBachSibDcaV0Daughters; //!
  Float_t fTreeCascVarBachSibV0CosineOfPointingAngle; //!
  Float_t fTreeCascVarBachSibV0V0Radius; //!
  Float_t fTreeCascVarBachSibV0DcaPosToPrimVertex; //!
  Float_t fTreeCascVarBachSibV0DcaNegToPrimVertex; //!
  Float_t fTreeCascVarBachSibV0InvMassK0s; //!
  Float_t fTreeCascVarBachSibV0InvMassLambda; //!
  Float_t fTreeCascVarBachSibV0InvMassAntiLambda; //!
  
  //Negative Sibling Testing Variables
  Float_t fTreeCascVarNegSibPt; //!
  Float_t fTreeCascVarNegSibDcaV0ToPrimVertex; //!
  Float_t fTreeCascVarNegSibDcaV0Daughters; //!
  Float_t fTreeCascVarNegSibV0CosineOfPointingAngle; //!
  Float_t fTreeCascVarNegSibV0V0Radius; //!
  Float_t fTreeCascVarNegSibV0DcaPosToPrimVertex; //!
  Float_t fTreeCascVarNegSibV0DcaNegToPrimVertex; //!
  Float_t fTreeCascVarNegSibV0InvMassK0s; //!
  Float_t fTreeCascVarNegSibV0InvMassLambda; //!
  Float_t fTreeCascVarNegSibV0InvMassAntiLambda; //!
  
  //Positive Sibling Testing Variables
  Float_t fTreeCascVarPosSibPt; //!
  Float_t fTreeCascVarPosSibDcaV0ToPrimVertex; //!
  Float_t fTreeCascVarPosSibDcaV0Daughters; //!
  Float_t fTreeCascVarPosSibV0CosineOfPointingAngle; //!
  Float_t fTreeCascVarPosSibV0V0Radius; //!
  Float_t fTreeCascVarPosSibV0DcaPosToPrimVertex; //!
  Float_t fTreeCascVarPosSibV0DcaNegToPrimVertex; //!
  Float_t fTreeCascVarPosSibV0InvMassK0s; //!
  Float_t fTreeCascVarPosSibV0InvMassLambda; //!
  Float_t fTreeCascVarPosSibV0InvMassAntiLambda; //!
  
  Int_t   fTreeCascVarIsPhysicalPrimary; //!
  Bool_t fTreeCascVarIsPhysicalPrimaryNegative;
  Bool_t fTreeCascVarIsPhysicalPrimaryPositive;
  Bool_t fTreeCascVarIsPhysicalPrimaryBachelor;
  Bool_t fTreeCascVarIsPhysicalPrimaryNegativeMother;
  Bool_t fTreeCascVarIsPhysicalPrimaryPositiveMother;
  Bool_t fTreeCascVarIsPhysicalPrimaryBachelorMother;
  Bool_t fTreeCascVarIsPhysicalPrimaryNegativeGrandMother;
  Bool_t fTreeCascVarIsPhysicalPrimaryPositiveGrandMother;
  Bool_t fTreeCascVarIsPhysicalPrimaryBachelorGrandMother;
  
  //Cluster information for all daughter tracks
  Bool_t fTreeCascVarPosITSClusters0;
  Bool_t fTreeCascVarPosITSClusters1;
  Bool_t fTreeCascVarPosITSClusters2;
  Bool_t fTreeCascVarPosITSClusters3;
  Bool_t fTreeCascVarPosITSClusters4;
  Bool_t fTreeCascVarPosITSClusters5;
  
  Bool_t fTreeCascVarNegITSClusters0;
  Bool_t fTreeCascVarNegITSClusters1;
  Bool_t fTreeCascVarNegITSClusters2;
  Bool_t fTreeCascVarNegITSClusters3;
  Bool_t fTreeCascVarNegITSClusters4;
  Bool_t fTreeCascVarNegITSClusters5;
  
  Bool_t fTreeCascVarBachITSClusters0;
  Bool_t fTreeCascVarBachITSClusters1;
  Bool_t fTreeCascVarBachITSClusters2;
  Bool_t fTreeCascVarBachITSClusters3;
  Bool_t fTreeCascVarBachITSClusters4;
  Bool_t fTreeCascVarBachITSClusters5;
  
  //Cluster information for all daughter tracks
  Bool_t fTreeCascVarPosITSSharedClusters0;
  Bool_t fTreeCascVarPosITSSharedClusters1;
  Bool_t fTreeCascVarPosITSSharedClusters2;
  Bool_t fTreeCascVarPosITSSharedClusters3;
  Bool_t fTreeCascVarPosITSSharedClusters4;
  Bool_t fTreeCascVarPosITSSharedClusters5;
  
  Bool_t fTreeCascVarNegITSSharedClusters0;
  Bool_t fTreeCascVarNegITSSharedClusters1;
  Bool_t fTreeCascVarNegITSSharedClusters2;
  Bool_t fTreeCascVarNegITSSharedClusters3;
  Bool_t fTreeCascVarNegITSSharedClusters4;
  Bool_t fTreeCascVarNegITSSharedClusters5;
  
  Bool_t fTreeCascVarBachITSSharedClusters0;
  Bool_t fTreeCascVarBachITSSharedClusters1;
  Bool_t fTreeCascVarBachITSSharedClusters2;
  Bool_t fTreeCascVarBachITSSharedClusters3;
  Bool_t fTreeCascVarBachITSSharedClusters4;
  Bool_t fTreeCascVarBachITSSharedClusters5;
  
  Int_t fTreeCascVarPosTPCNClusters;
  Int_t fTreeCascVarNegTPCNClusters;
  Int_t fTreeCascVarBachTPCNClusters;
  Int_t fTreeCascVarPosTPCNClustersShared;
  Int_t fTreeCascVarNegTPCNClustersShared;
  Int_t fTreeCascVarBachTPCNClustersShared;
  
  //Uncertainty information on mass (from KF) for testing purposes
  Float_t fTreeCascVarV0LambdaMassError;
  Float_t fTreeCascVarV0AntiLambdaMassError;
  
  Bool_t fTreeCascVarBachIsKink;
  Bool_t fTreeCascVarPosIsKink;
  Bool_t fTreeCascVarNegIsKink;
  
  Bool_t fTreeCascVarIsValidAddedITSPointLayer1;
  Bool_t fTreeCascVarIsValidAddedITSPointLayer2;
  Bool_t fTreeCascVarAddedHitLayer1;
  Bool_t fTreeCascVarAddedHitLayer2;
  
  //Cowboy/sailor studies
  Bool_t  fTreeCascVarIsCowboy;   //store if V0 is cowboy-like or sailor-like in XY plane
  Float_t fTreeCascVarCowboyness; //negative -> cowboy, positive -> sailor
  Bool_t  fTreeCascVarIsCascadeCowboy;   //store if V0 is cowboy-like or sailor-like in XY plane
  Float_t fTreeCascVarCascadeCowboyness; //negative -> cowboy, positive -> sailor
  
  //Well, why not? Let's give it a shot
  Int_t   fTreeCascVarSwappedPID;         //!
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  //Save full info for full re-vertex offline replay ('sandbox mode')
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  AliExternalTrackParam *fTreeCascVarBachTrack;
  AliExternalTrackParam *fTreeCascVarPosTrack;
  AliExternalTrackParam *fTreeCascVarNegTrack;
  AliESDVertex *fTreeCascVarAliESDvertex;//!
  
  AliExternalTrackParam *fTreeCascVarCascadeTrack;
  AliExternalTrackParam *fTreeCascVarCascadeTrackImproved;
  
  Float_t fTreeCascVarMagneticField;
  
  //===========================================================================================
  //   Histograms
  //===========================================================================================
  
  TH1D *fHistEventCounter; //!
  TH1D *fHistCentrality;
  
  //Histograms for efficiency denominators (at final analysis level selections)
  //V0s
  TH3D *fHistGeneratedPtVsYVsCentralityK0Short;
  TH3D *fHistGeneratedPtVsYVsCentralityLambda;
  TH3D *fHistGeneratedPtVsYVsCentralityAntiLambda;
  
  //Cascades
  TH3D *fHistGeneratedPtVsYVsCentralityXiMinus;
  TH3D *fHistGeneratedPtVsYVsCentralityXiPlus;
  TH3D *fHistGeneratedPtVsYVsCentralityOmegaMinus;
  TH3D *fHistGeneratedPtVsYVsCentralityOmegaPlus;
  
  //Hypertriton
  TH3D *fHistGeneratedPtVsYVsCentralityHypertriton;
  TH3D *fHistGeneratedPtVsYVsCentralityAntihypertriton;
  
  AliAnalysisTaskStrangenessVsMultiplicityMCRun2(const AliAnalysisTaskStrangenessVsMultiplicityMCRun2&);            // not implemented
  AliAnalysisTaskStrangenessVsMultiplicityMCRun2& operator=(const AliAnalysisTaskStrangenessVsMultiplicityMCRun2&); // not implemented
  
  ClassDef(AliAnalysisTaskStrangenessVsMultiplicityMCRun2, 2);
  //1: first implementation
  //2: Addition of ML Classes Data members
};

#endif
