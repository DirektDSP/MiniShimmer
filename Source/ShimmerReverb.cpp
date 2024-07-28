/*
  ==============================================================================

    ShimmerReverb.cpp
    Created: 22 Jun 2024 12:44:51pm
    Author:  seamu

  ==============================================================================
*/

#include "ShimmerReverb.h"

ShimmerReverb::ShimmerReverb()
{
}

ShimmerReverb::~ShimmerReverb()
{
}

void ShimmerReverb::prepare(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;

    pitchShifter.setTransposeSemitones(12);

    // Prepare reverb
    juce::Reverb::Parameters reverbParams;
    reverbParams.roomSize = 0.5f;
    reverbParams.damping = 0.5f;
    reverbParams.wetLevel = 0.33f;
    reverbParams.dryLevel = 0.4f;
    reverbParams.width = 1.0f;
    reverbParams.freezeMode = 0.0f;
    reverb.setParameters(reverbParams);

    // Prepare pitch shifter
    pitchShifter.presetDefault(2, sampleRate);
    feedbackBuffer.setSize(2, samplesPerBlock); // Assuming stereo
    processedBuffer.setSize(2, samplesPerBlock); // Assuming stereo
    feedbackBuffer.clear();
}

void ShimmerReverb::prepare(juce::dsp::ProcessSpec spec)
{

    pitchShifter.setTransposeSemitones(12);

    // Prepare reverb
    juce::Reverb::Parameters reverbParams;
    reverbParams.roomSize = 0.5f;
    reverbParams.damping = 0.5f;
    reverbParams.wetLevel = 0.33f;
    reverbParams.dryLevel = 0.4f;
    reverbParams.width = 1.0f;
    reverbParams.freezeMode = 0.0f;
    reverb.setParameters(reverbParams);

    // Prepare pitch shifter
    pitchShifter.presetDefault(2, spec.sampleRate);
    feedbackBuffer.setSize(2, spec.maximumBlockSize); // Assuming stereo
    processedBuffer.setSize(2, spec.maximumBlockSize); // Assuming stereo
    feedbackBuffer.clear();
}


void ShimmerReverb::processAudioBlock(juce::AudioBuffer<float>& inputBuffer)
{
    int numChannels = inputBuffer.getNumChannels();
    int numSamples = inputBuffer.getNumSamples();
    juce::dsp::AudioBlock<float> reverbBlock(inputBuffer);
    juce::dsp::AudioBlock<float> feedbackBlock(feedbackBuffer);
    dryBuffer.makeCopyOf(inputBuffer);

    // Reverb
    feedbackBlock.multiplyBy(reverbParams.damping / 2);
    reverbBlock.add(feedbackBlock);
    reverb.process(juce::dsp::ProcessContextReplacing<float>(reverbBlock));

    // Pitch Shift

    // convert reverbBlock to an audio buffer
    reverbBuffer.setSize(numChannels, numSamples, false, false, true);
    for (int channel = 0; channel < numChannels; ++channel)
    {
        reverbBuffer.copyFrom(channel, 0, reverbBlock.getChannelPointer(channel), numSamples);
    }

    if (pitchShiftSemitones != 0) {
        float* const* reverbedData = reverbBuffer.getArrayOfWritePointers();
        float* const* processedData = processedBuffer.getArrayOfWritePointers();
        pitchShifter.process(const_cast<float**>(reverbedData), numSamples, const_cast<float**>(processedData), numSamples);
    }
    else {
        processedBuffer.makeCopyOf(reverbBuffer);
    }

    // copy to feedback

    feedbackBuffer.makeCopyOf(processedBuffer);

    // mix wet and dry
    processedBuffer.applyGain(reverbParams.wetLevel);
    dryBuffer.applyGain(reverbParams.dryLevel);
    inputBuffer.clear();
    for (int channel = 0; channel < numChannels; ++channel) {
        inputBuffer.addFrom(channel, 0, dryBuffer.getReadPointer(channel), numSamples);
        inputBuffer.addFrom(channel, 0, processedBuffer.getReadPointer(channel), numSamples);
    }

    // Apply 
    feedbackBuffer.applyGain(reverbParams.damping/2);
}


void ShimmerReverb::setReverbParameters(float roomSize, float damping, float wetLevel, float dryLevel, float width, int freeze_mode)
{
    reverbParams.roomSize = roomSize - 0.01f;
    reverbParams.damping = damping;
    reverbParams.wetLevel = wetLevel;
    reverbParams.dryLevel = dryLevel;
    reverbParams.width = width;
    reverbParams.freezeMode = freeze_mode;
    reverb.setParameters(reverbParams);

}

void ShimmerReverb::setPitchShift(int shiftSemitones)
{
    pitchShiftSemitones = shiftSemitones;
    pitchShifter.setTransposeSemitones(shiftSemitones);
}
