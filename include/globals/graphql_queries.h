#ifndef GRAPHQL_H
#define GRAPHQL_H

// Attempting to do a multi-line variable declaration: HOWTO?
const char *PUSH = "               \
mutation CreateSignalMeasurement(  \
  $signalId: ID!                   \
  $signalSecret: String!           \
  $measurement: Int!               \
) {                                \
  createSignalMeasurement(         \
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

const char *PULL = "               \
query CheckSignalMeasurement(      \
  $signalId: ID!                   \
) {                                \
    signal(id: $signalId)  {       \
      measurements (limit:1){      \
        occupancy                  \
        {                          \
          spots                    \
          beds                     \
        }                          \
        capacity                   \
        {                          \
          spots                    \
          beds                     \
        }                          \
      }                            \
    }                              \
}";

#endif