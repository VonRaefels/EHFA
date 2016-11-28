/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

Random random;

//==============================================================================
EhfaAudioProcessor::EhfaAudioProcessor()
	: onParameter(nullptr),
	filterOnParameter(nullptr),
	mixParameter(nullptr),
	shiftParameter(nullptr)
{
	random = Random();
	currentAngle = 0.0;
	angleDelta = 0.0;

	updateAngleDelta(this->DEFAULT_FREQ, 0);

	addParameter(onParameter = new AudioParameterBool("on", "On", true));
	addParameter(filterOnParameter = new AudioParameterBool("filter", "Filter On", false));
	addParameter(mixParameter = new AudioParameterFloat("mix", "Blend", 0.0f, 100.0f, 50.0f));
	addParameter(shiftParameter = new AudioParameterFloat("shift", "Shift", 100.0f, 10000.0f, 5050.0f));
}

EhfaAudioProcessor::~EhfaAudioProcessor()
{
	delete &random;
}

//==============================================================================
const String EhfaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EhfaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EhfaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double EhfaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EhfaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EhfaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EhfaAudioProcessor::setCurrentProgram (int index)
{
}

const String EhfaAudioProcessor::getProgramName (int index)
{
    return String();
}

void EhfaAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EhfaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	updateAngleDelta(0, 0);
	l1 = 0;
	l2 = 0;
	o1 = 0;
	o2 = 0;
}

void EhfaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EhfaAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void EhfaAudioProcessor::updateAngleDelta(double shift, double fine)
{
	const double cyclesPerSample = (shift + fine) / getSampleRate();
	angleDelta = cyclesPerSample * 2.0 * double_Pi;                                
}

void EhfaAudioProcessor::setMix(float mix) {
	*mixParameter = mix;
}

void EhfaAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if (!*onParameter)
		return;

	AudioSampleBuffer output = AudioSampleBuffer();
	output.makeCopyOf(buffer, true);

	const float level = 0.075f;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	int numSamples = buffer.getNumSamples();
	int startSample = 0;

	while (--numSamples >= 0)
    {
        const float currentSample = (float) (sin(currentAngle) * level);

		for (int i = totalNumOutputChannels; --i >= 0;) {
			float input = buffer.getSample(i, startSample);
			float ring = input*currentSample;

			float x1, x2 = l1, x3 = l2;
			float y2 = o1, y3 = o2;
			x1 = ring;
			float y = ring;

			if (*filterOnParameter) {
				y = b1*x1 + b2*x2 + b3*x3 - a2*y2 - a3*y3;
			}

			l1 = x1;
			l2 = x2;
			o1 = y;
			o2 = y2;

			float out = ((*mixParameter)*y + (100 - (*mixParameter))*input) / 100;
			buffer.addSample(i, startSample, out);
		}

        currentAngle += angleDelta;
        ++startSample;
    }
}

//==============================================================================
bool EhfaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EhfaAudioProcessor::createEditor()
{
    return new EhfaAudioProcessorEditor (*this);
}

//==============================================================================
void EhfaAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EhfaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EhfaAudioProcessor();
}
