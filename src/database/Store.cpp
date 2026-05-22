#include "database/Store.h"
#include "database/Database.h"
#include <iostream>
#include <cstdlib>

Store::Store() : currentCustomer(nullptr), nextOrderId(1) {}

void Store::start() {
    Database::initializeData();
    currentCustomer = customerDAO.getCustomerById(1); // Default login
    if (!currentCustomer) {
        std::cerr << "[FATAL ERROR] Failed to load default customer. Database initialization may have failed.\n";
    }
}

bool Store::checkout() {
    if (!currentCustomer) return false;
    
    Cart& cart = currentCustomer->getCart();
    const auto& items = cart.getItems();
    
    if (items.empty()) return false;

    // Validate stock
    for (const auto& item : items) {
        if (item.getProduct()->getStock() < item.getQuantity()) {
            return false;
        }
    }

    // Deduct stock
    for (const auto& item : items) {
        item.getProduct()->reduceStock(item.getQuantity());
    }

    // Create order
    Order order(nextOrderId++, currentCustomer->getId(), items, cart.getTotal());
    orderDAO.saveOrder(order);
    
    std::cout << "\n[SUCCESS] Order Placed Successfully!";
    order.display();

    // Clear cart
    cart.clear();
    return true;
}

ProductDAO& Store::getProductDAO() noexcept { return productDAO; }
OrderDAO& Store::getOrderDAO() noexcept { return orderDAO; }
std::shared_ptr<Customer> Store::getCurrentCustomer() const noexcept { return currentCustomer; }
