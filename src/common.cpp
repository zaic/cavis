#include "common.h"

QPushButton* createButtonFromIcon(const char* icon_path, int icon_size, int button_size)
{
    if(button_size == -1) button_size = icon_size;
    QPushButton *button = new QPushButton;
    button->setFixedSize(button_size, button_size);
    button->setIcon(QIcon(icon_path));
    button->setIconSize(QSize(icon_size, icon_size));
    return button;
}
