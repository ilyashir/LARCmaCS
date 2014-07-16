#include "receiver.h"
#include <iostream>

using namespace std;

void ReceiverWorker::run(){

    QPointF p;
    SSL_DetectionFrame detection;
    int balls_n = 0;
    SSL_DetectionBall ball;
    int robots_blue_n = 0;
    int robots_yellow_n = 0;
    SSL_DetectionRobot robot;
    int team = 0;
    double x, y, orientation;
    double conf;
    int idCam = 0;

    client.open(false);

    cout << "run?" << endl;

    while(!shutdownread){

//        cout << "Run!" << endl;

        if ( client.receive(packet) )
        {
            //see if the packet contains a robot detection frame:
            if ( packet.has_detection() )
            {
//                PacketSSL packetssl;
//                detection = packet.detection();

//                idCam=detection.camera_id()+1;
//                balls_n = detection.balls_size();

//                //Ball info:
//                if(balls_n!=0){
//                    packetssl.balls[0]=idCam;
//                    ball = detection.balls(0);
//                    packetssl.balls[1]=ball.x();
//                    packetssl.balls[2]=ball.y();
//                }
//                else
//                    packetssl.balls[0]=0;

//                robots_blue_n =  detection.robots_blue_size();
//                robots_yellow_n =  detection.robots_yellow_size();

//                //Robot info

//                for (int j = 0; j < TEAM_COUNT/4; j++)
//                    if(packetssl.robots_blue[j]==idCam)
//                        packetssl.robots_blue[j]=0;
//                for (int i = 0; i < robots_blue_n; i++) {
//                    robot = detection.robots_blue(i);
//                    packetssl.robots_blue[robot.robot_id()]=idCam;
//                    packetssl.robots_blue[robot.robot_id()+12]=robot.x();
//                    packetssl.robots_blue[robot.robot_id()+24]=robot.y();
//                    packetssl.robots_blue[robot.robot_id()+36]=robot.orientation();
//                }

//                for (int j = 0; j < TEAM_COUNT/4; j++)
//                    if(packetssl.robots_yellow[j]==idCam)
//                        packetssl.robots_yellow[j]=0;
//                for (int i = 0; i < robots_yellow_n; i++) {
//                    robot = detection.robots_yellow(i);
//                    packetssl.robots_yellow[robot.robot_id()]=idCam;
//                    packetssl.robots_yellow[robot.robot_id()+12]=robot.x();
//                    packetssl.robots_yellow[robot.robot_id()+24]=robot.y();
//                    packetssl.robots_yellow[robot.robot_id()+36]=robot.orientation();
//                }



//                for ( i = 0; i < robots_blue_n+robots_yellow_n; i++ )
//                {
//  //               cout << "i=" << i << endl;
//                  if ( i<robots_blue_n )
//                  {
//                    robot = detection.robots_blue ( i );
//                    team = teamBlue;
//                    j=bluej;
//                  }
//                  else
//                  {
//                    robot = detection.robots_yellow ( i-robots_blue_n );
//                    team = teamYellow;
//                    j=yellowj;
//                  }

//                  conf =robot.confidence();
//                  int id=NA;
//                  if ( robot.has_robot_id() )
//                    id = robot.robot_id();
//                  else
//                    id = NA;
//                  x = robot.x();
//                  y = robot.y();
//                  if ( robot.has_orientation() )
//                    orientation = robot.orientation() *180.0/M_PI;
//                  else
//                    orientation = NAOrientation;

                  //seek to the next robot of the same camera and team colour
//                  while ( j<robots.size() && ( robots[j]->key!=detection.camera_id() || robots[j]->teamID!=team ) )
//                    j++;
//              //    cout << "robot size " << robots.size() << endl;

//                  if ( j+1>robots.size() )
//                    AddRobot ( new Robot ( x,y,orientation,team,id,detection.camera_id(),conf ) );

                emit activate();
            }
        }
    }

    client.close();
}
