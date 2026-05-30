#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "database/Store.h"

class CartPage : public QWidget {
    Q_OBJECT
public:
    explicit CartPage(Store& store, QWidget* parent = nullptr);
    void refreshCart();

signals:
    void checkoutRequested();
    void cartUpdated();

private slots:
    void handleCheckout();
    void handleEmptyCart();

private:
    Store& store;
    QTableWidget* cartTable;
    QLabel* totalLabel;
    QPushButton* btnCheckout;
    QPushButton* btnEmptyCart;

    void setupUI();
    void addRowToTable(int row, int productId, const QString& name, int qty, double price, double total);
};
