/* test.cpp
 * Corin Sandford
 * Fall 2016
 * This file is made into an executable: 'test'
 * Used to test high level things in the library
 */

#include <DRRT/drrt.h>

using namespace std;

int main( int argc, char* argv[] )
{
    error("Begin");
    string algorithmName = "RRTx";              // "RRT", "RRT*", "RRT#", or "RRTx"
    string expName = "Debug";                   // Name for output files

    double changeThresh = 1.0;                  // only for RRTx
    double total_time = 5.0;                    // total planning time (move after this,
                                                // and keep planning *50*
    double slice_time = 1.0/10.0;               // for saving data
    double envRad = 50.0;                       // environment spans -envRad to envRad
                                                // in each dimension
    double robotRad = 0.5;                      // robot radius
    string distanceFunction = "R3SDist";        // distance function for KD-Tree

    Eigen::VectorXd start(4), goal(4);
    start << 0.0, 0.0, 0.0, PI/4;               // robot goes to here *0,-40,0,pi/3*
                                                // (start location of search tree)
    goal << 50.0, 50.0, 0.0, -3*PI/4 ;          // robot comes from here *-40,40,0,-pi/3*
                                                // (goal location of search tree)

    bool MoveRobot = true;

    int d = 4;                                  // number of dimensions [x y 0.0(time) theta]
    //double timeOut = INF;                     // not used?

    Eigen::VectorXd lowerBounds(4), upperBounds(4);
    lowerBounds << -envRad, -envRad, 0.0, 0.0;
    upperBounds << envRad, envRad, 0.0, 2*PI;

    CSpace* C = new CSpace( d, /*-1.0,*/ lowerBounds, upperBounds, start, goal );

    C->robotRadius = robotRad;                  // init robot radius
    C->robotVelocity = 2.0;                     // init robot velocity
    C->minTurningRadius = 1.0;                  // init robot turning radius
    C->randNode = "randNodeOrFromStack(C)";     // set up sampling function
                                                // randNodeOrFromStack( C );
                                                // this is hard coded in drrt::RRTX()
    C->pGoal = 0.01;                            // probability for not picking random node
    C->spaceHasTime = false;                    // not using time parameter
    C->spaceHasTheta = true;                    // using theta (yaw)

    error("Parameters defined\nRunning RRTx");

    RRTX( C, total_time, slice_time, 10.0, 100.0, changeThresh, algorithmName, MoveRobot, false, false, "", distanceFunction );

    return 0;
}
