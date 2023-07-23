/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Module.h"
#include "Global.h"
#include "JZLookAndFeel.h"

//==============================================================================
JZDelayAudioProcessorEditor::JZDelayAudioProcessorEditor (JZDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (730, 600);
    
    //**************************************************************************//
    //**************************************************************************//
    
    // initial value is whatever audioprocessor says it is
    float igval = audioProcessor.inputGain;
    float ogval = audioProcessor.outputGain;
    float dmval = audioProcessor.dryMix;
    
    Global global_module = Global();
    global_module.setBoundaries(20, 225, 55, 520);
    global_module.setNumSliders(3);
    global_module.addSlider(&inputGainSlider, &inputGainLabel, "Input Gain", 0, -24.0, 24.0, 0.01, igval, 0.0, this, &sliderLookAndFeel);
    global_module.addSlider(&outputGainSlider, &outputGainLabel, "Output Gain", 1, -24.0, 24.0, 0.01, ogval, 0.0, this, &sliderLookAndFeel);
    global_module.addSlider(&dryMixSlider, &dryMixLabel, "Dry Mix", 2, 0.0, 100.0, 0.1, dmval, 100.0, this, &sliderLookAndFeel);
    global_module.makeVisible(this);
    
    
    //**************************************************************************//
    //**************************************************************************//
    
    Module delay1_module = Module();
    delay1_module.setEffectName("Delay 1");
    delay1_module.setNumSliders(4);
    delay1_module.setBoundaries(230, 455, 30, 300);
    float dT_val = audioProcessor.delayTime;
    float dR_val = audioProcessor.decayRate;
    float wM_val = audioProcessor.wetMix;
    float pS_val = audioProcessor.pan;
    delay1_module.addSlider(&delayTimeSlider, &delayTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, dT_val, 70.0, this, &sliderLookAndFeel);
    delay1_module.addSlider(&decayRateSlider, &decayRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, dR_val, 0.75, this, &sliderLookAndFeel);
    delay1_module.addSlider(&wetMixSlider, &wetMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, wM_val, 50.0, this, &sliderLookAndFeel);
    delay1_module.addSlider(&panSlider, &panLabel, "Pan", 3, -100.0, 100.0, 0.1, pS_val, 0.0, this, &sliderLookAndFeel);
    
    Module delay2_module = Module();
    delay2_module.setEffectName("Delay 2");
    delay2_module.setNumSliders(4);
    delay2_module.setBoundaries(230, 455, 310, 580);
    float dT2_val = audioProcessor.delayTwoTime;
    float dR2_val = audioProcessor.decayTwoRate;
    float wM2_val = audioProcessor.wetTwoMix;
    float pS2_val = audioProcessor.panTwo;
    delay2_module.addSlider(&delayTwoTimeSlider, &delayTwoTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, dT2_val, 70.0, this, &sliderLookAndFeel);
    delay2_module.addSlider(&decayTwoRateSlider, &decayTwoRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, dR2_val, 0.75, this, &sliderLookAndFeel);
    delay2_module.addSlider(&wetTwoMixSlider, &wetTwoMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, wM2_val, 50.0, this, &sliderLookAndFeel);
    delay2_module.addSlider(&panTwoSlider, &panTwoLabel, "Pan", 3, -100.0, 100.0, 0.1, pS2_val, 0.0, this, &sliderLookAndFeel);
    
    Module delay3_module = Module();
    delay3_module.setEffectName("Delay 3");
    delay3_module.setNumSliders(4);
    delay3_module.setBoundaries(480, 705, 30, 300);
    float dT3_val = audioProcessor.delayThreeTime;
    float dR3_val = audioProcessor.decayThreeRate;
    float wM3_val = audioProcessor.wetThreeMix;
    float pS3_val = audioProcessor.panThree;
    delay3_module.addSlider(&delayThreeTimeSlider, &delayThreeTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, dT3_val, 70.0, this, &sliderLookAndFeel);
    delay3_module.addSlider(&decayThreeRateSlider, &decayThreeRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, dR3_val, 0.75, this, &sliderLookAndFeel);
    delay3_module.addSlider(&wetThreeMixSlider, &wetThreeMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, wM3_val, 50.0, this, &sliderLookAndFeel);
    delay3_module.addSlider(&panThreeSlider, &panThreeLabel, "Pan", 3, -100.0, 100.0, 0.1, pS3_val, 0.0, this, &sliderLookAndFeel);
    
    Module delay4_module = Module();
    delay4_module.setEffectName("Delay 4");
    delay4_module.setNumSliders(4);
    delay4_module.setBoundaries(480, 705, 310, 580);
    float dT4_val = audioProcessor.delayFourTime;
    float dR4_val = audioProcessor.decayFourRate;
    float wM4_val = audioProcessor.wetFourMix;
    float pS4_val = audioProcessor.panFour;
    delay4_module.addSlider(&delayFourTimeSlider, &delayFourTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, dT4_val, 70.0, this, &sliderLookAndFeel);
    delay4_module.addSlider(&decayFourRateSlider, &decayFourRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, dR4_val, 0.75, this, &sliderLookAndFeel);
    delay4_module.addSlider(&wetFourMixSlider, &wetFourMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, wM4_val, 50.0, this, &sliderLookAndFeel);
    delay4_module.addSlider(&panFourSlider, &panFourLabel, "Pan", 3, -100.0, 100.0, 0.1, pS4_val, 0.0, this, &sliderLookAndFeel);
    
    delayOneButton.setToggleState(audioProcessor.delayOneEnable, juce::NotificationType::dontSendNotification);
    delay1_module.setNumButtons(5);
    delay1_module.addButton(&delayOneButton, this, 0);
    delay1_module.addButton(&pitchOneButton, this, 1);
    delayTwoButton.setToggleState(audioProcessor.delayTwoEnable, juce::NotificationType::dontSendNotification);
    delay2_module.setNumButtons(5);
    delay2_module.addButton(&delayTwoButton, this, 0);
    delay2_module.addButton(&pitchTwoButton, this, 1);
    delayThreeButton.setToggleState(audioProcessor.delayThreeEnable, juce::NotificationType::dontSendNotification);
    delay3_module.setNumButtons(5);
    delay3_module.addButton(&delayThreeButton, this, 0);
    delay3_module.addButton(&pitchThreeButton, this, 1);
    delayFourButton.setToggleState(audioProcessor.delayFourEnable, juce::NotificationType::dontSendNotification);
    delay4_module.setNumButtons(5);
    delay4_module.addButton(&delayFourButton, this, 0);
    delay4_module.addButton(&pitchFourButton, this, 1);
    
    delay1_module.makeVisible(this);
    delay2_module.makeVisible(this);
    delay3_module.makeVisible(this);
    delay4_module.makeVisible(this);
    
}

