/*
  ==============================================================================

    XYSlider.cpp
    Created: 2 Jan 2021 6:04:09pm
    Author:  Kleine

  ==============================================================================
*/

#include <JuceHeader.h>
#include "XYSlider.h"

//==============================================================================
XYSlider::XYSlider(VectorSynthAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    xSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    xSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    xSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    xSlider.setRange(0.0f, 1.0f, 0.01);
    addAndMakeVisible(xSlider);

    xSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "VOLUMEX", xSlider);

    ySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    ySlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    ySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    ySlider.setRange(0.0f, 1.0f, 0.01);
    addAndMakeVisible(ySlider);

    ySliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "VOLUMEY", ySlider);



}

XYSlider::~XYSlider()
{
}

void XYSlider::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */


    float volumeX = xSlider.getValue();
    float volumeY = ySlider.getValue();


    g.fillAll (juce::Colours::black); 
    
    g.setColour(juce::Colours::white);
    g.fillRect(40, 100, 100, 100 );

    g.setColour(juce::Colours::black);
    //DBG(volumeX);
    //DBG(volumeY);

    g.fillEllipse(40.0f + volumeX * 100.0f - 5.0f, 100.0f + (1.0f - volumeY) * 100.0f - 5.0f, 10.0f, 10.0f);
   

    // clear the background
   // draw some placeholder text
}

void XYSlider::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    float startX = 30.0f;
    float startY = 90.0f;

    float sliderYWidth = 40.0f;
    float sliderYHeight = 120.0f;

    float sliderXHeight = 40.0f;
    float sliderXWidth = 120.0f;

    ySlider.setBounds(0.0f , startY, sliderYWidth, sliderYHeight);
    xSlider.setBounds(startX, startY +sliderYHeight, sliderXWidth, sliderXHeight);


   
}

void XYSlider::sliderValueChanged(Slider* slider)
{

}
