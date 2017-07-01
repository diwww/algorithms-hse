#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include <algorithm>
#include "RailSystem.h"

void RailSystem::reset(void)
{
    for (std::pair<std::string, City*> city : cities)
    {
        city.second->total_fee = INT_MAX;
        city.second->from_city = "";
        city.second->total_distance = 0;
        city.second->visited = false;
    }
}

RailSystem::RailSystem(string const& filename)
{
    load_services(filename);
}

void RailSystem::load_services(string const& filename)
{
    ifstream inf(filename.c_str());
    string from, to;
    int fee, distance;

    while (inf.good())
    {

        // Read in the from city, to city, the fee, and distance.
        inf >> from >> to >> fee >> distance;

        if (inf.good())
        {
            // "If statement" here helps to avoid
            // duplicates and therefore memory leaks
            if (!is_valid_city(from))
                cities[from] = new City(from);

            // No need to check key existence here,
            // since the value is not a pointer
            outgoing_services[from].push_back(new Service(to, fee, distance));
        }
    }

    inf.close();
}

RailSystem::~RailSystem(void)
{
    for (std::pair<std::string, City*> city : cities)
        delete city.second;
    for (std::pair<std::string, std::list<Service* >> services : outgoing_services)
        for (Service* service : services.second)
            delete service;
}

void RailSystem::output_cheapest_route(const string& from, const string& to, ostream& out)
{
    reset();
    pair<int, int> totals = calc_route(from, to);

    if (totals.first == INT_MAX)
        out << "There is no route from " << from << " to " << to << "\n";
    else
    {
        out << "The cheapest route from " << from << " to " << to << "\n";
        out << "costs " << totals.first << " euros and spans " << totals.second
            << " kilometers\n";
        cout << recover_route(to) << "\n\n";
    }
}

bool RailSystem::is_valid_city(const string& name)
{
    return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(string from, string to)
{
    // Unvisited cities
    std::vector<City*> candidates;
    candidates.reserve(cities.size());

    // TODO: if check necessity
    // Initial node
    if (is_valid_city(from))
        cities[from]->total_fee = 0;

    for (std::pair<std::string, City*> city : cities)
        candidates.push_back(city.second);

    while (!candidates.empty())
    {
        std::sort(candidates.begin(), candidates.end(), Cheapest());
        City* minFeeCity = candidates.back();

        // If minFeeCity's total_fee is equal
        // to INT_MAX, then all reachable cities
        // are already visited
        if (minFeeCity->total_fee == INT_MAX)
            break;

        for (Service* service : outgoing_services[minFeeCity->name])
            if (cities[service->destination]->total_fee > minFeeCity->total_fee + service->fee)
            {
                cities[service->destination]->total_fee = minFeeCity->total_fee + service->fee;
                // TODO: check distance calculation
                cities[service->destination]->total_distance =
                        minFeeCity->total_distance + service->distance;
                cities[service->destination]->from_city = minFeeCity->name;
            }

        // Mark city visited and pop it
        // from unvisited vector
        minFeeCity->visited = true;
        candidates.pop_back();
    }

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited)
    {
        return pair<int, int>(cities[to]->total_fee, cities[to]->total_distance);
    }
    else
    {
        return pair<int, int>(INT_MAX, INT_MAX);
    }
}

string RailSystem::recover_route(const string& city)
{
    std::string temp = city;
    std::string currentCity = city;

    while (cities[currentCity]->from_city != "")
    {
        temp.insert(0, cities[currentCity]->from_city + " to ");
        currentCity = cities[currentCity]->from_city;
    }

    return temp;
}


Route RailSystem::getCheapestRoute(const string& from, const string& to)
{
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p = calc_route(from, to);
    return Route(from, to, p.first, p.second);
}