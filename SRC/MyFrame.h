#pragma once
#include "GUI.h"
#include "MyBrightnessSaturationContrastDialog.h"
#include "ColorsHexagon.h"
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>
#include <wx/statline.h>
#include <cmath>

float findMin(float x, float y, float z = 999999.9);
float findMax(float x, float y, float z = 0.0);

class MyFrame : public GUI {
	friend MyBrightnessSaturationContrastDialog;

protected:
	// Event handlers (copy from GUI.h and override)
	void m_fileOpenOnMenuSelection(wxCommandEvent& event);
	void m_fileSaveAsOnMenuSelection(wxCommandEvent& event);
	void GUIOnUpdateUI(wxUpdateUIEvent& event);
	void m_ViewStatusBarOnMenuSelection(wxCommandEvent& event);

	//hexagon
	void m_scrolledWindow1OnLeftDClick(wxMouseEvent& event);
	void m_clickHexagonButton(wxCommandEvent& event);
	void changePixelsAlgo(void);
	void changePropSlider(wxScrollEvent& event);

	// Modified hexagon
	void m_clickModHexagonButton(wxCommandEvent& event);
	void generateModHexagon();
	void calculateModHexagon(int* RGB);

	// Brightness, Saturation and Contrast
	void m_ViewBrightnessSaturationContrastWindowOnMenuSelection(wxCommandEvent& event);
	void setBrightness(int value, int valueMin, int valueMax, bool firstChange = true);
	void setSaturation(int value, int valueMin, int valueMax, bool firstChange = true);
	void setContrast(int value, int valueMin, int valueMax, bool firstChange = true);

	//Histograms
	void m_buttonHistogramOnButtonClick(wxCommandEvent& event);

	void generate_hist_img(wxImage &img,wxBitmap &bitmap, int count[256], int r, int g, int b);
	void paintHistograms(void);
	void calculateHistograms(wxImage &img, int rgb_count[256], int r_count[256], int g_count[256], int b_count[256]);
	void updateHistogram(void);

	void Repaint(void); // Repaint the Old and New image.
public:
	MyFrame(wxWindow* parent);
	~MyFrame();
	wxImage imgOld;
	wxImage imgToBSC;
	wxImage imgNew;
	wxBitmap bitMapOld;
	wxBitmap bitMapNew;

	// Brightness and Saturation
	bool showBrightnessSaturationContrastDialog = false;
	MyBrightnessSaturationContrastDialog* brightnessDialog = nullptr;

	//Hexagon
	wxColor * hexagonColor = new wxColor(0, 0, 0);
	wxColor pickedColor = wxColor(0, 0, 0);
	ColorsHexagon * hexagon;
	wxStaticText * colorFromImageTxt;
	wxStaticText * colorFromHexagonTxt;
	wxButton * hexagonButton;
	wxStaticText * m_propText;
	wxSlider * m_propSlider;
	int hexagonSliderValue;

	// Modified hexagon
	wxStaticLine* m_staticline1;
	wxButton * modHexagonButton;
	wxImage redPartHex;
	wxImage bluePartHex;
	wxImage greenPartHex;
	wxBitmap bitmapRedPartHex;
	wxBitmap bitmapBluePartHex;
	wxBitmap bitmapGreenPartHex;
	bool modHexagonGenerated = false;

	//Histograms
	bool histogramsGenerated = false;
	wxImage imgHistogramRGB;
	wxImage imgHistogramR;
	wxImage imgHistogramG;
	wxImage imgHistogramB;
	wxBitmap bitMapHistogramRGB;
	wxBitmap bitMapHistogramR;
	wxBitmap bitMapHistogramG;
	wxBitmap bitMapHistogramB;

	wxImage imgHistogramRGB_n;
	wxImage imgHistogramR_n;
	wxImage imgHistogramG_n;
	wxImage imgHistogramB_n;
	wxBitmap bitMapHistogramRGB_n;
	wxBitmap bitMapHistogramR_n;
	wxBitmap bitMapHistogramG_n;
	wxBitmap bitMapHistogramB_n;
};

