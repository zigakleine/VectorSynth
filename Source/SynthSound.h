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

    double getWaveSize(int index)  const noexcept
    {
        if (index == 0) {
            return waveSize1;
        }
        else if (index == 1) {
            return waveSize2;
        }
        else if (index == 2) {
            return waveSize3;
        }
        else {
            return waveSize4;
        }
    }

    void setWaveSize(double newWaveSize, int index) 
    {
        if (index == 0) {
            waveSize1 = newWaveSize;
        }
        else if (index == 1) {
            waveSize2 = newWaveSize;
        }
        else if (index == 2) {
            waveSize3 = newWaveSize;
        }
        else {
            waveSize4 = newWaveSize;
        }
    }

    Array<float> getWave(int index) const noexcept
    {
        if (index == 0) {
            return wave1;
        }
        else if (index == 1) {
            return wave2;
        }
        else if (index == 2) {
            return wave3;
        }
        else {
            return wave4;
        }
    }

    void setWave(Array<float> newWave, int index)
    {
        if (index == 0) {
            wave1 = newWave;
        }
        else if (index == 1) {
            wave2 = newWave;
        }
        else if (index == 2) {
            wave3 = newWave;
        }
        else {
            wave4 = newWave;
        }
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
    Array<float> wave1;
    Array<float> wave2;
    Array<float> wave3;
    Array<float> wave4;
    double waveSize1;
    double waveSize2;
    double waveSize3;
    double waveSize4;
    ADSR::Parameters adsrParams;

};
