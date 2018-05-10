#include <unordered_set>
#include <memory>

class Room;

class RoomMaintainer {
    public:
        RoomMaintainer();
        void visit(std::shared_ptr<Room> room);
        void cleanup();
    private:
        std::unordered_set<std::shared_ptr<Room>> rooms;
};