#include <iostream>
#include <vector>
#include <string>
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
        bool equal = true;
        equal = equal && (m.music_id == music_id);
        equal = equal && (m.artist_name == artist_name);
        equal = equal && (m.year == year);
        return equal;
    };
};

class Song : public Music {
public:
    const string name;
    const string genre;
    unsigned int duration;

    Song() : Music(), name(""), genre(""), duration(0) {};

    Song(string _music_id, string _artist_name, unsigned int _year, string _name, string _genre, unsigned int _duration)
            :
            Music(_music_id, _artist_name, _year), name(std::move(_name)), genre(std::move(_genre)),
            duration(_duration) {};

    bool operator==(Song &s) {
        Music music = static_cast<Music>(*this);
        bool equal = true;
        equal = equal && (s.genre == genre);
        equal = equal && (s.name == name);
        equal = equal && (s.duration = duration);
        equal = equal && (music.music_id == music_id);
        equal = equal && (music.artist_name == artist_name);
        equal = equal && (music.year == year);
        return equal;
    };
};

const int max_playlist_songs = 3;

class Playlist {
    vector<Song> my_playlist;

public:
    bool insert_song(Song &song) {
        int songs_by_this_artist = 0;
        for (Song s : my_playlist) {
            if (s == song) {
                return false;
            }

            if (s.artist_name == song.artist_name) {
                songs_by_this_artist++;
                if (songs_by_this_artist == max_playlist_songs) {
                    return false;
                }
            }
        }
        my_playlist.push_back(song);
        return true;
    }

    Playlist shuffle_songs() {
        Playlist shuffled_playlist;

        vector<Song> copied_playlist(my_playlist);

        srand(time(0));
        while (copied_playlist.size() > 0) {
            int index = rand() % copied_playlist.size();
            shuffled_playlist.my_playlist.push_back(my_playlist.at(index));
            copied_playlist.erase(copied_playlist.begin() + (index - 1));
        }
        return shuffled_playlist;
    }

    friend Playlist operator+(Playlist &p1, Playlist &p2);

};

// must use p1/p2 because it is a friend function
Playlist operator+(Playlist &p1, Playlist &p2) {
    Playlist combined_playlist;
    combined_playlist.my_playlist = p1.my_playlist;

    for (int i = 0; i < p2.my_playlist.size(); i++) {
        combined_playlist.my_playlist.push_back(p2.my_playlist.at(i));
    }

    return combined_playlist;
}


int main() {

    Music music_test1 = Music("testId", "Drake", 2020);
    Song song_test1 = Song("testId", "Drake", 2020, "Forever", "Rap", 5);

}


