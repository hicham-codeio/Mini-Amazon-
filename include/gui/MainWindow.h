#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "database/Store.h"

class ProductPage;
class CartPage;
class CheckoutPage;
class OrderHistoryPage;
class RecommendationPage;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Store& store, QWidget* parent = nullptr);

private slots:
    void switchPage(int index);
    void updateSidebarCartCount();

private:
    Store& store;
    QStackedWidget* stackedWidget;
    
    // Navigation Buttons
    QPushButton* btnProducts;
    QPushButton* btnCart;
    QPushButton* btnCheckout;
    QPushButton* btnOrderHistory;
    QPushButton* btnRecommendations;

    // Pages
    ProductPage* productPage;
    CartPage* cartPage;
    CheckoutPage* checkoutPage;
    OrderHistoryPage* orderHistoryPage;
    RecommendationPage* recommendationPage;

    void setupUI();
};
