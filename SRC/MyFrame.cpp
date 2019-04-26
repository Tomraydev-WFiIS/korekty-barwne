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
	if (!image.LoadFile(wxString("..\\img\\lena.png"))) {
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
	//Paint images
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
	//Paint histograms
	if(histogramsGenerated) paintHistograms();
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

void MyFrame::m_buttonHistogramOnButtonClick(wxCommandEvent& event) {
	//***** Calculating the histograms *****
	int rgb_count[256] = { 0 };
	int r_count[256]  = { 0 };
	int g_count[256]  = { 0 };
	int b_count[256]  = { 0 };
	int rgb_count_n[256] = { 0 };
	int r_count_n[256] = { 0 };
	int g_count_n[256] = { 0 };
	int b_count_n[256] = { 0 };

	calculateHistograms(imgOld, rgb_count, r_count, g_count, b_count);
	calculateHistograms(imgNew, rgb_count_n, r_count_n, g_count_n, b_count_n);
	
	//***** Creating the histogram images *****
	generate_hist_img(imgHistogramRGB, bitMapHistogramRGB, rgb_count, 0x00, 0x00, 0x00);
	generate_hist_img(imgHistogramR, bitMapHistogramR, r_count, 0xff, 0x00, 0x00);
	generate_hist_img(imgHistogramG, bitMapHistogramG, g_count, 0x00, 0xff, 0x00);
	generate_hist_img(imgHistogramB, bitMapHistogramB, b_count, 0x00, 0x00, 0xff);

	generate_hist_img(imgHistogramRGB_n, bitMapHistogramRGB_n, rgb_count_n, 0x00, 0x00, 0x00);
	generate_hist_img(imgHistogramR_n, bitMapHistogramR_n, r_count_n, 0xff, 0x00, 0x00);
	generate_hist_img(imgHistogramG_n, bitMapHistogramG_n, g_count_n, 0x00, 0xff, 0x00);
	generate_hist_img(imgHistogramB_n, bitMapHistogramB_n, b_count_n, 0x00, 0x00, 0xff);
	//***** Drawing the histogram images *****
	histogramsGenerated = true;
	paintHistograms();
	SetStatusText(wxT("Generated old and new histograms"), 0);
	return;
}

void MyFrame::paintHistograms(void) {
	int margin = 5;
	wxClientDC dc_1(m_panel_hist_old);
	wxClientDC dc_2(m_panel_hist_new);
	wxBufferedDC dc1(&dc_1);
	wxBufferedDC dc2(&dc_2);
	dc1.Clear();
	dc2.Clear();
	dc1.DrawBitmap(bitMapHistogramRGB, 0, 0, true);
	dc1.DrawBitmap(bitMapHistogramR, 0, 100 + margin, true);
	dc1.DrawBitmap(bitMapHistogramG, 0, 2 * (100 + margin), true);
	dc1.DrawBitmap(bitMapHistogramB, 0, 3 * (100 + margin), true);

	dc2.DrawBitmap(bitMapHistogramRGB_n, 0, 0, true);
	dc2.DrawBitmap(bitMapHistogramR_n, 0, 100 + margin, true);
	dc2.DrawBitmap(bitMapHistogramG_n, 0, 2 * (100 + margin), true);
	dc2.DrawBitmap(bitMapHistogramB_n, 0, 3 * (100 + margin), true);
	return;
}

void MyFrame::calculateHistograms(wxImage &img, int rgb_count[256], int r_count[256], int g_count[256], int b_count[256]) {
	unsigned char *pixels = img.GetData();
	int w = img.GetWidth();
	int h = img.GetHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int r = pixels[3 * (y*w + x)];
			int g = pixels[3 * (y*w + x) + 1];
			int b = pixels[3 * (y*w + x) + 2];
			rgb_count[(r + g + b) / 3]++;
			r_count[r]++;
			g_count[g]++;
			b_count[b]++;
		}
	}
}

void MyFrame::generate_hist_img(wxImage &img, wxBitmap &bitmap, int count[256], int r, int g, int b) {
	int hist_max = 1;
	for (int i = 0; i < 256; i++) {
		if (count[i] > hist_max) {
			hist_max = count[i];
		}
	}
	for (int i = 0; i < 256; i++) {
		count[i] = (100 * count[i]) / hist_max;
	}
	unsigned char hist_pixels[100 * 256 * 3];
	for (int i = 0; i < 100 * 256 * 3; i++) {
		hist_pixels[i] = 0xff;
	}
	for (int x = 0; x < 256; x++) {
		for (int y = 0; y < count[x]; y++) {
			hist_pixels[3 * ((99 - y) * 256 + x)] = r;
			hist_pixels[3 * ((99 - y) * 256 + x) + 1] = g;
			hist_pixels[3 * ((99 - y) * 256 + x) + 2] = b;
		}
	}
	img = wxImage(256, 100, hist_pixels, true);
	bitmap = wxBitmap(img);
}


//PISANIE DO KONSOLI W VS
/*for (int i = 0; i < 256; i++) {
		auto str = L"count[" + std::to_string(i) + "] = " + std::to_string(count[i]) + "\n";
		OutputDebugString(str);
	}*/