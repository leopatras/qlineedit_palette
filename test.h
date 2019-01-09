#include <QWidget>
#include <QPalette>

class MyWidget : public QWidget
{
  Q_OBJECT

public:

  MyWidget( QWidget * parent );

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

  static void setWidgetBackground( QWidget* w, const QColor& c, QPalette* p = NULL  , PaletteRoles role = RoleAll );

};
