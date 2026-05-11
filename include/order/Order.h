#include <vector>
#include <string>
class CartItem ;
class Order {
private:
int id;
std::string orderDate;
std::vector<CartItem> items;
double subtotal;
double tva;
double discount;
double totalAmount;
public:
Order(
int id,
const std::vector<CartItem>& items
);
void calculateTotal(
double tvaRate,
double discountRate
);
void display() const;
};