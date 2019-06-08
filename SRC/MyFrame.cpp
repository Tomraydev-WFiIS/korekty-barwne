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

int colorHelper(int value) {
	if (value > 255) return 255;
	else if (value < 0) return 0;
	else return value;
}

float findMin(float x, float y, float z) {
	float min;
	if (x < y)
		min = x;
	else
		min = y;
	if (z < min)
		min = z;
	return min;
}

float findMax(float x, float y, float z) {
	float max;
	if (x > y)
		max = x;
	else
		max = y;
	if (z > max)
		max = z;
	return max;
}

MyFrame::MyFrame(wxWindow* parent) : GUI(parent) {
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxPNGHandler);

	//Hexagon
	colorFromHexagonTxt = new wxStaticText(m_panel_hexagon_color, wxID_ANY, wxT("COLOR ON WHICH WE CHANGE"), wxDefaultPosition, wxDefaultSize, 0);
	this->hexagon = new ColorsHexagon(m_panel_hexagon_color, colorFromHexagonTxt, hexagonColor);
	m_panel_hexagon_sizer->Add(this->hexagon);

	m_propText = new wxStaticText(m_panel_hexagon_color, wxID_ANY, wxT("Correction strength: 0%"), wxDefaultPosition, wxDefaultSize, 0);
	m_propText->Wrap(-1);
	m_panel_hexagon_sizer->Add(m_propText, 0, wxALL, 5);

	m_propSlider = new wxSlider(m_panel_hexagon_color, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	m_propSlider->SetValue(0);
	m_propSlider->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame::changePropSlider), NULL, this);
	m_panel_hexagon_sizer->Add(m_propSlider, 0, wxALL, 5);

	colorFromImageTxt = new wxStaticText(m_panel_hexagon_color, wxID_ANY, wxT("COLOR TO CHANGE"), wxDefaultPosition, wxDefaultSize, 0);
	colorFromImageTxt->Wrap(-1);
	m_panel_hexagon_sizer->Add(colorFromImageTxt, 0, wxALL, 5);

	colorFromHexagonTxt->Wrap(-1);
	m_panel_hexagon_sizer->Add(colorFromHexagonTxt, 0, wxALL, 5);

	hexagonButton = new wxButton(m_panel_hexagon_color, wxID_ANY, wxT("CHANGE PIXELS COLOR"), wxDefaultPosition, wxDefaultSize, 0);
	hexagonButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::m_clickHexagonButton), NULL, this);
	m_panel_hexagon_sizer->Add(hexagonButton, 0, wxALL, 5);

	resetAllButton = new wxButton(m_panel_hexagon_color, wxID_ANY, wxT("RESET ALL SETTINGS"), wxDefaultPosition, wxDefaultSize, 0);
	resetAllButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::m_clickResetAllButton), NULL, this);
	m_panel_hexagon_sizer->Add(resetAllButton, 0, wxALL, 5);

	///////////////////////////////////////////////////////////////////////

	// Modified Hexagon

	modHexagonCheckBox = new wxCheckBox(m_panel_hexagon_mod, wxID_ANY, wxT("Turn on/off mod hexagon"), wxDefaultPosition, wxDefaultSize, 0);
	m_panel_hexagon_sizer->Add(modHexagonCheckBox, 0, wxALIGN_CENTER | wxALL, 5);
	modHexagonCheckBox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame::m_clickModHexagonButton), NULL, this);
	///////////////////////////////////////////////////////////////////////
	wxImage image;
	if (!image.LoadFile(wxString("..\\img\\lena.png"))) {
		wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		Destroy();
		return;
	}
	else {
		imgOld = image.Copy();
		imgToBSC = imgOld.Copy();
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

MyFrame::~MyFrame() {
	delete brightnessDialog;
}

void MyFrame::GUIOnUpdateUI(wxUpdateUIEvent& event) {
	Repaint();
}

void MyFrame::m_fileOpenOnMenuSelection(wxCommandEvent& event) {
	wxFileDialog
		openFileDialog(this, _("Open image file"), "..\\img", "",
			"Image files (*.bmp,*.jpeg,*.jpg,*.png)|*.bmp;*.jpeg;*.jpg;*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL) {
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
	if (!image.LoadFile(wxString(fileName))) {
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
	Repaint();
	SetStatusText(wxT("Loaded file: " + fileName), 0);
}

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int bezwzgl(int w) {
	if (w >= 0) return w;
	else return w * (-1);
}

void MyFrame::changePixelsAlgo(bool resetBSC) {
	wxImage processImage = this->imgNew.Copy();
	int ratio = this->m_propSlider->GetValue();
	hexagonSliderValue = ratio;

	if (resetBSC || (lastHexagonValue != hexagonSliderValue))
		processImage = this->imgOld.Copy();
	if ((lastImageColor != pickedColor ) || (lastPickedColor != *hexagonColor))
	{
		processImage = this->imgOld.Copy();
		lastImageColor = pickedColor;
		lastPickedColor = *hexagonColor;
	}
	for (int i = 0; i < processImage.GetWidth(); i++) {
		for (int j = 0; j < processImage.GetHeight(); j++) {
			wxColor pixelColor = wxColor(processImage.GetRed(i, j), processImage.GetGreen(i, j), processImage.GetBlue(i, j));

			if (pixelColor == pickedColor) {
				processImage.SetRGB(i, j, hexagonColor->Red(), hexagonColor->Green(), hexagonColor->Blue());
			}
			else {

				int new_r = colorHelper(pixelColor.Red() * (100 - ratio) / 100 + hexagonColor->Red() * ratio / 100);
				int new_g = colorHelper(pixelColor.Green() * (100 - ratio) / 100 + hexagonColor->Green() * ratio / 100);
				int new_b = colorHelper(pixelColor.Blue() * (100 - ratio) / 100 + hexagonColor->Blue() * ratio / 100);

				processImage.SetRGB(i, j, new_r, new_g, new_b);
			}
		}
	}
	imgNew = processImage.Copy();
	this->bitMapNew = wxBitmap(processImage);
	lastHexagonValue = hexagonSliderValue;
	if (brightnessDialog && (resetBSC == false)) {
		setBrightness(brightnessDialog->getBrightness(), brightnessDialog->getMinBrightness(), brightnessDialog->getMaxBrightness());
		setSaturation(brightnessDialog->getSaturation(), brightnessDialog->getMinSaturation(), brightnessDialog->getMaxSaturation(), false);
		setContrast(brightnessDialog->getContrast(), brightnessDialog->getMinContrast(), brightnessDialog->getMaxContrast(), false);

	}
	this->Refresh();
}

void  MyFrame::m_clickHexagonButton(wxCommandEvent& event) {
	if ((lastHexagonValue == this->m_propSlider->GetValue()) && ((lastImageColor == pickedColor) && (lastPickedColor == *hexagonColor)))
		return;
	hexagonChanged = true;
	changePixelsAlgo();

	if (histogramsGenerated)
		updateHistogram();
}

void  MyFrame::m_clickResetAllButton(wxCommandEvent& event) {
	wxScrollEvent tmp{};
	if(brightnessDialog)
		brightnessDialog->ResetAll();
	lastHexagonValue = 0;
	this->m_propSlider->SetValue(0);
	this->changePropSlider(tmp);
	pickedColor = wxColor(0, 0, 0);
	colorFromImageTxt->SetForegroundColour(pickedColor);
	colorFromImageTxt->Refresh();

	*hexagonColor = wxColor(0, 0, 0);
	colorFromHexagonTxt->SetForegroundColour(*hexagonColor);
	colorFromHexagonTxt->Refresh();

	this->imgNew = this->imgOld.Copy();
	this->bitMapNew = wxBitmap(this->imgNew.Copy());
	this->Refresh();
}

void MyFrame::calculateModHexagon(int* RGB) {

	// Change by hexagon
	int hexagonSliderValue = this->m_propSlider->GetValue();
	RGB[0] = colorHelper(RGB[0] * (100.0 - hexagonSliderValue) / 100.0 + hexagonColor->Red() * hexagonSliderValue / 100.0);
	RGB[1] = colorHelper(RGB[1] * (100.0 - hexagonSliderValue) / 100.0 + hexagonColor->Green() * hexagonSliderValue / 100.0);
	RGB[2] = colorHelper(RGB[2] * (100.0 - hexagonSliderValue) / 100.0 + hexagonColor->Blue() * hexagonSliderValue / 100.0);

	double brightness = 0.0, saturation = 0.0, contrast = 0.0;
	if (brightnessDialog) {
		brightness = brightnessDialog->getBrightness() - ((brightnessDialog->getMaxBrightness() + brightnessDialog->getMinBrightness()) / 2);
		saturation = (double)brightnessDialog->getSaturation() / ((brightnessDialog->getMaxSaturation() + brightnessDialog->getMinSaturation()) / 2.0) - 1.0;
		contrast = brightnessDialog->getContrast() - ((brightnessDialog->getMaxContrast() + brightnessDialog->getMinContrast()) / 2);
		contrast = (contrast + 256.0) / (257.0 - contrast);
	}
	else
		return;



	//Change brightness
	for (int i = 0; i < 3; i++)
	{
		int newValue = RGB[i] + brightness;
		if (newValue <= 1)
			newValue = 1;
		else if (newValue > 255)
			newValue = 255;
		RGB[i] = newValue;
	}

	// Change saturation
	float hue, sat, val;
	float x, f, i, p, q, t;
	x = findMin(RGB[0], RGB[1], RGB[2]);
	val = findMax(RGB[0], RGB[1], RGB[2]);
	if (x == val)
	{
		hue = 0;
		sat = 0;
	}
	else
	{
		if (RGB[0] == x)
		{
			f = RGB[1] - RGB[2];
			i = 3.0;
		}
		else if (RGB[1] == x)
		{
			f = RGB[2] - RGB[0];
			i = 5.0;
		}
		else
		{
			f = RGB[0] - RGB[1];
			i = 1.0;
		}

		hue = fmod((i - f / (val - x)) * 60, 360);
		sat = ((val - x) / val);

		// change in saturation
		if (saturation > 0)
		{
			sat += (1.0 - sat) * saturation;
		}
		else
		{
			sat += sat * saturation;
		}

		if (sat > 1.0)
			sat = 1.0;
		if (sat < 0.0)
			sat = 0.0;

		// HSV to RGB
		if (val == 0)
		{
			RGB[0] = 0;
			RGB[1] = 0;
			RGB[2] = 0;
		}
		else
		{
			hue /= 60;
			i = floor(hue);
			f = hue - i;
			p = val * (1 - sat);
			q = val * (1 - (sat*f));
			t = val * (1 - (sat*(1 - f)));
			if (i == 0)
			{
				RGB[0] = val;
				RGB[1] = t;
				RGB[2] = p;
			}
			else if (i == 1)
			{
				RGB[0] = q;
				RGB[1] = val;
				RGB[2] = p;
			}
			else if (i == 2)
			{
				RGB[0] = p;
				RGB[1] = val;
				RGB[2] = t;
			}
			else if (i == 3)
			{
				RGB[0] = p;
				RGB[1] = q;
				RGB[2] = val;
			}
			else if (i == 4)
			{
				RGB[0] = t;
				RGB[1] = p;
				RGB[2] = val;
			}
			else if (i == 5)
			{
				RGB[0] = val;
				RGB[1] = p;
				RGB[2] = q;
			}

		}
	}

	// Change contrast
	for (unsigned int i = 0; i < 3; i++)
	{
		int newValue = (RGB[i] - (255.0 / 2.0)) * contrast + 255.0 / 2.0;
		if (newValue < 0)
			newValue = 0;
		else if (newValue > 255)
			newValue = 255;
		RGB[i] = newValue;
	}

}

void MyFrame::generateModHexagon() {
	wxClientDC dc(m_panel_hexagon_mod);
	wxBufferedDC dc1(&dc);

	const wxBrush* background = wxWHITE_BRUSH;
	dc1.SetBackground(*background);
	dc1.Clear();

	int* RGB = new int[3];

	/****** BLUE PART *******/
	wxImage constBlueHexagon;
	constBlueHexagon.Create(200, 200);
	constBlueHexagon.SetMask(true);

	const int a_blue = 110;
	const int b_blue = 70;
	const double step_a_blue = 255 / a_blue;
	const double step_b_blue = 255 / b_blue;

	for (int i = 0; i < a_blue; i++) {
		for (int j = 0; j < b_blue; j++) {
			RGB[0] = 255 - step_a_blue * i;
			RGB[1] = step_b_blue * j;
			RGB[2] = 255;
			calculateModHexagon(RGB);
			constBlueHexagon.SetRGB(j, i + j / 2, RGB[0], RGB[1], RGB[2]);
		}
	}

	/****** GREEN PART *******/
	wxImage constGreenHexagon;
	constGreenHexagon.Create(200, 400);
	constGreenHexagon.SetMask(true);

	const int a_green = 110;
	const int b_green = 70;
	const double step_a_green = 255 / a_green;
	const double step_b_green = 255 / b_green;

	for (int i = 0; i < a_green; i++) {
		for (int j = 0; j < b_green; j++) {
			RGB[0] = 255 - step_a_green * i;
			RGB[1] = 255;
			RGB[2] = 255 - step_b_green * j;
			calculateModHexagon(RGB);
			constGreenHexagon.SetRGB(j, i - j / 2 + 65, RGB[0], RGB[1], RGB[2]);
		}
	}

	/****** RED PART *******/
	wxImage constRedHexagon;
	constRedHexagon.Create(100, 100);
	constRedHexagon.SetMask(true);

	const int a_red = 100;
	const int b_red = 100;
	const double step_a_red = 255 / a_red;
	const double step_b_red = 255 / b_red;

	for (int i = 0; i < a_red; i++) {
		for (int j = 0; j < b_red; j++) {
			RGB[0] = 255;
			RGB[1] = step_a_red * i;
			RGB[2] = 255 - step_b_red * j;
			calculateModHexagon(RGB);
			constRedHexagon.SetRGB(j, i, RGB[0], RGB[1], RGB[2]);
		}
	}

	const double angle = 2 * M_PI / 360;
	constRedHexagon = constRedHexagon.Rotate(angle * 45, wxPoint(50, 50));
	constRedHexagon = constRedHexagon.Scale(145, 85);

	dc1.DrawBitmap(wxBitmap(constRedHexagon), 28, 7, true);
	dc1.DrawBitmap(wxBitmap(constGreenHexagon), 100, 20, true);
	dc1.DrawBitmap(wxBitmap(constBlueHexagon), 30, 50, true);


}

void MyFrame::m_clickModHexagonButton(wxCommandEvent& event) {
	if (modHexagonGenerated)
	{
		modHexagonGenerated = false;
		wxClientDC dc(m_panel_hexagon_mod);
		wxBufferedDC dc1(&dc);

		const wxBrush* background = wxWHITE_BRUSH;
		dc1.SetBackground(*background);
		dc1.Clear();
		this->Refresh();
	}
	else
		modHexagonGenerated = true;
	//generateModHexagon();
}

void MyFrame::changePropSlider(wxScrollEvent& event) {
	int value = this->m_propSlider->GetValue();
	wxString str = "Correction strength: ";
	str.Append(wxString::Format(wxT("%i"), value));
	str.Append("%");
	this->m_propText->SetLabelText(str);
}

void MyFrame::m_fileSaveAsOnMenuSelection(wxCommandEvent& event) {
	wxImage image = imgNew;
	wxFileDialog
		saveFileDialog(this, _("Save image file"), "..\\img", "",
			"Image files (*.bmp,*.jpeg,*.jpg,*.png)|*.bmp;*.jpeg;*.jpg;*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
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
	if (histogramsGenerated)
		paintHistograms();

	if (modHexagonGenerated)
		generateModHexagon();
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

void MyFrame::m_ViewBrightnessSaturationContrastWindowOnMenuSelection(wxCommandEvent& event)
{
	if (brightnessDialog == nullptr)
		brightnessDialog = new MyBrightnessSaturationContrastDialog(this);
	showBrightnessSaturationContrastDialog = !showBrightnessSaturationContrastDialog;
	brightnessDialog->Show(showBrightnessSaturationContrastDialog);

}

void MyFrame::setBrightness(int value, int valueMin, int valueMax, bool firstChange, bool reset) {
	value -= (valueMax + valueMin) / 2;
	//auto str = L"Brightness value " + std::to_string(value) + "\n"; OutputDebugString(str);
	if (reset)
		imgToBSC = imgOld.Copy();

	wxImage imgCpy = imgToBSC.Copy();;
	if (firstChange == false)
		imgCpy = imgNew.Copy();
	if (hexagonChanged == true)
	{
		imgCpy = imgNew.Copy();
		imgToBSC = imgNew.Copy();
		hexagonChanged = false;
	}
	if (reset)
	{
		imgNew = imgCpy.Copy();
		changePixelsAlgo(true);
		imgToBSC = imgNew.Copy();
		return;
	}
	unsigned int howManyPixels = 3 * imgCpy.GetHeight()*imgCpy.GetWidth();
	unsigned char* picturePixel = imgCpy.GetData();

	for (unsigned int i = 0; i < howManyPixels; i++)
	{
		int newValue = picturePixel[i] + value;
		if (newValue < 0)
			newValue = 0;
		else if (newValue > 255)
			newValue = 255;
		picturePixel[i] = newValue;
	}
	imgNew = imgCpy.Copy();
	wxBitmap bitmap(imgCpy);
	bitMapNew = bitmap;

	if (firstChange) {
		SetStatusText(wxT("Brightness set"), 0);
	}

}

void MyFrame::setSaturation(int enteredValue, int valueMin, int valueMax, bool firstChange, bool reset) {
	double value = (double)enteredValue / ((valueMax + valueMin) / 2) - 1.0;
	//auto str = L"Saturation in percent " + std::to_string(value) + "\n"; OutputDebugString(str);
	if (reset)
		imgToBSC = imgOld.Copy();

	wxImage imgCpy = imgToBSC.Copy();
	if (firstChange == false)
		imgCpy = imgNew.Copy();
	if (hexagonChanged == true)
	{
		imgCpy = imgNew.Copy();
		imgToBSC = imgNew.Copy();
		hexagonChanged = false;
	}
	if (reset)
	{
		imgNew = imgCpy.Copy();
		changePixelsAlgo(true);
		imgToBSC = imgNew.Copy();
		return;
	}
	unsigned int howManyPixels = 3 * imgCpy.GetHeight()*imgCpy.GetWidth();
	unsigned char* picturePixel = imgCpy.GetData();

	float hue, sat, val;
	float x, f, i, p, q, t;
	for (unsigned int k = 0; k < howManyPixels; k += 3)
	{
		// RGB to HSV
		x = findMin(picturePixel[k], picturePixel[k + 1], picturePixel[k + 2]);
		val = findMax(picturePixel[k], picturePixel[k + 1], picturePixel[k + 2]);
		if (x == val)
		{
			hue = 0;
			sat = 0;
		}
		else
		{
			if (picturePixel[k] == x)
			{
				f = picturePixel[k + 1] - picturePixel[k + 2];
				i = 3.0;
			}
			else if (picturePixel[k + 1] == x)
			{
				f = picturePixel[k + 2] - picturePixel[k];
				i = 5.0;
			}
			else
			{
				f = picturePixel[k] - picturePixel[k + 1];
				i = 1.0;
			}

			hue = fmod((i - f / (val - x)) * 60, 360);
			sat = ((val - x) / val);

			// change in saturation
			if (value > 0)
			{
				sat += (1.0 - sat) * value;
			}
			else
			{
				sat += sat * value;
			}

			if (sat > 1.0)
				sat = 1.0;
			if (sat < 0.0)
				sat = 0.0;

			// HSV to RGB
			if (val == 0)
			{
				picturePixel[k] = 0;
				picturePixel[k + 1] = 0;
				picturePixel[k + 2] = 0;
			}
			else
			{
				hue /= 60;
				i = floor(hue);
				f = hue - i;
				p = val * (1 - sat);
				q = val * (1 - (sat*f));
				t = val * (1 - (sat*(1 - f)));
				if (i == 0)
				{
					picturePixel[k] = val;
					picturePixel[k + 1] = t;
					picturePixel[k + 2] = p;
				}
				else if (i == 1)
				{
					picturePixel[k] = q;
					picturePixel[k + 1] = val;
					picturePixel[k + 2] = p;
				}
				else if (i == 2)
				{
					picturePixel[k] = p;
					picturePixel[k + 1] = val;
					picturePixel[k + 2] = t;
				}
				else if (i == 3)
				{
					picturePixel[k] = p;
					picturePixel[k + 1] = q;
					picturePixel[k + 2] = val;
				}
				else if (i == 4)
				{
					picturePixel[k] = t;
					picturePixel[k + 1] = p;
					picturePixel[k + 2] = val;
				}
				else if (i == 5)
				{
					picturePixel[k] = val;
					picturePixel[k + 1] = p;
					picturePixel[k + 2] = q;
				}

			}

		}
	}
	imgNew = imgCpy.Copy();
	wxBitmap bitmap(imgCpy);
	bitMapNew = bitmap;

	if (firstChange) {
		SetStatusText(wxT("Saturation set"), 0);
	}

}

void MyFrame::setContrast(int value, int valueMin, int valueMax, bool firstChange, bool reset) {
	value -= (valueMax + valueMin) / 2;


	wxImage imgCpy = imgToBSC.Copy();;
	if (firstChange == false)
		imgCpy = imgNew.Copy();
	if (hexagonChanged == true)
	{
		imgCpy = imgNew.Copy();
		imgToBSC = imgNew.Copy();
		hexagonChanged = false;
	}
	if (reset)
	{
		imgNew = imgCpy.Copy();
		changePixelsAlgo(true);
		imgToBSC = imgNew.Copy();
		return;
	}
	unsigned int howManyPixels = 3 * imgCpy.GetHeight()*imgCpy.GetWidth();
	unsigned char* picturePixel = imgCpy.GetData();
	double contrast = (value + 256.0) / (257.0 - value);

	for (unsigned int i = 0; i < howManyPixels; i++)
	{
		int newValue = (picturePixel[i] - (255.0 / 2.0)) * contrast + 255.0 / 2.0;
		if (newValue < 0)
			newValue = 0;
		else if (newValue > 255)
			newValue = 255;
		picturePixel[i] = newValue;
	}
	imgNew = imgCpy.Copy();
	wxBitmap bitmap(imgCpy);
	bitMapNew = bitmap;

	if (firstChange) {
		SetStatusText(wxT("Contrast set"), 0);
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

	pickedColor = wxColor(pixels[3 * (y*w + x)], pixels[3 * (y*w + x) + 1], pixels[3 * (y*w + x) + 2]);
	std::string color = std::to_string(pickedColor.Red()) + ", " + std::to_string(pickedColor.Green()) + ", " + std::to_string(pickedColor.Blue());
	colorFromImageTxt->SetForegroundColour(pickedColor);
	colorFromImageTxt->Refresh();

	//modify color
	int r = pickedColor.Red();
	int g = pickedColor.Green();
	int b = pickedColor.Blue();

	int max_value;
	if (g >= r && g >= b) {
		max_value = g / 255;
		g = 255;
		r *= max_value;
		b *= max_value;
	}
	else if (b >= g && b >= r) {
		max_value = b / 255;
		b = 255;
		r *= max_value;
		g *= max_value;
	}
	else {
		max_value = r / 255;
		r = 255;
		g *= max_value;
		b *= max_value;
	}

	wxColour modified_color(r, g, b);
	hexagon->setSelectedColor(modified_color);

	SetStatusText(wxT("Clicked " + std::to_string(x) + ", " + std::to_string(y) + " Color: " + color), 0);
	return;
}

void MyFrame::m_buttonHistogramOnButtonClick(wxCommandEvent& event) {
	//***** Calculating the histograms *****
	int rgb_count[256] = { 0 };
	int r_count[256] = { 0 };
	int g_count[256] = { 0 };
	int b_count[256] = { 0 };
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

void MyFrame::updateHistogram(void) {
	int rgb_count_n[256] = { 0 };
	int r_count_n[256] = { 0 };
	int g_count_n[256] = { 0 };
	int b_count_n[256] = { 0 };

	calculateHistograms(imgNew, rgb_count_n, r_count_n, g_count_n, b_count_n);
	generate_hist_img(imgHistogramRGB_n, bitMapHistogramRGB_n, rgb_count_n, 0x00, 0x00, 0x00);
	generate_hist_img(imgHistogramR_n, bitMapHistogramR_n, r_count_n, 0xff, 0x00, 0x00);
	generate_hist_img(imgHistogramG_n, bitMapHistogramG_n, g_count_n, 0x00, 0xff, 0x00);
	generate_hist_img(imgHistogramB_n, bitMapHistogramB_n, b_count_n, 0x00, 0x00, 0xff);
	paintHistograms();
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
