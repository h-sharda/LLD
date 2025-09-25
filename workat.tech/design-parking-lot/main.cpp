#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;

// CONSTANTS

// VEHICLE MAP, where new slots and vehicles can be added for optional requirement
// {vehicle, {slot_intervals, id}}
const unordered_map<string, pair<vector<pii>, int>> VEHICLE_MAP = {
    {"TRUCK", {{{0, 1}}, 0}}, {"BIKE", {{{1, 3}}, 1}}, {"CAR", {{{3, INT_MAX}}, 2}}};

class ParkingLot {
    string id;
    int floors;
    int slots;

    struct Ticket {
        int floor;
        int slot;
        int type;
        string regNo;
        string color;

        Ticket(int f, int s, int t, string r, string c) : floor(f), slot(s), type(t), regNo(r), color(c) {
        }
    };

    unordered_map<int, priority_queue<pii, vector<pii>, greater<>>> unoccupied; // {vechile, {{floor, slot}}}
    unordered_map<string, Ticket *> tickets;

  public:
    ParkingLot(string _id, int _floors, int _slots) {
        id = _id;
        floors = _floors;
        slots = _slots;

        for (auto &[_, vehicle] : VEHICLE_MAP) {
            int type = vehicle.second;

            for (auto &[l, r] : vehicle.first) {
                for (int j = 0; j < floors; j++) {
                    for (int k = l; k < min(r, slots); k++)
                        unoccupied[type].emplace(j, k);
                }
            }
        }
    }

    string park(int type, string regNo, string color) {
        if (unoccupied[type].empty())
            return "";

        auto [floor, slot] = unoccupied[type].top();

        string ticket = id + "_" + to_string(floor + 1) + "_" + to_string(slot + 1);
        tickets[ticket] = new Ticket(floor, slot, type, regNo, color);

        unoccupied[type].pop();

        return ticket;
    }

    pair<string, string> unpark(string ticket) {
        if (!tickets.count(ticket))
            return {"", ""};

        Ticket *ptr = tickets[ticket];

        int floor = ptr->floor, slot = ptr->slot, type = ptr->type;
        string regNo = ptr->regNo, color = ptr->color;

        unoccupied[type].emplace(floor, slot);

        delete ptr;
        tickets.erase(ticket);

        return {regNo, color};
    }

    vector<int> unoccupiedCount(int type) {
        vector<int> ans(floors + 1, 0);
        auto copy = unoccupied[type];

        while (!copy.empty()) {
            auto [floor, slot] = copy.top();
            copy.pop();
            ans[floor + 1]++;
        }

        return ans;
    }

    vector<vector<int>> unoccupiedSlots(int type) {
        vector<vector<int>> ans(floors + 1);
        auto copy = unoccupied[type];

        while (!copy.empty()) {
            auto [floor, slot] = copy.top();
            copy.pop();
            ans[floor + 1].push_back(slot + 1);
        }

        for (auto &floor : ans)
            sort(floor.begin(), floor.end());

        return ans;
    }

    vector<vector<int>> occupiedSlots(int type) {
        vector<vector<int>> ans(floors + 1);

        for (auto &[_, ptr] : tickets) {
            if (ptr->type != type)
                continue;

            int floor = ptr->floor, slot = ptr->slot;
            ans[floor + 1].push_back(slot + 1);
        }

        for (auto &floor : ans)
            sort(floor.begin(), floor.end());

        return ans;
    }
};

class IO {
    // Singular parking lot as stated by problem statment
    ParkingLot *pl = nullptr;

    // For Optional Requirement this can be changed to unordered_map<string, *ParkingLot>.
    // Not implemented currently because the current methods don't send ParkingLot ID in input parameters.

