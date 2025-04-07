#ifndef MYWIFI_H
#define MYWIFI_H

class myWiFi{
    public:
    myWiFi();
    bool connect(const char* ssid, const char* password, int timeout);
    void disconnect();
    bool connected();
};

#endif