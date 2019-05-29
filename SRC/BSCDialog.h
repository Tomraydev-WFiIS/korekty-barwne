///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class BrightnessSaturationContrastDialog
///////////////////////////////////////////////////////////////////////////////
class BrightnessSaturationContrastDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_BrightnessText;
		wxStaticText* m_SaturationText;
		wxStaticText* m_ContrastText;
		wxSlider* m_BrightnessScrollBar;
		wxSlider* m_SaturationScrollBar;
		wxSlider* m_ContrastScrollBar;
		wxSpinCtrl* m_BrightnessSetOnEnter;
		wxButton* m_BrightnessResetButton;
		wxSpinCtrl* m_SaturationSetOnEnter;
		wxButton* m_SaturationResetButton;
		wxSpinCtrl* m_ContrastSetOnEnter;
		wxButton* m_ContrastResetButton;

		// Virtual event handlers, overide them in your derived class
		virtual void OnScrollingBrightness( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScrollingSaturation( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScrollingContrast( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnSpinBrightness( wxSpinEvent& event ) { event.Skip(); }
		virtual void BrightnessReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinSaturation( wxSpinEvent& event ) { event.Skip(); }
		virtual void SaturationReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpinContrast( wxSpinEvent& event ) { event.Skip(); }
		virtual void ContrastReset( wxCommandEvent& event ) { event.Skip(); }


	public:

		BrightnessSaturationContrastDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Brightness Saturation & Contrast"), const wxPoint& pos = wxPoint( 100,600 ), const wxSize& size = wxSize( 441,135 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER );
		~BrightnessSaturationContrastDialog();

};

