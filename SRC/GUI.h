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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/grid.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI
///////////////////////////////////////////////////////////////////////////////
class GUI : public wxFrame
{
	private:

	protected:

		//Hexagon
		//wxPanel * m_panel_hexagon;
		wxBoxSizer* m_panel_hexagon_sizer;
		//////////////////////////////////

		wxMenuBar* m_menuBarTop;
		wxMenu* m_menuFile;
		wxMenu* m_menuView;
		wxScrolledWindow* m_scrolledWindow1;
		wxScrolledWindow* m_scrolledWindow2;
		wxNotebook* m_notebook1;
		wxPanel* m_panel_hexagon;
		wxNotebook* m_notebook3;
		wxPanel* m_panel_hexagon_color;
		wxPanel* m_panel_hexagon_mod;
		wxPanel* m_panel_histograms;
		wxNotebook* m_notebook4;
		wxPanel* m_panel_hist_old;
		wxPanel* m_panel_hist_new;
		wxButton* m_buttonHistogram;
		wxPanel* m_panel_convolutions;
		wxGrid* m_grid3;
		wxStatusBar* m_statusBar1;

		// Virtual event handlers, overide them in your derived class
		virtual void GUIOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_fileOpenOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_fileSaveAsOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_ViewStatusBarOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_ViewBrightnessSaturationContrastWindowOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_scrolledWindow1OnLeftDClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void m_buttonHistogramOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUI();

};

