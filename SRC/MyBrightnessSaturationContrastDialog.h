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

	bool resetBrightness = false,
			wasLastKeyResetBrightness = false,
			resetSaturation = false,
			wasLastKeyResetSaturation = false,
			resetContrast = false,
			wasLastKeyResetContrast = false;

public:
	MyBrightnessSaturationContrastDialog(wxWindow* parent) : BrightnessSaturationContrastDialog(parent) {
		brightnessValue = 256;
		saturationValue = 256;
		contrastValue   = 256;
	}

	virtual int getBrightness() const { return brightnessValue; }
	virtual int getMinBrightness() const { return m_BrightnessScrollBar->GetMin(); }
	virtual int getMaxBrightness() const { return m_BrightnessScrollBar->GetMax(); }

	virtual int getSaturation() const { return saturationValue; }
	virtual int getMinSaturation() const { return m_SaturationScrollBar->GetMin(); }
	virtual int getMaxSaturation() const { return m_SaturationScrollBar->GetMax(); }

	virtual int getContrast()   const { return contrastValue; }
	virtual int getMinContrast() const { return m_ContrastScrollBar->GetMin(); }
	virtual int getMaxContrast() const { return m_ContrastScrollBar->GetMax(); }


};