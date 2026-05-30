#include "product/Clothing.h"
#include <iomanip>
#include <iostream>
#include <utility>

Clothing::Clothing(int p_id, std::string p_name, double p_price, int p_stock, std::string p_size)
    : Product(p_id, std::move(p_name), "Clothing", p_price, p_stock), size(std::move(p_size)) {}

void Clothing::display() const {
    std::string details = "Size: " + size;

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

std::string Clothing::getDetails() const {
    return "Size: " + size;
}
