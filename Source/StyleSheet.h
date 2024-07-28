#pragma once

#include <JuceHeader.h>
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "MakeLogarithmicRange.h"

class RasterKnob : public juce::Slider
{
public:

	RasterKnob() : juce::Slider(SliderStyle::RotaryHorizontalVerticalDrag, TextEntryBoxPosition::NoTextBox)
	{
		setMouseCursor(MouseCursor::PointingHandCursor);
		setLookAndFeel(&mainSliderLookAndFeel);
	}

	~RasterKnob()
	{
		setLookAndFeel(nullptr);
	}

	class RasterKnobLookAndFeel : public juce::LookAndFeel_V4
	{
	public:

		RasterKnobLookAndFeel()
		{
			image = juce::ImageCache::getFromMemory(BinaryData::sliderFilmstrip_png, BinaryData::sliderFilmstrip_pngSize);
			// byImage = juce::ImageCache::getFromMemory(BinaryData::LittlePhatty_OFF_png, BinaryData::LittlePhatty_OFF_pngSize);
		}

		~RasterKnobLookAndFeel() override
		{
		}

		void drawRotarySlider(
			juce::Graphics& g,
			int x,
			int y,
			int width,
			int height,
			float sliderPosProportional,
			float /*rotaryStartAngle*/,
			float /*rotaryEndAngle*/,
			juce::Slider& /*slider*/) override
		{
			const auto frames = 129;
			const auto frameId = static_cast<int>(ceil(sliderPosProportional * (static_cast<float>(frames) - 1.0f)));

			// image is vertical strip, each frame is 1/100th of the height

			g.drawImage(image,
				x,
				y,
				width,
				height,
				0,
				frameId * image.getHeight() / frames,
				image.getWidth(),
				image.getHeight() / frames);
		}

	private:
		juce::Image image;
		juce::Image byImage;

		bool bp = false;


		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RasterKnobLookAndFeel)
	} mainSliderLookAndFeel;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RasterKnob)
};







class ChipButton : public juce::ToggleButton
{

public:
    ChipButton() : juce::ToggleButton("")
    {
        setLookAndFeel(&mainButtonLookAndFeel);
        setImage();
        juce::Typeface::Ptr customTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::osb_ttf, BinaryData::osb_ttfSize);
        customFont_ = juce::Font(customTypeface).withHeight(20.0f);
    }

    ~ChipButton()
    {
        setLookAndFeel(nullptr);
    }

    void setImage()
    {
        offImage_ = ImageCache::getFromMemory(BinaryData::Chip_png, BinaryData::Chip_pngSize);
        onImage_ = ImageCache::getFromMemory(BinaryData::Chip1_png, BinaryData::Chip1_pngSize);
    }

    void setButtonText(const juce::String &text)
    {
        buttonText_ = text;
        repaint();
    }

    void paintButton(Graphics &g, bool isMouseOver, bool isButtonDown) override
    {
        const auto frameId = static_cast<int>(getToggleState());
        const auto image = frameId ? onImage_ : offImage_;
        g.drawImage(image, getLocalBounds().toFloat());

        g.setColour(juce::Colours::white);
        g.setFont(16.0f); // Set the font size
        g.setFont(customFont_);
        g.drawText(buttonText_, getLocalBounds(), juce::Justification::centred, true); // Draw text centered in the button
    }

private:
    juce::Image offImage_;
    juce::Image onImage_;
    juce::String buttonText_;
    juce::Font customFont_;

    class ChipButtonLookAndFeel : public juce::LookAndFeel_V4{
        public :
            ChipButtonLookAndFeel(){}

        void drawTickBox(Graphics & g, Component &component,
                         float x,
                         float y,
                         float w,
                         float h,
                         bool ticked,
                         bool isEnabled,
                         bool isMouseOverButton,
                         bool isButtonDown) override{
            // Do nothing, we're not drawing a tick box
        }

        private :
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChipButtonLookAndFeel)
    } mainButtonLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChipButton)
};


