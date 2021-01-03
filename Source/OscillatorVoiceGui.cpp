/*
  ==============================================================================

    OscillatorVoiceGui.cpp
    Created: 2 Jan 2021 2:47:52pm
    Author:  Kleine

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorVoiceGui.h"

//==============================================================================
OscillatorVoiceGui::OscillatorVoiceGui(int index_, bool show_, VectorSynthAudioProcessor& p) : processor(p)
{


    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    index = index_;
    show = show_;
    String oscNames[] = { "OSC1", "OSC2", "OSC3", "OSC4" };

 
    //ATTACK SLIDER
    attackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    attackSlider.setRange(0.0f, 3.0f, 0.01);
    addAndMakeVisible(attackSlider);

    attackLabel.setFont(10.0f);
    attackLabel.setText("Attack", NotificationType::dontSendNotification);
    attackLabel.setJustificationType(Justification::centredTop);
    attackLabel.attachToComponent(&attackSlider, false);

    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), (oscNames[index] + "ATTACK"), attackSlider);


    //DECAY SLIDER
    decaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decaySlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    decaySlider.setRange(0.0f, 3.0f, 0.01);
    addAndMakeVisible(decaySlider);

    decayLabel.setFont(10.0f);
    decayLabel.setText("Decay", NotificationType::dontSendNotification);
    decayLabel.setJustificationType(Justification::centredTop);
    decayLabel.attachToComponent(&decaySlider, false);

    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), (oscNames[index] + "DECAY"), decaySlider);

    //SUSTAIN SLIDER
    sustainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sustainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    sustainSlider.setRange(0.0f, 1.0f, 0.01);
    addAndMakeVisible(sustainSlider);

    sustainLabel.setFont(10.0f);
    sustainLabel.setText("Sustain", NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(Justification::centredTop);
    sustainLabel.attachToComponent(&sustainSlider, false);

    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), (oscNames[index] + "SUSTAIN"), sustainSlider);

    //RELEASE SLIDER
    releaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    releaseSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
    releaseSlider.setRange(0.0f, 3.0f, 0.01);
    addAndMakeVisible(releaseSlider);

    releaseLabel.setFont(10.0f);
    releaseLabel.setText("Release", NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(Justification::centredTop);
    releaseLabel.attachToComponent(&releaseSlider, false);

    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), (oscNames[index] + "RELEASE"), releaseSlider);


    String waveNums[] = { "1", "2", "3" };

    for (int j = 0; j < 3; j++) {

        // WAVE SELECTORS
        processor.loadWavesIntoWaveSelector(&waveSelectors[j]);
        waveSelectors[j].setJustificationType(Justification::centred);
        addAndMakeVisible(waveSelectors[j]);
        waveSelectorAttachments[j] = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), (oscNames[index] + "WAVE" + waveNums[j]), waveSelectors[j]);

        // WAVE REPEATS SLIDERS
        repeatsSliders[j].setSliderStyle(Slider::SliderStyle::LinearHorizontal);
        repeatsSliders[j].setColour(Slider::ColourIds::thumbColourId, Colours::white);
        repeatsSliders[j].setTextBoxStyle(Slider::TextBoxBelow, false, 40, 20);
        repeatsSliders[j].setRange(0, 80, 1);
        addAndMakeVisible(repeatsSliders[j]);

        repeatsAttachments[j] = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), (oscNames[index] + "REPEATS" + waveNums[j]), repeatsSliders[j]);


    }


}

OscillatorVoiceGui::~OscillatorVoiceGui()
{
}

void OscillatorVoiceGui::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);
    //g.drawText (title, getLocalBounds(), juce::Justification::centred, true);   // draw some placeholder text
}

void OscillatorVoiceGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    float startX = 0.5f;
    float startY = 0.3f;
    float sliderWidth = 0.1f;
    float sliderHeight = 0.4f;

    float waveSelectorX = 0.1f;
    float waveSelectorY = 0.1f;
    float waveSelectorHeight = 0.1f;
    float waveSelectorWidth = 0.3f;

    if (show) {
        attackSlider.setBoundsRelative(startX, startY, sliderWidth, sliderHeight);
        decaySlider.setBoundsRelative(startX + sliderWidth * 1, startY, sliderWidth, sliderHeight);
        sustainSlider.setBoundsRelative(startX + sliderWidth * 2, startY, sliderWidth, sliderHeight);
        releaseSlider.setBoundsRelative(startX + sliderWidth * 3, startY, sliderWidth, sliderHeight);

        for (int j = 0; j < 3; j++) {
            waveSelectors[j].setBoundsRelative(waveSelectorX, waveSelectorY + (waveSelectorHeight + 0.02f)*(2*j+1), waveSelectorWidth , waveSelectorHeight);
            repeatsSliders[j].setBoundsRelative(waveSelectorX, waveSelectorY + (waveSelectorHeight + 0.02f)*(2*j+2), waveSelectorWidth, waveSelectorHeight);
        }

    }

}
