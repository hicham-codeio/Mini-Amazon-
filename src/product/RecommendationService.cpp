#include "product/RecommendationService.h"
#include <algorithm>

std::vector<std::shared_ptr<Product>> RecommendationService::recommend(const std::vector<std::shared_ptr<Product>>& allProducts) {
    std::vector<std::shared_ptr<Product>> recommendations = allProducts;
    
    // Sort by stock descending to simulate popularity/availability
    std::sort(recommendations.begin(), recommendations.end(), [](const std::shared_ptr<Product>& a, const std::shared_ptr<Product>& b) {
        return a->getStock() > b->getStock();
    });

    if (recommendations.size() > 3) {
        recommendations.resize(3);
    }
    
    return recommendations;
}
