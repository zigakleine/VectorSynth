/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscillatorVoiceGui.h"
#include "XYSlider.h"

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
    VectorSynthAudioProcessor& processor;

    OscillatorVoiceGui oscillatorGui0{0, true, processor};
    OscillatorVoiceGui oscillatorGui1{1, true, processor};
    OscillatorVoiceGui oscillatorGui2{2, true, processor};
    OscillatorVoiceGui oscillatorGui3{3, true, processor};

    juce::TabbedComponent tabs{ TabbedButtonBar::Orientation::TabsAtTop };

    XYSlider xySlider{processor};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VectorSynthAudioProcessorEditor)
};
