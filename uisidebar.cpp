#include "uisidebar.h"
#include "ui_uisidebar.h"
#include "global.h"

UISideBar::UISideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISideBar)
{
    ui->setupUi(this);

    init();

    connectSignals();


}

UISideBar::~UISideBar()
{
    delete ui;
}

void UISideBar::init()
{
    group = new QButtonGroup(this);
    group->addButton(ui->homeBtn);
    group->addButton(ui->collectBtn);

    QIcon icon = roundPixmap(QPixmap(":/images/avatar.png"), QSize(50, 50), 25);
    ui->avatarBtn->setIcon(icon);
}

void UISideBar::connectSignals() // 优化点
{
    connect(ui->homeBtn, &QToolButton::toggled, [this](bool checked){
        if(checked) {
            emit pageChanged(MainPage::Main);
            ui->homeBtn->setIcon(QIcon(":/icon/homeSelect.png"));
        }
        else{
            ui->homeBtn->setIcon(QIcon(":/icon/homeNormal.png"));
        }
    });

    connect(ui->collectBtn, &QToolButton::toggled, [this](bool checked){
        if(checked) {
            emit pageChanged(MainPage::Collect);
            ui->collectBtn->setIcon(QIcon(":/icon/collect.png"));
        }
        else{
            ui->collectBtn->setIcon(QIcon(":/icon/dislove.png"));
        }
    });
}

