#include "CosReadOnlyGUI.h"


void CosReadOnlyGUI::paintEvent(QPaintEvent* ev){
	QPainter p{ this };
	int i = serv.getCos().size();
	int x = 0, y = 0;

	while (i) {

		p.drawImage(x, y, QImage("img.png"));

		if (x + 105 < width())
			x = x + 55;
		else {
			x = 0;
			y = y + 55;
			if (y > height())
				qDebug() << "Dimensiune fereastra depasita!";
		}

		i--;
	}
}