#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "database/Store.h"

class ProductPage : public QWidget {
    Q_OBJECT
public:
    explicit ProductPage(Store& store, QWidget* parent = nullptr);
    void refreshProducts();

signals:
    void cartUpdated();

private slots:
    void handleAddToCart();
    void handleAddToCart(int productId);
    void applyFilters();

private:
    Store& store;
    class QLineEdit* searchBox;
    class QComboBox* categoryFilter;
    class QComboBox* sortFilter;
    QTableWidget* productTable;
    QPushButton* btnAddToCart;

    void setupUI();
};
