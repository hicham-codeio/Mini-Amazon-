#include "cli/UI.h"
#include "database/Database.h"

int main() {
    Database::initializeData();
    
    UI ui;
    ui.run();

    Database::cleanupData();
    return 0;
}
