/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EhfaAudioProcessorEditor::EhfaAudioProcessorEditor (EhfaAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(450, 559);

	addAndMakeVisible(frequencySlider);
	frequencySlider.setRange(50, 5000.0);
	frequencySlider.setTextValueSuffix(" Hz");
	frequencySlider.addListener(this);

	addAndMakeVisible(onButton);
	onButton.setAlpha(0);
	juce::Rectangle<int> buttonBounds = onButton.getBounds();
	buttonBounds.setPosition(200, 372);
	buttonBounds.setBottom(420);
	buttonBounds.setRight(252);
	onButton.setBounds(buttonBounds);
	onButton.setButtonText("Hola");
	onButton.addListener(this);

	File back = File("C:\\Users\\IceCreamTaco\\Documents\\SMC\\Schematics\\ehfa(400).png");
	File onF = File("C:\\Users\\IceCreamTaco\\Documents\\SMC\\Schematics\\ehfa(OFF).png");
	background = ImageCache::getFromFile(back);
	on = ImageCache::getFromFile(onF);
}

EhfaAudioProcessorEditor::~EhfaAudioProcessorEditor()
{
}

//==============================================================================
void EhfaAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	g.drawImageAt(background, 0, 0);
	if (!processor.isOn) {
		g.drawImageAt(on, 0, 0);
	}
}

void EhfaAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	const int sliderLeft = 120;
	frequencySlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
}

void EhfaAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	if (slider == &frequencySlider)
	{
		processor.updateAngleDelta(frequencySlider.getValue());
	}
}


void EhfaAudioProcessorEditor::buttonClicked(Button* button) {
	if (button == &onButton) {
		processor.isOn = !processor.isOn;
		repaint();
	}
}
