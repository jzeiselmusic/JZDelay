/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>

#define RT_FILTER_LEN   21
#define ST_FILTER_LEN   6
#define MAX_BUF_SIZE    2048

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
    
    float lowpassFilterRT(float, int);
    void lowpassFilterStatic(float*, int);
    
    // universal parameter values
    float inputGain = 0.0;
    float outputGain = 0.0;
    float dryMix = 100.0;
    
    int bufferLen = 100000;
    
    
    std::vector<float> lpfVecL;
    std::vector<float> lpfVecLFilt;
    std::vector<float>::iterator itLFilt;
    std::vector<float>::iterator itL;
    std::vector<float> lpfVecR;
    std::vector<float> lpfVecRFilt;
    std::vector<float>::iterator itR;
    std::vector<float>::iterator itRFilt;
    
    // low pass filter at 10k Hz (for 44.1k sample rate)
    float filt_b[RT_FILTER_LEN] = {.0000018455, .00003691, .00035065,
                        .0021039, .008941, .0286,
                        .071532, .14306, .23248,
                        .30997, .3409, .30997,
                        .23248, .14306, .071432,
                        .0286, .008941, .0021039,
                        .00035065, .00003691, .0000018455};
    float filt_a[RT_FILTER_LEN] = {1.0, -1.8575, 4.3097, -5.2722, 6.5736,
                        -5.7714, 4.8401, -3.1634, 1.9135, -.94161,
                        .41936, -.15433, .0502, -.0134, .003105,
                        -.00057566, .00008722, -.00001002,
                        .0000008468, -.00000004552, .0000000012};
    
    float filt_bb[ST_FILTER_LEN] = {0.052786, 0.263932, 0.52786, 0.52786, 0.263932, 0.052786};
    float filt_aa[ST_FILTER_LEN] = {1.0, 0.0, 0.63344, 0.0, 0.055728, 0.0};
    
    //**************************************//
    //**************************************//
    
    // delay 1 parameter editor values
    float delayTime = 200.0;
    float decayRate = 0.75;
    float wetMix = 50.0;
    float pan = 0.0;
    bool delayOneEnable = false;
    bool pitchOneEnable = false;
    
    // delay 1 parameter processor values
    int numSamples = ceil(.001 * delayTime * getSampleRate());
    int readPosL;
    int writePosL;
    int readPosR;
    int writePosR;
    
    // delay 1 list to store memory values
    float* echoListL = (float*)calloc(bufferLen, sizeof(float));
    float* echoListR = (float*)calloc(bufferLen, sizeof(float));
    
    // lists to store the output buffer that will be mixed with others
    float* outputBufL = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    float* outputBufR = (float*)calloc(MAX_BUF_SIZE, sizeof(float));

    
    //**************************************//
    //**************************************//
    
    // delay 2 parameter editor values
    float delayTwoTime = 200.0;
    float decayTwoRate = 0.75;
    float wetTwoMix = 50.0;
    float panTwo = 0.0;
    bool delayTwoEnable = false;
    bool pitchTwoEnable = false;
    
    // delay 2 parameter processor values
    int numTwoSamples = ceil(.001 * delayTwoTime * getSampleRate());
    int readTwoPosL;
    int writeTwoPosL;
    int readTwoPosR;
    int writeTwoPosR;
    
    // delay 2 list to store memory values
    float* echoTwoListL = (float*)calloc(bufferLen, sizeof(float));
    float* echoTwoListR = (float*)calloc(bufferLen, sizeof(float));
    
    // lists to store the output buffer that will be mixed with others
    float* outputTwoBufL = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    float* outputTwoBufR = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    
    //**************************************//
    //**************************************//
    
    // delay 3 parameter editor values
    float delayThreeTime = 200.0;
    float decayThreeRate = 0.75;
    float wetThreeMix = 50.0;
    float panThree = 0.0;
    bool delayThreeEnable = false;
    bool pitchThreeEnable = false;
    
    // delay 3 parameter processor values
    int numThreeSamples = ceil(.001 * delayThreeTime * getSampleRate());
    int readThreePosL;
    int writeThreePosL;
    int readThreePosR;
    int writeThreePosR;
    
    // delay 3 list to store memory values
    float* echoThreeListL = (float*)calloc(bufferLen, sizeof(float));
    float* echoThreeListR = (float*)calloc(bufferLen, sizeof(float));
    
    // lists to store the output buffer that will be mixed with others
    float* outputThreeBufL = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    float* outputThreeBufR = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    
    //**************************************//
    //**************************************//
    
    // delay 4 parameter editor values
    float delayFourTime = 200.0;
    float decayFourRate = 0.75;
    float wetFourMix = 50.0;
    float panFour = 0.0;
    bool delayFourEnable = false;
    bool pitchFourEnable = false;
    
    // delay 4 parameter processor values
    int numFourSamples = ceil(.001 * delayFourTime * getSampleRate());
    int readFourPosL;
    int writeFourPosL;
    int readFourPosR;
    int writeFourPosR;
    
    // delay 4 list to store memory values
    float* echoFourListL = (float*)calloc(bufferLen, sizeof(float));
    float* echoFourListR = (float*)calloc(bufferLen, sizeof(float));
    
    // lists to store the output buffer that will be mixed with others
    float* outputFourBufL = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    float* outputFourBufR = (float*)calloc(MAX_BUF_SIZE, sizeof(float));
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JZDelayAudioProcessor)
};
