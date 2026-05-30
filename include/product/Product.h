#pragma once
#include <string>
#include <iostream>

class Product {
private:
    int id = 0;
    std::string name;
    std::string category;
    double price = 0.0;
    int stock = 0;

public:
    Product(int p_id, std::string p_name, std::string p_category, double p_price, int p_stock);
    virtual ~Product() = default;

    int getId() const noexcept;
    const std::string& getName() const noexcept;
    const std::string& getCategory() const noexcept;
    double getPrice() const noexcept;
    int getStock() const noexcept;
    
    void setStock(int newStock) noexcept;
    bool reduceStock(int quantity) noexcept;

    virtual void display() const = 0; 
    virtual std::string getDetails() const = 0;
};
