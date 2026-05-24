#ifndef CARTITEM_H
#define CARTITEM_H

#include <memory>

class Product;

class CartItem {
private:
    std::shared_ptr<Product> product;
    int quantity;

public:
    CartItem(
        std::shared_ptr<Product> product,
        int quantity
    );

    double getTotal() const;

    int getQuantity() const;

    std::shared_ptr<Product> getProduct() const;
};

#endif