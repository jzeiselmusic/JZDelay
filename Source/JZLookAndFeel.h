
#pragma once

#include "JuceHeader.h"

using namespace juce;

class JZLookAndFeel : public LookAndFeel_V4
{
public:
    JZLookAndFeel()
    {
        setColourScheme(getLightColourScheme());
        
    }
private:
};

