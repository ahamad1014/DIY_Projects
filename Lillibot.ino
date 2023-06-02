#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi Credentials
const char* ssid = "FTTH-E109";
const char* password = "123456789";

int IP1 =1;   
int IP2 =3;    
int IP3 =15;
int IP4 =13;

ESP8266WebServer server(80);

static const char PROGMEM INDEX_HTML[] = R"(
<html>
  <head>
    <title>ESP8266 Robot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}
      table { margin-left: auto; margin-right: auto; }
      td { padding: 8 px; }
      .button 
      {
        background-color: #2f4468;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 18px;
        margin: 6px 3px;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }
    </style>
  </head>
  <body>
    <h1>ESP8266 Robot</h1>
    <table>
      <tr>
 <td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('forward');" ontouchstart="toggleCheckbox('forward');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Forward</button></td></tr>
      <tr><td align="center"><button class="button" onmousedown="toggleCheckbox('left');" ontouchstart="toggleCheckbox('left');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Left</button></td><td align="center"><button class="button" onmousedown="toggleCheckbox('stop');" ontouchstart="toggleCheckbox('stop');">Stop</button></td><td align="center"><button class="button" onmousedown="toggleCheckbox('right');" ontouchstart="toggleCheckbox('right');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Right</button></td></tr>
      <tr>
        <td colspan="3" align="center">
          <button class="button" onmousedown="toggleCheckbox('backward');" ontouchstart="toggleCheckbox('backward');" onmouseup="toggleCheckbox('stop');" ontouchend="toggleCheckbox('stop');">Backward</button>
        </td>
      </tr>                   
    </table>
    <script>
    function toggleCheckbox(x)
    {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/action?action=" + x, true);
      xhr.send();
    }
  </script>
  </body>
</html>
)";

void setup() {
  pinMode( IP1, OUTPUT);
  pinMode( IP2, OUTPUT);
  pinMode( IP3, OUTPUT);
  pinMode( IP4, OUTPUT);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/action", handleAction);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleAction() {
  String action = server.arg("action");

  if (action == "forward")
  {
    digitalWrite(IP1, HIGH);  /* 1  */
    digitalWrite(IP2, LOW); /* 0  */

    digitalWrite(IP3, HIGH);  /* 1  */
    digitalWrite(IP4, LOW); /* 0  */
      

    Serial.println("Device FORWARD");
  }
  else if (action == "backward")
  {
    digitalWrite(IP1, LOW);  /* 0  */
    digitalWrite(IP2, HIGH); /* 1  */
    
    digitalWrite(IP3, LOW);  /* 0  */
    digitalWrite(IP4, HIGH); /* 1  */
 
    Serial.println("Device BACKWARD");
  }
  else if (action == "left")
  {
    digitalWrite(IP1, LOW);  /* 0  */
    digitalWrite(IP2, HIGH); /* 1  */
    
    digitalWrite(IP3, HIGH);  /* 1  */
    digitalWrite(IP4, LOW); /* 0  */

    Serial.println("Device LEFT");
  }
  else if (action == "right")
  {
    digitalWrite(IP1, HIGH);  /* 1  */
    digitalWrite(IP2, LOW); /* 0  */
    
    digitalWrite(IP3, LOW);  /* 0  */
    digitalWrite(IP4, HIGH); /* 1  */

    Serial.println("Device RIGHT");
  }
  else if (action == "stop")
  {
    digitalWrite(IP1, LOW);  /* 0  */
    digitalWrite(IP2, LOW); /* 0  */
    digitalWrite(IP3, LOW);  /* 0  */
    digitalWrite(IP4, LOW); /* 0  */

    Serial.println("Device OFF");
  }

  server.send(200, "text/html", "Action: " + action);
}


void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

