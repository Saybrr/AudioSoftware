/*
  ==============================================================================

    Oscilator.cpp
    Created: 24 Feb 2020 5:42:17pm
    Author:  Helazo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscilator.h"

//==============================================================================
Oscilator::Oscilator(SynthFrameworkAudioProcessor& p, string num) : 
    processor(p)
{
    setSize(200, 200);
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Triangle", 2);
    oscMenu.addItem("Sawtooth", 3);
    oscMenu.addItem("Square", 4);
    oscMenu.addItem("Noise", 5);

    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    oscMenu.setJustificationType(Justification::centred);

    //connect wave selection with combobox menu
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype" + num, oscMenu);


}

Oscilator::~Oscilator()
{
}

void Oscilator::paint (Graphics& g)
{
    
}

void Oscilator::resized()
{
    //shrink the bounds of the rectangle by 40 pixels from 200x200
    //as set in the constructor
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    //draw menu 20 px down from reduced center
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscilator::comboBoxChanged(ComboBox* box) 
{
    //DO NOTHING
}