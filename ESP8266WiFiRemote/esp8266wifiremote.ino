#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "ircodes.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

//GPIO pins
#define GPIO4 4
#define GPIO0 0

//Set wifi credentials here
const char* ssid     = "";
const char* password = "";

//set GPIO 4 to send IR signals
IRsend irsend(GPIO4);  

//Start server on port 80
ESP8266WebServer server(80);

// set the specified channel
void set_channel(String value, String *message)
{
  if (message != NULL)
  {
    *message += value;
  }
  for (int i = 0; i < value.length(); i++)
  {
    switch (value.charAt(i))
    {
      case '0':
        irsend.sendRaw(rawData0, sizeof(rawData0) / sizeof(uint16_t), 38);
        break;
      case '1':
        irsend.sendRaw(rawData1, sizeof(rawData1) / sizeof(uint16_t), 38);
        break;
      case '2':
        irsend.sendRaw(rawData2, sizeof(rawData2) / sizeof(uint16_t), 38);
        break;
      case '3':
        irsend.sendRaw(rawData3, sizeof(rawData3) / sizeof(uint16_t), 38);
        break;
      case '4':
        irsend.sendRaw(rawData4, sizeof(rawData4) / sizeof(uint16_t), 38);
        break;
      case '5':
        irsend.sendRaw(rawData5, sizeof(rawData5) / sizeof(uint16_t), 38);
        break;
      case '6':
        irsend.sendRaw(rawData6, sizeof(rawData6) / sizeof(uint16_t), 38);
        break;
      case '7':
        irsend.sendRaw(rawData7, sizeof(rawData7) / sizeof(uint16_t), 38);
        break;
      case '8':
        irsend.sendRaw(rawData8, sizeof(rawData8) / sizeof(uint16_t), 38);
        break;
      case '9':
        irsend.sendRaw(rawData9, sizeof(rawData9) / sizeof(uint16_t), 38);
        break;
    }
    delay(100);
  }
  irsend.sendRaw(rawDataOK, sizeof(rawDataOK) / sizeof(uint16_t), 38);
}

