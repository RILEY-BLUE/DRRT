#ifndef DUBINSEDGE_H
#define DUBINSEDGE_H

// #include <DRRT/edge.h> to make a new type of edge
#include <DRRT/edge.h>


// #include this file in drrt_data_structures.h
// Remember to implement Edge::NewEdge(Eigen::VectorXd,Eigen::VectorXd)

class DubinsEdge : public Edge
{
public:
    // Constructors
    DubinsEdge()
        : Edge() {}

    DubinsEdge(std::shared_ptr<ConfigSpace> ConfigSpace,
               std::shared_ptr<KDTree> tree_,
               std::shared_ptr<KDTreeNode> start,
               std::shared_ptr<KDTreeNode> end)
        : Edge(ConfigSpace,tree_,start,end) {}

    bool ValidMove();
    Eigen::VectorXd PoseAtDistAlongEdge(double distAlongEdge);
    Eigen::VectorXd PoseAtTimeAlongEdge(double timeAlongEdge);
    void CalculateTrajectory();
    void CalculateHoverTrajectory();
    bool ExplicitEdgeCheck(std::shared_ptr<Obstacle> obstacle);
};

#endif // DUBINSEDGE_H
