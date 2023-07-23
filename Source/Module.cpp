
#include "Module.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JZLookAndFeel.h"

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

void Module::setNumButtons(int num)
{
    numButtons = num;
}

void Module::setEffectName(char const* name)
{
    effectName = name;
}

void Module::addSlider(juce::Slider* newSlider, juce::Label* newLabel,
                       char const* name, int num,
                       float start, float stop,
                       float step, float init_val, float doubclick_val,
                       juce::Slider::Listener* sliderL,
                       JZLookAndFeel* lookandfeel)
{
    int width = endy - starty;
    int step_y = width / (numSliders+1);
    // set parameters for this slider
    newSlider->setSliderSnapsToMousePosition(true);
    newSlider->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    newSlider->setTitle(name);
    
    newSlider->setRange(start, stop, step);
    newSlider->setValue(init_val);
    
    newSlider->setTextBoxIsEditable(false);
    newSlider->setDoubleClickReturnValue(true, doubclick_val, NULL);
    newSlider->addListener(sliderL);
    
    newSlider->setLookAndFeel(lookandfeel);
    
    newSlider->setBounds(startx, starty + ((num+1)*step_y), endx - startx, 20);
    
    // add a label with same name and attach
    newLabel->setText (name, juce::dontSendNotification);
    newLabel->attachToComponent (newSlider, false); //
    newLabel->setJustificationType(juce::Justification::topLeft);
    
    // add slider to our slider list
    sliderList.push_back(newSlider);
    // add label to our label list
    labelList.push_back(newLabel);
}


void Module::addButton(juce::ToggleButton* button, juce::Button::Listener* buttonL, int num)
{
    int width = endx - startx;
    int step_x = width / numButtons;
    button->setBounds(startx + (num*step_x), starty, 20, 20);
    button->addListener(buttonL);
    buttonList.push_back(button);
}

void Module::makeVisible(juce::Component* component) {
    
    for (int i = 0; i < sliderList.size(); ++i)
    {
        component->addAndMakeVisible(sliderList[i]);
    }
    for (int i = 0; i < buttonList.size(); ++i)
    {
        component->addAndMakeVisible(buttonList[i]);
    }
}

void Module::valuesChanged(juce::Slider::Listener* sliderL)
{
    for (int i = 0; i < sliderList.size(); ++i)
    {
        sliderL->sliderValueChanged(sliderList[i]);
    }
}

