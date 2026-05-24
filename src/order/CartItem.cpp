#include "order/CartItem.h"
#include "product/Product.h"

CartItem::CartItem(
    std::shared_ptr<Product> product,
    int quantity
)
{
    this->product = product;
    this->quantity = quantity;
}

double CartItem::getTotal() const
{
    return product->getPrice() * quantity;
}

int CartItem::getQuantity() const
{
    return quantity;
}

std::shared_ptr<Product> CartItem::getProduct() const
{
    return product;
}