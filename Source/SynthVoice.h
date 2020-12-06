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
            
            Array<float> wave = playingSound->getWave();
            double waveSize = playingSound->getWaveSize();
            ADSR::Parameters adsrParams = playingSound->getAdsrParams();

            adsr.setParameters(adsrParams);
                
            increment = noteFrequency * waveSize / this->getSampleRate();

            for (int smp = 0; smp < numSamples; smp++) {

                noteAmplitude = adsr.getNextSample();

                for (int ch = 0; ch < outputBuffer.getNumChannels(); ch++) {
                    outputBuffer.addSample(ch, startSample, (wave[(int)phase] * noteAmplitude) * masterAmplitude);
                }

                startSample++;
                phase = fmod((phase + increment), waveSize);

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
    double phase = 0;
    double increment;

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