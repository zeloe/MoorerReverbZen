/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MoorerReverbZenAudioProcessorEditor::MoorerReverbZenAudioProcessorEditor (MoorerReverbZenAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
erKnob("Er", 0, 1, 0.1, 0),
erTimeknob("ErTime",0,1,0.1,0),
resonancesKnob("Resoances", 0,1,0.1,0),
resonancesTimeKnob("ResoancesTime", 0, 1, 0.1, 0),
lateReflectionsKnob("lateRefelctions", 0, 1, 0.1, 0),
lateReflectionsTimeKnob("lateRefelctionsTime",0,1,0.1,0),
erAttachment(audioProcessor.treeState, "er", erKnob),
erTimeAttachment(audioProcessor.treeState, "ertime", erTimeknob),
resoancesAttachment(audioProcessor.treeState, "resonances", resonancesKnob),
resoancesTimeAttachment(audioProcessor.treeState, "resonancestime", resonancesTimeKnob),
lateReflectionsAttachment(audioProcessor.treeState, "lateReflextions", lateReflectionsKnob),
lateReflectionsTimeAttachment(audioProcessor.treeState, "lateReflextionstime", lateReflectionsTimeKnob)

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(1.0);
    setResizeLimits(500, 500, 750, 750);
    erKnob.setStyles(juce::Zen_Knob::ZenStyles::blackknob);
    erKnob.setTextValueSuffix(" ER");
    erKnob.setRange(0.00f, 1.f,0.01f);
    addAndMakeVisible(&erKnob);
        
    erTimeknob.setStyles(juce::Zen_Knob::ZenStyles::blackknob);
    erTimeknob.setTextValueSuffix(" ERTime");
    erTimeknob.setRange(0.01f,1.f,0.01f);
    addAndMakeVisible(&erTimeknob);
    
    resonancesKnob.setStyles(juce::Zen_Knob::ZenStyles::blackknob);
    resonancesKnob.setTextValueSuffix(" Resonances");
    resonancesKnob.setRange(0.00f,1.f,0.01f);
    addAndMakeVisible(&resonancesKnob);
    
    resonancesTimeKnob.setStyles(juce::Zen_Knob::ZenStyles::blackknob);
    resonancesTimeKnob.setTextValueSuffix(" ResonancesTime");
    resonancesTimeKnob.setRange(0.00f,1.f,0.01f);
    addAndMakeVisible(&resonancesTimeKnob);
    
    lateReflectionsKnob.setStyles(juce::Zen_Knob::ZenStyles::blackknob);
    lateReflectionsKnob.setTextValueSuffix(" LateReflections");
    lateReflectionsKnob.setRange(00.f,1.f,0.01f);
    addAndMakeVisible(&lateReflectionsKnob);
    
    lateReflectionsTimeKnob.setStyles(juce::Zen_Knob::ZenStyles::blackknob);
    lateReflectionsTimeKnob.setTextValueSuffix(" LateReflectionsTime");
    lateReflectionsTimeKnob.setRange(00.f,1.f,0.01f);
    addAndMakeVisible(&lateReflectionsTimeKnob);
}

MoorerReverbZenAudioProcessorEditor::~MoorerReverbZenAudioProcessorEditor()
{
    
    
    

    
}

//==============================================================================
void MoorerReverbZenAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    
   
}

void MoorerReverbZenAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
        auto width = bounds.getWidth();
        auto height = bounds.getHeight();
    auto size = 2.3;
        auto offset_x =  width / 10;
        auto offset_y = height / 10 ;
  
        
        erKnob.setBounds(offset_x * 2, offset_y * 2, offset_x * size, offset_x * size);
        erTimeknob.setBounds(offset_x * 2 , offset_y * 5, offset_x * size, offset_x * size);
    resonancesKnob.setBounds(offset_x * 4, offset_y * 2, offset_x * size, offset_x * size);
    resonancesTimeKnob.setBounds(offset_x * 4,offset_y * 5,offset_x * size,offset_x * size);
    lateReflectionsKnob.setBounds(offset_x * 6,offset_y * 2,offset_x * size,offset_x * size);
    lateReflectionsTimeKnob.setBounds(offset_x * 6,offset_y *5,offset_x * size,offset_x * size);
}


