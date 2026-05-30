#pragma once
#include "product/Product.h"

class Electronics : public Product {
private:
    int warrantyMonths = 0;

public:
    Electronics(int p_id, std::string p_name, double p_price, int p_stock, int p_warrantyMonths);
    void display() const override;
    std::string getDetails() const override;
};
