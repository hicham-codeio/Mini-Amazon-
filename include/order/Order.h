#pragma once
#include <vector>
#include "order/CartItem.h"

class Order {
private:
    int id = 0;
    int customerId = 0;
    std::vector<CartItem> items;
    double subtotal = 0.0;
    double tvaAmount = 0.0;
    double finalTotal = 0.0;

public:
    Order(int p_id, int p_customerId, std::vector<CartItem> p_items, double p_subtotal);
    int getId() const noexcept;
    int getCustomerId() const noexcept;
    double getFinalTotal() const noexcept;
    const std::vector<CartItem>& getItems() const noexcept;
    void display() const;
};
