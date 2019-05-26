#pragma once
#include <wx/colour.h>
#include <wx/control.h>
#include <wx/panel.h>
#include <wx/dcscreen.h>
#include <wx/dcclient.h>

class ColorsHexagon : public wxPanel {
	static const int hexagonWidth = 200;
	static const int hexagonHeight = 200;

	wxColor selectedColor;
	wxWindow * parent;
	wxWindowDC * windowDC;
	wxImage areaImage;

	//small hack
	wxControl * reactControl;
	wxColor * hexColor;

	int ptrPos_x = hexagonWidth/2;
	int ptrPos_y = hexagonHeight/2;

public:
	ColorsHexagon(wxPanel* parent);
	ColorsHexagon(wxPanel* parent, wxControl * control, wxColor * color);
	~ColorsHexagon();

	void paintEvent(wxPaintEvent & evt);
	void leftClick(wxMouseEvent& event);

	wxColor getSelectedColor();
	void setSelectedColor(const wxColor &color);
	void setPointerPosition(int pos_x, int pos_y);

	DECLARE_EVENT_TABLE()
};