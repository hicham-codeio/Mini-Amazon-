#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "database/Store.h"

class RecommendationPage : public QWidget {
    Q_OBJECT
public:
    explicit RecommendationPage(Store& store, QWidget* parent = nullptr);
    void refreshRecommendations();

private:
    Store& store;
    class QScrollArea* scrollArea;
    class QWidget* scrollWidget;
    class QGridLayout* gridLayout;

    void setupUI();
};
