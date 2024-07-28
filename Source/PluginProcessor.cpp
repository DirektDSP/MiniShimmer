/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MiniShimmerAudioProcessor::MiniShimmerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{

    apvts.state.setProperty(Service::PresetManager::presetNameProperty, "", nullptr);
    apvts.state.setProperty("version", ProjectInfo::versionString, nullptr);

    presetManager = std::make_unique<Service::PresetManager>(apvts);

}

MiniShimmerAudioProcessor::~MiniShimmerAudioProcessor()
{
}

//==============================================================================
const juce::String MiniShimmerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MiniShimmerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MiniShimmerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MiniShimmerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MiniShimmerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MiniShimmerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MiniShimmerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MiniShimmerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MiniShimmerAudioProcessor::getProgramName (int index)
{
    return {};
}

void MiniShimmerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MiniShimmerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    shimmerReverb.prepare(spec);

}

void MiniShimmerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MiniShimmerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void MiniShimmerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // FETCH PARAMETERS =====================================================================

    auto in = apvts.getRawParameterValue("IN")->load();
    auto out = apvts.getRawParameterValue("OUT")->load();
    auto bypass = apvts.getRawParameterValue("BYPASS")->load();
    auto roomSize = apvts.getRawParameterValue("ROOM_SIZE")->load();
    auto damping = apvts.getRawParameterValue("DAMPING")->load();
    auto wetLevel = apvts.getRawParameterValue("WET")->load();
    auto dryLevel = apvts.getRawParameterValue("DRY")->load();
    auto width = apvts.getRawParameterValue("WIDTH")->load();
    auto freeze = apvts.getRawParameterValue("FREEZE")->load();
    int pitch = apvts.getRawParameterValue("PITCH")->load();

    // END PARAMETERS =======================================================================
    if (!bypass) {

        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            // Apply input gain
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                channelData[sample] *= in;
            }
        }


        // REVERB ================================================================================
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear(i, 0, buffer.getNumSamples());

        shimmerReverb.setPitchShift(pitch);
        shimmerReverb.setReverbParameters(roomSize, damping, wetLevel, dryLevel, width, freeze);
        shimmerReverb.processAudioBlock(buffer);

        // END REVERB ============================================================================


        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            // Apply output gain 
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                channelData[sample] *= out;
            }
        }
    }
}

//==============================================================================
bool MiniShimmerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MiniShimmerAudioProcessor::createEditor()
{
    #ifdef NDEBUG // NDEBUG is defined by default in release builds
        //return new MiniShimmerAudioProcessorEditor(*this); // Return the editor in release mode
    return new GenericAudioProcessorEditor(*this);
    #else
        return new GenericAudioProcessorEditor(*this); // Return the editor in debug mode
    #endif
}

//==============================================================================
void MiniShimmerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.


    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MiniShimmerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.


    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MiniShimmerAudioProcessor();
}
