#include "database/ProductDAO.h"
#include "database/Database.h"

std::vector<std::shared_ptr<Product>> ProductDAO::getAllProducts() const {
    return Database::productsTable;
}

std::shared_ptr<Product> ProductDAO::getProductById(int id) const {
    for (const auto& p : Database::productsTable) {
        if (p->getId() == id) {
            return p;
        }
    }
    return nullptr;
}

void ProductDAO::updateStock(int productId, int newStock) {
    auto p = getProductById(productId);
    if (p) {
        p->setStock(newStock);
    }
}
