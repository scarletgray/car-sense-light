// Define functional protoypes.

#define DEG_2_RAD 180/M_PI
#define GLOBAL_RADIUS 6371000
#define PAUSE_FOR_LOOP 1000
#define MAX_PELOTON 4

#define BRAKE_THRESHOLD 234
#define SWERVE_THRESHOLD 654

#define NRF_TIMEOUT 1000
#define NRF_ADDRESS 00065

// Define the Rider structure to hold a consistent set of information
struct Rider {
    double latitude;
    double longitude;
    double elevation;
    double heading;
    double speed;
    double accel_x;
    double accel_y;
    bool is_swerving;
    bool is_breaking;
    int address;
};