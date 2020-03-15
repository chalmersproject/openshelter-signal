//////////////////////////////////////////////////////////
//                Shelter Properties                    //
//////////////////////////////////////////////////////////
#define shelter_latitude 43.6492
#define shelter_longitude -79.3995
String phone_number = "4162031624";
String friendly_name = "St. Felix Centre Augusta";


//json objects
FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonObject jsonParseResult;

String jsonData = "";
FirebaseJson testJson;

String path = "/Shelters/st_felix_augusta";
String path_firecode_occupancy = "/Shelters/st_felix_augusta/Service_Status/Firecode_Space/Firecode_Occupancy";
//available space
int bed_occupancy = 42;
int bed_capacity      = 43;
//------------------------//
int firecode_capacity = 65;
int firecode_occupancy = 42;

//Client Properties
bool adult_only = false;
bool youth_only = false;
bool family_only = false;
bool male_only = false;
bool female_only = false;
bool lgbtq_only = false;
bool all_allowed = true;

//meal_status (meal, no_meal, snacks)
String meal_status = "meal";