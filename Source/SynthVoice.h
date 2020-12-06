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

class SynthVoice : public SynthesiserVoice
{
public:

    SynthVoice() {
        this->setAdsrSampleRate(this->getSampleRate());
    }
    
    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        noteFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        adsr.noteOn();
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        allowTailOff = true;
        adsr.noteOff();
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
            
            Array<float> wave1= playingSound->getWave(0);
            Array<float> wave2 = playingSound->getWave(1);
            Array<float> wave3 = playingSound->getWave(2);
            Array<float> wave4 = playingSound->getWave(3);

            double waveSize1 = playingSound->getWaveSize(0);
            double waveSize2 = playingSound->getWaveSize(1);
            double waveSize3 = playingSound->getWaveSize(2);
            double waveSize4 = playingSound->getWaveSize(3);

            ADSR::Parameters adsrParams = playingSound->getAdsrParams();

            adsr.setParameters(adsrParams);
                
            increment1 = noteFrequency * waveSize1 / this->getSampleRate();
            increment2 = noteFrequency * waveSize2 / this->getSampleRate();
            increment3 = noteFrequency * waveSize3 / this->getSampleRate();
            increment3 = noteFrequency * waveSize4 / this->getSampleRate();

            for (int smp = 0; smp < numSamples; smp++) {

                noteAmplitude = adsr.getNextSample();

                for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++) {

                    float currentSample = (((wave1[(int)phase1] + wave2[(int)phase2] + wave3[(int)phase3] + wave3[(int)phase4])
                        * noteAmplitude) * masterAmplitude)/4.0;

                    outputBuffer.addSample(ch, startSample, currentSample);
                }

                startSample++;
                phase1 = fmod((phase1 + increment1), waveSize1);
                phase2 = fmod((phase2 + increment2), waveSize2);
                phase3 = fmod((phase3 + increment3), waveSize3);
                phase4 = fmod((phase4 + increment4), waveSize4);

                if (noteAmplitude <= 0.002 && !this->isKeyDown()) {
                    clearCurrentNote();
                    break;
                }

            }
        }

    }

    void setAdsrSampleRate(double sampleRate) {
        adsr.setSampleRate(sampleRate);
    }

    //=====================================================================================
private:

    double noteFrequency = 0;
    double noteAmplitude = 0;
    double masterAmplitude = 0.2;
    double phase1 = 0;
    double phase2 = 0;
    double phase3 = 0;
    double phase4 = 0;
    double increment1;
    double increment2;
    double increment3;
    double increment4;

    ADSR adsr;
  
};

/*
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