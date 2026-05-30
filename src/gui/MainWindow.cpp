#include "gui/MainWindow.h"
#include "gui/ProductPage.h"
#include "gui/CartPage.h"
#include "gui/CheckoutPage.h"
#include "gui/OrderHistoryPage.h"
#include "gui/RecommendationPage.h"
#include <QLabel>
#include <QButtonGroup>
#include <QApplication>

MainWindow::MainWindow(Store& p_store, QWidget* parent) 
    : QMainWindow(parent), store(p_store) {
    setupUI();
}

void MainWindow::setupUI() {
    setWindowTitle("Mini E-Commerce System");
    resize(800, 600);

    // Main widget and layout
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Sidebar for navigation
    QWidget* sidebar = new QWidget(this);
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(220);
    QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setAlignment(Qt::AlignTop);
    sidebarLayout->setContentsMargins(15, 20, 15, 20);
    sidebarLayout->setSpacing(10);

    QLabel* titleLabel = new QLabel("<h2>📦 Mini Amazon</h2>", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #ff6600; margin-bottom: 20px;");
    sidebarLayout->addWidget(titleLabel);

    QButtonGroup* btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true);

    btnProducts = new QPushButton("🛒 View Products", this);
    btnCart = new QPushButton("🛍️ View Cart", this);
    btnCheckout = new QPushButton("💳 Checkout", this);
    btnOrderHistory = new QPushButton("📜 Order History", this);
    btnRecommendations = new QPushButton("⭐ Recommendations", this);

    QPushButton* buttons[] = {btnProducts, btnCart, btnCheckout, btnOrderHistory, btnRecommendations};
    for (int i = 0; i < 5; ++i) {
        buttons[i]->setCheckable(true);
        buttons[i]->setCursor(Qt::PointingHandCursor);
        btnGroup->addButton(buttons[i], i);
        sidebarLayout->addWidget(buttons[i]);
    }
    btnProducts->setChecked(true);

    mainLayout->addWidget(sidebar);

    // Stacked widget for pages
    stackedWidget = new QStackedWidget(this);
    stackedWidget->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(stackedWidget, 1);

    setCentralWidget(centralWidget);

    // Apply Global Stylesheet
    QString styleSheet = R"(
        QMainWindow { background-color: #121212; color: #ffffff; }
        QWidget { background-color: #121212; color: #ffffff; font-family: 'Segoe UI', Arial, sans-serif; font-size: 14px; }
        #sidebar { background-color: #1a1a1a; border-right: 1px solid #333333; }
        QPushButton { background-color: #2a2a2a; color: #ffffff; border: 1px solid #333333; padding: 12px 15px; border-radius: 6px; text-align: left; font-weight: bold; }
        QPushButton:hover { background-color: #3d3d3d; border-color: #ff6600; }
        QPushButton:checked { background-color: #ff6600; color: white; border-color: #ff6600; }
        QTableWidget { background-color: #1e1e1e; alternate-background-color: #252525; color: #ffffff; border: 1px solid #333333; border-radius: 8px; gridline-color: #333333; outline: none; }
        QHeaderView::section { background-color: #2a2a2a; color: #ffffff; padding: 10px; border: none; border-bottom: 2px solid #ff6600; font-weight: bold; font-size: 13px; }
        QTableWidget::item { padding: 5px; }
        QTableWidget::item:selected { background-color: #ff6600; color: white; }
        QScrollBar:vertical { background: #1e1e1e; width: 12px; margin: 0px 0px 0px 0px; }
        QScrollBar::handle:vertical { background: #555555; min-height: 20px; border-radius: 6px; }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }
        QLabel { color: #ffffff; background: transparent; }
        QLineEdit, QComboBox, QSpinBox { background-color: #2a2a2a; color: #ffffff; border: 1px solid #444444; padding: 8px; border-radius: 4px; }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus { border: 1px solid #ff6600; }
        QMessageBox { background-color: #1e1e1e; color: #ffffff; }
        QMessageBox QPushButton { text-align: center; }
    )";
    qApp->setStyleSheet(styleSheet);

    // Initialize pages
    productPage = new ProductPage(store, this);
    cartPage = new CartPage(store, this);
    checkoutPage = new CheckoutPage(store, this);
    orderHistoryPage = new OrderHistoryPage(store, this);
    recommendationPage = new RecommendationPage(store, this);

    stackedWidget->addWidget(productPage);        // index 0
    stackedWidget->addWidget(cartPage);           // index 1
    stackedWidget->addWidget(checkoutPage);       // index 2
    stackedWidget->addWidget(orderHistoryPage);   // index 3
    stackedWidget->addWidget(recommendationPage); // index 4

    // Connect signals and slots
    connect(btnProducts, &QPushButton::clicked, this, [this]() { switchPage(0); });
    connect(btnCart, &QPushButton::clicked, this, [this]() { switchPage(1); });
    connect(btnCheckout, &QPushButton::clicked, this, [this]() { switchPage(2); });
    connect(btnOrderHistory, &QPushButton::clicked, this, [this]() { switchPage(3); });
    connect(btnRecommendations, &QPushButton::clicked, this, [this]() { switchPage(4); });
    
    // Connect inter-page signals
    connect(cartPage, &CartPage::checkoutRequested, this, [this]() { switchPage(2); });
    connect(checkoutPage, &CheckoutPage::orderCompleted, this, [this]() { switchPage(3); });
    connect(productPage, &ProductPage::cartUpdated, this, &MainWindow::updateSidebarCartCount);
    connect(cartPage, &CartPage::cartUpdated, this, &MainWindow::updateSidebarCartCount);
    connect(checkoutPage, &CheckoutPage::cartUpdated, this, &MainWindow::updateSidebarCartCount);
    
    updateSidebarCartCount();
}

void MainWindow::updateSidebarCartCount() {
    auto currentCustomer = store.getCurrentCustomer();
    if (currentCustomer) {
        int count = currentCustomer->getCart().getItems().size();
        if (count > 0) {
            btnCart->setText(QString("🛍️ View Cart (%1)").arg(count));
        } else {
            btnCart->setText("🛍️ View Cart");
        }
    }
}

void MainWindow::switchPage(int index) {
    stackedWidget->setCurrentIndex(index);
    if (index == 0) {
        productPage->refreshProducts();
    } else if (index == 1) {
        cartPage->refreshCart();
    } else if (index == 2) {
        checkoutPage->refreshCheckout();
    } else if (index == 3) {
        orderHistoryPage->refreshHistory();
    } else if (index == 4) {
        recommendationPage->refreshRecommendations();
    }
}
