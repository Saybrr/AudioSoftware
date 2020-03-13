/*
  ==============================================================================

    SynthVoice.h
    Created: 13 Feb 2020 9:27:01pm
    Author:  Helazo

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"
class SynthVoice : public SynthesiserVoice {
public: 
    
     bool canPlaySound(SynthesiserSound* sound) 
    {
        //cant play if there is no voice object
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
     //==============================================================================
     static double noteHz(int midiNoteNumber, double centsOffset)
         //By Joshua Hodge
     {
         double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
         hertz *= std::pow(2.0, centsOffset / 1200);
         return hertz;
     }

     //==============================================================================
     void getOscType(int num,atomic<float>* selection, atomic<float>* pshift, atomic<float>* gain)
     {
         operators[num].oscChoice = static_cast<int>(*selection);
         operators[num].pitchShift = static_cast<int>(*pshift);
         operators[num].level = static_cast<int>(*gain);
     }
     //==============================================================================
     double setOscType(int num)
     {
         double sample1, sample2, sample3, sample4;
         double sFreq1, sFreq2;
         sFreq1= operators[0].frequency;
         sFreq2 = operators[1].frequency;
         switch (operators[0].oscChoice)
         {
         case 0:
             sample1 = operators[0].osc.sinewave(sFreq1);
             break;
         case 1:
             sample1 = operators[0].osc.triangle(sFreq1);
             break;
         case 2:
             sample1 = operators[0].osc.saw(sFreq1);
             break;
         case 3:
             sample1 = operators[0].osc.square(sFreq1);
             break;
         default:
             sample1 = operators[0].osc.sinewave(sFreq1);
             break;
         }

         switch (operators[1].oscChoice)
         {
         case 0:
             sample2 = operators[1].osc.sinewave(sFreq2);
             break;
         case 1:
             sample2 = operators[1].osc.triangle(sFreq2);
             break;
         case 2:
             sample2 = operators[1].osc.saw(sFreq2);
             break;
         case 3:
             sample2 = operators[1].osc.square(sFreq2);
             break;
         default:
             sample2 = operators[1].osc.sinewave(sFreq2);
             break;
         }

         return sample1 + sample2;
         //return product of all oscs??? 

          //if serial
         // 1 = wave(freq)
          //2 = 1*wave(2freq)
         //3 = 2*wave(3freq)
         //4 = 3*wave(4freq) ????? 

     }
     
     //==============================================================================

     void getADSR(int num, std::atomic<float>* attack, atomic<float>* decay, 
                        atomic<float>* sustain, atomic<float>* release)
         //get asdr params from sliders, write them to maxiEnv
     {

         operators[num].env.setAttack(static_cast<double>(*attack));
         operators[num].env.setDecay(static_cast<double>(*decay));
         operators[num].env.setSustain(static_cast<double>(*sustain));
         operators[num].env.setRelease(static_cast<double>(*release));
     }
    //==============================================================================
     double setADSR(int num) 
         //sets ASDR and driggers env
     {
         return operators[num].env.adsr(setOscType(num), operators[num].env.trigger);
     }

    //============================================================================== 
     void getFilterParams(int num, float* fType, float* fCutoff, float* fRes)
         //get filter params from sliders, to be used in setFilter
     {
         operators[num].filterChoice = *fType;
         operators[num].cutoff = *fCutoff;
         operators[num].resonance = *fRes;
     }

    //==============================================================================

     void startNote(int midiNoteNumber, float velocity, 
                              SynthesiserSound* sound, int currentPitchWheelPosition)
     {
         for (int i = 0; i < operators.size(); i++) {
            operators[i].env.trigger = 1;
            operators[i].level = velocity;
            //pitchbend in cents = semitones x 100
            operators[i].frequency = noteHz(midiNoteNumber, operators[i].pitchShift * 100) ;
         }
         
        //std::cout << midiNoteNumber << std::endl;
     }
    //==============================================================================  

     void stopNote(float velocity, bool allowTailOff) override
     {   
         //clear stoppped notes to be used for the next played notes
         //used to maintain polyphony
         for (int i = 0; i < operators.size(); i++) {
             operators[i].env.trigger = 0;
             allowTailOff = true;

             if (velocity == 0)
                 clearCurrentNote();
         }
         
       
     }
        
    //==============================================================================  

     void 	pitchWheelMoved(int newPitchWheelValue)
    {
        
    }
       
    //==============================================================================  

     void 	controllerMoved(int controllerNumber, int newControllerValue)
    {

    }
      
    //==============================================================================  

     void 	renderNextBlock(AudioBuffer< float >& outputBuffer, 
                                    int startSample, int numSamples) 
     {     
         //set ADSR for the synth
         //TODO: make knobs midi macros
         double output;
            
         for (int sample = 0; sample < numSamples; ++sample) {
         
             for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {

                 //set all params 
                 output = setADSR(0) + setADSR(1);
                 outputBuffer.addSample(channel, startSample, setADSR(0) * 0.3f);
                 outputBuffer.addSample(channel, startSample, setADSR(1) * 0.3f);
            

                 
             }
             ++startSample;
         }
     }

private: 
    //operator struct, gonna need 4 of these 
    typedef struct myOperator {
        double level;
        double frequency;

        int oscChoice;

        double filterChoice;
        double cutoff;
        double resonance;

        float gain;

        float pitchShift;

        maxiOsc osc;
        maxiEnv env;
        maxiFilter filter;
    } op;

    //vector of 4 operator structs
    //bruh moment vector initialization
    op op1, op2;
    vector<op> operators = { op1,op2 };
 
};