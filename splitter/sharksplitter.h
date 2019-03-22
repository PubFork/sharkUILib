#ifndef DFSPLITTER_H
#define DFSPLITTER_H

#include <QObject>
#include <QSplitter>
#include <QToolButton>

#include "uiglobal.h"

class SharkSplitterHandle: public QSplitterHandle
{
	Q_OBJECT
public:
	SharkSplitterHandle(Qt::Orientation orientation, QSplitter *parent=0);
	void setDeriction(int dr =1);
	void setMinimumSize();
signals:
	void doubleClicked();
protected:
	// QWidget interface
	void paintEvent(QPaintEvent *event);
	//void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void drawerButton(QRect btn_rt, QPainter *P, bool isHover, bool isleft);

	int oldWidth;
	bool bOver ;

	QRect fr_rt;

	// QWidget interface
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

	void h_draw();
	void v_draw();

	// QWidget interface
protected:
	void moveEvent(QMoveEvent *event);

	// QWidget interface
protected:
	void resizeEvent(QResizeEvent *event);
};

class SharkSplitter : public QSplitter
{
	Q_OBJECT
public:
	SharkSplitter(Qt::Orientation orientation= Qt::Horizontal, QWidget *parent = 0);
	SharkSplitter( QWidget *parent = 0);

protected:
	QSplitterHandle *createHandle();

	// QWidget interface

	void resizeEvent(QResizeEvent *event);

	QList<int> _sizes_last;
	QList<int> _sizs_minimum;



protected slots:
	  void doubleclicked_handle_event();
	  void slotHandleMoved(int pos,int index);
};

#endif // DFSPLITTER_H