JZDelayAudioProcessorEditor::~JZDelayAudioProcessorEditor()
{
}

//==============================================================================
void JZDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
}



void JZDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

}





void JZDelayAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of universal slider change
    
    if (slider == &inputGainSlider) {
        audioProcessor.inputGain = inputGainSlider.getValue();
    }
    else if (slider == &outputGainSlider) {
        audioProcessor.outputGain = outputGainSlider.getValue();
    }
    else if (slider == &dryMixSlider) {
        audioProcessor.dryMix = dryMixSlider.getValue();
    }
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of delay 1 slider change
    
    else if (slider == &delayTimeSlider) {
        audioProcessor.delayTime = delayTimeSlider.getValue();
        // if this slider is moved, reset echo parameters
        int tempNumSamples = ceil(.001 * delayTimeSlider.getValue() *
                                            audioProcessor.getSampleRate());
        if (tempNumSamples != audioProcessor.numSamples) {
            audioProcessor.numSamples = tempNumSamples;
            audioProcessor.readPosL = 1; //
            audioProcessor.writePosL = 0; // always write to 1 before read. both are incremented
            audioProcessor.readPosR = 1;
            audioProcessor.writePosR = 0;
        }
    }
    else if (slider == &decayRateSlider) {
        audioProcessor.decayRate = decayRateSlider.getValue();
    }
    else if (slider == &wetMixSlider) {
        audioProcessor.wetMix = wetMixSlider.getValue();
    }
    else if (slider == &panSlider) {
        audioProcessor.pan = panSlider.getValue();
    }
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of delay 2 slider change
    
    else if (slider == &delayTwoTimeSlider) {
        audioProcessor.delayTwoTime = delayTwoTimeSlider.getValue();
        // if this slider is moved, reset echo parameters
        int tempTwoNumSamples = ceil(.001 * delayTwoTimeSlider.getValue() *
                                            audioProcessor.getSampleRate());
        if (tempTwoNumSamples != audioProcessor.numTwoSamples) {
            audioProcessor.numTwoSamples = tempTwoNumSamples;
            audioProcessor.readTwoPosL = 1; //
            audioProcessor.writeTwoPosL = 0; // always write to 1 before read. both are incremented
            audioProcessor.readTwoPosR = 1;
            audioProcessor.writeTwoPosR = 0;
        }
    }
    else if (slider == &decayTwoRateSlider) {
        audioProcessor.decayTwoRate = decayTwoRateSlider.getValue();
    }
    else if (slider == &wetTwoMixSlider) {
        audioProcessor.wetTwoMix = wetTwoMixSlider.getValue();
    }
    else if (slider == &panTwoSlider) {
        audioProcessor.panTwo = panTwoSlider.getValue();
    }
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of delay 3 slider change
    
    else if (slider == &delayThreeTimeSlider) {
        audioProcessor.delayThreeTime = delayThreeTimeSlider.getValue();
        // if this slider is moved, reset echo parameters
        int tempThreeNumSamples = ceil(.001 * delayThreeTimeSlider.getValue() *
                                            audioProcessor.getSampleRate());
        if (tempThreeNumSamples != audioProcessor.numThreeSamples) {
            audioProcessor.numThreeSamples = tempThreeNumSamples;
            audioProcessor.readThreePosL = 1; //
            audioProcessor.writeThreePosL = 0; // always write to 1 before read. both are incremented
            audioProcessor.readThreePosR = 1;
            audioProcessor.writeThreePosR = 0;
        }
    }
    else if (slider == &decayThreeRateSlider) {
        audioProcessor.decayThreeRate = decayThreeRateSlider.getValue();
    }
    else if (slider == &wetThreeMixSlider) {
        audioProcessor.wetThreeMix = wetThreeMixSlider.getValue();
    }
    else if (slider == &panThreeSlider) {
        audioProcessor.panThree = panThreeSlider.getValue();
    }
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of delay 4 slider change
    
    else if (slider == &delayFourTimeSlider) {
        audioProcessor.delayFourTime = delayFourTimeSlider.getValue();
        // if this slider is moved, reset echo parameters
        int tempFourNumSamples = ceil(.001 * delayFourTimeSlider.getValue() *
                                            audioProcessor.getSampleRate());
        if (tempFourNumSamples != audioProcessor.numFourSamples) {
            audioProcessor.numFourSamples = tempFourNumSamples;
            audioProcessor.readFourPosL = 1; //
            audioProcessor.writeFourPosL = 0; // always write to 1 before read. both are incremented
            audioProcessor.readFourPosR = 1;
            audioProcessor.writeFourPosR = 0;
        }
    }
    else if (slider == &decayFourRateSlider) {
        audioProcessor.decayFourRate = decayFourRateSlider.getValue();
    }
    else if (slider == &wetFourMixSlider) {
        audioProcessor.wetFourMix = wetFourMixSlider.getValue();
    }
    else if (slider == &panFourSlider) {
        audioProcessor.panFour = panFourSlider.getValue();
    }
    
}



