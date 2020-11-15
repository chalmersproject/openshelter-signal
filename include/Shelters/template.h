//////////////////////////////////////////////////////////
//                Shelter Properties                    //
//////////////////////////////////////////////////////////
#define shelter_latitude 00.0000000
#define shelter_longitude -00.0000000
String phone_number = "(416) 555-5555";
String shelter_name = "best_shelter_in_the_world";
String friendly_name = "The best shelter in the world";
String friendly_address = "555 Somewherin Toronto";

//available space
int occupancy = 0;
int capacity = 88;
//------------------------//
int bed_occupancy = 42;
int bed_capacity = 60;

//Client Properties
bool adult_only = false;
bool youth_only = false;
bool family_only = false;
bool male_only = false;
bool female_only = false;
bool lgbtq_only = false;
bool all_allowed = false;
bool pet_friendly = false;

//meal_status (meal, no_meal, snacks)
String meal_status = "meal";

//------------------------//
// creates path variables for firebase to use
String path = "/Shelters/" + shelter_name;
String path_firecode_occupancy = "/Shelters/" + shelter_name + "/Service_Status/Firecode_Space/Firecode_Occupancy";
