/**
 * @author T Motsoeneng
 * @link https://github.com/themegat
 */

#include <Arduino.h>
#include <vector>

#ifndef FireInterface_h
#define FireInterface_h

typedef struct
{
    String key;
    String value;
} FireStringMap;

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
    void append(String node, String key, std::vector<FireStringMap> payload);
};

#endif