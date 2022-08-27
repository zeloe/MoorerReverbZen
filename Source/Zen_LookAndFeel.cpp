/*
  ==============================================================================

    Zen_LookAndFeel.cpp
    Created: 22 Feb 2022 7:39:26pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#include "Zen_LookAndFeel.h"
namespace juce
{
Zen_GreenKnob::Zen_GreenKnob()
{
}

Zen_GreenKnob::~Zen_GreenKnob()
{
}
void Zen_GreenKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto color =  juce::Colours::green;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::black);
    g.fillPath (p);
}
Zen_RedKnob::Zen_RedKnob()
{
}

Zen_RedKnob::~Zen_RedKnob()
{
}
void Zen_RedKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
        
    auto color =  juce::Colours::red;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::black);
    g.fillPath (p);
}
Zen_BlueKnob::Zen_BlueKnob()
{
}

Zen_BlueKnob::~Zen_BlueKnob()
{
}
void Zen_BlueKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
        
    auto color =  juce::Colours::blue;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::black);
    g.fillPath (p);
}

Zen_WhiteKnob::Zen_WhiteKnob()
{
}

Zen_WhiteKnob::~Zen_WhiteKnob()
{
}
void Zen_WhiteKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto color =  juce::Colours::white;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::black);
    g.fillPath (p);
}


Zen_BrownKnob::Zen_BrownKnob()
{
}

Zen_BrownKnob::~Zen_BrownKnob()
{
}
void Zen_BrownKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
        
    auto color =  juce::Colours::brown;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::black);
    g.fillPath (p);
}


Zen_LightBlueKnob::Zen_LightBlueKnob()
{
}

Zen_LightBlueKnob::~Zen_LightBlueKnob()
{
}
void Zen_LightBlueKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    
    auto color =  juce::Colours::lightblue;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::black);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::black);
    g.fillPath (p);

       
    }
    
}
juce::Zen_BlackKnob::Zen_BlackKnob()
{
}

juce::Zen_BlackKnob::~Zen_BlackKnob()
{
}
void juce::Zen_BlackKnob::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                   const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    
    auto color =  juce::Colours::black;
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
            auto centreX = (float) x + (float) width  * 0.5f;
            auto centreY = (float) y + (float) height * 0.5f;
            auto rx = centreX - radius;
            auto ry = centreY - radius;
            auto rw = radius * 2.0f;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour (color);
    g.fillEllipse (rx, ry, rw, rw);
    // fill
  
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::white);
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
 
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
            
     
    // pointer
    g.setColour (juce::Colours::white);
    g.fillPath (p);

    
}
