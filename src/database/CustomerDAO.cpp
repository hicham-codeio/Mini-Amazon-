#include "database/CustomerDAO.h"
#include "database/Database.h"

std::shared_ptr<Customer> CustomerDAO::getCustomerById(int id) const {
    for (const auto& c : Database::customersTable) {
        if (c->getId() == id) {
            return c;
        }
    }
    return nullptr;
}
