#pragma once
#include "database/ProductDAO.h"
#include "database/OrderDAO.h"
#include "database/CustomerDAO.h"
#include "user/Customer.h"
#include <memory>

class Store {
private:
    ProductDAO productDAO;
    OrderDAO orderDAO;
    CustomerDAO customerDAO;
    std::shared_ptr<Customer> currentCustomer = nullptr;
    int nextOrderId = 1;

public:
    Store();
    void start();
    bool checkout();
    
    ProductDAO& getProductDAO() noexcept;
    OrderDAO& getOrderDAO() noexcept;
    std::shared_ptr<Customer> getCurrentCustomer() const noexcept;
};
