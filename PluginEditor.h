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
class KnobLF : public juce::LookAndFeel_V3
{
public:
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) 
	{
		const float radius = jmin(width / 2, height / 2) - 4.0f;
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// fill
		//g.setColour(Colours::orange);
		//g.fillEllipse(rx, ry, rw, rw);

		// outline
		//g.setColour(Colours::red);
		//g.drawEllipse(rx, ry, rw, rw, 1.0f);

		Path p;
		const float pointerLength = radius * 0.5f;
		const float pointerThickness = 3.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius + 7, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

		// pointer
		g.setColour(Colours::slategrey);
		g.fillPath(p);
	}
};

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
	Slider blendKnob, fineKnob, shiftKnob;
	Image backgroundImage, onImage, filterImage;
	TextButton onButton, filterButton;
	KnobLF knoblf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EhfaAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
