#include "user/Customer.h"
#include <utility>

Customer::Customer(int p_id, std::string p_name) : id(p_id), name(std::move(p_name)) {}

int Customer::getId() const noexcept { return id; }
const std::string& Customer::getName() const noexcept { return name; }
Cart& Customer::getCart() noexcept { return cart; }
const Cart& Customer::getCart() const noexcept { return cart; }