// root web page
void handle_root()
{
  String message = "<!DOCTYPE html>\n"
                   "<html>\n"
                   "<head>\n"
                   "<title>TV Web Remote</title>\n"
                   "<script>\n"
                   "function pressButton(btn,value){\n"
                   " var xmlhttp = new XMLHttpRequest();\n"
                   " xmlhttp.onreadystatechange=function() {\n"
                   "  if (xmlhttp.readyState==4 && xmlhttp.status==200) {\n"
                   "   var response = xmlhttp.responseText;\n"
                   "  }\n"
                   " }\n"
                   " xmlhttp.open('GET','/button?task=' + btn + '&value=' + value);\n"
                   " xmlhttp.send();\n"
                   " return false;\n"
                   "}\n"
                   "</script>\n"
                   "</head>\n"
                   "<body>\n"
                   "<style type='text/css'>\n"
                   "body {\n"
                   "  padding-left:20px;\n"
                   "  padding-right:20px;\n"
                   "  margin: 0;\n"
                   "  font-family: Geneva,'Lucida Sans','Lucida Grande',sans-serif;\n"
                   "  font-size: 30px;\n"
                   "  line-height: 40px;\n"
                   "  color: #575757;\n"
                   "  background-color: #fff;\n"
                   "}\n"
                   ".buttongroup {\n"
                   " width:100%;\n"
                   " max-width:800px;\n"
                   "}\n"
                   ".span6 {\n"
                   "  width:48%;\n"
                   "}\n"
                   ".span4 {\n"
                   " width:31.5%;\n"
                   "}\n"
                   ".span12 {\n"
                   " width:100%;\n"
                   "}\n"
                   ".button {\n"
                   "  border:2px solid #333;\n"
                   "  padding-top:30px;\n"
                   "  padding-bottom:30px;\n"
                   "  margin:2px;\n"
                   "  text-align:center;\n"
                   "  font-weight:bold;\n"
                   "  max-width:380px;\n"
                   "  float:left;\n"
                   "  border-radius: 48px;\n"
                   "  background-color: #eee;\n"
                   "}\n"
                   "a {\n"
                   "  color: #333;\n"
                   "}\n"
                   ".buttonrow {\n"
                   "  clear: both;\n"
                   "}\n"
                   ".power_btn {\n"
                   "  background-color:#f88;\n"
                   "}\n"
                   ".number_btn {\n"
                   " background-color:#aaa;\n"
                   "}\n"
                   ".channel_btn {\n"
                   " background-color:#8f8;\n"
                   "}\n"
                   "</style>\n"
                   "<div class='buttongroup span12'>\n"
                   "<a href='#' onclick='pressButton(\"power\");return false;'><div class='button power_btn span4'>Power</div></a>\n"
                   "<a href='#' onclick='pressButton(\"tvpower\");return false;'><div class='button power_btn span4'>N/A</div></a>\n"
                   "<a href='#' onclick='pressButton(\"cablepower\");return false;'><div class='button power_btn span4'>N/A</div></a>\n"
                   "</div>\n"
                   "<div class='buttongroup span12'>\n"
                   "<a href='#' onclick='pressButton(\"source\");return false;'><div class='button span6'>Source</div></a>\n"
                   "<a href='#' onclick='pressButton(\"mute\");return false;'><div class='button span6'>Mute</div></a>\n"
                   "<a href='#' onclick='pressButton(\"volup\");return false;'><div class='button span6'>Volume+</div></a>\n"
                   "<a href='#' onclick='pressButton(\"chanup\");return false;'><div class='button span6'>Channel+</div></a>\n"
                   "<a href='#' onclick='pressButton(\"voldn\");return false;'><div class='button span6'>Volume-</div></a>\n"
                   "<a href='#' onclick='pressButton(\"chandn\");return false;'><div class='button span6'>Channel-</div></a>\n";
  //message += cbuttons;
  message +=
    "</div>\n"
    "<div class='buttongroup span12'>\n"
    "<a href='#' onclick='pressButton(\"num7\");'><div class='button number_btn span4'>7</div></a>\n"
    "<a href='#' onclick='pressButton(\"num8\");'><div class='button number_btn span4'>8</div></a>\n"
    "<a href='#' onclick='pressButton(\"num9\");'><div class='button number_btn span4'>9</div></a>\n"
    "<a href='#' onclick='pressButton(\"num4\");'><div class='button number_btn span4'>4</div></a>\n"
    "<a href='#' onclick='pressButton(\"num5\");'><div class='button number_btn span4'>5</div></a>\n"
    "<a href='#' onclick='pressButton(\"num6\");'><div class='button number_btn span4'>6</div></a>\n"
    "<a href='#' onclick='pressButton(\"num1\");'><div class='button number_btn span4'>1</div></a>\n"
    "<a href='#' onclick='pressButton(\"num2\");'><div class='button number_btn span4'>2</div></a>\n"
    "<a href='#' onclick='pressButton(\"num3\");'><div class='button number_btn span4'>3</div></a>\n"
    "<a href='#' onclick='pressButton(\"ok\");'><div class='button number_btn span4'>OK</div></a>\n"
    "<a href='#' onclick='pressButton(\"num0\");'><div class='button number_btn span4'>0</div></a>\n"
    "<a href='#' onclick='pressButton(\"return\");'><div class='button number_btn span4'>Return</div></a>\n"

    "</div>\n"
    "</body>\n"
    "</html>\n";
  server.send(200, "text/html", message);
  delay(100);
}

