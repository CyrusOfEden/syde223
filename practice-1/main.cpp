#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Music {
public:
    const string id;
    const string artist_name;
    unsigned int year;

    Music() : id(""), artist_name(""), year(0) {};

    Music(string _id, string _artist, unsigned int _year) : id(_id), artist_name(_artist), year(_year) {};

    string get_artist() {
        return artist_name;
    };

    bool operator==(Music &m) {
        return m.id == id;
    };
};

// requires: genre, song name, song length (unsigned int)
class Song : Music {
public:
    const string genre;
    const string song_name;
    unsigned int song_length;

    Song() : genre(""), song_name(""), song_length(0) {
        super();
    };

    Song(string _genre, string _song_name, unsigned int _song_length) : genre(_genre), song_name(_song_name),
                                                                        song_length(_song_length) {};

    bool operator==(Song &s) {
        return s.id == id;
    };
};

};

class Playlist {
};

int main() {
    srand(time(0));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
