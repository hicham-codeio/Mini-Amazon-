#include "order/Order.h"
#include <iostream>
#include <iomanip>
#include <utility>

Order::Order(int p_id, int p_customerId, std::vector<CartItem> p_items, double p_subtotal)
    : id(p_id), customerId(p_customerId), items(std::move(p_items)), subtotal(p_subtotal) {
    tvaAmount = subtotal * 0.20; // 20% TVA
    finalTotal = subtotal + tvaAmount;
}

int Order::getId() const noexcept { return id; }
int Order::getCustomerId() const noexcept { return customerId; }
double Order::getFinalTotal() const noexcept { return finalTotal; }
const std::vector<CartItem>& Order::getItems() const noexcept { return items; }

void Order::display() const {
    std::cout << "\n";
    std::cout << "+" << std::string(36, '=') << "+\n";
    std::cout << "| " << std::left << std::setw(34) << ("Order #" + std::to_string(id)) << " |\n";
    std::cout << "+" << std::string(22, '-') << "+" << std::string(13, '-') << "+\n";
    for (const auto& item : items) {
        std::string name_qty = item.getProduct()->getName() + " (x" + std::to_string(item.getQuantity()) + ")";
        std::cout << "| " << std::left << std::setw(20) << name_qty.substr(0, 20)
                  << " | $" << std::right << std::fixed << std::setprecision(2) << std::setw(9) << item.getTotalPrice() << " |\n";
    }
    std::cout << "+" << std::string(22, '-') << "+" << std::string(13, '-') << "+\n";
    std::cout << "| " << std::left << std::setw(20) << "Subtotal:" << " | $" << std::right << std::setw(9) << subtotal << " |\n";
    std::cout << "| " << std::left << std::setw(20) << "TVA (20%):" << " | $" << std::right << std::setw(9) << tvaAmount << " |\n";
    std::cout << "| " << std::left << std::setw(20) << "Total:" << " | $" << std::right << std::setw(9) << finalTotal << " |\n";
    std::cout << "+" << std::string(36, '=') << "+\n";
}
