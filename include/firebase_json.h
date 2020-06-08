void set_local_json()
{
  FirebaseJson Firecode_Space;
  Firecode_Space.addInt("Firecode_Occupancy", occupancy).addInt("Firecode_Capacity", capacity);


  FirebaseJson Bed_Space;
  Bed_Space.addInt("Bed_Occupancy", bed_occupancy).addInt("Bed_Capacity", bed_capacity);


  FirebaseJson Service_Status;
  Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space).addString("meal_status", meal_status);
  // Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space);

  FirebaseJson Shelter_Properties;
  Shelter_Properties.addDouble("latitude", shelter_latitude).addDouble("longitude", shelter_longitude).addString("phone_number", phone_number).addString("friendly_name", friendly_name).addString("friendly_address",friendly_address);

  FirebaseJson Shelter_Contact;
  Shelter_Contact.addString("phone_number", phone_number).addString("friendly_name", friendly_name);

  // Shelter_Properties.addDouble("latitude", shelter_latitude).addDouble("longitude", shelter_longitude);

  FirebaseJson Client_Properties;
  Client_Properties.addBool("adult_only",adult_only).addBool("youth_only",youth_only).addBool("family_only",family_only).addBool("male_only", male_only).addBool("female_only",female_only).addBool("lgbtq_only",lgbtq_only).addBool("pet_friendly", pet_friendly).addBool("all_allowed",all_allowed);

  json.addJson("Service_Status", &Service_Status).addJson("Shelter_Properties", &Shelter_Properties).addJson("Shelter_Contact", &Shelter_Contact).addJson("Client_Properties", &Client_Properties);
}

void write_local_to_remote()
{
  if (Firebase.setJSON(firebaseData, path, json))
  {
      Serial.println("PASSED local json pushed to firebase!");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("------------------------------------");
      Serial.println();
  }
  else
  {
      Serial.println("FAILED push local json to firebase!");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
  }
}
