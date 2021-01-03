/*
  ==============================================================================

    XYSlider.h
    Created: 2 Jan 2021 6:04:09pm
    Author:  Kleine

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class XYSlider  : public juce::Component, public juce::Slider::Listener
{
public:
    XYSlider(VectorSynthAudioProcessor& p);
    ~XYSlider() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider xSlider;
    juce::Slider ySlider;

    void sliderValueChanged(Slider* slider) override;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> xSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ySliderAttachment;

    VectorSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XYSlider)
};
