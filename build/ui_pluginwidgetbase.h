#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading ui file 'pluginwidgetbase.ui'
**
** Created: Tue Apr 7 14:55:38 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PLUGINWIDGETBASE_H
#define UI_PLUGINWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginWidgetBase
{
public:
    QHBoxLayout *horizontalLayout;
    QListView *availableView;

    void setupUi(QWidget *PluginWidgetBase)
    {
        if (PluginWidgetBase->objectName().isEmpty())
            PluginWidgetBase->setObjectName(QString::fromUtf8("PluginWidgetBase"));
        PluginWidgetBase->resize(400, 256);
        horizontalLayout = new QHBoxLayout(PluginWidgetBase);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        availableView = new QListView(PluginWidgetBase);
        availableView->setObjectName(QString::fromUtf8("availableView"));

        horizontalLayout->addWidget(availableView);


        retranslateUi(PluginWidgetBase);

        QMetaObject::connectSlotsByName(PluginWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *PluginWidgetBase)
    {
        PluginWidgetBase->setWindowTitle(tr2i18n("Form", 0));
        Q_UNUSED(PluginWidgetBase);
    } // retranslateUi

};

namespace Ui {
    class PluginWidgetBase: public Ui_PluginWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PLUGINWIDGETBASE_H

