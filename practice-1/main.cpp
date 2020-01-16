#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

static default_random_engine rnd_gen;

int randint(const int low, const int high) {
    return uniform_int_distribution(low, high)(rnd_gen);
}

class Music {
    string id;
    string artist_name;
    unsigned int year;

public:

    Music() : id(""), artist_name(""), year(0) {}

    Music(string new_id, string new_artist_name, unsigned int new_year)
            : id(std::move(new_id)), artist_name(std::move(new_artist_name)), year(new_year) {}

    string get_id() const {
        return id;
    }

    string get_artist_name() const {
        return artist_name;
    }

    unsigned int get_year() const {
        return year;
    }

    bool operator==(const Music &m) const {
        return m.id == id && m.artist_name == artist_name && m.year == year;
    }

    bool operator!=(const Music &m) const {
        return this != &m;
    }
};

class Song : public Music {
    string name;
    string genre;
    unsigned int duration;

public:

    Song() : Music(), name(""), genre(""), duration(0) {}

    Song(Music new_music, string new_name, string new_genre, unsigned int new_duration)
            : Music(std::move(new_music)), name(std::move(new_name)), genre(std::move(new_genre)),
              duration(new_duration) {}

    string get_name() const {
        return name;
    }

    string get_genre() const {
        return genre;
    }

    unsigned int get_duration() const {
        return duration;
    }

    bool operator==(const Song &s) const {
        if (s.genre != genre || s.name != name || s.duration != duration) {
            return false;
        }
        Music this_music = static_cast<Music>(*this);
        Music m = static_cast<Music>(s);
        return this_music == m;
    };

    bool operator!=(const Song &s) const {
        return this != &s;
    }
};


class Playlist {
    static const int MAX_TRACKS_PER_ARTIST = 3;
    vector<Song> tracks;

public:
    Playlist() : tracks({}) {};

    explicit Playlist(vector<Song> &new_tracks) : tracks(new_tracks) {};

    bool insert_song(Song &song) {
        int songs_by_this_artist = 0;
        for (Song s : tracks) {
            if (s == song) {
                return false;
            }
            if (s.get_artist_name() == song.get_artist_name()) {
                songs_by_this_artist++;
                if (songs_by_this_artist == MAX_TRACKS_PER_ARTIST) {
                    return false;
                }
            }
        }
        tracks.push_back(song);
        return true;
    }

    vector<Song> get_tracks() const {
        return tracks;
    }

    Playlist shuffle_songs() const {
        vector<Song> shuffled_tracks(tracks);
        const int tracks_count = shuffled_tracks.size();
        for (int i = tracks_count - 1; i > 0; i -= 1) {
            int j = randint(i, tracks_count - 1);
            swap(shuffled_tracks[i], shuffled_tracks[j]);
        }
        return Playlist(shuffled_tracks);
    }

    friend Playlist operator+(Playlist &p1, Playlist &p2);
};


Playlist operator+(Playlist &p1, Playlist &p2) {
    vector<Song> combined_tracks(p1.tracks);
    combined_tracks.insert(combined_tracks.end(), p2.tracks.begin(), p2.tracks.end());
    return Playlist(combined_tracks);
}

void test_music() {
    cout << "\tMusic" << endl;
    cout << "\t\tempty constructor" << endl;
    Music music_0;
    assert(music_0.get_id().empty());
    assert(music_0.get_artist_name().empty());
    assert(music_0.get_year() == 0);

    cout << "\t\tconstructor" << endl;
    Music music_1 = Music("testId", "Playboi Carti", 2020);
    assert(music_1.get_id() == "testId");
    assert(music_1.get_artist_name() == "Playboi Carti");
    assert(music_1.get_year() == 2020);

    cout << "\t\toperator==" << endl;
    Music music_2 = Music("anotherId", "Frank Sinatra", 1969);
    assert(music_1 != music_2);
}

