#ifndef PACKETSSL_H
#define PACKETSSL_H

#include <QVector>
#include <QPoint>

#define TEAM_COUNT 48
#define BALL_COUNT 3
#define TEAM_COUNT_d (TEAM_COUNT * sizeof(double))
#define BALL_COUNT_d (BALL_COUNT * sizeof(double))

struct PacketSSL
{
    PacketSSL()
    {
        memset(robots_blue, 0, TEAM_COUNT_d);
        memset(robots_yellow, 0, TEAM_COUNT_d);
        memset(balls, 0, BALL_COUNT_d);
    }

    PacketSSL(const PacketSSL &ps)
    {
        memcpy(robots_blue, ps.robots_blue, TEAM_COUNT_d);
        memcpy(robots_yellow, ps.robots_yellow, TEAM_COUNT_d);
        memcpy(balls, ps.balls, BALL_COUNT_d);
    }

    double robots_blue[48];
    double robots_yellow[48];
    double balls[3];
};

#endif // PACKETSSL_H
