#!/bin/bash

set -e

echo "Creating team-based project structure..."

# Root directories
mkdir -p src/product
mkdir -p src/order
mkdir -p src/user
mkdir -p src/database

mkdir -p include/product
mkdir -p include/order
mkdir -p include/user
mkdir -p include/database

mkdir -p sql
mkdir -p lib
mkdir -p build

# Main
touch src/main.cpp

# 👤 Member 1 — Product & Recommendation
touch src/product/Product.cpp
touch src/product/Electronics.cpp
touch src/product/Food.cpp
touch src/product/Clothing.cpp
touch src/product/RecommendationService.cpp

touch include/product/Product.h
touch include/product/Electronics.h
touch include/product/Food.h
touch include/product/Clothing.h
touch include/product/RecommendationService.h

# 👤 Member 2 — Cart & Order
touch src/order/Cart.cpp
touch src/order/CartItem.cpp
touch src/order/Order.cpp

touch include/order/Cart.h
touch include/order/CartItem.h
touch include/order/Order.h

# 👤 Member 3 — Customer & UI
touch src/user/Customer.cpp
touch src/user/UI.cpp

touch include/user/Customer.h
touch include/user/UI.h

# 👤 Member 4 — Database & Store
touch src/database/Database.cpp
touch src/database/ProductDAO.cpp
touch src/database/OrderDAO.cpp
touch src/database/CustomerDAO.cpp
touch src/database/Store.cpp

touch include/database/Database.h
touch include/database/ProductDAO.h
touch include/database/OrderDAO.h
touch include/database/CustomerDAO.h
touch include/database/Store.h

# SQL schema
cat <<EOL > sql/schema.sql
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
EOL

# README
cat <<EOL > README.md
# C++ Store Project with MySQL

## Team Structure

- product/   → Product models & recommendation
- order/     → Cart & order logic
- user/      → UI & customer handling
- database/  → MySQL & system integration

## Build
make
./app
EOL

# Makefile
cat <<EOL > Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = \$(wildcard src/*/*.cpp) src/main.cpp
OUT = app

all:
\t\$(CXX) \$(CXXFLAGS) \$(SRC) -o \$(OUT)

clean:
\trm -f \$(OUT)
EOL

echo "✅ Project structure created successfully!"