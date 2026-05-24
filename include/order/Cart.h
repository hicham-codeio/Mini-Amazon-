#ifndef CART_H
#define CART_H

#include <vector>
#include <memory>

#include "CartItem.h"

class Product;

class Cart {
private:
    std::vector<CartItem> items;

public:
    void addProduct(
        std::shared_ptr<Product> product,
        int quantity
    );

    void removeProduct(int productId);

    void clear();

    double calculateTotal() const;

    void displayCart() const;

    const std::vector<CartItem>& getItems() const;
};

#endif