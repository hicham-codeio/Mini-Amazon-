#pragma once
#include <memory>
#include "user/Customer.h"

class CustomerDAO {
public:
    std::shared_ptr<Customer> getCustomerById(int id) const;
};
