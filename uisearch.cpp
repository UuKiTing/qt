#include "uisearch.h"
#include "ui_uisearch.h"

UISearch::UISearch(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UISearch)
{
    ui->setupUi(this);
}

UISearch::~UISearch()
{
    delete ui;
}
