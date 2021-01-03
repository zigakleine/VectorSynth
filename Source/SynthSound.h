/*
  ==============================================================================

    SynthSound.h
    Created: 5 Dec 2020 10:16:28pm
    Author:  Kleine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscillatorVoice.h"


class SynthSound : public SynthesiserSound
{

public:

    SynthSound() {


        volumeX = 0.5f;
        volumeY = 0.5f;
    }


    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }

    bool appliesToChannel(int midiNoteNumber) override
    {
        return true;
    }

    double getWaveSize(int index1, int index2)  const noexcept
    {
        return oscillatorVoices[index1].getWaveSize(index2);
    }

    void setWaveSize(double newWaveSize, int index1, int index2)
    {
        oscillatorVoices[index1].setWaveSize(newWaveSize, index2);
    }

    int getWaveRepeats(int index1, int index2)  const noexcept
    {
        return oscillatorVoices[index1].getWaveRepeats(index2);
    }

    void setWaveRepeats(int newWaveRepeats, int index1, int index2)
    {
        oscillatorVoices[index1].setWaveRepeats(newWaveRepeats, index2);
    }

    Array<float> getWave(int index1, int index2) const noexcept
    {
        return oscillatorVoices[index1].getWave(index2);
    }

    void setWave(Array<float> newWave, int index1, int index2)
    {
        oscillatorVoices[index1].setWave(newWave, index2);
    }

    ADSR::Parameters getAdsrParams(int index) const noexcept
    {
        return oscillatorVoices[index].getAdsrParams();
    }

    void setAdsrParams(ADSR::Parameters newAdsrParams, int index)
    {
        oscillatorVoices[index].setAdsrParams(newAdsrParams);
    }


    int getWaveNum(int index1, int index2)  const noexcept
    {
        return oscillatorVoices[index1].getWaveNum(index2);
    }

    void setWaveNum(int newWaveNum, int index1, int index2)
    {
        oscillatorVoices[index1].setWaveNum(newWaveNum, index2);
    }

    float getVolumeX() 
    {
        return volumeX;
    }

    float getVolumeY()
    {
        return volumeY;
    }

    void setVolumeX(float newVolumeX)
    {
        volumeX = newVolumeX;
    }

    void setVolumeY(float newVolumeY)
    {
        volumeY = newVolumeY;
    }


private:
    friend class SynthVoice;
   
    OscillatorVoice oscillatorVoices[4];

    float volumeX;
    float volumeY;

};
