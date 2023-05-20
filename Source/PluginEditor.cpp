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
    setSize (750, 600);
    
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
    delayTimeSlider.setRange(30.0, 2000.0, 1);
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
    decayRateSlider.setRange(0.01, 0.99, .01);
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
    
    // pan slider parameters
    panSlider.setSliderSnapsToMousePosition(true);
    panSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    panSlider.setTitle("Pan");
    panSlider.setRange(-100.0, 100.0, 0.1);
    panSlider.setValue(0.0);
    panSlider.setTextBoxIsEditable(true);
    panSlider.setDoubleClickReturnValue(true, 0.0, NULL);
    panSlider.addListener(this);
    addAndMakeVisible(panSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (panLabel);
    panLabel.setText ("Pan", juce::dontSendNotification);
    panLabel.attachToComponent (&panSlider, false); //
    panLabel.setJustificationType(juce::Justification::topLeft);
    
    
    //**************************************************************************//
    //**************************************************************************//
    
    // parameters for delay 2 //
    
    addAndMakeVisible(delayTwoButton);
    delayTwoButton.addListener(this);
    
    // delay time slider parameters
    delayTwoTimeSlider.setSliderSnapsToMousePosition(true);
    delayTwoTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayTwoTimeSlider.setTitle("Delay Time");
    delayTwoTimeSlider.setRange(30.0, 2000.0, 1);
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
    decayTwoRateSlider.setRange(0.01, 0.99, .01);
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
    
    // pan slider parameters
    panTwoSlider.setSliderSnapsToMousePosition(true);
    panTwoSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    panTwoSlider.setTitle("Pan");
    panTwoSlider.setRange(-100.0, 100.0, .1);
    panTwoSlider.setValue(0.0);
    panTwoSlider.setTextBoxIsEditable(true);
    panTwoSlider.setDoubleClickReturnValue(true, 0.0, NULL);
    panTwoSlider.addListener(this);
    addAndMakeVisible(panTwoSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (panTwoLabel);
    panTwoLabel.setText ("Pan", juce::dontSendNotification);
    panTwoLabel.attachToComponent (&panTwoSlider, false); //
    panTwoLabel.setJustificationType(juce::Justification::topLeft);
    
    
    
    //**************************************************************************//
    //**************************************************************************//
    
    // parameters for delay 3 //
    
    addAndMakeVisible(delayThreeButton);
    delayThreeButton.addListener(this);
    
    // delay time slider parameters
    delayThreeTimeSlider.setSliderSnapsToMousePosition(true);
    delayThreeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayThreeTimeSlider.setTitle("Delay Time");
    delayThreeTimeSlider.setRange(30.0, 2000.0, 1);
    delayThreeTimeSlider.setValue(70.0);
    delayThreeTimeSlider.setTextBoxIsEditable(true);
    delayThreeTimeSlider.setDoubleClickReturnValue(true, 70.0, NULL);
    delayThreeTimeSlider.addListener(this);
    addAndMakeVisible(delayThreeTimeSlider);
    
    // add label to delay time slider
    addAndMakeVisible (delayThreeTimeLabel);
    delayThreeTimeLabel.setText ("Delay Time (ms)", juce::dontSendNotification);
    delayThreeTimeLabel.attachToComponent (&delayThreeTimeSlider, false); //
    delayThreeTimeLabel.setJustificationType(juce::Justification::topLeft);
    
    // decay rate slider parameters
    decayThreeRateSlider.setSliderSnapsToMousePosition(true);
    decayThreeRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    decayThreeRateSlider.setTitle("Decay Rate");
    decayThreeRateSlider.setRange(0.01, 0.99, .01);
    decayThreeRateSlider.setValue(0.75);
    decayThreeRateSlider.setTextBoxIsEditable(true);
    decayThreeRateSlider.setDoubleClickReturnValue(true, 0.75, NULL);
    decayThreeRateSlider.addListener(this);
    addAndMakeVisible(decayThreeRateSlider);
    
    // add label to decay rate slider
    addAndMakeVisible (decayThreeRateLabel);
    decayThreeRateLabel.setText ("Decay Rate", juce::dontSendNotification);
    decayThreeRateLabel.attachToComponent (&decayThreeRateSlider, false); //
    decayThreeRateLabel.setJustificationType(juce::Justification::topLeft);
    
    // wet mix slider parameters
    wetThreeMixSlider.setSliderSnapsToMousePosition(true);
    wetThreeMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wetThreeMixSlider.setTitle("Wet Mix");
    wetThreeMixSlider.setRange(0.0, 100.0, .1);
    wetThreeMixSlider.setValue(50.0);
    wetThreeMixSlider.setTextBoxIsEditable(true);
    wetThreeMixSlider.setDoubleClickReturnValue(true, 50.0, NULL);
    wetThreeMixSlider.addListener(this);
    addAndMakeVisible(wetThreeMixSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (wetThreeMixLabel);
    wetThreeMixLabel.setText ("Wet Mix", juce::dontSendNotification);
    wetThreeMixLabel.attachToComponent (&wetThreeMixSlider, false); //
    wetThreeMixLabel.setJustificationType(juce::Justification::topLeft);
    
    // pan slider parameters
    panThreeSlider.setSliderSnapsToMousePosition(true);
    panThreeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    panThreeSlider.setTitle("Pan");
    panThreeSlider.setRange(-100.0, 100.0, 0.1);
    panThreeSlider.setValue(0.5);
    panThreeSlider.setTextBoxIsEditable(true);
    panThreeSlider.setDoubleClickReturnValue(true, 0.0, NULL);
    panThreeSlider.addListener(this);
    addAndMakeVisible(panThreeSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (panThreeLabel);
    panThreeLabel.setText ("Pan", juce::dontSendNotification);
    panThreeLabel.attachToComponent (&panThreeSlider, false); //
    panThreeLabel.setJustificationType(juce::Justification::topLeft);
    
    
    //**************************************************************************//
    //**************************************************************************//
    
    // parameters for delay 4 //
    
    addAndMakeVisible(delayFourButton);
    delayFourButton.addListener(this);
    
    // delay time slider parameters
    delayFourTimeSlider.setSliderSnapsToMousePosition(true);
    delayFourTimeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    delayFourTimeSlider.setTitle("Delay Time");
    delayFourTimeSlider.setRange(30.0, 2000.0, 1);
    delayFourTimeSlider.setValue(70.0);
    delayFourTimeSlider.setTextBoxIsEditable(true);
    delayFourTimeSlider.setDoubleClickReturnValue(true, 70.0, NULL);
    delayFourTimeSlider.addListener(this);
    addAndMakeVisible(delayFourTimeSlider);
    
    // add label to delay time slider
    addAndMakeVisible (delayFourTimeLabel);
    delayFourTimeLabel.setText ("Delay Time (ms)", juce::dontSendNotification);
    delayFourTimeLabel.attachToComponent (&delayFourTimeSlider, false); //
    delayFourTimeLabel.setJustificationType(juce::Justification::topLeft);
    
    // decay rate slider parameters
    decayFourRateSlider.setSliderSnapsToMousePosition(true);
    decayFourRateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    decayFourRateSlider.setTitle("Decay Rate");
    decayFourRateSlider.setRange(0.01, 0.99, .01);
    decayFourRateSlider.setValue(0.75);
    decayFourRateSlider.setTextBoxIsEditable(true);
    decayFourRateSlider.setDoubleClickReturnValue(true, 0.75, NULL);
    decayFourRateSlider.addListener(this);
    addAndMakeVisible(decayFourRateSlider);
    
    // add label to decay rate slider
    addAndMakeVisible (decayFourRateLabel);
    decayFourRateLabel.setText ("Decay Rate", juce::dontSendNotification);
    decayFourRateLabel.attachToComponent (&decayFourRateSlider, false); //
    decayFourRateLabel.setJustificationType(juce::Justification::topLeft);
    
    // wet mix slider parameters
    wetFourMixSlider.setSliderSnapsToMousePosition(true);
    wetFourMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    wetFourMixSlider.setTitle("Wet Mix");
    wetFourMixSlider.setRange(0.0, 100.0, .1);
    wetFourMixSlider.setValue(50.0);
    wetFourMixSlider.setTextBoxIsEditable(true);
    wetFourMixSlider.setDoubleClickReturnValue(true, 50.0, NULL);
    wetFourMixSlider.addListener(this);
    addAndMakeVisible(wetFourMixSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (wetFourMixLabel);
    wetFourMixLabel.setText ("Wet Mix", juce::dontSendNotification);
    wetFourMixLabel.attachToComponent (&wetFourMixSlider, false); //
    wetFourMixLabel.setJustificationType(juce::Justification::topLeft);
    
    
    // pan slider parameters
    panFourSlider.setSliderSnapsToMousePosition(true);
    panFourSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    panFourSlider.setTitle("Pan");
    panFourSlider.setRange(-100.0, 100.0, 0.1);
    panFourSlider.setValue(0.5);
    panFourSlider.setTextBoxIsEditable(true);
    panFourSlider.setDoubleClickReturnValue(true, 0.0, NULL);
    panFourSlider.addListener(this);
    addAndMakeVisible(panFourSlider);
    
    // add label to wet mix slider
    addAndMakeVisible (panFourLabel);
    panFourLabel.setText ("Pan", juce::dontSendNotification);
    panFourLabel.attachToComponent (&panFourSlider, false); //
    panFourLabel.setJustificationType(juce::Justification::topLeft);
    
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
    inputGainSlider.setBounds(sliderLeft, 55, 60, 340);
    outputGainSlider.setBounds(sliderLeft+60, 55, 60, 340);
    dryMixSlider.setBounds(sliderLeft+120, 55, 60, 340);
    
    // drawing boxes for delay 1 parameters
    delayOneButton.setBounds(230, 30, 20, 20);
    delayTimeSlider.setBounds(230, 80, 225, 20);
    decayRateSlider.setBounds(230, 130, 225, 20);
    wetMixSlider.setBounds(230, 180, 225, 20);
    panSlider.setBounds(230, 230, 225, 20);
    
    // drawing boxes for delay 2 parameters
    
    delayTwoButton.setBounds(230, 310, 20, 20);
    delayTwoTimeSlider.setBounds(230, 360, 225, 20);
    decayTwoRateSlider.setBounds(230, 410, 225, 20);
    wetTwoMixSlider.setBounds(230, 460, 225, 20);
    panTwoSlider.setBounds(230, 510, 225, 20);
    
    // drawing boxes for delay 3 parameters
    
    delayThreeButton.setBounds(480, 30, 20, 20);
    delayThreeTimeSlider.setBounds(480, 80, 225, 20);
    decayThreeRateSlider.setBounds(480, 130, 225, 20);
    wetThreeMixSlider.setBounds(480, 180, 225, 20);
    panThreeSlider.setBounds(480, 230, 225, 20);
    
    // drawing boxes for delay 4 parameters
    
    delayFourButton.setBounds(480, 410, 20, 20);
    delayFourTimeSlider.setBounds(480, 360, 225, 20);
    decayFourRateSlider.setBounds(480, 410, 225, 20);
    wetFourMixSlider.setBounds(480, 460, 225, 20);
    panFourSlider.setBounds(480, 510, 225, 20);
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
    else if (button == &delayThreeButton) {
        if (delayThreeButton.getState() == 2) {
            audioProcessor.delayThreeEnable = !audioProcessor.delayThreeEnable;
        }
    }
    else if (button == &delayFourButton) {
        if (delayFourButton.getState() == 2) {
            audioProcessor.delayFourEnable = !audioProcessor.delayFourEnable;
        }
    }
}


void JZDelayAudioProcessorEditor::buttonClicked(juce::Button *button) {

}
