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

    mLoadButton.onClick = [&]() { processor.loadFile(); };
    addAndMakeVisible(mLoadButton);

    setSize (600, 300); 
}

VectorSynthAudioProcessorEditor::~VectorSynthAudioProcessorEditor()
{
}

//==============================================================================
void VectorSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void VectorSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    mLoadButton.setBounds(getWidth() / 3 - 30, getHeight() / 2 - 50, 60, 100);
}
