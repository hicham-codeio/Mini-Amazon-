# 🛒 Mini E-Commerce System

A console-based Mini E-Commerce application developed in **C++** using **Object-Oriented Programming (OOP)** principles. The system allows customers to browse products, manage a shopping cart, place orders, and receive product recommendations.

## 📌 Features

* Product catalog management
* Product categories:

  * Electronics
  * Food
  * Clothing
* Shopping cart management
* Order processing and checkout
* Order history tracking
* Product recommendations
* Inventory and stock management
* Modular architecture using OOP concepts
* Data persistence through DAO and Database layers

---



## 🚀 Technologies Used

* C++17
* Qt Framework (GUI Development)
* Object-Oriented Programming (OOP)
* STL (Standard Template Library)
* MySQL Database
* DAO (Data Access Object) Design Pattern
* Git & GitHub for Version Control
---

## 🎯 OOP Concepts Applied

* Encapsulation
* Inheritance
* Polymorphism
* Abstraction
* Composition

---

## ⚙️ Build & Run

### Using g++

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o build/MiniAmazonCLI
g++ -std=c++17 -Iinclude src/*.cpp -o build/MiniAmazonGUI
```

Run:

```bash
./build/MiniAmazonCLI
./build/MiniAmazonGUI
```

### Using Makefile

```bash
make
./build/MiniAmazonCLI
./build/MiniAmazonGUI
```

---

## 👥 Team Members & Responsibilities

### 🔹 Hicham Ait Douch — Team Leader, Database & Store

Classes:

* Database
* ProductDAO
* OrderDAO
* CustomerDAO
* Store

Responsibilities:

* Team coordination and project integration
* System architecture and module integration
* Data persistence management
* Application flow control
* Code review, testing, and final deployment


### 🔹 Mohamed Ouhsine — Product & Recommendation

Classes:

* Product (Abstract)
* Electronics
* Food
* Clothing
* RecommendationService

Responsibilities:

* Product hierarchy design
* Inheritance implementation
* Polymorphism and recommendation logic
* Product management

### 🔹 Abdelghafor Agdz — Cart & Order

Classes:

* Cart
* CartItem
* Order

Responsibilities:

* Shopping cart management
* Total price calculations
* Checkout workflow
* Order generation

### 🔹 Ayoub Motaoukil — Customer & UI

Classes:

* Customer
* UI / Menu System

Responsibilities:

* User interaction
* Menu navigation
* Order history management
* Error handling


## 📷 Example Features

* Browse available products
* Add products to cart
* View shopping cart
* Checkout orders
* View order history
* Receive product recommendations

---


---

## 🎉 Final Note

> From segmentation faults to shopping carts — mission accomplished.
