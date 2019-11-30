FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonObject jsonParseResult;

String jsonData = "";
FirebaseJson testJson;
FirebaseJson Firecode_Space;

void set_local_json()
{
  Firecode_Space.addInt("Firecode_Occupancy", firecode_occupancy).addInt("Firecode_Capacity",firecode_capacity);

  FirebaseJson Bed_Space;
  Bed_Space.addInt("Bed_Occupancy", bed_occupancy).addInt("Bed_Capacity", bed_capacity);


  FirebaseJson Service_Status;
  Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space).addString("meal_status", meal_status);
  // Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space);

  FirebaseJson Client_Properties;
  Client_Properties.addBool("adult_only",adult_only).addBool("youth_only",youth_only).addBool("family_only",family_only).addBool("male_only",male_only).addBool("female_only",female_only).addBool("lgbtq_only",lgbtq_only).addBool("all_allowed",all_allowed);


  json.clear().addJson("Service_Status", &Service_Status).addJson("Client_Properties", &Client_Properties);
}

void write_remote_json_to_local()
{
  json.clear().setJsonData(jsonData);
  json.parse();
  size_t count = json.getJsonObjectIteratorCount();
  String key;
  String value;
  for (size_t i = 0; i < count; i++)
  {
    json.jsonObjectiterator(i,key,value);
    jsonParseResult = json.parseResult();

    Serial.print("KEY: ");
    Serial.print(key);
    Serial.print(", ");
    Serial.print("VALUE: ");
    Serial.print(value);
    Serial.print(", ");
    Serial.print("TYPE: ");
    Serial.println(jsonParseResult.type);
  }
}
