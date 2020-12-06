/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VectorSynthAudioProcessorEditor::VectorSynthAudioProcessorEditor (VectorSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    //mLoadButton.setButtonText("hej");
    //mLoadButton.onClick = [&]() { processor.loadFile(); };
    //addAndMakeVisible(mLoadButton);


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

    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "ATTACK", attackSlider);


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

    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DECAY", decaySlider);

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

    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SUSTAIN", sustainSlider);

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


    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "RELEASE", releaseSlider);

    processor.loadWavesIntoWaveSelector(&waveSelector1);
    waveSelector1.setJustificationType(Justification::centred);
    addAndMakeVisible(waveSelector1);
    waveSelectorAttachment1 = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), "WAVE1", waveSelector1);

    processor.loadWavesIntoWaveSelector(&waveSelector2);
    waveSelector2.setJustificationType(Justification::centred);
    addAndMakeVisible(waveSelector2);
    waveSelectorAttachment2 = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), "WAVE2", waveSelector2);

    processor.loadWavesIntoWaveSelector(&waveSelector3);
    waveSelector3.setJustificationType(Justification::centred);
    addAndMakeVisible(waveSelector3);
    waveSelectorAttachment3 = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), "WAVE3", waveSelector3);

    processor.loadWavesIntoWaveSelector(&waveSelector4);
    waveSelector4.setJustificationType(Justification::centred);
    addAndMakeVisible(waveSelector4);
    waveSelectorAttachment4 = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(), "WAVE4", waveSelector4);



    setSize (600, 300); 
}

VectorSynthAudioProcessorEditor::~VectorSynthAudioProcessorEditor()
{
}

//==============================================================================
void VectorSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    
    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void VectorSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //mLoadButton.setBounds(getWidth() / 3 - 30, getHeight() / 2 - 50, 60, 100);

    float startX = 0.6f;
    float startY = 0.6f;
    float sliderWidth = 0.1f;
    float sliderHeight   = 0.4f;

    float waveSelectorX = 0.2f;
    float waveSelectorY = 0.2f;
    float waveSelectorHeight = 0.1f;
    float waveSelectorWidth = 0.3f;


    attackSlider.setBoundsRelative(startX, startY, sliderWidth, sliderHeight);
    decaySlider.setBoundsRelative(startX + sliderWidth * 1, startY, sliderWidth, sliderHeight);
    sustainSlider.setBoundsRelative(startX + sliderWidth * 2, startY, sliderWidth, sliderHeight);
    releaseSlider.setBoundsRelative(startX + sliderWidth * 3, startY, sliderWidth, sliderHeight);

    waveSelector1.setBoundsRelative(waveSelectorX, waveSelectorY, waveSelectorWidth, waveSelectorHeight);
    waveSelector2.setBoundsRelative(waveSelectorX, waveSelectorY + (waveSelectorHeight + 0.05f)*1, waveSelectorWidth, waveSelectorHeight);
    waveSelector3.setBoundsRelative(waveSelectorX, waveSelectorY + (waveSelectorHeight + 0.05f)*2, waveSelectorWidth, waveSelectorHeight);
    waveSelector4.setBoundsRelative(waveSelectorX, waveSelectorY + (waveSelectorHeight + 0.05f)*3, waveSelectorWidth, waveSelectorHeight);

}

