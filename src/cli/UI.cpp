#include "cli/UI.h"
#include "product/RecommendationService.h"
#include <iostream>
#include <iomanip>
#include <limits>

UI::UI() = default;

static void printProductTableLine() {
    std::cout << "+" << std::string(7, '-') << "+" << std::string(22, '-') 
              << "+" << std::string(17, '-') << "+" << std::string(11, '-') 
              << "+" << std::string(7, '-') << "+" << std::string(27, '-') << "+\n";
}

static void printProductTableHeader() {
    printProductTableLine();
    std::cout << "| " << std::left << std::setw(5) << "ID" 
              << " | " << std::setw(20) << "Name" 
              << " | " << std::setw(15) << "Category" 
              << " | " << std::setw(9) << "Price" 
              << " | " << std::setw(5) << "Stock" 
              << " | " << std::setw(25) << "Details" << " |\n";
    printProductTableLine();
}

static void printCartTableLine() {
    std::cout << "+" << std::string(22, '-') << "+" << std::string(6, '-') 
              << "+" << std::string(11, '-') << "+" << std::string(13, '-') << "+\n";
}

static void printCartTableHeader() {
    printCartTableLine();
    std::cout << "| " << std::left << std::setw(20) << "Product Name" 
              << " | " << std::setw(4) << "Qty" 
              << " | " << std::setw(9) << "Unit Prc" 
              << " | " << std::setw(11) << "Total Prc" << " |\n";
    printCartTableLine();
}

void UI::run() {
    store.start();
    
    if (!store.getCurrentCustomer()) {
        std::cerr << "[FATAL ERROR] Failed to initialize customer. Application cannot continue.\n";
        return;
    }
    
    int choice = -1;
    while (choice != 0) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: addToCart(); break;
            case 3: viewCart(); break;
            case 4: checkout(); break;
            case 5: viewOrderHistory(); break;
            case 6: viewRecommendations(); break;
            case 0: std::cout << "Exiting...\n"; break;
            default: std::cout << "[ERROR] Invalid choice. Please try again.\n";
        }
    }
}

void UI::displayMenu() {
    std::cout << "\n=================================\n";
    std::cout << "     MINI E-COMMERCE SYSTEM\n";
    std::cout << "=================================\n";
    std::cout << "1. View Products\n";
    std::cout << "2. Add Product to Cart\n";
    std::cout << "3. View Cart\n";
    std::cout << "4. Checkout\n";
    std::cout << "5. View Order History\n";
    std::cout << "6. View Recommended Products (Popular)\n";
    std::cout << "0. Exit\n";
    std::cout << "---------------------------------\n";
    std::cout << "Enter your choice: ";
}

void UI::viewProducts() {
    std::cout << "\n--- Product Catalog ---\n";
    auto products = store.getProductDAO().getAllProducts();
    if (products.empty()) {
        std::cout << "No products available.\n";
        return;
    }
    printProductTableHeader();
    for (const auto& p : products) {
        if (p) p->display();
    }
    printProductTableLine();
}

void UI::addToCart() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) {
        std::cout << "[ERROR] No customer loaded. Please restart the application.\n";
        return;
    }

    std::cout << "\nEnter Product ID to add: ";
    int productId;
    if (!(std::cin >> productId)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid Product ID.\n";
        return;
    }

    auto p = store.getProductDAO().getProductById(productId);
    if (!p) {
        std::cout << "[ERROR] Product not found.\n";
        return;
    }

    std::cout << "Enter quantity: ";
    int qty;
    if (!(std::cin >> qty)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Invalid quantity.\n";
        return;
    }

    if (qty <= 0) {
        std::cout << "[ERROR] Quantity must be greater than 0.\n";
        return;
    }

    int existingQty = 0;
    for (const auto& item : currentCustomer->getCart().getItems()) {
        if (item.getProduct()->getId() == productId) {
            existingQty = item.getQuantity();
            break;
        }
    }

    if (p->getStock() < (qty + existingQty)) {
        if (existingQty > 0) {
            std::cout << "[ERROR] Insufficient stock. You already have " << existingQty 
                      << " in your cart, and only " << p->getStock() << " are available in stock.\n";
        } else {
            std::cout << "[ERROR] Insufficient stock. Only " << p->getStock() << " available.\n";
        }
        return;
    }

    currentCustomer->getCart().addProduct(p, qty);
    std::cout << "[SUCCESS] Added " << qty << "x " << p->getName() << " to cart.\n";
}

void UI::viewCart() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) {
        std::cout << "[ERROR] No customer loaded. Please restart the application.\n";
        return;
    }

    std::cout << "\n--- Your Shopping Cart ---\n";
    const auto& items = currentCustomer->getCart().getItems();
    
    if (items.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }

    printCartTableHeader();
    for (const auto& item : items) {
        auto p = item.getProduct();
        if (p) {
            std::cout << "| " << std::left << std::setw(20) << p->getName() 
                      << " | " << std::right << std::setw(4) << item.getQuantity() 
                      << " | $" << std::fixed << std::setprecision(2) << std::setw(7) << p->getPrice()
                      << " | $" << std::setw(9) << item.getTotalPrice() << " |\n";
        }
    }
    printCartTableLine();
    std::cout << std::right << std::setw(39) << "Total Cart Value: | $" 
              << std::fixed << std::setprecision(2) << std::setw(9) << currentCustomer->getCart().getTotal() << " |\n";
    printCartTableLine();
}

void UI::checkout() {
    if (store.checkout()) {
        std::cout << "[SUCCESS] Checkout complete. Thank you for your purchase!\n";
    } else {
        std::cout << "[ERROR] Checkout failed. Cart might be empty or items out of stock.\n";
    }
}

void UI::viewOrderHistory() {
    auto currentCustomer = store.getCurrentCustomer();
    if (!currentCustomer) {
        std::cout << "[ERROR] No customer loaded. Please restart the application.\n";
        return;
    }

    std::cout << "\n--- Order History ---\n";
    auto orders = store.getOrderDAO().getOrdersByCustomer(currentCustomer->getId());
    
    if (orders.empty()) {
        std::cout << "No past orders found.\n";
        return;
    }

    for (const auto& o : orders) {
        o.display();
    }
}

void UI::viewRecommendations() {
    std::cout << "\n--- Recommended Products (Based on Stock Popularity) ---\n";
    auto allProducts = store.getProductDAO().getAllProducts();
    auto recommendations = RecommendationService::recommend(allProducts);
    
    if (recommendations.empty()) {
        std::cout << "No recommendations available.\n";
        return;
    }
    
    printProductTableHeader();
    for (const auto& p : recommendations) {
        if (p) {
            p->display();
        }
    }
    printProductTableLine();
}
