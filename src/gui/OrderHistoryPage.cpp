#include "gui/OrderHistoryPage.h"
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

OrderHistoryPage::OrderHistoryPage(Store& p_store, QWidget* parent)
    : QWidget(parent), store(p_store) {
    setupUI();
}

void OrderHistoryPage::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("<h2>📜 Order History</h2>", this);
    layout->addWidget(titleLabel);

    historyTable = new QTableWidget(this);
    historyTable->setColumnCount(4);
    historyTable->setHorizontalHeaderLabels({"Order ID", "Date", "Total Paid", "Actions"});
    historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(historyTable);
}

void OrderHistoryPage::refreshHistory() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) return;

    auto orders = store.getOrderDAO().getOrdersByCustomer(currentCustomer->getId());
    historyTable->setRowCount(0);
    
    int row = 0;
    for (const auto& o : orders) {
        historyTable->insertRow(row);
        
        historyTable->setItem(row, 0, new QTableWidgetItem(QString("Order #%1").arg(o.getId())));
        historyTable->setItem(row, 1, new QTableWidgetItem("2026-05-22")); // Placeholder since Date is not in Order model
        
        QString totalPaid = "$" + QString::number(o.getFinalTotal(), 'f', 2);
        historyTable->setItem(row, 2, new QTableWidgetItem(totalPaid));
        
        QPushButton* btnDetails = new QPushButton("👁️ View Details", this);
        historyTable->setCellWidget(row, 3, btnDetails);
        
        QString itemsStr;
        for (const auto& item : o.getItems()) {
            if (item.getProduct()) {
                itemsStr += QString::fromStdString(item.getProduct()->getName()) + 
                            " (x" + QString::number(item.getQuantity()) + ")\n";
            }
        }
        
        connect(btnDetails, &QPushButton::clicked, this, [this, o, itemsStr, totalPaid]() {
            QString details = QString("Order #%1 Details:\n\nItems:\n%2\nTotal Paid: %3")
                                .arg(o.getId())
                                .arg(itemsStr)
                                .arg(totalPaid);
            QMessageBox::information(this, "Order Details", details);
        });
        
        row++;
    }
}
