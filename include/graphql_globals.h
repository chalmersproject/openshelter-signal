///////////////////////////////////////////////////////////////////////////////////////////
//                    QUERY                                                              //
///////////////////////////////////////////////////////////////////////////////////////////

//
// REQUEST FORMAT:
//

/*
{
  query: "...the raw query text...",
  variables: {
    signalId: "...",
    signalSecret: "...",
    _MEASUREMENT: 10
  }
}

reqJson = {
  query: "...",
  variables: varJson
}
*/

// #define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE 256
#define VARBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://api.chalmersproject.com/graphql";
// Attempting to do a multi-line variable declaration: HOWTO?
const char *MUTATION = "           \
mutation MeasureShelterOccupancy(  \
  $signalId: ID!                   \
  $signalSecret: String!           \
  $measurement: Int!               \
) {                                \
  measureShelterOccupancy(         \
    input: {                       \
      signalId: $signalId          \
      signalSecret: $signalSecret  \
      measurement: $measurement    \
    }                              \
  ) {                              \
    measurement {                  \
      id                           \
    }                              \
  }                                \
}";

typedef struct graphqlQuery
{
  char req[REQBUFF_SIZE];
  char var[VARBUFF_SIZE];
  int status;
  String resp;
} GraphqlQuery;

// HTTP POST to chalmersproject API
void occupancy_request(WiFiClientSecure client, int _MEASUREMENT)
{
  // GraphqlQuery *graphql = (GraphqlQuery *)malloc(sizeof(GraphqlQuery));
  HTTPClient http;
  DynamicJsonDocument reqJson(1024);
  DynamicJsonDocument varJson(1024);
  varJson["signalId"] = SIGNAL_ID;
  varJson["signalSecret"] = SIGNAL_SECRET;
  varJson["measurement"] = _MEASUREMENT;

  Serial.println("Sending HTTP POST");
  http.begin(client, _API_HOST);
  http.addHeader("Content-Type", "application/json");
  reqJson["query"] = MUTATION;
  reqJson["variables"] = varJson;

  String request;
  serializeJson(reqJson, request);
  Serial.print("Request: ");
  Serial.println(request);

  http.POST(request);

  Serial.print("Response: ");
  Serial.println(http.getString());
}