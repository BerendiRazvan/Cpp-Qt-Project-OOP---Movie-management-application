#pragma once
#include "qwidget.h"
#include "qpainter.h"
#include "qimage.h"
#include "qdebug.h"

#include "ServiceApp.h"
#include "Observer.h"

class CosReadOnlyGUI:public  QWidget, public Observer
{
private:

	ServFilme& serv;

public:
	QPaintEvent* evM;
	void update() override { paintEvent(evM); };
	void paintEvent(QPaintEvent* ev) override;

	CosReadOnlyGUI(ServFilme& serv) :serv{serv} {
		resize(700, 500);
		serv.totCosul().addObserver(this);
		paintEvent(evM);
	}
	~CosReadOnlyGUI() {
		serv.totCosul().removeObserver(this);
	}

};

