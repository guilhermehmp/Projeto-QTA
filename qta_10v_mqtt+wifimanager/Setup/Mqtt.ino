void callback(char* topic, byte* payload, unsigned int length) {
  String conc_payload;
  for (int i = 0; i < length; i++) {
    conc_payload  += ((char)payload[i]);
  }
  my_payload = conc_payload;
  my_topic = topic;
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("QTA_IoT")) {
      Serial.println("connected");
      client.subscribe("QTA_IoT_Recebe");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

 
