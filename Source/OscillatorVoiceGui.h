/*
  ==============================================================================

    OscillatorVoiceGui.h
    Created: 2 Jan 2021 2:47:52pm
    Author:  Kleine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OscillatorVoiceGui  : public juce::Component
{
public:
    OscillatorVoiceGui(int index_, bool show_, VectorSynthAudioProcessor& p);
    ~OscillatorVoiceGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    int index;
    bool show;

    juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label attackLabel, decayLabel, sustainLabel, releaseLabel;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    juce::ComboBox waveSelectors[3];
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelectorAttachments[3];

    juce::Slider repeatsSliders[3];
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> repeatsAttachments[3];


    VectorSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorVoiceGui)
};
