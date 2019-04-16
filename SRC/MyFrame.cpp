#include "MyFrame.h"
#include <wx/wxprec.h>
#include <wx/colordlg.h>
#include <wx/wfstream.h>
#include <wx/dcclient.h>
#include <wx/gdicmn.h>
#include <iostream>
#include <wx/dcmemory.h>
#include <wx/filedlg.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>

MyFrame::MyFrame(wxWindow* parent) : GUI(parent) {
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxPNGHandler);

	wxImage image;
	if (!image.LoadFile(wxString("..\\img\\placeholder.png"))) {
		wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		Destroy();
		return;
	}
	else {
		imgOld = image.Copy();
		imgNew = imgOld.Copy();
	}

	wxSize size = image.GetSize();
	m_scrolledWindow1->SetVirtualSize(size);
	m_scrolledWindow2->SetVirtualSize(size);

	wxBitmap bitmap(imgOld);
	bitMapOld = bitmap;
	bitMapNew = bitmap;
	pickedColor = wxColor(255, 255, 255);

	Repaint();
	SetStatusText(wxT("Load an image to get started"), 0);
}

void MyFrame::GUIOnUpdateUI(wxUpdateUIEvent& event) {
	Repaint();
}

void MyFrame::m_fileOpenOnMenuSelection(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Open image file"), "..\\img", "",
			"Image files (*.bmp,*.jpeg,*.jpg,*.png)|*.bmp;*.jpeg;*.jpg;*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}
	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		return;
	}
	wxString fileName = openFileDialog.GetPath();

	wxImage image;
	if (!image.LoadFile(wxString(fileName))){
		wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		Destroy();
		return;
	}
	else{
		imgOld = image.Copy();
		imgNew = imgOld.Copy();
	}

	wxSize size = image.GetSize();
	m_scrolledWindow1->SetVirtualSize(size);
	m_scrolledWindow2->SetVirtualSize(size);

	wxBitmap bitmap(imgOld);
	bitMapOld = bitmap;
	bitMapNew = bitmap;
	Repaint();
	SetStatusText(wxT("Loaded file: " + fileName), 0);
}
void MyFrame::m_fileSaveAsOnMenuSelection(wxCommandEvent& event) {
	wxImage image = imgNew;
	wxFileDialog
		saveFileDialog(this, _("Save image file"), "..\\img", "",
			"Image files (*.bmp,*.jpeg,*.jpg,*.png)|*.bmp;*.jpeg;*.jpg;*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}
	wxFileOutputStream output_stream(saveFileDialog.GetPath());
	if (!output_stream.IsOk())
	{
		wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
		return;
	}
	wxString fileName = saveFileDialog.GetPath();
	image.SaveFile(fileName);
	SetStatusText(wxT("Saved file: " + fileName), 0);
}

void MyFrame::Repaint(void) {
	wxClientDC dc_1(m_scrolledWindow1);
	wxClientDC dc_2(m_scrolledWindow2);
	wxBufferedDC dc1(&dc_1);
	wxBufferedDC dc2(&dc_2);
	m_scrolledWindow1->DoPrepareDC(dc1);
	m_scrolledWindow2->DoPrepareDC(dc2);
	dc1.Clear();
	dc2.Clear();
	dc1.DrawBitmap(bitMapOld, 0, 0, true);
	dc2.DrawBitmap(bitMapNew, 0, 0, true);
	return;
}

void MyFrame::m_ViewStatusBarOnMenuSelection(wxCommandEvent& event) {
	if (m_statusBar1->IsEnabled()) {
		m_statusBar1->Disable();
		m_statusBar1->Show(false);
	}
	else {
		m_statusBar1->Enable();
		m_statusBar1->Show(true);
	}
}

void MyFrame::m_scrolledWindow1OnLeftDClick(wxMouseEvent& event) {
	unsigned char *pixels = imgOld.GetData();
	int w = imgOld.GetWidth();
	int h = imgOld.GetHeight();

	int x;
	int y;
	m_scrolledWindow1->GetViewStart(&x, &y);
	x += event.GetPosition().x;
	y += event.GetPosition().y;
	if (x > w || y > h) {
		return;
	}

	pickedColor = wxColor(pixels[3*(y*w + x)], pixels[3*(y*w + x) + 1], pixels[3*(y*w + x) + 2]);
	std::string color = std::to_string(pickedColor.Red() ) + ", " + std::to_string(pickedColor.Green()) + ", " + std::to_string(pickedColor.Blue());

	SetStatusText(wxT("Clicked " + std::to_string(x) + ", " + std::to_string(y) + " Color: " + color ), 0);
	return;
}