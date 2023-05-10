/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>

//==============================================================================
JZDelayAudioProcessor::JZDelayAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
{
    // set universal parameters first
    inputGain = pow(10, 0.0); // start input gain at 1.0
    outputGain = pow(10, 0.0); // start output gain at 1.0
    dryMix = 100.0;
    
    // set default parameters for delay 1
    delayOneEnable = false;
    numSamples = ceil(.001 * 70.0 * getSampleRate());
    decayRate = 0.75;
    delayTime = 70.0;
    wetMix = 50.0;
    pan = 0.5;
    echoListL = (float*)calloc(10000, sizeof(float));
    echoListR = (float*)calloc(10000, sizeof(float));
    
    // set default parameters for delay 2
    delayTwoEnable = false;
    numTwoSamples = ceil(.001 * 70.0 * getSampleRate());
    decayTwoRate = 0.75;
    delayTwoTime = 70.0;
    wetTwoMix = 50.0;
    panTwo = 0.5;
    echoTwoListL = (float*)calloc(10000, sizeof(float));
    echoTwoListR = (float*)calloc(10000, sizeof(float));
    
    // set default parameters for delay 3
    delayThreeEnable = false;
    numThreeSamples = ceil(.001 * 70.0 * getSampleRate());
    decayThreeRate = 0.75;
    delayThreeTime = 70.0;
    wetThreeMix = 50.0;
    panThree = 0.5;
    echoThreeListL = (float*)calloc(10000, sizeof(float));
    echoThreeListR = (float*)calloc(10000, sizeof(float));
    
    
    // set default parameters for delay 4
    delayFourEnable = false;
    numFourSamples = ceil(.001 * 70.0 * getSampleRate());
    decayFourRate = 0.75;
    delayFourTime = 70.0;
    wetFourMix = 50.0;
    panFour = 0.5;
    echoFourListL = (float*)calloc(10000, sizeof(float));
    echoFourListR = (float*)calloc(10000, sizeof(float));
}

JZDelayAudioProcessor::~JZDelayAudioProcessor()
{
}

//==============================================================================
const juce::String JZDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JZDelayAudioProcessor::acceptsMidi() const
{
    return false;
}

bool JZDelayAudioProcessor::producesMidi() const
{
    return false;
}

bool JZDelayAudioProcessor::isMidiEffect() const
{
    return false;
}

double JZDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JZDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JZDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JZDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JZDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void JZDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JZDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    readPosL = 1;
    writePosL = 0;
    readPosR = 1;
    writePosR = 0;
    
    readTwoPosL = 1;
    writeTwoPosL = 0;
    readTwoPosR = 1;
    writeTwoPosR = 0;
    
    readThreePosL = 1;
    writeThreePosL = 0;
    readThreePosR = 1;
    writeThreePosR = 0;
    
    readFourPosL = 1;
    writeFourPosL = 0;
    readFourPosR = 1;
    writeFourPosR = 0;
}

void JZDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JZDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JZDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    // input gain
    buffer.applyGain(0, 0, buffer.getNumSamples(), inputGain);
    buffer.applyGain(1, 0, buffer.getNumSamples(), inputGain);
    
    
    float origL;
    float origR;
    
    float tempL;
    float tempR;
    
    float tempTwoL;
    float tempTwoR;
    
    float tempThreeL;
    float tempThreeR;
    
    float tempFourL;
    float tempFourR;
    
    float mult1, mult2, mult3, mult4;
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelWData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            tempL = 0;
            tempR = 0;
            
            tempTwoL = 0;
            tempTwoR = 0;
            
            tempThreeL = 0;
            tempThreeR = 0;
            
            tempFourL = 0;
            tempFourR = 0;
            
            mult1 = 0;
            mult2 = 0;
            mult3 = 0;
            mult4 = 0;
            
            if (channel == 0)
            {
                // L processing
                origL = channelWData[sample];
                
                readPosL = readPosL + 1 >= numSamples ? 0 : (readPosL + 1);
                writePosL = writePosL + 1 >= numSamples ? 0 : (writePosL + 1);
                
                readTwoPosL = readTwoPosL + 1 >= numTwoSamples ? 0 : (readTwoPosL + 1);
                writeTwoPosL = writeTwoPosL + 1 >= numTwoSamples ? 0 : (writeTwoPosL + 1);
                
                readThreePosL = readThreePosL + 1 >= numThreeSamples ? 0 : (readThreePosL + 1);
                writeThreePosL = writeThreePosL + 1 >= numThreeSamples ? 0 : (writeThreePosL + 1);
                
                readFourPosL = readFourPosL + 1 >= numFourSamples ? 0 : (readFourPosL + 1);
                writeFourPosL = writeFourPosL + 1 >= numFourSamples ? 0 : (writeFourPosL + 1);
                
                tempL = (float)(decayRate * echoListL[readPosL]);
                echoListL[writePosL] = origL + tempL;
                tempTwoL = (float)(decayTwoRate * echoTwoListL[readTwoPosL]);
                echoTwoListL[writeTwoPosL] = origL + tempTwoL;
                tempThreeL = (float)(decayThreeRate * echoThreeListL[readThreePosL]);
                echoThreeListL[writeThreePosL] = origL + tempThreeL;
                tempFourL = (float)(decayFourRate * echoFourListL[readFourPosL]);
                echoFourListL[writeFourPosL] = origL + tempFourL;
                
                if (delayOneEnable) {
                    mult1 = 1.0;
                }
                if (delayTwoEnable) {
                    mult2 = 1.0;
                }
                if (delayThreeEnable) {
                    mult3 = 1.0;
                }
                if (delayFourEnable) {
                    mult4 = 1.0;
                }
                
                channelWData[sample] = (wetMix*0.01) * tempL * mult1 +
                                       (wetTwoMix*0.01) * tempTwoL * mult2 +
                                       (wetThreeMix*0.01) * tempThreeL * mult3 +
                                       (wetFourMix*0.01) * tempFourL * mult4 +
                                       (dryMix*0.01) * origL;
                
            }
            else if (channel == 1)
            {
                // R processing
                origR = channelWData[sample];
                
                readPosR = readPosR + 1 >= numSamples ? 0 : (readPosR + 1);
                writePosR = writePosR + 1 >= numSamples ? 0 : (writePosR + 1);
                
                readTwoPosR = readTwoPosR + 1 >= numTwoSamples ? 0 : (readTwoPosR + 1);
                writeTwoPosR = writeTwoPosR + 1 >= numTwoSamples ? 0 : (writeTwoPosR + 1);
                
                readThreePosR = readThreePosR + 1 >= numThreeSamples ? 0 : (readThreePosR + 1);
                writeThreePosR = writeThreePosR + 1 >= numThreeSamples ? 0 : (writeThreePosR + 1);
                
                readFourPosR = readFourPosR + 1 >= numFourSamples ? 0 : (readFourPosR + 1);
                writeFourPosR = writeFourPosR + 1 >= numFourSamples ? 0 : (writeFourPosR + 1);
                
                tempR = (float)(decayRate * echoListR[readPosR]);
                echoListR[writePosR] = origR + tempR;
                tempTwoR = (float)(decayTwoRate * echoTwoListR[readTwoPosR]);
                echoTwoListR[writeTwoPosR] = origR + tempTwoR;
                tempThreeR = (float)(decayThreeRate * echoThreeListR[readThreePosR]);
                echoThreeListR[writeThreePosR] = origR + tempThreeR;
                tempFourR = (float)(decayFourRate * echoFourListR[readFourPosR]);
                echoFourListR[writeFourPosR] = origR + tempFourR;
                
                if (delayOneEnable) {
                    mult1 = 1.0;
                }
                if (delayTwoEnable) {
                    mult2 = 1.0;
                }
                if (delayThreeEnable) {
                    mult3 = 1.0;
                }
                if (delayFourEnable) {
                    mult4 = 1.0;
                }
                channelWData[sample] = (wetMix*0.01) * tempR*mult1 +
                                       (wetTwoMix*0.01) * tempTwoR * mult2 +
                                       (wetThreeMix*0.01) * tempThreeR * mult3 +
                                       (wetFourMix*0.01) * tempFourR * mult4 +
                                       (dryMix*0.01)*origR;
            }
        }
    }
    
    // output gain
    buffer.applyGain(0, 0, buffer.getNumSamples(), outputGain);
    buffer.applyGain(1, 0, buffer.getNumSamples(), outputGain);
}

//==============================================================================
bool JZDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JZDelayAudioProcessor::createEditor()
{
    return new JZDelayAudioProcessorEditor (*this);
}

//==============================================================================
void JZDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JZDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JZDelayAudioProcessor();
}
