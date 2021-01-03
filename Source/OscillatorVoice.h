/*
  ==============================================================================

    OscillatorVoice.h
    Created: 2 Jan 2021 7:11:04pm
    Author:  Kleine

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

class OscillatorVoice
{

public:

    OscillatorVoice() {

    }


    double getWaveSize(int index)  const noexcept
    {
        return waveSizes[index];
    }

    void setWaveSize(double newWaveSize, int index)
    {
        waveSizes[index] = newWaveSize;
    }


    int getWaveRepeats(int index)  const noexcept
    {
        return waveRepeats[index];
    }

    void setWaveRepeats(int newWaveRepeats, int index)
    {
        waveRepeats[index] = newWaveRepeats;
    }

    Array<float> getWave(int index) const noexcept
    {
        return waves[index];
    }

    void setWave(Array<float> newWave, int index)
    {
        waves[index] = newWave;
    }

    ADSR::Parameters getAdsrParams() const noexcept
    {
        return adsrParams;
    }

    void setAdsrParams(ADSR::Parameters newAdsrParams)
    {
        adsrParams = newAdsrParams;
    }

    int getWaveNum(int index)  const noexcept
    {
        return waveNums[index];
    }

    void setWaveNum(int newWaveNum, int index)
    {
        waveNums[index] = newWaveNum;
    }

private:


    Array<float> waves[3];
    int waveRepeats[3];
    double waveSizes[3];
    int waveNums[3];

    ADSR::Parameters adsrParams;

};
