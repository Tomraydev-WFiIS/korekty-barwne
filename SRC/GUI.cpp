///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 23 2019)
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

	m_menuBarTop->Append( m_menuView, wxT("View") );

	this->SetMenuBar( m_menuBarTop );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 1, 0, 0 );

	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	gSizer1->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( gSizer1, 2, wxEXPAND, 5 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 1, 1, 0, 0 );

	m_scrolledWindow2 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	gSizer2->Add( m_scrolledWindow2, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( gSizer2, 2, wxEXPAND, 5 );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 1, 0, 0 );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel3->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	gSizer3->Add( m_panel3, 0, wxEXPAND | wxALL, 5 );

	m_slider1 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gSizer3->Add( m_slider1, 0, wxALL, 5 );

	m_slider2 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	gSizer3->Add( m_slider2, 0, wxALL, 5 );


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
	m_scrolledWindow1->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUI::m_scrolledWindow1OnLeftDClick ), NULL, this );
}

GUI::~GUI()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUI::GUIOnUpdateUI ) );
	m_scrolledWindow1->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( GUI::m_scrolledWindow1OnLeftDClick ), NULL, this );

}
