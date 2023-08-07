#ifndef GRAPHQL_H
#define GRAPHQL_H

const char *PUSH = R"PUSH(
mutation CreateSignalMeasurement(
  $signalId: ID!
  $secretKey: String!
  $measurement: Int!
  ){
  createShelterMeasurement(
    input: {
      signalId: $signalId,       
      secretKey: $secretKey,    
      value: $measurement 
    }
  ) {
    shelterMeasurement {
      id
      value
    }
    errors
  }
} 
)PUSH";

const char *PULL = R"PULL(
query CheckSignalMeasurement(
  $signalId: ID!
  ) {
  shelterSignalMeasurementLast(id: $signalId){
    id
    value
    type
  }
}
)PULL";

const char *UPDATE_PARAMETERS = R"PARAMS(
query ShelterFromSignalId(
  $signalId: ID!
){
  shelterFromSignalId(id: $signalId )
  {
    id
    name
    maxHeadcount
    maxBedcount
  }
}
)PARAMS";

#endif