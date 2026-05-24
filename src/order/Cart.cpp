#include "order/Cart.h"
#include "order/CartItem.h"
#include "product/Product.h"

#include <iostream>

using namespace std;

void Cart::addProduct(
    shared_ptr<Product> product,
    int quantity
)
{
    if (quantity <= 0)
    {
        return;
    }
    for (auto& item : items)
    {
        if (item.getProduct()->getId() == product->getId())
        {
            int newQuantity =
                item.getQuantity() + quantity;

            item = CartItem(product, newQuantity);

            return;
        }
    }

    items.push_back(
        CartItem(product, quantity)
    );
}

void Cart::removeProduct(int productId)
{
    for (auto it = items.begin();
         it != items.end();
         it++)
    {
        if (it->getProduct()->getId() == productId)
        {
            items.erase(it);
            return;
        }
    }
}

void Cart::clear()
{
    items.clear();
}

double Cart::calculateTotal() const
{
    double total = 0.0;

    for (const auto& item : items)
    {
        total += item.getTotal();
    }

    return total;
}

void Cart::displayCart() const
{
    cout << "\n===== CART =====\n";

    for (const auto& item : items)
    {
        cout
        << item.getProduct()->getName()
        << " | Qty: "
        << item.getQuantity()
        << " | Total: "
        << item.getTotal()
        << endl;
    }

    cout << "Total Cart = "
         << calculateTotal()
         << endl;
}

const vector<CartItem>& Cart::getItems() const
{
    return items;
}