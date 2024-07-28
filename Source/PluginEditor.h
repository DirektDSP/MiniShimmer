/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "StyleSheet.h"
#include "PresetPanel.h"

//==============================================================================
/**
*/
class MiniShimmerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MiniShimmerAudioProcessorEditor (MiniShimmerAudioProcessor&);
    ~MiniShimmerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MiniShimmerAudioProcessor& audioProcessor;



    // UI Components

    Gui::PresetPanel presetPanel;
    ExtLabel versionLabel;


    BypassButton bypassButton;

    RasterKnob roomSizeKnob;
    RasterKnob dampingKnob;
    RasterKnob wetLevelKnob;
    RasterKnob dryLevelKnob;
    RasterKnob widthKnob;
    FreezeButton freezeButton;


    // Attachments for parameters

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> freezeAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniShimmerAudioProcessorEditor)
};
