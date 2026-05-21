#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
    protected: 
        int id_prod;
        std::string nom;
        double prix;
        int stock;

    public:
        Product(int id, std::string n, double p, int q);
        virtual ~Product() = default;
        
        int getId() const;
        std::string getNom() const;
        double getPrix() const;
        int getStock() const;

        void NouveauStock(int quantite);

        virtual void affecher() const = 0; 
};

#endif