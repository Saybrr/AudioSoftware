/*
  ==============================================================================

    Oscilator.h
    Created: 24 Feb 2020 5:42:17pm
    Author:  Helazo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscilator : public Component,
                  private ComboBox::Listener
{
public:
    Oscilator(SynthFrameworkAudioProcessor&, string num);
    ~Oscilator();

    void paint (Graphics&) override;
    void resized() override;
    
    //pure virtual function mandated by ComboBoxListener,
    //not actually used as the osc type will be passed by the value
    //state tree instead of this method?? 
    void comboBoxChanged(ComboBox*) override;

    

private:
    ComboBox oscMenu;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameworkAudioProcessor& processor;
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscilator)
};
