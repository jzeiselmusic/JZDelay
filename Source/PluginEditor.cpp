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
    setSize (500, 350);
    
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
    
    addAndMakeVisible(delayOneButton);
    delayOneButton.addListener(this);
    
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
    inputGainSlider.setBounds(sliderLeft, 55, 60, 250);
    outputGainSlider.setBounds(sliderLeft+60, 55, 60, 250);
    dryMixSlider.setBounds(sliderLeft+120, 55, 60, 250);
    
    delayOneButton.setBounds(230, 30, 20, 20);
    
    delayTimeSlider.setBounds(230, 80, 225, 20);
    decayRateSlider.setBounds(230, 130, 225, 20);
    wetMixSlider.setBounds(230, 180, 225, 20);
}


void JZDelayAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    
    if (slider == &inputGainSlider) {
        audioProcessor.inputGain = pow(10, inputGainSlider.getValue() / 20.0);
    }
    else if (slider == &outputGainSlider) {
        audioProcessor.outputGain = pow(10, outputGainSlider.getValue() / 20.0);
    }
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
    else if (slider == &dryMixSlider) {
        audioProcessor.dryMix = dryMixSlider.getValue();
    }
    
}

void JZDelayAudioProcessorEditor::buttonStateChanged(juce::Button *button) {
    printf("state is %d\n", delayOneButton.getState());
    if (button == &delayOneButton) {
        if (delayOneButton.getState() == 2) {
            audioProcessor.delayOneEnable = !audioProcessor.delayOneEnable;
        }
    }
}


void JZDelayAudioProcessorEditor::buttonClicked(juce::Button *button) {

}
