#include "database/OrderDAO.h"
#include "database/Database.h"

void OrderDAO::saveOrder(const Order& order) {
    Database::ordersTable.push_back(order);
}

std::vector<Order> OrderDAO::getOrdersByCustomer(int customerId) const {
    std::vector<Order> result;
    for (const auto& o : Database::ordersTable) {
        if (o.getCustomerId() == customerId) {
            result.push_back(o);
        }
    }
    return result;
}
