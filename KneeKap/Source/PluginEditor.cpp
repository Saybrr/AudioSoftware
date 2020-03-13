/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-60.0f, 0.0f, 0.01f);
    gainSlider.setValue(-20.0f);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider); 


    delaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    delaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    delaySlider.setRange(0.0f, 1000.0f, 1.0f);
    delaySlider.setValue(0.0f);
    delaySlider.addListener(this);
    addAndMakeVisible(delaySlider);

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));


}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    gainSlider.setBounds(getLocalBounds());
    delaySlider.setBounds(getWidth() / 2 + 100, getHeight() / 2 - 100, 100, getHeight() - 100);
}

void NewProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &gainSlider) {
        processor.rawVolume = gainSlider.getValue();
    }

    if (slider = &delaySlider) {
        processor.mDelayTime = delaySlider.getValue();
    }
}