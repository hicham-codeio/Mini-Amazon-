#pragma once
#include <memory>
#include "product/Product.h"

class CartItem {
private:
    std::shared_ptr<Product> product = nullptr;
    int quantity = 0;

public:
    CartItem(std::shared_ptr<Product> p_product, int p_quantity);
    std::shared_ptr<Product> getProduct() const noexcept;
    int getQuantity() const noexcept;
    void setQuantity(int qty) noexcept;
    double getTotalPrice() const noexcept;
};
