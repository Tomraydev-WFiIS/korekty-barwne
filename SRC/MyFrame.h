#pragma once
#include "GUI.h"
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>

class MyFrame : public GUI {
protected:
	// Event handlers (copy from GUI.h and override)
	void m_fileOpenOnMenuSelection(wxCommandEvent& event);
	void m_fileSaveAsOnMenuSelection(wxCommandEvent& event);
	void GUIOnUpdateUI(wxUpdateUIEvent& event);
	void m_ViewStatusBarOnMenuSelection(wxCommandEvent& event);
	void m_scrolledWindow1OnLeftDClick(wxMouseEvent& event);

	
	void Repaint(void); // Repaint the Old and New image.
public:
	MyFrame(wxWindow* parent);
	wxImage imgOld;
	wxImage imgNew;
	wxBitmap bitMapOld;
	wxBitmap bitMapNew;
	wxColor pickedColor;
};

