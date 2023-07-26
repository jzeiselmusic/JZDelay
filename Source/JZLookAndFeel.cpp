/*
  ==============================================================================

    JZLookAndFeel.cpp
    Created: 26 Jul 2023 8:58:34am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "JZLookAndFeel.h"
#include "JuceHeader.h"

using namespace juce;

JZLookAndFeel::JZLookAndFeel() {
    /* get the current working directory */
    File imageFile = getImage();
    /* put image into private slider_img variable */
    slider_img = ImageCache::getFromFile(imageFile);
    
    /* this value might change based on the image */
    num_sliders = 40;
}

File JZLookAndFeel::getImage() const
{
    /* get location of executable */
    auto start = juce::File::getSpecialLocation (juce::File::currentExecutableFile);
    /* search recursively backwards for source files */
    while (start.exists() && !start.isRoot() && start.getFileName() != "Builds")
        start = start.getParentDirectory();
    
    if (start.getFileName() == "Builds")
    {
        auto sources = start.getSiblingFile ("Source");
        if (sources.isDirectory())
        {
            return sources.getChildFile("sliders_total.png");
        }
        else
            throw std::domain_error("sources not found");
    }
    else
        throw std::domain_error("builds not found");
}

void JZLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider& slider) {
    
    if (slider_img.isValid())
    {
        /* get the current slider amount as a percentage of total possible */
        const double slider_amount = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
        
        const double frame_width = (double)slider_img.getWidth() / (double)num_sliders;
        const double frame = (double)slider_img.getWidth() * slider_amount;
        
        const double divide = frame / frame_width;
        /* this value will be a decimal. We want to find the nearest integer and then multiply by frame_width */
        int starting_x = (int)divide * (int)frame_width;
        
        g.drawImage(slider_img,
                    x,
                    y,
                    width,
                    height,
                    starting_x,
                    0,
                    (int)frame_width,
                    slider_img.getHeight(),
                    false);
    }
    else
    {
        throw std::domain_error("slider image not a valid image");
    }
    
};
