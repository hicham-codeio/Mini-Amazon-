#include <vector>
#include <memory>
class Product ; 
class CartItem ;
class Cart {
    private:
    std::vector<CartItem> items;
    public:
    void addProduct(
    std::shared_ptr<Product> product,
    int quantity
    );
    void removeProduct(int productId);
    void clear();
    double calculateTotal() const;
    void displayCart() const;
    const std::vector<CartItem>&
    getItems() const;
};