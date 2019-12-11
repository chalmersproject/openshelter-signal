FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonObject jsonParseResult;

String jsonData = "";
FirebaseJson testJson;

void set_local_json()
{
  FirebaseJson Firecode_Space;
  Firecode_Space.addInt("Firecode_Occupancy", firecode_occupancy).addInt("Firecode_Capacity",firecode_capacity);

  Serial.print("firecode_occupancy init value: ");
  Serial.println(firecode_occupancy);


  FirebaseJson Bed_Space;
  Bed_Space.addInt("Bed_Occupancy", bed_occupancy).addInt("Bed_Capacity", bed_capacity);


  FirebaseJson Service_Status;
  Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space).addString("meal_status", meal_status);
  // Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space);

  FirebaseJson Client_Properties;
  Client_Properties.addBool("adult_only",adult_only).addBool("youth_only",youth_only).addBool("family_only",family_only).addBool("male_only", male_only).addBool("female_only",female_only).addBool("lgbtq_only",lgbtq_only).addBool("all_allowed",all_allowed);


  // json.clear().addJson("Service_Status", &Service_Status).addJson("Client_Properties", &Client_Properties);
  json.addJson("Service_Status", &Service_Status).addJson("Client_Properties", &Client_Properties);
}

void pull_remote_json()
{
  if (Firebase.getJSON(firebaseData, path))
  {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.print("VALUE: ");
      if (firebaseData.dataType() == "int")
          Serial.println(firebaseData.intData());
      else if (firebaseData.dataType() == "float")
          Serial.println(firebaseData.floatData(), 5);
      else if (firebaseData.dataType() == "double")
          printf("%.9lf\n", firebaseData.doubleData());
      else if (firebaseData.dataType() == "boolean")
          Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
      else if (firebaseData.dataType() == "string")
          Serial.println(firebaseData.stringData());
      else if (firebaseData.dataType() == "json"){

         jsonData = firebaseData.jsonData(); //store for next test
         Serial.println(firebaseData.jsonData());

      }
      Serial.println("------------------------------------");
      Serial.println();
  }
  else
  {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
  }
}

void write_remote_json_to_local()
{
  Serial.println("Clear local JSON");
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
