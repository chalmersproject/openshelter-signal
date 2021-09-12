//////////////////////////////////////////////////////////
//                Shelter Properties                    //
//////////////////////////////////////////////////////////
#define shelter_latitude 43.63178
#define shelter_longitude -79.42077
String phone_number = "(647)-333-1223";
String shelter_name = "better_living_center_respite";
String friendly_name = "Better Living Center Respite";
String friendly_address = "195 Princess Blvd Toronto, ON M6K3C3";

//available space
int occupancy = 30;
int capacity = 120;
//------------------------//
int bed_occupancy = 42;
int bed_capacity = 100;

//Client Properties
bool adult_only = false;
bool youth_only = false;
bool family_only = false;
bool male_only = false;
bool female_only = false;
bool lgbtq_only = false;
bool all_allowed = true;
bool pet_friendly = false;

//meal_status (meal, no_meal, snacks)
String meal_status = "meal";

//------------------------//
// creates path variables for firebase to use
String path = "/Shelters/" + shelter_name;
String path_firecode_occupancy = "/Shelters/" + shelter_name + "/Service_Status/Firecode_Space/Firecode_Occupancy";
