#pragma once
#include <vector>
#include "order/Order.h"

class OrderDAO {
public:
    void saveOrder(const Order& order);
    std::vector<Order> getOrdersByCustomer(int customerId) const;
};
