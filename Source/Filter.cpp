/*
  ==============================================================================

    Filter.cpp
    Created: 9 Jun 2023 3:45:32pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Filter.h"
#include <math.h>
#include <string.h>

Filter::Filter(bool isLowPass, float freqCutoff, int order, int samplingRate)
{
    
    this->type = isLowPass == 1 ? 1 : -1; // 1 for lowpass, -1 for highpass
    this->freqCutoff = freqCutoff;
    this->order = order;
    this->samplingRate = samplingRate;
    
    float alpha = tan((float)M_PI * freqCutoff / samplingRate);
    this->a1 = (alpha - 1) / (alpha + 1);
}

Filter::~Filter()
{
}

void Filter::filterBuffer(float* buffer, int numSamples)
{
    float xh = 0;
    float xh_new;
    float ap_y;
    float temp;
    
    for (int i = 0; i < this->order; ++i)
    {
        for (int k = 0; k < numSamples; ++k)
        {
            temp = buffer[k];
            xh_new = temp - this->a1*xh;
            ap_y = this->a1 * xh_new + xh;
            xh = xh_new;
            buffer[k] = 0.5 * (temp + this->type*ap_y);
        }
    }
}