void test_song() {
    cout << "\tSong" << endl;
    cout << "\t\tempty constructor" << endl;
    Song song_0;
    assert(song_0.get_id().empty());
    assert(song_0.get_artist_name().empty());
    assert(song_0.get_year() == 0);
    assert(song_0.get_name().empty());
    assert(song_0.get_genre().empty());
    assert(song_0.get_duration() == 0);

    cout << "\t\tconstructor" << endl;
    Music music_1 = Music("testId", "Playboi Carti", 2020);
    Song song_1 = Song(music_1, "Long time", "Rap", 2);
    assert(song_1.get_id() == music_1.get_id());
    assert(song_1.get_name() == "Long time");
    assert(song_1.get_genre() == "Rap");
    assert(song_1.get_duration() == 2);

    cout << "\t\toperator==" << endl;
    Song song_2 = Song(music_1, "Shoota", "Rap", 4);
    assert(song_1 == song_1);
    assert(song_1 != song_2);
}

void test_playlist() {
    Music music_1 = Music("testId", "Playboi Carti", 2020);
    Song song_1 = Song(music_1, "Long time", "Rap", 2);
    Song song_2 = Song(music_1, "Shoota", "Rap", 4);
    Song song_3 = Song(music_1, "Mileage", "Rap", 5);
    Song song_4 = Song(music_1, "Poke it out", "Rap", 2);

    Playlist my_playlist;

    cout << "\tPlaylist" << endl;
    cout << "\t\t.insert_song(&Song)" << endl;
    assert(my_playlist.insert_song(song_1));
    assert(my_playlist.insert_song(song_2));
    assert(my_playlist.insert_song(song_3));

    cout << "\t\tinserting a duplicate song" << endl;
    assert(!my_playlist.insert_song(song_1));

    cout << "\t\tinserting too many songs by the same artist" << endl;
    assert(!my_playlist.insert_song(song_4));
    assert(my_playlist.get_tracks().size() == 3); // the 4th track should not have been inserted

    cout << "\t\t.shuffle_songs()" << endl;
    auto tracks = my_playlist.get_tracks();
    auto shuffled_playlist = my_playlist.shuffle_songs();
    auto shuffled = shuffled_playlist.get_tracks();
    assert(tracks.at(0) != shuffled.at(0) || tracks.at(1) != shuffled.at(1) || tracks.at(2) != shuffled.at(2));

    assert(!shuffled_playlist.insert_song(song_4));

    cout << "\t\toperator+" << endl;
    Playlist other_playlist;
    assert(other_playlist.insert_song(song_4));
    auto combined_playlist = my_playlist + other_playlist;
    assert(combined_playlist.get_tracks().size() == 4);
}

int main() {
    srand(time(nullptr));

    cout << endl << "Testing...";
    cout << endl << endl;
    test_music();
    cout << endl;
    test_song();
    cout << endl;
    test_playlist();
    cout << endl << endl;
    cout << "All tests completed successfully!" << endl;

    return 0;
};
<<<<<<< Updated upstream
=======

//    Music music_1 = Music("testId", "Mac Miller", 2020);
//
//    Song song_1 = Song(music_1, "Good News", "Rap", 5);
//    Song song_2 = Song(music_1, "Best Day Ever", "Rap", 2);
//    Song song_3 = Song(music_1, "Nikes on my Feet", "Rap", 4);
//    Song song_4 = Song(music_1, "Wings", "Rap", 4);
//
//    Playlist playlistTwo;
//
//    playlistTwo.insert_song(song_1);
//    playlistTwo.insert_song(song_2);
//    playlistTwo.insert_song(song_3);
//    playlistTwo.insert_song(song_4);
//    playlistTwo.insert_song(song_1);
//
//    Playlist shuffled_playlist_test = playlistTwo.shuffle_songs();
//
//    playlistTwo.print();
//    shuffled_playlist_test.print();

>>>>>>> Stashed changes
