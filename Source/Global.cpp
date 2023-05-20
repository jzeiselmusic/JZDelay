/*
  ==============================================================================

    Global.cpp
    Created: 20 May 2023 11:54:32am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Global.h"

void Global::setBoundaries(int startxx, int endxx, int startyy, int endyy)
{
    startx = startxx;
    endx = endxx;
    starty = startyy;
    endy = endyy;
}

void Global::setNumSliders(int num)
{
    numSliders = num;
}


void Global::addSlider(juce::Slider* newSlider, juce::Label* newLabel,
                       char const* name, int num,
                       float start, float stop,
                       float step, float init_val, float doubclick_val,
                       juce::Slider::Listener* sliderL)
{
    int width = endx - startx;
    int step_x = width / numSliders;
    
    newSlider->setSliderSnapsToMousePosition(true);
    newSlider->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    newSlider->setTitle(name);
    newSlider->setRange(start, stop, step);
    newSlider->setValue(init_val);
    newSlider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 35, 20);
    newSlider->setDoubleClickReturnValue(true, doubclick_val, NULL);
    newSlider->addListener(sliderL);
    
    newSlider->setBounds(startx + num*step_x, starty, 60, endy-starty);
    
    newLabel->setText (name, juce::dontSendNotification);
    newLabel->attachToComponent (newSlider, false);
    newLabel->setJustificationType(juce::Justification::top);
    newLabel->setMinimumHorizontalScale(0.5);
    
    sliderList.push_back(newSlider);
    labelList.push_back(newLabel);
}


void Global::makeVisible(juce::Component* component) {
    
    for (int i = 0; i < sliderList.size(); ++i)
    {
        component->addAndMakeVisible(sliderList[i]);
    }
}