  public:
    void begin() {
        while (true) {
            string line;
            getline(cin, line);

            vector<string> tokens;
            istringstream iss(line);
            string token;
            while (iss >> token)
                tokens.push_back(token);

            try {
                if (tokens[0] == "create_parking_lot") {

                    if (tokens.size() != 4)
                        throw invalid_argument("Invalid token length, Read README for proper deatails.");

                    int floors = stoi(tokens[2]), slots = stoi(tokens[3]);

                    if (pl != nullptr)
                        delete pl;

                    pl = new ParkingLot(tokens[1], floors, slots);

                    cout << "Created parking lot with " << floors << " floors and " << slots << " slots per floor\n";

                } else {
                    if (pl == nullptr) {
                        throw logic_error("Create parking lot before using functions.");
                    } else if (tokens[0] == "park_vehicle") {
                        if (tokens.size() != 4)
                            throw invalid_argument("Invalid token length, Read README for proper deatails.");

                        auto ptr = VEHICLE_MAP.find(tokens[1]);
                        if (ptr == VEHICLE_MAP.end())
                            throw invalid_argument("vehicle type not found.");

                        int type = ptr->second.second;

                        string ticket = pl->park(type, tokens[2], tokens[3]);
                        if (ticket.empty()) {
                            cout << "Parking Lot Full\n";
                        } else {
                            cout << "Parked vehicle. Ticket ID: " << ticket << "\n";
                        }
                    } else if (tokens[0] == "unpark_vehicle") {
                        if (tokens.size() != 2)
                            throw invalid_argument("Invalid token length, Read README for proper deatails.");

                        auto [regNo, color] = pl->unpark(tokens[1]);

                        if (regNo.empty()) {
                            cout << "Invalid Ticket\n";
                        } else {
                            cout << "Unparked vehicle with Registration Number: " << regNo << " and Color: " << color
                                 << "\n";
                        }

                    } else if (tokens[0] == "display") {
                        if (tokens.size() != 3)
                            throw invalid_argument("Invalid token length, Read README for proper deatails.");

                        auto ptr = VEHICLE_MAP.find(tokens[2]);
                        if (ptr == VEHICLE_MAP.end())
                            throw invalid_argument("vehicle type not found.");

                        int type = ptr->second.second;

                        if (tokens[1] == "free_count") {
                            auto res = pl->unoccupiedCount(type);
                            for (int i = 1; i < res.size(); i++) {
                                cout << "No. of free slots for " << tokens[2] << " on Floor " << i << ": " << res[i]
                                     << "\n";
                            }

                        } else if (tokens[1] == "free_slots") {
                            auto res = pl->unoccupiedSlots(type);

                            for (int i = 1; i < res.size(); i++) {
                                cout << "Free slots for " << tokens[2] << " on Floor " << i << ": ";
                                int sz = res[i].size();
                                for (int j = 0; j < sz; j++) {
                                    cout << res[i][j];
                                    if (j != sz - 1)
                                        cout << ",";
                                }
                                cout << "\n";
                            }

                        } else if (tokens[1] == "occupied_slots") {
                            auto res = pl->occupiedSlots(type);

                            for (int i = 1; i < res.size(); i++) {
                                cout << "Occupied slots for " << tokens[2] << " on Floor " << i << ": ";
                                int sz = res[i].size();
                                for (int j = 0; j < sz; j++) {
                                    cout << res[i][j];
                                    if (j != sz - 1)
                                        cout << ",";
                                }
                                cout << "\n";
                            }
                        } else {
                            throw invalid_argument("Invalid function used for display.");
                        }

                    } else if (tokens[0] == "exit") {
                        break;
                    } else {
                        // Additional Commands can be added here for Optional Requirement.
                        throw invalid_argument("Invalid function used.");
                    }
                }
            } catch (const invalid_argument &e) {
                cerr << "Invalid input: " << e.what() << '\n';
            } catch (const out_of_range &e) {
                cerr << "Out of range: " << e.what() << '\n';
            } catch (...) {
                cerr << "Unknown exception caught.\n";
            }
        }
    }
};

int main() {
    IO io;
    io.begin();

    return 0;
}
