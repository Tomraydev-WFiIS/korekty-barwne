#include <wx/wx.h>
#include <memory>
#include "MyFrame.h"


class MyApp : public wxApp {

public:

	virtual bool OnInit();
	virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame *mainFrame = new MyFrame(nullptr);

	mainFrame->SetTitle(wxString("PGK - Korekty barwne"));
	mainFrame->Show(true);
	SetTopWindow(mainFrame);

	return true;
}