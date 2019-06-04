#include "MyBrightnessSaturationContrastDialog.h"
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


void MyBrightnessSaturationContrastDialog::OnScrollingBrightness(wxScrollEvent& event) {
	double value = m_BrightnessScrollBar->GetValue();
	brightnessValue = value;
	static_cast<MyFrame*>(GetParent())->setBrightness(brightnessValue, m_BrightnessScrollBar->GetMin(), m_BrightnessScrollBar->GetMax());

	static_cast<MyFrame*>(GetParent())->setSaturation(saturationValue, m_SaturationScrollBar->GetMin(), m_SaturationScrollBar->GetMax(), false);
	static_cast<MyFrame*>(GetParent())->setContrast(contrastValue, m_ContrastScrollBar->GetMin(), m_ContrastScrollBar->GetMax(), false);

	value = (value - m_BrightnessScrollBar->GetMin()) / (m_BrightnessScrollBar->GetMax() - m_BrightnessScrollBar->GetMin());
	value = value * (m_BrightnessSetOnEnter->GetMax() - m_BrightnessSetOnEnter->GetMin()) + m_BrightnessSetOnEnter->GetMin();

	m_BrightnessSetOnEnter->SetValue(value);

	static_cast<MyFrame*>(GetParent())->Repaint();

}

void MyBrightnessSaturationContrastDialog::OnScrollingSaturation(wxScrollEvent& event) {
	double value = m_SaturationScrollBar->GetValue();
	saturationValue = value;
	static_cast<MyFrame*>(GetParent())->setSaturation(saturationValue, m_SaturationScrollBar->GetMin(), m_SaturationScrollBar->GetMax());

	static_cast<MyFrame*>(GetParent())->setBrightness(brightnessValue, m_BrightnessScrollBar->GetMin(), m_BrightnessScrollBar->GetMax(), false);
	static_cast<MyFrame*>(GetParent())->setContrast(contrastValue, m_ContrastScrollBar->GetMin(), m_ContrastScrollBar->GetMax(), false);


	value = (value - m_SaturationScrollBar->GetMin()) / (m_SaturationScrollBar->GetMax() - m_SaturationScrollBar->GetMin());
	value = value * (m_SaturationSetOnEnter->GetMax() - m_SaturationSetOnEnter->GetMin()) + m_SaturationSetOnEnter->GetMin();

	m_SaturationSetOnEnter->SetValue(value);

	static_cast<MyFrame*>(GetParent())->Repaint();
}

void MyBrightnessSaturationContrastDialog::OnScrollingContrast(wxScrollEvent& event) {
	double value = m_ContrastScrollBar->GetValue();
	contrastValue = value;
	static_cast<MyFrame*>(GetParent())->setContrast(contrastValue, m_ContrastScrollBar->GetMin(), m_ContrastScrollBar->GetMax());

	static_cast<MyFrame*>(GetParent())->setBrightness(brightnessValue, m_BrightnessScrollBar->GetMin(), m_BrightnessScrollBar->GetMax(), false);
	static_cast<MyFrame*>(GetParent())->setSaturation(saturationValue, m_SaturationScrollBar->GetMin(), m_SaturationScrollBar->GetMax(), false);


	value = (value - m_ContrastScrollBar->GetMin()) / (m_ContrastScrollBar->GetMax() - m_ContrastScrollBar->GetMin());
	value = value * (m_ContrastSetOnEnter->GetMax() - m_ContrastSetOnEnter->GetMin()) + m_ContrastSetOnEnter->GetMin();

	m_ContrastSetOnEnter->SetValue(value);

	static_cast<MyFrame*>(GetParent())->Repaint();
}

void MyBrightnessSaturationContrastDialog::BrightnessReset(wxCommandEvent& event) {
	wxScrollEvent tmp{};
	int value = (m_BrightnessScrollBar->GetMax() + m_BrightnessScrollBar->GetMin()) / 2.0;
	m_BrightnessScrollBar->SetValue(value);

	int valueOnEnter = (m_BrightnessSetOnEnter->GetMax() + m_BrightnessSetOnEnter->GetMin()) / 2.0;
	m_BrightnessSetOnEnter->SetValue(0);
	OnScrollingBrightness(tmp);
}

void MyBrightnessSaturationContrastDialog::SaturationReset(wxCommandEvent& event) {
	wxScrollEvent tmp{};
	int value = (m_SaturationScrollBar->GetMax() + m_SaturationScrollBar->GetMin()) / 2.0;
	m_SaturationScrollBar->SetValue(value);

	int valueOnEnter = (m_SaturationSetOnEnter->GetMax() + m_SaturationSetOnEnter->GetMin()) / 2.0;
	m_SaturationSetOnEnter->SetValue(0);
	OnScrollingSaturation(tmp);
}

void MyBrightnessSaturationContrastDialog::ContrastReset(wxCommandEvent& event) {
	wxScrollEvent tmp{};
	int value = (m_ContrastScrollBar->GetMax() + m_ContrastScrollBar->GetMin()) / 2;
	m_ContrastScrollBar->SetValue(value);

	int valueOnEnter = (m_ContrastSetOnEnter->GetMax() + m_ContrastSetOnEnter->GetMin()) / 2.0;
	m_ContrastSetOnEnter->SetValue(0);
	OnScrollingContrast(tmp);
}

void MyBrightnessSaturationContrastDialog::OnSpinBrightness(wxSpinEvent& event) {
	double value = m_BrightnessSetOnEnter->GetValue();
	value = ((value - m_BrightnessSetOnEnter->GetMin()) / (m_BrightnessSetOnEnter->GetMax() - m_BrightnessSetOnEnter->GetMin())) * (double)(m_BrightnessScrollBar->GetMax() - m_BrightnessScrollBar->GetMin());
	wxScrollEvent tmp{};
	m_BrightnessScrollBar->SetValue((int)value);
	OnScrollingBrightness(tmp);
}


void MyBrightnessSaturationContrastDialog::OnSpinSaturation(wxSpinEvent& event) {
	double value = m_SaturationSetOnEnter->GetValue();
	value = ((value - m_SaturationSetOnEnter->GetMin()) / (m_SaturationSetOnEnter->GetMax() - m_SaturationSetOnEnter->GetMin())) * (double)(m_SaturationScrollBar->GetMax() - m_SaturationScrollBar->GetMin());
	wxScrollEvent tmp{};
	m_SaturationScrollBar->SetValue((int)value);
	OnScrollingSaturation(tmp);
}

void MyBrightnessSaturationContrastDialog::OnSpinContrast(wxSpinEvent& event) {
	double value = m_ContrastSetOnEnter->GetValue();
	value = ((value - m_ContrastSetOnEnter->GetMin()) / (m_ContrastSetOnEnter->GetMax() - m_ContrastSetOnEnter->GetMin())) * (double)(m_ContrastScrollBar->GetMax() - m_ContrastScrollBar->GetMin());
	wxScrollEvent tmp{};
	m_ContrastScrollBar->SetValue((int)value);
	OnScrollingContrast(tmp);
}