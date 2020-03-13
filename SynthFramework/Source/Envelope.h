/*
  ==============================================================================

    Envelope.h
    Created: 24 Feb 2020 9:00:04pm
    Author:  Helazo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope    : public Component, Slider::Listener
{
public:
    Envelope(SynthFrameworkAudioProcessor&, string num);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameworkAudioProcessor& processor;

    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;

    Slider gainSlider;
    Label gainLabel;

    Label attackLabel;
    Label decayLabel;
    Label sustainLabel;
    Label releaseLabel;

    Slider pitchShiftSlider;
    Label pitchShiftLabel;

    

    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> oscTypeTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> pitchShiftTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> gainTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
