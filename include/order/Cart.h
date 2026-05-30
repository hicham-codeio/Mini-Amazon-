#pragma once
#include <vector>
#include <memory>
#include "order/CartItem.h"

class Cart {
private:
    std::vector<CartItem> items;

public:
    void addProduct(std::shared_ptr<Product> product, int quantity);
    void removeProduct(int productId);
    void updateQuantity(int productId, int newQuantity);
    const std::vector<CartItem>& getItems() const noexcept;
    void clear() noexcept;
    double getTotal() const noexcept;
};
