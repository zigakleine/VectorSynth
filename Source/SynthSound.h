/*
  ==============================================================================

    SynthSound.h
    Created: 5 Dec 2020 10:16:28pm
    Author:  Kleine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{

public:

    SynthSound(){

    }


    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }

    bool appliesToChannel(int midiNoteNumber) override
    {
        return true;
    }

    double getWaveSize()  const noexcept
    {
        return waveSize;
    }

    void setWaveSize(double newWaveSize) 
    {
        waveSize = newWaveSize;
    }

    Array<float> getWave() const noexcept
    {
        return wave;
    }

    void setWave(Array<float> newWave)
    {
        wave = newWave;
    }

    ADSR::Parameters getAdsrParams() const noexcept
    {
        return adsrParams;
    }

    void setAdsrParams(ADSR::Parameters newAdsrParams)
    {
        adsrParams = newAdsrParams;
    }

private:
    friend class SynthVoice;
    Array<float> wave;
    double waveSize;
    ADSR::Parameters adsrParams;

};
