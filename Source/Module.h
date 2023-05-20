/*
  ==============================================================================

    Module.h
    Created: 19 May 2023 7:36:38pm
    Author:  Jacob Zeisel

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

class Module
{
    public:
        Module() {};
        // setters
        void setBoundaries(int startxx, int endxx, int startyy, int endyy);
        void setNumSliders(int numSliders);
        void setNumButtons(int numButtons);
        void setEffectName(char const*);
        
        // adders
        void addSlider(juce::Slider*, juce::Label*,
                       char const* name, int num, float start, float stop,
                       float step, float init_val, float doubclick_val,
                       juce::Slider::Listener*);
    
        void addButton(juce::ToggleButton*, juce::Button::Listener*, int num);
    
        // init
        void makeVisible(juce::Component* comp);
    
        void valuesChanged(juce::Slider::Listener*);
        
    
    private:
    
        std::vector<juce::Slider*> sliderList;
        std::vector<juce::Label*> labelList;
        std::vector<juce::Button*> buttonList;
        
        int numSliders, numButtons;
        char const* effectName;
        int startx, starty, endx, endy;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Module);
    
};
