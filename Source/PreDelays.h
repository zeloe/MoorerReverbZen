/*
  ==============================================================================

    MoorerReverb.h
    Created: 13 Aug 2022 2:30:59pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Delay.h"


template <typename Type>
class PreDelays
{
public:
    PreDelays(){};
    ~PreDelays(){};
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        delaySmooth.reset(spec.sampleRate,0.00001f);
        for(auto& dl : delayLines)
        {
            dl.prepare(spec);
        }
        updateParameters();
        updateAmount();
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
    void getAmount (Type newValue)
    {
        amount = newValue;
        updateAmount();
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
    std::array<Delay<Type>, 7> delayLines ;
   
    const float preDelayParams [8]
    {0.0199,0.0354,0.0389,0.0414,0.0699,0.0796,0.000};
    const float filterparams [8]
    {1942,1363,1312,1574,981,1036,16000};
    const float preDelayAmpParams [8]
    {1.00,1.00,0.818,0.635,0.719,0.267,0.242,0.0};
 
    void updateParameters()
    {
        size_t counter = 0;
        for(auto& dl : delayLines)
        {
            dl.setFilterCutoff(filterparams[counter]);
            counter++;
        }
        size_t counter2 = 0;
        for(auto& dl : delayLines)
        {
            dl.setWetLevel(preDelayAmpParams[counter2]);
            counter2++;
            
        }
       
    }
    void updateAmount()
    {
        size_t counter3 = 0;
        for(auto& dl : delayLines)
        {
            dl.setAmount(amount);
            counter3++;
        }
        
    }
    void updateTime()
    {
        size_t counter3 = 0;
        for(auto& dl : delayLines)
        {
            dl.setDelayTime(0,preDelayParams[counter3] * delaySmooth.getNextValue());
            
            counter3++;
            
        }
        
    }
    
};
