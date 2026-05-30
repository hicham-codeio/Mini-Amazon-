#pragma once
#include "database/Store.h"

class UI {
private:
    Store store;

    void displayMenu();
    void viewProducts();
    void addToCart();
    void viewCart();
    void checkout();
    void viewOrderHistory();
    void viewRecommendations();

public:
    UI();
    void run();
};
