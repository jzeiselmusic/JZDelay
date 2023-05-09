/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JZDelayAudioProcessorEditor::JZDelayAudioProcessorEditor (JZDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 700);
    
    // parameters for universal control
    //**************************************************************************//
    //**************************************************************************//
    // pre-gain slider parameters
    inputGainSlider.setSliderSnapsToMousePosition(true);
    inputGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    inputGainSlider.setTitle("Input Gain");
    inputGainSlider.setRange(-24.0, 24.0, 0.01);
    inputGainSlider.setValue(0.0);
    inputGainSlider.setTextBoxIsEditable(false);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 35, 20);
    inputGainSlider.setDoubleClickReturnValue(true, 0.0, NULL);
    inputGainSlider.addListener(this);
    addAndMakeVisible(inputGainSlider);
    
    // post-gain slider parameters
    outputGainSlider.setSliderSnapsToMousePosition(true);
    outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    outputGainSlider.setTitle("Output Gain");
    outputGainSlider.setRange(-24.0, 24.0, 0.01);
    outputGainSlider.setValue(0.0);
    outputGainSlider.setTextBoxIsEditable(false);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 35, 20);
    outputGainSlider.setDoubleClickReturnValue(true, 0.0, NULL);
    outputGainSlider.addListener(this);
    addAndMakeVisible(outputGainSlider);
    
    // add labels to both gain sliders
    addAndMakeVisible (inputGainLabel);
    inputGainLabel.setText ("Input Gain", juce::dontSendNotification);
    inputGainLabel.attachToComponent (&inputGainSlider, false); //
    inputGainLabel.setJustificationType(juce::Justification::top);
    inputGainLabel.setMinimumHorizontalScale(0.5);
    
    addAndMakeVisible (outputGainLabel);
    outputGainLabel.setText ("Output Gain", juce::dontSendNotification);
    outputGainLabel.attachToComponent (&outputGainSlider, false); //
    outputGainLabel.setJustificationType(juce::Justification::centredTop);
    outputGainLabel.setMinimumHorizontalScale(0.5);
    
    // dry mix slider parameters
    dryMixSlider.setSliderSnapsToMousePosition(true);
    dryMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    dryMixSlider.setTitle("Dry Mix");
    dryMixSlider.setRange(0.0, 100.0, .1);
    dryMixSlider.setValue(100.0);
    dryMixSlider.setTextBoxIsEditable(true);
    dryMixSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 35, 20);
    dryMixSlider.setDoubleClickReturnValue(true, 100.0, NULL);
    dryMixSlider.addListener(this);
    addAndMakeVisible(dryMixSlider);
    
    // add label to dry mix slider
    addAndMakeVisible (dryMixLabel);
    dryMixLabel.setText ("Dry Mix", juce::dontSendNotification);
    dryMixLabel.attachToComponent (&dryMixSlider, false); //
    dryMixLabel.setJustificationType(juce::Justification::top);
    
    //**************************************************************************//
    //**************************************************************************//
    
    // parameters for delay 1 //
    
    addAndMakeVisible(delayOneButton);
    delayOneButton.addListener(this);
    
    // delay time slider parameters
    delayTimeSlider.setSliderSnapsToMousePosition(true);
    delayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTimeSlider.setTitle("Delay Time");
    delayTimeSlider.setRange(30.0, 150.0, 1);
    delayTimeSlider.setValue(70.0);
    delayTimeSlider.setTextBoxIsEditable(true);
    delayTimeSlider.setDoubleClickReturnValue(true, 70.0, NULL);
    delayTimeSlider.addListener(this);
    addAndMakeVisible(delayTimeSlider);
    
    // add label to delay time slider
    addAndMakeVisible (delayTimeLabel);
    delayTimeLabel.setText ("Delay Time (ms)", juce::dontSendNotification);
    delayTimeLabel.attachToComponent (&delayTimeSlider, false); //
    delayTimeLabel.setJustificationType(juce::Justification::topLeft);
    
    // decay rate slider parameters
    decayRateSlider.setSliderSnapsToMousePosition(true);
    decayRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    decayRateSlider.setTitle("Decay Rate");
    decayRateSlider.setRange(0.1, 0.9, .01);
    decayRateSlider.setValue(0.75);
    decayRateSlider.setTextBoxIsEditable(true);
    decayRateSlider.setDoubleClickReturnValue(true, 0.75, NULL);
    decayRateSlider.addListener(this);
    addAndMakeVisible(decayRateSlider);
    
    // add label to decay rate slider
    addAndMakeVisible (decayRateLabel);
    decayRateLabel.setText ("Decay Rate", juce::dontSendNotification);
    decayRateLabel.attachToComponent (&decayRateSlider, false); //
    decayRateLabel.setJustificationType(juce::Justification::topLeft);
    
    // wet mix slider parameters
    wetMixSlider.setSliderSnapsToMousePosition(true);
    wetMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wetMixSlider.setTitle("Wet Mix");
    wetMixSlider.setRange(0.0, 100.0, .1);
    wetMixSlider.setValue(50.0);
    wetMixSlider.setTextBoxIsEditable(true);
    wetMixSlider.setDoubleClickReturnValue(true, 50.0, NULL);
    wetMixSlider.addListener(this);
    addAndMakeVisible(wetMixSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (wetMixLabel);
    wetMixLabel.setText ("Wet Mix", juce::dontSendNotification);
    wetMixLabel.attachToComponent (&wetMixSlider, false); //
    wetMixLabel.setJustificationType(juce::Justification::topLeft);
    
    
    
    //**************************************************************************//
    //**************************************************************************//
    
    // parameters for delay 2 //
    
    addAndMakeVisible(delayTwoButton);
    delayTwoButton.addListener(this);
    
    // delay time slider parameters
    delayTwoTimeSlider.setSliderSnapsToMousePosition(true);
    delayTwoTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTwoTimeSlider.setTitle("Delay Time");
    delayTwoTimeSlider.setRange(30.0, 150.0, 1);
    delayTwoTimeSlider.setValue(70.0);
    delayTwoTimeSlider.setTextBoxIsEditable(true);
    delayTwoTimeSlider.setDoubleClickReturnValue(true, 70.0, NULL);
    delayTwoTimeSlider.addListener(this);
    addAndMakeVisible(delayTwoTimeSlider);
    
    // add label to delay time slider
    addAndMakeVisible (delayTwoTimeLabel);
    delayTwoTimeLabel.setText ("Delay Time (ms)", juce::dontSendNotification);
    delayTwoTimeLabel.attachToComponent (&delayTwoTimeSlider, false); //
    delayTwoTimeLabel.setJustificationType(juce::Justification::topLeft);
    
    // decay rate slider parameters
    decayTwoRateSlider.setSliderSnapsToMousePosition(true);
    decayTwoRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    decayTwoRateSlider.setTitle("Decay Rate");
    decayTwoRateSlider.setRange(0.1, 0.9, .01);
    decayTwoRateSlider.setValue(0.75);
    decayTwoRateSlider.setTextBoxIsEditable(true);
    decayTwoRateSlider.setDoubleClickReturnValue(true, 0.75, NULL);
    decayTwoRateSlider.addListener(this);
    addAndMakeVisible(decayTwoRateSlider);
    
    // add label to decay rate slider
    addAndMakeVisible (decayTwoRateLabel);
    decayTwoRateLabel.setText ("Decay Rate", juce::dontSendNotification);
    decayTwoRateLabel.attachToComponent (&decayTwoRateSlider, false); //
    decayTwoRateLabel.setJustificationType(juce::Justification::topLeft);
    
    // wet mix slider parameters
    wetTwoMixSlider.setSliderSnapsToMousePosition(true);
    wetTwoMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wetTwoMixSlider.setTitle("Wet Mix");
    wetTwoMixSlider.setRange(0.0, 100.0, .1);
    wetTwoMixSlider.setValue(50.0);
    wetTwoMixSlider.setTextBoxIsEditable(true);
    wetTwoMixSlider.setDoubleClickReturnValue(true, 50.0, NULL);
    wetTwoMixSlider.addListener(this);
    addAndMakeVisible(wetTwoMixSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (wetTwoMixLabel);
    wetTwoMixLabel.setText ("Wet Mix", juce::dontSendNotification);
    wetTwoMixLabel.attachToComponent (&wetTwoMixSlider, false); //
    wetTwoMixLabel.setJustificationType(juce::Justification::topLeft);
    
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
    auto sliderLeft = 30;
    
    // drawing boxes for universal parameters
    inputGainSlider.setBounds(sliderLeft, 55, 60, 400);
    outputGainSlider.setBounds(sliderLeft+60, 55, 60, 400);
    dryMixSlider.setBounds(sliderLeft+120, 55, 60, 400);
    
    // drawing boxes for delay 1 parameters
    delayOneButton.setBounds(230, 30, 20, 20);
    delayTimeSlider.setBounds(230, 80, 225, 20);
    decayRateSlider.setBounds(230, 130, 225, 20);
    wetMixSlider.setBounds(230, 180, 225, 20);
    
    // drawing boxes for delay 2 parameters
    
    delayTwoButton.setBounds(230, 230, 20, 20);
    delayTwoTimeSlider.setBounds(230, 280, 225, 20);
    decayTwoRateSlider.setBounds(230, 330, 225, 20);
    wetTwoMixSlider.setBounds(230, 380, 225, 20);
}


void JZDelayAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of universal slider change
    
    if (slider == &inputGainSlider) {
        audioProcessor.inputGain = pow(10, inputGainSlider.getValue() / 20.0);
    }
    else if (slider == &outputGainSlider) {
        audioProcessor.outputGain = pow(10, outputGainSlider.getValue() / 20.0);
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
    
    //****************************************************************************//
    //****************************************************************************//
    
    // in the case of delay 2 slider change
    
    else if (slider == &delayTwoTimeSlider) {
        audioProcessor.delayTwoTime = delayTwoTimeSlider.getValue();
        // if this slider is moved, reset echo parameters
        int tempTwoNumSamples = ceil(.001 * delayTwoTimeSlider.getValue() *
                                            audioProcessor.getSampleRate());
        if (tempTwoNumSamples != audioProcessor.numSamples) {
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
    
}

void JZDelayAudioProcessorEditor::buttonStateChanged(juce::Button *button) {
    if (button == &delayOneButton) {
        // state is 2 when button is toggled
        // state is 1 when button is hovered
        // state is 0 otherwise
        if (delayOneButton.getState() == 2) {
            audioProcessor.delayOneEnable = !audioProcessor.delayOneEnable;
        }
    }
    else if (button == &delayTwoButton) {
        if (delayTwoButton.getState() == 2) {
            audioProcessor.delayTwoEnable = !audioProcessor.delayTwoEnable;
        }
    }
}


void JZDelayAudioProcessorEditor::buttonClicked(juce::Button *button) {

}
