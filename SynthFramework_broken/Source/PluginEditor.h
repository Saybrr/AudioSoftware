/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscilator.h"
#include "Envelope.h"

//==============================================================================
/**
*/
class SynthFrameworkAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor&);
    ~SynthFrameworkAudioProcessorEditor();
 
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
   

    vector <Slider> adsr_sliders;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    
    Oscilator oscGUI_1;
    Envelope envGui_1;
    Oscilator oscGUI_2;
    Envelope envGui_2;
    Oscilator oscGUI_3;
    Envelope envGui_3;
    Oscilator oscGUI_4;
    Envelope envGui_4;

    SynthFrameworkAudioProcessor& processor;




    OwnedArray<Component> components;
    template <typename ComponentType>
    ComponentType* addToButtonList(ComponentType* newComp)
    {
        components.add(newComp);
        addAndMakeVisible(newComp);
        return newComp;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFrameworkAudioProcessorEditor)
};
