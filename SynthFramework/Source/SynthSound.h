/*
  ==============================================================================

    SynthSound.h
    Created: 13 Feb 2020 8:59:22pm
    Author:  Juno

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound 
{
public: 
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true; 
    }

    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};
