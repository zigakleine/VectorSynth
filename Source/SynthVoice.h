/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Dec 2020 10:17:04pm
    Author:  Kleine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "OscillatorVoice.h"

class SynthVoice : public SynthesiserVoice
{
public:

    SynthVoice() {
        this->setAdsrSampleRate(this->getSampleRate());

        for (int i = 0; i < 4; i++) {
            phases[i] = 0;
            oscCycles[i] = 0;
            currentWaveIndexes[i] = 0;
        }


    }
    
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        noteFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        for (int i = 0; i < 4; i++) {
            adsrs[i].noteOn();

            phases[i] = 0;
            oscCycles[i] = 0;
            currentWaveIndexes[i] = 0;
            
        }

    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        allowTailOff = true;
        for (int i = 0; i < 4; i++) {
            adsrs[i].noteOff();
        }
    }

    void pitchWheelMoved(int newPitchWheelValue) override
    {
    
    }

    void controllerMoved(int controllerNumber, int newControllerValue) override
    {

    }

    void renderNextBlock(AudioBuffer <float>& outputBuffer, int startSample, int numSamples) override
    {
              
        if (SynthSound* playingSound = static_cast<SynthSound*> (getCurrentlyPlayingSound().get())) {
            
            Array<float> waves[4];
            double waveSizes[4];

            for (int i = 0; i < 4; i++) {
                waves[i] = playingSound->getWave(i, currentWaveIndexes[i]);
                waveSizes[i] = playingSound->getWaveSize(i, currentWaveIndexes[i]);

                increments[i] = noteFrequency * waveSizes[i] / this->getSampleRate();
             
                ADSR::Parameters adsrParams = playingSound->getAdsrParams(i);
                adsrs[i].setParameters(adsrParams);


            }
            
            for (int smp = 0; smp < numSamples; smp++) {

                for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++) {

                    float currentSample = 0;

                    for (int i = 0; i < 4; i++) {
                        //      1
                        //  ----------
                        //  |        |
                        // 0|        |2
                        //  |        |
                        //  ----------
                        //      3

                        float currentOscVolume = -1.0f;

                        if (i == 0) {
                            currentOscVolume = 1.0f - playingSound->getVolumeX();
                        }
                        else if (i == 1) {
                            currentOscVolume = 1.0f - playingSound->getVolumeY();
                        }
                        else if (i == 2) {
                            currentOscVolume = playingSound->getVolumeX();
                        }
                        else {
                            currentOscVolume = playingSound->getVolumeY();
                        }

                        noteAmplitudes[i] = adsrs[i].getNextSample();
                        currentSample += ((waves[i][(int)phases[i]] * noteAmplitudes[i]) * currentOscVolume);

                    }
                        
                     currentSample = (currentSample * masterAmplitude)/4.0;

                    outputBuffer.addSample(ch, startSample, currentSample);
                }

                startSample++;

                int oscillatorsPlaying = 4;
                for (int i = 0; i < 4; i++) {

                    if (oscCycles[i] < maxOscCycles) {
                        oscCycles[i] += (int)(phases[i] + increments[i]) / waveSizes[i];
                    }

                    int maxOscCycles = playingSound->getWaveRepeats(i, currentWaveIndexes[i]);
                    if (maxOscCycles != -1) {
                        if (oscCycles[i] >= maxOscCycles) {

                            int newWaveIndex = (currentWaveIndexes[i] + 1) % 2;
                            currentWaveIndexes[i] = newWaveIndex;
                            oscCycles[i] = 0;
                            waveSizes[i] = playingSound->getWaveSize(i, currentWaveIndexes[i]);
                            increments[i] = noteFrequency * waveSizes[i] / this->getSampleRate();
                            
                        }
            
                    }
      
                    phases[i] = fmod((phases[i] + increments[i]), waveSizes[i]);
       

                    if (noteAmplitudes[i] <= 0.002 && !this->isKeyDown()) {
                        oscillatorsPlaying -= 1;
                    }
                }
                bool shouldClear = (oscillatorsPlaying == 0);

                if (shouldClear) {
                    clearCurrentNote();
                    break;
                }

            }
        }

    }

    void setAdsrSampleRate(double sampleRate) {
        for (int i = 0; i < 4; i++) {
            adsrs[i].setSampleRate(sampleRate);
        }

    }

    //=====================================================================================
private:

    double noteFrequency = 0;
    double noteAmplitude = 0;
    double masterAmplitude = 0.4;

    double phases[4];
    double increments[4];

    double noteAmplitudes[4];

    int oscCycles[4];
    int maxOscCycles = 100;

    int currentWaveIndexes[4];

    ADSR adsrs[4];
  
};

/*
 //obsolete stuff:


MidiBuffer::Iterator it(midiMessages);

MidiMessage currentMessage;
int samplePos;


Array<Array<int>> noteMessages;

while (it.getNextEvent(currentMessage, samplePos)) {

    String msg = currentMessage.getDescription();

    if (currentMessage.isNoteOnOrOff()) {

        float velocity = currentMessage.getFloatVelocity();
        int pitch = currentMessage.getNoteNumber();

        if (currentMessage.isNoteOn()) {

            Array<int> noteOnMsg = {pitch, samplePos, 1};

            noteMessages.add(noteOnMsg);

        }
        else if (currentMessage.isNoteOff()) {

            Array<int> noteOffMsg = { pitch, samplePos, 0 };

            noteMessages.add(noteOffMsg);

        }

    }
}
*/