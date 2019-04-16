#ifndef SINGLEDIALG_H
#define SINGLEDIALG_H

#include <QObject>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include "ui_inputdialog.h"


template< class Type >
class SingleInputDialog : public QDialog
{

public:
	explicit SingleInputDialog(QString str,QWidget *parent = 0) :
		QDialog(parent),
		ui(new Ui::InputDialog)
	{
		ui->setupUi(this);
		_layout = new QGridLayout(this);
		_layout->setContentsMargins(2,2,2,2);
		setLayout(_layout);
		setWindowTitle( tr("Please input datas"));

		int n=0;
		_widget= new Type();
		QLabel* lbl = new QLabel(str);
		lbl->setAlignment(Qt::AlignTop);
		_layout->addWidget(lbl, n,0);
		_layout->addWidget(_widget, n,1);

		QSizePolicy pl(QSizePolicy::Expanding,QSizePolicy::Preferred);
		pl.setVerticalStretch(2);

		_widget->setSizePolicy(pl);
		n++;

		_layout->addItem( new QSpacerItem(10,10,QSizePolicy::Minimum, QSizePolicy::Expanding) ,n,0);
		n++;
		_layout->addWidget( ui->buttonBox,n,0,1,2);
	}




	Type* widget()
	{
		return _widget;
	}

	~SingleInputDialog()
	{

	}


private:
	Ui::InputDialog *ui;
	Type* _widget;
	QGridLayout* _layout;

};


template< class Type1,class Type2, class Type3 >
class MultipleInputDialog : public QDialog
{

public:
	explicit MultipleInputDialog(QString str1,QString str2,QString str3,QWidget *parent = 0) :
		QDialog(parent),
		ui(new Ui::InputDialog)
	{
		ui->setupUi(this);
		_layout = new QGridLayout(this);
		_layout->setContentsMargins(2,2,2,2);
		setLayout(_layout);
		setWindowTitle( tr("Please input datas"));

		QSizePolicy pl(QSizePolicy::Expanding,QSizePolicy::Preferred);
		pl.setVerticalStretch(2);


		int n=0;
		_widget1= new Type1();
		QLabel* lbl = new QLabel(str1);
		lbl->setAlignment(Qt::AlignTop);
		_layout->addWidget(lbl, n,0);
		_layout->addWidget(_widget1, n,1);
		_widget1->setSizePolicy(pl);
		n++;

		_widget2= new Type2();
		QLabel* lb2 = new QLabel(str2);
		lb2->setAlignment(Qt::AlignTop);
		_layout->addWidget(lb2, n,0);
		_layout->addWidget(_widget2, n,1);
		_widget2->setSizePolicy(pl);
		n++;

		_widget3= new Type1();
		QLabel* lb3 = new QLabel(str3);
		lb3->setAlignment(Qt::AlignTop);
		_layout->addWidget(lb3, n,0);
		_layout->addWidget(_widget3, n,1);
		_widget3->setSizePolicy(pl);
		n++;


		_layout->addItem( new QSpacerItem(10,10,QSizePolicy::Minimum, QSizePolicy::Expanding) ,n,0);
		n++;
		_layout->addWidget( ui->buttonBox,n,0,1,2);
	}




	Type1* widget(Type1*)
	{
		return _widget1;
	}

	Type2* widget(Type2*)
	{
		return _widget2;
	}
	Type3* widget(Type3*)
	{
		return _widget3;
	}
	~MultipleInputDialog()
	{

	}


private:
	Ui::InputDialog *ui;
	Type1* _widget1;
	Type2* _widget2;
	Type3* _widget3;
	QGridLayout* _layout;

};
#endif // SINGLEDIALG_H
