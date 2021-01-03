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
  
    
    addAndMakeVisible(oscillatorGui0);
    addAndMakeVisible(oscillatorGui1);
    addAndMakeVisible(oscillatorGui2);
    addAndMakeVisible(oscillatorGui3);

    addAndMakeVisible(xySlider);
 

    tabs.addTab("Oscillator voice 1", juce::Colours::black, &oscillatorGui0, false);
    tabs.addTab("Oscillator voice 2", juce::Colours::black, &oscillatorGui1, false);
    tabs.addTab("Oscillator voice 3", juce::Colours::black, &oscillatorGui2, false);
    tabs.addTab("Oscillator voice 4", juce::Colours::black, &oscillatorGui3, false);

    addAndMakeVisible(tabs);


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

    xySlider.repaint();
    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void VectorSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //mLoadButton.setBounds(getWidth() / 3 - 30, getHeight() / 2 - 50, 60, 100


    float mainComponentWidth = 0.75f;
    float mainComponentHeight = 1.0f;

    float sliderComponentWidth = 0.25f;
    float sliderComponentHeight = 1.0f;

    tabs.setBoundsRelative(0.0f, 0.0f, mainComponentWidth, mainComponentHeight);
    xySlider.setBoundsRelative(mainComponentWidth, 0.0f, sliderComponentWidth, sliderComponentHeight);

}

