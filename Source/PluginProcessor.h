/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    
    // universal parameter values
    float inputGain;
    float outputGain;
    float dryMix;
    
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
    
    // delay 1 list to store memory values
    float* echoListL;
    float* echoListR;
    
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
