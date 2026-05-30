#include "gui/CheckoutPage.h"
#include <QMessageBox>
#include <QFrame>

CheckoutPage::CheckoutPage(Store& p_store, QWidget* parent)
    : QWidget(parent), store(p_store) {
    setupUI();
}

void CheckoutPage::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QFrame* receiptFrame = new QFrame(this);
    receiptFrame->setFixedWidth(400);
    receiptFrame->setStyleSheet("QFrame { background-color: #1e1e1e; border: 1px solid #333333; border-radius: 10px; padding: 20px; }");
    QVBoxLayout* receiptLayout = new QVBoxLayout(receiptFrame);

    QLabel* titleLabel = new QLabel("<h2>🧾 Checkout Summary</h2>", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    receiptLayout->addWidget(titleLabel);

    subtotalLabel = new QLabel("Subtotal: $0.00", this);
    tvaLabel = new QLabel("TVA (20%): $0.00", this);
    discountLabel = new QLabel("Discount: $0.00", this);
    discountLabel->setStyleSheet("color: #4CAF50;");
    finalTotalLabel = new QLabel("<b>Final Total: $0.00</b>", this);
    finalTotalLabel->setStyleSheet("font-size: 18px; color: #ff6600; margin-top: 15px;");

    QFont font = subtotalLabel->font();
    font.setPointSize(12);
    subtotalLabel->setFont(font);
    tvaLabel->setFont(font);
    discountLabel->setFont(font);

    receiptLayout->addWidget(subtotalLabel);
    receiptLayout->addWidget(tvaLabel);
    receiptLayout->addWidget(discountLabel);
    
    QFrame* hLine = new QFrame(this);
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    hLine->setStyleSheet("background-color: #333333;");
    receiptLayout->addWidget(hLine);
    
    receiptLayout->addWidget(finalTotalLabel);

    btnConfirm = new QPushButton("✅ Confirm Order", this);
    btnConfirm->setStyleSheet("background-color: #ff6600; font-size: 16px; padding: 15px; margin-top: 20px;");
    receiptLayout->addWidget(btnConfirm);

    layout->addWidget(receiptFrame);

    connect(btnConfirm, &QPushButton::clicked, this, &CheckoutPage::handleConfirmOrder);
}

void CheckoutPage::refreshCheckout() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) return;

    double subtotal = currentCustomer->getCart().getTotal();
    double tvaAmount = subtotal * 0.20;
    
    // Simulate a simple discount logic (e.g. 5% off if subtotal > $100)
    double discountAmount = (subtotal > 100.0) ? (subtotal * 0.05) : 0.0;
    
    double finalTotal = subtotal + tvaAmount - discountAmount;

    subtotalLabel->setText(QString("Subtotal: $%1").arg(subtotal, 0, 'f', 2));
    tvaLabel->setText(QString("TVA (20%): $%1").arg(tvaAmount, 0, 'f', 2));
    discountLabel->setText(QString("Discount: -$%1").arg(discountAmount, 0, 'f', 2));
    finalTotalLabel->setText(QString("<b>Final Total: $%1</b>").arg(finalTotal, 0, 'f', 2));

    btnConfirm->setEnabled(subtotal > 0);
}

void CheckoutPage::handleConfirmOrder() {
    auto reply = QMessageBox::question(this, "Confirm Order", "Are you sure you want to proceed with the payment?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (store.checkout()) {
            QMessageBox::information(this, "Order Successful", "🎉 Order placed successfully!\nThank you for your purchase.");
            emit orderCompleted();
            emit cartUpdated();
        } else {
            QMessageBox::critical(this, "Error", "Checkout failed. Items might be out of stock.");
        }
    }
}
