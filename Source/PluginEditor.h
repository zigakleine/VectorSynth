/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VectorSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VectorSynthAudioProcessorEditor (VectorSynthAudioProcessor&);
    ~VectorSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TextButton mLoadButton;

    juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label attackLabel, decayLabel, sustainLabel, releaseLabel;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    juce::ComboBox waveSelector1, waveSelector2, waveSelector3, waveSelector4;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectorAttachment1, waveSelectorAttachment2, waveSelectorAttachment3,
        waveSelectorAttachment4;

    VectorSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorSynthAudioProcessorEditor)
};