class SquareChipButton : public juce::ToggleButton
{

public:
	SquareChipButton() : juce::ToggleButton("")
	{
		setLookAndFeel(&mainButtonLookAndFeel);
		setImage();
		juce::Typeface::Ptr customTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::osb_ttf, BinaryData::osb_ttfSize);
		customFont_ = juce::Font(customTypeface).withHeight(20.0f);
	}

	~SquareChipButton()
	{
		setLookAndFeel(nullptr);
	}

	void setImage()
	{
		offImage_ = ImageCache::getFromMemory(BinaryData::SquareChipOff_png, BinaryData::SquareChipOff_pngSize);
		onImage_ = ImageCache::getFromMemory(BinaryData::SquareChipOn_png, BinaryData::SquareChipOn_pngSize);
	}

	void setButtonText(const juce::String& text)
	{
		buttonText_ = text;
		repaint();
	}

	void paintButton(Graphics& g, bool isMouseOver, bool isButtonDown) override
	{
		const auto frameId = static_cast<int>(getToggleState());
		const auto image = frameId ? onImage_ : offImage_;
		g.drawImage(image, getLocalBounds().toFloat());

		g.setColour(juce::Colours::white);
		g.setFont(16.0f); // Set the font size
		g.setFont(customFont_);
		g.drawText(buttonText_, getLocalBounds(), juce::Justification::centred, true); // Draw text centered in the button
	}

private:
	juce::Image offImage_;
	juce::Image onImage_;
	juce::String buttonText_;
	juce::Font customFont_;

	class SquareChipButtonLookAndFeel : public juce::LookAndFeel_V4 {
	public:
		SquareChipButtonLookAndFeel() {}

		void drawTickBox(Graphics& g, Component& component,
			float x,
			float y,
			float w,
			float h,
			bool ticked,
			bool isEnabled,
			bool isMouseOverButton,
			bool isButtonDown) override {
			// Do nothing, we're not drawing a tick box
		}

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SquareChipButtonLookAndFeel)
	} mainButtonLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SquareChipButton)
};



class BypassButton : public juce::ToggleButton
{

public:
	BypassButton() : juce::ToggleButton("")
	{
		setLookAndFeel(&mainButtonLookAndFeel);
		setImage();
	}

	~BypassButton()
	{
		setLookAndFeel(nullptr);
	}

	void setImage()
	{
		offImage_ = ImageCache::getFromMemory(BinaryData::Toggle_png, BinaryData::Toggle_pngSize);
		onImage_ = ImageCache::getFromMemory(BinaryData::Toggle1_png, BinaryData::Toggle1_pngSize);
	}

	void paintButton(Graphics& g, bool isMouseOver, bool isButtonDown) override
	{
		const auto frameId = static_cast<int>(getToggleState());
		const auto image = frameId ? onImage_ : offImage_;
		g.drawImage(image, getLocalBounds().toFloat());


	}

private:
	juce::Image offImage_;
	juce::Image onImage_;



	class BypassButtonLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		BypassButtonLookAndFeel()
		{
		}

		void drawTickBox(Graphics& g, Component& component,
			float x,
			float y,
			float w,
			float h,
			bool ticked,
			bool isEnabled,
			bool isMouseOverButton,
			bool isButtonDown) override
		{
			// Do nothing, we're not drawing a tick box
		}

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassButtonLookAndFeel)
	} mainButtonLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BypassButton)
};


class FreezeButton : public juce::ToggleButton
{

public:
	FreezeButton() : juce::ToggleButton("")
	{
		setLookAndFeel(&mainButtonLookAndFeel);
		setImage();
	}

	~FreezeButton()
	{
		setLookAndFeel(nullptr);
	}

	void setImage()
	{
		offImage_ = ImageCache::getFromMemory(BinaryData::FreezeIconOff_png, BinaryData::FreezeIconOff_pngSize);
		onImage_ = ImageCache::getFromMemory(BinaryData::FreezeIcon_png, BinaryData::FreezeIcon_pngSize);
	}

	void paintButton(Graphics& g, bool isMouseOver, bool isButtonDown) override
	{
		const auto frameId = static_cast<int>(getToggleState());
		const auto image = frameId ? onImage_ : offImage_;
		g.drawImage(image, getLocalBounds().toFloat());


	}

private:
	juce::Image offImage_;
	juce::Image onImage_;



