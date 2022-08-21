/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MoorerReverbZenAudioProcessor::MoorerReverbZenAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
,treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    treeState.addParameterListener("er", this);
    treeState.addParameterListener("ertime", this);
    treeState.addParameterListener("resonances", this);
    treeState.addParameterListener("resonancestime", this);
    treeState.addParameterListener("lateReflextions", this);
    treeState.addParameterListener("lateReflextionstime", this);
}


MoorerReverbZenAudioProcessor::~MoorerReverbZenAudioProcessor()
{
    treeState.removeParameterListener("er", this);
    treeState.removeParameterListener("ertime", this);
    treeState.removeParameterListener("resonances", this);
    treeState.removeParameterListener("resonancestime", this);
    treeState.removeParameterListener("lateReflextions", this);
    treeState.removeParameterListener("lateReflextionstime", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout
MoorerReverbZenAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    auto pEr = (std::make_unique<juce::AudioParameterFloat>("er",
                                                          "Er",0.00f,1.f,0.75f));
    auto pErTime = (std::make_unique<juce::AudioParameterFloat>("ertime",
                                                          "ErTime",0.01f,1.f,0.75f));
    auto pResonances = (std::make_unique<juce::AudioParameterFloat>("resonances",
                                                          "Resonances",0.00f,1.f,0.75f));
    auto pResonancesTime = (std::make_unique<juce::AudioParameterFloat>("resonancestime",
                                                          "ResonancesTime",0.01f,1.f,0.75f));
    auto pLateReflextions = (std::make_unique<juce::AudioParameterFloat>("lateReflextions",
                                                          "Latereflextions",0.00f,1.f,0.75f));
    auto pLateReflextionsTime = (std::make_unique<juce::AudioParameterFloat>("lateReflextionstime",
                                                          "LatereflextionsTime",0.01f,1.f,0.75f));
    
   
    
    params.push_back(std::move(pEr));
    params.push_back(std::move(pErTime));
    params.push_back(std::move(pResonances));
    params.push_back(std::move(pResonancesTime));
    params.push_back(std::move(pLateReflextions));
    params.push_back(std::move(pLateReflextionsTime));
    
    return {params.begin(),params.end()};
}

void MoorerReverbZenAudioProcessor::parameterChanged(const juce::String &paramterID, float newValue)
{
    if (paramterID == "er")
    {
        audioEngine.updateAmount(newValue);
    } else if (paramterID == "ertime")
    {
        audioEngine.updatepreReverbTime(newValue);
    } else if (paramterID == "resonances")
    {
        audioEngine.updateReso(newValue);
    } else if (paramterID == "resonancestime")
    {
        audioEngine.updateresoReverbTime(newValue);
    } else if (paramterID == "lateReflextions")
    {
        audioEngine.updateLateReflextions(newValue);
    } else if (paramterID == "lateReflextionstime")
    {
        audioEngine.updatelateReverbTime(newValue);
    }
  
}

void MoorerReverbZenAudioProcessor::updateParameters()
{
    audioEngine.updateAmount(treeState.getRawParameterValue("er")->load());
    audioEngine.updatepreReverbTime(treeState.getRawParameterValue("ertime")->load());
    audioEngine.updateReso(treeState.getRawParameterValue("resonances")->load());
    audioEngine.updateresoReverbTime(treeState.getRawParameterValue("resonancestime")->load());
    audioEngine.updateLateReflextions(treeState.getRawParameterValue("lateReflextions")->load());
    audioEngine.updatelateReverbTime(treeState.getRawParameterValue("lateReflextionstime")->load());
    
}

//==============================================================================
const juce::String MoorerReverbZenAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MoorerReverbZenAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MoorerReverbZenAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MoorerReverbZenAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MoorerReverbZenAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MoorerReverbZenAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MoorerReverbZenAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MoorerReverbZenAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MoorerReverbZenAudioProcessor::getProgramName (int index)
{
    return {};
}

void MoorerReverbZenAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MoorerReverbZenAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    audioEngine.reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = 1;
    audioEngine.prepare(spec);
    updateParameters();
    
}

void MoorerReverbZenAudioProcessor::releaseResources()
{
    audioEngine.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MoorerReverbZenAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MoorerReverbZenAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    audioEngine.renderNextBlock (buffer);
   
}

//==============================================================================
bool MoorerReverbZenAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MoorerReverbZenAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);//MoorerReverbZenAudioProcessorEditor (*this);
}

//==============================================================================
void MoorerReverbZenAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos (destData, true);
                 treeState.state.writeToStream(mos);
}

void MoorerReverbZenAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
                      if(tree.isValid() )
                      {
                          treeState.replaceState(tree);
                      }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MoorerReverbZenAudioProcessor();
}
