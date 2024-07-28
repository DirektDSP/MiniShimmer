/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "PresetManager.h"
#include "ShimmerReverb.h"
#include <JuceHeader.h>

//==============================================================================
/**
*/
class MiniShimmerAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MiniShimmerAudioProcessor();
    ~MiniShimmerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    Service::PresetManager& getPresetManager() { return *presetManager; }
    AudioProcessorValueTreeState apvts;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{"IN", 1}, "In Gain", 0.0f, 5.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{"OUT", 1}, "Out Gain", 0.0f, 5.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterBool>(ParameterID{ "BYPASS", 1 }, "Bypass", false));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{ "ROOM_SIZE", 1 }, "Room Size", 0.0f, 1.0f, 0.5f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{ "DAMPING", 1 }, "Damping", 0.0f, 1.0f, 0.5f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{ "WET", 1 }, "Wet Level", 0.0f, 1.0f, 0.33f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{ "DRY", 1 }, "Dry Level", 0.0f, 1.0f, 0.4f));
        params.push_back(std::make_unique<juce::AudioParameterFloat>(ParameterID{ "WIDTH", 1 }, "Width", 0.0f, 1.0f, 1.0f));
        params.push_back(std::make_unique<juce::AudioParameterBool>(ParameterID{ "FREEZE", 1 }, "Freeze", false));
        params.push_back(std::make_unique<juce::AudioParameterInt>(ParameterID{ "PITCH", 1 }, "Pitch", 1, 12, 12));

        return { params.begin(), params.end() };
    }

private:
    std::unique_ptr<Service::PresetManager> presetManager;
    ShimmerReverb shimmerReverb;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniShimmerAudioProcessor)
};
