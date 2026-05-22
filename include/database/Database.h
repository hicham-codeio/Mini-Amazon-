#pragma once
#include <vector>
#include <memory>
#include "product/Product.h"
#include "user/Customer.h"
#include "order/Order.h"

class ProductDAO;
class CustomerDAO;
class OrderDAO;

class Database {
private:
    static std::vector<std::shared_ptr<Product>> productsTable;
    static std::vector<std::shared_ptr<Customer>> customersTable;
    static std::vector<Order> ordersTable;
    
    friend class ProductDAO;
    friend class CustomerDAO;
    friend class OrderDAO;

public:
    static void initializeData();
    static void cleanupData();
};
