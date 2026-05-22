#include "database/Database.h"
#include "product/Electronics.h"
#include "product/Food.h"
#include "product/Clothing.h"

std::vector<std::shared_ptr<Product>> Database::productsTable;
std::vector<std::shared_ptr<Customer>> Database::customersTable;
std::vector<Order> Database::ordersTable;

void Database::initializeData() {
    if (!productsTable.empty() || !customersTable.empty()) {
        return;
    }
    productsTable.push_back(std::make_shared<Electronics>(101, "Laptop XYZ", 1200.0, 10, 24));
    productsTable.push_back(std::make_shared<Electronics>(102, "Smartphone ABC", 800.0, 15, 12));
    productsTable.push_back(std::make_shared<Food>(201, "Organic Apple", 2.5, 100, "2026-06-01"));
    productsTable.push_back(std::make_shared<Food>(202, "Whole Wheat Bread", 3.0, 50, "2026-05-15"));
    productsTable.push_back(std::make_shared<Clothing>(301, "Cotton T-Shirt", 15.0, 200, "M"));
    productsTable.push_back(std::make_shared<Clothing>(302, "Denim Jeans", 45.0, 50, "32"));

    customersTable.push_back(std::make_shared<Customer>(1, "Alice Smith"));
    customersTable.push_back(std::make_shared<Customer>(2, "Bob Jones"));
}

void Database::cleanupData() {
    productsTable.clear();
    customersTable.clear();
    ordersTable.clear();
}
