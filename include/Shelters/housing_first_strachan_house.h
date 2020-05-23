//////////////////////////////////////////////////////////
//                Shelter Properties                    //
//////////////////////////////////////////////////////////
#define shelter_latitude 43.640730
#define shelter_longitude -79.410792
String phone_number = "(416) 395-0928";
String friendly_name = "Housing First Strachan House";
String friendly_address = "805A Wellington St W Toronto";

String shelter_name = "housing_first_strachan_house";
String path = "/Shelters/" + shelter_name;
String path_firecode_occupancy = "/Shelters/" + shelter_name + "/Service_Status/Firecode_Space/Firecode_Occupancy";
//available space
int firecode_occupancy = 0;
int firecode_capacity = 88;
//------------------------//
int bed_occupancy = 42;
int bed_capacity  = 60;

//Client Properties
bool adult_only = true;
bool youth_only = false;
bool family_only = false;
bool male_only = false;
bool female_only = false;
bool lgbtq_only = false;
bool pet_friendly = false;
bool all_allowed = false;


//meal_status (meal, no_meal, snacks)
String meal_status = "meal";