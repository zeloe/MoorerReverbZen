/*
  ==============================================================================

    AudioProcessor.h
    Created: 13 Aug 2022 3:22:32pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "PreDelays.h"
#include "LPCF.h"
#include "APF.h"
#include "MCF.h"
class AudioEngine
{
public:
    AudioEngine() {};
    ~AudioEngine() {};
    
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept
    {
        fxChainL.prepare(spec);
        fxChainR.prepare(spec);
    }
    void reset()
    {
        fxChainL.reset();
        fxChainR.reset();
    }
    void renderNextBlock (juce::AudioBuffer<float>& outputAudio)
    {
        //auto block = juce::dsp::AudioBlock<float> (outputAudio).getSubBlock ((size_t) startSample, (size_t) numSamples);
        juce::dsp::AudioBlock<float> block(outputAudio);
       
        auto blockL = block.getSingleChannelBlock(0);
        auto blockR = block.getSingleChannelBlock(1);
        juce::dsp::ProcessContextReplacing<float> contextL (blockL);
        fxChainL.process(contextL);
        juce::dsp::ProcessContextReplacing<float> contextR (blockR);
        fxChainR.process(contextR);
    }
    
    void updateAmount (float newValue)
    {
        fxChainL.template get<preDelayIndex>().getAmount(newValue);
        fxChainR.template get<preDelayIndex>().getAmount(newValue);
    }
    void updateReso (float newValue)
    {
        fxChainL.template get<LPCFIndex>().getReso(newValue);
        fxChainR.template get<LPCFIndex>().getReso(newValue);
    }
    void updateLateReflextions (float newValue)
    {
        fxChainL.template get<APFIndex>().getLate(newValue);
        fxChainR.template get<APFIndex>().getLate(newValue);
    }
    
    void updatepreReverbTime (float newValue)
    {
        fxChainL.template get<preDelayIndex>().getTime(newValue);
        fxChainR.template get<preDelayIndex>().getTime(newValue);
        
        
    }
    void updateresoReverbTime (float newValue)
    {
        fxChainL.template get<LPCFIndex>().getTime(newValue);
        fxChainR.template get<LPCFIndex>().getTime(newValue);
    }
    void updatelateReverbTime (float newValue)
    {
        fxChainL.template get<APFIndex>().getTime(newValue);
        fxChainR.template get<APFIndex>().getTime(newValue);
    }
   
    
private:
    enum
    {
        preDelayIndex,
        LPCFIndex,
        APFIndex
    };
    
    juce::dsp::ProcessorChain<PreDelays<float> ,LPCF<float>,  APF<float>> fxChainL;
    juce::dsp::ProcessorChain<PreDelays<float> ,LPCF<float>, APF<float>> fxChainR;  
   
    
    
};
