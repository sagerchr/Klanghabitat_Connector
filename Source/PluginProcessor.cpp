/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KlanghabitatConnectorAudioProcessor::KlanghabitatConnectorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this,nullptr)

#endif
{
    
    NormalisableRange<float> inputRange(0.1f, 255.0f, 1.0f);
    treeState.createAndAddParameter("input", "input", "input", inputRange, 50.0f ,nullptr, nullptr);
    NormalisableRange<float> outputRange(0.1f, 255.0f, 1.0f);
    treeState.createAndAddParameter("output", "output", "output", outputRange, 50.0f ,nullptr, nullptr);
    NormalisableRange<float> attackRange(0.1f, 120.0f, 0.1f);
    treeState.createAndAddParameter("attack", "attack", "attack", attackRange, 10.0f ,nullptr, nullptr);
    NormalisableRange<float> releaseRange(10.0f, 500.0f, 10.0f);
    treeState.createAndAddParameter("release", "release", "release", releaseRange, 50.0f ,nullptr, nullptr);
    NormalisableRange<float> ratioRange(0.0f, 20.0f, 1.0f);
    treeState.createAndAddParameter("ratio", "ratio", "ratio", ratioRange, 1.0f ,nullptr, nullptr);
    NormalisableRange<float> thresholdRange(-20.0f, 0.0f, 0.1f);
    treeState.createAndAddParameter("threshold", "threshold", "threshold", thresholdRange, 0.0f ,nullptr, nullptr);
    treeState.state = ValueTree("Foo");    /* <--- initialise!!! */
}

KlanghabitatConnectorAudioProcessor::~KlanghabitatConnectorAudioProcessor()
{
}

//==============================================================================
const String KlanghabitatConnectorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KlanghabitatConnectorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KlanghabitatConnectorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KlanghabitatConnectorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KlanghabitatConnectorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KlanghabitatConnectorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KlanghabitatConnectorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KlanghabitatConnectorAudioProcessor::setCurrentProgram (int index)
{
}

const String KlanghabitatConnectorAudioProcessor::getProgramName (int index)
{
    return {};
}

void KlanghabitatConnectorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void KlanghabitatConnectorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void KlanghabitatConnectorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KlanghabitatConnectorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void KlanghabitatConnectorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
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
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool KlanghabitatConnectorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* KlanghabitatConnectorAudioProcessor::createEditor()
{
    return new KlanghabitatConnectorAudioProcessorEditor (*this);
}

//==============================================================================
void KlanghabitatConnectorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KlanghabitatConnectorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KlanghabitatConnectorAudioProcessor();
}
