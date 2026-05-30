#include "product/Food.h"
#include <iomanip>
#include <iostream>
#include <utility>

Food::Food(int p_id, std::string p_name, double p_price, int p_stock, std::string p_expirationDate)
    : Product(p_id, std::move(p_name), "Food", p_price, p_stock), expirationDate(std::move(p_expirationDate)) {}

void Food::display() const {
    std::string details = "Exp: " + expirationDate;

    std::cout
        << "| " << std::left  << std::setw(5)  << getId()
        << " | " << std::setw(35) << getName()
        << " | " << std::setw(15) << getCategory()
        << " | $" << std::right << std::fixed << std::setprecision(2)
        << std::setw(8) << getPrice()
        << std::left
        << " | " << std::setw(5) << getStock()
        << " | " << std::setw(25) << details
        << " |\n";
}

std::string Food::getDetails() const {
    return "Exp: " + expirationDate;
}
