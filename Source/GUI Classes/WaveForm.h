/*
  ==============================================================================

    WaveForm.h
    Created: 18 Apr 2020 2:23:23pm
    Author:  Christian Sager

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Waveform    : public Component

{
public:
    //===============================================================================================
    Waveform()
    {
            for (int i =0; i<1000;i++){ch_array [i] = 0;}
            for (int i = 0; i < 1000; i++) { gainreduct_array[i] = 0; }
    }

    void addSample(int sample);
    void addGainreduct(int sample);
    void update();
    void colour(int colorID);
    void threshold(float threshold);
    void clearWaveform();
    void side(int side);
    
    void paint (Graphics& g) override;
    
private:
    //===============================================================================================

    //===============================================================================================
    int ch_array[1000];
    int gainreduct_array[1000];
    int gainreduct = 0;
    int left = 0;
    Colour color = Colours::grey;
    float threshold_value = 0;
};
