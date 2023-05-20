/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Module.h"

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
    
    Module delay1_module = Module();
    delay1_module.setEffectName("Delay 1");
    delay1_module.setNumSliders(4);
    delay1_module.setBoundaries(230, 455, 30, 300);
    delay1_module.addSlider(&delayTimeSlider, &delayTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, 100.0, this);
    delay1_module.addSlider(&decayRateSlider, &decayRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, 0.75, this);
    delay1_module.addSlider(&wetMixSlider, &wetMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, 50.0, this);
    delay1_module.addSlider(&panSlider, &panLabel, "Pan", 3, -100.0, 100.0, 0.1, 0.0, this);
    
    Module delay2_module = Module();
    delay2_module.setEffectName("Delay 2");
    delay2_module.setNumSliders(4);
    delay2_module.setBoundaries(230, 455, 310, 580);
    delay2_module.addSlider(&delayTwoTimeSlider, &delayTwoTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, 100.0, this);
    delay2_module.addSlider(&decayTwoRateSlider, &decayTwoRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, 0.75, this);
    delay2_module.addSlider(&wetTwoMixSlider, &wetTwoMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, 50.0, this);
    delay2_module.addSlider(&panTwoSlider, &panTwoLabel, "Pan", 3, -100.0, 100.0, 0.1, 0.0, this);
    
    Module delay3_module = Module();
    delay3_module.setEffectName("Delay 3");
    delay3_module.setNumSliders(4);
    delay3_module.setBoundaries(480, 735, 30, 300);
    delay3_module.addSlider(&delayThreeTimeSlider, &delayThreeTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, 100.0, this);
    delay3_module.addSlider(&decayThreeRateSlider, &decayThreeRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, 0.75, this);
    delay3_module.addSlider(&wetThreeMixSlider, &wetThreeMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, 50.0, this);
    delay3_module.addSlider(&panThreeSlider, &panThreeLabel, "Pan", 3, -100.0, 100.0, 0.1, 0.0, this);
    
    Module delay4_module = Module();
    delay4_module.setEffectName("Delay 4");
    delay4_module.setNumSliders(4);
    delay4_module.setBoundaries(480, 735, 310, 580);
    delay4_module.addSlider(&delayFourTimeSlider, &delayFourTimeLabel, "Delay Time", 0, 30.0, 2000.0, 1.0, 100.0, this);
    delay4_module.addSlider(&decayFourRateSlider, &decayFourRateLabel, "Decay Rate", 1, 0.01, 0.99, 0.01, 0.75, this);
    delay4_module.addSlider(&wetFourMixSlider, &wetFourMixLabel, "Wet Mix", 2, 0.0, 100.0, 0.1, 50.0, this);
    delay4_module.addSlider(&panFourSlider, &panFourLabel, "Pan", 3, -100.0, 100.0, 0.1, 0.0, this);
    
    delay1_module.addButton(&delayOneButton, this);
    delay2_module.addButton(&delayTwoButton, this);
    delay3_module.addButton(&delayThreeButton, this);
    delay4_module.addButton(&delayFourButton, this);
    
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
    auto sliderLeft = 30;
    
    // drawing boxes for universal parameters
    inputGainSlider.setBounds(sliderLeft, 55, 60, 340);
    outputGainSlider.setBounds(sliderLeft+60, 55, 60, 340);
    dryMixSlider.setBounds(sliderLeft+120, 55, 60, 340);

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
