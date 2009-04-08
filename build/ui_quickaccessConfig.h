#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading ui file 'quickaccessConfig.ui'
**
** Created: Wed Apr 8 23:24:38 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QUICKACCESSCONFIG_H
#define UI_QUICKACCESSCONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kicondialog.h"
#include "klineedit.h"
#include "ktabwidget.h"
#include "kurlrequester.h"

QT_BEGIN_NAMESPACE

class Ui_QuickAccessConfig
{
public:
    QWidget *general;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *selectLabel;
    KUrlRequester *urlRequester;
    QLabel *filterLabel;
    QHBoxLayout *horizontalLayout;
    KLineEdit *filterEdit;
    QSpacerItem *horizontalSpacer;
    QCheckBox *hiddenBox;
    QCheckBox *onlyDirsBox;
    QCheckBox *navigationBox;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *singleClickBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *dolphinSortingBox;
    QSpacerItem *verticalSpacer_2;
    QWidget *appearance;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    KIconButton *iconbutton;
    QLabel *label;
    QComboBox *iconSizeCombo;
    QLabel *label_3;
    QComboBox *viewModeCombo;
    QCheckBox *tooltipBox;
    QCheckBox *customLabelBox;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *customLabel;
    QLineEdit *customLabelEdit;
    QSpacerItem *verticalSpacer;
    QWidget *preview;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *previewBox;
    QFrame *line;
    QLabel *previewLabel1;
    QHBoxLayout *pluginLayout;
    QLabel *previewLabel2;
    QFrame *line_2;

    void setupUi(KTabWidget *QuickAccessConfig)
    {
        if (QuickAccessConfig->objectName().isEmpty())
            QuickAccessConfig->setObjectName(QString::fromUtf8("QuickAccessConfig"));
        QuickAccessConfig->resize(414, 236);
        general = new QWidget();
        general->setObjectName(QString::fromUtf8("general"));
        verticalLayout_2 = new QVBoxLayout(general);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        selectLabel = new QLabel(general);
        selectLabel->setObjectName(QString::fromUtf8("selectLabel"));
        selectLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, selectLabel);

