/*
  ==============================================================================

    Delay.h
    Created: 6 Aug 2022 3:30:03pm
    Author:  Zeno  Loesch

  ==============================================================================
*/
#include "JuceHeader.h"
#include "DelayLine.h"
#pragma once
template <typename Type, size_t maxNumChannels = 1>
class FFeedbackCombDelay
{
public:
    //==============================================================================
    FFeedbackCombDelay()
    {
        setMaxDelayTime (5.0f);
        setDelayTime (0, 0.7f);
        setWetLevel (1.0f);
        setFeedback (0.5f);
    }
    ~FFeedbackCombDelay(){};
    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        jassert (spec.numChannels <= maxNumChannels);
        sampleRate = (Type) spec.sampleRate;
        updateDelayLineSize();
        updateDelayTime();
        filterCoefs = juce::dsp::IIR::Coefficients<Type>::makeFirstOrderLowPass (sampleRate, Type (5000));
       
        for (auto& f : filters)
        {
            f.prepare (spec);
            f.coefficients = filterCoefs;
        }
        ampSmooth.reset(sampleRate,0.00001f);
    }

    //==============================================================================
    void reset() noexcept
    {
        for (auto& dline : FBdelayLines)
            dline.clear();
    }

    //==============================================================================
    size_t getNumChannels() const noexcept
    {
        return FBdelayLines.size();
    }

    //==============================================================================
    void setMaxDelayTime (Type newValue)
    {
        jassert (newValue > Type (0));
        maxDelayTime = newValue;
        updateDelayLineSize();
    }

    //==============================================================================
    void setFeedback (Type newValue) noexcept
    {
        jassert (newValue >= Type (0) && newValue <= Type (1));
        feedback = newValue;
    }

    //==============================================================================
    void setWetLevel (Type newValue) noexcept
    {
        jassert (newValue >= Type (0) && newValue <= Type (1));
        wetLevel = newValue;
    }
    
    void setReso (Type newValue)
    {
        ampSmooth.setTargetValue(newValue);
    }
    void setTime (Type newValue)
    {
        time = newValue;
    }
    //==============================================================================
    void setDelayTime (size_t channel, Type newValue)
    {
        if (channel >= getNumChannels())
        {
            jassertfalse;
            return;
        }

        jassert (newValue >= Type (0));
        delayTimes[channel] = newValue;
        updateDelayTime();
    }

    //==============================================================================
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        auto& inputBlock  = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        auto numSamples  = outputBlock.getNumSamples();
        auto numChannels = outputBlock.getNumChannels();

        jassert (inputBlock.getNumSamples() == numSamples);
        jassert (inputBlock.getNumChannels() == numChannels);

        //juce::ignoreUnused (numSamples);
        
        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* input  = inputBlock .getChannelPointer (ch);
            auto* output = outputBlock.getChannelPointer (ch);
            auto& FBdline = FBdelayLines[ch];
            auto delayTime = delayTimesSample[ch];
            auto& filter = filters[ch];
            for (size_t i = 0; i < numSamples; ++i)
                   {
                   
                       auto inputSample = input[i];
                       auto FBdelayedSample = filter.processSample ((FBdline.get (delayTime)));
                       auto FBdlineInputSample = (outputSample);
                       outputSample = ampSmooth.getNextValue() *(( inputSample) -  (wetLevel * FBdelayedSample))+ (1.f - ampSmooth.getNextValue()) * inputSample;
                       FBdline.push(FBdlineInputSample);
                       output[i] = (outputSample);
                       
                   }
        }
    }

private:
    //==============================================================================
    juce::LinearSmoothedValue<Type> ampSmooth {0.0f};
    std::array<DelayLine<Type>, maxNumChannels> FBdelayLines;
    std::array<size_t, maxNumChannels> delayTimesSample;
    std::array<Type, maxNumChannels> delayTimes;
    std::array<juce::dsp::IIR::Filter<Type>, maxNumChannels> filters;
    Type feedback { Type (0) };
    Type wetLevel { Type (0) };
    Type time { Type (0) };
    typename juce::dsp::IIR::Coefficients<Type>::Ptr filterCoefs;
    Type sampleRate   { Type (44.1e3) };
    Type maxDelayTime { Type (2) };
    Type outputSample {Type (0)};
    Type amount {Type (0)};
    //==============================================================================
    void updateDelayLineSize()
    {
        auto delayLineSizeSamples = (size_t) std::ceil (maxDelayTime * sampleRate);
         // [2]
            for (auto& dline : FBdelayLines)
                    dline.resize (delayLineSizeSamples);
    }

    //==============================================================================
    void updateDelayTime() noexcept
    {
        for (size_t ch = 0; ch < maxNumChannels; ++ch)
            delayTimesSample[ch] = (size_t) juce::roundToInt (delayTimes[ch] * sampleRate);
        
        
    }
};
