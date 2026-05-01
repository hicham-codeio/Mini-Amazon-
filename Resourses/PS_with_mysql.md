# 📁 Project Structure with MySQL

## 🔹 Directory Organization

    MiniEcommerce/
    │
    ├── src/
    │   ├── main.cpp
    │   │
    │   ├── models/
    │   │   ├── Product.cpp
    │   │   ├── Electronics.cpp
    │   │   ├── Food.cpp
    │   │   ├── Clothing.cpp
    │   │   ├── Cart.cpp
    │   │   ├── CartItem.cpp
    │   │   ├── Order.cpp
    │   │   └── Customer.cpp
    │   │
    │   ├── database/
    │   │   ├── Database.cpp
    │   │   ├── ProductDAO.cpp
    │   │   ├── OrderDAO.cpp
    │   │   └── CustomerDAO.cpp
    │   │
    │   ├── services/
    │   │   ├── Store.cpp
    │   │   ├── CartService.cpp
    │   │   └── RecommendationService.cpp
    │
    ├── include/
    │   ├── models/
    │   ├── database/
    │   └── services/
    │
    ├── sql/
    │   └── schema.sql
    │
    ├── lib/
    ├── build/
    ├── README.md
    └── Makefile / CMakeLists.txt

## 🔹 Description

-   models/: Business logic classes\
-   database/: Data Access Objects (DAO) for MySQL\
-   services/: Application logic\
-   sql/: Database schema\
-   lib/: MySQL connector libraries

## 🔹 Database Schema (MySQL)

    CREATE TABLE products (
        id INT PRIMARY KEY,
        name VARCHAR(100),
        category VARCHAR(50),
        price DOUBLE,
        stock INT
    );

    CREATE TABLE customers (
        id INT PRIMARY KEY,
        name VARCHAR(100)
    );

    CREATE TABLE orders (
        id INT PRIMARY KEY,
        customer_id INT,
        total DOUBLE,
        FOREIGN KEY (customer_id) REFERENCES customers(id)
    );

    CREATE TABLE order_items (
        id INT PRIMARY KEY AUTO_INCREMENT,
        order_id INT,
        product_id INT,
        quantity INT,
        FOREIGN KEY (order_id) REFERENCES orders(id),
        FOREIGN KEY (product_id) REFERENCES products(id)
    );

## ✅ Summary

The project follows a layered architecture with separation between
models, services, and database access. MySQL is used for persistent
storage, ensuring scalability and data management.
