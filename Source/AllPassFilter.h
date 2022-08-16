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
class APFdelay
{
public:
    //==============================================================================
    APFdelay()
    {
        setMaxDelayTime (5.0f);
        setDelayTime (0, 0.7f);
        setWetLevel (1.0f);
        setFeedback (0.5f);
    }
    ~APFdelay(){};
    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        jassert (spec.numChannels <= maxNumChannels);
        sampleRate = (Type) spec.sampleRate;
        updateDelayLineSize();
        updateDelayTime();
        filterCoefs = juce::dsp::IIR::Coefficients<Type>::makeFirstOrderLowPass (sampleRate, Type (5000));
        ampSmooth.reset(sampleRate, 0.00001f);
        for (auto& f : filters)
        {
            f.prepare (spec);
            f.coefficients = filterCoefs;
        }
    }

    //==============================================================================
    void reset() noexcept
    {
        for (auto& dline : FFdelayLines)
            dline.clear();
        for (auto& dline : FBdelayLines)
            dline.clear();
    }
    void setFilterCutoff (Type newCutoff) noexcept
    {
        filterCoefs = juce::dsp::IIR::Coefficients<Type>::makeFirstOrderLowPass(sampleRate, newCutoff);
    }
    //==============================================================================
    size_t getNumChannels() const noexcept
    {
        return FFdelayLines.size();
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
    void setLate (Type newValue)
    {
        ampSmooth.setTargetValue(newValue);
    }
    
    void setTime (Type newValue)
    {
        time = newValue;
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

        
        for (size_t ch = 0; ch < numChannels; ++ch)
        {
            auto* input  = inputBlock .getChannelPointer (ch);
            auto* output = outputBlock.getChannelPointer (ch);
            auto& FFdline = FFdelayLines[ch];
            auto& FBdline = FBdelayLines[ch];
            auto delayTime = delayTimesSample[ch];
            auto& filter = filters[ch];
            for (size_t i = 0; i < numSamples; ++i)
                   {
                       auto delayedSample = filter.processSample(FFdline.get (delayTime));          
                       auto inputSample = input[i];
                       auto dlineInputSample = (inputSample);
                       FFdline.push (dlineInputSample);
                       auto FBdelayedSample = filter.processSample(FBdline.get (delayTime));
                       
                       outputSample = (ampSmooth.getNextValue()) * ((inputSample * wetLevel) + ((1.f-wetLevel) *(delayedSample) -  wetLevel * FBdelayedSample)) + (1.f-ampSmooth.getNextValue()) * inputSample;
                       auto FBdlineInputSample = (outputSample);
                       FBdline.push(FBdlineInputSample);
                       output[i] = (outputSample);
                       
                   }
        }
    }

private:
    //==============================================================================
    juce::LinearSmoothedValue<Type> ampSmooth {0.0f};
    std::array<DelayLine<Type>, maxNumChannels> FFdelayLines;
    std::array<DelayLine<Type>, maxNumChannels> FBdelayLines;
    std::array<size_t, maxNumChannels> delayTimesSample;
    std::array<Type, maxNumChannels> delayTimes;
    std::array<juce::dsp::IIR::Filter<Type>, maxNumChannels> filters;
    typename juce::dsp::IIR::Coefficients<Type>::Ptr filterCoefs;
    Type feedback { Type (0) };
    Type time { Type (0) };
    Type wetLevel { Type (0) };
    Type sampleRate   { Type (44.1e3) };
    Type maxDelayTime { Type (2) };
    Type outputSample {Type (0)};
    Type amount {Type (0)};
    //==============================================================================
    void updateDelayLineSize()
    {
        auto delayLineSizeSamples = (size_t) std::ceil (maxDelayTime * sampleRate);
         
            for (auto& dline : FFdelayLines)
                    dline.resize (delayLineSizeSamples);    // [2]
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
