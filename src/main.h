// Define functional protoypes.

#define DEG_2_RAD 180/M_PI
#define GLOBAL_RADIUS 6371000
#define PAUSE_FOR_LOOP 1000
#define MAX_PELOTON 4

#define BRAKE_THRESHOLD 234
#define SWERVE_THRESHOLD 654

// Define the Rider structure to hold a consistent set of information
struct Rider {
    double latitude;
    double longitude;
    double elevation = 0;
    double heading = 0;
    double speed = 0;
    double accel_x = 0;
    double accel_y = 0;
    bool is_swerving = false;
    bool is_breaking = false;
    String name = "none";
    String address = "00001";
};