#pragma once

#include <memory>

class Product;

class CartItem {

private:

    std::shared_ptr<Product> product;
    int quantity;

public:

    // Constructeur
    CartItem(std::shared_ptr<Product> product , int quantity );

    // Getters
    std::shared_ptr<Product>
    getProduct() const;

    int getQuantity() const;

    // Setter
    void setQuantity(int quantity);

    // Méthodes
    double getTotal() const;
};
