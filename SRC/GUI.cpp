///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

GUI::GUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menuBarTop = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_fileOpen;
	m_fileOpen = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Open...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_fileOpen );

	wxMenuItem* m_fileSaveAs;
	m_fileSaveAs = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Save as...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_fileSaveAs );

	m_menuBarTop->Append( m_menuFile, wxT("File") );

	m_menuView = new wxMenu();
	wxMenuItem* m_ViewStatusBar;
	m_ViewStatusBar = new wxMenuItem( m_menuView, wxID_ANY, wxString( wxT("Status Bar") ) , wxEmptyString, wxITEM_CHECK );
	m_menuView->Append( m_ViewStatusBar );
	m_ViewStatusBar->Check( true );

	wxMenuItem* m_ViewBrightnessSaturationContrastWindow;
	m_ViewBrightnessSaturationContrastWindow = new wxMenuItem( m_menuView, wxID_ANY, wxString( wxT("Brightness, Saturation, Contrast") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuView->Append( m_ViewBrightnessSaturationContrastWindow );

	m_menuBarTop->Append( m_menuView, wxT("View") );

	this->SetMenuBar( m_menuBarTop );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 1, 0, 0 );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	gSizer1->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( gSizer1, 3, wxEXPAND, 5 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 1, 1, 0, 0 );

	m_scrolledWindow2 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	gSizer2->Add( m_scrolledWindow2, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( gSizer2, 3, wxEXPAND, 5 );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 1, 0, 0 );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel_hexagon = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel_hexagon, wxT("Hexagon"), true );
	m_panel_histograms = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_notebook4 = new wxNotebook( m_panel_histograms, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel_hist_old = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxSize( 256,-1 ), wxTAB_TRAVERSAL );
	m_notebook4->AddPage( m_panel_hist_old, wxT("Old"), false );
	m_panel_hist_new = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxSize( 256,-1 ), wxTAB_TRAVERSAL );
	m_notebook4->AddPage( m_panel_hist_new, wxT("New"), false );

	bSizer2->Add( m_notebook4, 1, wxEXPAND | wxALL, 5 );

	m_buttonHistogram = new wxButton( m_panel_histograms, wxID_ANY, wxT("Generate Histograms"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_buttonHistogram, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	///////////////////// Hexagon /////////////////////////
	m_panel_hexagon_sizer = new wxBoxSizer(wxVERTICAL);
	m_panel_hexagon->SetSizer(m_panel_hexagon_sizer);
	////////////////////////////////////////////////////////


	m_panel_histograms->SetSizer( bSizer2 );
	m_panel_histograms->Layout();
	bSizer2->Fit( m_panel_histograms );
	m_notebook1->AddPage( m_panel_histograms, wxT("Histograms"), false );
	m_panel_convolutions = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_grid3 = new wxGrid( m_panel_convolutions, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_grid3->CreateGrid( 3, 3 );
	m_grid3->EnableEditing( true );
	m_grid3->EnableGridLines( true );
	m_grid3->EnableDragGridSize( false );
	m_grid3->SetMargins( 0, 0 );

	// Columns
	m_grid3->AutoSizeColumns();
	m_grid3->EnableDragColMove( false );
	m_grid3->EnableDragColSize( true );
	m_grid3->SetColLabelSize( 20 );
	m_grid3->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_grid3->EnableDragRowSize( true );
	m_grid3->SetRowLabelSize( 30 );
	m_grid3->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_grid3->SetDefaultCellAlignment( wxALIGN_CENTER, wxALIGN_TOP );
	bSizer3->Add( m_grid3, 0, wxALL, 5 );


	m_panel_convolutions->SetSizer( bSizer3 );
	m_panel_convolutions->Layout();
	bSizer3->Fit( m_panel_convolutions );
	m_notebook1->AddPage( m_panel_convolutions, wxT("Convolutions"), false );

	gSizer3->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( gSizer3, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUI::GUIOnUpdateUI ) );
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI::m_fileOpenOnMenuSelection ), this, m_fileOpen->GetId());
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI::m_fileSaveAsOnMenuSelection ), this, m_fileSaveAs->GetId());
	m_menuView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI::m_ViewStatusBarOnMenuSelection ), this, m_ViewStatusBar->GetId());
	m_menuView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUI::m_ViewBrightnessSaturationContrastWindowOnMenuSelection ), this, m_ViewBrightnessSaturationContrastWindow->GetId());
	m_scrolledWindow1->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUI::m_scrolledWindow1OnLeftDClick ), NULL, this );
	m_buttonHistogram->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::m_buttonHistogramOnButtonClick ), NULL, this );
}

GUI::~GUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUI::GUIOnUpdateUI ) );
	m_scrolledWindow1->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUI::m_scrolledWindow1OnLeftDClick ), NULL, this );
	m_buttonHistogram->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::m_buttonHistogramOnButtonClick ), NULL, this );

}
