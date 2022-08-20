/*
  ==============================================================================

    LPCF.h
    Created: 13 Aug 2022 3:48:41pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "FFeedbackCombDelay.h"
template <typename Type>
class LPCF
{
public:
    LPCF(){};
    ~LPCF(){};
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        delaySmooth.reset(spec.sampleRate,0.00001f);
        for(auto& dl : delayLines)
        {
            dl.prepare(spec);
        }
        updateParameters();
        updateReso();
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
    void getReso (Type newValue)
    {
        amount = newValue;
        updateReso();
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
    std::array<FFeedbackCombDelay<Type>, 18> delayLines ;
    const float fbcfdelaytime [18]
    {
        0.0043, 0.0215, 0.0255,
        0.0268, 0.0270, 0.0298,
        0.0458, 0.0485, 0.0572,
        0.0587, 0.0595, 0.0612,
        0.0707, 0.0708, 0.0726,
        0.0741, 0.0753, 0.0797
    };
    
    const float fbcfampscale[18]
    {
        0.841, 0.504, 0.491,
        0.379, 0.380, 0.346,
        0.289, 0.272,0.192,
        0.193, 0.217, 0.181,
        0.180, 0.181, 0.176,
        0.142, 0.167, 0.134
        
    };
    
    void updateParameters()
    {
        
        size_t counter1 = 0;
        for(auto& dl : delayLines)
        {
            dl.setWetLevel(fbcfampscale[counter1]);
            counter1++;
        }
        
    }
    void updateReso()
    {
        size_t counter = 0;
        for(auto& dl : delayLines)
        {
            dl.setReso(amount);
            counter++;
        }
        
    }
    void updateTime()
    {
        size_t counter1 = 0;
        for(auto& dl : delayLines)
        {
            dl.setDelayTime(0,fbcfdelaytime[counter1] * delaySmooth.getNextValue());
            counter1++;
        }
        
        
    }
    
};
