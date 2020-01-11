#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

class Music {
public:
    const string music_id;
    const string artist_name;
    unsigned int year;

    Music() : music_id(""), artist_name(""), year(0) {};

    Music(string _music_id, string _artist_name, unsigned int _year) :
            music_id(std::move(_music_id)),
            artist_name(std::move(_artist_name)),
            year(_year) {};

    string get_artist() {
        return artist_name;
    };

    bool operator==(Music &m) {
        return (m.music_id == music_id && m.artist_name == artist_name && m.year == year);
    };
};

class Song : public Music {
public:
    const string genre;
    const string name;
    unsigned int duration;

    Song() : Music(), name(""), genre(""), duration(0) {};

    Song(string _music_id,
         string _artist_name,
         unsigned int _year,
         string _name,
         string _genre,
         unsigned int _duration) :
            Music(_music_id, _artist_name, _year),
    name(std::move(_name)),
    genre(std::move(_genre)),
    duration(_duration) {};

    bool operator==(Song &s) {
        return (s.year == year &&
                s.duration == duration &&
                s.music_id == music_id &&
                s.artist_name == artist_name &&
                s.name == name &&
                s.genre == genre);
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
                songs_by_this_artist++;
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





}
