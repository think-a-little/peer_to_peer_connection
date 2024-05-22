#include "apcs.h"

APCS::APCS(int flight_type, int flight_number, int cycle_number, int segment_number) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
}
