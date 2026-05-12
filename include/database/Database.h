#include <iostream>

class Database {
private:
MYSQL* conn;
public:
bool connect();
void disconnect();
MYSQL* getConnection();
};