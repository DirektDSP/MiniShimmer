/*
  ==============================================================================

    ShimmerReverb.h
    Created: 22 Jun 2024 12:44:51pm
    Author:  seamu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "signalsmith-stretch/signalsmith-stretch.h"

class ShimmerReverb
{
public:
    ShimmerReverb();
    ~ShimmerReverb();

    void prepare(double sampleRate, int samplesPerBlock);
    void prepare(juce::dsp::ProcessSpec spec);
    void processAudioBlock(juce::AudioBuffer<float>& buffer);
    void setReverbParameters(float roomSize, float damping, float wetLevel, float dryLevel, float width, int freeze_mode);
    void setPitchShift(int shiftSemitones);

private:
    juce::AudioBuffer<float> reverbBuffer;
    juce::AudioBuffer<float> dryBuffer;
    juce::Reverb::Parameters reverbParams;
    juce::dsp::Reverb reverb;
    signalsmith::stretch::SignalsmithStretch<float> pitchShifter;
    double currentSampleRate = 44100.0;
    int pitchShiftSemitones = 12; // Default to one octave up

    juce::AudioBuffer<float> feedbackBuffer;
    juce::AudioBuffer<float> processedBuffer; // Buffer for intermediate processing
};