// button web page
void handle_button()
{
  digitalWrite(GPIO0, LOW);
  String message = "button send: ";
  String task = "";
  String value = "";
  task = "";
  value = "";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    if (server.argName(i) == "task")
    {
      task = server.arg(i);
    }
    if (server.argName(i) == "value")
    {
      value = server.arg(i);
    }
  }
  if (task == "mute")
  {
    message += "{mute}";
    irsend.sendRaw(rawDataMute, sizeof(rawDataMute) / sizeof(uint16_t), 38);
  }
  else if (task == "source")
  {
    message += "{source:" + value + "}";
    irsend.sendRaw(rawDataSource, sizeof(rawDataSource) / sizeof(uint16_t), 38);
    if (value.toInt() > 0)
    {
      delay(1500);
    }
    for (int i = 1; i <= min(10, value.toInt()); i++)
    {
      irsend.sendRaw(rawDataSource, sizeof(rawDataSource) / sizeof(uint16_t), 38);
      delay(250);
    }
  }
  else if (task == "power")
  {
    message += "{power}";
    irsend.sendRaw(rawDataPower, sizeof(rawDataPower) / sizeof(uint16_t), 38);
    delay(100);
  }
  else if (task == "volup")
  {
    message += "{volup:" + value + "}";
    for (int i = 0; i <= min(29, value.toInt()); i++)
    {
      irsend.sendRaw(rawDataVolumeUp, sizeof(rawDataVolumeUp) / sizeof(uint16_t), 38);
      delay(100);
    }

  }
  else if (task == "voldn")
  {
    message += "{voldn:" + value + "}";
    for (int i = 0; i <= min(29, value.toInt()); i++)
    {
      irsend.sendRaw(rawDataVolumeDown, sizeof(rawDataVolumeDown) / sizeof(uint16_t), 38);
      delay(100);
    }
  }
  else if (task == "chanup")
  {
    message += "{chanup}";
    for (int i = 0; i < min(200, value.toInt()); i++)
    {
      irsend.sendRaw(rawDataChannelUp, sizeof(rawDataChannelUp) / sizeof(uint16_t), 38);
      delay(100);
    }

  }
  else if (task == "chandn")
  {
    message += "{chandn}";
    for (int i = 0; i < min(200, value.toInt()); i++)
    {
      irsend.sendRaw(rawDataChannelDown, sizeof(rawDataChannelDown) / sizeof(uint16_t), 38);
      delay(100);
    }
  }
  else if (task == "num0")
  {
    message += "{0}";
    irsend.sendRaw(rawData0, sizeof(rawData0) / sizeof(uint16_t), 38);
  }
  else if (task == "num1")
  {
    message += "{1}";
    irsend.sendRaw(rawData1, sizeof(rawData1) / sizeof(uint16_t), 38);
  }
  else if (task == "num2")
  {
    message += "{2}";
    irsend.sendRaw(rawData2, sizeof(rawData2) / sizeof(uint16_t), 38);
  }
  else if (task == "num3")
  {
    message += "{3}";
    irsend.sendRaw(rawData3, sizeof(rawData3) / sizeof(uint16_t), 38);
  }
  else if (task == "num4")
  {
    message += "{4}";
    irsend.sendRaw(rawData4, sizeof(rawData4) / sizeof(uint16_t), 38);
  }
  else if (task == "num5")
  {
    message += "{5}";
    irsend.sendRaw(rawData5, sizeof(rawData5) / sizeof(uint16_t), 38);
  }
  else if (task == "num6")
  {
    message += "{6}";
    irsend.sendRaw(rawData6, sizeof(rawData6) / sizeof(uint16_t), 38);
  }
  else if (task == "num7")
  {
    message += "{7}";
    irsend.sendRaw(rawData7, sizeof(rawData7) / sizeof(uint16_t), 38);
  }
  else if (task == "num8")
  {
    message += "{8}";
    irsend.sendRaw(rawData8, sizeof(rawData8) / sizeof(uint16_t), 38);
  }
  else if (task == "num9")
  {
    message += "{9}";
    irsend.sendRaw(rawData9, sizeof(rawData9) / sizeof(uint16_t), 38);
  }
  else if (task == "ok")
  {
    message += "{ok}";
    irsend.sendRaw(rawDataOK, sizeof(rawDataOK) / sizeof(uint16_t), 38);
  }
  else if (task == "return")
  {
    message += "{return}";
    irsend.sendRaw(rawDataReturn, sizeof(rawDataReturn) / sizeof(uint16_t), 38);
  }
  else if (task == "channel")
  {
    message += "{channel}";
    set_channel(value, &message);
  }
  else if (task == "random")
  {
    message += "{random}";
    char mem[1024];
    char *tvalue = mem;
    strncpy(mem, value.c_str(), min(1024, sizeof(value)));
    if (strchr(tvalue, '-'))
    {
      const char *range1 = strtok(tvalue, "-");
      const char *range2 = strtok(NULL, "-");
      int newchannel = random(max(atoi(range1), 1), min(atoi(range2) + 1, 5000));
      set_channel(String(newchannel), &message);
    }
    else if (strchr(tvalue, ','))
    {
      const char *channels[100];
      int ccount = 0;
      const char *token;
      channels[ccount++] = token = strtok(tvalue, ",");
      while (token && ccount < 100)
      {
        channels[ccount++] = token = strtok(NULL, ",");
      }
      const char *newchannel = channels[random(0, ccount - 1)];
      set_channel(String(newchannel), &message);
    }
  }
  else
  {
    message += " {unknown:" + task + "}";
  }
  Serial.print("button pressed: ");
  Serial.println(task);
  server.send(200, "text/plain", message);
  delay(100);
  digitalWrite(GPIO0, HIGH);
}

void setup()
{
Serial.begin(115200);
  pinMode(GPIO0, OUTPUT); // set red LED
  randomSeed(analogRead(GPIO0));
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

  Serial.println("");
  Serial.println("Huzzah TV Web Server");
  delay(2000);
 // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\rConnecting");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite(0, HIGH);
    delay(500);
    digitalWrite(0, LOW);
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("\nConnected to: ");
  Serial.print(ssid);
  Serial.print("\nIP address: ");
  Serial.print(WiFi.localIP());
  server.on("/", handle_root);
  server.on("/button", handle_button);
  server.begin();
  Serial.print("\nHTTP server started");
}

void loop()
{
  delay(500);
  server.handleClient();
}