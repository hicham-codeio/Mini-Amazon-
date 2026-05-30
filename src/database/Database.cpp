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
    // Original Products
    productsTable.push_back(std::make_shared<Electronics>(101, "Laptop XYZ", 1200.0, 10, 24));
    productsTable.push_back(std::make_shared<Electronics>(102, "Smartphone ABC", 800.0, 15, 12));
    productsTable.push_back(std::make_shared<Food>(201, "Organic Apple", 2.5, 100, "2026-06-01"));
    productsTable.push_back(std::make_shared<Food>(202, "Whole Wheat Bread", 3.0, 50, "2026-05-15"));
    productsTable.push_back(std::make_shared<Clothing>(301, "Cotton T-Shirt", 15.0, 200, "M"));
    productsTable.push_back(std::make_shared<Clothing>(302, "Denim Jeans", 45.0, 50, "32"));

    // New Electronics
    productsTable.push_back(std::make_shared<Electronics>(103, "Sony WH-1000XM5 Headphones", 348.0, 45, 12));
    productsTable.push_back(std::make_shared<Electronics>(104, "MacBook Pro 16-inch M3 Max", 3499.0, 15, 36));
    productsTable.push_back(std::make_shared<Electronics>(105, "Samsung 65-inch OLED TV", 1799.99, 8, 24));
    productsTable.push_back(std::make_shared<Electronics>(106, "Nintendo Switch OLED", 349.99, 120, 12));
    productsTable.push_back(std::make_shared<Electronics>(107, "Logitech MX Master 3S Mouse", 99.99, 85, 12));
    productsTable.push_back(std::make_shared<Electronics>(108, "Dell UltraSharp 27 Monitor", 450.0, 30, 36));
    productsTable.push_back(std::make_shared<Electronics>(109, "Anker 10000mAh Power Bank", 25.99, 210, 18));
    productsTable.push_back(std::make_shared<Electronics>(110, "GoPro HERO12 Black", 399.0, 5, 12));

    // New Food
    productsTable.push_back(std::make_shared<Food>(203, "Lindt Dark Chocolate 85%", 4.5, 300, "2027-01-15"));
    productsTable.push_back(std::make_shared<Food>(204, "Lavazza Espresso Coffee Beans 1kg", 18.99, 60, "2026-10-20"));
    productsTable.push_back(std::make_shared<Food>(205, "Avocado (Pack of 4)", 5.99, 25, "2026-05-30"));
    productsTable.push_back(std::make_shared<Food>(206, "Blue Diamond Almonds 16oz", 9.49, 140, "2027-03-01"));
    productsTable.push_back(std::make_shared<Food>(207, "Kerrygold Pure Irish Butter", 4.99, 80, "2026-08-10"));
    productsTable.push_back(std::make_shared<Food>(208, "Wagyu Ribeye Steak 16oz", 89.99, 4, "2026-06-05"));
    productsTable.push_back(std::make_shared<Food>(209, "San Pellegrino Sparkling Water", 1.99, 500, "2027-11-01"));
    productsTable.push_back(std::make_shared<Food>(210, "Fresh Atlantic Salmon Fillet", 12.50, 9, "2026-05-25"));

    // New Clothing
    productsTable.push_back(std::make_shared<Clothing>(303, "Nike Air Force 1 Sneakers", 110.0, 40, "10"));
    productsTable.push_back(std::make_shared<Clothing>(304, "Levi's 501 Original Fit Jeans", 69.50, 75, "34x32"));
    productsTable.push_back(std::make_shared<Clothing>(305, "The North Face Nuptse Jacket", 280.0, 12, "L"));
    productsTable.push_back(std::make_shared<Clothing>(306, "Adidas Ultraboost Running Shoes", 180.0, 20, "9.5"));
    productsTable.push_back(std::make_shared<Clothing>(307, "Ralph Lauren Polo Shirt", 95.0, 65, "M"));
    productsTable.push_back(std::make_shared<Clothing>(308, "Under Armour Athletic Shorts", 35.0, 150, "XL"));
    productsTable.push_back(std::make_shared<Clothing>(309, "Cashmere Winter Scarf", 120.0, 6, "One Size"));
    productsTable.push_back(std::make_shared<Clothing>(310, "Hanes Men's Crew Socks 6-Pack", 14.99, 300, "10-13"));

    customersTable.push_back(std::make_shared<Customer>(1, "Alice Smith"));
    customersTable.push_back(std::make_shared<Customer>(2, "Bob Jones"));
}

void Database::cleanupData() {
    productsTable.clear();
    customersTable.clear();
    ordersTable.clear();
}
