/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Zen_Knob.h"
//==============================================================================
/**
*/
class MoorerReverbZenAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MoorerReverbZenAudioProcessorEditor (MoorerReverbZenAudioProcessor&);
    ~MoorerReverbZenAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
   
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MoorerReverbZenAudioProcessor& audioProcessor;
   
    juce::Zen_Knob erKnob,erTimeknob, resonancesKnob, resonancesTimeKnob, lateReflectionsKnob, lateReflectionsTimeKnob;
    using APVTS = juce::AudioProcessorValueTreeState;
            using Attachment = APVTS::SliderAttachment;
        Attachment erAttachment, erTimeAttachment, resoancesAttachment, resoancesTimeAttachment,lateReflectionsAttachment, lateReflectionsTimeAttachment;
   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoorerReverbZenAudioProcessorEditor)
};
