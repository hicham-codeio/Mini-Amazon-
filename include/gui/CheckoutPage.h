#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "database/Store.h"

class CheckoutPage : public QWidget {
    Q_OBJECT
public:
    explicit CheckoutPage(Store& store, QWidget* parent = nullptr);
    void refreshCheckout();

signals:
    void orderCompleted();
    void cartUpdated();

private slots:
    void handleConfirmOrder();

private:
    Store& store;
    QLabel* subtotalLabel;
    QLabel* tvaLabel;
    QLabel* discountLabel;
    QLabel* finalTotalLabel;
    QPushButton* btnConfirm;

    void setupUI();
};