	class FreezeButtonLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		FreezeButtonLookAndFeel()
		{
		}

		void drawTickBox(Graphics& g, Component& component,
			float x,
			float y,
			float w,
			float h,
			bool ticked,
			bool isEnabled,
			bool isMouseOverButton,
			bool isButtonDown) override
		{
			// Do nothing, we're not drawing a tick box
		}

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FreezeButtonLookAndFeel)
	} mainButtonLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FreezeButton)
};


class GainSlider : public juce::Slider
{
public:
	GainSlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
	{
		setLookAndFeel(&mainSliderLookAndFeel);
		////setRange(-60.0f, 12.0f, 0.1f);
		// Define a logarithmic range for dB values from -60 dB to 12 dB
		//NormalisableRange<double> range = dbRange(std::pow(10.0f, -60.0f / 20.0f), std::pow(10.0f, 12.0f / 20.0f));
		//setNormalisableRange(range);
		setValue(0.0f);
		setTextValueSuffix(" dB");
		setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour::fromRGB(33, 33, 33));
		setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour::fromRGB(33, 33, 33));
		setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
		setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
	}

	~GainSlider()
	{
		setLookAndFeel(nullptr);
	}

private:

	class GainSliderLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		GainSliderLookAndFeel()
		{
			//setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::white);
			//setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::white);
			//setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
			//setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
		}

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainSliderLookAndFeel)
	} mainSliderLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainSlider)
};

class PresetButton : public juce::TextButton
{
public:
	PresetButton() : juce::TextButton("")
	{
		setLookAndFeel(&mainButtonLookAndFeel);
	}

	~PresetButton()
	{
		setLookAndFeel(nullptr);
	}

private:
	class PresetButtonLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		PresetButtonLookAndFeel()
		{
			bgColour = Colour::fromRGB(26, 27, 40);
		}
        
        Font getTextButtonFont(TextButton&, int buttonHeight) override
        {
            return juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::osb_ttf, BinaryData::osb_ttfSize)).withHeight(20.0f);
        }

		void drawButtonBackground(Graphics& g, Button& button,
			const Colour& backgroundColour,
			bool isMouseOverButton,
			bool isButtonDown) override
		{
			// draw flat background colour without any rounded borders
			g.setColour(bgColour);
			g.fillAll();
		}

	private:
		juce::Colour bgColour;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetButtonLookAndFeel)
	} mainButtonLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetButton)
};


class PresetCB : public juce::ComboBox
{
public:
	PresetCB() : juce::ComboBox("")
	{
		setLookAndFeel(&mainCBLookAndFeel);
        
	}

	~PresetCB()
	{
		setLookAndFeel(nullptr);
	}

private:
	class PresetCBLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		PresetCBLookAndFeel()
		{
			bgColour = Colour::fromRGB(26, 27, 40);
		}

