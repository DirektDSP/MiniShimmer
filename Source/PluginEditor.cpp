/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MiniShimmerAudioProcessorEditor::MiniShimmerAudioProcessorEditor (MiniShimmerAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p),
    presetPanel(p.getPresetManager())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(960, 540);
    addAndMakeVisible(presetPanel);



    //     inGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "IN", inGainKnob);
    //   addAndMakeVisible(inGainKnob);
    //
       //outGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "OUT", outGainKnob);
    //   addAndMakeVisible(outGainKnob);


    addAndMakeVisible(bypassButton);
    bypassButton.setButtonText("M");
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "BYPASS", bypassButton);

    addAndMakeVisible(roomSizeKnob);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ROOM_SIZE", roomSizeKnob);

    addAndMakeVisible(dampingKnob);
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DAMPING", dampingKnob);

    addAndMakeVisible(wetLevelKnob);
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WET", wetLevelKnob);

    addAndMakeVisible(dryLevelKnob);
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRY", dryLevelKnob);

    addAndMakeVisible(widthKnob);
    widthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WIDTH", widthKnob);

    addAndMakeVisible(freezeButton);
    freezeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "FREEZE", freezeButton);


    addAndMakeVisible(versionLabel);
    versionLabel.setText("", juce::dontSendNotification);

}

MiniShimmerAudioProcessorEditor::~MiniShimmerAudioProcessorEditor()
{
}

//==============================================================================
void MiniShimmerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    /*
    auto backgroundImage = juce::ImageCache::getFromMemory(BinaryData::Main_png, BinaryData::Main_pngSize);
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
    */

    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);


}

void MiniShimmerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..


    presetPanel.setBounds(0, 0, getWidth(), 60);

    versionLabel.setBounds(0, 0, 200, 60);

    bypassButton.setBounds(87, 347, 25, 25);
    
    
    roomSizeKnob.setBounds(53, 139, 60, 60);
    dampingKnob.setBounds(140, 139, 60, 60);
    widthKnob.setBounds(227, 139, 60, 60);
    wetLevelKnob.setBounds(53, 251, 60, 60);
    dryLevelKnob.setBounds(140, 251, 60, 60);
    freezeButton.setBounds(234, 258, 45, 45);



}
