/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EigenCoreAudioProcessorEditor::EigenCoreAudioProcessorEditor (EigenCoreAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    ledGreen = juce::ImageFileFormat::loadFrom(BinaryData::GreenLight_png, BinaryData::GreenLight_pngSize);
    ledOff = juce::ImageFileFormat::loadFrom(BinaryData::DarkLight_png, BinaryData::DarkLight_pngSize);
    setSize (200, 50);
}

EigenCoreAudioProcessorEditor::~EigenCoreAudioProcessorEditor()
{
}

//==============================================================================
void EigenCoreAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.drawImage(ledGreen, 10, 0, 25, 25, 0, 0, ledGreen.getWidth(), ledGreen.getHeight());
    g.drawImage(ledOff, 10 + 50, 0, 25, 25, 0, 0, ledOff.getWidth(), ledOff.getHeight());
    g.drawImage(ledOff, 10 + 50*2, 0, 25, 25, 0, 0, ledOff.getWidth(), ledOff.getHeight());
    g.drawImage(ledOff, 10 + 50*3, 0, 25, 25, 0, 0, ledOff.getWidth(), ledOff.getHeight());

    g.setColour(juce::Colours::white);
    g.setFont(12.0f);
    g.drawFittedText("Pico", 0, 25, 45, 20, juce::Justification::centred, false);
    g.drawFittedText("Tau", 50, 25, 45, 20, juce::Justification::centred, false);
    g.drawFittedText("Alpha", 50*2, 25, 45, 20, juce::Justification::centred, false);
    g.drawFittedText("Mapper", 50*3, 25, 45, 20, juce::Justification::centred, false);

}

void EigenCoreAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
