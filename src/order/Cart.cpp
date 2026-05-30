#include "order/Cart.h"
#include <iostream>
#include <algorithm>
#include <numeric>

void Cart::addProduct(std::shared_ptr<Product> product, int quantity) {
    if (!product) return;
    
    auto it = std::find_if(items.begin(), items.end(), [&](const CartItem& item) {
        return item.getProduct()->getId() == product->getId();
    });

    if (it != items.end()) {
        it->setQuantity(it->getQuantity() + quantity);
    } else {
        items.emplace_back(std::move(product), quantity);
    }
}

void Cart::removeProduct(int productId) {
    items.erase(std::remove_if(items.begin(), items.end(), [&](const CartItem& item) {
        return item.getProduct()->getId() == productId;
    }), items.end());
}

void Cart::updateQuantity(int productId, int newQuantity) {
    if (newQuantity <= 0) {
        removeProduct(productId);
        return;
    }

    auto it = std::find_if(items.begin(), items.end(), [&](const CartItem& item) {
        return item.getProduct()->getId() == productId;
    });

    if (it != items.end()) {
        it->setQuantity(newQuantity);
    }
}

const std::vector<CartItem>& Cart::getItems() const noexcept { return items; }

void Cart::clear() noexcept { items.clear(); }

double Cart::getTotal() const noexcept {
    return std::accumulate(items.begin(), items.end(), 0.0, [](double sum, const CartItem& item) {
        return sum + item.getTotalPrice();
    });
}