        Font getComboBoxFont (ComboBox& /*box*/) override
            {
                return juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::osb_ttf, BinaryData::osb_ttfSize)).withHeight(20.0f);
            }
        
        Font getPopupMenuFont() override
            {
                return juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::osb_ttf, BinaryData::osb_ttfSize)).withHeight(20.0f);
            }
        
		void drawComboBox(Graphics& g, int width, int height, bool isButtonDown,
			int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) override
		{
			// Define corner radius

			// draw rounded background colour
			g.setColour(bgColour);
			Rectangle<float> backgroundRect(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
			g.fillAll();

			// draw the icon as white
			g.setColour(Colours::white);
			Path path;
			path.startNewSubPath(0.0f, 0.0f);
			path.lineTo(8.0f, 0.0f);
			path.lineTo(4.0f, 8.0f);
			path.closeSubPath();
			g.fillPath(path, AffineTransform::translation(width - 12.0f, (height - 8.0f) * 0.5f));
		}

		// do the same for the dropdown menu

		void drawPopupMenuBackground(Graphics& g, int width, int height) override
		{
			g.setColour(bgColour);
			g.fillAll();
		}

		void      // change the highlight colour
			drawPopupMenuItem(Graphics& g, const juce::Rectangle<int>& area,
				bool isSeparator, bool isActive,
				bool isHighlighted, bool isTicked,
				bool hasSubMenu, const String& text,
				const String& shortcutKeyText,
				const Drawable* icon, const Colour* const textColourToUse) override
		{
			if (isSeparator)
			{
				Rectangle<float> r(area.toFloat().reduced(0, 7));
				r.removeFromTop(r.getHeight() * 0.5f - 0.5f);

				g.setColour(bgColour);
				g.fillRect(r.removeFromTop(1));

				ColourGradient cg(bgColour, 0.0f, 0.0f,
					bgColour.brighter(0.1f), 0.0f, (float)area.getHeight(), false);

				g.setGradientFill(cg);
				g.fillRect(r.removeFromTop(1));
			}
			else
			{
				Rectangle<int> r(area);

				if (isHighlighted)
				{
					g.setColour(bgColour.brighter(0.1f));
					g.fillRect(r);

					g.setColour(bgColour.brighter(0.2f));
					g.drawRect(r, 1);
				}

				g.setColour(bgColour);
				g.setFont(jmin(15.0f, area.getHeight() * 0.85f));

				Rectangle<float> iconArea((float)r.removeFromLeft((r.getHeight() * 5) / 4).reduced(3).getX(),
					(float)r.getY(), (float)r.getHeight(), (float)r.getHeight());

				if (icon != nullptr)
				{
					icon->drawWithin(g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
				}
				else if (isTicked)
				{
					const Path tick(getTickShape(1.0f));
					g.setColour(Colours::white);
					g.fillPath(tick, tick.getTransformToScaleToFit(iconArea.reduced(iconArea.getWidth() / 5, 0).toFloat(), true));
				}

				if (hasSubMenu)
				{
					const auto arrowH = 0.6f * getPopupMenuFont().getHeight();

					const auto x = (float)r.removeFromRight((int)arrowH).getX();
					const auto halfH = (float)r.getCentreY();

					Path path;
					path.startNewSubPath(x, halfH - arrowH * 0.5f);
					path.lineTo(x + arrowH * 0.6f, halfH);
					path.lineTo(x, halfH + arrowH * 0.5f);

					g.strokePath(path, PathStrokeType(2.0f));
				}
				g.setColour(isHighlighted ? Colours::white : Colours::grey);
				g.setFont(getPopupMenuFont());

				g.setColour(Colours::white);
				g.drawText(text, r, Justification::centredLeft, true);
			}
		}






	private:

		juce::Colour bgColour;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetCBLookAndFeel)
	} mainCBLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetCB)
};

class ModeCB : public juce::ComboBox
{
public:
	ModeCB() : juce::ComboBox("")
	{
		setLookAndFeel(&mainCBLookAndFeel);
	}

	~ModeCB()
	{
		setLookAndFeel(nullptr);
	}

private:
	class ModeCBLookAndFeel : public juce::LookAndFeel_V4
	{
	public:
		ModeCBLookAndFeel()
		{
			strokeColour = Colour::fromRGB(147, 149, 185);
			bgColour = Colour::fromRGB(85, 87, 114);
		}

