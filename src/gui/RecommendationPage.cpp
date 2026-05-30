#include "gui/RecommendationPage.h"
#include "product/RecommendationService.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QFrame>
#include <QPushButton>

RecommendationPage::RecommendationPage(Store& p_store, QWidget* parent)
    : QWidget(parent), store(p_store) {
    setupUI();
}

void RecommendationPage::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("<h2>⭐ Recommended Products</h2><p>Popular items based on stock levels.</p>", this);
    layout->addWidget(titleLabel);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; } QWidget#scrollWidget { background-color: transparent; }");
    
    scrollWidget = new QWidget();
    scrollWidget->setObjectName("scrollWidget");
    gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setSpacing(20);
    gridLayout->setAlignment(Qt::AlignTop);
    
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);
}

void RecommendationPage::refreshRecommendations() {
    // Clear existing layout items
    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }

    auto allProducts = store.getProductDAO().getAllProducts();
    auto recommendations = RecommendationService::recommend(allProducts);
    
    int row = 0;
    int col = 0;
    const int MAX_COLS = 3;

    for (const auto& p : recommendations) {
        if (p) {
            QFrame* card = new QFrame(this);
            card->setFixedSize(220, 150);
            card->setStyleSheet("QFrame { background-color: #2a2a2a; border-radius: 8px; border: 1px solid #444; } QFrame:hover { border: 1px solid #ff6600; }");
            
            QVBoxLayout* cardLayout = new QVBoxLayout(card);
            cardLayout->setAlignment(Qt::AlignCenter);
            
            QLabel* nameLabel = new QLabel(QString("<b>%1</b>").arg(QString::fromStdString(p->getName())), this);
            nameLabel->setStyleSheet("font-size: 14px; border: none;");
            
            QLabel* priceLabel = new QLabel(QString("$%1").arg(p->getPrice(), 0, 'f', 2), this);
            priceLabel->setStyleSheet("color: #ff6600; font-weight: bold; border: none;");
            
            QLabel* catLabel = new QLabel(QString::fromStdString(p->getCategory()), this);
            catLabel->setStyleSheet("color: #888; border: none;");

            cardLayout->addWidget(nameLabel);
            cardLayout->addWidget(catLabel);
            cardLayout->addWidget(priceLabel);
            
            gridLayout->addWidget(card, row, col);
            
            col++;
            if (col >= MAX_COLS) {
                col = 0;
                row++;
            }
        }
    }
}
