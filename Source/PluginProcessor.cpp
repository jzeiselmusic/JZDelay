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
    buffer.applyGain(0, 0, buffer.getNumSamples(), pow(10, inputGain/20.0));
    buffer.applyGain(1, 0, buffer.getNumSamples(), pow(10, inputGain/20.0));
    
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
    
    float pan_L_val_1;
    float pan_L_val_2;
    float pan_L_val_3;
    float pan_L_val_4;
    
    float pan_R_val_1;
    float pan_R_val_2;
    float pan_R_val_3;
    float pan_R_val_4;
    
    
    float mult1, mult2, mult3, mult4;
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelRData = buffer.getReadPointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            
            // set these to 0.0 so that they must be
            // recalculated every time we read from the buffer
            //
            tempL = 0.0;
            tempR = 0.0;
            
            tempTwoL = 0.0;
            tempTwoR = 0.0;
            
            tempThreeL = 0.0;
            tempThreeR = 0.0;
            
            tempFourL = 0.0;
            tempFourR = 0.0;
            
            mult1 = 0;
            mult2 = 0;
            mult3 = 0;
            mult4 = 0;
            
            if (channel == 0)
            {
                // L processing
                
                // original input data
                origL = channelRData[sample];
                
                // increment read and write positions
                readPosL = readPosL + 1 >= (numSamples/2.0) ? 0 : (readPosL + 1);
                writePosL = writePosL + 1 >= (numSamples/2.0) ? 0 : (writePosL + 1);
                
                readTwoPosL = readTwoPosL + 1 >= (numTwoSamples/2.0) ? 0 : (readTwoPosL + 1);
                writeTwoPosL = writeTwoPosL + 1 >= (numTwoSamples/2.0) ? 0 : (writeTwoPosL + 1);
                
                readThreePosL = readThreePosL + 1 >= (numThreeSamples/2.0) ? 0 : (readThreePosL + 1);
                writeThreePosL = writeThreePosL + 1 >= (numThreeSamples/2.0) ? 0 : (writeThreePosL + 1);
                
                readFourPosL = readFourPosL + 1 >= (numFourSamples/2.0) ? 0 : (readFourPosL + 1);
                writeFourPosL = writeFourPosL + 1 >= (numFourSamples/2.0) ? 0 : (writeFourPosL + 1);
                
                // calculate regressive echo value
                // and write to echo buffer only the value that must echo and original input
                // we keep separate echo buffers for each delay
                tempL = (float)(decayRate * echoListL[readPosL]);
                tempL = lowpassFilter(tempL, 0); // 0 for left side
                echoListL[writePosL] = origL + tempL;
                tempTwoL = (float)(decayTwoRate * echoTwoListL[readTwoPosL]);
                echoTwoListL[writeTwoPosL] = origL + tempTwoL;
                tempThreeL = (float)(decayThreeRate * echoThreeListL[readThreePosL]);
                echoThreeListL[writeThreePosL] = origL + tempThreeL;
                tempFourL = (float)(decayFourRate * echoFourListL[readFourPosL]);
                echoFourListL[writeFourPosL] = origL + tempFourL;
                
                // enable or disable based on button
                if (delayOneEnable)
                {
                    mult1 = 1.0;
                }
                if (delayTwoEnable)
                {
                    mult2 = 1.0;
                }
                if (delayThreeEnable)
                {
                    mult3 = 1.0;
                }
                if (delayFourEnable)
                {
                    mult4 = 1.0;
                }
                
                // calculate pan value for each component
                pan_L_val_1 = 1.0 - ((pan / 200.0) + 0.5);
                pan_L_val_2 = 1.0 - ((panTwo / 200.0) + 0.5);
                pan_L_val_3 = 1.0 - ((panThree / 200.0) + 0.5);
                pan_L_val_4 = 1.0 - ((panFour / 200.0) + 0.5);
                
                // full calculation of output
                // and write to channel data buffer output
                
                outputBufL[sample] = (wetMix*0.01) * tempL * mult1 * pan_L_val_1;
                outputTwoBufL[sample] = (wetTwoMix*0.01) * tempTwoL * mult2 * pan_L_val_2;
                outputThreeBufL[sample] = (wetThreeMix*0.01) * tempThreeL * mult3 * pan_L_val_3;
                outputFourBufL[sample] = (wetFourMix*0.01) * tempFourL * mult4 * pan_L_val_4;
                
                /*channelWData[sample] = (wetMix*0.01) * tempL * mult1 * pan_L_val_1 +
                                       (wetTwoMix*0.01) * tempTwoL * mult2 * pan_L_val_2 +
                                       (wetThreeMix*0.01) * tempThreeL * mult3 * pan_L_val_3 +
                                       (wetFourMix*0.01) * tempFourL * mult4 * pan_L_val_4 +
                                       (dryMix*0.01) * origL;*/
                
            }
            else if (channel == 1)
            {
                // R processing
                origR = channelRData[sample];
                
                readPosR = readPosR + 1 >= (numSamples/2.0) ? 0 : (readPosR + 1);
                writePosR = writePosR + 1 >= (numSamples/2.0) ? 0 : (writePosR + 1);
                
                readTwoPosR = readTwoPosR + 1 >= (numTwoSamples/2.0) ? 0 : (readTwoPosR + 1);
                writeTwoPosR = writeTwoPosR + 1 >= (numTwoSamples/2.0) ? 0 : (writeTwoPosR + 1);
                
                readThreePosR = readThreePosR + 1 >= (numThreeSamples/2.0) ? 0 : (readThreePosR + 1);
                writeThreePosR = writeThreePosR + 1 >= (numThreeSamples/2.0) ? 0 : (writeThreePosR + 1);
                
                readFourPosR = readFourPosR + 1 >= (numFourSamples/2.0) ? 0 : (readFourPosR + 1);
                writeFourPosR = writeFourPosR + 1 >= (numFourSamples/2.0) ? 0 : (writeFourPosR + 1);
                
                tempR = (float)(decayRate * echoListR[readPosR]);
                tempR = lowpassFilter(tempR, 1); // 1 for right side
                echoListR[writePosR] = origR + tempR;
                tempTwoR = (float)(decayTwoRate * echoTwoListR[readTwoPosR]);
                echoTwoListR[writeTwoPosR] = origR + tempTwoR;
                tempThreeR = (float)(decayThreeRate * echoThreeListR[readThreePosR]);
                echoThreeListR[writeThreePosR] = origR + tempThreeR;
                tempFourR = (float)(decayFourRate * echoFourListR[readFourPosR]);
                echoFourListR[writeFourPosR] = origR + tempFourR;
                
                if (delayOneEnable)
                {
                    mult1 = 1.0;
                }
                if (delayTwoEnable)
                {
                    mult2 = 1.0;
                }
                if (delayThreeEnable)
                {
                    mult3 = 1.0;
                }
                if (delayFourEnable)
                {
                    mult4 = 1.0;
                }
                
                // calculate pan value for each component
                pan_R_val_1 = (pan / 200.0) + 0.5;
                pan_R_val_2 = (panTwo / 200.0) + 0.5;
                pan_R_val_3 = (panThree / 200.0) + 0.5;
                pan_R_val_4 = (panFour / 200.0) + 0.5;
                
                outputBufR[sample] = (wetMix*0.01) * tempR * mult1 * pan_R_val_1;
                outputTwoBufR[sample] = (wetTwoMix*0.01) * tempTwoR * mult2 * pan_R_val_2;
                outputThreeBufR[sample] = (wetThreeMix*0.01) * tempThreeR * mult3 * pan_R_val_3;
                outputFourBufR[sample] = (wetFourMix*0.01) * tempFourR * mult4 * pan_R_val_4;
                
                /*channelWData[sample] = (wetMix*0.01) * tempR*mult1 * pan_R_val_1 +
                                       (wetTwoMix*0.01) * tempTwoR * mult2 * pan_R_val_2 +
                                       (wetThreeMix*0.01) * tempThreeR * mult3 * pan_R_val_3 +
                                       (wetFourMix*0.01) * tempFourR * mult4 * pan_R_val_4 +
                                       (dryMix*0.01)*origR;*/
            }
            
        }
    }
    
    // now all the output buffers should be filled and we need to
    // 1. if necessary, do pitch shifting on them
    // 2. afterwards, mix them together into a single output buffer
    
    // pitch shifting
    float* temp_pitch_bufferL = (float*)calloc(buffer.getNumSamples(), sizeof(float));
    float* temp_pitch_bufferR = (float*)calloc(buffer.getNumSamples(), sizeof(float));
    int iterator = 0;
    if (pitchOneEnable)
    {
        // go through output buffer and take every other sample
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            if (i%2 == 0)
            {
                temp_pitch_bufferL[iterator] = outputBufL[i];
                temp_pitch_bufferR[iterator] = outputBufR[i];
                ++iterator;
            }
        }
        for (int i = 0; i < buffer.getNumSamples()/2; ++i)
        {
            outputBufL[i] = temp_pitch_bufferL[i];
            outputBufR[i] = temp_pitch_bufferR[i];
        }
        for (int i = 0; i < buffer.getNumSamples()/2; ++i)
        {
            outputBufL[buffer.getNumSamples()/2 + i] = temp_pitch_bufferL[i];
            outputBufR[buffer.getNumSamples()/2 + i] = temp_pitch_bufferR[i];
        }
    }
    if (pitchTwoEnable)
    {
        
    }
    if (pitchThreeEnable)
    {
        
    }
    if (pitchFourEnable)
    {
        
    }
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelWData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            if (channel == 0)
            {
                channelWData[sample] = outputBufL[sample] + outputTwoBufL[sample] +
                                        outputThreeBufL[sample] + outputFourBufL[sample] +
                                        (dryMix*0.01) * channelWData[sample];
            }
            else if (channel == 1)
            {
                channelWData[sample] = outputBufR[sample] + outputTwoBufR[sample] +
                                       outputThreeBufR[sample] + outputFourBufR[sample] +
                                        (dryMix*0.01) * channelWData[sample];
            }
        }
    }
    
    
    // output gain
    buffer.applyGain(0, 0, buffer.getNumSamples(), pow(10, outputGain/20.0));
    buffer.applyGain(1, 0, buffer.getNumSamples(), pow(10, outputGain/20.0));
}

