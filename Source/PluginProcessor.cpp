/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VectorSynthAudioProcessor::VectorSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), APVTS(*this, nullptr, "PARAMETERS", createParameters())
#endif
{

    APVTS.state.addListener(this);

    synth.clearVoices();

    for (int i = 0; i < numVoices; i++) {

        synth.addVoice(new SynthVoice());

    }

    synth.clearSounds();
    synth.addSound(new SynthSound());
    updateWave(0, 0);
    updateWave(0, 1);
    updateWave(0, 2);
    updateWave(0, 3);
}

VectorSynthAudioProcessor::~VectorSynthAudioProcessor()
{
    reader = nullptr;
}

//==============================================================================
const juce::String VectorSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VectorSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VectorSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VectorSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VectorSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VectorSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VectorSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VectorSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VectorSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void VectorSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void VectorSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    sampleRateGlobal = sampleRate;
    synth.setCurrentPlaybackSampleRate(sampleRateGlobal);

}

void VectorSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VectorSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VectorSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    if (shouldUpdate) {
        updateADSR();

        int index1 = APVTS.getRawParameterValue("WAVE1")->load();
        updateWave(index1, 0);

        int index2 = APVTS.getRawParameterValue("WAVE2")->load();
        updateWave(index2, 1);

        int index3 = APVTS.getRawParameterValue("WAVE3")->load();
        updateWave(index3, 2);

        int index4 = APVTS.getRawParameterValue("WAVE4")->load();
        updateWave(index4, 3);

        shouldUpdate = false;
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool VectorSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VectorSynthAudioProcessor::createEditor()
{
    return new VectorSynthAudioProcessorEditor (*this);
}

//==============================================================================
void VectorSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VectorSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VectorSynthAudioProcessor();
}

void VectorSynthAudioProcessor::updateADSR() {
    if (SynthSound* currentSound = static_cast<SynthSound*>(synth.getSound(0).get())) {

        ADSR::Parameters adsrParams;

        

        adsrParams.attack = APVTS.getRawParameterValue("ATTACK")->load();
        adsrParams.decay = APVTS.getRawParameterValue("DECAY")->load();
        adsrParams.sustain = APVTS.getRawParameterValue("SUSTAIN")->load();
        adsrParams.release = APVTS.getRawParameterValue("RELEASE")->load();


        currentSound->setAdsrParams(adsrParams);

    }
}

AudioProcessorValueTreeState::ParameterLayout VectorSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

    parameters.push_back(std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 3.0f, 0.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 3.0f, 0.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 3.0f, 0.0f));

    parameters.push_back(std::make_unique<AudioParameterFloat>("WAVE1", "wave1", 0, BinaryData::namedResourceListSize, 0));
    parameters.push_back(std::make_unique<AudioParameterFloat>("WAVE2", "wave2", 0, BinaryData::namedResourceListSize, 0));
    parameters.push_back(std::make_unique<AudioParameterFloat>("WAVE3", "wave3", 0, BinaryData::namedResourceListSize, 0));
    parameters.push_back(std::make_unique<AudioParameterFloat>("WAVE4", "wave4", 0, BinaryData::namedResourceListSize, 0));

    return { parameters.begin(), parameters.end() };
}

void VectorSynthAudioProcessor::loadWavesIntoWaveSelector(juce::ComboBox* selector)
{

    for (int i = 0; i < BinaryData::namedResourceListSize; i++) {
        int binaryDataSize;
        const char* name = BinaryData::getNamedResource(BinaryData::namedResourceList[i], binaryDataSize);
        selector->addItem(BinaryData::namedResourceList[i], i + 1);
    }   

}

void VectorSynthAudioProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    shouldUpdate = true;
}

void VectorSynthAudioProcessor::updateWave(int index, int waveNum) {

    int binaryDataSize = 0;
    
    const char* name = BinaryData::getNamedResource(BinaryData::namedResourceList[index], binaryDataSize);

    MemoryInputStream inputStream(name, binaryDataSize, false);

    WavAudioFormat wavFormat;
    reader = wavFormat.createReaderFor(&inputStream, true);

    int numSamples = reader->lengthInSamples;

    mWaveForm.setSize(2, numSamples);
    reader->read(&mWaveForm, 0, numSamples, 0, true, true);
    

    DBG("hello");
    const float* waveFormReadPointer = mWaveForm.getReadPointer(0);

    int wtSize = numSamples;

    waveTable.clear();

    for (int smp = 0; smp < numSamples; smp++) {
        //DBG(waveFormReadPointer[smp]);
        waveTable.insert(smp, waveFormReadPointer[smp]);
    }

    if (SynthSound* currentSound = static_cast<SynthSound*>(synth.getSound(0).get())) {
        
        currentSound->setWave(waveTable, waveNum);
        currentSound->setWaveSize(numSamples, waveNum);

    }
}