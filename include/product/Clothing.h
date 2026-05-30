#pragma once
#include "product/Product.h"

class Clothing : public Product {
private:
    std::string size;

public:
    Clothing(int p_id, std::string p_name, double p_price, int p_stock, std::string p_size);
    void display() const override;
    std::string getDetails() const override;
};
