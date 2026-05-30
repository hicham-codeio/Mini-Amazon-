#include "gui/ProductPage.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <algorithm>

ProductPage::ProductPage(Store& p_store, QWidget* parent)
    : QWidget(parent), store(p_store) {
    setupUI();
}

void ProductPage::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Top Controls Layout
    QHBoxLayout* controlsLayout = new QHBoxLayout();
    
    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("🔍 Search products...");
    
    categoryFilter = new QComboBox(this);
    categoryFilter->addItems({"All Categories", "Electronics", "Food", "Clothing"});
    
    sortFilter = new QComboBox(this);
    sortFilter->addItems({"Sort by ID", "Price: Low to High", "Price: High to Low"});

    controlsLayout->addWidget(searchBox, 2);
    controlsLayout->addWidget(categoryFilter, 1);
    controlsLayout->addWidget(sortFilter, 1);

    layout->addLayout(controlsLayout);

    productTable = new QTableWidget(this);
    productTable->setColumnCount(6);
    productTable->setHorizontalHeaderLabels({"ID", "Name", "Category", "Price", "Stock", "Add to Cart"});
    productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    productTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productTable->setSelectionMode(QAbstractItemView::SingleSelection);
    productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    btnAddToCart = new QPushButton("➕ Add Selected to Cart", this);

    layout->addWidget(productTable);
    layout->addWidget(btnAddToCart);

    connect(btnAddToCart, &QPushButton::clicked, this, [this]() {
        int currentRow = productTable->currentRow();
        if (currentRow >= 0) {
            int productId = productTable->item(currentRow, 0)->text().toInt();
            handleAddToCart(productId);
        } else {
            QMessageBox::warning(this, "Warning", "Please select a product first.");
        }
    });
    
    connect(productTable, &QTableWidget::itemDoubleClicked, this, [this](QTableWidgetItem* item) {
        if (item) {
            int productId = productTable->item(item->row(), 0)->text().toInt();
            handleAddToCart(productId);
        }
    });

    connect(searchBox, &QLineEdit::textChanged, this, &ProductPage::applyFilters);
    connect(categoryFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ProductPage::applyFilters);
    connect(sortFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ProductPage::applyFilters);
}

void ProductPage::refreshProducts() {
    applyFilters();
}

void ProductPage::applyFilters() {
    auto products = store.getProductDAO().getAllProducts();
    
    // Search filter
    QString searchText = searchBox->text().toLower();
    if (!searchText.isEmpty()) {
        products.erase(std::remove_if(products.begin(), products.end(), [&](const std::shared_ptr<Product>& p) {
            return p && QString::fromStdString(p->getName()).toLower().indexOf(searchText) == -1;
        }), products.end());
    }

    // Category filter
    QString cat = categoryFilter->currentText();
    if (cat != "All Categories") {
        products.erase(std::remove_if(products.begin(), products.end(), [&](const std::shared_ptr<Product>& p) {
            return p && QString::fromStdString(p->getCategory()) != cat;
        }), products.end());
    }

    // Sorting
    int sortIdx = sortFilter->currentIndex();
    if (sortIdx == 1) { // Price: Low to High
        std::sort(products.begin(), products.end(), [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
            return a->getPrice() < b->getPrice();
        });
    } else if (sortIdx == 2) { // Price: High to Low
        std::sort(products.begin(), products.end(), [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
            return a->getPrice() > b->getPrice();
        });
    }

    productTable->setRowCount(0);
    int row = 0;
    for (const auto& p : products) {
        if (p) {
            productTable->insertRow(row);
            
            auto* idItem = new QTableWidgetItem(QString::number(p->getId()));
            auto* nameItem = new QTableWidgetItem(QString::fromStdString(p->getName()));
            auto* catItem = new QTableWidgetItem(QString::fromStdString(p->getCategory()));
            
            QString priceStr = "$" + QString::number(p->getPrice(), 'f', 2);
            auto* priceItem = new QTableWidgetItem(priceStr);
            
            auto* stockItem = new QTableWidgetItem(QString::number(p->getStock()));

            if (p->getStock() < 15) {
                stockItem->setForeground(QBrush(QColor("#ff4444")));
                stockItem->setFont(QFont("", -1, QFont::Bold));
            }

            productTable->setItem(row, 0, idItem);
            productTable->setItem(row, 1, nameItem);
            productTable->setItem(row, 2, catItem);
            productTable->setItem(row, 3, priceItem);
            productTable->setItem(row, 4, stockItem);
            
            QPushButton* btnRowAdd = new QPushButton("🛒 Add to Cart", this);
            btnRowAdd->setStyleSheet("background-color: #ff6600; padding: 5px; margin: 2px; border-radius: 4px; font-weight: bold;");
            int pId = p->getId();
            connect(btnRowAdd, &QPushButton::clicked, this, [this, pId]() {
                handleAddToCart(pId);
            });
            productTable->setCellWidget(row, 5, btnRowAdd);
            
            row++;
        }
    }
}

void ProductPage::handleAddToCart(int productId) {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) {
        QMessageBox::critical(this, "Error", "No customer loaded.");
        return;
    }

    auto p = store.getProductDAO().getProductById(productId);
    
    if (!p) {
        QMessageBox::critical(this, "Error", "Product not found.");
        return;
    }

    bool ok;
    int qty = QInputDialog::getInt(this, "Add to Cart", 
                                   QString("Enter quantity for %1:").arg(QString::fromStdString(p->getName())), 
                                   1, 1, p->getStock(), 1, &ok);
    
    if (ok) {
        int existingQty = 0;
        for (const auto& item : currentCustomer->getCart().getItems()) {
            if (item.getProduct()->getId() == productId) {
                existingQty = item.getQuantity();
                break;
            }
        }

        if (p->getStock() < (qty + existingQty)) {
            QMessageBox::warning(this, "Error", 
                QString("Insufficient stock. You already have %1 in your cart, and only %2 are available.")
                .arg(existingQty).arg(p->getStock()));
            return;
        }

        currentCustomer->getCart().addProduct(p, qty);
        QMessageBox::information(this, "Success", 
            QString("✅ Added %1x %2 to cart.").arg(qty).arg(QString::fromStdString(p->getName())));
        emit cartUpdated();
    }
}

// Old slot to keep header compatibility
void ProductPage::handleAddToCart() {
    int currentRow = productTable->currentRow();
    if (currentRow >= 0) {
        int productId = productTable->item(currentRow, 0)->text().toInt();
        handleAddToCart(productId);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a product first.");
    }
}
