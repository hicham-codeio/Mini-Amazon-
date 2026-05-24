#include "order/Order.h"
#include "product/Product.h"
#include <iostream>

using namespace std;

Order::Order(
    int id,
    const vector<CartItem>& items
)
{
    this->id = id;
    this->items = items;

    subtotal = 0.0;
    tva = 0.0;
    discount = 0.0;
    totalAmount = 0.0;
}

void Order::calculateTotal(
    double tvaRate,
    double discountRate
)
{
    subtotal = 0.0;

    for (const auto& item : items)
    {
        subtotal += item.getTotal();
    }

    discount = subtotal * discountRate;

    tva = (subtotal - discount) * tvaRate;

    totalAmount =
        subtotal - discount + tva;
}

void Order::display() const
{
    cout << "\n===== ORDER =====\n";

    for (const auto& item : items)
    {
        cout
        << item.getProduct()->getName()
        << " | Qty: "
        << item.getQuantity()
        << " | Price: "
        << item.getProduct()->getPrice()
        << " | Total: "
        << item.getTotal()
        << endl;
    }

    cout << "\nSubtotal : "
         << subtotal << endl;

    cout << "Discount : "
         << discount << endl;

    cout << "TVA : "
         << tva << endl;

    cout << "Total : "
         << totalAmount << endl;
}