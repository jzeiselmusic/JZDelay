/*
  ==============================================================================

    Filter.h
    Created: 9 Jun 2023 3:45:37pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

class Filter {
    
public:
    
    // constructor and destructor
    Filter(bool isLowPass, float freqCutoff, int order, int samplingRate);
    ~Filter(void);
    
    void filterBuffer(float* buffer, int numSamples);
    
private:
    
    float type; // 1 for lowpass, -1 for highpass
    float freqCutoff;
    int order;
    int samplingRate;
    float a1;
};
