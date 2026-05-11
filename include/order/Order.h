#pragma once

#include <vector>
#include <string>

#include "CartItem.h"

class Order {

private:

    int id;
    std::string orderDate;
    std::vector<CartItem> items;
    double subtotal , tva , discount , totalAmount ;

public:

    // Constructeur
    Order( int id , const std::vector<CartItem>& items );

    // Calculs
    void calculateTotal( double tvaRate , double discountRate );

    // Affichage
    void display() const;

    // Getters
    int getId() const;

    std::string
    getOrderDate() const;

    double getSubtotal() const;

    double getTva() const;

    double getDiscount() const;

    double getTotalAmount() const;

    const std::vector<CartItem>&
    getItems() const;
};
