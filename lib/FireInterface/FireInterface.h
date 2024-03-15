/**
 * @author T Motsoeneng
 * @email tshepomotsoeneng0@gmail.com
 * @create date 2024-03-15
 * @modify date 2024-03-15
 */

#include <Arduino.h>

#ifndef FireInterface_h
#define FireInterface_h

class FireInterface{
    private:
        String _apiKey;
        String _dbUrl;
        String _readPath;
        String _userEmail;
        String _userPassword;
        String _cachedRead;
        void _processJson();
    
    public:
        FireInterface(String apiKey, String dbUrl, String readPath, String userEmail, String userPassword);
        void connect();
        void ready();
        void read();
};

#endif