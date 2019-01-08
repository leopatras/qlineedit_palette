#include <QApplication>
#include <QLineEdit>
#include <QMainWindow>
#include <QLayout>

class MyLineEdit : public QLineEdit
{
  Q_OBJECT

public:

  MyLineEdit( QWidget * parent );

  // Change widget background and foreground colors
  enum PaletteRole {
    RoleNo = 0x0,
    RoleBackgroundRole = 0x1,
    RoleWindow = 0x2,
    RoleBase = 0x4,
    RoleForegroundRole = 0x8,
    RoleText = 0x10,
    RoleWindowText = 0x20,
    RoleButtonText = 0x40,
    RoleAll = 0x80
  };

  Q_DECLARE_FLAGS( PaletteRoles, PaletteRole )
  Q_FLAG( PaletteRoles )

  void setWidgetBackground( const QColor& c, QPalette* p = NULL, bool set = true );
  static const QMetaObject* getQtMetaObject()
  {
    return &staticMetaObject;
  }
};
