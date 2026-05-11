#pragma once

#include <vector>
#include <memory>

#include "CartItem.h"

class Product;

class Cart {

private:

    std::vector<CartItem> items;

public:

    // Ajouter un produit
    void addProduct(
        std::shared_ptr<Product> product,
        int quantity
    );

    // Supprimer un produit
    void removeProduct(int productId);

    // Vider le panier
    void clear();

    // Calculer le total
    double calculateTotal() const;

    // Afficher le panier
    void displayCart() const;

    // Getter
    const std::vector<CartItem>&
    getItems() const;
};