void JZDelayAudioProcessorEditor::buttonStateChanged(juce::Button *button)
{
    if (button == &delayOneButton)
    {
        // state is 2 when button is toggled
        // state is 1 when button is hovered
        // state is 0 otherwise
        if (delayOneButton.getState() == 2)
        {
            audioProcessor.delayOneEnable = !audioProcessor.delayOneEnable;
        }
    }
    else if (button == &delayTwoButton)
    {
        if (delayTwoButton.getState() == 2)
        {
            audioProcessor.delayTwoEnable = !audioProcessor.delayTwoEnable;
        }
    }
    else if (button == &delayThreeButton)
    {
        if (delayThreeButton.getState() == 2)
        {
            audioProcessor.delayThreeEnable = !audioProcessor.delayThreeEnable;
        }
    }
    else if (button == &delayFourButton)
    {
        if (delayFourButton.getState() == 2)
        {
            audioProcessor.delayFourEnable = !audioProcessor.delayFourEnable;
        }
    }
    
    //****************************************************************************//
    //****************************************************************************//
    
    
    else if (button == &pitchOneButton)
    {
        if (pitchOneButton.getState() == 2)
        {
            audioProcessor.pitchOneEnable = !audioProcessor.pitchOneEnable;
        }
    }
    
    else if (button == &pitchTwoButton)
    {
        if (pitchTwoButton.getState() == 2)
        {
            audioProcessor.pitchTwoEnable = !audioProcessor.pitchTwoEnable;
        }
    }
    
    else if (button == &pitchThreeButton)
    {
        if (pitchThreeButton.getState() == 2)
        {
            audioProcessor.pitchThreeEnable = !audioProcessor.pitchThreeEnable;
        }
    }
    
    else if (button == &pitchFourButton)
    {
        if (pitchFourButton.getState() == 2)
        {
            audioProcessor.pitchFourEnable = !audioProcessor.pitchFourEnable;
        }
    }
    
}


void JZDelayAudioProcessorEditor::buttonClicked(juce::Button *button) {

}
