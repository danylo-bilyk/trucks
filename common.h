#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include <list>

namespace   my {
class                           Scene;

class                           Link;
class                           Node;
class                           Truck;

typedef Scene                   *ScenePtr;
typedef Link                    *LinkPtr;
typedef Node                    *NodePtr;
typedef Truck                   *TruckPtr;

typedef std::vector<LinkPtr>    LinksArray;
typedef std::list<LinkPtr>      LinksList;

typedef std::vector<NodePtr>    NodesArray;
typedef std::list<NodePtr>      NodesList;

typedef std::vector<TruckPtr>   TrucksArray;
typedef std::list<TruckPtr>     TrucksList;

enum NodeType {
    INTERCHANGE,
    STORAGE,
    MINEDUMP
};

typedef std::size_t size_t;

typedef std::vector<size_t> Route;
typedef std::vector<Route> Routes;

typedef std::vector<double> Distances;
typedef std::vector<Distances> DistanceMatrix;

class Data {

    public:
        Data(ScenePtr scene);

        size_t      getNodesCount()     { return (Nodes.size()); }

        size_t      getTrucksCount()    { return (Trucks.size()); }

        TruckPtr    getTruck(size_t i)  { return (Trucks.at(i)); }

        double      getEmptySpeed()     { return (EmptySpeed); }

        double      getFullSpeed()      { return (FullSpeed); }

    private:
        ScenePtr        Scene;

        double          EmptySpeed;
        double          FullSpeed;

        DistanceMatrix  NodesDistances;

        NodesArray      Nodes;
        TrucksArray     Trucks;
        LinksArray      Links;

        Routes          TrucksRoutes;
};
}

#endif //COMMON_H
