#include "CartItem.h"
#include "../../include/product/Product.h"

CartItem::CartItem(std::shared_ptr<Product> product, int quantity)
    : product(product), quantity(quantity) {}

std::shared_ptr<Product> CartItem::getProduct() const {
    return product;
}

int CartItem::getQuantity() const {
    return quantity;
}

void CartItem::setQuantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
    }
}

double CartItem::getTotal() const {
    if (!product) return 0.0;
    return product->getPrice() * quantity;
}
