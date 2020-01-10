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
    const string music_id;
    const string artist_name;
    unsigned int year;

    Music() {
        music_id = "";
        artist_name = "";
        year = 0;
    };

    Music(string _music_id, string _artist_name, unsigned int _year) {
        music_id = _music_id;
        artist_name = _artist_name;
        year = _year;
    };

    string get_artist() {
        return artist_name;
    };

    bool operator==(Music &m) {
        bool is_equal = true;
        is_equal = is_equal && (m.music_id == music_id);
        is_equal = is_equal && (m.artist_name == artist_name);
        is_equal = is_equal && (m.year == year);
        return is_equal;
    };
};

class Song : public Music {
public:
    const string genre;
    const string name;
    unsigned int duration;

    Song() {
        genre = "";
        name = "";
        duration = 0;
    };

    Song(string _genre, string _name, unsigned int _duration) {
        genre = _genre;
        name = _name;
        duration = _duration;
    };

    bool operator==(Song &s) {
        Music music = static_cast<Music>(this);
        bool is_equal = true;
        is_equal = is_equal && (s.genre == genre);
        is_equal = is_equal && (s.name == name);
        is_equal = is_equal && (s.duration = duration);
        is_equal = is_equal && (music.music_id == music_id);
        is_equal = is_equal && (music.artist_name == artist_name);
        is_equal = is_equal && (music.year == year);
        return is_equal;
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
