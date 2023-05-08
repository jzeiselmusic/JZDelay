/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class JZDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener
{
public:
    JZDelayAudioProcessorEditor (JZDelayAudioProcessor&);
    ~JZDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider *slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JZDelayAudioProcessor& audioProcessor;
    
    juce::Slider inputGainSlider;
    juce::Slider outputGainSlider;
    juce::Label inputGainLabel;
    juce::Label outputGainLabel;
    
    juce::Slider delayTimeSlider;
    juce::Label delayTimeLabel;
    
    juce::Slider decayRateSlider;
    juce::Label decayRateLabel;
    
    juce::Slider wetMixSlider;
    juce::Label wetMixLabel;
    
    juce::Slider dryMixSlider;
    juce::Label dryMixLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JZDelayAudioProcessorEditor)
};
