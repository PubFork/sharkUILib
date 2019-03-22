#include "sharksplitter.h"
#include <QPainter>
#include <QMouseEvent>

#include <QDebug>
const int handle_button_width = 80;
const int minWidth = 100;

SharkSplitterHandle::SharkSplitterHandle(Qt::Orientation orientation, QSplitter *parent)
	:QSplitterHandle(orientation,parent)

{
	//MYMEMO: using splitter to left or right
	setMouseTracking(true);
}

void SharkSplitterHandle::setDeriction(int dr)//0-->collapse to left,, 1 to right
{

}

void SharkSplitterHandle::setMinimumSize() {}



void SharkSplitterHandle::drawerButton(QRect btn_rt, QPainter *P, bool isHover, bool isleft)
{
	QPainterPath PP, PA;
	P->setRenderHint(QPainter::Antialiasing);
	int X = btn_rt.x();
	int Y = btn_rt.y();
	int H = btn_rt.height();
	int W = btn_rt.width();




	if (orientation() == Qt::Horizontal)
	{
		PP.addRect(X, Y, W, handle_button_width);
		P->fillPath(PP, QColor(31, 127, 253, 96));

		X = X + 2;
		W = W - 4;
		Y = btn_rt.y() + H / 2 - W / 2 ;
		if (isleft) {
			PA.moveTo(X, Y + W );
			PA.lineTo(X + W, Y);
			PA.lineTo(X + W, Y + 2*W);
			PA.lineTo(X, Y + W );
		} else {
			PA.moveTo(X, Y);
			PA.lineTo(X + W, Y + W );
			PA.lineTo(X, Y + W*2);
			PA.lineTo(X, Y);
		}
	}
	else
	{
		PP.addRect(X, Y, handle_button_width, H);
		P->fillPath(PP, QColor(31, 127, 253, 96));

		X = btn_rt.x() + btn_rt.width()/2 ;

		if (isleft) {
			PA.moveTo(X, Y  );
			PA.lineTo(X +H-2, Y+H);
			PA.lineTo(X -H+2, Y +H);
			PA.lineTo(X, Y  );
		} else {
			PA.moveTo(X, Y+H  );
			PA.lineTo(X +H-2, Y);
			PA.lineTo(X -H+2, Y );
			PA.lineTo(X, Y+H  );
		}
	}

	P->fillPath(PA, QColor(96, 96, 96));

}

void SharkSplitterHandle::paintEvent(QPaintEvent *event)
{
	bool isLeftDriection = false;
	QPainter painter(this);
	QRect h_rt = rect();
	painter.fillRect( h_rt, QPalette().color(QPalette::AlternateBase));
	painter.drawRect(h_rt);

	if (orientation() == Qt::Horizontal)
	{
		fr_rt = QRect(0, h_rt.height()/2 -handle_button_width/2, h_rt.width(), handle_button_width);
	}
	else
	{
		fr_rt= QRect(h_rt.width() / 2 -handle_button_width/2, 0, handle_button_width, h_rt.height() );
	}


	auto szs = splitter()->sizes();
	if(splitter()->handle(splitter()->count()-1) == this)
	{
		if(szs[splitter()->count()-1] ==0)
			isLeftDriection = true;
	}
	else
	{
		for(int n= 1; n< splitter()->count(); n++)
		{
			if( splitter()->handle(n) == this)
			{
				isLeftDriection = (szs[n-1] !=0);
				break;
			}
		}
	}

	drawerButton(fr_rt,&painter,bOver,isLeftDriection);
 }
/*
void DFSplitterHandle::mousePressEvent(QMouseEvent *event)
{
	QSplitterHandle::mousePressEvent(event);
}*/
void SharkSplitterHandle::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (orientation() == Qt::Horizontal)
	{
		QRect h_rt = rect();
		QRect fr_rt(0, h_rt.height()/2 -handle_button_width/2, h_rt.width(), handle_button_width);
		auto pt1 = event->pos();

		int i = 0;
		for( i=1 ; i< splitter()->count(); i++)
		{
			if( splitter()->handle(i) == this)
				break;
		}


		if(fr_rt.contains(pt1))
		{
			auto szs = splitter()->sizes();
			emit(doubleClicked());
		}
	}
	else
	{
		QRect h_rt = rect();
		QRect fr_rt(h_rt.width() / 2 -handle_button_width/2, 0, handle_button_width, h_rt.height() );
		auto pt1 = event->pos();

		int i = 0;
		for( i=1 ; i< splitter()->count(); i++)
		{
			if( splitter()->handle(i) == this)
				break;
		}


		if(fr_rt.contains(pt1))
		{
			auto szs = splitter()->sizes();
			emit(doubleClicked());
		}
	}
}
void SharkSplitterHandle::mouseMoveEvent(QMouseEvent *event)
{
	QSplitterHandle::mouseMoveEvent(event);
	auto pt1 = event->pos();

	setCursor(Qt::SplitHCursor);
	//qDebug() << __FUNCTION__ << pt1 << fr_rt;
	if(fr_rt.contains(pt1))
	{

		setCursor(Qt::ArrowCursor);
		bOver =true;
		return;
	}
	if( event->button()  | Qt::LeftButton)
	{
		if(pt1.y() > fr_rt.y() && pt1.y() < fr_rt.bottom())
			return;
	}	
	update();

}

