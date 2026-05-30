#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "database/Store.h"

class OrderHistoryPage : public QWidget {
    Q_OBJECT
public:
    explicit OrderHistoryPage(Store& store, QWidget* parent = nullptr);
    void refreshHistory();

private:
    Store& store;
    QTableWidget* historyTable;

    void setupUI();
};
