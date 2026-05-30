#include "order/CartItem.h"
#include <utility>

CartItem::CartItem(std::shared_ptr<Product> p_product, int p_quantity) 
    : product(std::move(p_product)), quantity(p_quantity) {}

std::shared_ptr<Product> CartItem::getProduct() const noexcept { return product; }
int CartItem::getQuantity() const noexcept { return quantity; }
void CartItem::setQuantity(int qty) noexcept { quantity = qty; }

double CartItem::getTotalPrice() const noexcept {
    if (product) {
        return product->getPrice() * quantity;
    }
    return 0.0;
}
