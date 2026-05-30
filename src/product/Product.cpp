#include "product/Product.h"
#include <utility>

Product::Product(int p_id, std::string p_name, std::string p_category, double p_price, int p_stock)
    : id(p_id), name(std::move(p_name)), category(std::move(p_category)), price(p_price), stock(p_stock) {}

int Product::getId() const noexcept { return id; }
const std::string& Product::getName() const noexcept { return name; }
const std::string& Product::getCategory() const noexcept { return category; }
double Product::getPrice() const noexcept { return price; }
int Product::getStock() const noexcept { return stock; }

void Product::setStock(int newStock) noexcept { stock = newStock; }

bool Product::reduceStock(int quantity) noexcept {
    if (stock >= quantity) {
        stock -= quantity;
        return true;
    }
    return false;
}
