/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>

#define FILTER_LEN 21

//==============================================================================
/**
*/
class JZDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    JZDelayAudioProcessor();
    ~JZDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float lowpassFilter(float, int);
    
    // universal parameter values
    float inputGain;
    float outputGain;
    float dryMix;
    
    int bufferLen = 100000;
    
    std::vector<float> lpfVecL;
    std::vector<float> lpfVecLFilt;
    std::vector<float>::iterator itLFilt;
    std::vector<float>::iterator itL;
    std::vector<float> lpfVecR;
    std::vector<float> lpfVecRFilt;
    std::vector<float>::iterator itR;
    std::vector<float>::iterator itRFilt;
    
    float filt_b[FILTER_LEN] = {.0000018455, .00003691, .00035065,
                        .0021039, .008941, .0286,
                        .071532, .14306, .23248,
                        .30997, .3409, .30997,
                        .23248, .14306, .071432,
                        .0286, .008941, .0021039,
                        .00035065, .00003691, .0000018455};
    float filt_a[FILTER_LEN] = {1.0, -1.8575, 4.3097, -5.2722, 6.5736,
                        -5.7714, 4.8401, -3.1634, 1.9135, -.94161,
                        .41936, -.15433, .0502, -.0134, .003105,
                        -.00057566, .00008722, -.00001002,
                        .0000008468, -.00000004552, .0000000012};
    
    //**************************************//
    //**************************************//
    
    // delay 1 parameter editor values
    float delayTime;
    float decayRate;
    float wetMix;
    bool delayOneEnable;
    float pan;
    
    // delay 1 parameter processor values
    int numSamples;
    int readPosL;
    int writePosL;
    int readPosR;
    int writePosR;
    
    int envelopeVal;
    
    // delay 1 list to store memory values
    float* echoListL;
    float* echoListR;
    
    int* envelopeList;

    
    //**************************************//
    //**************************************//
    
    // delay 2 parameter editor values
    float delayTwoTime;
    float decayTwoRate;
    float wetTwoMix;
    bool delayTwoEnable;
    float panTwo;
    
    // delay 2 parameter processor values
    int numTwoSamples;
    int readTwoPosL;
    int writeTwoPosL;
    int readTwoPosR;
    int writeTwoPosR;
    
    // delay 2 list to store memory values
    float* echoTwoListL;
    float* echoTwoListR;
    
    //**************************************//
    //**************************************//
    
    // delay 3 parameter editor values
    float delayThreeTime;
    float decayThreeRate;
    float wetThreeMix;
    bool delayThreeEnable;
    float panThree;
    
    // delay 3 parameter processor values
    int numThreeSamples;
    int readThreePosL;
    int writeThreePosL;
    int readThreePosR;
    int writeThreePosR;
    
    // delay 3 list to store memory values
    float* echoThreeListL;
    float* echoThreeListR;
    
    //**************************************//
    //**************************************//
    
    // delay 4 parameter editor values
    float delayFourTime;
    float decayFourRate;
    float wetFourMix;
    bool delayFourEnable;
    float panFour;
    
    // delay 4 parameter processor values
    int numFourSamples;
    int readFourPosL;
    int writeFourPosL;
    int readFourPosR;
    int writeFourPosR;
    
    // delay 4 list to store memory values
    float* echoFourListL;
    float* echoFourListR;
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JZDelayAudioProcessor)
};
