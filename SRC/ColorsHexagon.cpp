#include <wx/colour.h>
#include <iostream>
#include <wx/control.h>
#include <wx/frame.h>
#include <wx/graphics.h>
#include <wx/msgdlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include "ColorsHexagon.h"
#include <cmath>

BEGIN_EVENT_TABLE(ColorsHexagon, wxPanel)
	EVT_LEFT_DOWN(ColorsHexagon::leftClick)
	EVT_PAINT(ColorsHexagon::paintEvent)
END_EVENT_TABLE()


ColorsHexagon::ColorsHexagon(wxPanel* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(hexagonWidth, hexagonHeight)) {
	this->parent = parent;
	this->windowDC = new wxWindowDC(this);
	this->areaImage.Create(hexagonWidth, hexagonHeight);

	for (int i = 0; i < hexagonWidth; i++) {
		for (int j = 0; j < hexagonHeight; j++) {
			this->areaImage.SetRGB(i, j, 255, 255, 255);
		}
	}
}

ColorsHexagon::ColorsHexagon(wxPanel* parent, wxControl * control, wxColor * color) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(hexagonWidth, hexagonHeight)) {
	this->parent = parent;
	this->reactControl = control;
	this->hexColor = color;
	this->windowDC = new wxWindowDC(this);
	this->areaImage.Create(hexagonWidth, hexagonHeight);

	for (int i = 0; i < hexagonWidth; i++) {
		for (int j = 0; j < hexagonHeight; j++) {
			this->areaImage.SetRGB(i, j, 255, 255, 255);
		}
	}
}

ColorsHexagon::~ColorsHexagon() {
	//this->areaImage.Clear();
}

void ColorsHexagon::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	wxMemoryDC memDC;

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
			constBlueHexagon.SetRGB(j, i + j/2, 255 - step_a_blue * i, step_b_blue * j, 255);
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
			constGreenHexagon.SetRGB(j, i - j/2 + 65, 255 - step_a_green * i, 255, 255 - step_b_green * j);
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
			constRedHexagon.SetRGB(j, i, 255, step_a_red * i, 255 - step_b_red * j);
		}
	}

	const double angle = 2 * M_PI / 360;
	constRedHexagon = constRedHexagon.Rotate(angle * 45, wxPoint(50, 50));
	constRedHexagon = constRedHexagon.Scale(145, 85);

	wxBitmap map = wxBitmap(this->areaImage);
	memDC.SelectObject(map);
	memDC.DrawBitmap(wxBitmap(constRedHexagon), 28, 7, true);
	memDC.DrawBitmap(wxBitmap(constGreenHexagon), 100, 20, true);
	memDC.DrawBitmap(wxBitmap(constBlueHexagon), 30, 50, true);

	memDC.SetPen(wxPen(wxColor(0, 0, 0)));
	memDC.SetBrush(*wxBLACK_BRUSH);
	memDC.DrawCircle(ptrPos_x, ptrPos_y, 1);
	dc.Blit(0, 0, hexagonWidth, hexagonHeight, &memDC, 0, 0, wxCOPY, true);
}


void ColorsHexagon::leftClick(wxMouseEvent& event) {
	const wxPoint mousePoint = wxGetMousePosition();
	int mouseX = mousePoint.x - this->GetScreenPosition().x;
	int mouseY = mousePoint.y - this->GetScreenPosition().y;

	const wxPoint widgetPoint = this->GetPosition();
	int windowX = widgetPoint.x;
	int windowY = widgetPoint.y;

	if (mouseX < windowX + hexagonWidth && mouseY < windowY + hexagonHeight && mouseX != ptrPos_x && mouseY != ptrPos_y) {
		setPointerPosition(mouseX, mouseY);

		wxColor color;
		this->windowDC->GetPixel(mouseX, mouseY, &color);

		this->selectedColor = color;

		if (this->reactControl != nullptr) {
			this->hexColor->SetRGB(color.GetRGB());
			this->reactControl->SetForegroundColour(color);
			this->reactControl->Refresh();
		}

		this->parent->Refresh();
	}
}

wxColor ColorsHexagon::getSelectedColor() { 
	return this->selectedColor; 
}

void ColorsHexagon::setSelectedColor(const wxColor &color) { 
	for (int i = 0; i < hexagonWidth; i++) {
		for (int j = 0; j < hexagonHeight; j++) {
			wxColor tmp(this->areaImage.GetRed(i, j), this->areaImage.GetGreen(i, j), this->areaImage.GetBlue(i, j));

			if (tmp == color) {
				setPointerPosition(i, j);
				this->selectedColor = color;
				this->Refresh();
				break;
			}
		}
	}
}

void ColorsHexagon::setPointerPosition(int pos_x, int pos_y) {
	this->ptrPos_x = pos_x;
	this->ptrPos_y = pos_y;
}