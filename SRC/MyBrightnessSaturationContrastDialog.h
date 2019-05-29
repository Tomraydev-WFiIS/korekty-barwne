#pragma once
#include "BSCDialog.h"
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>



class MyBrightnessSaturationContrastDialog : public BrightnessSaturationContrastDialog {
protected:
	// Scroll bars
	virtual void OnScrollingBrightness(wxScrollEvent& event);
	virtual void OnScrollingSaturation(wxScrollEvent& event);
	virtual void OnScrollingContrast(wxScrollEvent& event);

	// Reset buttons
	virtual void BrightnessReset(wxCommandEvent& event);
	virtual void SaturationReset(wxCommandEvent& event);
	virtual void ContrastReset(wxCommandEvent& event);

	// Spin controls
	virtual void OnSpinBrightness(wxSpinEvent& event);
	virtual void OnSpinSaturation(wxSpinEvent& event);
	virtual void OnSpinContrast(wxSpinEvent& event);

	int brightnessValue;
	int saturationValue;
	int contrastValue;

public:
	MyBrightnessSaturationContrastDialog(wxWindow* parent) : BrightnessSaturationContrastDialog(parent) {
		brightnessValue = 256;
		saturationValue = 256;
		contrastValue = 256;
	}

};