        urlRequester = new KUrlRequester(general);
        urlRequester->setObjectName(QString::fromUtf8("urlRequester"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(urlRequester->sizePolicy().hasHeightForWidth());
        urlRequester->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, urlRequester);

        filterLabel = new QLabel(general);
        filterLabel->setObjectName(QString::fromUtf8("filterLabel"));
        filterLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, filterLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        filterEdit = new KLineEdit(general);
        filterEdit->setObjectName(QString::fromUtf8("filterEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filterEdit->sizePolicy().hasHeightForWidth());
        filterEdit->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(filterEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        formLayout_2->setLayout(1, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout_2->addLayout(formLayout_2);

        hiddenBox = new QCheckBox(general);
        hiddenBox->setObjectName(QString::fromUtf8("hiddenBox"));

        verticalLayout_2->addWidget(hiddenBox);

        onlyDirsBox = new QCheckBox(general);
        onlyDirsBox->setObjectName(QString::fromUtf8("onlyDirsBox"));

        verticalLayout_2->addWidget(onlyDirsBox);

        navigationBox = new QCheckBox(general);
        navigationBox->setObjectName(QString::fromUtf8("navigationBox"));

        verticalLayout_2->addWidget(navigationBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        singleClickBox = new QCheckBox(general);
        singleClickBox->setObjectName(QString::fromUtf8("singleClickBox"));
        singleClickBox->setEnabled(false);
        singleClickBox->setChecked(true);

        horizontalLayout_4->addWidget(singleClickBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        dolphinSortingBox = new QCheckBox(general);
        dolphinSortingBox->setObjectName(QString::fromUtf8("dolphinSortingBox"));
        dolphinSortingBox->setEnabled(false);

        horizontalLayout_2->addWidget(dolphinSortingBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        QuickAccessConfig->addTab(general, QString());
        appearance = new QWidget();
        appearance->setObjectName(QString::fromUtf8("appearance"));
        verticalLayout = new QVBoxLayout(appearance);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_2 = new QLabel(appearance);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        iconbutton = new KIconButton(appearance);
        iconbutton->setObjectName(QString::fromUtf8("iconbutton"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(iconbutton->sizePolicy().hasHeightForWidth());
        iconbutton->setSizePolicy(sizePolicy3);
        iconbutton->setIconSize(48);

        formLayout->setWidget(0, QFormLayout::FieldRole, iconbutton);

        label = new QLabel(appearance);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        iconSizeCombo = new QComboBox(appearance);
        iconSizeCombo->setObjectName(QString::fromUtf8("iconSizeCombo"));

        formLayout->setWidget(1, QFormLayout::FieldRole, iconSizeCombo);

        label_3 = new QLabel(appearance);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        viewModeCombo = new QComboBox(appearance);
        viewModeCombo->setObjectName(QString::fromUtf8("viewModeCombo"));

        formLayout->setWidget(2, QFormLayout::FieldRole, viewModeCombo);


        verticalLayout->addLayout(formLayout);

        tooltipBox = new QCheckBox(appearance);
        tooltipBox->setObjectName(QString::fromUtf8("tooltipBox"));

        verticalLayout->addWidget(tooltipBox);

        customLabelBox = new QCheckBox(appearance);
        customLabelBox->setObjectName(QString::fromUtf8("customLabelBox"));

        verticalLayout->addWidget(customLabelBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        customLabel = new QLabel(appearance);
        customLabel->setObjectName(QString::fromUtf8("customLabel"));
        customLabel->setEnabled(false);
        customLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(customLabel);

        customLabelEdit = new QLineEdit(appearance);
        customLabelEdit->setObjectName(QString::fromUtf8("customLabelEdit"));
        customLabelEdit->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(customLabelEdit->sizePolicy().hasHeightForWidth());
        customLabelEdit->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(customLabelEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 73, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        QuickAccessConfig->addTab(appearance, QString());
        preview = new QWidget();
        preview->setObjectName(QString::fromUtf8("preview"));
        verticalLayout_4 = new QVBoxLayout(preview);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        previewBox = new QCheckBox(preview);
        previewBox->setObjectName(QString::fromUtf8("previewBox"));

        verticalLayout_4->addWidget(previewBox);

        line = new QFrame(preview);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        previewLabel1 = new QLabel(preview);
        previewLabel1->setObjectName(QString::fromUtf8("previewLabel1"));

        verticalLayout_4->addWidget(previewLabel1);

        pluginLayout = new QHBoxLayout();
        pluginLayout->setObjectName(QString::fromUtf8("pluginLayout"));
        previewLabel2 = new QLabel(preview);
        previewLabel2->setObjectName(QString::fromUtf8("previewLabel2"));
        previewLabel2->setWordWrap(true);

        pluginLayout->addWidget(previewLabel2);

        line_2 = new QFrame(preview);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        pluginLayout->addWidget(line_2);


        verticalLayout_4->addLayout(pluginLayout);

        QuickAccessConfig->addTab(preview, QString());
#ifndef UI_QT_NO_SHORTCUT
        selectLabel->setBuddy(urlRequester);
        filterLabel->setBuddy(filterEdit);
        customLabel->setBuddy(customLabelEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(QuickAccessConfig);
        QObject::connect(customLabelBox, SIGNAL(clicked(bool)), customLabel, SLOT(setEnabled(bool)));
        QObject::connect(customLabelBox, SIGNAL(clicked(bool)), customLabelEdit, SLOT(setEnabled(bool)));
        QObject::connect(navigationBox, SIGNAL(toggled(bool)), singleClickBox, SLOT(setEnabled(bool)));
        QObject::connect(navigationBox, SIGNAL(toggled(bool)), dolphinSortingBox, SLOT(setEnabled(bool)));

        QuickAccessConfig->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QuickAccessConfig);
    } // setupUi

    void retranslateUi(KTabWidget *QuickAccessConfig)
    {
        QuickAccessConfig->setWindowTitle(tr2i18n("Form", 0));
        selectLabel->setText(tr2i18n("Directory:", 0));
        filterLabel->setText(tr2i18n("Filters:", 0));
        hiddenBox->setText(tr2i18n("Show hidden files", 0));
        onlyDirsBox->setText(tr2i18n("Show only folders", 0));
        navigationBox->setText(tr2i18n("Allow navigation", 0));
        singleClickBox->setText(tr2i18n("Navigate with single click", 0));
        dolphinSortingBox->setText(tr2i18n("Use Dolphin's directory sorting setting", 0));
        QuickAccessConfig->setTabText(QuickAccessConfig->indexOf(general), tr2i18n("General", 0));
        label_2->setText(tr2i18n("Custom icon:", 0));
        label->setText(tr2i18n("Icon SIze:", 0));
        iconSizeCombo->clear();
        iconSizeCombo->insertItems(0, QStringList()
         << tr2i18n("16", 0)
         << tr2i18n("22", 0)
         << tr2i18n("32", 0)
         << tr2i18n("48", 0)
         << tr2i18n("64", 0)
         << tr2i18n("128", 0)
        );
        label_3->setText(tr2i18n("View mode:", 0));
        viewModeCombo->clear();
        viewModeCombo->insertItems(0, QStringList()
         << tr2i18n("List mode", 0)
         << tr2i18n("Icon mode", 0)
        );
        tooltipBox->setText(tr2i18n("Show tooltips", 0));
        customLabelBox->setText(tr2i18n("Use a custom Label", 0));
        customLabel->setText(tr2i18n("Label:", 0));
        QuickAccessConfig->setTabText(QuickAccessConfig->indexOf(appearance), tr2i18n("Appearance", 0));
        previewBox->setText(tr2i18n("Show Previews", 0));
        previewLabel1->setText(tr2i18n("Preview plugins:", 0));
        previewLabel2->setText(tr2i18n("Here you can enable/disable the plugins.", 0));
        QuickAccessConfig->setTabText(QuickAccessConfig->indexOf(preview), tr2i18n("Preview", 0));
        Q_UNUSED(QuickAccessConfig);
    } // retranslateUi

};

namespace Ui {
    class QuickAccessConfig: public Ui_QuickAccessConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QUICKACCESSCONFIG_H

