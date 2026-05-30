#pragma once
#include <vector>
#include <memory>
#include "product/Product.h"

class RecommendationService {
public:
    static std::vector<std::shared_ptr<Product>> recommend(const std::vector<std::shared_ptr<Product>>& allProducts);
};
