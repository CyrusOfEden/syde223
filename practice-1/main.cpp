#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

class Music {
    string music_id;
    string artist_name;
    unsigned int year;

public:

    Music() : music_id(""), artist_name(""), year(0) {}

    Music(string new_music_id, string new_artist_name, unsigned int new_year)
            : music_id(new_music_id), artist_name(new_artist_name), year(new_year) {}

    string get_music_id() {
        return music_id;
    }

    string get_artist_name() {
        return artist_name;
    }

    unsigned int get_year() {
        return year;
    }

    bool operator==(const Music &m) {
        bool equal = true;
        equal = equal && (m.music_id == music_id);
        equal = equal && (m.artist_name == artist_name);
        equal = equal && (m.year == year);
        return equal;
    }
};

class Song : public Music {
    string name;
    string genre;
    unsigned int duration;

public:

    Song() : Music(), name(""), genre(""), duration(0) {}

    Song(Music new_music, string new_name, string new_genre, unsigned int new_duration)
            : Music(new_music), name(new_name), genre(new_genre), duration(new_duration) {}

    bool operator==(Song &s) {
        bool equal = true;
        equal = equal && (s.genre == genre);
        equal = equal && (s.name == name);
        equal = equal && (s.duration == duration);
        equal = equal && static_cast<Music>(*this) == static_cast<Music>(s);
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

            if (s.get_artist_name() == song.get_artist_name()) {
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

    // Music music_test1 = Music("testId", "Drake", 2020);
    // Song song_test1 = Song(music_test1, "Forever", "Rap", 5);
}




