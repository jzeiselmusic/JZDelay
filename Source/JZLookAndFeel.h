
#pragma once

#include "JuceHeader.h"

using namespace juce;

class JZLookAndFeel : public LookAndFeel_V4
{
public:
    JZLookAndFeel();
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider& slider) override;
    
    File getImage(void) const;
    
private:
    Image slider_img;
    int num_sliders;
};

