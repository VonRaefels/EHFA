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

	addAndMakeVisible(blendKnob);
	blendKnob.setRange(0, 100);
	blendKnob.setTopLeftPosition(72, 88);
	blendKnob.setSize(80, 80);

	blendKnob.setSliderStyle(Slider::Rotary);
	blendKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	blendKnob.setLookAndFeel(&knoblf);
	blendKnob.addListener(this);

	addAndMakeVisible(fineKnob);
	fineKnob.setRange(0, 1000);
	fineKnob.setTopLeftPosition(72 + 113, 88);
	fineKnob.setSize(80, 80);

	fineKnob.setSliderStyle(Slider::Rotary);
	fineKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	fineKnob.setLookAndFeel(&knoblf);
	fineKnob.addListener(this);

	addAndMakeVisible(shiftKnob);
	shiftKnob.setRange(100, 10000.0);
	shiftKnob.setTopLeftPosition(72 + 113*2, 89);
	shiftKnob.setSize(80, 80);

	shiftKnob.setSliderStyle(Slider::Rotary);
	shiftKnob.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	shiftKnob.setLookAndFeel(&knoblf);
	shiftKnob.addListener(this);

	addAndMakeVisible(onButton);
	onButton.setAlpha(0);
	juce::Rectangle<int> buttonBounds = onButton.getBounds();
	buttonBounds.setPosition(200, 372);
	buttonBounds.setBottom(420);
	buttonBounds.setRight(252);
	onButton.setBounds(buttonBounds);
	onButton.setButtonText("Hola");
	onButton.addListener(this);

	addAndMakeVisible(filterButton);
	filterButton.setAlpha(0);
	juce::Rectangle<int> buttonBounds2 = filterButton.getBounds();
	buttonBounds2.setPosition(213, 213);
	buttonBounds2.setBottom(240);
	buttonBounds2.setRight(240);
	filterButton.setBounds(buttonBounds2);
	filterButton.addListener(this);

	File back = File("C:\\Users\\IceCreamTaco\\Documents\\SMC\\Schematics\\ehfa(400).png");
	File onF = File("C:\\Users\\IceCreamTaco\\Documents\\SMC\\Schematics\\ehfa(OFF).png");
	File filterF = File("C:\\Users\\IceCreamTaco\\Documents\\SMC\\Schematics\\ehfa(400_filter).png");
	backgroundImage = ImageCache::getFromFile(back);
	onImage = ImageCache::getFromFile(onF);
	filterImage = ImageCache::getFromFile(filterF);
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
	Image bI = backgroundImage;
	if (processor.isFilterOn) {
		bI = filterImage;
	}
	g.drawImageAt(bI, 0, 0);
	if (!processor.isOn) {
		g.drawImageAt(onImage, 0, 0);
	}
}

void EhfaAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	//const int sliderLeft = 120;
	//blendKnob.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
}

void EhfaAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
	if (slider == &shiftKnob)
	{
		processor.updateAngleDelta(shiftKnob.getValue(), fineKnob.getValue());
	}

	if (slider == &fineKnob)
	{
		processor.updateAngleDelta(shiftKnob.getValue(), fineKnob.getValue());
	}

}


void EhfaAudioProcessorEditor::buttonClicked(Button* button) {
	if (button == &onButton) {
		processor.isOn = !processor.isOn;
		repaint();
	}
	if (button == &filterButton) {
		processor.isFilterOn = !processor.isFilterOn;
		repaint();
	}
}

