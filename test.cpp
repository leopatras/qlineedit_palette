#include "test.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>
MyLineEdit::MyLineEdit( QWidget * parent ) : QLineEdit( parent ) 
{
}

void MyLineEdit::setWidgetBackground( const QColor& c, QPalette* p , bool set )
{
  if( c.isValid() )
  {
    PaletteRoles role = RoleAll;

    QPalette pal = ( p ? *p : palette() );
    setAutoFillBackground( c.alpha() != 0 );

    if( role.testFlag( RoleAll ) || role.testFlag( RoleBackgroundRole ) )
    {
      pal.setColor( backgroundRole(), c );
    }

    if( role.testFlag( RoleAll ) || role.testFlag( RoleBase ) )
    {
      pal.setColor( QPalette::Base, c );
    }

    if( role.testFlag( RoleAll ) || role.testFlag( RoleWindow ) )
    {
      pal.setColor( QPalette::Window, c );
    }

    if( set )
    {
      setPalette( pal );
    }
  }
  else
  {
    setAutoFillBackground( false );
  }
}

//fake class for getting the QtMetaObject...
class MetaSucker : public QObject
{
public:

  static const QMetaObject* getQtMetaObject()
  {
    return &staticQtMetaObject;
  }
};

static QString getEnumValueInt( const QMetaObject* m, const QString& enumVar, int enumVal )
{
  int index = m->indexOfEnumerator( qPrintable( enumVar ) );

  if( index != -1 )
  {
    QMetaEnum menum = m->enumerator( index );

    if( enumVar == menum.name() )
    {
      if( menum.isFlag() )
      {
        return QString::fromLatin1( menum.valueToKeys( enumVal ) );
      }
      else
      {
        return QString::fromLatin1( menum.valueToKey( enumVal ) );
      }
    }
  }

  return QString();
}

static QString getStringFromEnum( const char* const enumName, int enumVal, QObject* o = NULL )
{
  const QMetaObject* qt = MyLineEdit::getQtMetaObject();
  const QString res = getEnumValueInt( qt, enumName, enumVal );

  if( !res.isNull() || o == NULL )
  {
    return res;
  }

  return getEnumValueInt( o->metaObject(), enumName, enumVal );
}

int main(int argc, char **argv)
{
  qDebug() << getStringFromEnum( "PaletteRoles", MyLineEdit::RoleAll );
  QApplication qapp( argc, argv );
  QMainWindow win;
  QWidget central( &win );
  win.setCentralWidget( &central );
  QGridLayout layout( &central );

  MyLineEdit le1( &central );
  le1.setWidgetBackground( Qt::red );
  QLineEdit le2( &central );
  le2.setAutoFillBackground( true );
  QPalette p = le2.palette();
  p.setColor( QPalette::Base, Qt::green );
  le2.setPalette( p );


  layout.addWidget( &le1, 0, 0 );
  layout.addWidget( &le2, 1, 0 );

  le1.setMinimumWidth( 200 );
  le1.setMinimumWidth( 200 );

  le1.setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );
  le2.setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed );

  layout.addItem( new QSpacerItem( 0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding ), 10, 10 );

  win.show();
  return qapp.exec();
}
