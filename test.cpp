#include "test.h"
#include <QApplication>
#include <QLineEdit>
#include <QComboBox>
#include <QMainWindow>
#include <QLayout>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
MyWidget::MyWidget( QWidget * parent ) : QWidget( parent ) 
{}

//this is our function setting background colors since 10 years
void MyWidget::setWidgetBackground( QWidget* w, const QColor& c, QPalette* p, PaletteRoles role )
{
  if( c.isValid() )
  {
    QPalette pal = ( p ? *p : w->palette() );
    w->setAutoFillBackground( c.alpha() != 0 );

    if( role.testFlag( RoleAll ) || role.testFlag( RoleBackgroundRole ) )
    {
      pal.setColor( w->backgroundRole(), c );
    }

    if( role.testFlag( RoleAll ) || role.testFlag( RoleBase ) )
    {
      pal.setColor( QPalette::Base, c );
    }

    if( role.testFlag( RoleAll ) || role.testFlag( RoleWindow ) )
    {
      pal.setColor( QPalette::Window, c );
    }

    w->setPalette( pal );
  }
  else
  {
    w->setAutoFillBackground( false );
  }
}


int main(int argc, char **argv)
{
  //qDebug() << MyWidget::RoleAll;
  QApplication qapp( argc, argv );
  QMainWindow win;
  QWidget central( &win );
  win.setCentralWidget( &central );
  QGridLayout layout( &central );

  QLineEdit le1( &central );
  MyWidget::setWidgetBackground( &le1, Qt::red );
  QComboBox q( &central );
  MyWidget::setWidgetBackground( &q, Qt::magenta );

  //just an additional  very basic trial
  QLineEdit le2( &central );
  le2.setAutoFillBackground( true );
  QPalette p = le2.palette();
  p.setColor( QPalette::Base, Qt::green );
  le2.setPalette( p );


  layout.addWidget( &le1, 0, 0 );
  layout.addWidget( &q, 1, 0 );
  layout.addWidget( &le2, 2, 0 );

  le1.setMinimumWidth( 200 );
  le1.setMinimumWidth( 200 );

  le1.setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
  q.setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
  le2.setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );

  layout.addItem( new QSpacerItem( 0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding ), 10, 10 );

  win.show();
  return qapp.exec();
}
