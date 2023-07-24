#ifndef GRAPHQL_H
#define GRAPHQL_H

// Attempting to do a multi-line variable declaration: HOWTO?

const char *PUSH = R"PUSH(
mutation CreateSignalMeasurement(
  $signalId: ID!
  $secretKey: String!
  $value: Int!
  ){
  createShelterMeasurement(
    input: {
      signalId: $signalId,       
      secretKey: $signalSecret,    
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
  $id: ID!
  ) {
  shelterSignalMeasurementLast(id: $signalId){
    id
    value
    type
  }
}
)PULL";

#endif