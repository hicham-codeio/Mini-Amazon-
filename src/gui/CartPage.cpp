#include "gui/CartPage.h"
#include <QHeaderView>
#include <QMessageBox>

CartPage::CartPage(Store& p_store, QWidget* parent)
    : QWidget(parent), store(p_store) {
    setupUI();
}

void CartPage::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("<h2>🛍️ Shopping Cart</h2>", this);
    layout->addWidget(titleLabel);

    cartTable = new QTableWidget(this);
    cartTable->setColumnCount(5);
    cartTable->setHorizontalHeaderLabels({"Name", "Quantity", "Unit Price", "Total Price", "Actions"});
    cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(cartTable);

    QHBoxLayout* bottomLayout = new QHBoxLayout();
    totalLabel = new QLabel("<b>Total: $0.00</b>", this);
    totalLabel->setStyleSheet("font-size: 16px; color: #ff6600;");
    
    btnEmptyCart = new QPushButton("🗑️ Empty Cart", this);
    btnEmptyCart->setStyleSheet("background-color: #aa0000;");
    
    btnCheckout = new QPushButton("💳 Proceed to Checkout", this);

    bottomLayout->addWidget(totalLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnEmptyCart);
    bottomLayout->addWidget(btnCheckout);

    layout->addLayout(bottomLayout);

    connect(btnCheckout, &QPushButton::clicked, this, &CartPage::handleCheckout);
    connect(btnEmptyCart, &QPushButton::clicked, this, &CartPage::handleEmptyCart);
}

void CartPage::refreshCart() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) return;

    const auto& items = currentCustomer->getCart().getItems();
    cartTable->setRowCount(0);
    
    int row = 0;
    for (const auto& item : items) {
        auto p = item.getProduct();
        if (p) {
            addRowToTable(row, p->getId(), QString::fromStdString(p->getName()), item.getQuantity(), p->getPrice(), item.getTotalPrice());
            row++;
        }
    }
    
    totalLabel->setText(QString("<b>Total: $%1</b>").arg(currentCustomer->getCart().getTotal(), 0, 'f', 2));
}

void CartPage::addRowToTable(int row, int productId, const QString& name, int qty, double price, double total) {
    cartTable->insertRow(row);
    cartTable->setItem(row, 0, new QTableWidgetItem(name));
    cartTable->setItem(row, 1, new QTableWidgetItem(QString::number(qty)));
    cartTable->setItem(row, 2, new QTableWidgetItem("$" + QString::number(price, 'f', 2)));
    cartTable->setItem(row, 3, new QTableWidgetItem("$" + QString::number(total, 'f', 2)));
    
    QWidget* actionWidget = new QWidget(this);
    QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
    actionLayout->setContentsMargins(0, 0, 0, 0);
    actionLayout->setSpacing(5);
    
    QPushButton* btnMinus = new QPushButton("➖", this);
    QPushButton* btnPlus = new QPushButton("➕", this);
    QPushButton* btnRemove = new QPushButton("❌", this);
    
    btnMinus->setFixedWidth(30);
    btnPlus->setFixedWidth(30);
    btnRemove->setFixedWidth(30);
    
    actionLayout->addWidget(btnMinus);
    actionLayout->addWidget(btnPlus);
    actionLayout->addWidget(btnRemove);
    actionLayout->setAlignment(Qt::AlignCenter);
    
    cartTable->setCellWidget(row, 4, actionWidget);
    
    connect(btnPlus, &QPushButton::clicked, this, [this, productId]() {
        auto p = store.getProductDAO().getProductById(productId);
        auto customer = store.getCurrentCustomer();
        if (p && customer) {
            int currentQty = 0;
            for (const auto& item : customer->getCart().getItems()) {
                if (item.getProduct()->getId() == productId) {
                    currentQty = item.getQuantity(); break;
                }
            }
            if (currentQty < p->getStock()) {
                customer->getCart().updateQuantity(productId, currentQty + 1);
                refreshCart();
                emit cartUpdated();
            } else {
                QMessageBox::warning(this, "Stock Limit", "Cannot add more. Stock limit reached.");
            }
        }
    });
    
    connect(btnMinus, &QPushButton::clicked, this, [this, productId]() {
        auto customer = store.getCurrentCustomer();
        if (customer) {
            int currentQty = 0;
            for (const auto& item : customer->getCart().getItems()) {
                if (item.getProduct()->getId() == productId) {
                    currentQty = item.getQuantity(); break;
                }
            }
            if (currentQty > 1) {
                customer->getCart().updateQuantity(productId, currentQty - 1);
                refreshCart();
                emit cartUpdated();
            } else {
                customer->getCart().removeProduct(productId);
                refreshCart();
                emit cartUpdated();
            }
        }
    });
    
    connect(btnRemove, &QPushButton::clicked, this, [this, productId]() {
        auto customer = store.getCurrentCustomer();
        if (customer) {
            customer->getCart().removeProduct(productId);
            refreshCart();
            emit cartUpdated();
        }
    });
}

void CartPage::handleEmptyCart() {
    auto currentCustomer = store.getCurrentCustomer();
    if (currentCustomer && !currentCustomer->getCart().getItems().empty()) {
        auto reply = QMessageBox::question(this, "Confirm", "Are you sure you want to empty your cart?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            currentCustomer->getCart().clear();
            refreshCart();
            emit cartUpdated();
        }
    }
}

void CartPage::handleCheckout() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer || currentCustomer->getCart().getItems().empty()) {
        QMessageBox::warning(this, "Warning", "Your cart is empty.");
        return;
    }
    emit checkoutRequested();
}
