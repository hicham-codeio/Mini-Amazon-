#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>

#include "CartItem.h"

class Order {
private:
    int id;
    std::string orderDate;
    std::vector<CartItem> items;

    double subtotal;
    double tva;
    double discount;
    double totalAmount;

public:
    Order(
        int id,
        const std::vector<CartItem>& items
    );

    void calculateTotal(
        double tvaRate,
        double discountRate
    );

    void display() const;
};

#endif