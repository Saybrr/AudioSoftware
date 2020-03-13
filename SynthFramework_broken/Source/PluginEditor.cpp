/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI_1 (p,"1"), envGui_1 (p, "1"), oscGUI_2(p, "2"), envGui_2(p, "2"),
    oscGUI_3(p,"3"), envGui_3(p, "3"), oscGUI_4(p, "4"), envGui_4(p, "4")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);



    //oscGUI will be a child of pluginEditor
    addAndMakeVisible(&oscGUI_1);
    addAndMakeVisible(&envGui_1);
    addAndMakeVisible(&oscGUI_2);
    addAndMakeVisible(&envGui_2);
    /*addAndMakeVisible(&oscGUI_3);
    addAndMakeVisible(&envGui_3);
    addAndMakeVisible(&oscGUI_4);
    addAndMakeVisible(&envGui_4);*/

}   
SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));


  
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    //constants for osc components 
    const int componentWidth = 200;
    const int componentHeight = 200;
    const int offset = 10;

    //rectangle with the same dimentions as whole plugins
    juce::Rectangle<int> area = getLocalBounds();
    

    //im gonna want to put 4 oscs in here 
    oscGUI_1.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui_1.setBounds(area.removeFromTop(componentHeight));
    oscGUI_2.setBounds(area.getX() - componentWidth, area.getY(), componentWidth, componentHeight);
    envGui_2.setBounds(area.getX(), area.getY() + offset, area.getWidth(), componentHeight);
    oscGUI_3.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui_3.setBounds(area.removeFromTop(componentHeight));
    oscGUI_4.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGui_4.setBounds(area.removeFromTop(componentHeight));

    
}

