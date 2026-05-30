#include "product/Electronics.h"
#include <iomanip>
#include <iostream>
#include <utility>

Electronics::Electronics(int p_id, std::string p_name, double p_price, int p_stock, int p_warrantyMonths)
    : Product(p_id, std::move(p_name), "Electronics", p_price, p_stock), warrantyMonths(p_warrantyMonths) {}

void Electronics::display() const {
    std::string details = "Warranty: " + std::to_string(warrantyMonths) + " mo";

    std::cout
        << "| " << std::left << std::setw(5) << getId()
        << " | " << std::setw(35) << getName()
        << " | " << std::setw(15) << getCategory()
        << " | $" << std::right << std::fixed << std::setprecision(2)
        << std::setw(8) << getPrice()
        << std::left
        << " | " << std::setw(5) << getStock()
        << " | " << std::setw(25) << details
        << " |\n";
}

std::string Electronics::getDetails() const {
    return "Warranty: " + std::to_string(warrantyMonths) + " mo";
}
