/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "XyPad.h"

//==============================================================================
/**
*/
class JZDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener,
                                        public juce::Button::Listener
{
public:
    JZDelayAudioProcessorEditor (JZDelayAudioProcessor&);
    ~JZDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider *slider) override;
    void buttonStateChanged(juce::Button *button) override;
    void buttonClicked(juce::Button *button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JZDelayAudioProcessor& audioProcessor;
    
    // objects for universal parameters
    juce::Slider inputGainSlider;
    juce::Slider outputGainSlider;
    juce::Label inputGainLabel;
    juce::Label outputGainLabel;
    juce::Slider dryMixSlider;
    juce::Label dryMixLabel;
    // xypad
    Gui::XyPad xypad;
    
    // objects for delay 1
    juce::ToggleButton delayOneButton;
    juce::Slider delayTimeSlider;
    juce::Label delayTimeLabel;
    juce::Slider decayRateSlider;
    juce::Label decayRateLabel;
    juce::Slider wetMixSlider;
    juce::Label wetMixLabel;
    
    // objects for delay 2
    juce::ToggleButton delayTwoButton;
    juce::Slider delayTwoTimeSlider;
    juce::Label delayTwoTimeLabel;
    juce::Slider decayTwoRateSlider;
    juce::Label decayTwoRateLabel;
    juce::Slider wetTwoMixSlider;
    juce::Label wetTwoMixLabel;
    
    //objects for delay 3
    juce::ToggleButton delayThreeButton;
    juce::Slider delayThreeTimeSlider;
    juce::Label delayThreeTimeLabel;
    juce::Slider decayThreeRateSlider;
    juce::Label decayThreeRateLabel;
    juce::Slider wetThreeMixSlider;
    juce::Label wetThreeMixLabel;
    
    //objects for delay 4
    juce::ToggleButton delayFourButton;
    juce::Slider delayFourTimeSlider;
    juce::Label delayFourTimeLabel;
    juce::Slider decayFourRateSlider;
    juce::Label decayFourRateLabel;
    juce::Slider wetFourMixSlider;
    juce::Label wetFourMixLabel;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JZDelayAudioProcessorEditor)
};
