#pragma once
#include <string>
#include "order/Cart.h"

class Customer {
private:
    int id = 0;
    std::string name;
    Cart cart;

public:
    Customer(int p_id, std::string p_name);
    int getId() const noexcept;
    const std::string& getName() const noexcept;
    Cart& getCart() noexcept;
    const Cart& getCart() const noexcept;
};
