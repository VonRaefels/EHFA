/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/

class EhfaAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EhfaAudioProcessor();
    ~EhfaAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void updateAngleDelta(double shift, double fine);
	void setMix(float mix);

	double currentAngle, angleDelta;
	float l1, l2;
	float o1, o2;
	float b1 = 0.05, b2 = 0, b3 = -0.0475;
	float a1 = 1.0, a2 = -1.9, a3 = 0.9025;

	AudioParameterFloat* shiftParameter;
	AudioParameterFloat* mixParameter;
	AudioParameterBool* onParameter;
	AudioParameterBool* filterOnParameter;

	const double DEFAULT_FREQ = 5050;
	const double DEFAULT_MIX = 50;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EhfaAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