		void drawComboBox(Graphics& g, int width, int height, bool isButtonDown,
			int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) override
		{
			// Define corner radius
			float cornerRadius = 5.0f;

			// draw rounded background colour
			g.setColour(bgColour);
			Rectangle<float> backgroundRect(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
			g.fillRoundedRectangle(backgroundRect, cornerRadius);

			// draw the outline
			g.setColour(strokeColour);
			// 2.0f stroke, so draw the rectangle 1.0f bigger
			Rectangle<float> borderRect(1.0f, 1.0f, static_cast<float>(width) - 2.0f, static_cast<float>(height) - 2.0f);
			g.drawRoundedRectangle(borderRect, cornerRadius, 1.0f);


			// draw the icon as black
			g.setColour(Colours::white);
			Path path;
			path.startNewSubPath(0.0f, 0.0f);
			path.lineTo(8.0f, 0.0f);
			path.lineTo(4.0f, 8.0f);
			path.closeSubPath();
			g.fillPath(path, AffineTransform::translation(width - 16.0f, (height - 8.0f) * 0.5f));
		}

		// do the same for the dropdown menu

		void drawPopupMenuBackground(Graphics& g, int width, int height) override
		{
			g.setColour(bgColour);
			g.fillAll();
		}

		

		void      // change the highlight colour
			drawPopupMenuItem(Graphics& g, const juce::Rectangle<int>& area,
				bool isSeparator, bool isActive,
				bool isHighlighted, bool isTicked,
				bool hasSubMenu, const String& text,
				const String& shortcutKeyText,
				const Drawable* icon, const Colour* const textColourToUse) override
		{
			if (isSeparator)
			{
				Rectangle<float> r(area.toFloat().reduced(0, 7));
				r.removeFromTop(r.getHeight() * 0.5f - 0.5f);

				g.setColour(bgColour);
				g.fillRect(r.removeFromTop(1));

				ColourGradient cg(bgColour, 0.0f, 0.0f,
					bgColour.brighter(0.1f), 0.0f, (float)area.getHeight(), false);

				g.setGradientFill(cg);
				g.fillRect(r.removeFromTop(1));
			}
			else
			{
				Rectangle<int> r(area);

				if (isHighlighted)
				{
					g.setColour(bgColour.brighter(0.1f));
					g.fillRoundedRectangle(r.toFloat(), 5.0f);

					g.setColour(bgColour.brighter(0.2f));
					g.drawRoundedRectangle(r.toFloat().reduced(0.5f, 0.5f), 5.0f, 1.0f);
				}

				g.setColour(Colours::white);
				g.setFont(jmin(15.0f, area.getHeight() * 0.85f));

				Rectangle<float> iconArea((float)r.removeFromLeft((r.getHeight() * 5) / 4).reduced(3).getX(),
					(float)r.getY(), (float)r.getHeight(), (float)r.getHeight());

				if (icon != nullptr)
				{
					icon->drawWithin(g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
				}
				else if (isTicked)
				{
					const Path tick(getTickShape(1.0f));
					g.setColour(Colours::white);
					g.fillPath(tick, tick.getTransformToScaleToFit(iconArea.reduced(iconArea.getWidth() / 5, 0).toFloat(), true));
				}

				if (hasSubMenu)
				{
					const auto arrowH = 0.6f * getPopupMenuFont().getHeight();

					const auto x = (float)r.removeFromRight((int)arrowH).getX();
					const auto halfH = (float)r.getCentreY();

					Path path;
					path.startNewSubPath(x, halfH - arrowH * 0.5f);
					path.lineTo(x + arrowH * 0.6f, halfH);
					path.lineTo(x, halfH + arrowH * 0.5f);

					g.strokePath(path, PathStrokeType(2.0f));
				}
				g.setColour(isHighlighted ? Colours::white : Colours::grey);
				g.setFont(getPopupMenuFont());

				g.setColour(Colours::white);
				g.drawText(text, r, Justification::centredLeft, true);
			}
		}






	private:

		juce::Colour bgColour;
		juce::Colour strokeColour;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModeCBLookAndFeel)
	} mainCBLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModeCB)
};



class ExtLabel : public Label
{
public:
	ExtLabel() : Label("", "")
	{
		setLookAndFeel(&mainLabelLookAndFeel);
	}

	~ExtLabel()
	{
		setLookAndFeel(nullptr);
	}

	// Change the cursor to a pointing hand when hovering over the label
	void mouseEnter(const MouseEvent& event) override
	{
		setMouseCursor(MouseCursor::PointingHandCursor);
	}

	// Restore the default cursor when the mouse leaves the label
	void mouseExit(const MouseEvent& event) override
	{
		setMouseCursor(MouseCursor::NormalCursor);
	}

	// click = open link
	void mouseDown(const MouseEvent& event) override
	{
		if (event.mods.isLeftButtonDown())
		{
			URL("https://direktdsp.com").launchInDefaultBrowser();
		}
	}

private:
	struct MainLabelLookAndFeel : public LookAndFeel_V4
	{
		MainLabelLookAndFeel()
		{
		}

	private:
		juce::Colour bgColour;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLabelLookAndFeel)
	} mainLabelLookAndFeel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ExtLabel)
};
