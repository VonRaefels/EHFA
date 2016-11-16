/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class EhfaAudioProcessorEditor  : public AudioProcessorEditor,
	public Button::Listener, public Slider::Listener
{
public:
    EhfaAudioProcessorEditor (EhfaAudioProcessor&);
    ~EhfaAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	void sliderValueChanged(Slider* slider) override;
	void buttonClicked(Button* button) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EhfaAudioProcessor& processor;
	Slider frequencySlider;
	Image background, on;
	TextButton onButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EhfaAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
