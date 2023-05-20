/*
  ==============================================================================

    Module.cpp
    Created: 19 May 2023 7:36:30pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Module.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"


void Module::setBoundaries(int startxx, int endxx, int startyy, int endyy)
{
    startx = startxx;
    endx = endxx;
    starty = startyy;
    endy = endyy;
}

void Module::setNumSliders(int num)
{
    numSliders = num;
}

void Module::setEffectName(char const* name)
{
    effectName = name;
}

void Module::addSlider(char const* name, int num,
                       float start, float stop,
                       float step, float init_val,
                       juce::Slider::Listener* sliderL,
                       juce::Button::Listener* buttonL)
{
    int width = endy - starty;
    int step_y = width / (numSliders+1);
    // set parameters for this slider
    juce::Slider* newSlider = new juce::Slider;
    newSlider->setSliderSnapsToMousePosition(true);
    newSlider->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    newSlider->setTitle(name);
    
    newSlider->setRange(start, stop, step);
    newSlider->setValue(init_val);
    
    newSlider->setTextBoxIsEditable(false);
    newSlider->setDoubleClickReturnValue(true, init_val, NULL);
    newSlider->addListener(sliderL);
    
    newSlider->setBounds(startx, starty + ((num+1)*step_y), endx - startx, 20);
    
    // add a label with same name and attach
    juce::Label* newLabel = new juce::Label;
    newLabel->setText (name, juce::dontSendNotification);
    newLabel->attachToComponent (newSlider, false); //
    newLabel->setJustificationType(juce::Justification::topLeft);
    
    // add a button and add to button list
    juce::ToggleButton* newButton = new juce::ToggleButton;
    newButton->setBounds(startx, starty, 20, 20);
    newButton->addListener(buttonL);
    
    // add slider to our slider list
    sliderList.push_back(newSlider);
    // add label to our label list
    labelList.push_back(newLabel);
    // add button to button list
    buttonList.push_back(newButton);
}

void Module::makeVisible(juce::Component* component) {
    
    for (int i = 0; i < numSliders; ++i)
    {
        component->addAndMakeVisible(sliderList[i]);
        component->addAndMakeVisible(buttonList[i]);
    }
}
