///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "BSCDialog.h"

///////////////////////////////////////////////////////////////////////////

BrightnessSaturationContrastDialog::BrightnessSaturationContrastDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,150 ), wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );

	m_BrightnessText = new wxStaticText( this, wxID_ANY, wxT("Brightness"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_BrightnessText->Wrap( -1 );
	gSizer1->Add( m_BrightnessText, 0, wxALL|wxEXPAND, 5 );

	m_SaturationText = new wxStaticText( this, wxID_ANY, wxT("Saturation"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_SaturationText->Wrap( -1 );
	gSizer1->Add( m_SaturationText, 0, wxEXPAND|wxALL, 5 );

	m_ContrastText = new wxStaticText( this, wxID_ANY, wxT("Contrast"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_ContrastText->Wrap( -1 );
	gSizer1->Add( m_ContrastText, 0, wxALL|wxEXPAND, 5 );


	bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 3, 0, 0 );

	m_BrightnessScrollBar = new wxSlider( this, wxID_ANY, 256, 0, 512, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gSizer2->Add( m_BrightnessScrollBar, 0, wxALL|wxEXPAND, 5 );

	m_SaturationScrollBar = new wxSlider( this, wxID_ANY, 256, 0, 512, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gSizer2->Add( m_SaturationScrollBar, 0, wxALL|wxEXPAND, 5 );

	m_ContrastScrollBar = new wxSlider( this, wxID_ANY, 256, 0, 512, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gSizer2->Add( m_ContrastScrollBar, 0, wxALL|wxEXPAND, 5 );


	bSizer1->Add( gSizer2, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 6, 0, 0 );

	m_BrightnessSetOnEnter = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -100, 100, 0 );
	gSizer3->Add( m_BrightnessSetOnEnter, 0, wxALL|wxEXPAND, 5 );

	m_BrightnessResetButton = new wxButton( this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_BrightnessResetButton, 0, wxALL|wxEXPAND, 5 );

	m_SaturationSetOnEnter = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -100, 100, -100 );
	gSizer3->Add( m_SaturationSetOnEnter, 0, wxALL|wxEXPAND, 5 );

	m_SaturationResetButton = new wxButton( this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_SaturationResetButton, 0, wxALL|wxEXPAND, 5 );

	m_ContrastSetOnEnter = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -100, 100, -100 );
	gSizer3->Add( m_ContrastSetOnEnter, 0, wxALL|wxEXPAND, 5 );

	m_ContrastResetButton = new wxButton( this, wxID_ANY, wxT("RESET"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( m_ContrastResetButton, 0, wxALL|wxEXPAND, 5 );


	bSizer1->Add( gSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_BrightnessSetOnEnter->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrightnessSaturationContrastDialog::OnSpinBrightness ), NULL, this );
	m_BrightnessResetButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrightnessSaturationContrastDialog::BrightnessReset ), NULL, this );
	m_SaturationSetOnEnter->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrightnessSaturationContrastDialog::OnSpinSaturation ), NULL, this );
	m_SaturationResetButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrightnessSaturationContrastDialog::SaturationReset ), NULL, this );
	m_ContrastSetOnEnter->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrightnessSaturationContrastDialog::OnSpinContrast ), NULL, this );
	m_ContrastResetButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrightnessSaturationContrastDialog::ContrastReset ), NULL, this );
}

BrightnessSaturationContrastDialog::~BrightnessSaturationContrastDialog()
{
	// Disconnect Events
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_BrightnessScrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingBrightness ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_SaturationScrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingSaturation ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_ContrastScrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( BrightnessSaturationContrastDialog::OnScrollingContrast ), NULL, this );
	m_BrightnessSetOnEnter->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrightnessSaturationContrastDialog::OnSpinBrightness ), NULL, this );
	m_BrightnessResetButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrightnessSaturationContrastDialog::BrightnessReset ), NULL, this );
	m_SaturationSetOnEnter->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrightnessSaturationContrastDialog::OnSpinSaturation ), NULL, this );
	m_SaturationResetButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrightnessSaturationContrastDialog::SaturationReset ), NULL, this );
	m_ContrastSetOnEnter->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( BrightnessSaturationContrastDialog::OnSpinContrast ), NULL, this );
	m_ContrastResetButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BrightnessSaturationContrastDialog::ContrastReset ), NULL, this );

}
