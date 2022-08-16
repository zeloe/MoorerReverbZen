/*
  ==============================================================================

    APF.h
    Created: 15 Aug 2022 6:39:57pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "AllPassFilter.h"
template <typename Type>
class APF
{
public:
    APF(){};
    ~APF(){};
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        delaySmooth.reset(spec.sampleRate,0.00001f);
        for(auto& dl : delayLines)
        {
            dl.prepare(spec);
        }
        updateParameters();
        updateLate();
        updateTime();
    }
    void reset() noexcept
    {
        for(auto& dl : delayLines)
        {
            dl.reset();
        }
        
    }
    
    template <typename ProcessContext>
        void process(const ProcessContext& context) noexcept
        {
           
            for(auto& dl : delayLines)
            {
                dl.process(context);
            }
            
        }
    void getLate (Type newValue)
    {
        amount = newValue;
        updateLate();
    }
    void getTime (Type newValue)
    {
        delaySmooth.setTargetValue(newValue);
        updateTime();
    }
private:
    juce::LinearSmoothedValue<Type> delaySmooth {0.0f};
    Type amount {Type (0)};
    Type time {Type (0)};
    juce::dsp::AudioBlock<float> ffcDelayBlock;
    std::array<APFdelay<Type>, 6> delayLines ;
        const float delaystimes [7]
        {0.5,0.6,0.70,0.8,0.9,0.10};
        const float filtercoeffs [7]
        {100,300,400,500,600,700};
        const float wetLevels [7]
        {0.75,0.65,0.85,0.88,0.89,0.79};
    void updateParameters()
    {
        
        
        size_t counter1 = 0;
        for(auto& dl : delayLines)
        {
            dl.setWetLevel(wetLevels[counter1]);
            counter1++;
        }
        size_t counter2 = 0;
        for(auto& dl : delayLines)
        {
            dl.setFilterCutoff(filtercoeffs[counter2]);
            counter2++;
        }
        
        
    }
    void updateLate()
    {
        size_t counter4 = 0;
        for(auto& dl : delayLines)
        {
            dl.setLate(amount);
            counter4++;
        }
        
    }
    
    void updateTime()
    {
        size_t counter = 0;
        for(auto& dl : delayLines)
        {
            dl.setDelayTime(0,delaystimes[counter] * delaySmooth.getNextValue());
            counter++;
        }
        
    }
    
};
