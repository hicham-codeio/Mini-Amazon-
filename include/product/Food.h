#pragma once
#include "product/Product.h"

class Food : public Product {
private:
    std::string expirationDate;

public:
    Food(int p_id, std::string p_name, double p_price, int p_stock, std::string p_expirationDate);
    void display() const override;
    std::string getDetails() const override;
};
