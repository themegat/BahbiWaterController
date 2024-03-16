/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */

#include <Arduino.h>
#include <vector>

#ifndef FireInterface_h
#define FireInterface_h

typedef struct
{
    String key;
    String value;
} FireMap;

class FirebaseJson;

class FireInterface
{
private:
    String _apiKey;
    String _dbUrl;
    String _readPath;
    String _writePath;
    String _userEmail;
    String _userPassword;
    String _cachedRead;
    void _processJson();

public:
    FireInterface();
    void connect();
    void ready();
    void read();
    void append(String node, String key, std::vector<FireMap> payload);
};

#endif