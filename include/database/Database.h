#include <stdio.h>

class Database {
private:
MYSQL* conn;
public:
bool connect();
void disconnect();
MYSQL* getConnection();
};