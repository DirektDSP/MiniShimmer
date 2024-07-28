/*
  ==============================================================================

    MakeLogarithmicRange.h
    Created: 18 Jun 2024 7:34:45am
    Author:  Seamus Mullan

  ==============================================================================
*/

#pragma once

// used to make sliders for volume logarithmic
//template<typename FloatType>
//static inline juce::NormalisableRange<FloatType> makeLogarithmicRange (FloatType min, FloatType max)
//    {
//        return juce::NormalisableRange<FloatType>
//        (
//            min, max,
//            [](FloatType start, FloatType end, FloatType normalised)
//            {
//                return start + (std::pow (FloatType (2), normalised * FloatType (10)) - FloatType (1)) * (end - start) / FloatType (1023);
//            },
//            [](FloatType start, FloatType end, FloatType value)
//            {
//                return (std::log (((value - start) * FloatType (1023) / (end - start)) + FloatType (1)) / std::log (FloatType (2))) / FloatType (10);
//            },
//            [](FloatType start, FloatType end, FloatType value)
//            {
//                // optimised for frequencies: >3 kHz: 2 decimals
//                if (value > FloatType (3000))
//                    return juce::jlimit (start, end, FloatType (100) * juce::roundToInt (value / FloatType (100)));
//
//                // optimised for frequencies: 1-3 kHz: 1 decimal
//                if (value > FloatType (1000))
//                    return juce::jlimit (start, end, FloatType (10) * juce::roundToInt (value / FloatType (10)));
//
//                return juce::jlimit (start, end, FloatType (juce::roundToInt (value)));
//            });
//    }


// smol but worky :)
static inline NormalisableRange<float> frequencyRange(float min, float max, float interval)
{
    return { min, max, interval, 1.f / std::log2(1.f + std::sqrt(max / min)) };
}
