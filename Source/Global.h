
#pragma once

#include <JuceHeader.h>
#include "JZLookAndFeel.h"

class Global
{
    public:
        Global() {};
        void setBoundaries(int startxx, int endxx, int startyy, int endyy);
        void setNumSliders(int numSliders);
    

        void addSlider(juce::Slider*, juce::Label*,
                   char const* name, int num, float start, float stop,
                   float step, float init_val, float doubclick_val,
                   juce::Slider::Listener*, JZLookAndFeel* lookandfeel);
        
        void makeVisible(juce::Component*);
    
    private:
        std::vector<juce::Slider*> sliderList;
        std::vector<juce::Label*> labelList;
    
        int numSliders;
        int startx, starty, endx, endy;
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Global);
};
