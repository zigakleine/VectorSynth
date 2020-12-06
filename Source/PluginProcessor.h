/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include "SynthSound.h"
#include "SynthVoice.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class VectorSynthAudioProcessor : public juce::AudioProcessor, public ValueTree::Listener
{
public:
    //==============================================================================
    VectorSynthAudioProcessor();
    ~VectorSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void updateWave(int index, int waveNum);
    void updateADSR();

    AudioProcessorValueTreeState::ParameterLayout createParameters();
    AudioProcessorValueTreeState& getAPVTS() { return APVTS; };


    void loadWavesIntoWaveSelector(juce::ComboBox* selector);

private:
    Synthesiser synth;
    int numVoices = 8;
    double sampleRateGlobal;


    int waveIndex = 0;
    Array<float> waveTable;
    AudioBuffer<float> mWaveForm;
    AudioFormatReader* reader{ nullptr };


    AudioProcessorValueTreeState APVTS;
    void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier &property) override;

    std::atomic<bool> shouldUpdate{ false };
 
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorSynthAudioProcessor)
};
