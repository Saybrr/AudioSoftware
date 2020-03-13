/*
  ==============================================================================

    Envelope.cpp
    Created: 24 Feb 2020 9:00:04pm
    Author:  Helazo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p, string num): processor(p)
{
    //setSize(200, 200);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    attackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, false);

    decaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decaySlider.setRange(0.1f, 5000.0f);
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    addAndMakeVisible(decayLabel);
    decayLabel.setText("Decay", dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, false);

    sustainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainSlider.setRange(0.1f, 5000.0f);
    sustainSlider.setValue(0.1f);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    addAndMakeVisible(sustainLabel);
    sustainLabel.setText("Sustain", dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, false);

    releaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.1f);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("release", dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, false);

    pitchShiftSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchShiftSlider.setRange(-36.0f, 36.0f);
    pitchShiftSlider.setValue(1.0f);
    pitchShiftSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
    pitchShiftSlider.addListener(this);
    addAndMakeVisible(&pitchShiftSlider);
    addAndMakeVisible(pitchShiftLabel);
    pitchShiftLabel.setText("PitchShift", dontSendNotification);
    pitchShiftLabel.attachToComponent(&pitchShiftSlider, false);

    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setRange(0.0f, 1.0f);
    gainSlider.setValue(1.0f);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 20);
    gainSlider.addListener(this);
    addAndMakeVisible(&gainSlider);
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);



    attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
        "attack" + num, attackSlider);
    sustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
        "sustain" + num, sustainSlider);
    decayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
        "decay" + num, decaySlider);
    releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
        "release" + num, releaseSlider);
    pitchShiftTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
        "pitchshift" + num, pitchShiftSlider);

    gainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
        "gain" + num, gainSlider);

}

Envelope::~Envelope()
{

}

void Envelope::paint (Graphics& g)
{

}

void Envelope::resized()
{
    //juce::Rectangle<int> area = getLocalBounds().reduced(40);
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const int sliderWidth = 50;
    const int sliderHeight = 100;

    attackSlider.setBounds(50, 100,sliderWidth,sliderHeight);
    decaySlider.setBounds(150, 100, sliderWidth,sliderHeight);
    sustainSlider.setBounds(250, 100, sliderWidth, sliderHeight);
    releaseSlider.setBounds(350, 100, sliderWidth, sliderHeight);
    pitchShiftSlider.setBounds(450, 100, sliderWidth, sliderHeight);
    gainSlider.setBounds(550, 100, sliderWidth, sliderHeight);

}
void Envelope::sliderValueChanged(Slider* slider)
{
    if (slider == &attackSlider) {
        processor.attackTime = attackSlider.getValue();
    }
    if (slider == &releaseSlider) {
        processor.releaseTime = releaseSlider.getValue();
    }
    if (slider == &decaySlider) {
        processor.decayTime = decaySlider.getValue();
    }
    if (slider == &sustainSlider) {
        processor.sustainTime = sustainSlider.getValue();
    }
    if (slider == &pitchShiftSlider) {
        processor.pitchShift = pitchShiftSlider.getValue();
    }
  

}