/*
  ==============================================================================

    WaveForm.cpp
    Created: 18 Apr 2020 2:23:23pm
    Author:  Christian Sager

  ==============================================================================
*/

#include "WaveForm.h"


void Waveform::addSample(int sample){
    
    for (int i =0; i<500;i++)
    {
        ch_array [i] = ch_array [i+1]; // Increment the ringbuffer by 1
        
    }
        ch_array [499] = sample; // Add new element at the end of the ringbuffer
    repaint();
}

/*Update the graph*/
void Waveform::update(){
   repaint();
}

/*Draw the graph with paint method in component*/
void Waveform::paint (Graphics& g){

        int middlepoint=50;
        int xPosition = 0;
           
    g.fillAll (Colours::grey);

    g.setColour (Colours::orange);
        for(int i = 0; i<500; i++){
            g.fillRect (i+xPosition, middlepoint - (ch_array [i]/2), 1,  ch_array [i]+1);
     }
    g.fillRect (501,100-ch_array [499],510,ch_array [499]);
}

