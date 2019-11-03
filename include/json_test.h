void json_test()
{
    String path = "/Shelters/st_felix_augusta";

    String jsonData = "";
    FirebaseJson testJson;

    FirebaseJson Firecode_Space;
    Firecode_Space.addInt("Firecode_Occupancy", firecode_occupancy).addInt("Firecode_Capacity",firecode_capacity);
    
    FirebaseJson Bed_Space;
    Bed_Space.addInt("Bed_Occupancy", bed_occupancy).addInt("Bed_Capacity", bed_capacity);

    
    FirebaseJson Service_Status;
    Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space).addString("meal_status", meal_status);
    // Service_Status.addJson("Firecode_Space", &Firecode_Space).addJson("Bed_Space", &Bed_Space);

    FirebaseJson Client_Properties;
    Client_Properties.addBool("adult_only",adult_only).addBool("youth_only",youth_only).addBool("family_only",family_only).addBool("male_only",male_only).addBool("female_only",female_only).addBool("lgbtq_only",lgbtq_only).addBool("all_allowed",all_allowed);

    FirebaseJson json;
    json.clear().addJson("Service_Status", &Service_Status).addJson("Client_Properties", &Client_Properties);
    


/* !!------ EXAMPLE JSON.add* FUNCTIONS ------!!

json2.addString("test1","hello world").addString("test2","nice to see you");
jsonArr2.addInt(99).addBool(true).addDouble(190.24555673).addString("Firebase");
jsonArr.addJson(&json2).addString("welcome").addArray(&jsonArr2);
json3.addDouble("myVal",212.224).addString("myStr","bad");
json4.setJsonData("{\"simpleData\":\"this is a string\"}");//Manual set raw json string.
json.clear().addInt("data1",100).addArray("myArray",&jsonArr).addJson("anotherData",&json3).addJson("data2",&json4);

*/  


    Serial.println("------------------------------------");
    Serial.println("JSON Data");
    Serial.println(json.toString());
    Serial.println("------------------------------------");
    


   
    Serial.println("------------------------------------");
    Serial.println("Set JSON test...");

    if (Firebase.setJSON(firebaseData, path, json))
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
        else if (firebaseData.dataType() == "json")
            Serial.println(firebaseData.jsonData());
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



    Serial.println("------------------------------------");
    Serial.println("Get JSON test...");

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

    FirebaseJsonObject jsonParseResult;


     Serial.println("------------------------------------");
     Serial.println("Iterate all get back json data...");

      testJson.clear().setJsonData(jsonData);
      testJson.parse();
      size_t count =testJson.getJsonObjectIteratorCount();
      String key;
      String value;

      for (size_t i = 0; i < count; i++)
      {
        
        testJson.jsonObjectiterator(i,key,value);
        jsonParseResult = testJson.parseResult();

        Serial.print("KEY: ");
        Serial.print(key);
        Serial.print(", ");
        Serial.print("VALUE: ");
        Serial.print(value); 
        Serial.print(", ");
        Serial.print("TYPE: ");
        Serial.println(jsonParseResult.type);        

      }

     Serial.println("------------------------------------");
     Serial.println();


    Serial.println("------------------------------------");
    Serial.println("Parse for some child node...");

    
    testJson.parse().get("Client_Properties").get("all_allowed");    

    jsonParseResult = testJson.parseResult();

    if(jsonParseResult.success){
     
      Serial.println("1. Parse json data result for node /Client_Properties/all_allowed");
      Serial.print("TYPE: ");
      Serial.println(jsonParseResult.type);
      Serial.print("VALUE: ");
      Serial.println(jsonParseResult.stringValue);
      //Serial.println(jsonParseResult.doubleValue);

    }else{
      Serial.println("1. Parse json data for node /Client_Properties/all_allowed!");
    } 

    //Set parse with false to get data through all children nodes, 
    //otherwise this would be failed to get child node data because of it's under data2 node.
    testJson.parse(false).get("simpleData"); 


    jsonParseResult = testJson.parseResult();

    Serial.println();

    if(jsonParseResult.success){
     
      Serial.println("2. Parse json data result for node /data2/simpleData with skipChild set to false");
      Serial.print("TYPE: ");
      Serial.println(jsonParseResult.type);
      Serial.print("VALUE: ");
      Serial.println(jsonParseResult.stringValue);
      //Serial.println(jsonParseResult.doubleValue);

    }else{
      Serial.println("2. Parse json data for node /data2/simpleData was failed!");
    }    



    //Any json object inside array also can be accessed by set parse(false),
    //The next test will ignore it and the result was failed as expected.
    testJson.parse().get("test2"); 


    jsonParseResult = testJson.parseResult();

    Serial.println();

    if(jsonParseResult.success){
     
      Serial.println("3. Parse json data result for node /myArray/test2 with skipChild set to true, or ignored");
      Serial.print("TYPE: ");
      Serial.println(jsonParseResult.type);
      Serial.print("VALUE: ");
      Serial.println(jsonParseResult.stringValue);
      //Serial.println(jsonParseResult.doubleValue);

    }else{
      Serial.println("3. Parse json data for node /myArray/test2 was failed as expected!");
    }     
        
     Serial.println("------------------------------------");
     Serial.println();
}