//==============================================================================

float JZDelayAudioProcessor::lowpassFilter(float current_val, int side)
{
    float result;
    float result_b;
    float result_a;
    if (side == 0) // for L
    {
        itL = lpfVecL.begin();
        lpfVecL.insert(itL, current_val);
        if (lpfVecL.size() > FILTER_LEN+10)
        {
            lpfVecL.pop_back();
            lpfVecLFilt.pop_back();
            result_b = 0.0;
            result_a = 0.0;
            for (int i = 0; i < FILTER_LEN; ++i)
            {
                result_b += lpfVecL[i]*filt_b[i];
                if (i < FILTER_LEN-1)
                {
                    result_a += lpfVecLFilt[i]*filt_a[i+1];
                }
            }
            result = result_b - result_a;
            itLFilt = lpfVecLFilt.begin();
            lpfVecLFilt.insert(itLFilt, result);
            return result;
        }
        else
        {
            itLFilt = lpfVecLFilt.begin();
            lpfVecLFilt.insert(itLFilt, current_val);
            return current_val;
        }
    }
    else if (side == 1) // for R
    {
        itR = lpfVecR.begin();
        lpfVecR.insert(itR, current_val);
        if (lpfVecR.size() > FILTER_LEN+10)
        {
            lpfVecR.pop_back();
            lpfVecRFilt.pop_back();
            result_b = 0.0;
            result_a = 0.0;
            for (int i = 0; i < FILTER_LEN; ++i)
            {
                result_b += lpfVecR[i]*filt_b[i];
                if (i < FILTER_LEN-1)
                {
                    result_a += lpfVecRFilt[i]*filt_a[i+1];
                }
            }
            result = result_b - result_a;
            itRFilt = lpfVecRFilt.begin();
            lpfVecRFilt.insert(itRFilt, result);
            return result;
        }
        else
        {
            itRFilt = lpfVecRFilt.begin();
            lpfVecRFilt.insert(itRFilt, current_val);
            return current_val;
        }
    }
    return 0.0;
}


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
