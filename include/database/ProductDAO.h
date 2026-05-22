#pragma once
#include <vector>
#include <memory>
#include "product/Product.h"

class ProductDAO {
public:
    std::vector<std::shared_ptr<Product>> getAllProducts() const;
    std::shared_ptr<Product> getProductById(int id) const;
    void updateStock(int productId, int newStock);
};
