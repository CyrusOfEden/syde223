#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Artwork {
};

class Music {
public:
    Artwork artwork;
    const string id;
    const string artist_name;
    unsigned int year;

    Music() : id(""), artist_name(""), year(0) {};

    Music(string &_id, string &_artist, unsigned int _year) : id(_id), artist_name(_artist), year(_year) {};

    string get_artist() {
        return artist_name;
    };

    bool operator==(Music &m) {
        return m.id == id;
    };
};

class Song {
};

class Playlist {
};

int main() {
    srand(time(0));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
