#ifndef WeRaspberryPi_H
#define WeRaspberryPi_H

#include <Arduino.h>

class WeRaspberryPi
{
public:
	WeRaspberryPi();

    void init();

	bool setBlocklyServer(bool isOn);
    
    uint8_t setWifiInformation(String _ssid, String _password);

    uint8_t  result_len;
    uint8_t result_buffer[64];

    bool contains(const uint8_t text_buffer[], uint8_t size);

	bool speechRecognition(void);
	bool textToSpeech(const uint8_t gbk_code[], uint32_t len);
	bool freeDialogue(void);

    bool setBaiduAccount(String _apikey, String _secretkey);
    bool textRecognition();
    bool animalRecognition();
    bool plantRecognition();
    bool objectRecognition();

    bool tinywebdbUpdate(String _user, String _secret, String _tag, String _value);
    bool tinywebdbGet(String _user, String _secret, String _tag);
    bool tinywebdbDelete(String _user, String _secret, String _tag);
    bool tinywebdbCount(String _user, String _secret);
    char* tinywebdbGetResult(String _user, String _secret, String _tag);

    bool faceTrain(uint8_t number);
    bool faceCompare(uint8_t number); 

};

#endif