void SharkSplitterHandle::enterEvent(QEvent *event)
{
	QSplitterHandle::enterEvent(event);
}
void SharkSplitterHandle::leaveEvent(QEvent *event)
{
	update();
	QSplitterHandle::leaveEvent(event);
}

void SharkSplitterHandle::h_draw()
{

}

void SharkSplitterHandle::v_draw()
{

}


void SharkSplitterHandle::moveEvent(QMoveEvent *event)
{
	auto pt1 = event->pos();
	if(fr_rt.contains(pt1))
		setCursor(Qt::ArrowCursor);
	else
		setCursor(Qt::SplitHCursor);
}

void SharkSplitterHandle::resizeEvent(QResizeEvent *event)
{

}


SharkSplitter::SharkSplitter(Qt::Orientation orientation, QWidget *parent )
	:QSplitter (orientation, parent)
{
	setHandleWidth(1);
	connect(this, SIGNAL(splitterMoved(int , int )), this , SLOT(slotHandleMoved(int, int)));
}

SharkSplitter::SharkSplitter( QWidget *parent )
	:QSplitter ( parent)
{
	setHandleWidth(1);
	connect(this, SIGNAL(splitterMoved(int , int )), this , SLOT(slotHandleMoved(int, int)));
}

QSplitterHandle *SharkSplitter::createHandle()
  {
	  auto hd =  new SharkSplitterHandle(orientation(), this);
	  connect(hd, SIGNAL(doubleClicked()), this, SLOT(doubleclicked_handle_event()));
	  _sizes_last<< minWidth;
	  _sizs_minimum << minWidth;
	  return hd;
}


void SharkSplitter::resizeEvent(QResizeEvent *event)
{
	 QSplitter::resizeEvent(event);
 }

void SharkSplitter::slotHandleMoved(int pos,int index)
{
	auto szs = sizes();
	_sizes_last = szs;
	QList<int > n_szs;
	if(count() == 2)
	{
		if( szs[0] < minWidth)
			n_szs << minWidth << width() - minWidth;
		else if( szs[1] < minWidth)
			n_szs << width() - minWidth << minWidth;
	}
	else
	{

	}
	if(n_szs.count() > 1 )
		setSizes(n_szs);

}

 void SharkSplitter::doubleclicked_handle_event()
 {
	 SharkSplitterHandle* hd = (SharkSplitterHandle*) sender();
	 auto szs = sizes();
	 if( hd == handle(1) && count() == 2)
	 {
		 if(szs[1] != 0)
			 setSizes( QList<int>() << width() << 0);
		 else
			 setSizes( QList<int>() << width()-_sizes_last[1] << _sizes_last[1]);
	 }
	 else if( hd == handle(1) && count() > 2)
	 {
		 QList<int> n_szs;
		if(szs[0] == 0)
		{
			setSizes( _sizes_last );
		}
		else
		{
			n_szs << 0 << szs[0] + szs[1];
			for(int n =2; n < count(); n++)
			{
				n_szs << szs[n];
			}
			setSizes(n_szs);
		}

	 }
	 else if( hd == handle( count() -1 ) && count() > 2)
	 {
		 if( szs[ count() -1] ==0 )
		 {
			 setSizes( _sizes_last );
		 }
		 else
		 {
			QList<int> n_szs;
			for(int n= 0; n < count()-2; n++)
				n_szs << szs[n];
			n_szs << szs[count() -2] + szs[count() - 1] << 0;
			setSizes(n_szs);
		 }

	 }
	 else
	 {

		 int i = 0;
		 for( i=1 ; i< count(); i++)
		 {
			 if( handle(i) == hd)
				 break;
		 }
		 i-=1;

		 QList<int> n_szs;
		if(szs[i] == 0)
		{
			setSizes( _sizes_last );
		}
		else
		{
			for(int n=0; n<i; n++)
				n_szs  << szs[n];
			n_szs << 0 << szs[i] + szs[i+1];
			for(int n= i+2; n < count(); n++)
				n_szs << szs[n];
			setSizes(n_szs);
		}
	 }
 }


