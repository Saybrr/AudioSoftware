/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
SynthFrameworkAudioProcessor::SynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
tree(*this,nullptr)
#endif
{   
    NormalisableRange<float> attackParam(0.1f, 5000);
    NormalisableRange<float> decayParam(0.1f, 5000);
    NormalisableRange<float> sustainParam(0.1f, 5000);
    NormalisableRange<float> releaseParam(0.1f, 5000);
    NormalisableRange<float> pitchShiftParam(-36.0f, 36.0f);
    NormalisableRange<float> gainParam(0,1);

    //params that make it possible to get/set states and automate parameters in my DAW 
    tree.createAndAddParameter("attack1", "Attack1", "Attack", attackParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("release1", "Release1", "Release", releaseParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("sustain1", "Sustain1", "Sustain", sustainParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay1", "Decay1", "Decay", decayParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("pitchshift1", "PitchShift1", "Pitch Shift", pitchShiftParam, -12, nullptr, nullptr);
    tree.createAndAddParameter("gain1", "Gain1", "Gain", gainParam, 1, nullptr, nullptr);

    tree.createAndAddParameter("attack2", "Attack2", "Attack", attackParam, 50.0f, nullptr, nullptr);
    tree.createAndAddParameter("release2", "Release2", "Release", releaseParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("sustain2", "Sustain2", "Sustain", sustainParam, 5000.0f, nullptr, nullptr);
    tree.createAndAddParameter("decay2", "Decay2", "Decay2", decayParam, 5000.0f, nullptr, nullptr);
    tree.createAndAddParameter("pitchshift2", "PitchShift2", "Pitch Shift", pitchShiftParam, -12, nullptr, nullptr);
    tree.createAndAddParameter("gain2", "Gain2", "Gain", gainParam, 1, nullptr, nullptr);
    /*
    tree.createAndAddParameter("attack3", "Attack3", "Attack", attackParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("release3", "Release3", "Release", releaseParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("sustain3", "Sustain3", "Sustain", sustainParam,0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay3", "Decay3", "Decay", decayParam, 0.1f, nullptr, nullptr);

    tree.createAndAddParameter("attack4", "Attack4", "Attack4", attackParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("release4", "Release4", "Release", releaseParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("sustain4", "Sustain4", "Sustain", sustainParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay4", "Decay4", "Decay", decayParam, 0.1f, nullptr, nullptr);*/
    
    //combobox select indexes from 1, but valueTree indexes from 0,
    //need to normalize range
    NormalisableRange<float> wavetypeParam(0, 4);
    tree.createAndAddParameter("wavetype1", "Wavetype1", "Wave Type", wavetypeParam, 0, nullptr, nullptr);
    tree.createAndAddParameter("wavetype2", "Wavetype2", "Wave Type", wavetypeParam, 0, nullptr, nullptr);
    //tree.createAndAddParameter("wavetype3", "Wavetype3", "Wave Type", wavetypeParam, 0, nullptr, nullptr);
    //tree.createAndAddParameter("wavetype4", "Wavetype4", "Wave Type", wavetypeParam, 0, nullptr, nullptr);*/

    tree.state = ValueTree("theTree");

    //create 5 voices
    mySynth.clearVoices();
    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

SynthFrameworkAudioProcessor::~SynthFrameworkAudioProcessor()
{
}

//==============================================================================
const String SynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    //safeguarding incase samplerate is changed mid playback? 
    lastSampleRate = sampleRate; 
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}   

void SynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SynthFrameworkAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0l; i < mySynth.getNumVoices(); i++) {
        //VOICE1
        //TODO: add num argument to ADSR, OSCTYPE to determine which
        //maxiosc and env to change 
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
            myVoice->getADSR(0, tree.getRawParameterValue("attack1"),
                tree.getRawParameterValue("decay1"),
                tree.getRawParameterValue("sustain1"),
                tree.getRawParameterValue("release1"));

            myVoice->getOscType(0, tree.getRawParameterValue("wavetype1"), 
                     tree.getRawParameterValue("pitchshift1"),
                     tree.getRawParameterValue("gain1"));
        }
        //VOICE2
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
            myVoice->getADSR(1, tree.getRawParameterValue("attack2"),
                tree.getRawParameterValue("decay2"),
                tree.getRawParameterValue("sustain2"),
                tree.getRawParameterValue("release2"));

            myVoice->getOscType(1, tree.getRawParameterValue("wavetype2"), 
                    tree.getRawParameterValue("pitchshift2"),
                    tree.getRawParameterValue("gain2"));
        }
        ////VOICE3
        //if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
        //    myVoice->getADSR(tree.getRawParameterValue("attack3"),
        //        tree.getRawParameterValue("decay3"),
        //        tree.getRawParameterValue("sustain3"),
        //        tree.getRawParameterValue("release3"));

        //    myVoice->getOscType(tree.getRawParameterValue("wavetype3"));
        ////VOICE4
        //if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
        //    myVoice->getADSR(tree.getRawParameterValue("attack4"),
        //        tree.getRawParameterValue("decay4"),
        //        tree.getRawParameterValue("sustain4"),
        //        tree.getRawParameterValue("release4"));

        //    myVoice->getOscType(tree.getRawParameterValue("wavetype4"));

      
    }
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

    //    // ..do something to the data...
    //}
}

//==============================================================================
bool SynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthFrameworkAudioProcessor::createEditor()
{
    return new SynthFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void SynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameworkAudioProcessor();
}
