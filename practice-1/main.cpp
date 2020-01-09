#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

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
class Song : public Music {
public:
    const string genre;
    const string name;
    unsigned int duration;

    Song() : genre(""), name(""), duration(0) {
    };

    Song(string _genre, string _name, unsigned int _duration) : genre(_genre), name(_name), duration(_duration) {};

    bool operator==(Song &s) {
        return s.id == id;
    };
};

const int MAX_SONGS_PER_ARTIST_IN_PLAYLIST = 3;

class Playlist {
public:
    vector<Song> tracks;

    Playlist() : tracks({}) {};

    explicit Playlist(vector<Song> &_tracks) : tracks(_tracks) {};

    friend Playlist operator+(Playlist &p1, Playlist &p2);

    Playlist shuffle_songs() {
        auto shuffled_tracks = vector(tracks);
        auto rng = default_random_engine{0};
        shuffle(begin(shuffled_tracks), end(shuffled_tracks), rng);
        return Playlist(shuffled_tracks);
    }

    bool insert_song(Song &song) {
        int songs_by_this_artist = 0;
        for (Song s : tracks) {
            if (s == song) {
                return false;
            }
            if (s.artist_name == song.artist_name) {
                songs_by_this_artist += 1;
                if (songs_by_this_artist == MAX_SONGS_PER_ARTIST_IN_PLAYLIST) {
                    return false;
                }
            }
        }
        tracks.push_back(song);
        return true;
    }
};

Playlist operator+(Playlist &p1, Playlist &p2) {
    auto tracks = vector(p1.tracks);
    tracks.insert(tracks.end(), p2.tracks.begin(), p2.tracks.end());
    return Playlist(tracks);
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
